#include <iostream>
#include <string>

#include <CommandConsole.hpp>
#include <BasicParser.hpp>


// Test functions
void print_1(const std::string& str) {
    std::cout << "'" << str << "'" << std::endl;
}

void print_2(const std::string& str1, const std::string& str2) {
    std::cout << "'" << str1 << "' | '" << str2 << "'" << std::endl;
}

void sum(int a, int b) {
    std::cout << a + b << std::endl;
}


// Parser example (parses string as two integers separated by first space)
std::function<void(void)> sumParser(const std::function<void(int, int)> f, const std::string& args) {
    std::size_t delimiter_pos = args.find_first_of(' ');
    std::string arg0 = "", arg1 = ""; int iarg0, iarg1;

    if(delimiter_pos != std::string::npos && delimiter_pos > 0) {
        arg0 = args.substr(0, delimiter_pos);   iarg0 = std::stoi(arg0);
        arg1 = args.substr(delimiter_pos + 1);  iarg1 = std::stoi(arg1);
    }

    return std::bind(f, iarg0, iarg1);
}


int main() {
    CommandConsole cmd;

    // Bind available commands
    cmd.push("print",   print_1,    Parser::BasicParser::parse<std::string>);
    cmd.push("print2",  print_2,    Parser::BasicParser::parse<std::string, std::string>);
    cmd.push("sum",     sum,        Parser::BasicParser::parse<int, int>);

    // Executing commands
    cmd.execute("print something"); // print("something")
    cmd.execute("print something else"); //print("something else")
    cmd.execute("print2 something something else"); // print2("something", "something else")
    cmd.execute("sum 1 7"); // sum(1, 7)
    cmd.execute("sum 3 9"); // sum(3, 9)

    // Exit
    system("pause");
    return 0;
}
