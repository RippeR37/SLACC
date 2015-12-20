#pragma once

#include <algorithm>
#include <functional>
#include <map>

#include "BasicParser.hpp"


class CommandConsole {
    public:
        // Push command with custom parser
        template<typename Func, typename FuncParser>
        void push(const std::string& cmdName, const Func& func, const FuncParser& funcParser) {
            _command_parsers[cmdName] = std::bind(funcParser, func, std::placeholders::_1);
        }

        // Push command with default (basic) parser - std::function wrapper
        template<typename... FuncArgs>
        void push(const std::string& cmdName, const std::function<void(FuncArgs...)>& func) {
            push(cmdName, func, Parser::BasicParser::parse<FuncArgs...>);
        }

        // Push command with default (basic) parser - function pointer
        template<typename... FuncArgs>
        void push(const std::string& cmdName, void(*func)(FuncArgs...)) {
            push(cmdName, func, Parser::BasicParser::parse<FuncArgs...>);
        }


        // Execute command with given arguments
        void execute(const std::string& command) {
            std::size_t name_str = command.find_first_not_of(" \t\r\n");
            std::size_t name_end = command.find_first_of(" \t\r\n", name_str);
            std::size_t name_len =
                (name_str != std::string::npos) ?
                    ((name_end == std::string::npos ? command.length() : name_end) - name_str) : 0;

            std::size_t args_pos = std::min(name_str + name_len + 1, command.length());

            std::string cmd_name = (name_len > 0) ? command.substr(name_str, name_len) : "";
            std::string cmd_args = (name_len > 0) ? command.substr(args_pos)           : "";

            if(_command_parsers.count(cmd_name) > 0)
                _command_parsers[cmd_name](cmd_args)(); // get parser (with binded function), bind arguments and execute
        }

    private:
        std::map<std::string, std::function<std::function<void(void)>(const std::string&)>> _command_parsers;
};
