#ifndef __CSINGLETON_H__
#define __CSINGLETON_H__

#include <assert.h>

template <class Type>
class CSingleton
{
protected:
	CSingleton()
	{
		assert(Pointer == 0 && "CSingleton::CSingleton(): Pointer is not NULL");
		Pointer = static_cast<Type *>(this);
	}
	~CSingleton() { Pointer = 0; }

public:
	static __forceinline Type *Get()
	{
		return Pointer;
	}
	static __forceinline Type &Inst()
	{
		assert(pointer != 0 && "CSingleton::Inst(): Pointer is NULL");
		return *Pointer;
	}

private:
	static Type * Pointer;
};

template <class Type>
Type *CSingleton<Type>::Pointer = 0;


#endif /* __CSINGLETON_H__ */
