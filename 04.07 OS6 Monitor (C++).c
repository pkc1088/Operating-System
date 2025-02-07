//Ice provides monitors with the IceUtil::Monitor class 
//(defined in IceUtil/Monitor.h):
namespace IceUtil
{
    template <class T>
    class Monitor 
    {
    public:
        void lock() const;
        void unlock() const;
        bool tryLock() const;
 
        void wait() const;
        bool timedWait(const Time&) const;
        void notify();
        void notifyAll();
 
        typedef LockT<Monitor<T> > Lock;
        typedef TryLockT<Monitor<T> > TryLock;
    };
}
//Note that Monitor is a template class that requires either Mutex or RecMutex as its template parameter. 
//(Instantiating a Monitor with a RecMutex makes the monitor recursive.)

template<class T> class Queue : public IceUtil::Monitor<IceUtil::Mutex>
{
public:
    Queue() : _waitingReaders(0) {}
 
    void put(const T& item)
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        _q.push_back(item);
        if(_waitingReaders)
        {
            notify();
        }
    }
 
    T get()
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        while(_q.size() == 0)
        {
            try 
            {
                ++_waitingReaders;
                wait();
                --_waitingReaders;
            }
            catch (...)
            {
                --_waitingReaders;
                throw;
            }
        }
        T item = _q.front();
        _q.pop_front();
        return item;
    }
 
private:
    list<T> _q;
    short _waitingReaders;
};
//A better option than calling notifyAll is to wake up waiting readers one at a time. 
//To do this, we keep track of the number of waiting readers 
//and call notify only if a reader needs to be woken up:


