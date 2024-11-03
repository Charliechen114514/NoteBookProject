# 说一说QString

​	在这篇博客中，我打算总结一下一个非常，非常常用的类：那就是Qt的QString这个类。笔者认为，这算是在最广泛使用的C++库中最好用的字符串之一了。

## QString类的构造

​	QString的构造方式非常多，但是笔者大多数情况下只会用到其中的几个。

| 构造函数                                             | 描述                                                      |
| ---------------------------------------------------- | --------------------------------------------------------- |
| `QString()`                                          | 默认构造函数，创建一个空字符串。                          |
| `QString(QChar ch)`                                  | 从单个 `QChar` 创建 `QString`。                           |
| `QString(QLatin1StringView str)`                     | 从 `QLatin1StringView` 创建 `QString`。                   |
| `QString(const QByteArray &ba)`                      | 从 `QByteArray` 创建 `QString`。                          |
| `QString(const char *str)`                           | 从 C 风格字符串创建 `QString`。                           |
| `QString(const char8_t *str)`                        | 从 UTF-8 编码的 C 风格字符串创建 `QString`（自 6.1 起）。 |
| `QString(const QChar *unicode, qsizetype size = -1)` | 从字符数组创建 `QString`，可指定字符数量。                |
| `QString(qsizetype size, QChar ch)`                  | 创建一个指定大小的字符串，所有字符初始化为 `ch`。         |
| `QString(const QString &other)`                      | 复制构造函数，从另一个 `QString` 创建。                   |
| `QString(QString &&other)`                           | 移动构造函数，从另一个 `QString` 移动数据。               |
| `~QString()`                                         | 析构函数，释放 `QString` 的资源。                         |

​	生成的QString包含了至少STL的所有功能。这里笔者不再赘述。但是为了阐述QT的字符串跟std::string的区别，有必要介绍一下QChar，也就是QString的组成单元：

## QChar: Base of the QString

​	QChar的API也很精彩：

| API                                             | 描述                                           |
| ----------------------------------------------- | ---------------------------------------------- |
| `QChar()`                                       | 默认构造函数，创建一个空字符。                 |
| `QChar(QChar::SpecialCharacter ch)`             | 从特殊字符枚举创建 `QChar`。                   |
| `QChar(QLatin1Char ch)`                         | 从 `QLatin1Char` 创建 `QChar`。                |
| `QChar(char ch)`                                | 从单个 `char` 创建 `QChar`。                   |
| `QChar(char16_t ch)`                            | 从 `char16_t` 创建 `QChar`。                   |
| `QChar(int code)`                               | 从 Unicode 代码点创建 `QChar`。                |
| `QChar(short code)`                             | 从短整型代码点创建 `QChar`。                   |
| `QChar(uchar ch)`                               | 从无符号字符创建 `QChar`。                     |
| `QChar(uint code)`                              | 从无符号整型代码点创建 `QChar`。               |
| `QChar(ushort code)`                            | 从无符号短整型代码点创建 `QChar`。             |
| `QChar(wchar_t ch)`                             | 从宽字符创建 `QChar`。                         |
| `QChar(uchar cell, uchar row)`                  | 从单元格和行号创建 `QChar`（用于表格字符）。   |
| `QChar::Category category() const`              | 获取字符类别。                                 |
| `uchar cell() const`                            | 获取字符的单元格编号。                         |
| `unsigned char combiningClass() const`          | 获取字符的组合类。                             |
| `QString decomposition() const`                 | 获取字符的分解形式。                           |
| `QChar::Decomposition decompositionTag() const` | 获取字符的分解标记。                           |
| `int digitValue() const`                        | 获取字符的数字值（如果是数字字符）。           |
| `QChar::Direction direction() const`            | 获取字符的方向。                               |
| `bool hasMirrored() const`                      | 检查字符是否具有镜像形式。                     |
| `bool isDigit() const`                          | 检查字符是否是数字字符。                       |
| `bool isHighSurrogate() const`                  | 检查字符是否为高代理项。                       |
| `bool isLetter() const`                         | 检查字符是否为字母字符。                       |
| `bool isLetterOrNumber() const`                 | 检查字符是否为字母或数字字符。                 |
| `bool isLowSurrogate() const`                   | 检查字符是否为低代理项。                       |
| `bool isLower() const`                          | 检查字符是否为小写字母。                       |
| `bool isMark() const`                           | 检查字符是否为标记字符。                       |
| `bool isNonCharacter() const`                   | 检查字符是否为非字符（如控制字符）。           |
| `bool isNull() const`                           | 检查字符是否为空字符。                         |
| `bool isNumber() const`                         | 检查字符是否为数字。                           |
| `bool isPrint() const`                          | 检查字符是否为可打印字符。                     |
| `bool isPunct() const`                          | 检查字符是否为标点符号。                       |
| `bool isSpace() const`                          | 检查字符是否为空格字符。                       |
| `bool isSurrogate() const`                      | 检查字符是否为代理字符。                       |
| `bool isSymbol() const`                         | 检查字符是否为符号字符。                       |
| `bool isTitleCase() const`                      | 检查字符是否为标题大小写。                     |
| `bool isUpper() const`                          | 检查字符是否为大写字母。                       |
| `QChar::JoiningType joiningType() const`        | 获取字符的连接类型。                           |
| `QChar mirroredChar() const`                    | 获取字符的镜像字符。                           |
| `uchar row() const`                             | 获取字符的行号。                               |
| `QChar::Script script() const`                  | 获取字符的脚本类型。                           |
| `QChar toCaseFolded() const`                    | 将字符转换为折叠形式（用于大小写不敏感比较）。 |
| `char toLatin1() const`                         | 将字符转换为 `Latin-1` 字符。                  |
| `QChar toLower() const`                         | 将字符转换为小写形式。                         |
| `QChar toTitleCase() const`                     | 将字符转换为标题大小写形式。                   |
| `QChar toUpper() const`                         | 将字符转换为大写形式。                         |
| `char16_t & unicode()`                          | 获取字符的 Unicode 值（可修改）。              |
| `char16_t unicode() const`                      | 获取字符的 Unicode 值（只读）。                |
| `QChar::UnicodeVersion unicodeVersion() const`  |                                                |

​	非常多！他也能从静态的非QChar数据转化：

| API                                                     | 描述                                              |
| ------------------------------------------------------- | ------------------------------------------------- |
| `QChar::Category category(char32_t ucs4)`               | 获取指定 UCS-4 代码点的字符类别。                 |
| `unsigned char combiningClass(char32_t ucs4)`           | 获取指定 UCS-4 代码点的组合类。                   |
| `QChar::UnicodeVersion currentUnicodeVersion()`         | 获取当前的 Unicode 版本。                         |
| `QString decomposition(char32_t ucs4)`                  | 获取指定 UCS-4 代码点的分解形式。                 |
| `QChar::Decomposition decompositionTag(char32_t ucs4)`  | 获取指定 UCS-4 代码点的分解标记。                 |
| `int digitValue(char32_t ucs4)`                         | 获取指定 UCS-4 代码点的数字值（如果是数字字符）。 |
| `QChar::Direction direction(char32_t ucs4)`             | 获取指定 UCS-4 代码点的方向。                     |
| `QChar fromLatin1(char c)`                              | 从单个 `Latin-1` 字符创建 `QChar`。               |
| `QChar fromUcs2(char16_t c)`                            | 从 UCS-2 代码点创建 `QChar`（自 6.0 起）。        |
| `auto fromUcs4(char32_t c)`                             | 从 UCS-4 代码点创建 `QChar`（自 6.0 起）。        |
| `bool hasMirrored(char32_t ucs4)`                       | 检查指定 UCS-4 代码点是否具有镜像形式。           |
| `char16_t highSurrogate(char32_t ucs4)`                 | 获取指定 UCS-4 代码点的高代理字符。               |
| `bool isDigit(char32_t ucs4)`                           | 检查指定 UCS-4 代码点是否为数字字符。             |
| `bool isHighSurrogate(char32_t ucs4)`                   | 检查指定 UCS-4 代码点是否为高代理项。             |
| `bool isLetter(char32_t ucs4)`                          | 检查指定 UCS-4 代码点是否为字母字符。             |
| `bool isLetterOrNumber(char32_t ucs4)`                  | 检查指定 UCS-4 代码点是否为字母或数字字符。       |
| `bool isLowSurrogate(char32_t ucs4)`                    | 检查指定 UCS-4 代码点是否为低代理项。             |
| `bool isLower(char32_t ucs4)`                           | 检查指定 UCS-4 代码点是否为小写字母。             |
| `bool isMark(char32_t ucs4)`                            | 检查指定 UCS-4 代码点是否为标记字符。             |
| `bool isNonCharacter(char32_t ucs4)`                    | 检查指定 UCS-4 代码点是否为非字符。               |
| `bool isNumber(char32_t ucs4)`                          | 检查指定 UCS-4 代码点是否为数字。                 |
| `bool isPrint(char32_t ucs4)`                           | 检查指定 UCS-4 代码点是否为可打印字符。           |
| `bool isPunct(char32_t ucs4)`                           | 检查指定 UCS-4 代码点是否为标点符号。             |
| `bool isSpace(char32_t ucs4)`                           | 检查指定 UCS-4 代码点是否为空格字符。             |
| `bool isSurrogate(char32_t ucs4)`                       | 检查指定 UCS-4 代码点是否为代理字符。             |
| `bool isSymbol(char32_t ucs4)`                          | 检查指定 UCS-4 代码点是否为符号字符。             |
| `bool isTitleCase(char32_t ucs4)`                       | 检查指定 UCS-4 代码点是否为标题大小写。           |
| `bool isUpper(char32_t ucs4)`                           | 检查指定 UCS-4 代码点是否为大写字母。             |
| `QChar::JoiningType joiningType(char32_t ucs4)`         | 获取指定 UCS-4 代码点的连接类型。                 |
| `char16_t lowSurrogate(char32_t ucs4)`                  | 获取指定 UCS-4 代码点的低代理字符。               |
| `char32_t mirroredChar(char32_t ucs4)`                  | 获取指定 UCS-4 代码点的镜像字符。                 |
| `bool requiresSurrogates(char32_t ucs4)`                | 检查指定 UCS-4 代码点是否需要代理。               |
| `QChar::Script script(char32_t ucs4)`                   | 获取指定 UCS-4 代码点的脚本类型。                 |
| `char32_t surrogateToUcs4(char16_t high, char16_t low)` | 将高低代理字符转换为 UCS-4 代码点。               |
| `char32_t surrogateToUcs4(QChar high, QChar low)`       | 将高低代理 `QChar` 转换为 UCS-4 代码点。          |
| `char32_t toCaseFolded(char32_t ucs4)`                  | 将指定 UCS-4 代码点转换为折叠形式。               |
| `char32_t toLower(char32_t ucs4)`                       | 将指定 UCS-4 代码点转换为小写形式。               |
| `char32_t toTitleCase(char32_t ucs4)`                   | 将指定 UCS-4 代码点转换为标题大小写形式。         |
| `char32_t toUpper(char32_t ucs4)`                       | 将指定 UCS-4 代码点转换为大写形式。               |
| `QChar::UnicodeVersion unicodeVersion(char32_t ucs4)`   | 获取指定 UCS-4 代码点的 Unicode 版本。            |

​	当然，它还支持一些运算符：

| API                                                     | 描述                                              |
| ------------------------------------------------------- | ------------------------------------------------- |
| `bool operator!=(const QChar &c1, const QChar &c2)`     | 检查两个 `QChar` 对象是否不相等。                 |
| `bool operator<(const QChar &c1, const QChar &c2)`      | 检查第一个 `QChar` 是否小于第二个 `QChar`。       |
| `QDataStream & operator<<(QDataStream &out, QChar chr)` | 将 `QChar` 对象写入数据流。                       |
| `bool operator<=(const QChar &c1, const QChar &c2)`     | 检查第一个 `QChar` 是否小于或等于第二个 `QChar`。 |
| `bool operator==(const QChar &c1, const QChar &c2)`     | 检查两个 `QChar` 对象是否相等。                   |
| `bool operator>(const QChar &c1, const QChar &c2)`      | 检查第一个 `QChar` 是否大于第二个 `QChar`。       |
| `bool operator>=(const QChar &c1, const QChar &c2)`     | 检查第一个 `QChar` 是否大于或等于第二个 `QChar`。 |
| `QDataStream & operator>>(QDataStream &in, QChar &chr)` | 从数据流中读取 `QChar` 对象。                     |

上面的API非常繁多。不需要每一个记录。而是用到啥现查。

### 尝试我们的QChar