# Logger

---
It is an attempt to create simple, readable, flexible
and universal logger for personal purposes.
The main idea is implement useful tool,
which can be easy added to any `C++` project.

First ideas, which were implemented here,
were come up and developed in the 
[SQL to CypherQL Converter](https://github.com/temikfart/sql2cypher.git).

## How to use

Now, you can download this repository and manually integrate
`Logger` into your project.
* Import `logger.hpp`, where you want to use `Logger`;
* Create `log.txt` file, where logs will be placed;
* Write your first log:
    ```C++
    #include "logger.hpp"
    #include "macro.hpp"
    
    int main() {
        logger::Logger::init(logger::info, "log.txt");
  
        LOG(logger::info) << "Hello, world!";
        LOGI << "Short form";
        
        return 0;
    }
    ```
* Read logs in the `log.txt` file:
    ```
    2022-09-25 22:26:16 [INFO] main.cpp main() at line 11: Hello, world!
    2022-09-25 22:26:16 [INFO] main.cpp main() at line 12: Short form
    ```

## Inspired by

Some ideas of implementation was inspired by
[PLOG](https://github.com/SergiusTheBest/plog#license) project, which
is more complicated and thoughtful for now :)

## License

This project is licensed under the
[MIT license](https://choosealicense.com/licenses/mit/).
You can freely use `Logger` in your commercial or opensource software.
