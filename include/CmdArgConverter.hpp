#pragma once

#include <stdexcept>
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
         * String to unsigned char converter
         */
        template<>
        class CmdArgConvert<std::string, char> {
        public:
            unsigned char operator()(const std::string& from) {
                if(from.length() == 0)
                    throw std::runtime_error("Unable to cast command argument from empty string to char");

                return from[0];
            }
        };

        /**
         * String to string converter
         */
        template<>
        class CmdArgConvert<std::string, std::string> {
        public:
            std::string operator()(const std::string& from) {
                std::size_t i = from.find_first_not_of(" \t\r\n");
                std::size_t j = from.find_last_not_of(" \t\r\n") + 1;

                return from.substr(i, j - i);
            }
        };

        /**
         * String to unsigned int converter
         */
        template<>
        class CmdArgConvert<std::string, unsigned int> {
        public:
            unsigned int operator()(const std::string& from) { return std::stoul(from); }
        };

        /**
         * String to int converter
         */
        template<>
        class CmdArgConvert<std::string, int> {
            public:
                int operator()(const std::string& from) { return std::stoi(from); }
        };

        /**
         * String to unsigned long int converter
         */
        template<>
        class CmdArgConvert<std::string, unsigned long int> {
        public:
            unsigned long int operator()(const std::string& from) { return std::stoul(from); }
        };

        /**
         * String to long int converter
         */
        template<>
        class CmdArgConvert<std::string, long int> {
        public:
            long int operator()(const std::string& from) { return std::stol(from); }
        };

        /**
         * String to unsigned long long int converter
         */
        template<>
        class CmdArgConvert<std::string, unsigned long long int> {
        public:
            unsigned long long int operator()(const std::string& from) { return std::stoull(from); }
        };

        /**
         * String to long long int converter
         */
        template<>
        class CmdArgConvert<std::string, long long int> {
        public:
            long long int operator()(const std::string& from) { return std::stoll(from); }
        };

        /**
         * String to float converter
         */
        template<>
        class CmdArgConvert<std::string, float> {
        public:
            float operator()(const std::string& from) { return std::stof(from); }
        };

        /**
         * String to double converter
         */
        template<>
        class CmdArgConvert<std::string, double> {
        public:
            double operator()(const std::string& from) { return std::stod(from); }
        };

        /**
         * String to long double converter
         */
        template<>
        class CmdArgConvert<std::string, long double> {
        public:
            long double operator()(const std::string& from) { return std::stold(from); }
        };

    }
}
