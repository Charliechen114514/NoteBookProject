# CMake 教程跟做与翻译 3

## STEP2: 构建一个可以使用的库

​	要在 CMake 中添加库，请使用 add_library() 命令并指定哪些源文件应组成库。我们可以使用一个或多个子目录来组织项目，而不是将所有源文件放在一个目录中。 在这种情况下，我们将专门为我们的库创建一个子目录。 在这里，我们可以添加一个新的 CMakeLists.txt 文件和一个或多个源文件。 在顶层 CMakeLists.txt 文件中，我们将使用 add_subdirectory() 命令将子目录添加到构建中。

​	一旦创建了库，它就会通过 target_include_directories() 和 target_link_libraries() 连接到我们的可执行目标。

​	下面我们尝试使用CMake来构建一个更加具备层级的构建脚本。

### 首先先有一个库：

​	现在我们将Math库放到一个目录下，表达的是我们这里是一个子构建系统：构建一个Math库。各位参考一下：

```
➜  tree MathLibs/
MathLibs/
├── CMakeLists.txt
├── mathLibs.c
└── mathLibs.h

1 directory, 3 files
```

​	在这里，我们写一个一行话的CMakeLists.txt:那就是表达构建一个MathLibs:

```
add_library(MathLib mathLibs.c)
```

```
➜  cat MathLibs/mathLibs.c 
#include "mathLibs.h"

int my_add(const int add1, const int add2){
    return add1 + add2;
}
➜  cat MathLibs/mathLibs.h
#ifndef _LIB_H
#define _LIB_H

int my_add(const int add1, const int add2);

#endif /* ifndef _LIB_H
#define _LIB_H */
```

​	下一步就是修改我们的main.c:

```
#include <stdio.h>
#include "Config.h"
#include "mathLibs.h"

int main()
{
    printf("VERISON_MAJOR: %d", VERSION_MAJOR);
    printf("%d + %d = %d", 1, 2, my_add(1, 2));
}
```

​	很好，下面我们重点改CMakeLists.txt

```
cmake_minimum_required(VERSION 3.30)

project(CharliesDemo
        VERSION 1.0)

configure_file(Config.h.in Config.h)

# 添加一个构建的子目录，CMake将会先构建这个子目录的内容
add_subdirectory(MathLibs)

add_executable(CharliesDemo main.c)

# 添加一个包含目录：这是因为main.c中应用了mathLibs.h
target_include_directories( CharliesDemo PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/MathLibs")
                            
# 提示链接我们构建的库
target_link_libraries(CharliesDemo PUBLIC MathLib)

```

​	现在，我们就完成了我们的构建脚本即可！

