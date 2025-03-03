Ecco l'aggiornamento del README con la spiegazione dettagliata della macro `PRAGMA_LOGGING_CONFIGURE` inclusa:

---

# Super Cool Logging Library - README

Welcome to the most **powerful, flexible, and elegant logging** library ever! Whether you’re debugging, tracking errors, or just need some juicy log output for your project, this library has got your back. Easy to configure, easy to use, and packed with killer features. Let’s dive into how to set up and use this library like a boss.

---

## Table of Contents

- [Getting Started](#getting-started)
- [Defining Logging Categories](#defining-logging-categories)
- [Configuring Logging Rules](#configuring-logging-rules)
- [Setting Logging Targets](#setting-logging-targets)
- [Using Different Log Levels](#using-different-log-levels)
- [Customizing Log Patterns](#customizing-log-patterns)
- [Full Example](#full-example)

---

## Getting Started

To get started with the super logging functionality, you need to **define your logging categories** and **set up logging targets**. Below is a quick rundown of the essential macros you’ll use to set up your project.

### Step 1: Include the header file
Make sure the appropriate header file is included for logging functionality to work:

```cpp
#include "logging.h"
```

### Step 2: Configure the logger
Configure logging rules globally by calling `PRAGMA_LOGGING_CONFIGURE(rules)` with your desired configuration.

```cpp
PRAGMA_LOGGING_CONFIGURE("your_custom_rules");
```

This will set the logging rules that your project will follow.

---

## Defining Logging Categories

You can declare logging categories for different parts of your program. Each category allows you to control logging levels and formatting separately.

### Declaring a Logging Category

To declare a category, use the macro `PRAGMA_DECLARE_LOGGING_CATEGORY(name)`.

```cpp
PRAGMA_DECLARE_LOGGING_CATEGORY(myCategory);
```

This creates a `myCategory` logging category that can be used to log different levels of information (info, debug, warning, error).

### Declaring a Logging Category with a Custom Name

If you want to assign a custom name to the category, use `PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(name, categoryName)`.

```cpp
PRAGMA_DECLARE_LOGGING_CATEGORY_NAME(myCategory, "MyCustomCategory");
```

Now, you have a logging category with a custom name that will be registered automatically.

---

## Configuring Logging Rules

You can configure the logging behavior by specifying rules using the `PRAGMA_LOGGING_CONFIGURE` macro. These rules allow you to **enable or disable specific logging levels** for each category, or apply global logging rules across all categories. 

### Syntax

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
PRAGMA_LOGGING_CONFIGURE("myCategory.debug=true");    // Enables debug logs for 'myCategory'
PRAGMA_LOGGING_CONFIGURE("myCategory.info=false");     // Disables info logs for 'myCategory'
PRAGMA_LOGGING_CONFIGURE("myCategory.warning=true");   // Enables warning logs for 'myCategory'
PRAGMA_LOGGING_CONFIGURE("myCategory.error=true");     // Enables error logs for 'myCategory'
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
- **`%{full_time}`**: Full timestamp.
- **`%{time}`**: Simple timestamp.
- **`%{precise_time}`**: High-precision timestamp.
- **`%{file}`**: Source file.
- **`%{line}`**: Line number.
- **`%{function}`**: Function name.
- **`%{message}`**: Log message.
- **`%{threadid}`**: Current thread ID.
- **`%{category}`**: Log category name.
- **`%{time process}`**: Time since process start.

To set your custom pattern, use the `PRAGMA_LOGGING_PATTERN(pattern)` macro:

```cpp
PRAGMA_LOGGING_PATTERN("%{level} - %{time} - %{file}:%{line} - %{message}");
```

This will set the log format to include the log level, timestamp, file name, line number, and message content.

---

## Full Example

Here’s how a full example might look in your application:

```cpp
#include "logging.h"

PRAGMA_DECLARE_LOGGING_CATEGORY(myCategory);
PRAGMA_LOGGING_CONFIGURE("level=debug, output=console");

int main() {
    PRAGMA_LOGGING_PATTERN("%{level} %{time} %{message}");

    pragma_info(myCategory) << "Application started";
    pragma_debug(myCategory) << "Debugging application";
    pragma_warning(myCategory) << "This is a warning";
    pragma_error(myCategory) << "An error occurred!";
    
    return 0;
}
```

In this example:
- We configure the logger to output `debug` level logs to the console.
- We log messages at various levels (info, debug, warning, and error).
- The logs will follow the custom pattern specified.

---

## Conclusion

This logging library gives you **full control** over your log outputs, allowing you to format logs as you see fit and send them to different targets. With categories, log levels, custom patterns, and granular configurations, your logs will be as readable and useful as possible. Get started today and enjoy a new world of logging possibilities! 🚀