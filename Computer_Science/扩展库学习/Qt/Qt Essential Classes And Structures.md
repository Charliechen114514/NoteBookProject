# Qt Essential Classes

## QVariant

​	同std::variant是一样的，他是一个更加高级的union。在一个时间下，它虽然实际上只能是一种类型，但是一个variant可以hold住所有的types（因为本质上都是内存块塞0和1，理解这一点的同志们直接看API就完事了），这样，我们直接就可以存储一个通用的类型，对于不同的场景做对应的转换就好了！我的另一个意思是：提供了一个统一的接口来处理各种数据类型。`QVariant` 可以存储简单的数据类型（如整型、浮点型、字符串等）以及复杂的数据类型（如自定义类、列表等）。

| 方法                                         | 描述                                                         |
| -------------------------------------------- | ------------------------------------------------------------ |
| `QVariant()`                                 | 默认构造函数，创建一个无效的 QVariant。                      |
| `QVariant(const QVariant &other)`            | 拷贝构造函数。                                               |
| `QVariant(QVariant &&other)`                 | 移动构造函数。                                               |
| `QVariant &operator=(const QVariant &other)` | 赋值操作符。                                                 |
| `QVariant &operator=(QVariant &&other)`      | 移动赋值操作符。                                             |
| `bool isValid() const`                       | 检查 QVariant 是否有效。                                     |
| `bool isNull() const`                        | 检查 QVariant 是否为空。                                     |
| `int type() const`                           | 返回存储数据的类型。                                         |
| `QString typeName() const`                   | 返回存储数据类型的名称。                                     |
| `template<typename T>`                       | `T value()`：将 QVariant 转换为指定类型。                    |
| `void clear()`                               | 清除存储的数据。                                             |
| `static QVariant fromValue(const T &value)`  | 从值创建 QVariant。                                          |
| `template<typename T>`                       | `static T fromVariant(const QVariant &variant)`：从 QVariant 获取值。 |
| `QVariantList toList() const`                | 将 QVariant 转换为 QVariantList（如有必要）。                |
| `QVariantMap toMap() const`                  | 将 QVariant 转换为 QVariantMap（如有必要）。                 |

> 试一手：

```
#include <QVariant>
#include <QString>
#include <QDebug>

int main() {
    QVariant variant;

    // 存储整数
    variant = 42;
    qDebug() << "Stored integer:" << variant.toInt();

    // 存储字符串
    variant = QString("Hello, QVariant!");
    qDebug() << "Stored string:" << variant.toString();

    // 检查类型
    if (variant.type() == QVariant::String) {
        qDebug() << "Variant holds a string.";
    }

    // 使用 fromValue 和 toVariant
    QVariant doubleVariant = QVariant::fromValue(3.14);
    double value = doubleVariant.value<double>();
    qDebug() << "Stored double:" << value;

    return 0;
}
```

## QFlags

​	这个笔者感悟比较深：他在你设置一些对象的属性的时候很管用：它通过位运算提供了一种简单而高效的方式来组合多个标志。`QFlags` 主要用于处理枚举类型的标志组合，使得代码更加清晰和易于维护。

​	笔者建议你按照std::bitset的一个高级抽象来理解。我们实际上就是使用比特表达信息！完事！

| 方法                                          | 描述                                                         |
| --------------------------------------------- | ------------------------------------------------------------ |
| `QFlags()`                                    | 默认构造函数，创建一个无效的 QFlags 对象。                   |
| `QFlags(Flags f)`                             | 构造函数，使用给定的标志初始化 QFlags 对象。                 |
| `QFlags(const QFlags &other)`                 | 拷贝构造函数。                                               |
| `QFlags(QFlags &&other)`                      | 移动构造函数。                                               |
| `QFlags &operator=(const QFlags &other)`      | 赋值操作符。                                                 |
| `QFlags &operator=(QFlags &&other)`           | 移动赋值操作符。                                             |
| `QFlags operator|(const QFlags &other) const` | 或操作符，用于实现位或操作符，允许将两个 `QFlags` 对象的标志组合在一起。这个操作符返回一个新的 `QFlags` 对象，包含了两个原对象的所有标志。 |
| `QFlags operator&(const QFlags &other) const` | 位与操作符，用于获取共同标志。                               |
| `QFlags operator^(const QFlags &other) const` | 位异或操作符，用于获取不共同的标志。                         |
| `QFlags operator~() const`                    | 位非操作符，反转当前标志。                                   |
| `bool testFlag(Flags f) const`                | 测试特定标志是否被设置。                                     |
| `QFlags& operator|=(const QFlags &other)`     | 赋值操作                                                     |
| `QFlags& operator&=(const QFlags &other)`     | 复合位与赋值操作符。                                         |
| `QFlags& operator^=(const QFlags &other)`     | 复合位异或赋值操作符。                                       |
| `static QFlags fromValue(int value)`          | 从整数值创建 QFlags 对象。                                   |

```
#include <QCoreApplication>
#include <QFlags>
#include <QDebug>

enum MyFlags {
    FlagA = 0x1, // 0001
    FlagB = 0x2, // 0010
    FlagC = 0x4  // 0100
};

Q_DECLARE_FLAGS(MyFlagSet, MyFlags)

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 创建标志
    MyFlagSet flags;
    flags |= FlagA;  // 添加 FlagA
    flags |= FlagB;  // 添加 FlagB

    // 检查标志
    if (flags.testFlag(FlagA)) {
        qDebug() << "FlagA is set.";
    }

    if (flags.testFlag(FlagB)) {
        qDebug() << "FlagB is set.";
    }

    // 组合标志
    MyFlagSet moreFlags = FlagB | FlagC; // 组合 FlagB 和 FlagC
    flags |= moreFlags; // 添加组合的标志

    // 输出当前标志状态
    qDebug() << "Current flags:" << flags;

    // 测试 FlagC 是否被设置
    if (flags.testFlag(FlagC)) {
        qDebug() << "FlagC is set.";
    }

    // 使用位与操作获取共同标志
    MyFlagSet commonFlags = flags & moreFlags;
    qDebug() << "Common flags:" << commonFlags;

    return a.exec();
}

Q_DECLARE_METATYPE(MyFlagSet)
```

## QRandomGenerator

​	这个玩意是检验你是Qt6选手还是Qt5选手的标准类。他就是qt5的qrand()的高级版，提供了一系列方法来生成均匀分布和正态分布的随机数，支持多种数据类型。`QRandomGenerator` 是线程安全的，因此可以在多线程环境中安全使用。

- **性能**：高效生成随机数，适合需要大量随机数的应用场景。
- **可移植性**：在不同平台上具有一致的行为。
- **种子控制**：支持通过种子初始化生成器，以便于生成可重复的随机数序列。
- **随机数分布**：支持生成均匀分布、正态分布等类型的随机数。

| 方法                                | 描述                                         |
| ----------------------------------- | -------------------------------------------- |
| `QRandomGenerator()`                | 默认构造函数，使用当前时间作为种子。         |
| `QRandomGenerator(uint seed)`       | 使用指定种子初始化生成器。                   |
| `static QRandomGenerator *global()` | 返回全局的随机数生成器实例。                 |
| `int bounded(int range)`            | 生成一个在 `[0, range)` 范围内的随机整数。   |
| `double generateDouble()`           | 生成一个在 `[0.0, 1.0)` 范围内的随机浮点数。 |
| `int generateInt()`                 | 生成一个随机整数。                           |
| `void seed(uint seed)`              | 设置生成器的种子。                           |
| `static void globalSeed(uint seed)` | 设置全局随机数生成器的种子。                 |

```
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 创建一个 QRandomGenerator 实例
    QRandomGenerator *generator = QRandomGenerator::global();

    // 生成 10 个随机整数
    qDebug() << "Random integers:";
    for (int i = 0; i < 10; ++i) {
        int randomInt = generator->bounded(100); // 在 [0, 100) 范围内
        qDebug() << randomInt;
    }

    // 生成 10 个随机浮点数
    qDebug() << "Random doubles:";
    for (int i = 0; i < 10; ++i) {
        double randomDouble = generator->generateDouble(); // 在 [0.0, 1.0) 范围内
        qDebug() << randomDouble;
    }

    return a.exec();
}
```

## 经典的Qt容器

### QVector

​	`QVector` 是 Qt 提供的一种动态数组容器，类似于 C++ 标准库中的 `std::vector`。它用于存储同一类型的元素，并支持快速的随机访问、插入和删除操作。`QVector` 主要用于需要动态调整大小且频繁读取元素的场景。

​	是的，就是std::vector的Qt版本。笔者在《Qt高性能编程》中见到过观点：use std rather than qt，这个事情仁者见仁智者见智。笔者认为按照场景使用最好。

- **动态大小**：`QVector` 可以根据需要自动扩展或收缩。
- **快速随机访问**：可以通过索引快速访问元素，访问时间复杂度为 O(1)。
- **连续内存存储**：数据在内存中是连续存储的，能更好地利用 CPU 缓存，提高性能。
- **支持多种数据类型**：可以存储任意类型的数据，通常与 Qt 的其他类型（如 `QVariant`）结合使用。
- **高效的内存管理**：通过智能的内存分配策略减少内存碎片。

| 方法                                             | 描述                                               |
| ------------------------------------------------ | -------------------------------------------------- |
| `QVector<T>()`                                   | 默认构造函数，创建一个空的 `QVector`。             |
| `QVector<T>(int size)`                           | 创建一个指定大小的 `QVector`，元素初始化为 `T()`。 |
| `QVector<T>(const QVector<T> &other)`            | 拷贝构造函数，复制另一个 `QVector` 的内容。        |
| `~QVector()`                                     | 析构函数，释放内存。                               |
| `T& operator[](int index)`                       | 返回指定索引处的元素的引用。                       |
| `const T& operator[](int index) const`           | 返回指定索引处的元素的常量引用。                   |
| `int size() const`                               | 返回当前元素的数量。                               |
| `bool isEmpty() const`                           | 判断 `QVector` 是否为空。                          |
| `void append(const T &value)`                    | 在 `QVector` 末尾添加一个新元素。                  |
| `void prepend(const T &value)`                   | 在 `QVector` 开头添加一个新元素。                  |
| `void insert(int index, const T &value)`         | 在指定位置插入一个新元素。                         |
| `void removeAt(int index)`                       | 移除指定位置的元素。                               |
| `void clear()`                                   | 清空 `QVector` 中的所有元素。                      |
| `T takeAt(int index)`                            | 移除并返回指定位置的元素。                         |
| `void resize(int size)`                          | 调整 `QVector` 的大小，增加或减少元素数量。        |
| `T& first()`                                     | 返回第一个元素的引用。                             |
| `T& last()`                                      | 返回最后一个元素的引用。                           |
| `QVector<T> mid(int pos, int length = -1) const` | 返回从 `pos` 开始的子数组。                        |
| `QVector<T> &operator=(const QVector<T> &other)` | 赋值运算符，复制另一个 `QVector` 的内容。          |
| `bool operator==(const QVector<T> &other) const` | 判断两个 `QVector` 是否相等。                      |

```
#include <QVector>
#include <QDebug>

int main() {
    // 创建一个空的 QVector
    QVector<int> vec;

    // 添加元素
    vec.append(10);
    vec.append(20);
    vec.append(30);
    
    // 输出当前大小
    qDebug() << "Size:" << vec.size(); // Size: 3

    // 访问元素
    qDebug() << "First element:" << vec.first(); // First element: 10

    // 插入元素
    vec.insert(1, 15);
    
    // 输出元素
    for (int i = 0; i < vec.size(); ++i) {
        qDebug() << vec[i]; // 10 15 20 30
    }

    // 移除元素
    vec.removeAt(2); // 移除元素 20

    // 清空 QVector
    vec.clear();
    
    // 检查是否为空
    qDebug() << "Is empty:" << vec.isEmpty(); // Is empty: true

    return 0;
}
```

​	它的数据结构特点：

- **访问速度**：因为数据是连续存储的，所以 `QVector` 的访问速度通常比链表等非连续存储的数据结构快。
- **插入和删除**：虽然在末尾插入和删除操作的时间复杂度为 O(1)，但在中间位置插入和删除的时间复杂度为 O(n)，这要注意。

​	它的常见的使用场景：

- **动态数据集合**：当需要一个大小可变的数组来存储数据时，例如用户输入、实时数据流等。
- **临时存储**：处理算法时使用的临时数据，例如排序、搜索等。
- **图形界面**：在 Qt 应用中，常用于存储 UI 组件、图形对象等。

### QList

> 注意在Qt6下，QList == QVector，这里是给Qt5看的：

​	QList实际上更加的智能，这点随了Java的List：原生类型存数值，复杂类型存指针。但是注意，QList仍然是连续的。比起来，QLinkedList确实是真正的链表！这点请所有使用链表的客户程序员注意！使用链表是QLinkedList！

| `QList<T>()`                                   | 默认构造函数，创建一个空的 `QList`。             |
| ---------------------------------------------- | ------------------------------------------------ |
| `QList<T>(int size)`                           | 创建一个指定大小的 `QList`，元素初始化为 `T()`。 |
| `QList<T>(const QList<T> &other)`              | 拷贝构造函数，复制另一个 `QList` 的内容。        |
| `~QList()`                                     | 析构函数，释放内存。                             |
| `T& operator[](int index)`                     | 返回指定索引处的元素的引用。                     |
| `const T& operator[](int index) const`         | 返回指定索引处的元素的常量引用。                 |
| `int size() const`                             | 返回当前元素的数量。                             |
| `bool isEmpty() const`                         | 判断 `QList` 是否为空。                          |
| `void append(const T &value)`                  | 在 `QList` 末尾添加一个新元素。                  |
| `void prepend(const T &value)`                 | 在 `QList` 开头添加一个新元素。                  |
| `void insert(int index, const T &value)`       | 在指定位置插入一个新元素。                       |
| `void removeAt(int index)`                     | 移除指定位置的元素。                             |
| `void clear()`                                 | 清空 `QList` 中的所有元素。                      |
| `T takeAt(int index)`                          | 移除并返回指定位置的元素。                       |
| `T& first()`                                   | 返回第一个元素的引用。                           |
| `T& last()`                                    | 返回最后一个元素的引用。                         |
| `QList<T> mid(int pos, int length = -1) const` | 返回从 `pos` 开始的子列表。                      |
| `QList<T> &operator=(const QList<T> &other)`   | 赋值运算符，复制另一个 `QList` 的内容。          |
| `bool operator==(const QList<T> &other) const` | 判断两个 `QList` 是否相等。                      |

```
#include <QList>
#include <QDebug>

int main() {
    // 创建一个空的 QList
    QList<int> list;

    // 添加元素
    list.append(10);
    list.append(20);
    list.append(30);

    // 输出当前大小
    qDebug() << "Size:" << list.size(); // Size: 3

    // 访问元素
    qDebug() << "First element:" << list.first(); // First element: 10

    // 插入元素
    list.insert(1, 15);
    
    // 输出元素
    for (int i = 0; i < list.size(); ++i) {
        qDebug() << list[i]; // 10 15 20 30
    }

    // 移除元素
    list.removeAt(2); // 移除元素
```

### QMap

​	`QMap` 是 Qt 提供的一种基于红黑树的关联容器，主要用于存储键值对。它类似于 C++ 标准库中的 `std::map`，但在使用上更加方便，特别是在与 Qt 其他类的结合使用时。`QMap` 提供了快速的查找、插入和删除操作，同时能够保持键的有序性。

- **有序性**：`QMap` 中的键是自动排序的，因此可以根据键的顺序遍历元素。
- **快速查找**：使用红黑树实现，查找、插入和删除的平均时间复杂度为 O(log n)。
- **多类型支持**：可以存储任意类型的键值对，通常与 Qt 的其他类型（如 `QString`, `QVariant`）结合使用。
- **重复键处理**：`QMap` 不允许重复的键，如果插入一个已存在的键，原有的值将被覆盖。
- **易于使用的 API**：提供了丰富的方法来操作键值对，方便开发者管理数据。

| 方法                                                         | 描述                                       |
| ------------------------------------------------------------ | ------------------------------------------ |
| `QMap<Key, T>()`                                             | 默认构造函数，创建一个空的 `QMap`。        |
| `QMap<Key, T>(const QMap<Key, T> &other)`                    | 拷贝构造函数，复制另一个 `QMap` 的内容。   |
| `~QMap()`                                                    | 析构函数，释放内存。                       |
| `int size() const`                                           | 返回当前键值对的数量。                     |
| `bool isEmpty() const`                                       | 判断 `QMap` 是否为空。                     |
| `void insert(const Key &key, const T &value)`                | 插入一个键值对，如果键已存在，值将被覆盖。 |
| `T value(const Key &key, const T &defaultValue = T()) const` | 返回指定键的值，如果键不存在则返回默认值。 |
| `void remove(const Key &key)`                                | 移除指定键的元素。                         |
| `bool contains(const Key &key) const`                        | 判断是否包含指定的键。                     |
| `QList<Key> keys() const`                                    | 返回所有键的列表。                         |
| `QList<T> values() const`                                    | 返回所有值的列表。                         |
| `QList<T> values(const Key &key) const`                      | 返回指定键对应的值的列表。                 |
| `Key firstKey() const`                                       | 返回第一个键。                             |
| `Key lastKey() const`                                        | 返回最后一个键。                           |
| `void clear()`                                               | 清空 `QMap` 中的所有键值对。               |
| `QMap<Key, T> &operator=(const QMap<Key, T> &other)`         | 赋值运算符，复制另一个 `QMap` 的内容。     |
| `bool operator==(const QMap<Key, T> &other) const`           | 判断两个 `QMap` 是否相等。                 |

```
#include <QMap>
#include <QString>
#include <QDebug>

int main() {
    QMap<QString, int> grades;

    // 插入键值对
    grades.insert("Alice", 85);
    grades.insert("Bob", 90);
    grades.insert("Charlie", 78);

    // 输出总数
    qDebug() << "Total students:" << grades.size(); // Total students: 3

    // 获取某个学生的成绩
    qDebug() << "Alice's grade:" << grades.value("Alice"); // Alice's grade: 85

    // 修改成绩
    grades["Alice"] = 95; // 更新 Alice 的成绩
    qDebug() << "Alice's updated grade:" << grades.value("Alice"); // Alice's updated grade: 95

    // 检查某个学生是否存在
    if (grades.contains("David")) {
        qDebug() << "David's grade:" << grades.value("David");
    } else {
        qDebug() << "David not found."; // David not found.
    }

    // 移除某个学生
    grades.remove("Charlie");

    // 输出所有学生的成绩
    for (const QString &name : grades.keys()) {
        qDebug() << name << ":" << grades.value(name);
    }

    // 清空 QMap
    grades.clear();
    qDebug() << "Is empty:" << grades.isEmpty(); // Is empty: true

    return 0;
}
```

`QMap` 的性能在大多数场景下都非常优秀。由于采用红黑树实现，其查找、插入和删除操作的平均时间复杂度为 O(log n)。虽然在某些情况下，`QMap` 的性能可能略逊于 `QHash`（哈希表实现），但在需要有序存储时，`QMap` 是更好的选择。

`QMap` 的使用场景非常广泛，包括但不限于：

- **配置存储**：存储配置信息时，可以使用键值对的形式存储各类配置项，便于查找和修改。
- **数据索引**：在需要根据某种键（如 ID、名称）快速查找数据时，使用 `QMap` 可以高效地管理这些关系。
- **有序数据**：在需要保持元素顺序的同时又要快速查找和修改的场合，`QMap` 是一个理想的选择。



### QMultiMap

`QMultiMap` 是 Qt 提供的一种特殊的关联容器，允许多个值与同一个键关联。它类似于 `QMap`，但不同之处在于 `QMultiMap` 允许键的重复，适合于需要存储多个值而不想丢失键的场景。

- **允许重复键**：`QMultiMap` 允许多个值与同一个键关联，适合存储一对多关系的数据。
- **自动排序**：与 `QMap` 一样，`QMultiMap` 中的键是自动排序的，能够根据键的顺序遍历元素。
- **快速查找**：基于红黑树实现，查找、插入和删除的平均时间复杂度为 O(log n)。
- **多类型支持**：支持存储任意类型的键值对，通常与 Qt 的其他类型（如 `QString`, `QVariant`）结合使用。
- **易于使用的 API**：提供了丰富的方法来操作键值对，方便开发者管理数据。

| 方法                                                         | 描述                                          |
| ------------------------------------------------------------ | --------------------------------------------- |
| `QMultiMap<Key, T>()`                                        | 默认构造函数，创建一个空的 `QMultiMap`。      |
| `QMultiMap<Key, T>(const QMultiMap<Key, T> &other)`          | 拷贝构造函数，复制另一个 `QMultiMap` 的内容。 |
| `~QMultiMap()`                                               | 析构函数，释放内存。                          |
| `int size() const`                                           | 返回当前键值对的数量。                        |
| `bool isEmpty() const`                                       | 判断 `QMultiMap` 是否为空。                   |
| `void insert(const Key &key, const T &value)`                | 插入一个键值对，允许同一个键有多个值。        |
| `QList<T> values(const Key &key) const`                      | 返回指定键对应的所有值的列表。                |
| `void remove(const Key &key)`                                | 移除所有与指定键关联的元素。                  |
| `bool contains(const Key &key) const`                        | 判断是否包含指定的键。                        |
| `QList<Key> keys() const`                                    | 返回所有键的列表。                            |
| `Key firstKey() const`                                       | 返回第一个键。                                |
| `Key lastKey() const`                                        | 返回最后一个键。                              |
| `void clear()`                                               | 清空 `QMultiMap` 中的所有键值对。             |
| `QMultiMap<Key, T> &operator=(const QMultiMap<Key, T> &other)` | 赋值运算符，复制另一个 `QMultiMap` 的内容。   |
| `bool operator==(const QMultiMap<Key, T> &other) const`      | 判断两个 `QMultiMap` 是否相等。               |

```
#include <QMultiMap>
#include <QString>
#include <QDebug>

int main() {
    QMultiMap<QString, QString> studentCourses;

    // 插入多个值
    studentCourses.insert("Alice", "Math");
    studentCourses.insert("Alice", "Science");
    studentCourses.insert("Bob", "Math");
    studentCourses.insert("Charlie", "History");
    studentCourses.insert("Charlie", "Math");

    // 输出每个学生的课程
    for (const QString &student : studentCourses.keys()) {
        QList<QString> courses = studentCourses.values(student);
        qDebug() << student << "is enrolled in:" << courses;
    }

    // 移除某个学生的所有课程
    studentCourses.remove("Alice");

    // 检查是否存在
    if (!studentCourses.contains("Alice")) {
        qDebug() << "Alice has been removed from the course list.";
    }

    // 清空 QMultiMap
    studentCourses.clear();
    qDebug() << "Is empty:" << studentCourses.isEmpty(); // Is empty: true

    return 0;
}
```

​	`QMultiMap` 的性能与 `QMap` 类似，查找、插入和删除操作的平均时间复杂度为 O(log n)。由于它允许重复键的特性，在管理一对多关系时非常有效。

`QMultiMap` 适用于多种场景:

- **多对多关系存储**：在需要存储一对多或多对多关系的数据时，`QMultiMap` 是理想的选择。
- **分类数据**：在需要将数据分类存储时，可以使用相同的键来代表不同的类别。
- **标签系统**：在实现标签系统时，可以将多个标签与同一对象关联，方便管理和查询。

### QSet

​	`QSet` 是 Qt 提供的一种集合容器，主要用于存储唯一值的集合。它类似于 C++ 标准库中的 `std::set`，但在使用上更加方便，特别是在与 Qt 其他类的结合使用时。`QSet` 适合用于需要存储不重复元素的场景，提供快速的查找、插入和删除操作。

- **唯一性**：`QSet` 中的每个元素都是唯一的，不能存储重复的值。
- **无序性**：元素在集合中没有特定的顺序，遍历时的顺序与插入顺序无关。
- **快速查找**：基于哈希表实现，查找、插入和删除操作的平均时间复杂度为 O(1)。
- **多类型支持**：可以存储任意类型的数据，通常与 Qt 的其他类型（如 `QString`, `QVariant`）结合使用。
- **易于使用的 API**：提供了丰富的方法来操作集合，方便开发者管理数据。

| 方法                                            | 描述                                                   |
| ----------------------------------------------- | ------------------------------------------------------ |
| `QSet<T>()`                                     | 默认构造函数，创建一个空的 `QSet`。                    |
| `QSet<T>(const QSet<T> &other)`                 | 拷贝构造函数，复制另一个 `QSet` 的内容。               |
| `~QSet()`                                       | 析构函数，释放内存。                                   |
| `int size() const`                              | 返回集合中元素的数量。                                 |
| `bool isEmpty() const`                          | 判断 `QSet` 是否为空。                                 |
| `void insert(const T &value)`                   | 向集合中添加一个新元素，如果元素已存在，则不进行操作。 |
| `void remove(const T &value)`                   | 移除集合中的指定元素。                                 |
| `bool contains(const T &value) const`           | 判断集合是否包含指定元素。                             |
| `QList<T> toList() const`                       | 将集合转换为 `QList`。                                 |
| `QSet<T> intersect(const QSet<T> &other) const` | 返回与另一个集合的交集。                               |
| `QSet<T> unite(const QSet<T> &other) const`     | 返回与另一个集合的并集。                               |
| `QSet<T> subtract(const QSet<T> &other) const`  | 返回从集合中减去另一个集合后的结果。                   |
| `void clear()`                                  | 清空集合中的所有元素。                                 |
| `QSet<T> &operator=(const QSet<T> &other)`      | 赋值运算符，复制另一个 `QSet` 的内容。                 |
| `bool operator==(const QSet<T> &other) const`   | 判断两个 `QSet` 是否相等。                             |

```
#include <QSet>
#include <QString>
#include <QDebug>

int main() {
    QSet<QString> students;

    // 插入学生姓名
    students.insert("Alice");
    students.insert("Bob");
    students.insert("Charlie");
    students.insert("Alice"); // 重复插入，不会改变集合

    // 输出当前学生人数
    qDebug() << "Total students:" << students.size(); // Total students: 3

    // 检查是否包含某个学生
    if (students.contains("Bob")) {
        qDebug() << "Bob is in the set.";
    }

    // 移除某个学生
    students.remove("Charlie");

    // 输出所有学生姓名
    for (const QString &name : students) {
        qDebug() << name;
    }

    // 清空集合
    students.clear();
    qDebug() << "Is empty:" << students.isEmpty(); // Is empty: true

    return 0;
}
```

### QHash

`QHash` 是 Qt 提供的一种基于哈希表的关联容器，主要用于存储键值对。它允许快速的查找、插入和删除操作，适合需要频繁访问数据的场景。与 `QMap` 不同的是，`QHash` 不会自动排序其元素，主要关注数据的存取效率。

- **键的唯一性**：`QHash` 中的每个键都是唯一的，不能存储重复的键。
- **无序性**：元素在集合中没有特定的顺序，遍历时的顺序与插入顺序无关。
- **快速查找**：基于哈希表实现，查找、插入和删除操作的平均时间复杂度为 O(1)。
- **多类型支持**：可以存储任意类型的键值对，通常与 Qt 的其他类型（如 `QString`, `QVariant`）结合使用。
- **易于使用的 API**：提供了丰富的方法来操作键值对，方便开发者管理数据。

| 方法                                                         | 描述                                                   |
| ------------------------------------------------------------ | ------------------------------------------------------ |
| `QHash<Key, T>()`                                            | 默认构造函数，创建一个空的 `QHash`。                   |
| `QHash<Key, T>(const QHash<Key, T> &other)`                  | 拷贝构造函数，复制另一个 `QHash` 的内容。              |
| `~QHash()`                                                   | 析构函数，释放内存。                                   |
| `int size() const`                                           | 返回当前键值对的数量。                                 |
| `bool isEmpty() const`                                       | 判断 `QHash` 是否为空。                                |
| `void insert(const Key &key, const T &value)`                | 向哈希表中插入一个键值对，如果键已存在，则值将被覆盖。 |
| `void remove(const Key &key)`                                | 移除指定键的元素。                                     |
| `bool contains(const Key &key) const`                        | 判断是否包含指定的键。                                 |
| `T value(const Key &key, const T &defaultValue = T()) const` | 返回指定键的值，如果键不存在则返回默认值。             |
| `QList<Key> keys() const`                                    | 返回所有键的列表。                                     |
| `QList<T> values() const`                                    | 返回所有值的列表。                                     |
| `void clear()`                                               | 清空 `QHash` 中的所有键值对。                          |
| `QHash<Key, T> &operator=(const QHash<Key, T> &other)`       | 赋值运算符，复制另一个 `QHash` 的内容。                |
| `bool operator==(const QHash<Key, T> &other) const`          | 判断两个 `QHash` 是否相等。                            |

```
cpp复制代码#include <QHash>
#include <QString>
#include <QDebug>

int main() {
    QHash<QString, int> grades;

    // 插入学生成绩
    grades.insert("Alice", 85);
    grades.insert("Bob", 90);
    grades.insert("Charlie", 78);

    // 输出学生总数
    qDebug() << "Total students:" << grades.size(); // Total students: 3

    // 获取某个学生的成绩
    qDebug() << "Alice's grade:" << grades.value("Alice"); // Alice's grade: 85

    // 修改成绩
    grades["Alice"] = 95; // 更新 Alice 的成绩
    qDebug() << "Alice's updated grade:" << grades.value("Alice"); // Alice's updated grade: 95

    // 检查某个学生是否存在
    if (grades.contains("David")) {
        qDebug() << "David's grade:" << grades.value("David");
    } else {
        qDebug() << "David not found."; // David not found.
    }

    // 移除某个学生
    grades.remove("Charlie");

    // 输出所有学生的成绩
    for (const QString &name : grades.keys()) {
        qDebug() << name << ":" << grades.value(name);
    }

    // 清空 QHash
    grades.clear();
    qDebug() << "Is empty:" << grades.isEmpty(); // Is empty: true

    return 0;
}
```

`QHash` 适用于多种场景，例如：

- **数据索引**：在需要根据某个键快速查找数据时，`QHash` 是一个理想的选择。
- **缓存机制**：可以使用 `QHash` 来实现简单的缓存机制，以存储计算结果或数据。
- **频率统计**：在处理需要统计元素出现频率的场景时，`QHash` 可以轻松存储和更新频率。