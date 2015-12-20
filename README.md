## SLACC - Simple Lightweight Adaptable Command Console


Command console module written in C++11 for use as in-game console module or simple scripting engine. 

This module have zero dependencies so it's super easy to use in existing projects. It heavily uses variadic templates to provide automatisation of binding commands with functions and nice API. Small usage example below:
```c++
void func1_ptr(const std::string& name) {
    std::cout << "Hello " << name << "!" << std::endl;
}

std::function<void(float)> func2_wrapper = [](float x) {
    std::cout << x << "^2 = " << x*x << std::endl;
}

auto func3_lambda = [](int x, float y, const std::string& z) {
    std::cout << x << y << z << std::endl;
}

/* ... */

CommandConsole cmd;

cmd.push("func1", func_ptr);      // default parser, types are infered from function pointer
cmd.push("func2", func2_wrapper); // default parser, types are infered from std::function wrapper
// to use lambda, either wrap it in std::function or provide valid parser
cmd.push("func3", func3_lambda, Parser::BasicParser::parse<int, float, std::string>);

cmd.execute("func1 John"); // func1_ptr("John")
cmd.execute("func2 9.0f"); // func2_wrapper(9.0f)
cmd.execute("func3 0 3.14 \"hello world\""); // func3_lambda(0, 3.14f, "hello world")
```


### Requirements
- C++11 supporting compiler (project for Visual Studio 2013 provided)


### Platforms tested
- Windows (tested on Windows 7 x64)


### Compilers tested
- MSVC (tested on Visual Studio 2013)
- GCC (tested on 5.1.0)


### Dependencies
None!


### License
See [LICENSE](LICENSE) file.


### Examples of usage
You can find example usage in `src/main.cpp` file.
