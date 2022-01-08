#ifndef SIGMAX_POOL_MGR_H
#define SIGMAX_POOL_MGR_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cassert>
#include "common.h"
using namespace std;

template<typename DataType>
class PoolMgr{
protected:
    vector<PID> pids;
    vector<DataType> pool;
public:
    template <typename ...Args>
    explicit PoolMgr(size_t num_size, Args&& ...args);
    ~PoolMgr(){ clear(); }
    DataType& dispense();
    PID peek_next();
    void recycle(DataType&& data_obj);
    void clear();
    void dump(const string& tag = "") const;
};

template<typename DataType>
template<typename ...Args>
PoolMgr<DataType>::PoolMgr(size_t num_size, Args&& ...args)
        : pids(vector<PID>(num_size+1)),
          pool(vector<DataType>(num_size+1, {forward<Args>(args)...}))
{
    for(int i=0; i<pids.capacity(); i++){
        pids[i] = i;
    }
}

template<typename DataType>
DataType& PoolMgr<DataType>::dispense() {
    if(pids[0]+1 >= pids.capacity()) {  // expand
        size_t old_capacity = pids.capacity();
        pids.resize(old_capacity * 2);
#ifdef DEBUG
        cout << "Resize pool: " << old_capacity << " to "
             << pids.capacity() << endl;
#endif
        for(size_t i=old_capacity; i<pids.capacity(); i++){
            pids[i] = i;
        }
        pool.resize(pids.capacity(), pool[0]);
    }
    pids[0] += 1;
    PID _pid = pids[pids[0]];
    pool[_pid].pid = pids[0];
    return pool[_pid];
}

template<typename DataType>
PID PoolMgr<DataType>::peek_next() {
#ifdef DEBUG
    if (pids[0]+1 >= pids.capacity()) {
        cout << "Peek exceed, need to expand" << endl;
    }
#endif
    return pids[pids[0]+1];
}

template<typename DataType>
void PoolMgr<DataType>::recycle(DataType &&obj) {
    pool[pids[pids[0]]].pid = obj.pid;
    swap(pids[obj.pid], pids[pids[0]]);
    pids[0] -= 1;
}

template<typename DataType>
void PoolMgr<DataType>::clear(){
    for(int i=0; i<pids.capacity(); i++){
        pids[i] = i;
    }
}

template<typename DataType>
void PoolMgr<DataType>::dump(const string &tag) const {
    cout << tag << " ----------------" << endl;
    cout << tag << " PoolMgrType::dump() " << "len(pids):" << pids.size()
         << " len(data):" << pool.size() << " capacity:" << pool.capacity()
         << endl;
    auto cur_id = pids[0];
    cout << tag << " cur_id:" << cur_id << endl;
    cout << tag << " ";
    for(auto i=1; i<min(cur_id+1, pool.size()); i++){
        cout << pids[i] << " ";
    }
    cout << endl;
    cout << tag << " Dumping Pool:" << endl;
    for(auto i=1; i<min(cur_id+1, pool.size()); i++){
        PID _pid = pids[i];
        cout << tag << " ";
        pool[_pid].dump();
    }
    cout << tag << " ----------------" << endl;
}

#endif //SIGMAX_POOL_MGR_H
