#ifndef DRILL_COMMON_ATOMIC_H_
#define DRILL_COMMON_ATOMIC_H_
#include <cstdint>
#include <cstddef>

namespace drill{
namespace common{

template<typename T>

class AtomicIntegerT{
public:
	AtomicIntegerT(): _value(0)  {  }
	T get()
	{
	    return __sync_val_compare_and_swap(&_value, 0, 0);
	}
	bool test(T x)
	{
		return __sync_bool_compare_and_swap(&_value,x,x);
	}

	bool testAndset(T oldval, T newval)
	{
		return __sync_bool_compare_and_swap(oldval, newval);
	}
	
	
	T getAndAdd(T x)
	{  
	  	return __sync_fetch_and_add(&_value, x);
	}

	T getAndSub(T x)
	{
		return getAndAdd(-x);
	}
	T addAndGet(T x)  {    return getAndAdd(x) + x;  }

	T subAndGet(T x) { return getAndAdd(-x) - x; } 
	
	T incrementAndGet()  {    return addAndGet(1);  }
	T decrementAndGet()  {    return addAndGet(-1);  }
	void add(T x)  {    getAndAdd(x);  }

	void increment()  {    incrementAndGet();  }

	void decrement()  {    decrementAndGet();  }

	T getAndSet(T newValue)
	{
		return __sync_lock_test_and_set(&_value, 
												newValue);  
	}
	
private:
	 volatile T _value;
};
typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;
typedef AtomicIntegerT<size_t>  AtomicSizeT;


}
}
#endif
