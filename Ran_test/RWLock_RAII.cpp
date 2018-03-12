#include <iostream>
#include <mutex>
#include <condition_variable>

//C++实现的读写锁，直接使用lock、unlock在c++中是不推荐的，推荐采用RAII方法，即类unique_writeguard、unique_readguard
using std::cout;
using std::endl;

class WfirstRWLock{
public:
    WfirstRWLock() = default;
    ~WfirstRWLock() = default;

    void lock_read(){
        std::unique_lock<std::mutex> ulk(counter_metex);
        cond_r.wait(ulk, [=]()-> bool { return write_cnt == 0;});
        ++read_cnt;
    }

    void lock_write(){
        std::unique_lock<std::mutex> ulk(counter_metex);
        ++write_cnt;
        cond_w.wait(ulk, [=]-> bool {return read_cnt == 0 && !inwriteflag;});
        inwriteflag = true;
    }

    void releasr_read(){
        std::unique_lock<std::mutex> ulk(counter_metex);
        if(--read_cnt == 0 && write_cnt > 0)
            cond_w.notify_one();
    }

    void release_write(){
        std::unique_lock<std::mutex> ulk(counter_metex);
        if(--write_cnt == 0)
            cond_r.notify_all();
        else
            cond_w.notify_one();
        inwriteflag = false;
    }

private:
    volatile size_t read_cnt {0};
    volatile size_t write_cnt {0};
    volatile bool inwriteflag {false};
    std::mutex counter_metex;
    std::condition_variable cond_w;
    std::condition_variable cond_r;
};

template <typename _RWLockable>
class unique_writeguard{
public:
    explicit unique_writeguard(_RWLockable &rw_lockable):rw_lockable_(rw_lockable){
        rw_lockable_.lock_write();
    }
    ~unique_writeguard(){
        rw_lockable_.release_write();
    }

private:
    unique_writeguard() = delete;
    unique_writeguard(const unique_writeguard&) = delete;
    unique_writeguard& operator=(const unique_writeguard&) = delete;

    _RWLockable *rw_lockable_;
};

template <typename _RWLockable>
class unique_readguard{
public:
    explicit unique_readguard(_RWLockable &rw_lockable):rw_lockable_(rw_lockable){
        rw_lockable_.lock_read();
    }
    ~unique_readguard(){
        rw_lockable_.release_read();
    }

private:
    unique_readguard() = delete;
    unique_readguard(const unique_readguard&) = delete;
    unique_readguard& operator=(const unique_readguard&) = delete;   //赋值构造函数返回值为引用用于连续赋值

    _RWLockable *rw_lockable_;
};


int main(){

    return 0;
}