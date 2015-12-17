#pragma once

#include <string>


namespace Parser 
{
    namespace detail
    {
        /**
        * CmdArgConverter - template functors used to convert current argument from std::string to given type
        *                   In default version, it uses constructor with FROM-type argument.
        *
        * FROM - type from which current argument will be converted, usually std::string
        * TO   - type to which you current argument will be converted
        */
        template<typename FROM, typename TO>
        class CmdArgConvert {
            public:
                TO operator()(const FROM& from) { return TO(from); }
        };

        /**
         * 
         */
        template<>
        class CmdArgConvert<std::string, int> {
            public:
                int operator()(const std::string& from) { return std::stoi(from); }
        };

        /**
         *
         */
        template<>
        class CmdArgConvert<std::string, float> {
        public:
            float operator()(const std::string& from) { return std::stof(from); }
        };
    }
}
