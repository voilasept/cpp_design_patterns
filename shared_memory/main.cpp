#include <iostream>
#include <cstring>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/process.hpp>

using namespace std;
namespace ipc = boost::interprocess;

// $ Users/hanchen/CLionProjects/shared_memory/cmake-build-debug/shared_memory master

void console_out_read(boost::process::ipstream& outstream)
{
    // to redirect stdio
    // https://stackoverflow.com/questions/57262709/read-cout-and-write-to-cin-of-a-process-with-boostprocess
    std::string line;
    while (std::getline(outstream, line))
    {
        std::cout << line << '\n';
    }
}

int main(int argc, char *argv[]) {

    string pn (argv[1]);
    cout << pn << endl;

    if (pn == "master") {
        // shared_memory is OS persistent, still exist even after process died!
        if(ipc::shared_memory_object::remove("message_relay")){
            cout << "successfully removed shared memory" << endl;
        }
        boost::process::ipstream outstream;

        ipc::shared_memory_object shm_obj {ipc::create_only, "message_relay", ipc::read_write};
        shm_obj.truncate(sizeof(double) * 2);   // not map to any process yet

        /* map shared_memory_object (from shared memory) into a process' address space.
        * In fact, the OS can map a region larger than the requested size
        * (because the region must be multiples of page size [e.g. 512bytes]),
        * but mapped region will always refer to the user-requested size.
        */
        /* specify entire region if default offset and size */
        ipc::mapped_region region(shm_obj, ipc::read_write);
        cout << region.get_address() << " " << region.get_size() << endl;
        for (int i = 0; i < region.get_size(); i++) {
            memset(static_cast<char *>(region.get_address()) + i, (i - 'a') % ('z' - 'a') + 'a', 1);
        }
        std::thread cro([&](){ console_out_read(outstream);});
        boost::process::child cproc (
                "/Users/hanchen/CLionProjects/shared_memory/cmake-build-debug/shared_memory child",
                boost::process::std_out > outstream);
        cproc.wait();
        cro.join();

        // user must explicitly destroy it
        ipc::shared_memory_object::remove(shm_obj.get_name());
    }
    else if (pn == "child"){
        cout << "child launched" << endl;
        ipc::shared_memory_object shm_obj {ipc::open_only, "message_relay", ipc::read_only};
        ipc::mapped_region region(shm_obj, ipc::read_only);
        auto* addr = static_cast<char*>(region.get_address());
        for(int i = 0; i < region.get_size(); i++){
            cout << *(addr + i) << " ";
        }
    }

    return 0;
}
