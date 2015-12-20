#pragma once

#include <functional>
#include <type_traits>


namespace Parser
{

    namespace CmdArgApplyer
    {
        /**
         * Forward declaration
         */
        namespace detail
        {
            template <std::size_t N>
            struct CmdArgApplyer_Helper;
        }


        /**
         * CmdArgApplyer
         */
        template<typename Func, typename... Args>
        void apply(const Func& func, const std::tuple<Args...>& args) {
            detail::CmdArgApplyer_Helper< std::tuple_size<std::tuple<Func, Args...>>::value - 1 >::apply(func, args);
        }



        /************************************************************/


        namespace detail
        {
            template <std::size_t N>
            struct CmdArgApplyer_Helper
            {
                template <typename Func, typename Tuple, typename... Args>
                static void apply(const Func& func, const Tuple& tuple, const Args&... args) {
                    CmdArgApplyer_Helper<N - 1>::apply(func, tuple, std::get<N - 1>(tuple), args...);
                }
            };

            template <>
            struct CmdArgApplyer_Helper<0>
            {
                template <typename Func, typename Tuple, typename... Args>
                static void apply(const Func& func, const Tuple& tuple, const Args&... args) {
                    (void) tuple; // unused argument warning

                    func(args...);
                }
            };
        }
    }

}
