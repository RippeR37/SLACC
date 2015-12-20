#pragma once

#include <algorithm>
#include <cctype>
#include <functional>
#include <tuple>

#include "CmdArgApplyer.hpp"
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
        void parse(const std::function<void(Ts...)>& func, const std::string& cmdArgs) {
            // Remove references in types to avoid conversion problems
            std::tuple<typename std::remove_reference<Ts>::type...> tupledArgs =
                detail::ArgToTupleSplitter<typename std::remove_reference<Ts>::type...>(cmdArgs);

            CmdArgApplyer::apply(func, tupledArgs);
        }

        /**
         * Basic parser - Specialization for commands with 0 arguments.
         *                Any passed arguments are ignored.
         */
        template<>
        void parse<>(const std::function<void()>& func, const std::string& cmdArgs) {
            (void) cmdArgs; // unused parameter warning

            func();
        }

        /**
         * Basic argument parsing - returns tuple <arg0, rest>
         */
        std::tuple<std::string, std::string> parseFirstArg(const std::string& args) {
            std::size_t i = 0, j = 0, k; // first argument is substring of range [i, j] in 'args'

            // Skip whitespaces before argument
            while(i < args.length() && std::isspace(args[i]))
                ++i;

            // If all characters are whitespaces, return empty argument
            if(i == args.length())
                return std::make_tuple(std::string(""), std::string(""));


            if(args[i] == '\"') {
                // If argument starts with opening ", then look for closing "
                j = ++i;

                while(j < args.length() && args[j] != '\"')
                    ++j;

            } else {
                // If argument starts from anything else, it ends upon first whitespace
                j = i + 1;

                while(j < args.length() && !std::isspace(args[j]))
                    ++j;
            }

            // Verify that k is in [0, args.length()] range and remove whitespaces from left side
            k = std::min(j + 1, args.length());
            while(k < args.length() && isspace(args[k]))
                ++k;

            return std::make_tuple(args.substr(i, j - i), args.substr(k));
        }


        /***************************************************************************************/


        namespace detail
        {
            /**
             * ArgToTupleSplitter<T, U, Args...> - splits arguments in std::string to std::tuple<T, U, Args...> between whitespaces.
             *                                     Last argument uses what's left in argument list.
             *
             * T - current argument type
             * U - next argument type
             * Args... - possible next argument types
             */
            template<typename T, typename U, typename... Args>
            std::tuple<T, U, Args...> ArgToTupleSplitter(const std::string& str) {
                std::tuple<std::string, std::string> parsedArgs = parseFirstArg(str);
                std::string& this_arg  = std::get<0>(parsedArgs);
                std::string& rest_args = std::get<1>(parsedArgs);

                return std::tuple_cat(
                    std::make_tuple(Parser::detail::CmdArgConvert<std::string, T>{}(this_arg)),     // this argument
                    ArgToTupleSplitter<U, Args...>(rest_args)                                       // rest of arguments
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
