# C++八股文——异常处理（要点 + 流程）

#### 前言

​	笔者补充一些遇到的八股文，也算是一些最近复习的小复盘！

## 一句话现说明白

​	C++异常的核心思想是：**表驱动（zero-cost） + 栈展开（unwinding）**。正常路径无运行时开销，**只有抛出时才付代价（查表 + 调用析构 + 跳转）**。

## 两种常见实现模型

- **Itanium C++ ABI 风格（GCC/Clang 在大多数平台上）**
  - 属于 *zero-cost* 模型：编译阶段生成异常处理表，运行时根据表查找处理器；运行库提供接口，都会放到一个.eh_frame的段种。
- **MSVC（Windows）**
  - x64 也采用表驱动（结构不同），x86 早期有基于 SEH 的注册表方式（注册栈帧）。实现细节和符号不同，但总体思想类似：抛出时查表/调用 personality function、展开栈帧并转到 landing pad。

##  抛出到捕获的大致运行时流程

1. **创建异常对象**
   - 编译器把 `throw E;` 翻译成：调用 `__cxa_allocate_exception(size)` 分配内存，拷贝/移动构造 `E` 到该内存，再调用 `__cxa_throw(ptr, &type_info, cleanup)`。（对于非内存异常的exception会分配到堆上，其余可能会生成到预留的静态区上（也就是标记成static的地方））
   - Exception object 内部关联了 `type_info`（用于类型匹配）和运行期控制块。
2. **搜索阶段（search phase）**
   - 运行时（如 `_Unwind_RaiseException`）从抛出点开始，调用每个栈帧对应的 *personality function*（由编译器在异常表里指定）来询问该帧是否有匹配该异常类型的 catch。
   - 这个阶段不会执行析构，只是查表判断是否存在合适的 handler，并记录目标帧/landing pad。
3. **展开阶段（cleanup / unwind phase）**
   - 若找到 handler，运行时开始从抛出点向目标帧展开栈（逐帧执行），调用每帧的析构（局部对象析构、finally-like cleanups），直到到达目标 landing pad。
   - 对每个被展开的帧，会执行与之对应的清理代码（这些清理代码也在编译阶段生成并通过表索引）。
4. **进入 handler**
   - 当展开到目标帧后，运行时把异常对象“传递”进 handler：
     - 如果 `catch (T e)`（按值），就会把异常对象拷贝/移动到 handler 的局部拷贝（注意可能发生切片）；
     - 如果 `catch (T& e)`（按引用），handler 引用直接绑定到异常对象（不会拷贝）。
   - 然后控制流跳到 handler 的代码继续执行。
5. **结束/释放**
   - 当 handler 执行完退出异常处理（或异常在 handler 中被再次抛出），运行时在必要时释放最初分配的异常对象（通过 `__cxa_free_exception` 等）。

## 表数据：LSDA / DWARF / .gcc_except_table

- 编译器为每个函数生成 unwind 信息（如何恢复寄存器、如何运行局部析构的表），并生成语言特定数据区（LSDA，Language Specific Data Area），LSDA 中记录该函数有哪些 landing pads、哪些 catch 能匹配哪些类型、需要哪些指针调整（pointer adjustment）等。运行期只读这些表来决定怎样展开栈和哪里跳到 handler。

## 类型匹配 & 指针调整

- catch 的匹配基于 RTTI (`std::type_info`)：在 LSDA 中记录要匹配的类型描述符，运行时比较异常对象的 type_info 与 catch 的 type_info。
- 对于多继承 / 虚继承，异常对象的指针可能需要做 **adjustment**（偏移）以使其正确地转换成 catch 所期待的基类指针；这些偏移也在表中记录，personality function 应用它们。

## rethrow、嵌套 & 异常在析构中抛出

- `throw;` 在 catch 块内会重新抛出当前异常（运行时会记录“当前正在处理的异常”）。
- 在栈展开过程中若析构函数又抛出异常，会导致 **terminate**（**C++规定不能有两个同时未被捕获的异常**）。C++11 引入 `std::uncaught_exceptions()` 来更可靠地检测嵌套 unwind 情形。

## exception_ptr 与跨线程/跨模块

- `std::exception_ptr` 可以保存异常并在别处重新抛出（内部是对异常控制块的共享引用）。用于把异常带到其他线程、延后处理等。
- **跨共享库（DLL/.so）边界**：必须保证 ABI 与 RTTI 类型信息兼容（相同的 C++ ABI），否则类型匹配会失败。

## noexcept 与终止策略

- `noexcept` 或 `throw()`：若函数在运行中抛出异常，会立即调用 `std::terminate()`（默认终止程序）。编译器会基于 noexcept 做优化（内联更大胆等）。
- `std::terminate` 默认调用 `abort()`，可以通过 `std::set_terminate` 自定义。

## 性能与建议

- 正常路径（不抛异常）几乎无运行时成本（表驱动）；缺点是抛出时开销大（查表 + 栈展开 + 析构执行）。
- 推荐用异常处理错误而非普通控制流；但是嵌入式、驱动、实时系统常规避免异常（因为抛出代价不可预测）。
- 对于频繁失败的操作（例如经常性错误返回），考虑返回错误码而不是抛异常。

## 异常面试答题卡片（速记）

1. **C++ 异常怎么实现？**
   表驱动 + 栈展开（zero-cost）。编译器生成 unwind 表和 LSDA，运行时查表、调用 personality function、展开栈并转到 landing pad。
2. **zero-cost model 是啥？**
    正常路径无运行时开销，只有真正抛出时才查表和展开栈。
3. **抛出时发生什么（高层流程）？**
    分配异常对象 → `__cxa_throw` → search phase 找 handler → unwind phase 执行析构 → 进入 handler。
4. **异常对象如何分配与释放？**
    通常用 `__cxa_allocate_exception` 分配，处理完由运行时释放；`exception_ptr` 可共享引用。
5. **类型匹配怎么做？**
    用 RTTI (`type_info`) 与 LSDA 中记录的类型比对，必要时对指针做偏移（多继承/虚继承）。
6. **catch 按值/按引用差别？**
    `catch(T)`：按值拷贝（可能切片）；`catch(T&)`：绑定到原异常对象，无拷贝。
7. **`throw;` 与 `throw e;` 区别？**
    `throw;` 重新抛出当前异常（保留原信息）；`throw e;` 会构造拷贝，可能切片。
8. **personality function 和 LSDA 是啥？**
    LSDA：语言特定数据区，记录 landing pads 与匹配信息；personality function 解释 LSDA 决定是否处理/清理。
9. **为什么析构中再抛异常会 terminate？**
    因为栈展开时不能同时存在两个未处理异常——会调用 `std::terminate()`。
10. **`noexcept` 有何作用？**
     表示不抛异常；若抛出则 `std::terminate()`；编译器可据此做更激进优化。
11. **rethrow 如何实现？**
     `throw;` 或 `std::rethrow_exception` 利用运行时记录的当前异常/exception_ptr 重抛。
12. **异常跨线程/跨模块注意点？**
     可用 `std::exception_ptr` 跨线程；跨库需保证相同 C++ ABI 与 RTTI，否则匹配可能失败。
13. **`catch(...)` 能干什么？**
     捕获任意异常但无法直接得知类型，可用 `std::current_exception()` + `rethrow` 获取更多信息。
14. **性能建议？**
     异常用于错误处理（非频繁控制流）；频繁错误用返回码，实时/内核代码尽量避免异常。
15. **如何安全写析构？**
     析构内捕获所有异常，绝不让异常逃出析构，或用日志/状态记录错误。
16. **如何测试异常安全性？**
     引入失败注入（模拟分配失败），验证 strong/basic/no-throw 语义与资源无泄漏。
17. **常见能背的函数名字（加分项）？**
     `__cxa_allocate_exception`, `__cxa_throw`, `_Unwind_RaiseException`, `__cxa_begin_catch`, `__cxa_end_catch`, `__cxa_rethrow`。
18. **一行记忆句（总纲）**
     “编译期把元数据放表，运行时抛出时查表展开栈并执行清理后跳到 handler。