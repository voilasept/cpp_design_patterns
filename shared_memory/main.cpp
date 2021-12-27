#include <iostream>
#include <cstring>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;
namespace ipc = boost::interprocess;

int main() {

    // shared_memory is OS persistent, still exist even after process died!
    if(ipc::shared_memory_object::remove("message_relay")){
        cout << "successfully removed shared memory" << endl;
    }

    ipc::shared_memory_object shm_obj {ipc::create_only, "message_relay", ipc::read_write};


    shm_obj.truncate(sizeof(double) * 2);   // not map to any process yet

    /* map shared_memory_object (from shared memory) into a process' address space.
     * In fact, the OS can map a region larger than the requested size
     * (because the region must be multiples of page size [e.g. 512bytes]),
     * but mapped region will always refer to the user-requested size.
     */
    /* specify entire region if default offset and size */
    ipc::mapped_region region (shm_obj, ipc::read_write);  // Cannot allocate memory
    cout << region.get_address() << " " << region.get_size() << endl;
    for(int i=0; i<region.get_size(); i++) {
        memset(region.get_address(), (i-'a')%('z'-'a'), region.get_size());
    }


    // shared memory is persistent, user must explicitly destroy it
    ipc::shared_memory_object::remove(shm_obj.get_name());

    return 0;
}
