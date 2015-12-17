#pragma once

#include <functional>
#include <tuple>

#include "CmdArgBinder.hpp"
#include "CmdArgConverter.hpp"


namespace Parser 
{

    namespace BasicParser
    {

        /**
        * Forward declaration
        */
        namespace detail
        {
            template<typename T, typename U, typename... Args>
            std::tuple<T, U, Args...> ArgToTupleSplitter(const std::string& str);

            template<typename T>
            std::tuple<T> ArgToTupleSplitter(const std::string& str);
        }


        /**
         * Basic Parser
         */
        template<typename... Ts>
        std::function<void(void)> parse(std::function<void(Ts...)> func, const std::string& cmdArgs) {
            std::tuple<Ts...> tupledArgs = detail::ArgToTupleSplitter<Ts...>(cmdArgs);

            return CmdArgBinder::bind(func, tupledArgs);
        }



        /***************************************************************************************/


        namespace detail
        {
            /**
             * ArgToTupleSplitter<T, U, Args...> - splits arguments in std::string to std::tuple<T, U, Args...> between whitespaces.
             *                                     last argument uses what's left in argument list
             *
             * T - current argument type
             * U - next argument type
             * Args... - possible next argument types
             */
            template<typename T, typename U, typename... Args>
            std::tuple<T, U, Args...> ArgToTupleSplitter(const std::string& str) {
                std::size_t delimiter_pos = str.find_first_of(' ');
                std::string this_str = str, next_str = "";

                if(delimiter_pos != std::string::npos) {
                    this_str = str.substr(0, delimiter_pos);
                    next_str = str.substr(delimiter_pos + 1);
                }

                return std::tuple_cat(
                    std::make_tuple(Parser::detail::CmdArgConvert<std::string, T>{}(this_str)),     // this argument
                    ArgToTupleSplitter<U, Args...>(next_str)                                        // rest of arguments
                );
            }

            /**
             * ArgToTupleSplitter<T> - specialization to ArgToTupleSplitter<T, U, Args...> which handles last argument.
             *                         This method uses as argument's source whole string, not only till first whitespace!
             *
             * T - current argument type
             */
            template<typename T>
            std::tuple<T> ArgToTupleSplitter(const std::string& str) {
                return std::make_tuple(Parser::detail::CmdArgConvert<std::string, T>{}(str));
            }
        
        }

    }
    
}
