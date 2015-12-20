#include <cmath>
#include <iostream>
#include <string>

#include <CommandConsole.hpp>


// Test functions
void helloWorld() {
    std::cout << "Hello world" << std::endl;
}

void print_1(const std::string& str) {
    std::cout << "'" << str << "'" << std::endl;
}

void print_2(const std::string& str1, const std::string& str2) {
    std::cout << "'" << str1 << "' | '" << str2 << "'" << std::endl;
}

void sum(int a, int b) {
    std::cout << a + b << std::endl;
}


// Lambda function not wrapped in std::function wrapper
auto sqrt_lambda = [](double x) {
    std::cout << std::sqrt(x) << std::endl;
};

// Lambda function wrapped in std::function wrapper
std::function<void(double, double)> mult_f = [](double x, double y) {
    std::cout << x * y << std::endl;
};


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


    // Bind commands with default parser (function pointers or std::function wrappers only!)
    cmd.push("helloworld", helloWorld);
    cmd.push("print", print_1);
    cmd.push("mult",  mult_f);

    // Bind commands with provided parser
    cmd.push("print2", print_2, Parser::BasicParser::parse<std::string, std::string>);
    cmd.push("sum", sum, sumParser);

    // Bind commands to lambda functions or functor objects (either wrapped in std::function or pass explicit parser)
    cmd.push("sqrt", std::function<void(double)>(sqrt_lambda));
    cmd.push("sqrt", sqrt_lambda, Parser::BasicParser::parse<double>);


    // Executing commands
    cmd.execute("helloworld"); // hw()
    cmd.execute("helloworld  321 32512"); // hw()
    cmd.execute("print something"); // print("something")
    cmd.execute("print something else"); //print("something else")
    cmd.execute(" \t\r  print2 \n something  \t something else  "); // print2("something", "something else")
    cmd.execute("print2   \" two  words \"   second_arg  "); // print2(" two words ", "second_arg")
    cmd.execute("sum 1 7"); // sum(1, 7)
    cmd.execute("sqrt 2"); // sqrt_lambda(2.0)
    cmd.execute("mult 4.5 1.5"); // mult_f(4.5, 1.5)


    // Exit
    system("pause");
    return 0;
}
