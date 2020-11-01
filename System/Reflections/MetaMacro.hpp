///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REFLECTIONS_METAMACRO_HPP
#define SYSTEM_REFLECTIONS_METAMACRO_HPP
namespace System
{
	namespace Reflections
	{
#ifdef _MSC_VER
#define GET_ARG_COUNT_(...)  \
   PASTE(GET_ARG_COUNT_I(__VA_ARGS__, \
      99, 98, 97, 96, 95, 94, 93, 92, 91, 90, \
      89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
      79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
      69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
      59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
      49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
      39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
      29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
      19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
      9, 8, 7, 6, 5, 4, 3, 2, 1, 0, \
      ), __CUB_empty())

#else

#define GET_ARG_COUNT_(...)     \
   GET_ARG_COUNT_I(__VA_ARGS__, \
      99, 98, 97, 96, 95, 94, 93, 92, 91, 90, \
      89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
      79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
      69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
      59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
      49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
      39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
      29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
      19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
      9, 8, 7, 6, 5, 4, 3, 2, 1, 0, \
      )

#endif

#define GET_ARG_COUNT(...) GET_ARG_COUNT_(__dummy__, ##__VA_ARGS__)
#define GET_ARG_COUNT_I( \
      e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, \
      e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, \
      e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, \
      e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, \
      e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, \
      e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, \
      e60, e61, e62, e63, e64, e65, e66, e67, e68, e69, \
      e70, e71, e72, e73, e74, e75, e76, e77, e78, e79, \
      e80, e81, e82, e83, e84, e85, e86, e87, e88, e89, \
      e90, e91, e92, e93, e94, e95, e96, e97, e98, e99, \
      size, ...) \
   size

#define REPEAT_0(func, i, arg)
#define REPEAT_1(func, i, arg)        func(i, arg)
#define REPEAT_2(func, i, arg, ...)   func(i, arg) REPEAT_1(func, i + 1, __VA_ARGS__)
#define REPEAT_3(func, i, arg, ...)   func(i, arg) REPEAT_2(func, i + 1, __VA_ARGS__)
#define REPEAT_4(func, i, arg, ...)   func(i, arg) REPEAT_3(func, i + 1, __VA_ARGS__)
#define REPEAT_5(func, i, arg, ...)   func(i, arg) REPEAT_4(func, i + 1, __VA_ARGS__)
#define REPEAT_6(func, i, arg, ...)   func(i, arg) REPEAT_5(func, i + 1, __VA_ARGS__)
#define REPEAT_7(func, i, arg, ...)   func(i, arg) REPEAT_6(func, i + 1, __VA_ARGS__)
#define REPEAT_8(func, i, arg, ...)   func(i, arg) REPEAT_7(func, i + 1, __VA_ARGS__)
#define REPEAT_9(func, i, arg, ...)   func(i, arg) REPEAT_8(func, i + 1, __VA_ARGS__)
#define REPEAT_10(func, i, arg, ...)  func(i, arg) REPEAT_9(func, i + 1, __VA_ARGS__)
#define REPEAT_11(func, i, arg, ...)  func(i, arg) REPEAT_10(func, i + 1, __VA_ARGS__)
#define REPEAT_12(func, i, arg, ...)  func(i, arg) REPEAT_11(func, i + 1, __VA_ARGS__)
#define REPEAT_13(func, i, arg, ...)  func(i, arg) REPEAT_12(func, i + 1, __VA_ARGS__)
#define REPEAT_14(func, i, arg, ...)  func(i, arg) REPEAT_13(func, i + 1, __VA_ARGS__)
#define REPEAT_15(func, i, arg, ...)  func(i, arg) REPEAT_14(func, i + 1, __VA_ARGS__)
#define REPEAT_16(func, i, arg, ...)  func(i, arg) REPEAT_15(func, i + 1, __VA_ARGS__)
#define REPEAT_17(func, i, arg, ...)  func(i, arg) REPEAT_16(func, i + 1, __VA_ARGS__)
#define REPEAT_18(func, i, arg, ...)  func(i, arg) REPEAT_17(func, i + 1, __VA_ARGS__)
#define REPEAT_19(func, i, arg, ...)  func(i, arg) REPEAT_18(func, i + 1, __VA_ARGS__)
#define REPEAT_20(func, i, arg, ...)  func(i, arg) REPEAT_19(func, i + 1, __VA_ARGS__)
#define REPEAT_21(func, i, arg, ...)  func(i, arg) REPEAT_20(func, i + 1, __VA_ARGS__)
#define REPEAT_22(func, i, arg, ...)  func(i, arg) REPEAT_21(func, i + 1, __VA_ARGS__)
#define REPEAT_23(func, i, arg, ...)  func(i, arg) REPEAT_22(func, i + 1, __VA_ARGS__)
#define REPEAT_24(func, i, arg, ...)  func(i, arg) REPEAT_23(func, i + 1, __VA_ARGS__)
#define REPEAT_25(func, i, arg, ...)  func(i, arg) REPEAT_24(func, i + 1, __VA_ARGS__)
#define REPEAT_26(func, i, arg, ...)  func(i, arg) REPEAT_25(func, i + 1, __VA_ARGS__)
#define REPEAT_27(func, i, arg, ...)  func(i, arg) REPEAT_26(func, i + 1, __VA_ARGS__)
#define REPEAT_28(func, i, arg, ...)  func(i, arg) REPEAT_27(func, i + 1, __VA_ARGS__)
#define REPEAT_29(func, i, arg, ...)  func(i, arg) REPEAT_28(func, i + 1, __VA_ARGS__)
#define REPEAT_30(func, i, arg, ...)  func(i, arg) REPEAT_29(func, i + 1, __VA_ARGS__)
#define REPEAT_31(func, i, arg, ...)  func(i, arg) REPEAT_30(func, i + 1, __VA_ARGS__)
#define REPEAT_32(func, i, arg, ...)  func(i, arg) REPEAT_31(func, i + 1, __VA_ARGS__)
#define REPEAT_33(func, i, arg, ...)  func(i, arg) REPEAT_32(func, i + 1, __VA_ARGS__)
#define REPEAT_34(func, i, arg, ...)  func(i, arg) REPEAT_33(func, i + 1, __VA_ARGS__)
#define REPEAT_35(func, i, arg, ...)  func(i, arg) REPEAT_34(func, i + 1, __VA_ARGS__)
#define REPEAT_36(func, i, arg, ...)  func(i, arg) REPEAT_35(func, i + 1, __VA_ARGS__)
#define REPEAT_37(func, i, arg, ...)  func(i, arg) REPEAT_36(func, i + 1, __VA_ARGS__)
#define REPEAT_38(func, i, arg, ...)  func(i, arg) REPEAT_37(func, i + 1, __VA_ARGS__)
#define REPEAT_39(func, i, arg, ...)  func(i, arg) REPEAT_38(func, i + 1, __VA_ARGS__)
#define REPEAT_40(func, i, arg, ...)  func(i, arg) REPEAT_39(func, i + 1, __VA_ARGS__)
#define REPEAT_41(func, i, arg, ...)  func(i, arg) REPEAT_40(func, i + 1, __VA_ARGS__)
#define REPEAT_42(func, i, arg, ...)  func(i, arg) REPEAT_41(func, i + 1, __VA_ARGS__)
#define REPEAT_43(func, i, arg, ...)  func(i, arg) REPEAT_42(func, i + 1, __VA_ARGS__)
#define REPEAT_44(func, i, arg, ...)  func(i, arg) REPEAT_43(func, i + 1, __VA_ARGS__)
#define REPEAT_45(func, i, arg, ...)  func(i, arg) REPEAT_44(func, i + 1, __VA_ARGS__)
#define REPEAT_46(func, i, arg, ...)  func(i, arg) REPEAT_45(func, i + 1, __VA_ARGS__)
#define REPEAT_47(func, i, arg, ...)  func(i, arg) REPEAT_46(func, i + 1, __VA_ARGS__)
#define REPEAT_48(func, i, arg, ...)  func(i, arg) REPEAT_47(func, i + 1, __VA_ARGS__)
#define REPEAT_49(func, i, arg, ...)  func(i, arg) REPEAT_48(func, i + 1, __VA_ARGS__)
#define REPEAT_50(func, i, arg, ...)  func(i, arg) REPEAT_49(func, i + 1, __VA_ARGS__)
#define REPEAT_51(func, i, arg, ...)  func(i, arg) REPEAT_50(func, i + 1, __VA_ARGS__)
#define REPEAT_52(func, i, arg, ...)  func(i, arg) REPEAT_51(func, i + 1, __VA_ARGS__)
#define REPEAT_53(func, i, arg, ...)  func(i, arg) REPEAT_52(func, i + 1, __VA_ARGS__)
#define REPEAT_54(func, i, arg, ...)  func(i, arg) REPEAT_53(func, i + 1, __VA_ARGS__)
#define REPEAT_55(func, i, arg, ...)  func(i, arg) REPEAT_54(func, i + 1, __VA_ARGS__)
#define REPEAT_56(func, i, arg, ...)  func(i, arg) REPEAT_55(func, i + 1, __VA_ARGS__)
#define REPEAT_57(func, i, arg, ...)  func(i, arg) REPEAT_56(func, i + 1, __VA_ARGS__)
#define REPEAT_58(func, i, arg, ...)  func(i, arg) REPEAT_57(func, i + 1, __VA_ARGS__)
#define REPEAT_59(func, i, arg, ...)  func(i, arg) REPEAT_58(func, i + 1, __VA_ARGS__)
#define REPEAT_60(func, i, arg, ...)  func(i, arg) REPEAT_59(func, i + 1, __VA_ARGS__)
#define REPEAT_61(func, i, arg, ...)  func(i, arg) REPEAT_60(func, i + 1, __VA_ARGS__)
#define REPEAT_62(func, i, arg, ...)  func(i, arg) REPEAT_61(func, i + 1, __VA_ARGS__)
#define REPEAT_63(func, i, arg, ...)  func(i, arg) REPEAT_62(func, i + 1, __VA_ARGS__)
#define REPEAT_64(func, i, arg, ...)  func(i, arg) REPEAT_63(func, i + 1, __VA_ARGS__)

#define STR(x) #x
#define CONCATE(x, y) x ## y
#define STRING(x) STR(x)
#define PARE(...) __VA_ARGS__
#define EAT(...)
#define PAIR(x) PARE x // PAIR((int) x) => PARE(int) x => int x
#define STRIP(x) EAT x // STRIP((int) x) => EAT(int) x => x
#define PASTE(x, y) CONCATE(x, y)
	}
}
#endif // !SYSTEM_REFLECTIONS_METAMACRO_HPP
