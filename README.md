# Logger

---
It is an attempt to create simple, readable, flexible
and universal logger for personal purposes.
The main idea is implement useful tool,
which can be easy added to any `C++` project.

First ideas, which were implemented here,
were come up and developed in the 
[SQL to CypherQL Converter](https://github.com/temikfart/sql2cypher.git).

### Table of contents

1. [How to use](#How-to-use)
2. [Appenders](#Appenders)
   1. [FileAppender](#FileAppender)
   2. [ConsoleAppender](#ConsoleAppender)
3. [Inspired by](#Inspired-by)
4. [License](#License)

## How to use

Now, you can download this repository and manually integrate
`Logger` into your project.
* Import `logger.hpp` and `macro.hpp`, where you want to use `Logger`;
* Write your first log:
    ```C++
    #include "logger.hpp"
    #include "macro.hpp"
    
    int main() {
        logger::Logger::init(logger::info, "../log");
  
        LOG(logger::info) << "Hello, world!";
        LOGI << "Short form";
        
        return 0;
    }
    ```
* Read logs in the `2022-09-25-22:26:16.log` file:
    ```
    2022-09-25 22:26:16 [INFO] main.cpp main() at line 11: Hello, world!
    2022-09-25 22:26:16 [INFO] main.cpp main() at line 12: Short form
    ```

## Appenders
You can write logs in the several places at the same time.
Just add new appender to the `logger` instance:
```C++
logger::init(logger::debug, "../log");
logger::init(logger::error, logger::cerr);

LOGF << "fatal error";
```
Log _"fatal error"_ will be written in the file inside the `../log`
directory and in the `cerr` stream too.

_Notice: if you set different severity levels to appenders,
you will have logs in the output stream according to message's
severity and severity of each appender._

#### Example:
```C++
logger::init(logger::debug, "../log");
logger::init(logger::error, logger::cerr);

LOGE << "Something went wrong!"; // will be written in both
// ...
LOGD << "try to open file...";   // will be written only in the file
open(file);
```

### FileAppender

This appender writes logs in the special `.log` file,
path of which was specified during `logger::init` call.

#### File Creation

When you invoke `logger::init()`, you pass path to the logs directory
as the second argument. This path is processed by internal functions
and as result new folder for the logs will be created.

New folder pass will be according to this table:

| Existence | Your path | Result folder | Result path |
| --- | --- | --- | --- |
| _[exists]_ | `/path/dir/file.cpp` | _[parent path]_ | `/path/dir` |
| _[exists]_ | `/path/dir` | _[current path]_ | `/path/dir` |
| _[doesn't exist]_ | `/path/dir/not_exists.cpp` | _[parent path]_ | `/path/dir` |
| _[doesn't exist]_ | `/path/dir` | _[current path]_ | `/path/dir` |
| _[doesn't exist]_ | `/path/dir/` | _[path to subdir]_ | `/path/dir/dir` |

### ConsoleAppender

This appender writes logs in the console stream (`stdout` or `stderr`),
which was specified during `logger::init` call.
Logs recorded with the `ConsoleAppender` have special colours 
according to the `Severity` level.

## Inspired by

Some ideas of implementation was inspired by
[PLOG](https://github.com/SergiusTheBest/plog#license) project, which
is more complicated and thoughtful for now :)

## License

This project is licensed under the
[MIT license](https://choosealicense.com/licenses/mit/).
You can freely use `Logger` in your commercial or opensource software.
