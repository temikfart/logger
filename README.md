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
3. [Formatters](#Formatters)
   1. [TXTFormatter](#TXTFormatter)
   2. [FuncMessagesFormatter](#FuncMessagesFormatter)
   3. [OnlyMessagesFormatter](#OnlyMessagesFormatter)
   4. [JSONFormatter](#JSONFormatter)
4. [Inspired by](#Inspired-by)
5. [License](#License)

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
    _Notice: you can change timezone for timestamps with_
    ```C++
    void utils::Time::set_timzone(int tz);
    ```
    _For example for Moscow: `set_timezone(3)`._

## Macros

This tools contains a lot of macros.
You can choose any _(See file `log.hpp`)_.

The most important and "root" macros are `LOG(severity)` and
`LOG_IF(condition, severity)`.

| Original macro | Long form | Short form | Message |
| --- | --- | --- | --- |
| LOG(logger::fatal) | LOG_FATAL | LOGF | `fatal` error |
| LOG(logger::error) | LOG_ERROR | LOGE | `error` |
| LOG(logger::warning) | LOG_WARN | LOGW | `warning` |
| LOG(logger::info) | LOG_INFO | LOGI | `info`|
| LOG(logger::trace) | LOG_TRACE | LOGT | `trace` |
| LOG(logger::debug) | LOG_DEBUG | LOGD | `debug` |

The same table of macros, but with condition:

| Original macro | Long form | Short form | Message |
| --- | --- | --- | --- |
| LOG_IF(condition, logger::fatal) | LOG_FATAL_IF(condition) | LOGF_IF(condition) | `fatal` error |
| LOG_IF(condition, logger::error) | LOG_ERROR_IF(condition) | LOGE_IF(condition) | `error` |
| LOG_IF(condition, logger::warning) | LOG_WARN_IF(condition) | LOGW_IF(condition) | `warning` |
| LOG_IF(condition, logger::info) | LOG_INFO_IF(condition) | LOGI_IF(condition) | `info`|
| LOG_IF(condition, logger::trace) | LOG_TRACE_IF(condition) | LOGT_IF(condition) | `trace` |
| LOG_IF(condition, logger::debug) | LOG_DEBUG_IF(condition) | LOGD_IF(condition) | `debug` |

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

When you invoke `logger::init()`, you pass path to the log's directory
or to the desired regular file as the second argument.
This path is processed by internal functions and as result 
new folder for the logs will be created.

New folder path will be according to this table:

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

You can colour every message with special severity as you want.
Just use method `set_console_colour` in the `Logger` class:
```C++
void set_console_colour(Severity severity, const MessageColours& msg_cols);
```
where `MessageColours` is a struct, which consist of two colours:
for the text and its background.
```C++
struct MessageColours {
    Colour text;
    Colour bg;
};
```

Also, you can turn coloured output off, just use the following methods:
```C++
void turn_colours_on();
void turn_colours_off();
```

#### Example:
```C++
logger::Logger::get()->set_console_colour(logger::info,
                                          {logger::yellow, logger::common});
```
where `logger::common` equals to "without colour"
(transparent background or common text colour).

## Formatters

Each formatter is a class, which has special static method `format`:
```C++
static std::string format(const Record& r);
```
The Formatters can represent log records in different forms.

### TXTFormatter

When you use `init` function to initializing the logger this formatter
is set by default. Log messages represents in the following format:
```
2022-09-25 22:26:16 [INFO] main.cpp main() at line 11: Hello, world!
```
as you can see, there are timestamp, severity, file, function, line and message.

### FuncMessagesFormatter

This formatter contains only message with the function, which sent it, and line.
```
main.cpp@11: Hello, world!
```

### OnlyMessagesFormatter

You can use this formatter, if you want see only the log messages.
```
Hello, world!
```

### JSONFormatter

This formatter represents logs as json array:
```json
[
	{
		"timestamp":"2023-02-17T12:46:31.237Z",
		"severity":"FATAL",
		"file":"main.cpp",
		"function":"main",
		"line":"9",
		"message":"Fatal"
	},
	{
		"timestamp":"2023-02-17T12:46:31.237Z",
		"severity":"ERROR",
		"file":"main.cpp",
		"function":"main",
		"line":"10",
		"message":"Error"
	}
]
```

## Inspired by

Some ideas of implementation was inspired by
[PLOG](https://github.com/SergiusTheBest/plog) project, which
is more complicated and thoughtful for now :)

## License

This project is licensed under the
[MIT license](https://choosealicense.com/licenses/mit/).
You can freely use `Logger` in your commercial or opensource software.
