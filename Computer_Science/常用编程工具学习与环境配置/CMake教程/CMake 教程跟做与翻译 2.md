# CMake 教程跟做与翻译 2

## STEP 1(Extra A)：指定C++的版本

​	有的时候，我们会是对一个比较年老的项目进行构建。这个时候，我们可能就需要限制一下使用的C/C++的版本（比如说使用的是C++98）来进行编译；或者，我们的项目很潮，使用的是C++17以上的版本，这个时候限制就显得更为必要了（一些新的特性需要新版本支持）。我们就需要作出限制。

​	在这里，我们需要使用到的就是：

```
CMAKE_CXX_STANDARD				# CMake里的C++标准变量
CMAKE_CXX_STANDARD_REQUIRED		# CMake里的一个BOOL变量，用于指示是否强迫版本
set()							# 设置这些变量使用到的CMake函数
```

​	当然，我们只需要在CMakeLists.txt中，在project的下方和add_executable函数的上方加入

```
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

​	这就表达了我们需要强制使用C++11编译本项目的意思！

## STEP1(Extra B): 为我们的项目添加版本信息与配置的头文件

​	有时，让 CMakelists.txt 文件中定义的变量在源代码中可用可能会很有用。在这种情况下，我们想打印项目版本。实现此目的的一种方法是使用已配置的头文件。我们创建一个包含一个或多个要替换的变量的输入文件。这些变量具有特殊的语法，看起来像 @VAR@。然后，我们使用 configure_file() 命令将输入文件复制到给定的输出文件，并用 CMakelists.txt 文件中 VAR 的当前值替换这些变量。

​	虽然我们可以直接在源代码中编辑版本，但最好使用此功能，因为它可以创建单一事实来源并避免重复。

​	项目的版本信息很容易添加，我在上一篇就说到了：

```
project(CharliesDemo VERSION 1.0)
```

​	下面，我们可以在源代码文件中使用了。使用的bridge在哪里呢？那就是使用CMake里的configure_file指令。

​	他的作用很简单：**将input文件复制到output文件，并在输入文件内容中的变量，替换引用为@VAR@或${VAR}的变量值。每个变量引用将替换为该变量的当前值，如果未定义该变量，则为空字符串**。

​	实际上就是做拷贝替换的工作

- COPYONLY：只拷贝文件，不进行任何的变量替换。这个选项在指定了NEWLINE_STYLE选项时不能使用（无效）。
- ESCAPE_QUOTES：躲过任何的反斜杠(C风格)转义。
- @ONLY：限制变量替换，让其只替换被@VAR@引用的变量(那么${VAR}格式的变量将不会被替换)。这在配置${VAR}语法的脚本时是非常有用的。
- NEWLINE_STYLE style：指定输出文件中的新行格式。UNIX和LF的新行是\n，DOS和WIN32和CRLF的新行格式是\r\n。这个选项在指定了COPYONLY选项时不能使用(无效)。

通常情况下，输入文件以.h.in为后缀，输出文件以.h为后缀。

​	我们下面来试试看：

```
#define VERSION_MAJOR @CharliesDemo_VERSION_MAJOR@
#define VERSION_MINOR @CharliesDemo_VERSION_MINOR@
```

​	引用工程的属性名称正式：工程名称+工程属性。我们的CMake在构建的时候就会替换我们的@VAR@为我们CMake的值。下面在CMake中配置：

```
configure_file(Config.h.in Config.h)
```

​	我们可以看看生成的Config.h文件

```
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
```

​	使用一下，你会发现一个问题：

```
#include <stdio.h>
#include "Config.h"
#include "lib.h"

int main()
{
    printf("VERISON_MAJOR: %d", VERSION_MAJOR);
    printf("%d + %d = %d", 1, 2, my_add(1, 2));
}
```

​	gcc找不到我们的Config.h。这里需要超前的提供一个这样的命令：

```
target_include_directories(CharliesDemo PUBLIC "${PROJECT_BINARY_DIR}")
```

​	这句话的含义是：对于目标CharliesDemo提供要索引的目录为我们的build路径。这里正有Config.h!

​	下面我们来看看我们的CMakeLists.txt脚本：

```
cmake_minimum_required(VERSION 3.30)

project(CharliesDemo
        VERSION 1.0)

configure_file(Config.h.in Config.h)

add_executable(CharliesDemo lib.c main.c)
target_include_directories(CharliesDemo PUBLIC "${PROJECT_BINARY_DIR}")
```

​	看官自行回忆每一句话的含义。



## Reference

[`_VERSION_MAJOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MAJOR.html#variable:_VERSION_MAJOR)

[`_VERSION_MINOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MINOR.html#variable:_VERSION_MINOR)

[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)

[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)

[`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD)

[`CMAKE_CXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD_REQUIRED.html#variable:CMAKE_CXX_STANDARD_REQUIRED)

[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)