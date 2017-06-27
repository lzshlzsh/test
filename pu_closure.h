/**
 * @file                pu_closure.h
 * @brief               以下宏 拷贝于 wxg的开源项目 libco, 并做了一些扩展
 * @version             1.0
 * @date                2015年10月29日
 * @author              sarenlin(林钊航),sarenlin@tencent.com
 * @copyright           Copyright 1998 - 2014 Tencent. All Rights Reserved.
 */

#ifndef PU_CLOSURE_H_
#define PU_CLOSURE_H_

#include "boost/bind.hpp"
#include "boost/function.hpp"

namespace r2
{

namespace pu
{

struct Closure
{
public :
    virtual ~Closure() {};
    virtual void exec() = 0;
};

// macro args
#define __R2_MACRO_GET_ARGS_CNT(...) __R2_MACRO_ARG_N(__VA_ARGS__)
#define __R2_MACRO_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, N, ...) N
#define __R2_MACRO_ARGS_SEQS 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2 , 1, 0
#define __R2_MACRO_JOIN_1(x, y) x##y

#define __R2_MACRO_JOIN(x, y) __R2_MACRO_JOIN_1(x, y)
#define __R2_MACRO_ARGS(...) __R2_MACRO_GET_ARGS_CNT(__VA_ARGS__, __R2_MACRO_ARGS_SEQS)

#define __DEVAL_1 0
#define __DEVAL_2 1
#define __DEVAL_3 2
#define __DEVAL_4 3
#define __DEVAL_5 4
#define __DEVAL_6 5
#define __DEVAL_7 6
#define __DEVAL_8 7
#define __DEVAL_9 8
#define __DEVAL_10 9
#define __DEVAL_11 10
#define __DEVAL_12 11
#define __DEVAL_13 12
#define __DEVAL_14 13
#define __DEVAL_15 14
#define __DEVAL_16 15
#define __DEVAL(n) __DEVAL_##n

// repeat
#define __R2_REPEAT_0(fun, a, ...)
#define __R2_REPEAT_1(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_2(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_3(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_4(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_5(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_6(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_7(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_8(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_9(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_10(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_11(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_12(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_13(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_14(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_15(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)
#define __R2_REPEAT_16(n, fun, a, ...) fun(n, a, __VA_ARGS__) __R2_MACRO_JOIN(__R2_REPEAT_, __DEVAL(n))(__DEVAL(n), fun, __VA_ARGS__,)

#define __R2_REPEAT_N(n, fun, ...) __R2_MACRO_JOIN(__R2_REPEAT_, n)(n, fun, __VA_ARGS__)
#define __R2_REPEAT(fun, ...) __R2_REPEAT_N(__R2_MACRO_ARGS(__VA_ARGS__), fun, __VA_ARGS__)

//2.implement
#define __DECL_TYPEOF(i, a, ...) typedef typeof(a) typeof_##a;
#define __IMPL_TYPEOF(i, a, ...) typeof_##a &a;
#define __IMPL_TYPEOF_CPY(i, a, ...) typeof_##a a;
#define __CON_PARAM_TYPEOF(i, a, ...) typeof_##a & a##r,
#define __PARAM_INIT_TYPEOF(i, a, ...) a(a##r),

#define R2_REF(name, ...)    \
__R2_REPEAT(__DECL_TYPEOF, __VA_ARGS__)    \
class type_##name   \
{   \
public :    \
    __R2_REPEAT(__IMPL_TYPEOF, __VA_ARGS__)    \
    int member_cnt_;    \
public :    \
    type_##name( \
            __R2_REPEAT(__CON_PARAM_TYPEOF, __VA_ARGS__) ... ) : \
            __R2_REPEAT(__PARAM_INIT_TYPEOF, __VA_ARGS__) member_cnt_(__R2_MACRO_ARGS(__VA_ARGS__)) \
    {} \
} name(__VA_ARGS__);

#define R2_FUNCTION(name, ...)   \
__R2_REPEAT(__DECL_TYPEOF, __VA_ARGS__)   \
class name : public Closure \
{   \
public :    \
    __R2_REPEAT(__IMPL_TYPEOF_CPY, __VA_ARGS__)   \
    int member_cnt_;    \
public :    \
    name(   \
        __R2_REPEAT(__CON_PARAM_TYPEOF, __VA_ARGS__ ) ...):  \
        __R2_REPEAT(__PARAM_INIT_TYPEOF, __VA_ARGS__) member_cnt_(__R2_MACRO_ARGS(__VA_ARGS__)) \
    {} \
    void exec()

#define R2_FUNCTION_END }


class SubCoroutine : public Closure
{
public :
    typedef boost::function<int()> BindFunc;
public :
    SubCoroutine() : result_(0) {}

    virtual void exec()
    {
        result_ = func_();
    }

#define __BASE_TEMPLATE_ARGS(n, ...) , class A##n
#define __TEMPLATE_ARGS(n) __R2_REPEAT_N(n, __BASE_TEMPLATE_ARGS, )
#define __BASE_FUNC_ARGS(n, ...) , A##n a##n
#define __FUNC_ARGS(n) __R2_REPEAT_N(n, __BASE_FUNC_ARGS, )
#define __BASE_INIT_ARGS(n, ...) , a##n
#define __INIT_ARGS(n) __R2_REPEAT_N(n, __BASE_INIT_ARGS, )

#define __DECLARE_BIND(n, ...)   \
    template<class F __TEMPLATE_ARGS(n) >    \
    SubCoroutine* bind(F f __FUNC_ARGS(n))           \
    { \
        func_ = boost::bind(f __INIT_ARGS(n));  \
        return this;    \
    }

    __DECLARE_BIND(0)
    __DECLARE_BIND(1)
    __DECLARE_BIND(2)
    __DECLARE_BIND(3)
    __DECLARE_BIND(4)
    __DECLARE_BIND(5)
    __DECLARE_BIND(6)
    __DECLARE_BIND(7)
    __DECLARE_BIND(8)

#undef __BASE_TEMPLATE_ARGS
#undef __TEMPLATE_ARGS
#undef __BASE_FUNC_ARGS
#undef __FUNC_ARGS
#undef __BASE_INIT_ARGS
#undef __INIT_ARGS
#undef __DECLARE_BIND

private :
    BindFunc func_;
    int result_;
};

}

}


#endif /* PU_CLOSURE_H_ */
