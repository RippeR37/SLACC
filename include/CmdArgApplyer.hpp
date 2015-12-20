#pragma once

#include <functional>


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
        void apply(Func func, std::tuple<Args...> args) {
            detail::CmdArgApplyer_Helper< std::tuple_size<std::tuple<Func, Args...>>::value - 1 >::apply(func, args);
        }



        /************************************************************/


        namespace detail
        {
            template <std::size_t N>
            struct CmdArgApplyer_Helper
            {
                template <typename Func, typename Tuple, typename... Args>
                static void apply(Func func, Tuple tuple, Args... args) {
                    CmdArgApplyer_Helper<N - 1>::apply(func, tuple, std::get<N - 1>(tuple), args...);
                }
            };

            template <>
            struct CmdArgApplyer_Helper<0>
            {
                template <typename Func, typename Tuple, typename... Args>
                static void apply(Func func, Tuple tuple, Args... args) {
                    (void) tuple; // unused argument warning

                    func(args...);
                }
            };
        }
    }

}
