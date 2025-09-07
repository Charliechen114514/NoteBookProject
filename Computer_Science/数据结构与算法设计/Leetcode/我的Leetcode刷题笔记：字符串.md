

# 我的Leetcode刷题笔记：字符串

## 1. 字符串拆分与替换

**典型题型**：路径分隔符替换、字符串空格处理、字符替换等。

- **基础操作**：
  - 遍历字符串逐字符检查；
  - 条件替换字符（例如 `'.'` 替换为空格 `' '`）；
  - 利用 `substr`、`split`（不同语言有不同实现）进行字符串拆分。
- **注意点**：
  - 边界条件处理，如空字符串、连续多个分隔符；
  - 是否需要原地修改字符串或构造新字符串；
  - 时间复杂度一般为 O(n)，n 为字符串长度。

------

## 2. 字符串逆序与单词反转

**典型题型**：反转单词顺序、处理多余空格。

- **核心思路**：
  - 利用双指针扫描字符串，跳过多余空格；
  - 按空格分割单词，存入数组或栈；
  - 逆序拼接单词，确保单词间仅保留一个空格。
- **常用技巧**：
  - 预处理去除前后空格；
  - 使用 `istringstream`（C++）、`split`（Python）简化拆词；
  - 小心处理空字符串或只有空格的情况。

------

## 3. 字符串轮转

**典型题型**：字符串循环移位、密码动态更新。

- **实现方式**：
  - 分割字符串为两部分，拼接顺序交换；
  - 或用循环替换方法，注意避免额外空间消耗。
- **扩展**：
  - 右旋转、左旋转均可类比处理；
  - 适合用作面试字符串算法题基础。

------

## 4. 字符串转换为整数（myAtoi）

**典型题型**：模拟 C/C++ `atoi` 函数。

- **关键点**：
  - 跳过前导空格；
  - 处理正负号；
  - 连续数字转换为整数；
  - 边界溢出截断处理；
  - 遇到非数字字符停止解析。
- **实现细节**：
  - 使用 `long` 类型存储中间结果防止溢出；
  - 判断结果是否超出 `INT_MIN` 和 `INT_MAX` 边界。

------

## 5. 有效数字判断

**典型题型**：判断字符串是否表示合法浮点数。

- **解析流程**：
  - 跳过前导空格；
  - 解析符号与整数、小数部分；
  - 解析可选指数部分（`e` 或 `E` 后接整数）；
  - 跳过尾随空格；
  - 判断是否完全解析且满足规则。
- **解析子模块**：
  - `parseDigits`：连续数字检查；
  - `parseNumber`：整数或小数，含符号；
  - `parseInteger`：指数部分整数，含符号。
- **重点难点**：
  - 小数格式多样（如 `"4."`，`".9"`）；
  - 指数必须有整数部分，且不接受小数；
  - 字符串中不可包含无关字符。

### 🔒题目解析：路径加密

给定一个路径字符串 `path`，其中使用 `'.'` 作为分隔符，现在需要将所有的 `'.'` 替换为空格 `' '`，以达到加密的目的。

------

### ✅示例

- **输入**：`"a.aef.qerf.bb"`
- **输出**：`"a aef qerf bb"`

------

### 🧠思路解析

1. 遍历整个 `path` 字符串。
2. 每当遇到字符 `'.'`，就将其替换为 `' '`。
3. 可直接在原字符串上修改，避免额外空间开销。

------

### 💻代码实现

```cpp
class Solution {
public:
    string pathEncryption(string path) {
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == '.') {
                path[i] = ' ';
            }
        }
        return path;
    }
};
```

或使用标准库函数：

```cpp
#include <algorithm>

class Solution {
public:
    string pathEncryption(string path) {
        std::replace(path.begin(), path.end(), '.', ' ');
        return path;
    }
};
```

------

### 🧪复杂度分析

- **时间复杂度**：O(n)，其中 n 是字符串的长度。
- **空间复杂度**：O(1)，在原字符串上修改。

------

### 📌注意事项

- 空字符串输入时代码依然有效。
- 标准库 `std::replace` 更简洁，功能等效。

------

### ✨题解：反转单词顺序

#### ✅题目目标

将一段从右往左表达的句子 `message` 转换为从左往右的自然语序。
 需要满足：

- 移除首尾空格；
- 单词间只保留一个空格；
- 单词顺序反转。

------

### 💡思路解析

1. **跳过多余空格**：手动处理，避免使用额外库函数；
2. **提取所有单词**：遍历整个字符串，用 `substr()` 将非空单词提取；
3. **逆序拼接**：从单词列表的尾部向前拼接字符串，注意处理空格。

------

### ✅简洁实现

```cpp
class Solution {
public:
    string reverseMessage(string message) {
        vector<string> words;
        int n = message.size();
        int i = 0;

        // 跳过前导空格
        while (i < n && message[i] == ' ') i++;

        while (i < n) {
            string word = "";
            // 提取一个完整单词
            while (i < n && message[i] != ' ') {
                word += message[i++];
            }
            if (!word.empty()) {
                words.push_back(word);
            }
            // 跳过空格
            while (i < n && message[i] == ' ') i++;
        }

        // 组装结果字符串
        string result;
        for (int j = words.size() - 1; j >= 0; --j) {
            result += words[j];
            if (j > 0) result += ' ';
        }

        return result;
    }
};
```

------

### 🔍复杂度分析

- **时间复杂度**：O(n)，其中 n 是 message 的长度；
- **空间复杂度**：O(n)，用于存储拆分的单词和最终字符串。

------

### ✅测试示例

```cpp
输入:  "  hello   world!  "
输出:  "world! hello"

输入:  "a good   example"
输出:  "example good a"
```

------

### 🔐题目解析：动态密码更新

给定字符串 `password` 和整数 `target`，要求将前 `target` 个字符**顺序移动**到末尾，返回新的密码。

------

### ✅示例

- 输入：`password = "s3cur1tyC0d3"`, `target = 4`
   输出：`"r1tyC0d3s3cu"`
- 输入：`password = "lrloseumgh"`, `target = 6`
   输出：`"umghlrlose"`

------

### 🧠思路解析

我们可以将原字符串分为两部分：

- `left = password.substr(0, target)`
- `right = password.substr(target)`

然后返回拼接结果 `right + left` 即可。

你的原实现手动构造一个结果字符串 `result`，效率也不错，但可以进一步精简。

------

### 💻更简洁写法

```cpp
class Solution {
public:
    string dynamicPassword(string password, int target) {
        return password.substr(target) + password.substr(0, target);
    }
};
```

------

### 🧪复杂度分析

- **时间复杂度**：O(n)，n 为 `password.length()`；
- **空间复杂度**：O(n)，需要新的字符串存储结果。

## 🔐题目解析：字符串转换为 32 位有符号整数（myAtoi）

给定一个字符串 `s`，实现一个函数将其转换为 32 位有符号整数（类似 C/C++ 中的 `atoi` 函数）。转换过程需要：

- 跳过前导空格；
- 处理可选的正负号；
- 读取连续数字字符；
- 遇到非数字字符停止转换；
- 处理整数溢出，截断至 [-2³¹, 2³¹-1] 范围。

------

### ✅示例

输入：s = "42"
 输出：42

输入：s = "   -42"
 输出：-42

输入：s = "4193 with words"
 输出：4193

------

### 🧠思路解析

1. 利用索引遍历字符串，先跳过所有前导空格。
2. 判断第一个非空字符是否为符号 `'+'` 或 `'-'`，确定整数符号。
3. 继续遍历数字字符，累计构建结果整数。
4. 每次累加后判断是否越界，若越界直接返回对应边界值。
5. 遇到非数字字符停止处理，返回当前结果。

------

### 💻代码实现

```cpp
class Solution {
public:
    int myAtoi(string str) {
        int i = 0, n = str.size();

        // 跳过前导空格
        while (i < n && str[i] == ' ') i++;

        // 读取符号
        int sign = 1;
        if (i < n && (str[i] == '+' || str[i] == '-')) {
            sign = (str[i] == '-') ? -1 : 1;
            i++;
        }

        long result = 0;
        // 读取数字字符，构建整数
        while (i < n && isdigit(str[i])) {
            result = result * 10 + (str[i] - '0');

            // 判断溢出并截断
            if (sign * result >= INT_MAX) return INT_MAX;
            if (sign * result <= INT_MIN) return INT_MIN;

            i++;
        }

        return static_cast<int>(sign * result);
    }
};
```

------

### 🧪复杂度分析

- 时间复杂度：O(n)，其中 n 是字符串长度。
- 空间复杂度：O(1)，只使用了常数额外空间。

------

### 📌总结

- 该算法线性扫描，清晰处理所有边界情况。
- 利用 `long` 防止中间溢出，及时截断。
- 是面试中常见字符串解析题目，适合掌握字符处理和边界判断。

好的，按照你之前的格式，帮你写一份有效数字判断的题解：

------

## 🔐题目解析：判断字符串是否为有效数字

给定一个字符串 `s`，判断其是否表示一个有效数字。有效数字的规则包括：

- 可有前导和尾随空格；
- 主体部分为整数或小数，整数和小数都可带符号；
- 可选的指数部分，由 `'e'` 或 `'E'` 后跟一个整数（可带符号）组成。

------

### ✅示例

输入：s = "0"
 输出：true

输入：s = "e"
 输出：false

输入：s = "."
 输出：false

------

### 🧠思路解析

1. 跳过前导空格；
2. 解析数字主体部分（整数或小数）：
   - 可选符号 `'+'` 或 `'-'`；
   - 小数的三种形式：
     - 数字 + '.'
     - 数字 + '.' + 数字
     - '.' + 数字
3. 解析可选指数部分：
   - `'e'` 或 `'E'` 后跟一个整数（可带符号）；
4. 跳过尾随空格；
5. 整体必须全部解析完且满足格式，才判定为有效数字。

------

### 💻代码实现

```cpp
class Solution {
public:
    bool validNumber(string s) {
        int i = 0, n = s.length();

        // 跳过前导空格
        while (i < n && s[i] == ' ') i++;

        // 解析数字主体部分（整数或小数）
        bool isNumeric = parseNumber(s, i);

        // 解析指数部分（如果存在）
        if (i < n && (s[i] == 'e' || s[i] == 'E')) {
            i++;
            bool hasExponent = parseInteger(s, i);
            if (!hasExponent) return false;
            isNumeric = isNumeric && hasExponent;
        }

        // 跳过尾随空格
        while (i < n && s[i] == ' ') i++;

        // 确保字符串全部解析完成
        return isNumeric && i == n;
    }

private:
    // 解析整数或小数部分
    bool parseNumber(const string& s, int& i) {
        // 可选符号
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) i++;

        bool intPart = parseDigits(s, i);

        // 处理小数点和小数部分
        if (i < s.size() && s[i] == '.') {
            i++;
            bool fracPart = parseDigits(s, i);
            // 整数部分和小数部分至少有一部分存在
            return intPart || fracPart;
        }

        return intPart;
    }

    // 解析指数部分（整数）
    bool parseInteger(const string& s, int& i) {
        // 可选符号
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) i++;
        return parseDigits(s, i);
    }

    // 解析数字序列
    bool parseDigits(const string& s, int& i) {
        int start = i;
        while (i < s.size() && isdigit(s[i])) i++;
        return i > start;
    }
};
```

------

🧪复杂度分析

- 时间复杂度：O(n)，n 为字符串长度。
- 空间复杂度：O(1)，只使用指针索引，无额外数据结构。

------

📌总结

- 利用指针扫描字符串，分块处理，结构清晰。
- 严格按照有效数字规则，避免误判。
- 适合字符串格式校验与解析类题目。

