## SLACC - Simple Lightweight Adaptable Command Console


Simple command console module written in C++11. This module have zero dependencies. It uses heavily (variadic) templates to provide nice API, like below:
```c++
void someFunction(int x, float y, const std::string& z) {
    std::cout << x << y << z << std::endl;
}

/* ... */

// Create console object
CommandConsole cmd;
// Push command "some_command" binded to `someFunction(...)` with basic
// as basic parser which reads arguments as (int, float, string)
cmd.push("some_command", someFunction, Parser::BasicParser::parse<int, float, std::string>);
// Test console by executing command
cmd.execute("some_command 1 3.14 hello world"); // invokes someFunction(1, 3.14f, "hello world")
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
