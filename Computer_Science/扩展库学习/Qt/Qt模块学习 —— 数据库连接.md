# Qt模块学习 —— 数据库连接

## 前言

​	在这个Section开始之前，我们就正式的结束大多数Qt Core/Widget的核心内容的学习了，之后开始更多的就是领域部分的学习 + 高阶内容。我们首先开始的就是Qt + 数据库开发的导论。

​	笔者建议，看完这章去写一个基于数据库查询的ToDo练习是合适的。

## 架构层说明

​	分为三层。

### 驱动程序层

​	这包括类 QSqlDriver、QSqlDriverCreator、QSqlDriverCreatorBase、QSqlDriverPlugin 和 QSqlResult。

此层提供特定数据库和 SQL API 层之间的低级桥梁。有关详细信息，请参阅 SQL 数据库驱动程序。

### SQL API 层

​	这些类提供对数据库的访问。使用 QSqlDatabase 类进行连接。使用 QSqlQuery 类实现数据库交互。除了 QSqlDatabase 和 QSqlQuery，SQL API 层还由 QSqlError、QSqlField、QSqlIndex 和 QSqlRecord 支持。

### 用户界面层

​	这些类将数据库中的数据链接到数据感知小部件。它们包括 QSqlQueryModel、QSqlTableModel 和 QSqlRelationalTableModel。这些类旨在与 Qt 的模型/视图框架配合使用。

​	值得一提的是我们作为普通程序员，可以不去理会驱动程序层的SqlDriver以及其工具类，他们是编写自己的驱动的，感兴趣的同志请自行阅读官方文档查阅API

# SQL API 层

## 数据库实例：QSqlDataBase

​	想要连接一个数据库，我们必须创建一个连接数据库的连接，填写必须要的参数（比如说主机名称，账号密码，数据库名称等），然后打开进行操作。这个事情交给QSqlDataBase

​	QSqlDatabase 类提供了一个通过连接访问数据库的接口。QSqlDatabase 的实例代表连接。**连接通过受支持的数据库驱动程序之一提供对数据库的访问，这些驱动程序派生自 QSqlDriver**。或者，您可以从 QSqlDriver 子类化您自己的数据库驱动程序。QSqlDatabase 实例只能由创建它的线程访问。因此，您必须确保在正确的上下文中创建它们。或者，您可以使用 QSqlDatabase::moveToThread() 更改上下文。

​	通过调用静态 addDatabase() 函数之一创建连接（即 QSqlDatabase 的实例），在其中指定要使用的驱动程序或驱动程序类型（取决于数据库的类型）和连接名称。连接以其自己的名称而不是它连接到的数据库的名称而闻名。您可以与一个数据库建立多个连接。 QSqlDatabase 还支持默认连接的概念，即未命名的连接。要创建默认连接，请在调用 addDatabase() 时不要传递连接名称参数。随后，如果您调用任何静态成员函数而不指定连接名称，则将假定使用默认连接。以下代码片段显示了如何创建和打开到 PostgreSQL 数据库的默认连接：

```
QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
db.setHostName("acidalia");
db.setDatabaseName("customdb");
db.setUserName("mojito");
db.setPassword("J0a1m8");
bool ok = db.open();
```

​	创建 QSqlDatabase 对象后，使用 setDatabaseName()、setUserName()、setPassword()、setHostName()、setPort() 和 setConnectOptions() 设置连接参数。然后调用 open() 激活与数据库的物理连接。只有打开该连接后，该连接才可用。

​	上面定义的连接将是默认连接，因为我们没有为 addDatabase() 指定连接名称。随后，您可以通过调用不带连接名称参数的 database() 来获取默认连接：

```
QSqlDatabase db = QSqlDatabase::database();
```

​	QSqlDatabase 是一个值类。通过一个 QSqlDatabase 实例对数据库连接所做的更改将影响代表同一连接的其他 QSqlDatabase 实例。使用 cloneDatabase() 基于现有数据库连接创建独立的数据库连接。

> 警告：强烈建议**您不要将 QSqlDatabase 的副本作为类的成员保留**，因为这将阻止在关闭时正确清理实例。如果您需要访问现有的 QSqlDatabase，则应使用 database() 进行访问。如果您选择拥有 QSqlDatabase 成员变量，则需要在删除 QCoreApplication 实例之前删除该变量，否则可能会导致未定义的行为。

​	**如果您创建多个数据库连接，请在调用 addDatabase() 时为每个连接指定一个唯一的连接名称。**使用带有连接名称的 database() 来获取该连接。使用带有连接名称的 removeDatabase() 来删除连接。如果您尝试删除其他 QSqlDatabase 对象引用的连接，QSqlDatabase 会输出警告。使用 contains() 查看给定的连接名称是否在连接列表中。

| **方法**              | **说明**                                                     |
| --------------------- | ------------------------------------------------------------ |
| `tables()`            | 返回当前连接的数据库中的表名列表。可以通过 `QSql::TableType` 类型过滤器（例如：`QSql::Tables`、`QSql::Views`、`QSql::SystemTables`）筛选不同类型的表。 |
| `primaryIndex()`      | 返回指定表的主索引。主索引是表中用于唯一标识记录的索引（通常是主键）。 |
| `record()`            | 返回指定表的元数据（例如字段信息）。该方法返回一个 `QSqlRecord` 对象，包含了表中字段的名称、类型、默认值等详细信息。 |
| `transaction()`       | 启动一个数据库事务，允许一组操作在同一事务中执行。如果事务成功，可以提交；如果失败，可以回滚。 |
| `commit()`            | 提交当前事务，保存事务期间所做的所有更改，完成事务的执行。   |
| `rollback()`          | 取消当前事务，撤销自事务开始以来所做的所有更改。             |
| `hasFeature()`        | 检查数据库驱动是否支持某个特性，如事务或保存点等。           |
| `lastError()`         | 返回上次数据库操作发生的错误信息。可以通过该方法获取详细的错误描述，帮助调试。 |
| `drivers()`           | 返回当前可用的所有 SQL 驱动程序的名称列表。                  |
| `isDriverAvailable()` | 检查特定的 SQL 驱动是否可用。可以用来验证所需的驱动是否存在并可用。 |
| `registerSqlDriver()` | 注册一个自定义的 SQL 驱动。允许将自定义的数据库驱动与 `QSqlDatabase` 一起使用。 |

### API

#### **Public Functions**

| **函数名**                                                   | **描述**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QSqlDatabase()`                                             | 默认构造函数                                                 |
| `QSqlDatabase(const QSqlDatabase &other)`                    | 复制构造函数，复制另一个 `QSqlDatabase` 对象的内容。         |
| `~QSqlDatabase()`                                            | 析构函数，关闭数据库连接。                                   |
| `void close()`                                               | 关闭当前数据库连接。                                         |
| `bool commit()`                                              | 提交当前事务。                                               |
| `QString connectOptions() const`                             | 获取连接的选项字符串。                                       |
| `QString connectionName() const`                             | 获取当前数据库连接的名称。                                   |
| `QString databaseName() const`                               | 获取当前数据库的名称。                                       |
| `QSqlDriver * driver() const`                                | 获取与数据库连接关联的驱动程序。                             |
| `QString driverName() const`                                 | 获取驱动程序的名称。                                         |
| `QString hostName() const`                                   | 获取数据库的主机名。                                         |
| `bool isOpen() const`                                        | 检查数据库连接是否已打开。                                   |
| `bool isOpenError() const`                                   | 检查数据库连接是否出现错误。                                 |
| `bool isValid() const`                                       | 检查数据库连接是否有效。                                     |
| `QSqlError lastError() const`                                | 获取最近的数据库错误。                                       |
| `bool moveToThread(QThread *targetThread)`                   | 将数据库对象移动到目标线程。仅在 Qt 6.8 或更高版本中可用。   |
| `QSql::NumericalPrecisionPolicy numericalPrecisionPolicy() const` | 获取数字精度策略。                                           |
| `bool open()`                                                | 打开数据库连接。                                             |
| `bool open(const QString &user, const QString &password)`    | 使用用户名和密码打开数据库连接。                             |
| `QString password() const`                                   | 获取当前数据库的密码。                                       |
| `int port() const`                                           | 获取当前数据库连接使用的端口号。                             |
| `QSqlIndex primaryIndex(const QString &tablename) const`     | 获取指定表的主键索引。                                       |
| `QSqlRecord record(const QString &tablename) const`          | 获取指定表的记录结构。                                       |
| `bool rollback()`                                            | 回滚当前事务。                                               |
| `void setConnectOptions(const QString &options = QString())` | 设置数据库连接的选项。                                       |
| `void setDatabaseName(const QString &name)`                  | 设置数据库名称。                                             |
| `void setHostName(const QString &host)`                      | 设置数据库的主机名。                                         |
| `void setNumericalPrecisionPolicy(QSql::NumericalPrecisionPolicy precisionPolicy)` | 设置数字精度策略。                                           |
| `void setPassword(const QString &password)`                  | 设置数据库的密码。                                           |
| `void setPort(int port)`                                     | 设置数据库连接使用的端口号。                                 |
| `void setUserName(const QString &name)`                      | 设置数据库的用户名。                                         |
| `QStringList tables(QSql::TableType type = QSql::Tables) const` | 获取数据库中的表名列表。                                     |
| `QThread * thread() const`                                   | 获取当前数据库连接所在的线程。仅在 Qt 6.8 或更高版本中可用。 |
| `bool transaction()`                                         | 开始事务。                                                   |
| `QString userName() const`                                   | 获取数据库的用户名。                                         |
| `QSqlDatabase & operator=(const QSqlDatabase &other)`        | 赋值操作符，赋值另一个 `QSqlDatabase` 对象的内容。           |

#### **Static Public Members**

| **函数名**                                                   | **描述**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QSqlDatabase addDatabase(const QString &type, const QString &connectionName = QLatin1StringView(defaultConnection))` | 创建并返回一个新的 `QSqlDatabase` 对象，并指定数据库类型和连接名称。 |
| `QSqlDatabase addDatabase(QSqlDriver *driver, const QString &connectionName = QLatin1StringView(defaultConnection))` | 创建并返回一个新的 `QSqlDatabase` 对象，并指定驱动程序和连接名称。 |
| `QSqlDatabase cloneDatabase(const QSqlDatabase &other, const QString &connectionName)` | 克隆一个数据库连接，并指定新连接的名称。                     |
| `QSqlDatabase cloneDatabase(const QString &other, const QString &connectionName)` | 克隆一个现有数据库连接，并指定新连接的名称。                 |
| `QStringList connectionNames()`                              | 获取所有已注册的数据库连接名称。                             |
| `bool contains(const QString &connectionName = QLatin1StringView(defaultConnection))` | 检查指定的连接名称是否存在。                                 |
| `QSqlDatabase database(const QString &connectionName = QLatin1StringView(defaultConnection), bool open = true)` | 获取指定连接名称的数据库对象，并可选择自动打开连接。         |
| `QStringList drivers()`                                      | 获取当前可用的所有数据库驱动程序名称。                       |
| `bool isDriverAvailable(const QString &name)`                | 检查指定名称的数据库驱动程序是否可用。                       |
| `void registerSqlDriver(const QString &name, QSqlDriverCreatorBase *creator)` | 注册一个新的数据库驱动程序。                                 |
| `void removeDatabase(const QString &connectionName)`         | 移除指定连接名称的数据库连接。                               |

#### **Protected Functions**

| **函数名**                          | **描述**                                               |
| ----------------------------------- | ------------------------------------------------------ |
| `QSqlDatabase(QSqlDriver *driver)`  | 构造函数，接受一个 `QSqlDriver` 作为数据库的驱动程序。 |
| `QSqlDatabase(const QString &type)` | 构造函数，接受数据库类型作为参数。                     |

## QSqlRecord

​	QSqlQuery 封装了在 QSqlDatabase 上执行的 SQL 查询中创建、导航和检索数据所涉及的功能。它可用于执行 DML（数据操作语言）语句，例如 SELECT、INSERT、UPDATE 和 DELETE，以及 DDL（数据定义语言）语句，例如 CREATE TABLE。它还可用于执行非标准 SQL 的数据库特定命令（例如 PostgreSQL 的 SET DATESTYLE=ISO）。

​	成功执行的 SQL 语句将查询的状态设置为活动状态，以便 isActive() 返回 true。否则，查询的状态将设置为非活动状态。无论哪种情况，在执行新的 SQL 语句时，查询都会定位在无效记录上。必须将活动查询导航到有效记录（以便 isValid() 返回 true），然后才能检索值。

​	对于某些数据库，**如果在调用 commit() 或 rollback() 时存在 SELECT 语句的活动查询，则提交或回滚将失败。有关详细信息，请参阅 isActive()。**

使用以下函数来导航记录：

- next()
- previous()
- first()
- last()
- seek()

​	这些函数允许程序员向前、向后或任意移动查询返回的记录。如果您只需要向前移动结果（例如，通过使用 next()），则可以使用 setForwardOnly()，这将节省大量内存开销并提高某些数据库的性能。一旦活动查询定位在有效记录上，就可以使用 value() 检索数据。所有数据都使用 QVariants 从 SQL 后端传输。

例如：

```
QSqlQuery query("SELECT country FROM artist");
while (query.next()) {
	QString country = query.value(0).toString();
	doSomething(country);
}
```

​	要访问查询返回的数据，请使用 value(int)。通过传递字段在语句中的位置（从 0 开始），可以访问 SELECT 语句返回的数据中的每个字段。这使得使用 SELECT * 查询变得不可取，因为返回的字段的顺序是不确定的。

​	为了提高效率，没有函数可以通过名称访问字段（除非您使用带有名称的准备好的查询，如下所述）。要将字段名称转换为索引，请使用 record().indexOf()，例如：

```
QSqlQuery query("SELECT * FROM artist");
int fieldNo = query.record().indexOf("country");
while (query.next()) {
	QString country = query.value(fieldNo).toString();
	doSomething(country);
}
```

​	QSqlQuery 支持准备好的查询执行和将参数值绑定到占位符。有些数据库不支持这些功能，因此对于这些数据库，Qt 模拟了所需的功能。例如，Oracle 和 ODBC 驱动程序具有适当的准备好的查询支持，Qt 会利用它；但对于没有此支持的数据库，Qt 会自行实现该功能，例如，在执行查询时用实际值替换占位符。使用 numRowsAffected() 可找出非 SELECT 查询影响了多少行，使用 size() 可找出 SELECT 检索了多少行。

​	Oracle 数据库使用冒号名称语法来识别占位符，例如 :name。ODBC 仅使用 ? 字符。Qt 支持这两种语法，但限制是您不能在同一个查询中混合使用它们。

您可以使用 boundValues() 检索单个变量中所有字段的值。

注意：并非所有 SQL 操作都支持绑定值。请参阅数据库系统的文档以检查它们的可用性。

#### 绑定值的方法

下面我们将介绍使用四种不同绑定方法的相同示例，以及将值绑定到存储过程的一个示例。

使用命名占位符进行命名绑定：

```
QSqlQuery query;
query.prepare("INSERT INTO person (id, forename, surname) "
"VALUES (:id, :forename, :surname)");
query.bindValue(":id", 1001);
query.bindValue(":forename", "Bart");
query.bindValue(":surname", "Simpson");
query.exec();
```

使用命名占位符进行位置绑定：

```
QSqlQuery query;
query.prepare("INSERT INTO person (id, forename, surname) "
"VALUES (:id, :forename, :surname)");
query.bindValue(0, 1001);
query.bindValue(1, "Bart");
query.bindValue(2, "Simpson");
query.exec();
```

使用位置占位符绑定值（版本 1）：

```
QSqlQuery query;
query.prepare("INSERT INTO person (id, forename, surname) "
"VALUES (?, ?, ?)");
query.bindValue(0, 1001);
query.bindValue(1, "Bart");
query.bindValue(2, "Simpson");
query.exec();
```

使用位置占位符绑定值（版本 2）：

```
QSqlQuery query;
query.prepare("INSERT INTO person (id, forename, surname) "
"VALUES (?, ?, ?)");
query.addBindValue(1001);
query.addBindValue("Bart");
query.addBindValue("Simpson");
query.exec();
```

将值绑定到存储过程：此代码调用存储过程填充 AsciiToInt()，通过其 in 参数向其传递一个字符，并将其结果放入 out 参数中。

```
QSqlQuery query;
query.prepare("CALL AsciiToInt(?, ?)");
query.bindValue(0, "A");
query.bindValue(1, 0, QSql::Out);
query.exec();
int i = query.boundValue(1).toInt(); // i 为 65
```

​	请注意，未绑定的参数将保留其值。

​	使用 return 语句返回值或返回多个结果集的存储过程不受完全支持。有关具体详细信息，请参阅 SQL 数据库驱动程序。

> 警告：在创建 QSqlQuery 之前，必须加载 SQL 驱动程序并打开连接。此外，在查询存在时，连接必须保持打开状态；否则，QSqlQuery 的行为是未定义的。

### API

| **方法**                                             | **说明**                                                    |
| ---------------------------------------------------- | ----------------------------------------------------------- |
| `QSqlRecord()`                                       | 默认构造函数，创建一个空的 `QSqlRecord` 对象。              |
| `QSqlRecord(const QSqlRecord &other)`                | 拷贝构造函数，创建一个与 `other` 相同的 `QSqlRecord` 对象。 |
| `QSqlRecord(QSqlRecord &&other)`                     | 移动构造函数，转移 `other` 对象的所有资源。                 |
| `~QSqlRecord()`                                      | 析构函数，销毁 `QSqlRecord` 对象并释放资源。                |
| `append(const QSqlField &field)`                     | 向 `QSqlRecord` 中添加一个 `QSqlField` 字段。               |
| `clear()`                                            | 清空记录中的所有字段，保持 `QSqlRecord` 对象的空状态。      |
| `clearValues()`                                      | 清空所有字段的值，保留字段的结构和名称。                    |
| `contains(QAnyStringView name)`                      | 检查记录中是否包含指定名称的字段。                          |
| `count()`                                            | 返回记录中字段的数量。                                      |
| `field(int index)`                                   | 根据字段的索引返回对应的 `QSqlField` 对象。                 |
| `field(QAnyStringView name)`                         | 根据字段的名称返回对应的 `QSqlField` 对象。                 |
| `fieldName(int index)`                               | 根据字段的索引返回字段的名称。                              |
| `indexOf(QAnyStringView name)`                       | 返回字段名称在记录中的索引位置。如果字段不存在，返回 `-1`。 |
| `insert(int pos, const QSqlField &field)`            | 在指定位置插入一个字段。                                    |
| `isEmpty()`                                          | 检查记录是否为空，即没有字段。                              |
| `isGenerated(int index)`                             | 检查指定索引的字段是否为自动生成的。                        |
| `isGenerated(QAnyStringView name)`                   | 检查指定名称的字段是否为自动生成的。                        |
| `isNull(int index)`                                  | 检查指定索引的字段是否为空（值为 `NULL`）。                 |
| `isNull(QAnyStringView name)`                        | 检查指定名称的字段是否为空（值为 `NULL`）。                 |
| `keyValues(const QSqlRecord &keyFields)`             | 根据传入的 `keyFields` 返回记录中的键值对。                 |
| `remove(int pos)`                                    | 移除指定位置的字段。                                        |
| `replace(int pos, const QSqlField &field)`           | 用新的字段替换指定位置的字段。                              |
| `setGenerated(QAnyStringView name, bool generated)`  | 设置指定名称字段是否为自动生成的。                          |
| `setGenerated(int index, bool generated)`            | 设置指定索引字段是否为自动生成的。                          |
| `setNull(int index)`                                 | 设置指定索引字段的值为 `NULL`。                             |
| `setNull(QAnyStringView name)`                       | 设置指定名称字段的值为 `NULL`。                             |
| `setValue(int index, const QVariant &val)`           | 设置指定索引字段的值。                                      |
| `setValue(QAnyStringView name, const QVariant &val)` | 设置指定名称字段的值。                                      |
| `swap(QSqlRecord &other)`                            | 交换当前记录与 `other` 记录的内容。                         |
| `value(int index)`                                   | 返回指定索引字段的值。                                      |
| `value(QAnyStringView name)`                         | 返回指定名称字段的值。                                      |
| `operator!=(const QSqlRecord &other)`                | 判断当前记录与 `other` 是否不同。                           |
| `operator=(QSqlRecord &&other)`                      | 移动赋值操作符，将 `other` 的资源转移到当前记录。           |
| `operator=(const QSqlRecord &other)`                 | 拷贝赋值操作符，将 `other` 的内容拷贝到当前记录。           |
| `operator==(const QSqlRecord &other)`                | 判断当前记录与 `other` 是否相等。                           |

## QSqlField

​	QSqlField 表示数据库表或视图中单个列的特征，例如数据类型和列名。字段还包含数据库列的值，可以查看或更改该值。字段数据值存储为 QVariants。不允许使用不兼容的类型。例如：

```
QSqlField field("age", QMetaType::fromType<int>());
field.setValue(QPixmap()); // 错误
```

但是，字段将尽可能尝试将某些数据类型转换为字段数据类型：

```
QSqlField field("age", QMetaType::fromType<int>());
field.setValue(QString("123")); // 将 QString 转换为 int
```

​	QSqlField 对象很少在应用程序代码中明确创建。它们通常通过已包含字段列表的 QSqlRecords 间接访问。例如：

```
QSqlQuery query;
...
QSqlRecord record = query.record();
QSqlField field = record.field("country");
```

​	QSqlField 对象可以提供一些关于字段的元数据，例如，其 name()、variant type()、length()、precision()、defaultValue()、typeID() 以及其 requiredStatus()、isGenerated() 和 isReadOnly()。可以检查字段的数据以查看其是否为 isNull()，并检索其 value()。编辑时，可以使用 setValue() 设置数据或使用 clear() 将其设置为 NULL。

### API

#### **构造函数与析构函数**

| **函数名**                                                   | **描述**                                        |
| ------------------------------------------------------------ | ----------------------------------------------- |
| `QSqlField(const QString &fieldName = QString(), QMetaType type = QMetaType(), const QString &table = QString())` | 构造函数，初始化字段名、数据类型和表名。        |
| `QSqlField(const QSqlField &other)`                          | 复制构造函数，复制一个已有的 `QSqlField` 对象。 |
| `~QSqlField()`                                               | 析构函数，清理 `QSqlField` 对象的资源。         |

#### **成员函数**

| **函数名**                                                   | **描述**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `void clear()`                                               | 清空 `QSqlField` 对象的内容，恢复其到初始状态。              |
| `QVariant defaultValue() const`                              | 获取字段的默认值。                                           |
| `bool isAutoValue() const`                                   | 判断该字段是否是自动生成的（如自增长字段）。                 |
| `bool isGenerated() const`                                   | 判断该字段是否是生成的（如计算字段）。                       |
| `bool isNull() const`                                        | 判断该字段是否为 NULL。                                      |
| `bool isReadOnly() const`                                    | 判断该字段是否是只读的。                                     |
| `bool isValid() const`                                       | 判断该字段是否有效。                                         |
| `int length() const`                                         | 获取字段的长度。                                             |
| `QMetaType metaType() const`                                 | 获取字段的元数据类型。                                       |
| `QString name() const`                                       | 获取字段的名称。                                             |
| `int precision() const`                                      | 获取字段的小数精度（仅适用于浮动点数类型）。                 |
| `QSqlField::RequiredStatus requiredStatus() const`           | 获取字段是否是必填的状态。                                   |
| `void setAutoValue(bool autoVal)`                            | 设置字段是否为自动生成字段。                                 |
| `void setDefaultValue(const QVariant &value)`                | 设置字段的默认值。                                           |
| `void setGenerated(bool gen)`                                | 设置字段是否为生成的字段。                                   |
| `void setLength(int fieldLength)`                            | 设置字段的长度。                                             |
| `void setMetaType(QMetaType type)`                           | 设置字段的元数据类型。                                       |
| `void setName(const QString &name)`                          | 设置字段的名称。                                             |
| `void setPrecision(int precision)`                           | 设置字段的小数精度。                                         |
| `void setReadOnly(bool readOnly)`                            | 设置字段是否为只读。                                         |
| `void setRequired(bool required)`                            | 设置字段是否为必填字段。                                     |
| `void setRequiredStatus(QSqlField::RequiredStatus required)` | 设置字段的必填状态。                                         |
| `void setTableName(const QString &tableName)`                | 设置字段所属的表名。                                         |
| `void setValue(const QVariant &value)`                       | 设置字段的值。                                               |
| `void swap(QSqlField &other)`                                | 交换当前字段与另一个字段的内容。仅在 Qt 6.6 或更高版本中可用。 |
| `QString tableName() const`                                  | 获取字段所属的表名。                                         |
| `QVariant value() const`                                     | 获取字段的值。                                               |

#### **操作符**

| **操作符**                                      | **描述**                                                |
| ----------------------------------------------- | ------------------------------------------------------- |
| `bool operator!=(const QSqlField &other) const` | 判断当前字段与另一个字段是否不相等。                    |
| `QSqlField & operator=(const QSqlField &other)` | 赋值操作符，赋值一个 `QSqlField` 对象的内容到当前对象。 |
| `bool operator==(const QSqlField &other) const` | 判断当前字段与另一个字段是否相等。                      |



## QSqlIndex 

​	索引是指数据库中的单个表或视图。有关组成索引的字段的信息可用于生成 SQL 语句。

| **方法**                                                     | **说明**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QSqlIndex(const QString &cursorname = QString(), const QString &name = QString())` | 构造函数，创建一个 `QSqlIndex` 对象，接受可选的游标名和索引名称。 |
| `QSqlIndex(const QSqlIndex &other)`                          | 拷贝构造函数，创建一个与 `other` 相同的 `QSqlIndex` 对象。   |
| `QSqlIndex(QSqlIndex &&other)`                               | 移动构造函数，将 `other` 对象的所有资源转移到当前对象。      |
| `~QSqlIndex()`                                               | 析构函数，销毁 `QSqlIndex` 对象并释放资源。                  |
| `append(const QSqlField &field)`                             | 向索引中添加一个字段。                                       |
| `append(const QSqlField &field, bool desc)`                  | 向索引中添加一个字段并指定该字段是否降序排列。               |
| `cursorName()`                                               | 返回索引的游标名称。                                         |
| `isDescending(int i)`                                        | 判断索引中指定位置的字段是否按降序排列。                     |
| `name()`                                                     | 返回索引的名称。                                             |
| `setCursorName(const QString &cursorName)`                   | 设置索引的游标名称。                                         |
| `setDescending(int i, bool desc)`                            | 设置索引中指定位置的字段是否按降序排列。                     |
| `setName(const QString &name)`                               | 设置索引的名称。                                             |
| `operator=(QSqlIndex &&other)`                               | 移动赋值操作符，将 `other` 的资源转移到当前索引对象。        |
| `operator=(const QSqlIndex &other)`                          | 拷贝赋值操作符，将 `other` 索引的内容拷贝到当前索引对象。    |

## QSqlRecord

​	QSqlRecord 类封装了数据库记录（通常是数据库中表或视图中的一行）的功能和特征。QSqlRecord 支持添加和删除字段以及设置和检索字段值。

​	可以使用 setValue() 按名称或位置设置记录字段的值；如果要将字段设置为空，请使用 setNull()。要按名称查找字段的位置，请使用 indexOf()；要查找特定位置的字段名称，请使用 fieldName()。使用 field() 检索给定字段的 QSqlField 对象。使用 contains() 查看记录是否包含特定字段名称。

​	生成要在数据库上执行的查询时，只有 isGenerated() 为真的字段才会包含在生成的 SQL 中。

​	可以使用 append() 或 insert() 添加记录的字段，使用 replace() 替换记录的字段，以及使用 remove() 删除记录的字段。可以使用 clear() 删除所有字段。字段数由 count() 给出；可以使用 clearValues() 清除所有值（为空）。

### API

| **方法**                                             | **说明**                                                     |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| `QSqlRecord()`                                       | 默认构造函数，创建一个空的 `QSqlRecord` 对象。               |
| `QSqlRecord(const QSqlRecord &other)`                | 拷贝构造函数，创建一个与 `other` 相同的 `QSqlRecord` 对象。  |
| `QSqlRecord(QSqlRecord &&other)`                     | 移动构造函数，将 `other` 对象的资源转移到当前对象。          |
| `~QSqlRecord()`                                      | 析构函数，销毁 `QSqlRecord` 对象并释放资源。                 |
| `append(const QSqlField &field)`                     | 向记录中追加一个字段。                                       |
| `clear()`                                            | 清空记录中的所有字段。                                       |
| `clearValues()`                                      | 清空记录中所有字段的值。                                     |
| `contains(QAnyStringView name) const`                | 判断记录中是否包含指定名称的字段。                           |
| `count() const`                                      | 返回记录中字段的数量。                                       |
| `field(int index) const`                             | 返回指定索引位置的字段。                                     |
| `field(QAnyStringView name) const`                   | 返回指定名称的字段。                                         |
| `fieldName(int index) const`                         | 返回指定索引位置字段的名称。                                 |
| `indexOf(QAnyStringView name) const`                 | 返回指定名称字段的索引位置。                                 |
| `insert(int pos, const QSqlField &field)`            | 在指定位置插入一个字段。                                     |
| `isEmpty() const`                                    | 判断记录是否为空（是否没有字段）。                           |
| `isGenerated(int index) const`                       | 判断指定位置的字段是否为自动生成的字段（如数据库自动填充的字段）。 |
| `isGenerated(QAnyStringView name) const`             | 判断指定名称的字段是否为自动生成的字段。                     |
| `isNull(int index) const`                            | 判断指定位置的字段值是否为 `NULL`。                          |
| `isNull(QAnyStringView name) const`                  | 判断指定名称的字段值是否为 `NULL`。                          |
| `keyValues(const QSqlRecord &keyFields) const`       | 根据指定的关键字段记录，返回与当前记录匹配的键值。           |
| `remove(int pos)`                                    | 删除指定位置的字段。                                         |
| `replace(int pos, const QSqlField &field)`           | 替换指定位置的字段为新的字段。                               |
| `setGenerated(QAnyStringView name, bool generated)`  | 设置指定名称的字段是否为自动生成字段。                       |
| `setGenerated(int index, bool generated)`            | 设置指定位置的字段是否为自动生成字段。                       |
| `setNull(int index)`                                 | 将指定位置的字段设置为 `NULL`。                              |
| `setNull(QAnyStringView name)`                       | 将指定名称的字段设置为 `NULL`。                              |
| `setValue(int index, const QVariant &val)`           | 设置指定位置的字段的值。                                     |
| `setValue(QAnyStringView name, const QVariant &val)` | 设置指定名称的字段的值。                                     |
| `swap(QSqlRecord &other)`                            | 交换当前记录与 `other` 记录中的字段数据。                    |
| `value(int index) const`                             | 获取指定位置字段的值。                                       |
| `value(QAnyStringView name) const`                   | 获取指定名称字段的值。                                       |
| `operator!=(const QSqlRecord &other) const`          | 判断当前记录与 `other` 记录是否不相等。                      |
| `operator=(QSqlRecord &&other)`                      | 移动赋值操作符，将 `other` 记录的字段数据转移到当前记录。    |
| `operator=(const QSqlRecord &other)`                 | 拷贝赋值操作符，将 `other` 记录的字段数据拷贝到当前记录。    |
| `operator==(const QSqlRecord &other) const`          | 判断当前记录与 `other` 记录是否相等。                        |

# 用户层

## QSqlQueryModel

​	QSqlQueryModel 是一个用于执行 SQL 语句和遍历结果集的高级接口。它建立在较低级别的 QSqlQuery 之上，可用于向 QTableView 等视图类提供数据。例如：

```
QSqlQueryModel *model = new QSqlQueryModel;
model->setQuery("SELECT name, salary FROM employee");
model->setHeaderData(0, Qt::Horizontal, tr("Name"));
model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
QTableView *view = new QTableView;
view->setModel(model);
view->show();
```

我们设置模型的查询，然后设置视图标题中显示的标签。

QSqlQueryModel 还可用于以编程方式访问数据库，而无需将其绑定到视图：

```
QSqlQueryModel model;
model.setQuery("SELECT name, salary FROM employee");
int salary = model.record(4).value("salary").toInt();
```

​	上面的代码片段从 SELECT 查询结果集中的第 4 条记录中提取 salary 字段。由于 salary 是第 2 列（或列索引 1），我们可以将最后一行重写如下：

```
int salary = model.data(model.index(4, 1)).toInt();
```

默	认情况下，该模型是只读的。要使其可读写，您必须将其子类化并重新实现 setData() 和 flags()。另一个选项是使用 QSqlTableModel，它基于单个数据库表提供读写模型。

### API

| **方法**                                                     | **说明**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QSqlQueryModel(QObject *parent = nullptr)`                  | 构造函数，创建一个 `QSqlQueryModel` 对象，接受一个可选的父对象。 |
| `~QSqlQueryModel()`                                          | 析构函数，销毁 `QSqlQueryModel` 对象并释放资源。             |
| `clear()`                                                    | 清空模型中的所有数据。                                       |
| `lastError() const`                                          | 返回执行查询时出现的最后一个错误信息。                       |
| `query() const`                                              | 返回与当前模型关联的 `QSqlQuery` 对象。                      |
| `record(int row) const`                                      | 返回指定行的元数据记录（`QSqlRecord`）。                     |
| `record() const`                                             | 返回当前模型中当前行的元数据记录（`QSqlRecord`）。           |
| `setQuery(QSqlQuery &&query)`                                | 设置新的 `QSqlQuery` 对象，并将其绑定到模型。                |
| `setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase())` | 设置新的查询字符串和数据库连接。                             |
| **重载公共函数**                                             |                                                              |
| `canFetchMore(const QModelIndex &parent = QModelIndex()) const` | 判断是否可以加载更多数据。                                   |
| `columnCount(const QModelIndex &index = QModelIndex()) const` | 返回模型中列的数量。                                         |
| `data(const QModelIndex &item, int role = Qt::DisplayRole) const` | 返回指定单元格的数据。                                       |
| `fetchMore(const QModelIndex &parent = QModelIndex())`       | 加载更多的数据项。                                           |
| `headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const` | 返回表头的数据（如列名、行名）。                             |
| `insertColumns(int column, int count, const QModelIndex &parent = QModelIndex())` | 在指定位置插入列。                                           |
| `removeColumns(int column, int count, const QModelIndex &parent = QModelIndex())` | 移除指定位置的列。                                           |
| `roleNames() const`                                          | 返回所有角色名称的映射关系。                                 |
| `rowCount(const QModelIndex &parent = QModelIndex()) const`  | 返回模型中行的数量。                                         |
| `setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole)` | 设置表头的数据显示。                                         |
| **保护函数**                                                 |                                                              |
| `indexInQuery(const QModelIndex &item) const`                | 获取与指定索引位置对应的查询项（主要用于模型与查询的映射）。 |
| `queryChange()`                                              | 当查询更改时，处理相关的更新。                               |
| `setLastError(const QSqlError &error)`                       | 设置查询的最后错误信息。                                     |

## QSqlTableModel

​	QSqlTableModel 是一个高级接口，用于从单个表中读取和写入数据库记录。它建立在较低级别的 QSqlQuery 之上，可用于向视图类（如 QTableView）提供数据。例如：

```
QSqlTableModel *model = new QSqlTableModel;
model->setTable("employee");
model->setEditStrategy(QSqlTableModel::OnManualSubmit);
model->select();
model->setHeaderData(0, Qt::Horizontal, tr("Name"));
model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

QTableView *view = new QTableView;
view->setModel(model);
view->hideColumn(0); // 不显示 ID
view->show();
```

​	我们设置 SQL 表的名称和编辑策略，然后设置视图标题中显示的标签。编辑策略决定了用户在视图中所做的更改何时实际应用于数据库。可能的值是 OnFieldChange、OnRowChange 和 OnManualSubmit。

QSqlTableModel 还可用于以编程方式访问数据库，而无需将其绑定到视图：

```
QSqlTableModel model;
model.setTable("employee");
model.select();
int salary = model.record(4).value("salary").toInt();
```

​	上面的代码片段从查询 SELECT * from employee 的结果集中的记录 4 中提取薪水字段。可以使用 setFilter() 设置过滤器，或使用 setSort() 修改排序顺序。最后，您必须调用 select() 以用数据填充模型。

### API

| **类型**       | **说明**                                                     |
| -------------- | ------------------------------------------------------------ |
| `EditStrategy` | 枚举类型，定义了数据编辑的策略。可能的值：`OnFieldChange`（字段改变时提交）、`OnRowChange`（行改变时提交）、`OnManualSubmit`（手动提交）。 |

| **方法**                                                     | **说明**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QSqlTableModel(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase())` | 构造函数，创建一个与指定数据库连接的 `QSqlTableModel` 对象。 |
| `~QSqlTableModel()`                                          | 析构函数，销毁 `QSqlTableModel` 对象并释放资源。             |
| `database() const`                                           | 返回与模型关联的 `QSqlDatabase` 对象。                       |
| `editStrategy() const`                                       | 返回当前的数据编辑策略，决定何时提交数据（如字段改变时、行改变时或手动提交）。 |
| `fieldIndex(const QString &fieldName) const`                 | 返回指定字段名对应的字段索引。                               |
| `filter() const`                                             | 返回当前的过滤条件字符串。                                   |
| `insertRecord(int row, const QSqlRecord &record)`            | 在指定行插入一条记录。                                       |
| `isDirty(const QModelIndex &index) const`                    | 检查指定单元格是否被修改。                                   |
| `isDirty() const`                                            | 检查模型中是否有任何未提交的修改。                           |
| `primaryKey() const`                                         | 返回表格的主键（`QSqlIndex`）。                              |
| `record() const`                                             | 返回当前行的 `QSqlRecord` 记录。                             |
| `record(int row) const`                                      | 返回指定行的 `QSqlRecord` 记录。                             |
| `revertRow(int row)`                                         | 撤销对指定行的修改。                                         |
| `setEditStrategy(QSqlTableModel::EditStrategy strategy)`     | 设置数据编辑策略。                                           |
| `setFilter(const QString &filter)`                           | 设置过滤条件，筛选显示的数据。                               |
| `setRecord(int row, const QSqlRecord &values)`               | 设置指定行的记录值。                                         |
| `setSort(int column, Qt::SortOrder order)`                   | 设置排序规则，按指定列进行排序。                             |
| `setTable(const QString &tableName)`                         | 设置模型所操作的数据库表格。                                 |
| `tableName() const`                                          | 返回当前模型操作的表格名称。                                 |

| **方法**                                                     | **说明**                   |
| ------------------------------------------------------------ | -------------------------- |
| `clear()`                                                    | 清空模型中的所有数据。     |
| `clearItemData(const QModelIndex &index)`                    | 清空指定单元格的数据。     |
| `data(const QModelIndex &index, int role = Qt::DisplayRole) const` | 返回指定索引单元格的数据。 |
| `flags(const QModelIndex &index) const`                      | 返回指定索引单元格的标志。 |
| `headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const` | 返回指定列或行的表头数据。 |
| `insertRows(int row, int count, const QModelIndex &parent = QModelIndex())` | 在指定位置插入多行。       |
| `removeColumns(int column, int count, const QModelIndex &parent = QModelIndex())` | 移除指定位置的多列。       |
| `removeRows(int row, int count, const QModelIndex &parent = QModelIndex())` | 移除指定位置的多行。       |
| `rowCount(const QModelIndex &parent = QModelIndex()) const`  | 返回指定父索引下的行数。   |
| `setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)` | 设置指定单元格的数据。     |
| `sort(int column, Qt::SortOrder order)`                      | 对指定列的数据进行排序。   |

| **方法**             | **说明**                           |
| -------------------- | ---------------------------------- |
| `revert()`           | 撤销当前所有的修改。               |
| `revertAll()`        | 撤销所有行的修改。                 |
| `select()`           | 查询并填充模型中的数据。           |
| `selectRow(int row)` | 查询并填充指定行的数据。           |
| `submit()`           | 提交当前数据（如果在编辑状态中）。 |
| `submitAll()`        | 提交所有更改的数据。               |

| **信号**                                    | **说明**                         |
| ------------------------------------------- | -------------------------------- |
| `beforeDelete(int row)`                     | 在删除某一行之前发出的信号。     |
| `beforeInsert(QSqlRecord &record)`          | 在插入新记录之前发出的信号。     |
| `beforeUpdate(int row, QSqlRecord &record)` | 在更新某一行记录之前发出的信号。 |
| `primeInsert(int row, QSqlRecord &record)`  | 在插入记录时发出的信号。         |

| **方法**                                              | **说明**                   |
| ----------------------------------------------------- | -------------------------- |
| `deleteRowFromTable(int row)`                         | 从表格中删除指定的行。     |
| `insertRowIntoTable(const QSqlRecord &values)`        | 向表格中插入一行数据。     |
| `orderByClause() const`                               | 返回数据库查询的排序子句。 |
| `primaryValues(int row) const`                        | 返回指定行的主键值。       |
| `selectStatement() const`                             | 返回生成的 SQL 查询语句。  |
| `setPrimaryKey(const QSqlIndex &key)`                 | 设置模型的主键。           |
| `updateRowInTable(int row, const QSqlRecord &values)` | 更新表格中指定行的数据。   |

## QSqlRelationalTableModel

QSqlRelationalTableModel 的作用类似于 QSqlTableModel，但允许将列设置为其他数据库表的外键。以下代码片段显示了如何设置 QSqlRelationalTableModel：

```
model->setTable("employee");

model->setRelation(2, QSqlRelation("city", "id", "name"));
model->setRelation(3, QSqlRelation("country", "id", "name"));
```

​	setRelation() 函数调用在两个表之间建立关系。第一次调用指定表 employee 中的第 2 列是与表 city 的字段 id 映射的外键，并且视图应向用户显示城市的名称字段。第二次调用对第 3 列执行类似操作。

​	如果您使用读写 QSqlRelationalTableModel，您可能希望在视图上使用 QSqlRelationalDelegate。与默认委托不同，QSqlRelationalDelegate 为作为其他表的外键的字段提供了一个组合框。要使用该类，只需在视图上使用 QSqlRelationalDelegate 实例调用 QAbstractItemView::setItemDelegate()：

```
std::unique_ptr<QTableView> view{new QTableView};
view->setModel(model);
view->setItemDelegate(new QSqlRelationalDelegate(view.get()));
```

关系表模型示例说明了如何结合使用 QSqlRelationalTableModel 和 QSqlRelationalDelegate 来为表提供外键支持。

- 表必须声明主键。

- 表的主键不得包含与另一个表的关系。

- 如果关系表包含引用所引用表中不存在的行的键，则包含无效键的行将不会通过模型公开。用户或数据库负责保持引用完整性。

​	如果关系的显示列名也用作关系表中的列名，或者如果它在多个关系中用作显示列名，则它将被别名化。别名是关系的表名、显示列名和由下划线连接的唯一 ID（例如 tablename_columnname_id）。QSqlRecord::fieldName() 将返回别名列名。检测到重复时，所有重复的显示列名都会被别名化，但主表中的列名不会使用别名。别名化不会影响 QSqlRelation，因此 QSqlRelation::displayColumn() 将返回原始显示列名。

​	引用表名已使用别名。别名是单词“relTblAl”和相关列索引，由下划线连接（例如 relTblAl_2）。别名可用于过滤表（例如，setFilter("relTblAl_2='Oslo' OR relTblAl_3='USA'"))。使用 setData() 时，角色应始终为 Qt::EditRole，使用 data() 时，角色应始终为 Qt::DisplayRole。

### API

| **类型**   | **说明**                                                     |
| ---------- | ------------------------------------------------------------ |
| `JoinMode` | 枚举类型，定义了表格连接的方式。可能的值：`InnerJoin`（内连接）和 `LeftJoin`（左连接）。 |

| **方法**                                                     | **说明**                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `QSqlRelationalTableModel(QObject *parent = nullptr, const QSqlDatabase &db = QSqlDatabase())` | 构造函数，创建一个与指定数据库连接的 `QSqlRelationalTableModel` 对象。 |
| `~QSqlRelationalTableModel()`                                | 析构函数，销毁 `QSqlRelationalTableModel` 对象并释放资源。   |
| `relation(int column) const`                                 | 返回指定列的关系（`QSqlRelation`），表示列与其他表之间的关系。 |
| `relationModel(int column) const`                            | 返回与指定列相关的模型（`QSqlTableModel`）。                 |
| `setJoinMode(QSqlRelationalTableModel::JoinMode joinMode)`   | 设置连接模式，可以选择内连接或左连接。                       |
| `setRelation(int column, const QSqlRelation &relation)`      | 设置指定列的关系，定义该列与其他表的关联方式。               |

| **方法**                                                     | **说明**                     |
| ------------------------------------------------------------ | ---------------------------- |
| `clear()`                                                    | 清空模型中的所有数据。       |
| `data(const QModelIndex &index, int role = Qt::DisplayRole) const` | 返回指定索引单元格的数据。   |
| `removeColumns(int column, int count, const QModelIndex &parent = QModelIndex())` | 移除指定位置的多列。         |
| `select()`                                                   | 查询并填充模型中的数据。     |
| `setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)` | 设置指定单元格的数据。       |
| `setTable(const QString &table)`                             | 设置模型所操作的数据库表格。 |

| **方法**             | **说明**             |
| -------------------- | -------------------- |
| `revertRow(int row)` | 撤销对指定行的修改。 |

| **方法**                                              | **说明**                   |
| ----------------------------------------------------- | -------------------------- |
| `insertRowIntoTable(const QSqlRecord &values)`        | 向表格中插入一行数据。     |
| `orderByClause() const`                               | 返回数据库查询的排序子句。 |
| `selectStatement() const`                             | 返回生成的 SQL 查询语句。  |
| `updateRowInTable(int row, const QSqlRecord &values)` | 更新表格中指定行的数据。   |