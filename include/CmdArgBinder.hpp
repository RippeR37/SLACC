#pragma once

#include <functional>


namespace Parser
{

    namespace CmdArgBinder
    {
        /**
         * Forward declaration
         */
        namespace detail
        {
            template <std::size_t N>
            struct CmdArgBinder_Helper;
        }


        /**
         * CmdArgBinder
         */
        template<typename Func, typename... Args>
        std::function<void(void)> bind(Func func, std::tuple<Args...> args) {
            return detail::CmdArgBinder_Helper< std::tuple_size<std::tuple<Func, Args...>>::value >
                ::bind(std::tuple_cat(std::tie(func), args));
        }



        /************************************************************/


        namespace detail
        {
            template <std::size_t N>
            struct CmdArgBinder_Helper
            {
                template <typename Tuple, typename... Args>
                static std::function<void(void)> bind(Tuple tuple, Args... args) {
                    return CmdArgBinder_Helper<N - 1>::bind(tuple, std::get<N - 1>(tuple), args...);
                }
            };

            template <>
            struct CmdArgBinder_Helper<0>
            {
                template <typename Tuple, typename... Args>
                static std::function<void(void)> bind(Tuple t, Args... args) {
                    (void) t; // unused argument warning

                    return std::bind(args...);
                }
            };
        }
    }

}
