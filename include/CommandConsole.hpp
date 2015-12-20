#pragma once

#include <algorithm>
#include <functional>
#include <map>

#include "BasicParser.hpp"


class CommandConsole {
    public:
        // Bind command with function using custom parser
        template<typename Func, typename FuncParser>
        void bind(const std::string& cmdName, const Func& func, const FuncParser& funcParser) {
            _command_parsers[cmdName] = std::bind(funcParser, func, std::placeholders::_1);
        }

        // Bind command with function using default (basic) parser - std::function wrapper
        template<typename... FuncArgs>
        void bind(const std::string& cmdName, const std::function<void(FuncArgs...)>& func) {
            bind(cmdName, func, Parser::BasicParser::parse<FuncArgs...>);
        }

        // Bind command with function using default (basic) parser - function pointer
        template<typename... FuncArgs>
        void bind(const std::string& cmdName, void(*func)(FuncArgs...)) {
            bind(cmdName, func, Parser::BasicParser::parse<FuncArgs...>);
        }


        // Execute command with given arguments
        void execute(const std::string& command) {
            // Command name
            std::size_t name_pos = command.find_first_not_of(" \t\r\n");
            std::size_t name_end = command.find_first_of(" \t\r\n", name_pos);
            std::size_t name_len =
                (name_pos != std::string::npos) ?
                ((name_end == std::string::npos ? command.length() : name_end) - name_pos) : 0;

            // Arguments
            std::size_t args_pos = std::min(name_pos + name_len + 1, command.length());
            std::size_t args_end = command.find_last_not_of(" \t\r\n");
            std::size_t args_len = std::max(args_pos, args_end) - args_pos + 1;

            // Values
            std::string cmd_name = (name_len > 0) ? command.substr(name_pos, name_len) : "";
            std::string cmd_args = (name_len > 0) ? command.substr(args_pos, args_len) : "";

            // Execution
            if(_command_parsers.count(cmd_name) > 0)
                _command_parsers[cmd_name](cmd_args);
        }

    private:
        std::map<std::string, std::function<void(const std::string&)>> _command_parsers;
};
