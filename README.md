# C++ Logging Library - README

Welcome to pragma_log, a logging library that's simple and pragmatic! Whether you're debugging, tracking errors, or just need a solid log output for your project, this library gets the job done without any fluff. Easy to configure, easy to use, and, like any good tool, it focuses on what really matters. Let’s see how to put it to work.

---

## Table of Contents

- [Getting Started](#getting-started)
- [Defining Logging Categories](#defining-logging-categories)
- [Configuring Logging Rules](#configuring-logging-rules)
- [Setting Logging Targets](#setting-logging-targets)
- [Using Different Log Levels](#using-different-log-levels)
- [Customizing Log Patterns](#customizing-log-patterns)

---

## Getting Started

To get started with the super logging functionality, you need to **define your logging categories** and **set up logging targets**. Below is a quick rundown of the essential macros you’ll use to set up your project.

### Option 1: single_include the header file
Make sure the appropriate header file is included for logging functionality to work:

```cpp
#include "single_include/pragma/log.hpp"
```

### Option 2: 
```CMakeLists.txt
include_directories(path/to/pragma_log)
```


## Defining Logging Categories

You can declare logging categories for different parts of your program. Each category allows you to control logging levels and formatting separately.

### Declaring a Logging Category 'in .hpp files'

To declare a category, use the macro `PRAGMA_DECLARE_LOGGING_CATEGORY(name)`. 

```cpp
PRAGMA_DECLARE_LOGGING_CATEGORY(myCategory);
```

This creates a `myCategory` logging category that can be used to log different levels of information (info, debug, warning, error).

### Declaring a Logging Category with a Custom Name 'in .cpp files'

If you want to assign a custom name to the category, use `PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(name, categoryName)`.

```cpp
PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(myCategory, "MyCustomCategory");
```

Now, you have a logging category with a custom name that will be registered automatically.

---

## Configuring Logging Rules

You can configure the logging behavior by specifying rules using the `PRAGMA_LOGGING_CONFIGURE` macro. These rules allow you to **enable or disable specific logging levels** for each category, or apply global logging rules across all categories. 

### Syntax with ',' to diveded rules 

```cpp
PRAGMA_LOGGING_CONFIGURE("category_name.level=true/false");
PRAGMA_LOGGING_CONFIGURE("category_name.*=true/false");
```

Here’s what you can configure:

- **`category_name.debug=true/false`**: Enables or disables the `debug` level logs for the specified category.
  
- **`category_name.info=true/false`**: Enables or disables the `info` level logs for the specified category.
  
- **`category_name.warning=true/false`**: Enables or disables the `warning` level logs for the specified category.
  
- **`category_name.error=true/false`**: Enables or disables the `error` level logs for the specified category.
  
- **`category_name.*=true/false`**: Enables or disables **all log levels** for the specified category at once (use `true` to enable and `false` to disable all levels).

### Example Configurations

- **Enabling and disabling individual levels for a category:**

```cpp
PRAGMA_LOGGING_CONFIGURE("myCategory.debug=true,myCategory.info=false,myCategory.warning=true,myCategory.error=true");   
```

- **Disabling all logs for a category:**

```cpp
PRAGMA_LOGGING_CONFIGURE("myCategory.*=false");  // Disables all logs for 'myCategory'
```

You can also define **global configurations** that affect multiple categories:

```cpp
PRAGMA_LOGGING_CONFIGURE("myCategory.*=false"); // Disable all logs for 'myCategory'
PRAGMA_LOGGING_CONFIGURE("network.debug=true");  // Enable debug logs for the 'network' category
```

This gives you **fine-grained control** over which logs are generated, allowing you to keep your output clean and focused on the most important information.

---

## Setting Logging Targets

You can choose where your logs are sent: Console, Syslog, or both.

- **Console Target**:
    ```cpp
    PRAGMA_LOGGING_TARGET_CONSOLE();
    ```

- **Syslog Target**:
    ```cpp
    PRAGMA_LOGGING_TARGET_SYSLOG();
    ```

- **Both Targets**:
    ```cpp
    PRAGMA_LOGGING_TARGET_BOTH();
    ```

Pick the target that fits your use case. You can change the target anytime during runtime.

---

## Using Different Log Levels

This library supports several log levels, each with its own macro to make logging effortless:

- **Info Level**:
    ```cpp
    pragma_info(myCategory) << "This is an info message";
    ```

- **Debug Level**:
    ```cpp
    pragma_debug(myCategory) << "This is a debug message";
    ```

- **Warning Level**:
    ```cpp
    pragma_warning(myCategory) << "This is a warning message";
    ```

- **Error Level**:
    ```cpp
    pragma_error(myCategory) << "This is an error message";
    ```

Each macro will automatically include metadata like the file, line number, and function name in the log output.

---

## Customizing Log Patterns

You can fully customize how your logs appear by changing the **log pattern**. Here are the available pattern placeholders:

- **`%{level}`**: Log level (info, debug, warning, error).
- **`%{full_time}`**: Full timestamp.               --> ("%Y-%m-%d %H:%M:%S")
- **`%{time}`**: Simple timestamp.                  --> ("%H:%M:%S")
- **`%{precise_time}`**: High-precision timestamp.  --> ("%H:%M:%S".ms)
- **`%{file}`**: Source file.
- **`%{line}`**: Line number.
- **`%{function}`**: Function name.
- **`%{message}`**: Log message.
- **`%{threadid}`**: Current thread ID.
- **`%{category}`**: Log category name.
- **`%{mic_time_process}`**: Microseconds since process start.
- **`%{ms_time_process}`**: Milliseconds since process start.
- **`%{sec_time_process}`**: Seconds since process start.
- **`%{min_time_process}`**: Minutes since process start.

To set your custom pattern, use the `PRAGMA_LOGGING_PATTERN(pattern)` macro:

```cpp
PRAGMA_LOGGING_PATTERN("%{level} - %{time} - %{file}:%{line} - %{message}");
```

This will set the log format to include the log level, timestamp, file name, line number, and message content.