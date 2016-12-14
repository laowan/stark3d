#ifndef _GLOBAL_H
#define _GLOBAL_H

#ifndef STARK_API
    #ifdef STARK_BUILD
        #define STARK_API /*__declspec(dllexport)*/
    #else
        #define STARK_API /*__declspec(dllimport)*/
    #endif
#endif

typedef signed char int8;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

#define SK_BEGIN_NAMESPACE namespace SK {
#define SK_END_NAMESPACE }
#define SK_USE_NAMESPACE using namespace SK;

// typical pimpl idiom
template <typename SELF>
class STARK_API Impl
{
public:
    inline virtual ~Impl() {}
    SELF* __self__;
};

template <typename SELF, typename IMPL>
class STARK_API pImpl
{
public:
    inline pImpl(void) : __impl__(new IMPL) {}
    inline pImpl(IMPL* impl) : __impl__(impl) {}
    inline ~pImpl(void) { delete __impl__; }
    inline IMPL* operator()(SELF* self) { __impl__->__self__ = self; return __impl__; }
    inline operator IMPL*(void) { return __impl__; }
    inline operator const IMPL*(void) const { return __impl__; }
    inline IMPL* operator->(void) { return __impl__; }
    inline const IMPL* operator->(void) const { return __impl__; }
    inline IMPL& operator*(void) { return __impl__; }
    inline const IMPL& operator*(void) const { return __impl__; }
    inline IMPL* get(void) { return __impl__; }
    inline const IMPL* get(void) const { return __impl__; }
    inline void swap(pImpl& t) { IMPL* s = __impl__; __impl__ = t.__impl__; t.__impl__ = s; }
protected:
    IMPL* __impl__;
private:
    pImpl(const pImpl&);
    pImpl& operator=(const pImpl&);
    bool operator==(const pImpl& t);
    bool operator!=(const pImpl& t);
};

#define SK_DECLARE_IMPL(C) friend class C##Impl; pImpl<C, C##Impl> __impl__

#define SK_I(C) C##Impl* d = static_cast<C##Impl*>(__impl__(this)); d
#define SK_E(C) C##Impl* d = static_cast<C##Impl*>(__impl__.get()); d
#define SK_D(C) C##Impl* d = static_cast<C##Impl*>(__impl__.get()); d
#define SK_C(C) const C##Impl* d = static_cast<const C##Impl*>(__impl__(this)); d
#define SK_Q(C) C* q = __self__; q

#ifdef _DEBUG
    #include <assert.h>
    #define ASSERT(exp) assert(exp)
#else
    #define ASSERT(exp)
#endif

#endif
