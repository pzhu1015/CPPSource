///////////////////////////////////////////////////////////////////
// Copyright 2020 Pengzhihu All Right Reserved
// FileName:
// Author: Pengzhihu
// Date: 2020-05-20
// Version: 1.0
// Description:
///////////////////////////////////////////////////////////////////
#ifndef SYSTEM_REFLECTIONS_REFLECTION_H
#define SYSTEM_REFLECTIONS_REFLECTION_H
#include <type_traits>
#include <utility>
#include <cstddef>
#include "System/Reflections/MetaMacro.hpp"

namespace System
{
	namespace Reflections
	{

#define FIELD_EACH(i, arg)                    \
    PAIR(arg);                                \
    template <typename T>                     \
    struct FIELD<T, i> {                      \
        T& obj;                               \
        FIELD(T& obj): obj(obj) {}            \
        auto value() -> decltype(auto) {      \
            return (obj.STRIP(arg));          \
        }                                     \
        static constexpr const char* name() { \
            return STRING(STRIP(arg));        \
        }                                     \
    };                                        \

#define DEFINE_STRUCT(st, ...)                                              \
    struct st {                                                             \
        template <typename, size_t> struct FIELD;                           \
        static constexpr size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__); \
        PASTE(REPEAT_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
    };                                                                      \

		template<typename T, typename = void>
		struct IsRefected : std::false_type { };

		template<typename T>
		struct IsRefected<T,
			std::void_t<decltype(&T::_field_count_)>>
			: std::true_type { };

		template<typename T>
		constexpr static bool IsReflected_v =
			IsRefected<T>::value;

		template<typename T, typename F, size_t... Is>
		inline constexpr void forEach(T&& obj, F&& f, std::index_sequence<Is...>) {
			using TDECAY = std::decay_t<T>;
			(void(f(typename TDECAY::template FIELD<TDECAY, Is>(obj).name(),
				typename TDECAY::template FIELD<TDECAY, Is>(obj).value())), ...);
		}

		template<typename T, typename F>
		inline constexpr void forEach(T&& obj, F&& f) {
			forEach(std::forward<T>(obj),
				std::forward<F>(f),
				std::make_index_sequence<std::decay_t<T>::_field_count_>{});
		}
	}
}
#endif // !SYSTEM_REFLECTIONS_REFLECTION_H
