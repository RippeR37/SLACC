#pragma once

#include <functional>
#include <map>


class CommandConsole {
    public:
        template<typename Func, typename FuncParser>
        void push(const std::string& cmdName, Func& func, FuncParser& funcParser) {
            _command_parsers[cmdName] = std::bind(funcParser, func, std::placeholders::_1);
        }

        void execute(const std::string& command) {
            std::size_t name_len = command.find_first_of(' ');
            std::string cmd_name = (name_len != std::string::npos && name_len > 0) ? command.substr(0,  name_len) : "";
            std::string cmd_args = (name_len != std::string::npos && name_len > 0) ? command.substr(name_len + 1) : "";

            if(_command_parsers.count(cmd_name) > 0)
                _command_parsers[cmd_name](cmd_args)(); // get parser (with binded function), bind arguments and execute
        }

    private:
        std::map<std::string, std::function<std::function<void(void)>(const std::string&)>> _command_parsers;
};
