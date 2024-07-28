# QString类详解 附录A

# QString Class

The QString class provides a Unicode character string. [More...](https://doc.qt.io/qt-6/qstring.html#details)

| Header: | #include < QString>                                          |
| ------- | ------------------------------------------------------------ |
| CMake:  | find_package(Qt6 REQUIRED COMPONENTS Core) target_link_libraries(mytarget PRIVATE Qt6::Core) |
| qmake:  | QT += core                                                   |

- [List of all members, including inherited members](https://doc.qt.io/qt-6/qstring-members.html)
- [Deprecated members](https://doc.qt.io/qt-6/qstring-obsolete.html)
- QString is part of [Implicitly Shared Classes](https://doc.qt.io/qt-6/shared.html) and [Classes for String Data](https://doc.qt.io/qt-6/string-processing.html).

**Note:** All functions in this class are [reentrant](https://doc.qt.io/qt-6/threads-reentrancy.html).

## Public Types

|       | **[ConstIterator](https://doc.qt.io/qt-6/qstring.html#ConstIterator-typedef)** |
| ----- | ------------------------------------------------------------ |
|       | **[Iterator](https://doc.qt.io/qt-6/qstring.html#Iterator-typedef)** |
| enum  | **[NormalizationForm](https://doc.qt.io/qt-6/qstring.html#NormalizationForm-enum)** { NormalizationForm_D, NormalizationForm_C, NormalizationForm_KD, NormalizationForm_KC } |
| enum  | **[SectionFlag](https://doc.qt.io/qt-6/qstring.html#SectionFlag-enum)** { SectionDefault, SectionSkipEmpty, SectionIncludeLeadingSep, SectionIncludeTrailingSep, SectionCaseInsensitiveSeps } |
| flags | **[SectionFlags](https://doc.qt.io/qt-6/qstring.html#SectionFlag-enum)** |
|       | **[const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef)** |
|       | **[const_pointer](https://doc.qt.io/qt-6/qstring.html#const_pointer-typedef)** |
|       | **[const_reference](https://doc.qt.io/qt-6/qstring.html#const_reference-typedef)** |
|       | **[const_reverse_iterator](https://doc.qt.io/qt-6/qstring.html#const_reverse_iterator-typedef)** |
|       | **[difference_type](https://doc.qt.io/qt-6/qstring.html#difference_type-typedef)** |
|       | **[iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx)** |
|       | **[pointer](https://doc.qt.io/qt-6/qstring.html#pointer-typedef)** |
|       | **[reference](https://doc.qt.io/qt-6/qstring.html#reference-typedef)** |
|       | **[reverse_iterator](https://doc.qt.io/qt-6/qstring.html#reverse_iterator-typedef)** |
|       | **[size_type](https://doc.qt.io/qt-6/qstring.html#size_type-typedef)** |
|       | **[value_type](https://doc.qt.io/qt-6/qstring.html#value_type-typedef)** |

## Public Functions

|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString)**() |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-1)**(const QChar **unicode*, qsizetype *size* = -1) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-2)**(QChar *ch*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-3)**(qsizetype *size*, QChar *ch*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-4)**(QLatin1StringView *str*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-5)**(const char8_t **str*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-8)**(const char **str*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-9)**(const QByteArray &*ba*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-6)**(const QString &*other*) |
|                                                              | **[QString](https://doc.qt.io/qt-6/qstring.html#QString-7)**(QString &&*other*) |
|                                                              | **[~QString](https://doc.qt.io/qt-6/qstring.html#dtor.QString)**() |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append)**(const QString &*str*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-1)**(QChar *ch*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-2)**(const QChar **str*, qsizetype *len*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-3)**(QStringView *v*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-4)**(QLatin1StringView *str*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-5)**(QUtf8StringView *str*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-6)**(const char **str*) |
| QString &                                                    | **[append](https://doc.qt.io/qt-6/qstring.html#append-7)**(const QByteArray &*ba*) |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg)**(const QString &*a*, int *fieldWidth* = 0, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-1)**(qlonglong *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-2)**(qulonglong *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-3)**(long *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-4)**(ulong *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-5)**(int *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-6)**(uint *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-7)**(short *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-8)**(ushort *a*, int *fieldWidth* = 0, int *base* = 10, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-9)**(double *a*, int *fieldWidth* = 0, char *format* = 'g', int *precision* = -1, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-10)**(char *a*, int *fieldWidth* = 0, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-11)**(QChar *a*, int *fieldWidth* = 0, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-12)**(QStringView *a*, int *fieldWidth* = 0, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-13)**(QLatin1StringView *a*, int *fieldWidth* = 0, QChar *fillChar* = u' ') const |
| QString                                                      | **[arg](https://doc.qt.io/qt-6/qstring.html#arg-14)**(Args &&... *args*) const |
| QString &                                                    | **[assign](https://doc.qt.io/qt-6/qstring.html#assign)**(QAnyStringView *v*) |
| QString &                                                    | **[assign](https://doc.qt.io/qt-6/qstring.html#assign-1)**(qsizetype *n*, QChar *c*) |
| QString &                                                    | **[assign](https://doc.qt.io/qt-6/qstring.html#assign-2)**(InputIterator *first*, InputIterator *last*) |
| const QChar                                                  | **[at](https://doc.qt.io/qt-6/qstring.html#at)**(qsizetype *position*) const |
| QChar                                                        | **[back](https://doc.qt.io/qt-6/qstring.html#back)**() const |
| QChar &                                                      | **[back](https://doc.qt.io/qt-6/qstring.html#back-1)**()     |
| QString::iterator                                            | **[begin](https://doc.qt.io/qt-6/qstring.html#begin)**()     |
| QString::const_iterator                                      | **[begin](https://doc.qt.io/qt-6/qstring.html#begin-1)**() const |
| qsizetype                                                    | **[capacity](https://doc.qt.io/qt-6/qstring.html#capacity)**() const |
| QString::const_iterator                                      | **[cbegin](https://doc.qt.io/qt-6/qstring.html#cbegin)**() const |
| QString::const_iterator                                      | **[cend](https://doc.qt.io/qt-6/qstring.html#cend)**() const |
| void                                                         | **[chop](https://doc.qt.io/qt-6/qstring.html#chop)**(qsizetype *n*) |
| QString                                                      | **[chopped](https://doc.qt.io/qt-6/qstring.html#chopped)**(qsizetype *len*) const |
| void                                                         | **[clear](https://doc.qt.io/qt-6/qstring.html#clear)**()     |
| int                                                          | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-1)**(const QString &*other*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| int                                                          | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-2)**(QLatin1StringView *other*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| int                                                          | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-3)**(QStringView *s*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| int                                                          | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-4)**(QChar *ch*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| QString::const_iterator                                      | **[constBegin](https://doc.qt.io/qt-6/qstring.html#constBegin)**() const |
| const QChar *                                                | **[constData](https://doc.qt.io/qt-6/qstring.html#constData)**() const |
| QString::const_iterator                                      | **[constEnd](https://doc.qt.io/qt-6/qstring.html#constEnd)**() const |
| bool                                                         | **[contains](https://doc.qt.io/qt-6/qstring.html#contains)**(const QString &*str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[contains](https://doc.qt.io/qt-6/qstring.html#contains-1)**(QChar *ch*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[contains](https://doc.qt.io/qt-6/qstring.html#contains-2)**(QLatin1StringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[contains](https://doc.qt.io/qt-6/qstring.html#contains-3)**(QStringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[contains](https://doc.qt.io/qt-6/qstring.html#contains-4)**(const QRegularExpression &*re*, QRegularExpressionMatch **rmatch* = nullptr) const |
| qsizetype                                                    | **[count](https://doc.qt.io/qt-6/qstring.html#count)**(const QString &*str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[count](https://doc.qt.io/qt-6/qstring.html#count-2)**(QChar *ch*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[count](https://doc.qt.io/qt-6/qstring.html#count-3)**(QStringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[count](https://doc.qt.io/qt-6/qstring.html#count-4)**(const QRegularExpression &*re*) const |
| QString::const_reverse_iterator                              | **[crbegin](https://doc.qt.io/qt-6/qstring.html#crbegin)**() const |
| QString::const_reverse_iterator                              | **[crend](https://doc.qt.io/qt-6/qstring.html#crend)**() const |
| QChar *                                                      | **[data](https://doc.qt.io/qt-6/qstring.html#data)**()       |
| const QChar *                                                | **[data](https://doc.qt.io/qt-6/qstring.html#data-1)**() const |
| QString::iterator                                            | **[end](https://doc.qt.io/qt-6/qstring.html#end)**()         |
| QString::const_iterator                                      | **[end](https://doc.qt.io/qt-6/qstring.html#end-1)**() const |
| bool                                                         | **[endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)**(const QString &*s*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith-1)**(QStringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith-2)**(QLatin1StringView *s*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith-3)**(QChar *c*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| QString::iterator                                            | **[erase](https://doc.qt.io/qt-6/qstring.html#erase)**(QString::const_iterator *first*, QString::const_iterator *last*) |
| QString::iterator                                            | **[erase](https://doc.qt.io/qt-6/qstring.html#erase-1)**(QString::const_iterator *it*) |
| QString &                                                    | **[fill](https://doc.qt.io/qt-6/qstring.html#fill)**(QChar *ch*, qsizetype *size* = -1) |
| QString                                                      | **[first](https://doc.qt.io/qt-6/qstring.html#first)**(qsizetype *n*) const |
| QChar                                                        | **[front](https://doc.qt.io/qt-6/qstring.html#front)**() const |
| QChar &                                                      | **[front](https://doc.qt.io/qt-6/qstring.html#front-1)**()   |
| qsizetype                                                    | **[indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)**(QLatin1StringView *str*, qsizetype *from* = 0, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf-1)**(QChar *ch*, qsizetype *from* = 0, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf-2)**(const QString &*str*, qsizetype *from* = 0, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf-3)**(QStringView *str*, qsizetype *from* = 0, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf-4)**(const QRegularExpression &*re*, qsizetype *from* = 0, QRegularExpressionMatch **rmatch* = nullptr) const |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert)**(qsizetype *position*, const QString &*str*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-1)**(qsizetype *position*, QChar *ch*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-2)**(qsizetype *position*, const QChar **unicode*, qsizetype *size*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-3)**(qsizetype *position*, QStringView *str*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-4)**(qsizetype *position*, QLatin1StringView *str*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-5)**(qsizetype *position*, QUtf8StringView *str*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-6)**(qsizetype *position*, const char **str*) |
| QString &                                                    | **[insert](https://doc.qt.io/qt-6/qstring.html#insert-7)**(qsizetype *position*, const QByteArray &*str*) |
| bool                                                         | **[isEmpty](https://doc.qt.io/qt-6/qstring.html#isEmpty)**() const |
| bool                                                         | **[isLower](https://doc.qt.io/qt-6/qstring.html#isLower)**() const |
| bool                                                         | **[isNull](https://doc.qt.io/qt-6/qstring.html#isNull)**() const |
| bool                                                         | **[isRightToLeft](https://doc.qt.io/qt-6/qstring.html#isRightToLeft)**() const |
| bool                                                         | **[isUpper](https://doc.qt.io/qt-6/qstring.html#isUpper)**() const |
| bool                                                         | **[isValidUtf16](https://doc.qt.io/qt-6/qstring.html#isValidUtf16)**() const |
| QString                                                      | **[last](https://doc.qt.io/qt-6/qstring.html#last)**(qsizetype *n*) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)**(const QString &*str*, qsizetype *from*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-1)**(QChar *c*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-2)**(QChar *ch*, qsizetype *from*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-3)**(QLatin1StringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-4)**(QLatin1StringView *str*, qsizetype *from*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-5)**(const QString &*str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-6)**(QStringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-7)**(QStringView *str*, qsizetype *from*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-8)**(const QRegularExpression &*re*, QRegularExpressionMatch **rmatch* = nullptr) const |
| qsizetype                                                    | **[lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf-9)**(const QRegularExpression &*re*, qsizetype *from*, QRegularExpressionMatch **rmatch* = nullptr) const |
| QString                                                      | **[left](https://doc.qt.io/qt-6/qstring.html#left)**(qsizetype *n*) const |
| QString                                                      | **[leftJustified](https://doc.qt.io/qt-6/qstring.html#leftJustified)**(qsizetype *width*, QChar *fill* = u' ', bool *truncate* = false) const |
| qsizetype                                                    | **[length](https://doc.qt.io/qt-6/qstring.html#length)**() const |
| int                                                          | **[localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare-1)**(const QString &*other*) const |
| int                                                          | **[localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare-2)**(QStringView *other*) const |
| QString                                                      | **[mid](https://doc.qt.io/qt-6/qstring.html#mid)**(qsizetype *position*, qsizetype *n* = -1) const |
| QString                                                      | **[normalized](https://doc.qt.io/qt-6/qstring.html#normalized)**(QString::NormalizationForm *mode*, QChar::UnicodeVersion *version* = QChar::Unicode_Unassigned) const |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend)**(const QString &*str*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-1)**(QChar *ch*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-2)**(const QChar **str*, qsizetype *len*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-3)**(QStringView *str*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-4)**(QLatin1StringView *str*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-5)**(QUtf8StringView *str*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-6)**(const char **str*) |
| QString &                                                    | **[prepend](https://doc.qt.io/qt-6/qstring.html#prepend-7)**(const QByteArray &*ba*) |
| void                                                         | **[push_back](https://doc.qt.io/qt-6/qstring.html#push_back)**(const QString &*other*) |
| void                                                         | **[push_back](https://doc.qt.io/qt-6/qstring.html#push_back-1)**(QChar *ch*) |
| void                                                         | **[push_front](https://doc.qt.io/qt-6/qstring.html#push_front)**(const QString &*other*) |
| void                                                         | **[push_front](https://doc.qt.io/qt-6/qstring.html#push_front-1)**(QChar *ch*) |
| QString::reverse_iterator                                    | **[rbegin](https://doc.qt.io/qt-6/qstring.html#rbegin)**()   |
| QString::const_reverse_iterator                              | **[rbegin](https://doc.qt.io/qt-6/qstring.html#rbegin-1)**() const |
| QString &                                                    | **[remove](https://doc.qt.io/qt-6/qstring.html#remove)**(qsizetype *position*, qsizetype *n*) |
| QString &                                                    | **[remove](https://doc.qt.io/qt-6/qstring.html#remove-1)**(QChar *ch*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[remove](https://doc.qt.io/qt-6/qstring.html#remove-2)**(QLatin1StringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[remove](https://doc.qt.io/qt-6/qstring.html#remove-3)**(const QString &*str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[remove](https://doc.qt.io/qt-6/qstring.html#remove-4)**(const QRegularExpression &*re*) |
| QString &                                                    | **[removeAt](https://doc.qt.io/qt-6/qstring.html#removeAt)**(qsizetype *pos*) |
| QString &                                                    | **[removeFirst](https://doc.qt.io/qt-6/qstring.html#removeFirst)**() |
| QString &                                                    | **[removeIf](https://doc.qt.io/qt-6/qstring.html#removeIf)**(Predicate *pred*) |
| QString &                                                    | **[removeLast](https://doc.qt.io/qt-6/qstring.html#removeLast)**() |
| QString::reverse_iterator                                    | **[rend](https://doc.qt.io/qt-6/qstring.html#rend)**()       |
| QString::const_reverse_iterator                              | **[rend](https://doc.qt.io/qt-6/qstring.html#rend-1)**() const |
| QString                                                      | **[repeated](https://doc.qt.io/qt-6/qstring.html#repeated)**(qsizetype *times*) const |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace)**(qsizetype *position*, qsizetype *n*, const QString &*after*) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-1)**(qsizetype *position*, qsizetype *n*, QChar *after*) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-2)**(qsizetype *position*, qsizetype *n*, const QChar **after*, qsizetype *alen*) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-3)**(QChar *before*, QChar *after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-4)**(const QChar **before*, qsizetype *blen*, const QChar **after*, qsizetype *alen*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-5)**(QLatin1StringView *before*, QLatin1StringView *after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-6)**(QLatin1StringView *before*, const QString &*after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-7)**(const QString &*before*, QLatin1StringView *after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-8)**(const QString &*before*, const QString &*after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-9)**(QChar *ch*, const QString &*after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-10)**(QChar *c*, QLatin1StringView *after*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString &                                                    | **[replace](https://doc.qt.io/qt-6/qstring.html#replace-11)**(const QRegularExpression &*re*, const QString &*after*) |
| void                                                         | **[reserve](https://doc.qt.io/qt-6/qstring.html#reserve)**(qsizetype *size*) |
| void                                                         | **[resize](https://doc.qt.io/qt-6/qstring.html#resize)**(qsizetype *size*) |
| void                                                         | **[resize](https://doc.qt.io/qt-6/qstring.html#resize-1)**(qsizetype *newSize*, QChar *fillChar*) |
| QString                                                      | **[right](https://doc.qt.io/qt-6/qstring.html#right)**(qsizetype *n*) const |
| QString                                                      | **[rightJustified](https://doc.qt.io/qt-6/qstring.html#rightJustified)**(qsizetype *width*, QChar *fill* = u' ', bool *truncate* = false) const |
| QString                                                      | **[section](https://doc.qt.io/qt-6/qstring.html#section)**(QChar *sep*, qsizetype *start*, qsizetype *end* = -1, QString::SectionFlags *flags* = SectionDefault) const |
| QString                                                      | **[section](https://doc.qt.io/qt-6/qstring.html#section-1)**(const QString &*sep*, qsizetype *start*, qsizetype *end* = -1, QString::SectionFlags *flags* = SectionDefault) const |
| QString                                                      | **[section](https://doc.qt.io/qt-6/qstring.html#section-2)**(const QRegularExpression &*re*, qsizetype *start*, qsizetype *end* = -1, QString::SectionFlags *flags* = SectionDefault) const |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum)**(int *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-1)**(short *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-2)**(ushort *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-3)**(uint *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-4)**(long *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-5)**(ulong *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-6)**(qlonglong *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-7)**(qulonglong *n*, int *base* = 10) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-8)**(float *n*, char *format* = 'g', int *precision* = 6) |
| QString &                                                    | **[setNum](https://doc.qt.io/qt-6/qstring.html#setNum-9)**(double *n*, char *format* = 'g', int *precision* = 6) |
| QString &                                                    | **[setRawData](https://doc.qt.io/qt-6/qstring.html#setRawData)**(const QChar **unicode*, qsizetype *size*) |
| QString &                                                    | **[setUnicode](https://doc.qt.io/qt-6/qstring.html#setUnicode)**(const QChar **unicode*, qsizetype *size*) |
| QString &                                                    | **[setUtf16](https://doc.qt.io/qt-6/qstring.html#setUtf16)**(const ushort **unicode*, qsizetype *size*) |
| void                                                         | **[shrink_to_fit](https://doc.qt.io/qt-6/qstring.html#shrink_to_fit)**() |
| QString                                                      | **[simplified](https://doc.qt.io/qt-6/qstring.html#simplified)**() const |
| qsizetype                                                    | **[size](https://doc.qt.io/qt-6/qstring.html#size)**() const |
| QString                                                      | **[sliced](https://doc.qt.io/qt-6/qstring.html#sliced)**(qsizetype *pos*, qsizetype *n*) const |
| QString                                                      | **[sliced](https://doc.qt.io/qt-6/qstring.html#sliced-1)**(qsizetype *pos*) const |
| QStringList                                                  | **[split](https://doc.qt.io/qt-6/qstring.html#split)**(const QString &*sep*, Qt::SplitBehavior *behavior* = Qt::KeepEmptyParts, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| QStringList                                                  | **[split](https://doc.qt.io/qt-6/qstring.html#split-1)**(QChar *sep*, Qt::SplitBehavior *behavior* = Qt::KeepEmptyParts, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| QStringList                                                  | **[split](https://doc.qt.io/qt-6/qstring.html#split-2)**(const QRegularExpression &*re*, Qt::SplitBehavior *behavior* = Qt::KeepEmptyParts) const |
| void                                                         | **[squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)**() |
| bool                                                         | **[startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith)**(const QString &*s*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith-1)**(QStringView *str*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith-2)**(QLatin1StringView *s*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| bool                                                         | **[startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith-3)**(QChar *c*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) const |
| void                                                         | **[swap](https://doc.qt.io/qt-6/qstring.html#swap)**(QString &*other*) |
| CFStringRef                                                  | **[toCFString](https://doc.qt.io/qt-6/qstring.html#toCFString)**() const |
| QString                                                      | **[toCaseFolded](https://doc.qt.io/qt-6/qstring.html#toCaseFolded)**() const |
| double                                                       | **[toDouble](https://doc.qt.io/qt-6/qstring.html#toDouble)**(bool **ok* = nullptr) const |
| emscripten::val                                              | **[toEcmaString](https://doc.qt.io/qt-6/qstring.html#toEcmaString)**() const |
| float                                                        | **[toFloat](https://doc.qt.io/qt-6/qstring.html#toFloat)**(bool **ok* = nullptr) const |
| QString                                                      | **[toHtmlEscaped](https://doc.qt.io/qt-6/qstring.html#toHtmlEscaped)**() const |
| int                                                          | **[toInt](https://doc.qt.io/qt-6/qstring.html#toInt)**(bool **ok* = nullptr, int *base* = 10) const |
| QByteArray                                                   | **[toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)**() const |
| QByteArray                                                   | **[toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)**() const |
| long                                                         | **[toLong](https://doc.qt.io/qt-6/qstring.html#toLong)**(bool **ok* = nullptr, int *base* = 10) const |
| qlonglong                                                    | **[toLongLong](https://doc.qt.io/qt-6/qstring.html#toLongLong)**(bool **ok* = nullptr, int *base* = 10) const |
| QString                                                      | **[toLower](https://doc.qt.io/qt-6/qstring.html#toLower)**() const |
| NSString *                                                   | **[toNSString](https://doc.qt.io/qt-6/qstring.html#toNSString)**() const |
| short                                                        | **[toShort](https://doc.qt.io/qt-6/qstring.html#toShort)**(bool **ok* = nullptr, int *base* = 10) const |
| std::string                                                  | **[toStdString](https://doc.qt.io/qt-6/qstring.html#toStdString)**() const |
| std::u16string                                               | **[toStdU16String](https://doc.qt.io/qt-6/qstring.html#toStdU16String)**() const |
| std::u32string                                               | **[toStdU32String](https://doc.qt.io/qt-6/qstring.html#toStdU32String)**() const |
| std::wstring                                                 | **[toStdWString](https://doc.qt.io/qt-6/qstring.html#toStdWString)**() const |
| uint                                                         | **[toUInt](https://doc.qt.io/qt-6/qstring.html#toUInt)**(bool **ok* = nullptr, int *base* = 10) const |
| ulong                                                        | **[toULong](https://doc.qt.io/qt-6/qstring.html#toULong)**(bool **ok* = nullptr, int *base* = 10) const |
| qulonglong                                                   | **[toULongLong](https://doc.qt.io/qt-6/qstring.html#toULongLong)**(bool **ok* = nullptr, int *base* = 10) const |
| ushort                                                       | **[toUShort](https://doc.qt.io/qt-6/qstring.html#toUShort)**(bool **ok* = nullptr, int *base* = 10) const |
| QList< uint>                                                 | **[toUcs4](https://doc.qt.io/qt-6/qstring.html#toUcs4)**() const |
| QString                                                      | **[toUpper](https://doc.qt.io/qt-6/qstring.html#toUpper)**() const |
| QByteArray                                                   | **[toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)**() const |
| qsizetype                                                    | **[toWCharArray](https://doc.qt.io/qt-6/qstring.html#toWCharArray)**(wchar_t **array*) const |
| decltype(qTokenize(*this, std::forward< Needle>(needle), flags...)) | **[tokenize](https://doc.qt.io/qt-6/qstring.html#tokenize)**(Needle &&*sep*, Flags... *flags*) const & |
| decltype(qTokenize(std::move(*this), std::forward< Needle>(needle), flags...)) | **[tokenize](https://doc.qt.io/qt-6/qstring.html#tokenize-1)**(Needle &&*sep*, Flags... *flags*) const && |
| decltype(qTokenize(std::move(*this), std::forward< Needle>(needle), flags...)) | **[tokenize](https://doc.qt.io/qt-6/qstring.html#tokenize-2)**(Needle &&*sep*, Flags... *flags*) && |
| QString                                                      | **[trimmed](https://doc.qt.io/qt-6/qstring.html#trimmed)**() const |
| void                                                         | **[truncate](https://doc.qt.io/qt-6/qstring.html#truncate)**(qsizetype *position*) |
| const QChar *                                                | **[unicode](https://doc.qt.io/qt-6/qstring.html#unicode)**() const |
| const ushort *                                               | **[utf16](https://doc.qt.io/qt-6/qstring.html#utf16)**() const |
| bool                                                         | **[operator!=](https://doc.qt.io/qt-6/qstring.html#operator-not-eq-9)**(const char **other*) const |
| bool                                                         | **[operator!=](https://doc.qt.io/qt-6/qstring.html#operator-not-eq-10)**(const QByteArray &*other*) const |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq)**(const QString &*other*) |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq-1)**(QChar *ch*) |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq-2)**(QStringView *str*) |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq-3)**(QLatin1StringView *str*) |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq-4)**(QUtf8StringView *str*) |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq-5)**(const char **str*) |
| QString &                                                    | **[operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq-6)**(const QByteArray &*ba*) |
| bool                                                         | **[operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-9)**(const char **other*) const |
| bool                                                         | **[operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-10)**(const QByteArray &*other*) const |
| bool                                                         | **[operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq-9)**(const char **other*) const |
| bool                                                         | **[operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq-10)**(const QByteArray &*other*) const |
| QString &                                                    | **[operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq)**(const QString &*other*) |
| QString &                                                    | **[operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq-1)**(QChar *ch*) |
| QString &                                                    | **[operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq-2)**(QLatin1StringView *str*) |
| QString &                                                    | **[operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq-3)**(QString &&*other*) |
| QString &                                                    | **[operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq-4)**(const char **str*) |
| QString &                                                    | **[operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq-5)**(const QByteArray &*ba*) |
| bool                                                         | **[operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-9)**(const char **other*) const |
| bool                                                         | **[operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-10)**(const QByteArray &*other*) const |
| bool                                                         | **[operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt-9)**(const char **other*) const |
| bool                                                         | **[operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt-10)**(const QByteArray &*other*) const |
| bool                                                         | **[operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq-9)**(const char **other*) const |
| bool                                                         | **[operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq-10)**(const QByteArray &*other*) const |
| QChar &                                                      | **[operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)**(qsizetype *position*) |
| const QChar                                                  | **[operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d-1)**(qsizetype *position*) const |

## Static Public Members

| QString | **[asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)**(const char **cformat*, ...) |
| ------- | ------------------------------------------------------------ |
| int     | **[compare](https://doc.qt.io/qt-6/qstring.html#compare)**(const QString &*s1*, const QString &*s2*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| int     | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-5)**(const QString &*s1*, QLatin1StringView *s2*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| int     | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-6)**(QLatin1StringView *s1*, const QString &*s2*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| int     | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-7)**(const QString &*s1*, QStringView *s2*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| int     | **[compare](https://doc.qt.io/qt-6/qstring.html#compare-8)**(QStringView *s1*, const QString &*s2*, Qt::CaseSensitivity *cs* = Qt::CaseSensitive) |
| QString | **[fromCFString](https://doc.qt.io/qt-6/qstring.html#fromCFString)**(CFStringRef *string*) |
| QString | **[fromEcmaString](https://doc.qt.io/qt-6/qstring.html#fromEcmaString)**(emscripten::val *jsString*) |
| QString | **[fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)**(const char **str*, qsizetype *size*) |
| QString | **[fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1-1)**(QByteArrayView *str*) |
| QString | **[fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1-2)**(const QByteArray &*str*) |
| QString | **[fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)**(const char **str*, qsizetype *size*) |
| QString | **[fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit-1)**(QByteArrayView *str*) |
| QString | **[fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit-2)**(const QByteArray &*str*) |
| QString | **[fromNSString](https://doc.qt.io/qt-6/qstring.html#fromNSString)**(const NSString **string*) |
| QString | **[fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)**(const QChar **unicode*, qsizetype *size*) |
| QString | **[fromStdString](https://doc.qt.io/qt-6/qstring.html#fromStdString)**(const std::string &*str*) |
| QString | **[fromStdU16String](https://doc.qt.io/qt-6/qstring.html#fromStdU16String)**(const std::u16string &*str*) |
| QString | **[fromStdU32String](https://doc.qt.io/qt-6/qstring.html#fromStdU32String)**(const std::u32string &*str*) |
| QString | **[fromStdWString](https://doc.qt.io/qt-6/qstring.html#fromStdWString)**(const std::wstring &*str*) |
| QString | **[fromUcs4](https://doc.qt.io/qt-6/qstring.html#fromUcs4)**(const char32_t **unicode*, qsizetype *size* = -1) |
| QString | **[fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)**(const char **str*, qsizetype *size*) |
| QString | **[fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8-1)**(QByteArrayView *str*) |
| QString | **[fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8-2)**(const QByteArray &*str*) |
| QString | **[fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8-3)**(const char8_t **str*) |
| QString | **[fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8-4)**(const char8_t **str*, qsizetype *size*) |
| QString | **[fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)**(const char16_t **unicode*, qsizetype *size* = -1) |
| QString | **[fromWCharArray](https://doc.qt.io/qt-6/qstring.html#fromWCharArray)**(const wchar_t **string*, qsizetype *size* = -1) |
| int     | **[localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare)**(const QString &*s1*, const QString &*s2*) |
| int     | **[localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare-3)**(QStringView *s1*, QStringView *s2*) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number)**(long *n*, int *base* = 10) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number-1)**(int *n*, int *base* = 10) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number-2)**(uint *n*, int *base* = 10) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number-3)**(ulong *n*, int *base* = 10) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number-4)**(qlonglong *n*, int *base* = 10) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number-5)**(qulonglong *n*, int *base* = 10) |
| QString | **[number](https://doc.qt.io/qt-6/qstring.html#number-6)**(double *n*, char *format* = 'g', int *precision* = 6) |
| QString | **[vasprintf](https://doc.qt.io/qt-6/qstring.html#vasprintf)**(const char **cformat*, va_list *ap*) |

## Related Non-Members

| qsizetype     | **[erase](https://doc.qt.io/qt-6/qstring.html#erase-3)**(QString &*s*, const T &*t*) |
| ------------- | ------------------------------------------------------------ |
| qsizetype     | **[erase_if](https://doc.qt.io/qt-6/qstring.html#erase_if-1)**(QString &*s*, Predicate *pred*) |
| bool          | **[operator!=](https://doc.qt.io/qt-6/qstring.html#operator-not-eq)**(const QString &*s1*, const QString &*s2*) |
| bool          | **[operator!=](https://doc.qt.io/qt-6/qstring.html#operator-not-eq-1)**(const QString &*s1*, QLatin1StringView *s2*) |
| bool          | **[operator!=](https://doc.qt.io/qt-6/qstring.html#operator-not-eq-11)**(const char **s1*, const QString &*s2*) |
| QString       | **[operator""_s](https://doc.qt.io/qt-6/qstring.html#operator-22-22_s)**(const char16_t **str*, size_t *size*) |
| QString       | **[operator+](https://doc.qt.io/qt-6/qstring.html#operator-2b)**(const QString &*s1*, const QString &*s2*) |
| QString       | **[operator+](https://doc.qt.io/qt-6/qstring.html#operator-2b-1)**(QString &&*s1*, const QString &*s2*) |
| QString       | **[operator+](https://doc.qt.io/qt-6/qstring.html#operator-2b-2)**(const QString &*s1*, const char **s2*) |
| QString       | **[operator+](https://doc.qt.io/qt-6/qstring.html#operator-2b-3)**(const char **s1*, const QString &*s2*) |
| bool          | **[operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-1)**(const QString &*s1*, const QString &*s2*) |
| bool          | **[operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-2)**(const QString &*s1*, QLatin1StringView *s2*) |
| bool          | **[operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-3)**(QLatin1StringView *s1*, const QString &*s2*) |
| bool          | **[operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-11)**(const char **s1*, const QString &*s2*) |
| QDataStream & | **[operator< < ](https://doc.qt.io/qt-6/qstring.html#operator-lt-lt)**(QDataStream &*stream*, const QString &*string*) |
| bool          | **[operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq)**(const QString &*s1*, const QString &*s2*) |
| bool          | **[operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq-1)**(const QString &*s1*, QLatin1StringView *s2*) |
| bool          | **[operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq-2)**(QLatin1StringView *s1*, const QString &*s2*) |
| bool          | **[operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq-11)**(const char **s1*, const QString &*s2*) |
| bool          | **[operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-1)**(const QString &*s1*, const QString &*s2*) |
| bool          | **[operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-2)**(const QString &*s1*, QLatin1StringView *s2*) |
| bool          | **[operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-3)**(QLatin1StringView *s1*, const QString &*s2*) |
| bool          | **[operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-11)**(const char **s1*, const QString &*s2*) |
| bool          | **[operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt)**(const QString &*s1*, const QString &*s2*) |
| bool          | **[operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt-1)**(const QString &*s1*, QLatin1StringView *s2*) |
| bool          | **[operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt-2)**(QLatin1StringView *s1*, const QString &*s2*) |
| bool          | **[operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt-11)**(const char **s1*, const QString &*s2*) |
| bool          | **[operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq)**(const QString &*s1*, const QString &*s2*) |
| bool          | **[operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq-1)**(const QString &*s1*, QLatin1StringView *s2*) |
| bool          | **[operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq-2)**(QLatin1StringView *s1*, const QString &*s2*) |
| bool          | **[operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq-11)**(const char **s1*, const QString &*s2*) |
| QDataStream & | **[operator>>](https://doc.qt.io/qt-6/qstring.html#operator-gt-gt)**(QDataStream &*stream*, QString &*string*) |

## Macros

|                 | **[QStringLiteral](https://doc.qt.io/qt-6/qstring.html#QStringLiteral)**(*str*) |
| --------------- | ------------------------------------------------------------ |
|                 | **[QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII)** |
|                 | **[QT_NO_CAST_TO_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_TO_ASCII)** |
|                 | **[QT_RESTRICTED_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_RESTRICTED_CAST_FROM_ASCII)** |
| const char *    | **[qPrintable](https://doc.qt.io/qt-6/qstring.html#qPrintable)**(const QString &*str*) |
| const wchar_t * | **[qUtf16Printable](https://doc.qt.io/qt-6/qstring.html#qUtf16Printable)**(const QString &*str*) |
| const char *    | **[qUtf8Printable](https://doc.qt.io/qt-6/qstring.html#qUtf8Printable)**(const QString &*str*) |

## Detailed Description

QString stores a string of 16-bit [QChar](https://doc.qt.io/qt-6/qchar.html)s, where each [QChar](https://doc.qt.io/qt-6/qchar.html) corresponds to one UTF-16 code unit. (Unicode characters with code values above 65535 are stored using surrogate pairs, i.e., two consecutive [QChar](https://doc.qt.io/qt-6/qchar.html)s.)

[Unicode](https://doc.qt.io/qt-6/unicode.html) is an international standard that supports most of the writing systems in use today. It is a superset of US-ASCII (ANSI X3.4-1986) and Latin-1 (ISO 8859-1), and all the US-ASCII/Latin-1 characters are available at the same code positions.

Behind the scenes, QString uses [implicit sharing](https://doc.qt.io/qt-6/implicit-sharing.html) (copy-on-write) to reduce memory usage and to avoid the needless copying of data. This also helps reduce the inherent overhead of storing 16-bit characters instead of 8-bit characters.

In addition to QString, Qt also provides the [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) class to store raw bytes and traditional 8-bit '\0'-terminated strings. For most purposes, QString is the class you want to use. It is used throughout the Qt API, and the Unicode support ensures that your applications will be easy to translate if you want to expand your application's market at some point. The two main cases where [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) is appropriate are when you need to store raw binary data, and when memory conservation is critical (like in embedded systems).

### Initializing a String

One way to initialize a QString is simply to pass a `const char *` to its constructor. For example, the following code creates a QString of size 5 containing the data "Hello":

```
QString str = "Hello";
```

QString converts the `const char *` data into Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

In all of the QString functions that take `const char *` parameters, the `const char *` is interpreted as a classic C-style '\0'-terminated string encoded in UTF-8. It is legal for the `const char *` parameter to be `nullptr`.

You can also provide string data as an array of [QChar](https://doc.qt.io/qt-6/qchar.html)s:

```
static const QChar data[4] = { 0x0055, 0x006e, 0x10e3, 0x03a3 };
QString str(data, 4);
```

QString makes a deep copy of the [QChar](https://doc.qt.io/qt-6/qchar.html) data, so you can modify it later without experiencing side effects. (If for performance reasons you don't want to take a deep copy of the character data, use [QString::fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)() instead.)

Another approach is to set the size of the string using [resize](https://doc.qt.io/qt-6/qstring.html#resize)() and to initialize the data character per character. QString uses 0-based indexes, just like C++ arrays. To access the character at a particular index position, you can use [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)(). On non-`const` strings, [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)() returns a reference to a character that can be used on the left side of an assignment. For example:

```
QString str;
str.resize(4);

str[0] = QChar('U');
str[1] = QChar('n');
str[2] = QChar(0x10e3);
str[3] = QChar(0x03a3);
```

For read-only access, an alternative syntax is to use the [at](https://doc.qt.io/qt-6/qstring.html#at)() function:

```
QString str;

for (qsizetype i = 0; i <  str.size(); ++i) {
    if (str.at(i) >= QChar('a') && str.at(i) < = QChar('f'))
        qDebug() < <  "Found character in range [a-f]";
}
```

The [at](https://doc.qt.io/qt-6/qstring.html#at)() function can be faster than [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)(), because it never causes a [deep copy](https://doc.qt.io/qt-6/implicit-sharing.html#deep-copy) to occur. Alternatively, use the [first](https://doc.qt.io/qt-6/qstring.html#first)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), or [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)() functions to extract several characters at a time.

A QString can embed '\0' characters ([QChar::Null](https://doc.qt.io/qt-6/qchar.html#SpecialCharacter-enum)). The [size](https://doc.qt.io/qt-6/qstring.html#size)() function always returns the size of the whole string, including embedded '\0' characters.

After a call to the [resize](https://doc.qt.io/qt-6/qstring.html#resize)() function, newly allocated characters have undefined values. To set all the characters in the string to a particular value, use the [fill](https://doc.qt.io/qt-6/qstring.html#fill)() function.

QString provides dozens of overloads designed to simplify string usage. For example, if you want to compare a QString with a string literal, you can write code like this and it will work as expected:

```
QString str;

if (str == "auto" || str == "extern"
        || str == "static" || str == "register") {
    // ...
}
```

You can also pass string literals to functions that take QStrings as arguments, invoking the QString(const char *) constructor. Similarly, you can pass a QString to a function that takes a `const char *` argument using the [qPrintable](https://doc.qt.io/qt-6/qstring.html#qPrintable)() macro which returns the given QString as a `const char *`. This is equivalent to calling < QString>.[toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)().[constData](https://doc.qt.io/qt-6/qstring.html#constData)().

### Manipulating String Data

QString provides the following basic functions for modifying the character data: [append](https://doc.qt.io/qt-6/qstring.html#append)(), [prepend](https://doc.qt.io/qt-6/qstring.html#prepend)(), [insert](https://doc.qt.io/qt-6/qstring.html#insert)(), [replace](https://doc.qt.io/qt-6/qstring.html#replace)(), and [remove](https://doc.qt.io/qt-6/qstring.html#remove)(). For example:

```
QString str = "and";
str.prepend("rock ");     // str == "rock and"
str.append(" roll");        // str == "rock and roll"
str.replace(5, 3, "&");   // str == "rock & roll"
```

In the above example the [replace](https://doc.qt.io/qt-6/qstring.html#replace)() function's first two arguments are the position from which to start replacing and the number of characters that should be replaced.

When data-modifying functions increase the size of the string, they may lead to reallocation of memory for the QString object. When this happens, QString expands by more than it immediately needs so as to have space for further expansion without reallocation until the size of the string has greatly increased.

The [insert](https://doc.qt.io/qt-6/qstring.html#insert)(), [remove](https://doc.qt.io/qt-6/qstring.html#remove)() and, when replacing a sub-string with one of different size, [replace](https://doc.qt.io/qt-6/qstring.html#replace)() functions can be slow ([linear time](https://doc.qt.io/qt-6/containers.html#linear-time)) for large strings, because they require moving many characters in the string by at least one position in memory.

If you are building a QString gradually and know in advance approximately how many characters the QString will contain, you can call [reserve](https://doc.qt.io/qt-6/qstring.html#reserve)(), asking QString to preallocate a certain amount of memory. You can also call [capacity](https://doc.qt.io/qt-6/qstring.html#capacity)() to find out how much memory the QString actually has allocated.

QString provides [STL-style iterators](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) ([QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) and [QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx)). In practice, iterators are handy when working with generic algorithms provided by the C++ standard library.

**Note:** Iterators over a QString, and references to individual characters within one, cannot be relied on to remain valid when any non-`const` method of the QString is called. Accessing such an iterator or reference after the call to a non-`const` method leads to undefined behavior. When stability for iterator-like functionality is required, you should use indexes instead of iterators as they are not tied to QString's internal state and thus do not get invalidated.

**Note:** Due to [implicit sharing](https://doc.qt.io/qt-6/implicit-sharing.html), the first non-`const` operator or function used on a given QString may cause it to, internally, perform a deep copy of its data. This invalidates all iterators over the string and references to individual characters within it. After the first non-`const` operator, operations that modify QString may completely (in case of reallocation) or partially invalidate iterators and references, but other methods (such as [begin](https://doc.qt.io/qt-6/qstring.html#begin)() or [end](https://doc.qt.io/qt-6/qstring.html#end)()) will not. Accessing an iterator or reference after it has been invalidated leads to undefined behavior.

A frequent requirement is to remove whitespace characters from a string ('\n', '\t', ' ', etc.). If you want to remove whitespace from both ends of a QString, use the [trimmed](https://doc.qt.io/qt-6/qstring.html#trimmed)() function. If you want to remove whitespace from both ends and replace multiple consecutive whitespaces with a single space character within the string, use [simplified](https://doc.qt.io/qt-6/qstring.html#simplified)().

If you want to find all occurrences of a particular character or substring in a QString, use the [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)() or [lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)() functions. The former searches forward starting from a given index position, the latter searches backward. Both return the index position of the character or substring if they find it; otherwise, they return -1. For example, here is a typical loop that finds all occurrences of a particular substring:

```
QString str = "We must be < b>bold< /b>, very < b>bold< /b>";
qsizetype j = 0;

while ((j = str.indexOf("< b>", j)) != -1) {
    qDebug() < <  "Found < b> tag at index position" < <  j;
    ++j;
}
```

QString provides many functions for converting numbers into strings and strings into numbers. See the [arg](https://doc.qt.io/qt-6/qstring.html#arg)() functions, the [setNum](https://doc.qt.io/qt-6/qstring.html#setNum)() functions, the [number](https://doc.qt.io/qt-6/qstring.html#number)() static functions, and the [toInt](https://doc.qt.io/qt-6/qstring.html#toInt)(), [toDouble](https://doc.qt.io/qt-6/qstring.html#toDouble)(), and similar functions.

To get an upper- or lowercase version of a string use [toUpper](https://doc.qt.io/qt-6/qstring.html#toUpper)() or [toLower](https://doc.qt.io/qt-6/qstring.html#toLower)().

Lists of strings are handled by the [QStringList](https://doc.qt.io/qt-6/qstringlist.html) class. You can split a string into a list of strings using the [split](https://doc.qt.io/qt-6/qstring.html#split)() function, and join a list of strings into a single string with an optional separator using [QStringList::join](https://doc.qt.io/qt-6/qstringlist.html#join)(). You can obtain a list of strings from a string list that contain a particular substring or that match a particular [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) using the [QStringList::filter](https://doc.qt.io/qt-6/qstringlist.html#filter)() function.

### Querying String Data

If you want to see if a QString starts or ends with a particular substring use [startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith)() or [endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)(). If you simply want to check whether a QString contains a particular character or substring, use the [contains](https://doc.qt.io/qt-6/qstring.html#contains)() function. If you want to find out how many times a particular character or substring occurs in the string, use count().

To obtain a pointer to the actual character data, call [data](https://doc.qt.io/qt-6/qstring.html#data)() or [constData](https://doc.qt.io/qt-6/qstring.html#constData)(). These functions return a pointer to the beginning of the [QChar](https://doc.qt.io/qt-6/qchar.html) data. The pointer is guaranteed to remain valid until a non-`const` function is called on the QString.

#### Comparing Strings

QStrings can be compared using overloaded operators such as [operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-1)(), [operator< =](https://doc.qt.io/qt-6/qstring.html#operator-lt-eq)(), [operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-1)(), [operator>=](https://doc.qt.io/qt-6/qstring.html#operator-gt-eq)(), and so on. Note that the comparison is based exclusively on the numeric Unicode values of the characters. It is very fast, but is not what a human would expect; the [QString::localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare)() function is usually a better choice for sorting user-interface strings, when such a comparison is available.

On Unix-like platforms (including Linux, macOS and iOS), when Qt is linked with the ICU library (which it usually is), its locale-aware sorting is used. Otherwise, on macOS and iOS, [localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare)() compares according the "Order for sorted lists" setting in the International preferences panel. On other Unix-like systems without ICU, the comparison falls back to the system library's `strcoll()`,

### Converting Between Encoded Strings Data and QString

QString provides the following three functions that return a `const char *` version of the string as [QByteArray](https://doc.qt.io/qt-6/qbytearray.html): [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), and [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)().

- [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)() returns a Latin-1 (ISO 8859-1) encoded 8-bit string.
- [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)() returns a UTF-8 encoded 8-bit string. UTF-8 is a superset of US-ASCII (ANSI X3.4-1986) that supports the entire Unicode character set through multibyte sequences.
- [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)() returns an 8-bit string using the system's local encoding. This is the same as [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)() on Unix systems.

To convert from one of these encodings, QString provides [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), and [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(). Other encodings are supported through the [QStringEncoder](https://doc.qt.io/qt-6/qstringencoder.html) and [QStringDecoder](https://doc.qt.io/qt-6/qstringdecoder.html) classes.

As mentioned above, QString provides a lot of functions and operators that make it easy to interoperate with `const char *` strings. But this functionality is a double-edged sword: It makes QString more convenient to use if all strings are US-ASCII or Latin-1, but there is always the risk that an implicit conversion from or to `const char *` is done using the wrong 8-bit encoding. To minimize these risks, you can turn off these implicit conversions by defining some of the following preprocessor symbols:

- [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) disables automatic conversions from C string literals and pointers to Unicode.
- [QT_RESTRICTED_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_RESTRICTED_CAST_FROM_ASCII) allows automatic conversions from C characters and character arrays, but disables automatic conversions from character pointers to Unicode.
- [QT_NO_CAST_TO_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_TO_ASCII) disables automatic conversion from QString to C strings.

You then need to explicitly call [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), or [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)() to construct a QString from an 8-bit string, or use the lightweight [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) class, for example:

```
QString url = "https://www.unicode.org/"_L1;
```

Similarly, you must call [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), or [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)() explicitly to convert the QString to an 8-bit string.

|                    Note for C Programmers                    |
| :----------------------------------------------------------: |
| Due to C++'s type system and the fact that QString is [implicitly shared](https://doc.qt.io/qt-6/implicit-sharing.html), QStrings may be treated like `int`s or other basic types. For example:`QString Widget::boolToString(bool b) {    QString result;    if (b)        result = "True";    else        result = "False";    return result; }`The `result` variable, is a normal variable allocated on the stack. When `return` is called, and because we're returning by value, the copy constructor is called and a copy of the string is returned. No actual copying takes place thanks to the implicit sharing. |

### Distinction Between Null and Empty Strings

For historical reasons, QString distinguishes between a null string and an empty string. A *null* string is a string that is initialized using QString's default constructor or by passing (`const char *`)0 to the constructor. An *empty* string is any string with size 0. A null string is always empty, but an empty string isn't necessarily null:

```
QString().isNull();               // returns true
QString().isEmpty();              // returns true

QString("").isNull();             // returns false
QString("").isEmpty();            // returns true

QString("abc").isNull();          // returns false
QString("abc").isEmpty();         // returns false
```

All functions except [isNull](https://doc.qt.io/qt-6/qstring.html#isNull)() treat null strings the same as empty strings. For example, [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)().[constData](https://doc.qt.io/qt-6/qstring.html#constData)() returns a valid pointer (*not* nullptr) to a '\0' character for a null string. We recommend that you always use the [isEmpty](https://doc.qt.io/qt-6/qstring.html#isEmpty)() function and avoid [isNull](https://doc.qt.io/qt-6/qstring.html#isNull)().

### Number Formats

When a [QString::arg](https://doc.qt.io/qt-6/qstring.html#arg)() `'%'` format specifier includes the `'L'` locale qualifier, and the base is ten (its default), the default locale is used. This can be set using [QLocale::setDefault](https://doc.qt.io/qt-6/qlocale.html#setDefault)(). For more refined control of localized string representations of numbers, see [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString)(). All other number formatting done by QString follows the C locale's representation of numbers.

When [QString::arg](https://doc.qt.io/qt-6/qstring.html#arg)() applies left-padding to numbers, the fill character `'0'` is treated specially. If the number is negative, its minus sign will appear before the zero-padding. If the field is localized, the locale-appropriate zero character is used in place of `'0'`. For floating-point numbers, this special treatment only applies if the number is finite.

#### Floating-point Formats

In member functions (e.g., [arg](https://doc.qt.io/qt-6/qstring.html#arg)(), [number](https://doc.qt.io/qt-6/qstring.html#number)()) that represent floating-point numbers (`float` or `double`) as strings, the form of display can be controlled by a choice of *format* and *precision*, whose meanings are as for [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString-8)(double, char, int).

If the selected *format* includes an exponent, localized forms follow the locale's convention on digits in the exponent. For non-localized formatting, the exponent shows its sign and includes at least two digits, left-padding with zero if needed.

### More Efficient String Construction

Many strings are known at compile time. But the trivial constructor QString("Hello"), will copy the contents of the string, treating the contents as Latin-1. To avoid this, one can use the [QStringLiteral](https://doc.qt.io/qt-6/qstring.html#QStringLiteral) macro to directly create the required data at compile time. Constructing a QString out of the literal does then not cause any overhead at runtime.

A slightly less efficient way is to use [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html). This class wraps a C string literal, precalculates it length at compile time and can then be used for faster comparison with QStrings and conversion to QStrings than a regular C string literal.

Using the QString `'+'` operator, it is easy to construct a complex string from multiple substrings. You will often write code like this:

```
    QString foo;
    QString type = "long";

    foo = "vector< "_L1 + type + ">::iterator"_L1;

    if (foo.startsWith("(" + type + ") 0x"))
        ...
```

There is nothing wrong with either of these string constructions, but there are a few hidden inefficiencies. Beginning with Qt 4.6, you can eliminate them.

First, multiple uses of the `'+'` operator usually means multiple memory allocations. When concatenating *n* substrings, where *n > 2*, there can be as many as *n - 1* calls to the memory allocator.

In 4.6, an internal template class `QStringBuilder` has been added along with a few helper functions. This class is marked internal and does not appear in the documentation, because you aren't meant to instantiate it in your code. Its use will be automatic, as described below. The class is found in `src/corelib/tools/qstringbuilder.cpp` if you want to have a look at it.

`QStringBuilder` uses expression templates and reimplements the `'%'` operator so that when you use `'%'` for string concatenation instead of `'+'`, multiple substring concatenations will be postponed until the final result is about to be assigned to a QString. At this point, the amount of memory required for the final result is known. The memory allocator is then called *once* to get the required space, and the substrings are copied into it one by one.

Additional efficiency is gained by inlining and reduced reference counting (the QString created from a `QStringBuilder` typically has a ref count of 1, whereas [QString::append](https://doc.qt.io/qt-6/qstring.html#append)() needs an extra test).

There are two ways you can access this improved method of string construction. The straightforward way is to include `QStringBuilder` wherever you want to use it, and use the `'%'` operator instead of `'+'` when concatenating strings:

```
    #include < QStringBuilder>

    QString hello("hello");
    QStringView el = QStringView{ hello }.mid(2, 3);
    QLatin1StringView world("world");
    QString message =  hello % el % world % QChar('!');
```

A more global approach, which is more convenient but not entirely source compatible, is to define `QT_USE_QSTRINGBUILDER` (by adding it to the compiler flags) at build time. This will make concatenating strings with `'+'` work the same way as `QStringBuilder` `'%'`.

**Note:** Take care when using the `auto` keyword with the result of string concatenation using QStringBuilder:

```
    QString str("QStringBuilder");

    // "s" type is deduced as QStringBuilder
    auto s = "Like hot glue, " % str % " concatenates strings";

    // Similarly the return type of this lambda is deduced as QStringBuilder
    auto concatenateStr = []() {
        return "Like hot glue, " % str % " concatenates strings";
    };
```

Typically this is not what is expected (and can result in undefined behavior). This issue can be fixed by specifying the return type:

```
    QString s = "Like hot glue, " % str % " concatenates strings";

    // With a lambda, specify a trailing return type
    auto concatenateStr = []() -> QString {
        return "Like hot glue, " % str % " concatenates strings";
    };
```

**Note:** [Clazy](https://invent.kde.org/sdk/clazy) has a check, auto-unexpected-qstringbuilder, that catches this issue.

### Maximum Size and Out-of-memory Conditions

The maximum size of QString depends on the architecture. Most 64-bit systems can allocate more than 2 GB of memory, with a typical limit of 2^63 bytes. The actual value also depends on the overhead required for managing the data block. As a result, you can expect the maximum size of 2 GB minus overhead on 32-bit platforms, and 2^63 bytes minus overhead on 64-bit platforms. The number of elements that can be stored in a QString is this maximum size divided by the size of [QChar](https://doc.qt.io/qt-6/qchar.html).

When memory allocation fails, QString throws a `std::bad_alloc` exception if the application was compiled with exception support. Out of memory conditions in Qt containers are the only case where Qt will throw exceptions. If exceptions are disabled, then running out of memory is undefined behavior.

Note that the operating system may impose further limits on applications holding a lot of allocated memory, especially large, contiguous blocks. Such considerations, the configuration of such behavior or any mitigation are outside the scope of the Qt API.

**See also** [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)(), [QChar](https://doc.qt.io/qt-6/qchar.html), [QStringView](https://doc.qt.io/qt-6/qstringview.html), [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html), and [QByteArray](https://doc.qt.io/qt-6/qbytearray.html).

## Member Type Documentation

### QString::ConstIterator

Qt-style synonym for [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef).

### QString::Iterator

Qt-style synonym for [QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx).

### enum QString::NormalizationForm

This enum describes the various normalized forms of Unicode text.

| Constant                        | Value | Description                                                  |
| ------------------------------- | ----- | ------------------------------------------------------------ |
| `QString::NormalizationForm_D`  | `0`   | Canonical Decomposition                                      |
| `QString::NormalizationForm_C`  | `1`   | Canonical Decomposition followed by Canonical Composition    |
| `QString::NormalizationForm_KD` | `2`   | Compatibility Decomposition                                  |
| `QString::NormalizationForm_KC` | `3`   | Compatibility Decomposition followed by Canonical Composition |

**See also** [normalized](https://doc.qt.io/qt-6/qstring.html#normalized)() and [Unicode Standard Annex #15](https://www.unicode.org/reports/tr15/).

### enum QString::SectionFlag flags QString::SectionFlags

This enum specifies flags that can be used to affect various aspects of the [section](https://doc.qt.io/qt-6/qstring.html#section)() function's behavior with respect to separators and empty fields.

| Constant                              | Value  | Description                                                  |
| ------------------------------------- | ------ | ------------------------------------------------------------ |
| `QString::SectionDefault`             | `0x00` | Empty fields are counted, leading and trailing separators are not included, and the separator is compared case sensitively. |
| `QString::SectionSkipEmpty`           | `0x01` | Treat empty fields as if they don't exist, i.e. they are not considered as far as *start* and *end* are concerned. |
| `QString::SectionIncludeLeadingSep`   | `0x02` | Include the leading separator (if any) in the result string. |
| `QString::SectionIncludeTrailingSep`  | `0x04` | Include the trailing separator (if any) in the result string. |
| `QString::SectionCaseInsensitiveSeps` | `0x08` | Compare the separator case-insensitively.                    |

The SectionFlags type is a typedef for [QFlags](https://doc.qt.io/qt-6/qflags.html)< SectionFlag>. It stores an OR combination of SectionFlag values.

**See also** [section](https://doc.qt.io/qt-6/qstring.html#section)().

### QString::const_iterator

**See also** [QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx).

### QString::const_pointer

The QString::const_pointer typedef provides an STL-style const pointer to a [QString](https://doc.qt.io/qt-6/qstring.html) element ([QChar](https://doc.qt.io/qt-6/qchar.html)).

### QString::const_reference

### QString::const_reverse_iterator

**See also** [QString::reverse_iterator](https://doc.qt.io/qt-6/qstring.html#reverse_iterator-typedef) and [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef).

### QString::difference_type

### QString::iterator

**See also** [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef).

### QString::pointer

The QString::pointer typedef provides an STL-style pointer to a [QString](https://doc.qt.io/qt-6/qstring.html) element ([QChar](https://doc.qt.io/qt-6/qchar.html)).

### QString::reference

### QString::reverse_iterator

**See also** [QString::const_reverse_iterator](https://doc.qt.io/qt-6/qstring.html#const_reverse_iterator-typedef) and [QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx).

### QString::size_type

### QString::value_type

## Member Function Documentation

### template < typename Args> [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(Args &&... *args*) const

Replaces occurrences of `%N` in this string with the corresponding argument from *args*. The arguments are not positional: the first of the *args* replaces the `%N` with the lowest `N` (all of them), the second of the *args* the `%N` with the next-lowest `N` etc.

`Args` can consist of anything that implicitly converts to [QString](https://doc.qt.io/qt-6/qstring.html), [QStringView](https://doc.qt.io/qt-6/qstringview.html) or [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html).

In addition, the following types are also supported: [QChar](https://doc.qt.io/qt-6/qchar.html), [QLatin1Char](https://doc.qt.io/qt-6/qlatin1char.html).

**See also** [QString::arg](https://doc.qt.io/qt-6/qstring.html#arg)().

### `[noexcept(...), since 6.0]`template < typename Needle, typename Flags> decltype([qTokenize](https://doc.qt.io/qt-6/qstringtokenizer.html#qTokenize)(std::move(*this), std::forward< Needle>(needle), flags...)) QString::tokenize(Needle &&*sep*, Flags... *flags*) &&

### `[noexcept(...), since 6.0]`template < typename Needle, typename Flags> decltype([qTokenize](https://doc.qt.io/qt-6/qstringtokenizer.html#qTokenize)(*this, std::forward< Needle>(needle), flags...)) QString::tokenize(Needle &&*sep*, Flags... *flags*) const &

### `[noexcept(...), since 6.0]`template < typename Needle, typename Flags> decltype([qTokenize](https://doc.qt.io/qt-6/qstringtokenizer.html#qTokenize)(std::move(*this), std::forward< Needle>(needle), flags...)) QString::tokenize(Needle &&*sep*, Flags... *flags*) const &&

Splits the string into substring views wherever *sep* occurs, and returns a lazy sequence of those strings.

Equivalent to

```
return QStringTokenizer{std::forward< Needle>(sep), flags...};
```

except it works without C++17 Class Template Argument Deduction (CTAD) enabled in the compiler.

See [QStringTokenizer](https://doc.qt.io/qt-6/qstringtokenizer.html) for how *sep* and *flags* interact to form the result.

**Note:** While this function returns [QStringTokenizer](https://doc.qt.io/qt-6/qstringtokenizer.html), you should never, ever, name its template arguments explicitly. If you can use C++17 Class Template Argument Deduction (CTAD), you may write

```
QStringTokenizer result = sv.tokenize(sep);
```

(without template arguments). If you can't use C++17 CTAD, you must store the return value only in `auto` variables:

```
auto result = sv.tokenize(sep);
```

This is because the template arguments of [QStringTokenizer](https://doc.qt.io/qt-6/qstringtokenizer.html) have a very subtle dependency on the specific [tokenize](https://doc.qt.io/qt-6/qstring.html#tokenize)() overload from which they are returned, and they don't usually correspond to the type used for the separator.

This function was introduced in Qt 6.0.

**Note:** (1) does not throw any exception when "noexcept(qTokenize(std::declval< QString>(), std::forward< Needle>(needle), flags...))" is true.

**Note:** (2) does not throw any exception when "noexcept(qTokenize(std::declval< const QString &>(), std::forward< Needle>(needle), flags...))" is true.

**Note:** (3) does not throw any exception when "noexcept(qTokenize(std::declval< const QString>(), std::forward< Needle>(needle), flags...))" is true.

**See also** [QStringTokenizer](https://doc.qt.io/qt-6/qstringtokenizer.html) and [qTokenize](https://doc.qt.io/qt-6/qstringtokenizer.html#qTokenize)().

### `[constexpr noexcept]`QString::QString()

Constructs a null string. Null strings are also considered empty.

**See also** [isEmpty](https://doc.qt.io/qt-6/qstring.html#isEmpty)(), [isNull](https://doc.qt.io/qt-6/qstring.html#isNull)(), and [Distinction Between Null and Empty Strings](https://doc.qt.io/qt-6/qstring.html#distinction-between-null-and-empty-strings).

### `[explicit]`QString::QString(const [QChar](https://doc.qt.io/qt-6/qchar.html) **unicode*, qsizetype *size* = -1)

Constructs a string initialized with the first *size* characters of the [QChar](https://doc.qt.io/qt-6/qchar.html) array *unicode*.

If *unicode* is 0, a null string is constructed.

If *size* is negative, *unicode* is assumed to point to a \0'-terminated array and its length is determined dynamically. The terminating null character is not considered part of the string.

QString makes a deep copy of the string data. The unicode data is copied as is and the Byte Order Mark is preserved if present.

**See also** [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)().

### QString::QString([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

Constructs a string of size 1 containing the character *ch*.

### QString::QString(qsizetype *size*, [QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

Constructs a string of the given *size* with every character set to *ch*.

**See also** [fill](https://doc.qt.io/qt-6/qstring.html#fill)().

### QString::QString([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*)

Constructs a copy of the Latin-1 string viewed by *str*.

**See also** [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)().

### `[since 6.1]`QString::QString(const char8_t **str*)

Constructs a string initialized with the UTF-8 string *str*. The given const char8_t pointer is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

This function was introduced in Qt 6.1.

**See also** [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), and [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

### QString::QString(const char **str*)

Constructs a string initialized with the 8-bit string *str*. The given const char pointer is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this constructor by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

**Note:** Defining [QT_RESTRICTED_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_RESTRICTED_CAST_FROM_ASCII) also disables this constructor, but enables a `QString(const char (&ch)[N])` constructor instead. Using non-literal input, or input with embedded NUL characters, or non-7-bit characters is undefined in this case.

**See also** [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), and [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

### QString::QString(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*ba*)

Constructs a string initialized with the byte array *ba*. The given byte array is converted to Unicode using [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

You can disable this constructor by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000). This behavior is different from Qt 5.x.

**See also** [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), and [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

### `[noexcept]`QString::QString(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*)

Constructs a copy of *other*.

This operation takes [constant time](https://doc.qt.io/qt-6/containers.html#constant-time), because QString is [implicitly shared](https://doc.qt.io/qt-6/implicit-sharing.html). This makes returning a QString from a function very fast. If a shared instance is modified, it will be copied (copy-on-write), and that takes [linear time](https://doc.qt.io/qt-6/containers.html#linear-time).

**See also** [operator=](https://doc.qt.io/qt-6/qstring.html#operator-eq)().

### `[noexcept]`QString::QString([QString](https://doc.qt.io/qt-6/qstring.html#QString) &&*other*)

Move-constructs a QString instance, making it point at the same object that *other* was pointing to.

### `[noexcept]`QString::~QString()

Destroys the string.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*)

Appends the string *str* onto the end of this string.

Example:

```
QString x = "free";
QString y = "dom";

x.append(y);
// x == "freedom"
```

This is the same as using the [insert](https://doc.qt.io/qt-6/qstring.html#insert)() function:

```
x.insert(x.size(), y);
```

The append() function is typically very fast ([constant time](https://doc.qt.io/qt-6/containers.html#constant-time)), because [QString](https://doc.qt.io/qt-6/qstring.html) preallocates extra space at the end of the string data so it can grow without reallocating the entire string each time.

**See also** [operator+=](https://doc.qt.io/qt-6/qstring.html#operator-2b-eq)(), [prepend](https://doc.qt.io/qt-6/qstring.html#prepend)(), and [insert](https://doc.qt.io/qt-6/qstring.html#insert)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This function overloads append().

Appends the character *ch* to this string.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append(const [QChar](https://doc.qt.io/qt-6/qchar.html) **str*, qsizetype *len*)

This function overloads append().

Appends *len* characters from the [QChar](https://doc.qt.io/qt-6/qchar.html) array *str* to this string.

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append([QStringView](https://doc.qt.io/qt-6/qstringview.html) *v*)

This function overloads append().

Appends the given string view *v* to this string and returns the result.

This function was introduced in Qt 6.0.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*)

This function overloads append().

Appends the Latin-1 string viewed by *str* to this string.

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append([QUtf8StringView](https://doc.qt.io/qt-6/qutf8stringview.html) *str*)

This function overloads append().

Appends the UTF-8 string view *str* to this string.

This function was introduced in Qt 6.5.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append(const char **str*)

This function overloads append().

Appends the string *str* to this string. The given const char pointer is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this function by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::append(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*ba*)

This function overloads append().

Appends the byte array *ba* to this string. The given byte array is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this function by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*a*, int *fieldWidth* = 0, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

Returns a copy of this string with the lowest numbered place marker replaced by string *a*, i.e., `%1`, `%2`, ..., `%99`.

*fieldWidth* specifies the minimum amount of space that argument *a* shall occupy. If *a* requires less space than *fieldWidth*, it is padded to *fieldWidth* with character *fillChar*. A positive *fieldWidth* produces right-aligned text. A negative *fieldWidth* produces left-aligned text.

This example shows how we might create a `status` string for reporting progress while processing a list of files:

```
QString i;           // current file's number
QString total;       // number of files to process
QString fileName;    // current file's name

QString status = QString("Processing file %1 of %2: %3")
                .arg(i).arg(total).arg(fileName);
```

First, `arg(i)` replaces `%1`. Then `arg(total)` replaces `%2`. Finally, `arg(fileName)` replaces `%3`.

One advantage of using arg() over [asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)() is that the order of the numbered place markers can change, if the application's strings are translated into other languages, but each arg() will still replace the lowest numbered unreplaced place marker, no matter where it appears. Also, if place marker `%i` appears more than once in the string, the arg() replaces all of them.

If there is no unreplaced place marker remaining, a warning message is output and the result is undefined. Place marker numbers must be in the range 1 to 99.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([qlonglong](https://doc.qt.io/qt-6/qttypes.html#qlonglong-typedef) *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The *base* argument specifies the base to use when converting the integer *a* into a string. The base must be between 2 and 36, with 8 giving octal, 10 decimal, and 16 hexadecimal numbers.

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([qulonglong](https://doc.qt.io/qt-6/qttypes.html#qulonglong-typedef) *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The *base* argument specifies the base to use when converting the integer *a* into a string. *base* must be between 2 and 36, with 8 giving octal, 10 decimal, and 16 hexadecimal numbers.

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(long *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The *a* argument is expressed in the given *base*, which is 10 by default and must be between 2 and 36.

The '%' can be followed by an 'L', in which case the sequence is replaced with a localized representation of *a*. The conversion uses the default locale. The default locale is determined from the system's locale settings at application startup. It can be changed using [QLocale::setDefault](https://doc.qt.io/qt-6/qlocale.html#setDefault)(). The 'L' flag is ignored if *base* is not 10.

```
QString str;
str = QString("Decimal 63 is %1 in hexadecimal")
        .arg(63, 0, 16);
// str == "Decimal 63 is 3f in hexadecimal"

QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
str = QString("%1 %L2 %L3")
        .arg(12345)
        .arg(12345)
        .arg(12345, 0, 16);
// str == "12345 12,345 3039"
```

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([ulong](https://doc.qt.io/qt-6/qttypes.html#ulong-typedef) *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The *base* argument specifies the base to use when converting the integer *a* to a string. The base must be between 2 and 36, with 8 giving octal, 10 decimal, and 16 hexadecimal numbers.

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(int *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

The *a* argument is expressed in base *base*, which is 10 by default and must be between 2 and 36. For bases other than 10, *a* is treated as an unsigned integer.

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The '%' can be followed by an 'L', in which case the sequence is replaced with a localized representation of *a*. The conversion uses the default locale, set by [QLocale::setDefault](https://doc.qt.io/qt-6/qlocale.html#setDefault)(). If no default locale was specified, the system locale is used. The 'L' flag is ignored if *base* is not 10.

```
QString str;
str = QString("Decimal 63 is %1 in hexadecimal")
        .arg(63, 0, 16);
// str == "Decimal 63 is 3f in hexadecimal"

QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
str = QString("%1 %L2 %L3")
        .arg(12345)
        .arg(12345)
        .arg(12345, 0, 16);
// str == "12345 12,345 3039"
```

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([uint](https://doc.qt.io/qt-6/qttypes.html#uint-typedef) *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

The *base* argument specifies the base to use when converting the integer *a* into a string. The base must be between 2 and 36.

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(short *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The *base* argument specifies the base to use when converting the integer *a* into a string. The base must be between 2 and 36, with 8 giving octal, 10 decimal, and 16 hexadecimal numbers.

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([ushort](https://doc.qt.io/qt-6/qttypes.html#ushort-typedef) *a*, int *fieldWidth* = 0, int *base* = 10, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

The *base* argument specifies the base to use when converting the integer *a* into a string. The base must be between 2 and 36, with 8 giving octal, 10 decimal, and 16 hexadecimal numbers.

**See also** [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(double *a*, int *fieldWidth* = 0, char *format* = 'g', int *precision* = -1, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

Argument *a* is formatted according to the specified *format* and *precision*. See [Floating-point Formats](https://doc.qt.io/qt-6/qstring.html#floating-point-formats) for details.

*fieldWidth* specifies the minimum amount of space that *a* is padded to and filled with the character *fillChar*. A positive value produces right-aligned text; a negative value produces left-aligned text.

```
double d = 12.34;
QString str = QString("delta: %1").arg(d, 0, 'E', 3);
// str == "delta: 1.234E+01"
```

**See also** [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString)(), [QLocale::FloatingPointPrecisionOption](https://doc.qt.io/qt-6/qlocale.html#FloatingPointPrecisionOption-enum), and [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg(char *a*, int *fieldWidth* = 0, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

The *a* argument is interpreted as a Latin-1 character.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([QChar](https://doc.qt.io/qt-6/qchar.html) *a*, int *fieldWidth* = 0, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This function overloads arg().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([QStringView](https://doc.qt.io/qt-6/qstringview.html) *a*, int *fieldWidth* = 0, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This is an overloaded function.

Returns a copy of this string with the lowest-numbered place-marker replaced by string *a*, i.e., `%1`, `%2`, ..., `%99`.

*fieldWidth* specifies the minimum amount of space that *a* shall occupy. If *a* requires less space than *fieldWidth*, it is padded to *fieldWidth* with character *fillChar*. A positive *fieldWidth* produces right-aligned text. A negative *fieldWidth* produces left-aligned text.

This example shows how we might create a `status` string for reporting progress while processing a list of files:

```
int i;                // current file's number
int total;            // number of files to process
QStringView fileName; // current file's name

QString status = QString("Processing file %1 of %2: %3")
                .arg(i).arg(total).arg(fileName);
```

First, `arg(i)` replaces `%1`. Then `arg(total)` replaces `%2`. Finally, `arg(fileName)` replaces `%3`.

One advantage of using arg() over [asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)() is that the order of the numbered place markers can change, if the application's strings are translated into other languages, but each arg() will still replace the lowest-numbered unreplaced place-marker, no matter where it appears. Also, if place-marker `%i` appears more than once in the string, arg() replaces all of them.

If there is no unreplaced place-marker remaining, a warning message is printed and the result is undefined. Place-marker numbers must be in the range 1 to 99.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::arg([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *a*, int *fieldWidth* = 0, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar* = u' ') const

This is an overloaded function.

Returns a copy of this string with the lowest-numbered place-marker replaced by the Latin-1 string viewed by *a*, i.e., `%1`, `%2`, ..., `%99`.

*fieldWidth* specifies the minimum amount of space that *a* shall occupy. If *a* requires less space than *fieldWidth*, it is padded to *fieldWidth* with character *fillChar*. A positive *fieldWidth* produces right-aligned text. A negative *fieldWidth* produces left-aligned text.

One advantage of using arg() over [asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)() is that the order of the numbered place markers can change, if the application's strings are translated into other languages, but each arg() will still replace the lowest-numbered unreplaced place-marker, no matter where it appears. Also, if place-marker `%i` appears more than once in the string, arg() replaces all of them.

If there is no unreplaced place-marker remaining, a warning message is printed and the result is undefined. Place-marker numbers must be in the range 1 to 99.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::asprintf(const char **cformat*, ...)

Safely builds a formatted string from the format string *cformat* and an arbitrary list of arguments.

The format string supports the conversion specifiers, length modifiers, and flags provided by printf() in the standard C++ library. The *cformat* string and `%s` arguments must be UTF-8 encoded.

**Note:** The `%lc` escape sequence expects a unicode character of type `char16_t`, or `ushort` (as returned by [QChar::unicode](https://doc.qt.io/qt-6/qchar.html#unicode)()). The `%ls` escape sequence expects a pointer to a zero-terminated array of unicode characters of type `char16_t`, or ushort (as returned by [QString::utf16](https://doc.qt.io/qt-6/qstring.html#utf16)()). This is at odds with the printf() in the standard C++ library, which defines `%lc` to print a wchar_t and `%ls` to print a `wchar_t*`, and might also produce compiler warnings on platforms where the size of `wchar_t` is not 16 bits.

**Warning:** We do not recommend using QString::asprintf() in new Qt code. Instead, consider using [QTextStream](https://doc.qt.io/qt-6/qtextstream.html) or [arg](https://doc.qt.io/qt-6/qstring.html#arg)(), both of which support Unicode strings seamlessly and are type-safe. Here is an example that uses [QTextStream](https://doc.qt.io/qt-6/qtextstream.html):

```
QString result;
QTextStream(&result) < <  "pi = " < <  3.14;
// result == "pi = 3.14"
```

For [translations](https://doc.qt.io/qt-6/qobject.html#tr), especially if the strings contains more than one escape sequence, you should consider using the [arg](https://doc.qt.io/qt-6/qstring.html#arg)() function instead. This allows the order of the replacements to be controlled by the translator.

**See also** [arg](https://doc.qt.io/qt-6/qstring.html#arg)().

### `[since 6.6]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::assign([QAnyStringView](https://doc.qt.io/qt-6/qanystringview.html) *v*)

Replaces the contents of this string with a copy of *v* and returns a reference to this string.

The size of this string will be equal to the size of *v*, converted to UTF-16 as if by `v.toString()`. Unlike [QAnyStringView::toString](https://doc.qt.io/qt-6/qanystringview.html#toString)(), however, this function only allocates memory if the estimated size exceeds the capacity of this string or this string is shared.

This function was introduced in Qt 6.6.

**See also** [QAnyStringView::toString](https://doc.qt.io/qt-6/qanystringview.html#toString)().

### `[since 6.6]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::assign(qsizetype *n*, [QChar](https://doc.qt.io/qt-6/qchar.html) *c*)

Replaces the contents of this string with *n* copies of *c* and returns a reference to this string.

The size of this string will be equal to *n*, which has to be non-negative.

This function will only allocate memory if *n* exceeds the capacity of this string or this string is shared.

This function was introduced in Qt 6.6.

**See also** [fill](https://doc.qt.io/qt-6/qstring.html#fill)().

### `[since 6.6]`template < typename InputIterator, if_compatible_iterator< InputIterator>> [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::assign(InputIterator *first*, InputIterator *last*)

Replaces the contents of this string with a copy of the elements in the iterator range [*first*, *last*) and returns a reference to this string.

The size of this string will be equal to the decoded length of the elements in the range [*first*, *last*), which need not be the same as the length of the range itself, because this function transparently recodes the input character set to UTF-16.

This function will only allocate memory if the number of elements in the range, or, for non-UTF-16-encoded input, the maximum possible size of the resulting string, exceeds the capacity of this string, or if this string is shared.

**Note:** This function overload only participates in overload resolution if `InputIterator` meets the requirements of a [LegacyInputIterator](https://en.cppreference.com/w/cpp/named_req/InputIterator) and the `value_type` of `InputIterator` is one of the following character types:

- [QChar](https://doc.qt.io/qt-6/qchar.html)
- [QLatin1Char](https://doc.qt.io/qt-6/qlatin1char.html)
- `char16_t`
- (on platforms, such as Windows, where it is a 16-bit type) `wchar_t`
- `char32_t`

**Note:** The behavior is undefined if either argument is an iterator into *this or [*first*, *last*) is not a valid range.

This function was introduced in Qt 6.6.

### const [QChar](https://doc.qt.io/qt-6/qchar.html) QString::at(qsizetype *position*) const

Returns the character at the given index *position* in the string.

The *position* must be a valid index position in the string (i.e., 0 < = *position* <  [size](https://doc.qt.io/qt-6/qstring.html#size)()).

**See also** [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)().

### [QChar](https://doc.qt.io/qt-6/qchar.html) QString::back() const

Returns the last character in the string. Same as `at(size() - 1)`.

This function is provided for STL compatibility.

**Warning:** Calling this function on an empty string constitutes undefined behavior.

**See also** [front](https://doc.qt.io/qt-6/qstring.html#front)(), [at](https://doc.qt.io/qt-6/qstring.html#at)(), and [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)().

### [QChar](https://doc.qt.io/qt-6/qchar.html) &QString::back()

Returns a reference to the last character in the string. Same as `operator[](size() - 1)`.

This function is provided for STL compatibility.

**Warning:** Calling this function on an empty string constitutes undefined behavior.

**See also** [front](https://doc.qt.io/qt-6/qstring.html#front)(), [at](https://doc.qt.io/qt-6/qstring.html#at)(), and [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)().

### [QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx) QString::begin()

Returns an [STL-style iterator](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) pointing to the first character in the string.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [constBegin](https://doc.qt.io/qt-6/qstring.html#constBegin)() and [end](https://doc.qt.io/qt-6/qstring.html#end)().

### [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) QString::begin() const

This function overloads begin().

### qsizetype QString::capacity() const

Returns the maximum number of characters that can be stored in the string without forcing a reallocation.

The sole purpose of this function is to provide a means of fine tuning [QString](https://doc.qt.io/qt-6/qstring.html)'s memory usage. In general, you will rarely ever need to call this function. If you want to know how many characters are in the string, call [size](https://doc.qt.io/qt-6/qstring.html#size)().

**Note:** a statically allocated string will report a capacity of 0, even if it's not empty.

**Note:** The free space position in the allocated memory block is undefined. In other words, one should not assume that the free memory is always located after the initialized elements.

**See also** [reserve](https://doc.qt.io/qt-6/qstring.html#reserve)() and [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)().

### [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) QString::cbegin() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) pointing to the first character in the string.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [begin](https://doc.qt.io/qt-6/qstring.html#begin)() and [cend](https://doc.qt.io/qt-6/qstring.html#cend)().

### [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) QString::cend() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) pointing just after the last character in the string.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [cbegin](https://doc.qt.io/qt-6/qstring.html#cbegin)() and [end](https://doc.qt.io/qt-6/qstring.html#end)().

### void QString::chop(qsizetype *n*)

Removes *n* characters from the end of the string.

If *n* is greater than or equal to [size](https://doc.qt.io/qt-6/qstring.html#size)(), the result is an empty string; if *n* is negative, it is equivalent to passing zero.

Example:

```
QString str("LOGOUT\r\n");
str.chop(2);
// str == "LOGOUT"
```

If you want to remove characters from the *beginning* of the string, use [remove](https://doc.qt.io/qt-6/qstring.html#remove)() instead.

**See also** [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)(), [resize](https://doc.qt.io/qt-6/qstring.html#resize)(), [remove](https://doc.qt.io/qt-6/qstring.html#remove)(), and [QStringView::chop](https://doc.qt.io/qt-6/qstringview.html#chop)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::chopped(qsizetype *len*) const

Returns a string that contains the [size](https://doc.qt.io/qt-6/qstring.html#size)() - *len* leftmost characters of this string.

**Note:** The behavior is undefined if *len* is negative or greater than [size](https://doc.qt.io/qt-6/qstring.html#size)().

**See also** [endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)(), [first](https://doc.qt.io/qt-6/qstring.html#first)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### void QString::clear()

Clears the contents of the string and makes it null.

**See also** [resize](https://doc.qt.io/qt-6/qstring.html#resize)() and [isNull](https://doc.qt.io/qt-6/qstring.html#isNull)().

### `[static noexcept]`int QString::compare(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

Compares *s1* with *s2* and returns an integer less than, equal to, or greater than zero if *s1* is less than, equal to, or greater than *s2*.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the comparison is case-sensitive; otherwise the comparison is case-insensitive.

Case sensitive comparison is based exclusively on the numeric Unicode values of the characters and is very fast, but is not what a human would expect. Consider sorting user-visible strings with [localeAwareCompare](https://doc.qt.io/qt-6/qstring.html#localeAwareCompare)().

```
int x = QString::compare("aUtO", "AuTo", Qt::CaseInsensitive);  // x == 0
int y = QString::compare("auto", "Car", Qt::CaseSensitive);     // y > 0
int z = QString::compare("auto", "Car", Qt::CaseInsensitive);   // z <  0
```

**Note:** This function treats null strings the same as empty strings, for more details see [Distinction Between Null and Empty Strings](https://doc.qt.io/qt-6/qstring.html#distinction-between-null-and-empty-strings).

**See also** [operator==](https://doc.qt.io/qt-6/qstring.html#operator-eq-eq-1)(), [operator< ](https://doc.qt.io/qt-6/qstring.html#operator-lt-1)(), [operator>](https://doc.qt.io/qt-6/qstring.html#operator-gt)(), and [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`int QString::compare(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads compare().

Lexically compares this string with the *other* string and returns an integer less than, equal to, or greater than zero if this string is less than, equal to, or greater than the other string.

Same as compare(*this, *other*, *cs*).

### `[noexcept]`int QString::compare([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *other*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads compare().

Same as compare(*this, *other*, *cs*).

### `[noexcept]`int QString::compare([QStringView](https://doc.qt.io/qt-6/qstringview.html) *s*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads compare().

Performs a comparison of this with *s*, using the case sensitivity setting *cs*.

### `[noexcept]`int QString::compare([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads compare().

Performs a comparison of this with *ch*, using the case sensitivity setting *cs*.

### `[static noexcept]`int QString::compare(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads compare().

Performs a comparison of *s1* and *s2*, using the case sensitivity setting *cs*.

### `[static noexcept]`int QString::compare([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads compare().

Performs a comparison of *s1* and *s2*, using the case sensitivity setting *cs*.

### `[static noexcept]`int QString::compare(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QStringView](https://doc.qt.io/qt-6/qstringview.html) *s2*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads compare().

### `[static noexcept]`int QString::compare([QStringView](https://doc.qt.io/qt-6/qstringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads compare().

### [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) QString::constBegin() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) pointing to the first character in the string.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [begin](https://doc.qt.io/qt-6/qstring.html#begin)() and [constEnd](https://doc.qt.io/qt-6/qstring.html#constEnd)().

### const [QChar](https://doc.qt.io/qt-6/qchar.html) *QString::constData() const

Returns a pointer to the data stored in the [QString](https://doc.qt.io/qt-6/qstring.html). The pointer can be used to access the characters that compose the string.

Note that the pointer remains valid only as long as the string is not modified.

**Note:** The returned string may not be '\0'-terminated. Use [size](https://doc.qt.io/qt-6/qstring.html#size)() to determine the length of the array.

**See also** [data](https://doc.qt.io/qt-6/qstring.html#data)(), [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)(), and [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)().

### [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) QString::constEnd() const

Returns a const [STL-style iterator](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) pointing just after the last character in the string.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [constBegin](https://doc.qt.io/qt-6/qstring.html#constBegin)() and [end](https://doc.qt.io/qt-6/qstring.html#end)().

### bool QString::contains(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns `true` if this string contains an occurrence of the string *str*; otherwise returns `false`.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString str = "Peter Pan";
str.contains("peter", Qt::CaseInsensitive);    // returns true
```

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)() and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### bool QString::contains([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads contains().

Returns `true` if this string contains an occurrence of the character *ch*; otherwise returns `false`.

### bool QString::contains([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads contains().

Returns `true` if this string contains an occurrence of the latin-1 string *str*; otherwise returns `false`.

### `[noexcept]`bool QString::contains([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads contains().

Returns `true` if this string contains an occurrence of the string view *str*; otherwise returns `false`.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)() and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### bool QString::contains(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) **rmatch* = nullptr) const

Returns `true` if the regular expression *re* matches somewhere in this string; otherwise returns `false`.

If the match is successful and *rmatch* is not `nullptr`, it also writes the results of the match into the [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) object pointed to by *rmatch*.

**See also** [QRegularExpression::match](https://doc.qt.io/qt-6/qregularexpression.html#match)().

### qsizetype QString::count(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns the number of (potentially overlapping) occurrences of the string *str* in this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**See also** [contains](https://doc.qt.io/qt-6/qstring.html#contains)() and [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)().

### qsizetype QString::count([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads count().

Returns the number of occurrences of character *ch* in the string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**See also** [contains](https://doc.qt.io/qt-6/qstring.html#contains)() and [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)().

### `[since 6.0]`qsizetype QString::count([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads count().

Returns the number of (potentially overlapping) occurrences of the string view *str* in this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

This function was introduced in Qt 6.0.

**See also** [contains](https://doc.qt.io/qt-6/qstring.html#contains)() and [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)().

### qsizetype QString::count(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*) const

This function overloads count().

Returns the number of times the regular expression *re* matches in the string.

For historical reasons, this function counts overlapping matches, so in the example below, there are four instances of "ana" or "ama":

```
QString str = "banana and panama";
str.count(QRegularExpression("a[nm]a"));    // returns 4
```

This behavior is different from simply iterating over the matches in the string using [QRegularExpressionMatchIterator](https://doc.qt.io/qt-6/qregularexpressionmatchiterator.html).

**See also** [QRegularExpression::globalMatch](https://doc.qt.io/qt-6/qregularexpression.html#globalMatch)().

### [QString::const_reverse_iterator](https://doc.qt.io/qt-6/qstring.html#const_reverse_iterator-typedef) QString::crbegin() const

Returns a const [STL-style](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) reverse iterator pointing to the first character in the string, in reverse order.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [begin](https://doc.qt.io/qt-6/qstring.html#begin)(), [rbegin](https://doc.qt.io/qt-6/qstring.html#rbegin)(), and [rend](https://doc.qt.io/qt-6/qstring.html#rend)().

### [QString::const_reverse_iterator](https://doc.qt.io/qt-6/qstring.html#const_reverse_iterator-typedef) QString::crend() const

Returns a const [STL-style](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) reverse iterator pointing just after the last character in the string, in reverse order.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [end](https://doc.qt.io/qt-6/qstring.html#end)(), [rend](https://doc.qt.io/qt-6/qstring.html#rend)(), and [rbegin](https://doc.qt.io/qt-6/qstring.html#rbegin)().

### [QChar](https://doc.qt.io/qt-6/qchar.html) *QString::data()

Returns a pointer to the data stored in the [QString](https://doc.qt.io/qt-6/qstring.html). The pointer can be used to access and modify the characters that compose the string.

Unlike [constData](https://doc.qt.io/qt-6/qstring.html#constData)() and [unicode](https://doc.qt.io/qt-6/qstring.html#unicode)(), the returned data is always '\0'-terminated.

Example:

```
QString str = "Hello world";
QChar *data = str.data();
while (!data->isNull()) {
    qDebug() < <  data->unicode();
    ++data;
}
```

Note that the pointer remains valid only as long as the string is not modified by other means. For read-only access, [constData](https://doc.qt.io/qt-6/qstring.html#constData)() is faster because it never causes a [deep copy](https://doc.qt.io/qt-6/implicit-sharing.html#deep-copy) to occur.

**See also** [constData](https://doc.qt.io/qt-6/qstring.html#constData)() and [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)().

### const [QChar](https://doc.qt.io/qt-6/qchar.html) *QString::data() const

This is an overloaded function.

**Note:** The returned string may not be '\0'-terminated. Use [size](https://doc.qt.io/qt-6/qstring.html#size)() to determine the length of the array.

**See also** [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)().

### [QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx) QString::end()

Returns an [STL-style iterator](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) pointing just after the last character in the string.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [begin](https://doc.qt.io/qt-6/qstring.html#begin)() and [constEnd](https://doc.qt.io/qt-6/qstring.html#constEnd)().

### [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) QString::end() const

This function overloads end().

### bool QString::endsWith(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns `true` if the string ends with *s*; otherwise returns `false`.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

```
QString str = "Bananas";
str.endsWith("anas");         // returns true
str.endsWith("pple");         // returns false
```

**See also** [startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith)().

### `[noexcept]`bool QString::endsWith([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads endsWith().

Returns `true` if the string ends with the string view *str*; otherwise returns `false`.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**See also** [startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith)().

### bool QString::endsWith([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads endsWith().

### bool QString::endsWith([QChar](https://doc.qt.io/qt-6/qchar.html) *c*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns `true` if the string ends with *c*; otherwise returns `false`.

This function overloads endsWith().

### `[since 6.1]`[QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx) QString::erase([QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) *first*, [QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) *last*)

Removes from the string the characters in the half-open range [ *first* , *last* ). Returns an iterator to the character immediately after the last erased character (i.e. the character referred to by *last* before the erase).

This function was introduced in Qt 6.1.

### `[since 6.5]`[QString::iterator](https://doc.qt.io/qt-6/qstring.html#iterator-typedefx) QString::erase([QString::const_iterator](https://doc.qt.io/qt-6/qstring.html#const_iterator-typedef) *it*)

Removes the character denoted by `it` from the string. Returns an iterator to the character immediately after the erased character.

```
QString c = "abcdefg";
auto it = c.erase(c.cbegin()); // c is now "bcdefg"; "it" points to "b"
```

This function was introduced in Qt 6.5.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::fill([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, qsizetype *size* = -1)

Sets every character in the string to character *ch*. If *size* is different from -1 (default), the string is resized to *size* beforehand.

Example:

```
QString str = "Berlin";
str.fill('z');
// str == "zzzzzz"

str.fill('A', 2);
// str == "AA"
```

**See also** [resize](https://doc.qt.io/qt-6/qstring.html#resize)().

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::first(qsizetype *n*) const

Returns a string that contains the first *n* characters of this string.

**Note:** The behavior is undefined when *n* <  0 or *n* > [size](https://doc.qt.io/qt-6/qstring.html#size)().

```
QString x = "Pineapple";
QString y = x.first(4);      // y == "Pine"
```

This function was introduced in Qt 6.0.

**See also** [last](https://doc.qt.io/qt-6/qstring.html#last)(), [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)(), [startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromCFString(CFStringRef *string*)

Constructs a new [QString](https://doc.qt.io/qt-6/qstring.html) containing a copy of the *string* CFString.

**Note:** this function is only available on macOS and iOS.

### `[static, since 6.6]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromEcmaString(emscripten::val *jsString*)

Converts the [ECMAScript string](https://262.ecma-international.org/#sec-string-object) *jsString* to [QString](https://doc.qt.io/qt-6/qstring.html). Behavior is undefined if the provided parameter is not a string.

This function was introduced in Qt 6.6.

**See also** [toEcmaString](https://doc.qt.io/qt-6/qstring.html#toEcmaString)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromLatin1(const char **str*, qsizetype *size*)

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the first *size* characters of the Latin-1 string *str*.

If *size* is `-1`, `strlen(str)` is used instead.

**See also** [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), and [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)().

### `[static, since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromLatin1([QByteArrayView](https://doc.qt.io/qt-6/qbytearrayview.html) *str*)

This is an overloaded function.

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the Latin-1 string *str*.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000).

This function was introduced in Qt 6.0.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromLatin1(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*str*)

This is an overloaded function.

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the Latin-1 string *str*.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000). This behavior is different from Qt 5.x.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromLocal8Bit(const char **str*, qsizetype *size*)

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the first *size* characters of the 8-bit string *str*.

If *size* is `-1`, `strlen(str)` is used instead.

On Unix systems this is equivalent to [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(). Note that on Apple systems this function does not take `\l{https://developer.apple.com/documentation/foundation/nsstring/1410091-defaultcstringencoding?language=objc}` {NSString.defaultCStringEncoding} or `\l{https://developer.apple.com/documentation/corefoundation/1541720-cfstringgetsystemencoding?language=objc}` {CFStringGetSystemEncoding()} into account, as these functions typically return the legacy "Western (Mac OS Roman)" encoding, which should not be used on modern Apple operating systems. On Windows the system's current code page is used.

**See also** [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), and [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

### `[static, since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromLocal8Bit([QByteArrayView](https://doc.qt.io/qt-6/qbytearrayview.html) *str*)

This is an overloaded function.

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the 8-bit string *str*.

On Unix systems this is equivalent to [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(). Note that on Apple systems this function does not take `\l{https://developer.apple.com/documentation/foundation/nsstring/1410091-defaultcstringencoding?language=objc}` {NSString.defaultCStringEncoding} or `\l{https://developer.apple.com/documentation/corefoundation/1541720-cfstringgetsystemencoding?language=objc}` {CFStringGetSystemEncoding()} into account, as these functions typically return the legacy "Western (Mac OS Roman)" encoding, which should not be used on modern Apple operating systems. On Windows the system's current code page is used.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000).

This function was introduced in Qt 6.0.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromLocal8Bit(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*str*)

This is an overloaded function.

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the 8-bit string *str*.

On Unix systems this is equivalent to [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(). Note that on Apple systems this function does not take `\l{https://developer.apple.com/documentation/foundation/nsstring/1410091-defaultcstringencoding?language=objc}` {NSString.defaultCStringEncoding} or `\l{https://developer.apple.com/documentation/corefoundation/1541720-cfstringgetsystemencoding?language=objc}` {CFStringGetSystemEncoding()} into account, as these functions typically return the legacy "Western (Mac OS Roman)" encoding, which should not be used on modern Apple operating systems. On Windows the system's current code page is used.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000). This behavior is different from Qt 5.x.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromNSString(const NSString **string*)

Constructs a new [QString](https://doc.qt.io/qt-6/qstring.html) containing a copy of the *string* NSString.

**Note:** this function is only available on macOS and iOS.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromRawData(const [QChar](https://doc.qt.io/qt-6/qchar.html) **unicode*, qsizetype *size*)

Constructs a [QString](https://doc.qt.io/qt-6/qstring.html) that uses the first *size* Unicode characters in the array *unicode*. The data in *unicode* is *not* copied. The caller must be able to guarantee that *unicode* will not be deleted or modified as long as the [QString](https://doc.qt.io/qt-6/qstring.html) (or an unmodified copy of it) exists.

Any attempts to modify the [QString](https://doc.qt.io/qt-6/qstring.html) or copies of it will cause it to create a deep copy of the data, ensuring that the raw data isn't modified.

Here is an example of how we can use a [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) on raw data in memory without requiring to copy the data into a [QString](https://doc.qt.io/qt-6/qstring.html):

```
QRegularExpression pattern("\u00A4");
static const QChar unicode[] = {
        0x005A, 0x007F, 0x00A4, 0x0060,
        0x1009, 0x0020, 0x0020};
qsizetype size = sizeof(unicode) / sizeof(QChar);

QString str = QString::fromRawData(unicode, size);
if (str.contains(pattern) {
    // ...
}
```

**Warning:** A string created with fromRawData() is *not* '\0'-terminated, unless the raw data contains a '\0' character at position *size*. This means [unicode](https://doc.qt.io/qt-6/qstring.html#unicode)() will *not* return a '\0'-terminated string (although [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)() does, at the cost of copying the raw data).

**See also** [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)() and [setRawData](https://doc.qt.io/qt-6/qstring.html#setRawData)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromStdString(const std::string &*str*)

Returns a copy of the *str* string. The given string is assumed to be encoded in UTF-8, and is converted to [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

**See also** [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), and [QByteArray::fromStdString](https://doc.qt.io/qt-6/qbytearray.html#fromStdString)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromStdU16String(const std::u16string &*str*)

Returns a copy of the *str* string. The given string is assumed to be encoded in UTF-16, and is converted to [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)() function.

**See also** [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)(), [fromStdWString](https://doc.qt.io/qt-6/qstring.html#fromStdWString)(), and [fromStdU32String](https://doc.qt.io/qt-6/qstring.html#fromStdU32String)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromStdU32String(const std::u32string &*str*)

Returns a copy of the *str* string. The given string is assumed to be encoded in UCS-4, and is converted to [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUcs4](https://doc.qt.io/qt-6/qstring.html#fromUcs4)() function.

**See also** [fromUcs4](https://doc.qt.io/qt-6/qstring.html#fromUcs4)(), [fromStdWString](https://doc.qt.io/qt-6/qstring.html#fromStdWString)(), and [fromStdU16String](https://doc.qt.io/qt-6/qstring.html#fromStdU16String)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromStdWString(const std::wstring &*str*)

Returns a copy of the *str* string. The given string is assumed to be encoded in utf16 if the size of wchar_t is 2 bytes (e.g. on windows) and ucs4 if the size of wchar_t is 4 bytes (most Unix systems).

**See also** [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)(), [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), [fromUcs4](https://doc.qt.io/qt-6/qstring.html#fromUcs4)(), [fromStdU16String](https://doc.qt.io/qt-6/qstring.html#fromStdU16String)(), and [fromStdU32String](https://doc.qt.io/qt-6/qstring.html#fromStdU32String)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUcs4(const char32_t **unicode*, qsizetype *size* = -1)

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the first *size* characters of the Unicode string *unicode* (ISO-10646-UCS-4 encoded).

If *size* is -1 (default), *unicode* must be \0'-terminated.

**See also** [toUcs4](https://doc.qt.io/qt-6/qstring.html#toUcs4)(), [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)(), [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)(), [setUtf16](https://doc.qt.io/qt-6/qstring.html#setUtf16)(), [fromWCharArray](https://doc.qt.io/qt-6/qstring.html#fromWCharArray)(), and [fromStdU32String](https://doc.qt.io/qt-6/qstring.html#fromStdU32String)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUtf8(const char **str*, qsizetype *size*)

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the first *size* bytes of the UTF-8 string *str*.

If *size* is `-1`, `strlen(str)` is used instead.

UTF-8 is a Unicode codec and can represent all characters in a Unicode string like [QString](https://doc.qt.io/qt-6/qstring.html). However, invalid sequences are possible with UTF-8 and, if any such are found, they will be replaced with one or more "replacement characters", or suppressed. These include non-Unicode sequences, non-characters, overlong sequences or surrogate codepoints encoded into UTF-8.

This function can be used to process incoming data incrementally as long as all UTF-8 characters are terminated within the incoming data. Any unterminated characters at the end of the string will be replaced or suppressed. In order to do stateful decoding, please use [QStringDecoder](https://doc.qt.io/qt-6/qstringdecoder.html).

**See also** [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), and [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)().

### `[static, since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUtf8([QByteArrayView](https://doc.qt.io/qt-6/qbytearrayview.html) *str*)

This is an overloaded function.

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the UTF-8 string *str*.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000).

This function was introduced in Qt 6.0.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUtf8(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*str*)

This is an overloaded function.

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the UTF-8 string *str*.

**Note:** : any null ('\0') bytes in the byte array will be included in this string, converted to Unicode null characters (U+0000). This behavior is different from Qt 5.x.

### `[static, since 6.1]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUtf8(const char8_t **str*)

This is an overloaded function.

This overload is only available when compiling in C++20 mode.

This function was introduced in Qt 6.1.

### `[static, since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUtf8(const char8_t **str*, qsizetype *size*)

This is an overloaded function.

This overload is only available when compiling in C++20 mode.

This function was introduced in Qt 6.0.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromUtf16(const char16_t **unicode*, qsizetype *size* = -1)

Returns a [QString](https://doc.qt.io/qt-6/qstring.html) initialized with the first *size* characters of the Unicode string *unicode* (ISO-10646-UTF-16 encoded).

If *size* is -1 (default), *unicode* must be \0'-terminated.

This function checks for a Byte Order Mark (BOM). If it is missing, host byte order is assumed.

This function is slow compared to the other Unicode conversions. Use [QString](https://doc.qt.io/qt-6/qstring.html)(const [QChar](https://doc.qt.io/qt-6/qchar.html) *, qsizetype) or [QString](https://doc.qt.io/qt-6/qstring.html)(const [QChar](https://doc.qt.io/qt-6/qchar.html) *) if possible.

[QString](https://doc.qt.io/qt-6/qstring.html) makes a deep copy of the Unicode data.

**See also** [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)(), [setUtf16](https://doc.qt.io/qt-6/qstring.html#setUtf16)(), and [fromStdU16String](https://doc.qt.io/qt-6/qstring.html#fromStdU16String)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::fromWCharArray(const wchar_t **string*, qsizetype *size* = -1)

Returns a copy of the *string*, where the encoding of *string* depends on the size of wchar. If wchar is 4 bytes, the *string* is interpreted as UCS-4, if wchar is 2 bytes it is interpreted as UTF-16.

If *size* is -1 (default), the *string* must be '\0'-terminated.

**See also** [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)(), [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), [fromUcs4](https://doc.qt.io/qt-6/qstring.html#fromUcs4)(), and [fromStdWString](https://doc.qt.io/qt-6/qstring.html#fromStdWString)().

### [QChar](https://doc.qt.io/qt-6/qchar.html) QString::front() const

Returns the first character in the string. Same as `at(0)`.

This function is provided for STL compatibility.

**Warning:** Calling this function on an empty string constitutes undefined behavior.

**See also** [back](https://doc.qt.io/qt-6/qstring.html#back)(), [at](https://doc.qt.io/qt-6/qstring.html#at)(), and [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)().

### [QChar](https://doc.qt.io/qt-6/qchar.html) &QString::front()

Returns a reference to the first character in the string. Same as `operator[](0)`.

This function is provided for STL compatibility.

**Warning:** Calling this function on an empty string constitutes undefined behavior.

**See also** [back](https://doc.qt.io/qt-6/qstring.html#back)(), [at](https://doc.qt.io/qt-6/qstring.html#at)(), and [operator[\]](https://doc.qt.io/qt-6/qstring.html#operator-5b-5d)().

### qsizetype QString::indexOf([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*, qsizetype *from* = 0, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns the index position of the first occurrence of the Latin-1 string viewed by *str* in this string, searching forward from index position *from*. Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString x = "sticky question";
QString y = "sti";
x.indexOf(y);               // returns 0
x.indexOf(y, 1);            // returns 10
x.indexOf(y, 10);           // returns 10
x.indexOf(y, 11);           // returns -1
```

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

**See also** [lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### qsizetype QString::indexOf([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, qsizetype *from* = 0, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads indexOf().

Returns the index position of the first occurrence of the character *ch* in this string, searching forward from index position *from*. Returns -1 if *ch* is not found.

### qsizetype QString::indexOf(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*, qsizetype *from* = 0, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns the index position of the first occurrence of the string *str* in this string, searching forward from index position *from*. Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString x = "sticky question";
QString y = "sti";
x.indexOf(y);               // returns 0
x.indexOf(y, 1);            // returns 10
x.indexOf(y, 10);           // returns 10
x.indexOf(y, 11);           // returns -1
```

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

**See also** [lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### `[noexcept]`qsizetype QString::indexOf([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, qsizetype *from* = 0, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads indexOf().

Returns the index position of the first occurrence of the string view *str* in this string, searching forward from index position *from*. Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

**See also** [QStringView::indexOf](https://doc.qt.io/qt-6/qstringview.html#indexOf)(), [lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### qsizetype QString::indexOf(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, qsizetype *from* = 0, [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) **rmatch* = nullptr) const

Returns the index position of the first match of the regular expression *re* in the string, searching forward from index position *from*. Returns -1 if *re* didn't match anywhere.

If the match is successful and *rmatch* is not `nullptr`, it also writes the results of the match into the [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) object pointed to by *rmatch*.

Example:

```
QString str = "the minimum";
str.indexOf(QRegularExpression("m[aeiou]"), 0);       // returns 4

QString str = "the minimum";
QRegularExpressionMatch match;
str.indexOf(QRegularExpression("m[aeiou]"), 0, &match);       // returns 4
// match.captured() == mi
```

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*)

Inserts the string *str* at the given index *position* and returns a reference to this string.

Example:

```
QString str = "Meal";
str.insert(1, QString("ontr"));
// str == "Montreal"
```

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *str*.

**See also** [append](https://doc.qt.io/qt-6/qstring.html#append)(), [prepend](https://doc.qt.io/qt-6/qstring.html#prepend)(), [replace](https://doc.qt.io/qt-6/qstring.html#replace)(), and [remove](https://doc.qt.io/qt-6/qstring.html#remove)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, [QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This function overloads insert().

Inserts *ch* at the given index *position* in the string.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *ch*.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, const [QChar](https://doc.qt.io/qt-6/qchar.html) **unicode*, qsizetype *size*)

This function overloads insert().

Inserts the first *size* characters of the [QChar](https://doc.qt.io/qt-6/qchar.html) array *unicode* at the given index *position* in the string.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *size* characters of the [QChar](https://doc.qt.io/qt-6/qchar.html) array *unicode*.

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, [QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*)

This function overloads insert().

Inserts the string view *str* at the given index *position* and returns a reference to this string.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *str*.

This function was introduced in Qt 6.0.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*)

This function overloads insert().

Inserts the Latin-1 string viewed by *str* at the given index *position*.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *str*.

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, [QUtf8StringView](https://doc.qt.io/qt-6/qutf8stringview.html) *str*)

This function overloads insert().

Inserts the UTF-8 string view *str* at the given index *position*.

**Note:** Inserting variable-width UTF-8-encoded string data is conceptually slower than inserting fixed-width string data such as UTF-16 ([QStringView](https://doc.qt.io/qt-6/qstringview.html)) or Latin-1 ([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html)) and should thus be used sparingly.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *str*.

This function was introduced in Qt 6.5.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, const char **str*)

This function overloads insert().

Inserts the C string *str* at the given index *position* and returns a reference to this string.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *str*.

This function is not available when [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) is defined.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::insert(qsizetype *position*, const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*str*)

This function overloads insert().

Interprets the contents of *str* as UTF-8, inserts the Unicode string it encodes at the given index *position* and returns a reference to this string.

This string grows to accommodate the insertion. If *position* is beyond the end of the string, space characters are appended to the string to reach this *position*, followed by *str*.

This function is not available when [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) is defined.

### `[noexcept]`bool QString::isEmpty() const

Returns `true` if the string has no characters; otherwise returns `false`.

Example:

```
QString().isEmpty();            // returns true
QString("").isEmpty();          // returns true
QString("x").isEmpty();         // returns false
QString("abc").isEmpty();       // returns false
```

**See also** [size](https://doc.qt.io/qt-6/qstring.html#size)().

### bool QString::isLower() const

Returns `true` if the string is lowercase, that is, it's identical to its [toLower](https://doc.qt.io/qt-6/qstring.html#toLower)() folding.

Note that this does *not* mean that the string does not contain uppercase letters (some uppercase letters do not have a lowercase folding; they are left unchanged by [toLower](https://doc.qt.io/qt-6/qstring.html#toLower)()). For more information, refer to the Unicode standard, section 3.13.

**See also** [QChar::toLower](https://doc.qt.io/qt-6/qchar.html#toLower)() and [isUpper](https://doc.qt.io/qt-6/qstring.html#isUpper)().

### bool QString::isNull() const

Returns `true` if this string is null; otherwise returns `false`.

Example:

```
QString().isNull();             // returns true
QString("").isNull();           // returns false
QString("abc").isNull();        // returns false
```

Qt makes a distinction between null strings and empty strings for historical reasons. For most applications, what matters is whether or not a string contains any data, and this can be determined using the [isEmpty](https://doc.qt.io/qt-6/qstring.html#isEmpty)() function.

**See also** [isEmpty](https://doc.qt.io/qt-6/qstring.html#isEmpty)().

### bool QString::isRightToLeft() const

Returns `true` if the string is read right to left.

**See also** [QStringView::isRightToLeft](https://doc.qt.io/qt-6/qstringview.html#isRightToLeft)().

### bool QString::isUpper() const

Returns `true` if the string is uppercase, that is, it's identical to its [toUpper](https://doc.qt.io/qt-6/qstring.html#toUpper)() folding.

Note that this does *not* mean that the string does not contain lowercase letters (some lowercase letters do not have a uppercase folding; they are left unchanged by [toUpper](https://doc.qt.io/qt-6/qstring.html#toUpper)()). For more information, refer to the Unicode standard, section 3.13.

**See also** [QChar::toUpper](https://doc.qt.io/qt-6/qchar.html#toUpper)() and [isLower](https://doc.qt.io/qt-6/qstring.html#isLower)().

### `[noexcept]`bool QString::isValidUtf16() const

Returns `true` if the string contains valid UTF-16 encoded data, or `false` otherwise.

Note that this function does not perform any special validation of the data; it merely checks if it can be successfully decoded from UTF-16. The data is assumed to be in host byte order; the presence of a BOM is meaningless.

**See also** [QStringView::isValidUtf16](https://doc.qt.io/qt-6/qstringview.html#isValidUtf16)().

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::last(qsizetype *n*) const

Returns the string that contains the last *n* characters of this string.

**Note:** The behavior is undefined when *n* <  0 or *n* > [size](https://doc.qt.io/qt-6/qstring.html#size)().

```
QString x = "Pineapple";
QString y = x.last(5);      // y == "apple"
```

This function was introduced in Qt 6.0.

**See also** [first](https://doc.qt.io/qt-6/qstring.html#first)(), [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)(), [endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### qsizetype QString::lastIndexOf(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*, qsizetype *from*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns the index position of the last occurrence of the string *str* in this string, searching backward from index position *from*.

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString x = "crazy azimuths";
QString y = "az";
x.lastIndexOf(y);           // returns 6
x.lastIndexOf(y, 6);        // returns 6
x.lastIndexOf(y, 5);        // returns 2
x.lastIndexOf(y, 1);        // returns -1
```

**Note:** When searching for a 0-length *str*, the match at the end of the data is excluded from the search by a negative *from*, even though `-1` is normally thought of as searching from the end of the string: the match at the end is *after* the last character, so it is excluded. To include such a final empty match, either give a positive value for *from* or omit the *from* parameter entirely.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### `[noexcept, since 6.3]`qsizetype QString::lastIndexOf([QChar](https://doc.qt.io/qt-6/qchar.html) *c*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

This function was introduced in Qt 6.3.

### qsizetype QString::lastIndexOf([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, qsizetype *from*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

Returns the index position of the last occurrence of the character *ch* in this string, searching backward from index position *from*.

### `[since 6.2]`qsizetype QString::lastIndexOf([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

Returns the index position of the last occurrence of the string *str* in this string. Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString x = "crazy azimuths";
QString y = "az";
x.lastIndexOf(y);           // returns 6
x.lastIndexOf(y, 6);        // returns 6
x.lastIndexOf(y, 5);        // returns 2
x.lastIndexOf(y, 1);        // returns -1
```

This function was introduced in Qt 6.2.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### qsizetype QString::lastIndexOf([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*, qsizetype *from*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

Returns the index position of the last occurrence of the Latin-1 string viewed by *str* in this string, searching backward from index position *from*.

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString x = "crazy azimuths";
QString y = "az";
x.lastIndexOf(y);           // returns 6
x.lastIndexOf(y, 6);        // returns 6
x.lastIndexOf(y, 5);        // returns 2
x.lastIndexOf(y, 1);        // returns -1
```

**Note:** When searching for a 0-length *str*, the match at the end of the data is excluded from the search by a negative *from*, even though `-1` is normally thought of as searching from the end of the string: the match at the end is *after* the last character, so it is excluded. To include such a final empty match, either give a positive value for *from* or omit the *from* parameter entirely.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### `[since 6.2]`qsizetype QString::lastIndexOf(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

Returns the index position of the last occurrence of the string *str* in this string. Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString x = "crazy azimuths";
QString y = "az";
x.lastIndexOf(y);           // returns 6
x.lastIndexOf(y, 6);        // returns 6
x.lastIndexOf(y, 5);        // returns 2
x.lastIndexOf(y, 1);        // returns -1
```

This function was introduced in Qt 6.2.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### `[noexcept, since 6.2]`qsizetype QString::lastIndexOf([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

Returns the index position of the last occurrence of the string view *str* in this string. Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

This function was introduced in Qt 6.2.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### `[noexcept]`qsizetype QString::lastIndexOf([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, qsizetype *from*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads lastIndexOf().

Returns the index position of the last occurrence of the string view *str* in this string, searching backward from index position *from*.

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

Returns -1 if *str* is not found.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**Note:** When searching for a 0-length *str*, the match at the end of the data is excluded from the search by a negative *from*, even though `-1` is normally thought of as searching from the end of the string: the match at the end is *after* the last character, so it is excluded. To include such a final empty match, either give a positive value for *from* or omit the *from* parameter entirely.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [contains](https://doc.qt.io/qt-6/qstring.html#contains)(), and [count](https://doc.qt.io/qt-6/qstring-obsolete.html#count-1)().

### `[since 6.2]`qsizetype QString::lastIndexOf(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) **rmatch* = nullptr) const

This function overloads lastIndexOf().

Returns the index position of the last match of the regular expression *re* in the string. Returns -1 if *re* didn't match anywhere.

If the match is successful and *rmatch* is not `nullptr`, it also writes the results of the match into the [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) object pointed to by *rmatch*.

Example:

```
QString str = "the minimum";
str.lastIndexOf(QRegularExpression("m[aeiou]"));      // returns 8

QString str = "the minimum";
QRegularExpressionMatch match;
str.lastIndexOf(QRegularExpression("m[aeiou]"), -1, &match);      // returns 8
// match.captured() == mu
```

**Note:** Due to how the regular expression matching algorithm works, this function will actually match repeatedly from the beginning of the string until the end of the string is reached.

This function was introduced in Qt 6.2.

### qsizetype QString::lastIndexOf(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, qsizetype *from*, [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) **rmatch* = nullptr) const

Returns the index position of the last match of the regular expression *re* in the string, which starts before the index position *from*.

If *from* is -1, the search starts at the last character; if it is -2, at the next to last character and so on.

Returns -1 if *re* didn't match anywhere.

If the match is successful and *rmatch* is not `nullptr`, it also writes the results of the match into the [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html) object pointed to by *rmatch*.

Example:

```
QString str = "the minimum";
str.lastIndexOf(QRegularExpression("m[aeiou]"));      // returns 8

QString str = "the minimum";
QRegularExpressionMatch match;
str.lastIndexOf(QRegularExpression("m[aeiou]"), -1, &match);      // returns 8
// match.captured() == mu
```

**Note:** Due to how the regular expression matching algorithm works, this function will actually match repeatedly from the beginning of the string until the position *from* is reached.

**Note:** When searching for a regular expression *re* that may match 0 characters, the match at the end of the data is excluded from the search by a negative *from*, even though `-1` is normally thought of as searching from the end of the string: the match at the end is *after* the last character, so it is excluded. To include such a final empty match, either give a positive value for *from* or omit the *from* parameter entirely.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::left(qsizetype *n*) const

Returns a substring that contains the *n* leftmost characters of the string.

If you know that *n* cannot be out of bounds, use [first](https://doc.qt.io/qt-6/qstring.html#first)() instead in new code, because it is faster.

The entire string is returned if *n* is greater than or equal to [size](https://doc.qt.io/qt-6/qstring.html#size)(), or less than zero.

**See also** [first](https://doc.qt.io/qt-6/qstring.html#first)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), [startsWith](https://doc.qt.io/qt-6/qstring.html#startsWith)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::leftJustified(qsizetype *width*, [QChar](https://doc.qt.io/qt-6/qchar.html) *fill* = u' ', bool *truncate* = false) const

Returns a string of size *width* that contains this string padded by the *fill* character.

If *truncate* is `false` and the [size](https://doc.qt.io/qt-6/qstring.html#size)() of the string is more than *width*, then the returned string is a copy of the string.

```
QString s = "apple";
QString t = s.leftJustified(8, '.');    // t == "apple..."
```

If *truncate* is `true` and the [size](https://doc.qt.io/qt-6/qstring.html#size)() of the string is more than *width*, then any characters in a copy of the string after position *width* are removed, and the copy is returned.

```
QString str = "Pineapple";
str = str.leftJustified(5, '.', true);    // str == "Pinea"
```

**See also** [rightJustified](https://doc.qt.io/qt-6/qstring.html#rightJustified)().

### `[noexcept]`qsizetype QString::length() const

Returns the number of characters in this string. Equivalent to [size](https://doc.qt.io/qt-6/qstring.html#size)().

**See also** [resize](https://doc.qt.io/qt-6/qstring.html#resize)().

### `[static]`int QString::localeAwareCompare(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Compares *s1* with *s2* and returns an integer less than, equal to, or greater than zero if *s1* is less than, equal to, or greater than *s2*.

The comparison is performed in a locale- and also platform-dependent manner. Use this function to present sorted lists of strings to the user.

**See also** [compare](https://doc.qt.io/qt-6/qstring.html#compare)(), [QLocale](https://doc.qt.io/qt-6/qlocale.html), and [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### int QString::localeAwareCompare(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*) const

This function overloads localeAwareCompare().

Compares this string with the *other* string and returns an integer less than, equal to, or greater than zero if this string is less than, equal to, or greater than the *other* string.

The comparison is performed in a locale- and also platform-dependent manner. Use this function to present sorted lists of strings to the user.

Same as `localeAwareCompare(*this, other)`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[since 6.0]`int QString::localeAwareCompare([QStringView](https://doc.qt.io/qt-6/qstringview.html) *other*) const

This function overloads localeAwareCompare().

Compares this string with the *other* string and returns an integer less than, equal to, or greater than zero if this string is less than, equal to, or greater than the *other* string.

The comparison is performed in a locale- and also platform-dependent manner. Use this function to present sorted lists of strings to the user.

Same as `localeAwareCompare(*this, other)`.

This function was introduced in Qt 6.0.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[static, since 6.0]`int QString::localeAwareCompare([QStringView](https://doc.qt.io/qt-6/qstringview.html) *s1*, [QStringView](https://doc.qt.io/qt-6/qstringview.html) *s2*)

This function overloads localeAwareCompare().

Compares *s1* with *s2* and returns an integer less than, equal to, or greater than zero if *s1* is less than, equal to, or greater than *s2*.

The comparison is performed in a locale- and also platform-dependent manner. Use this function to present sorted lists of strings to the user.

This function was introduced in Qt 6.0.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::mid(qsizetype *position*, qsizetype *n* = -1) const

Returns a string that contains *n* characters of this string, starting at the specified *position* index.

If you know that *position* and *n* cannot be out of bounds, use [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)() instead in new code, because it is faster.

Returns a null string if the *position* index exceeds the length of the string. If there are less than *n* characters available in the string starting at the given *position*, or if *n* is -1 (default), the function returns all characters that are available from the specified *position*.

**See also** [first](https://doc.qt.io/qt-6/qstring.html#first)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::normalized([QString::NormalizationForm](https://doc.qt.io/qt-6/qstring.html#NormalizationForm-enum) *mode*, [QChar::UnicodeVersion](https://doc.qt.io/qt-6/qchar.html#UnicodeVersion-enum) *version* = QChar::Unicode_Unassigned) const

Returns the string in the given Unicode normalization *mode*, according to the given *version* of the Unicode standard.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number(long *n*, int *base* = 10)

Returns a string equivalent of the number *n* according to the specified *base*.

The base is 10 by default and must be between 2 and 36. For bases other than 10, *n* is treated as an unsigned integer.

The formatting always uses [QLocale::C](https://doc.qt.io/qt-6/qlocale.html#Language-enum), i.e., English/UnitedStates. To get a localized string representation of a number, use [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString)() with the appropriate locale.

```
long a = 63;
QString s = QString::number(a, 16);             // s == "3f"
QString t = QString::number(a, 16).toUpper();     // t == "3F"
```

**See also** [setNum](https://doc.qt.io/qt-6/qstring.html#setNum)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number(int *n*, int *base* = 10)

This is an overloaded function.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number([uint](https://doc.qt.io/qt-6/qttypes.html#uint-typedef) *n*, int *base* = 10)

This is an overloaded function.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number([ulong](https://doc.qt.io/qt-6/qttypes.html#ulong-typedef) *n*, int *base* = 10)

This is an overloaded function.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number([qlonglong](https://doc.qt.io/qt-6/qttypes.html#qlonglong-typedef) *n*, int *base* = 10)

This is an overloaded function.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number([qulonglong](https://doc.qt.io/qt-6/qttypes.html#qulonglong-typedef) *n*, int *base* = 10)

This is an overloaded function.

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::number(double *n*, char *format* = 'g', int *precision* = 6)

Returns a string representing the floating-point number *n*.

Returns a string that represents *n*, formatted according to the specified *format* and *precision*.

For formats with an exponent, the exponent will show its sign and have at least two digits, left-padding the exponent with zero if needed.

**See also** [setNum](https://doc.qt.io/qt-6/qstring.html#setNum)(), [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString)(), [QLocale::FloatingPointPrecisionOption](https://doc.qt.io/qt-6/qlocale.html#FloatingPointPrecisionOption-enum), and [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*)

Prepends the string *str* to the beginning of this string and returns a reference to this string.

This operation is typically very fast ([constant time](https://doc.qt.io/qt-6/containers.html#constant-time)), because [QString](https://doc.qt.io/qt-6/qstring.html) preallocates extra space at the beginning of the string data, so it can grow without reallocating the entire string each time.

Example:

```
QString x = "ship";
QString y = "air";
x.prepend(y);
// x == "airship"
```

**See also** [append](https://doc.qt.io/qt-6/qstring.html#append)() and [insert](https://doc.qt.io/qt-6/qstring.html#insert)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This function overloads prepend().

Prepends the character *ch* to this string.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend(const [QChar](https://doc.qt.io/qt-6/qchar.html) **str*, qsizetype *len*)

This function overloads prepend().

Prepends *len* characters from the [QChar](https://doc.qt.io/qt-6/qchar.html) array *str* to this string and returns a reference to this string.

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*)

This function overloads prepend().

Prepends the string view *str* to the beginning of this string and returns a reference to this string.

This function was introduced in Qt 6.0.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*)

This function overloads prepend().

Prepends the Latin-1 string viewed by *str* to this string.

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend([QUtf8StringView](https://doc.qt.io/qt-6/qutf8stringview.html) *str*)

This function overloads prepend().

Prepends the UTF-8 string view *str* to this string.

This function was introduced in Qt 6.5.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend(const char **str*)

This function overloads prepend().

Prepends the string *str* to this string. The const char pointer is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this function by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::prepend(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*ba*)

This function overloads prepend().

Prepends the byte array *ba* to this string. The byte array is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this function by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### void QString::push_back(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*)

This function is provided for STL compatibility, appending the given *other* string onto the end of this string. It is equivalent to `append(other)`.

**See also** [append](https://doc.qt.io/qt-6/qstring.html#append)().

### void QString::push_back([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This is an overloaded function.

Appends the given *ch* character onto the end of this string.

### void QString::push_front(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*)

This function is provided for STL compatibility, prepending the given *other* string to the beginning of this string. It is equivalent to `prepend(other)`.

**See also** [prepend](https://doc.qt.io/qt-6/qstring.html#prepend)().

### void QString::push_front([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This is an overloaded function.

Prepends the given *ch* character to the beginning of this string.

### [QString::reverse_iterator](https://doc.qt.io/qt-6/qstring.html#reverse_iterator-typedef) QString::rbegin()

Returns a [STL-style](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) reverse iterator pointing to the first character in the string, in reverse order.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [begin](https://doc.qt.io/qt-6/qstring.html#begin)(), [crbegin](https://doc.qt.io/qt-6/qstring.html#crbegin)(), and [rend](https://doc.qt.io/qt-6/qstring.html#rend)().

### [QString::const_reverse_iterator](https://doc.qt.io/qt-6/qstring.html#const_reverse_iterator-typedef) QString::rbegin() const

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::remove(qsizetype *position*, qsizetype *n*)

Removes *n* characters from the string, starting at the given *position* index, and returns a reference to the string.

If the specified *position* index is within the string, but *position* + *n* is beyond the end of the string, the string is truncated at the specified *position*.

If *n* is < = 0 nothing is changed.

```
QString s = "Montreal";
s.remove(1, 4);
// s == "Meal"
```

Element removal will preserve the string's capacity and not reduce the amount of allocated memory. To shed extra capacity and free as much memory as possible, call [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)() after the last change to the string's size.

**See also** [insert](https://doc.qt.io/qt-6/qstring.html#insert)() and [replace](https://doc.qt.io/qt-6/qstring.html#replace)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::remove([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

Removes every occurrence of the character *ch* in this string, and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString t = "Ali Baba";
t.remove(QChar('a'), Qt::CaseInsensitive);
// t == "li Bb"
```

This is the same as `replace(ch, "", cs)`.

Element removal will preserve the string's capacity and not reduce the amount of allocated memory. To shed extra capacity and free as much memory as possible, call [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)() after the last change to the string's size.

**See also** [replace](https://doc.qt.io/qt-6/qstring.html#replace)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::remove([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This is an overloaded function.

Removes every occurrence of the given Latin-1 string viewed by *str* from this string, and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

This is the same as `replace(str, "", cs)`.

Element removal will preserve the string's capacity and not reduce the amount of allocated memory. To shed extra capacity and free as much memory as possible, call [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)() after the last change to the string's size.

**See also** [replace](https://doc.qt.io/qt-6/qstring.html#replace)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::remove(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

Removes every occurrence of the given *str* string in this string, and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

This is the same as `replace(str, "", cs)`.

Element removal will preserve the string's capacity and not reduce the amount of allocated memory. To shed extra capacity and free as much memory as possible, call [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)() after the last change to the string's size.

**See also** [replace](https://doc.qt.io/qt-6/qstring.html#replace)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::remove(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*)

Removes every occurrence of the regular expression *re* in the string, and returns a reference to the string. For example:

```
QString r = "Telephone";
r.remove(QRegularExpression("[aeiou]."));
// r == "The"
```

Element removal will preserve the string's capacity and not reduce the amount of allocated memory. To shed extra capacity and free as much memory as possible, call [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)() after the last change to the string's size.

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)(), and [replace](https://doc.qt.io/qt-6/qstring.html#replace)().

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::removeAt(qsizetype *pos*)

Removes the character at index *pos*. If *pos* is out of bounds (i.e. *pos* >= [size](https://doc.qt.io/qt-6/qstring.html#size)()), this function does nothing.

This function was introduced in Qt 6.5.

**See also** [remove](https://doc.qt.io/qt-6/qstring.html#remove)().

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::removeFirst()

Removes the first character in this string. If the string is empty, this function does nothing.

This function was introduced in Qt 6.5.

**See also** [remove](https://doc.qt.io/qt-6/qstring.html#remove)().

### `[since 6.1]`template < typename Predicate> [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::removeIf(Predicate *pred*)

Removes all elements for which the predicate *pred* returns true from the string. Returns a reference to the string.

This function was introduced in Qt 6.1.

**See also** [remove](https://doc.qt.io/qt-6/qstring.html#remove)().

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::removeLast()

Removes the last character in this string. If the string is empty, this function does nothing.

This function was introduced in Qt 6.5.

**See also** [remove](https://doc.qt.io/qt-6/qstring.html#remove)().

### [QString::reverse_iterator](https://doc.qt.io/qt-6/qstring.html#reverse_iterator-typedef) QString::rend()

Returns a [STL-style](https://doc.qt.io/qt-6/containers.html#stl-style-iterators) reverse iterator pointing just after the last character in the string, in reverse order.

**Warning:** The returned iterator is invalidated on detachment or when the [QString](https://doc.qt.io/qt-6/qstring.html) is modified.

**See also** [end](https://doc.qt.io/qt-6/qstring.html#end)(), [crend](https://doc.qt.io/qt-6/qstring.html#crend)(), and [rbegin](https://doc.qt.io/qt-6/qstring.html#rbegin)().

### [QString::const_reverse_iterator](https://doc.qt.io/qt-6/qstring.html#const_reverse_iterator-typedef) QString::rend() const

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::repeated(qsizetype *times*) const

Returns a copy of this string repeated the specified number of *times*.

If *times* is less than 1, an empty string is returned.

Example:

```
QString str("ab");
str.repeated(4);            // returns "abababab"
```

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(qsizetype *position*, qsizetype *n*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*after*)

Replaces *n* characters beginning at index *position* with the string *after* and returns a reference to this string.

**Note:** If the specified *position* index is within the string, but *position* + *n* goes outside the strings range, then *n* will be adjusted to stop at the end of the string.

Example:

```
QString x = "Say yes!";
QString y = "no";
x.replace(4, 3, y);
// x == "Say no!"
```

**See also** [insert](https://doc.qt.io/qt-6/qstring.html#insert)() and [remove](https://doc.qt.io/qt-6/qstring.html#remove)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(qsizetype *position*, qsizetype *n*, [QChar](https://doc.qt.io/qt-6/qchar.html) *after*)

This function overloads replace().

Replaces *n* characters beginning at index *position* with the character *after* and returns a reference to this string.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(qsizetype *position*, qsizetype *n*, const [QChar](https://doc.qt.io/qt-6/qchar.html) **after*, qsizetype *alen*)

This function overloads replace().

Replaces *n* characters beginning at index *position* with the first *alen* characters of the [QChar](https://doc.qt.io/qt-6/qchar.html) array *after* and returns a reference to this string.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace([QChar](https://doc.qt.io/qt-6/qchar.html) *before*, [QChar](https://doc.qt.io/qt-6/qchar.html) *after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence of the character *before* with the character *after* and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(const [QChar](https://doc.qt.io/qt-6/qchar.html) **before*, qsizetype *blen*, const [QChar](https://doc.qt.io/qt-6/qchar.html) **after*, qsizetype *alen*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces each occurrence in this string of the first *blen* characters of *before* with the first *alen* characters of *after* and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *before*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence in this string of the Latin-1 string viewed by *before* with the Latin-1 string viewed by *after*, and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**Note:** The text is not rescanned after a replacement.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *before*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence in this string of the Latin-1 string viewed by *before* with the string *after*, and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**Note:** The text is not rescanned after a replacement.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*before*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence of the string *before* with the string *after* and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**Note:** The text is not rescanned after a replacement.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*before*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence of the string *before* with the string *after* and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

Example:

```
QString str = "colour behaviour flavour neighbour";
str.replace(QString("ou"), QString("o"));
// str == "color behavior flavor neighbor"
```

**Note:** The replacement text is not rescanned after it is inserted.

Example:

```
QString equis = "xxxxxx";
equis.replace("xx", "x");
// equis == "xxx"
```

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence of the character *ch* in the string with *after* and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace([QChar](https://doc.qt.io/qt-6/qchar.html) *c*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *after*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive)

This function overloads replace().

Replaces every occurrence of the character *c* with the string *after* and returns a reference to this string.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**Note:** The text is not rescanned after a replacement.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::replace(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*after*)

This function overloads replace().

Replaces every occurrence of the regular expression *re* in the string with *after*. Returns a reference to the string. For example:

```
QString s = "Banana";
s.replace(QRegularExpression("a[mn]"), "ox");
// s == "Boxoxa"
```

For regular expressions containing capturing groups, occurrences of **\1**, **\2**, ..., in *after* are replaced with the string captured by the corresponding capturing group.

```
QString t = "A < i>bon mot< /i>.";
t.replace(QRegularExpression("< i>([^< ]*)< /i>"), "\\emph{\\1}");
// t == "A \\emph{bon mot}."
```

**See also** [indexOf](https://doc.qt.io/qt-6/qstring.html#indexOf)(), [lastIndexOf](https://doc.qt.io/qt-6/qstring.html#lastIndexOf)(), [remove](https://doc.qt.io/qt-6/qstring.html#remove)(), [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html), and [QRegularExpressionMatch](https://doc.qt.io/qt-6/qregularexpressionmatch.html).

### void QString::reserve(qsizetype *size*)

Ensures the string has space for at least *size* characters.

If you know in advance how large the string will be, you can call this function to save repeated reallocation in the course of building it. This can improve performance when building a string incrementally. A long sequence of operations that add to a string may trigger several reallocations, the last of which may leave you with significantly more space than you really need, which is less efficient than doing a single allocation of the right size at the start.

If in doubt about how much space shall be needed, it is usually better to use an upper bound as *size*, or a high estimate of the most likely size, if a strict upper bound would be much bigger than this. If *size* is an underestimate, the string will grow as needed once the reserved size is exceeded, which may lead to a larger allocation than your best overestimate would have and will slow the operation that triggers it.

**Warning:** reserve() reserves memory but does not change the size of the string. Accessing data beyond the end of the string is undefined behavior. If you need to access memory beyond the current end of the string, use [resize](https://doc.qt.io/qt-6/qstring.html#resize)().

This function is useful for code that needs to build up a long string and wants to avoid repeated reallocation. In this example, we want to add to the string until some condition is `true`, and we're fairly sure that size is large enough to make a call to reserve() worthwhile:

```
QString result;
qsizetype maxSize;
bool condition;
QChar nextChar;

result.reserve(maxSize);

while (condition)
    result.append(nextChar);

result.squeeze();
```

**See also** [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)(), [capacity](https://doc.qt.io/qt-6/qstring.html#capacity)(), and [resize](https://doc.qt.io/qt-6/qstring.html#resize)().

### void QString::resize(qsizetype *size*)

Sets the size of the string to *size* characters.

If *size* is greater than the current size, the string is extended to make it *size* characters long with the extra characters added to the end. The new characters are uninitialized.

If *size* is less than the current size, characters beyond position *size* are excluded from the string.

**Note:** While resize() will grow the capacity if needed, it never shrinks capacity. To shed excess capacity, use [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)().

Example:

```
QString s = "Hello world";
s.resize(5);
// s == "Hello"

s.resize(8);
// s == "Hello???" (where ? stands for any character)
```

If you want to append a certain number of identical characters to the string, use the [resize](https://doc.qt.io/qt-6/qstring.html#resize-1)(qsizetype, QChar) overload.

If you want to expand the string so that it reaches a certain width and fill the new positions with a particular character, use the [leftJustified](https://doc.qt.io/qt-6/qstring.html#leftJustified)() function:

If *size* is negative, it is equivalent to passing zero.

```
QString r = "Hello";
r = r.leftJustified(10, ' ');
// r == "Hello     "
```

**See also** [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)(), [reserve](https://doc.qt.io/qt-6/qstring.html#reserve)(), and [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)().

### void QString::resize(qsizetype *newSize*, [QChar](https://doc.qt.io/qt-6/qchar.html) *fillChar*)

This is an overloaded function.

Unlike [resize](https://doc.qt.io/qt-6/qstring.html#resize)(qsizetype), this overload initializes the new characters to *fillChar*:

```
QString t = "Hello";
r.resize(t.size() + 10, 'X');
// t == "HelloXXXXXXXXXX"
```

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::right(qsizetype *n*) const

Returns a substring that contains the *n* rightmost characters of the string.

If you know that *n* cannot be out of bounds, use [last](https://doc.qt.io/qt-6/qstring.html#last)() instead in new code, because it is faster.

The entire string is returned if *n* is greater than or equal to [size](https://doc.qt.io/qt-6/qstring.html#size)(), or less than zero.

**See also** [endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), [first](https://doc.qt.io/qt-6/qstring.html#first)(), [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::rightJustified(qsizetype *width*, [QChar](https://doc.qt.io/qt-6/qchar.html) *fill* = u' ', bool *truncate* = false) const

Returns a string of [size](https://doc.qt.io/qt-6/qstring.html#size)() *width* that contains the *fill* character followed by the string. For example:

```
QString s = "apple";
QString t = s.rightJustified(8, '.');    // t == "...apple"
```

If *truncate* is `false` and the [size](https://doc.qt.io/qt-6/qstring.html#size)() of the string is more than *width*, then the returned string is a copy of the string.

If *truncate* is true and the [size](https://doc.qt.io/qt-6/qstring.html#size)() of the string is more than *width*, then the resulting string is truncated at position *width*.

```
QString str = "Pineapple";
str = str.rightJustified(5, '.', true);    // str == "Pinea"
```

**See also** [leftJustified](https://doc.qt.io/qt-6/qstring.html#leftJustified)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::section([QChar](https://doc.qt.io/qt-6/qchar.html) *sep*, qsizetype *start*, qsizetype *end* = -1, [QString::SectionFlags](https://doc.qt.io/qt-6/qstring.html#SectionFlag-enum) *flags* = SectionDefault) const

This function returns a section of the string.

This string is treated as a sequence of fields separated by the character, *sep*. The returned string consists of the fields from position *start* to position *end* inclusive. If *end* is not specified, all fields from position *start* to the end of the string are included. Fields are numbered 0, 1, 2, etc., counting from the left, and -1, -2, etc., counting from right to left.

The *flags* argument can be used to affect some aspects of the function's behavior, e.g. whether to be case sensitive, whether to skip empty fields and how to deal with leading and trailing separators; see [SectionFlags](https://doc.qt.io/qt-6/qstring.html#SectionFlag-enum).

```
QString str;
QString csv = "forename,middlename,surname,phone";
QString path = "/usr/local/bin/myapp"; // First field is empty
QString::SectionFlag flag = QString::SectionSkipEmpty;

str = csv.section(',', 2, 2);   // str == "surname"
str = path.section('/', 3, 4);  // str == "bin/myapp"
str = path.section('/', 3, 3, flag); // str == "myapp"
```

If *start* or *end* is negative, we count fields from the right of the string, the right-most field being -1, the one from right-most field being -2, and so on.

```
str = csv.section(',', -3, -2);  // str == "middlename,surname"
str = path.section('/', -1); // str == "myapp"
```

**See also** [split](https://doc.qt.io/qt-6/qstring.html#split)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::section(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*sep*, qsizetype *start*, qsizetype *end* = -1, [QString::SectionFlags](https://doc.qt.io/qt-6/qstring.html#SectionFlag-enum) *flags* = SectionDefault) const

This function overloads section().

```
QString str;
QString data = "forename**middlename**surname**phone";

str = data.section("**", 2, 2); // str == "surname"
str = data.section("**", -3, -2); // str == "middlename**surname"
```

**See also** [split](https://doc.qt.io/qt-6/qstring.html#split)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::section(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, qsizetype *start*, qsizetype *end* = -1, [QString::SectionFlags](https://doc.qt.io/qt-6/qstring.html#SectionFlag-enum) *flags* = SectionDefault) const

This function overloads section().

This string is treated as a sequence of fields separated by the regular expression, *re*.

```
QString line = "forename\tmiddlename  surname \t \t phone";
QRegularExpression sep("\\s+");
str = line.section(sep, 2, 2); // str == "surname"
str = line.section(sep, -3, -2); // str == "middlename  surname"
```

**Warning:** Using this [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) version is much more expensive than the overloaded string and character versions.

**See also** [split](https://doc.qt.io/qt-6/qstring.html#split)() and [simplified](https://doc.qt.io/qt-6/qstring.html#simplified)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum(int *n*, int *base* = 10)

Sets the string to the printed value of *n* in the specified *base*, and returns a reference to the string.

The base is 10 by default and must be between 2 and 36.

```
QString str;
str.setNum(1234);       // str == "1234"
```

The formatting always uses [QLocale::C](https://doc.qt.io/qt-6/qlocale.html#Language-enum), i.e., English/UnitedStates. To get a localized string representation of a number, use [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString)() with the appropriate locale.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum(short *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum([ushort](https://doc.qt.io/qt-6/qttypes.html#ushort-typedef) *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum([uint](https://doc.qt.io/qt-6/qttypes.html#uint-typedef) *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum(long *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum([ulong](https://doc.qt.io/qt-6/qttypes.html#ulong-typedef) *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum([qlonglong](https://doc.qt.io/qt-6/qttypes.html#qlonglong-typedef) *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum([qulonglong](https://doc.qt.io/qt-6/qttypes.html#qulonglong-typedef) *n*, int *base* = 10)

This is an overloaded function.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum(float *n*, char *format* = 'g', int *precision* = 6)

This is an overloaded function.

Sets the string to the printed value of *n*, formatted according to the given *format* and *precision*, and returns a reference to the string.

The formatting always uses [QLocale::C](https://doc.qt.io/qt-6/qlocale.html#Language-enum), i.e., English/UnitedStates. To get a localized string representation of a number, use [QLocale::toString](https://doc.qt.io/qt-6/qlocale.html#toString)() with the appropriate locale.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setNum(double *n*, char *format* = 'g', int *precision* = 6)

This is an overloaded function.

Sets the string to the printed value of *n*, formatted according to the given *format* and *precision*, and returns a reference to the string.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [QLocale::FloatingPointPrecisionOption](https://doc.qt.io/qt-6/qlocale.html#FloatingPointPrecisionOption-enum), and [Number Formats](https://doc.qt.io/qt-6/qstring.html#number-formats).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setRawData(const [QChar](https://doc.qt.io/qt-6/qchar.html) **unicode*, qsizetype *size*)

Resets the [QString](https://doc.qt.io/qt-6/qstring.html) to use the first *size* Unicode characters in the array *unicode*. The data in *unicode* is *not* copied. The caller must be able to guarantee that *unicode* will not be deleted or modified as long as the [QString](https://doc.qt.io/qt-6/qstring.html) (or an unmodified copy of it) exists.

This function can be used instead of [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)() to re-use existings [QString](https://doc.qt.io/qt-6/qstring.html) objects to save memory re-allocations.

**See also** [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setUnicode(const [QChar](https://doc.qt.io/qt-6/qchar.html) **unicode*, qsizetype *size*)

Resizes the string to *size* characters and copies *unicode* into the string.

If *unicode* is `nullptr`, nothing is copied, but the string is still resized to *size*.

**See also** [unicode](https://doc.qt.io/qt-6/qstring.html#unicode)() and [setUtf16](https://doc.qt.io/qt-6/qstring.html#setUtf16)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::setUtf16(const [ushort](https://doc.qt.io/qt-6/qttypes.html#ushort-typedef) **unicode*, qsizetype *size*)

Resizes the string to *size* characters and copies *unicode* into the string.

If *unicode* is `nullptr`, nothing is copied, but the string is still resized to *size*.

Note that unlike [fromUtf16](https://doc.qt.io/qt-6/qstring.html#fromUtf16)(), this function does not consider BOMs and possibly differing byte ordering.

**See also** [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)() and [setUnicode](https://doc.qt.io/qt-6/qstring.html#setUnicode)().

### void QString::shrink_to_fit()

This function is provided for STL compatibility. It is equivalent to [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)().

**See also** [squeeze](https://doc.qt.io/qt-6/qstring.html#squeeze)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::simplified() const

Returns a string that has whitespace removed from the start and the end, and that has each sequence of internal whitespace replaced with a single space.

Whitespace means any character for which [QChar::isSpace](https://doc.qt.io/qt-6/qchar.html#isSpace)() returns `true`. This includes the ASCII characters '\t', '\n', '\v', '\f', '\r', and ' '.

Example:

```
QString str = "  lots\t of\nwhitespace\r\n ";
str = str.simplified();
// str == "lots of whitespace";
```

**See also** [trimmed](https://doc.qt.io/qt-6/qstring.html#trimmed)().

### `[noexcept]`qsizetype QString::size() const

Returns the number of characters in this string.

The last character in the string is at position size() - 1.

Example:

```
QString str = "World";
qsizetype n = str.size();   // n == 5
str.data()[0];              // returns 'W'
str.data()[4];              // returns 'd'
```

**See also** [isEmpty](https://doc.qt.io/qt-6/qstring.html#isEmpty)() and [resize](https://doc.qt.io/qt-6/qstring.html#resize)().

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::sliced(qsizetype *pos*, qsizetype *n*) const

Returns a string that contains *n* characters of this string, starting at position *pos*.

**Note:** The behavior is undefined when *pos* <  0, *n* <  0, or *pos* + *n* > [size](https://doc.qt.io/qt-6/qstring.html#size)().

```
QString x = "Nine pineapples";
QString y = x.sliced(5, 4);            // y == "pine"
QString z = x.sliced(5);               // z == "pineapples"
```

This function was introduced in Qt 6.0.

**See also** [first](https://doc.qt.io/qt-6/qstring.html#first)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::sliced(qsizetype *pos*) const

This is an overloaded function.

Returns a string that contains the portion of this string starting at position *pos* and extending to its end.

**Note:** The behavior is undefined when *pos* <  0 or *pos* > [size](https://doc.qt.io/qt-6/qstring.html#size)().

This function was introduced in Qt 6.0.

**See also** [first](https://doc.qt.io/qt-6/qstring.html#first)(), [last](https://doc.qt.io/qt-6/qstring.html#last)(), [sliced](https://doc.qt.io/qt-6/qstring.html#sliced)(), [chopped](https://doc.qt.io/qt-6/qstring.html#chopped)(), [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), and [truncate](https://doc.qt.io/qt-6/qstring.html#truncate)().

### [QStringList](https://doc.qt.io/qt-6/qstringlist.html) QString::split(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*sep*, [Qt::SplitBehavior](https://doc.qt.io/qt-6/qt.html#SplitBehaviorFlags-enum) *behavior* = Qt::KeepEmptyParts, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Splits the string into substrings wherever *sep* occurs, and returns the list of those strings. If *sep* does not match anywhere in the string, split() returns a single-element list containing this string.

*cs* specifies whether *sep* should be matched case sensitively or case insensitively.

If *behavior* is [Qt::SkipEmptyParts](https://doc.qt.io/qt-6/qt.html#SplitBehaviorFlags-enum), empty entries don't appear in the result. By default, empty entries are kept.

Example:

```
QString str = QStringLiteral("a,,b,c");

QStringList list1 = str.split(u',');
// list1: [ "a", "", "b", "c" ]

QStringList list2 = str.split(u',', Qt::SkipEmptyParts);
// list2: [ "a", "b", "c" ]
```

If *sep* is empty, split() returns an empty string, followed by each of the string's characters, followed by another empty string:

```
QString str = "abc";
auto parts = str.split(QString());
// parts: {"", "a", "b", "c", ""}
```

To understand this behavior, recall that the empty string matches everywhere, so the above is qualitatively the same as:

```
QString str = "/a/b/c/";
auto parts = str.split(u'/');
// parts: {"", "a", "b", "c", ""}
```

**See also** [QStringList::join](https://doc.qt.io/qt-6/qstringlist.html#join)() and [section](https://doc.qt.io/qt-6/qstring.html#section)().

### [QStringList](https://doc.qt.io/qt-6/qstringlist.html) QString::split([QChar](https://doc.qt.io/qt-6/qchar.html) *sep*, [Qt::SplitBehavior](https://doc.qt.io/qt-6/qt.html#SplitBehaviorFlags-enum) *behavior* = Qt::KeepEmptyParts, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This is an overloaded function.

### [QStringList](https://doc.qt.io/qt-6/qstringlist.html) QString::split(const [QRegularExpression](https://doc.qt.io/qt-6/qregularexpression.html) &*re*, [Qt::SplitBehavior](https://doc.qt.io/qt-6/qt.html#SplitBehaviorFlags-enum) *behavior* = Qt::KeepEmptyParts) const

This is an overloaded function.

Splits the string into substrings wherever the regular expression *re* matches, and returns the list of those strings. If *re* does not match anywhere in the string, split() returns a single-element list containing this string.

Here is an example where we extract the words in a sentence using one or more whitespace characters as the separator:

```
QString str;
QStringList list;

str = "Some  text\n\twith  strange whitespace.";
list = str.split(QRegularExpression("\\s+"));
// list: [ "Some", "text", "with", "strange", "whitespace." ]
```

Here is a similar example, but this time we use any sequence of non-word characters as the separator:

```
str = "This time, a normal English sentence.";
list = str.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
// list: [ "This", "time", "a", "normal", "English", "sentence" ]
```

Here is a third example where we use a zero-length assertion, **\b** (word boundary), to split the string into an alternating sequence of non-word and word tokens:

```
str = "Now: this sentence fragment.";
list = str.split(QRegularExpression("\\b"));
// list: [ "", "Now", ": ", "this", " ", "sentence", " ", "fragment", "." ]
```

**See also** [QStringList::join](https://doc.qt.io/qt-6/qstringlist.html#join)() and [section](https://doc.qt.io/qt-6/qstring.html#section)().

### void QString::squeeze()

Releases any memory not required to store the character data.

The sole purpose of this function is to provide a means of fine tuning [QString](https://doc.qt.io/qt-6/qstring.html)'s memory usage. In general, you will rarely ever need to call this function.

**See also** [reserve](https://doc.qt.io/qt-6/qstring.html#reserve)() and [capacity](https://doc.qt.io/qt-6/qstring.html#capacity)().

### bool QString::startsWith(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

Returns `true` if the string starts with *s*; otherwise returns `false`.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

```
QString str = "Bananas";
str.startsWith("Ban");     // returns true
str.startsWith("Car");     // returns false
```

**See also** [endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)().

### `[noexcept]`bool QString::startsWith([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This is an overloaded function.

Returns `true` if the string starts with the string view *str*; otherwise returns `false`.

If *cs* is [Qt::CaseSensitive](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) (the default), the search is case-sensitive; otherwise the search is case-insensitive.

**See also** [endsWith](https://doc.qt.io/qt-6/qstring.html#endsWith)().

### bool QString::startsWith([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads startsWith().

### bool QString::startsWith([QChar](https://doc.qt.io/qt-6/qchar.html) *c*, [Qt::CaseSensitivity](https://doc.qt.io/qt-6/qt.html#CaseSensitivity-enum) *cs* = Qt::CaseSensitive) const

This function overloads startsWith().

Returns `true` if the string starts with *c*; otherwise returns `false`.

### `[noexcept]`void QString::swap([QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*)

Swaps string *other* with this string. This operation is very fast and never fails.

### CFStringRef QString::toCFString() const

Creates a CFString from a [QString](https://doc.qt.io/qt-6/qstring.html).

The caller owns the CFString and is responsible for releasing it.

**Note:** this function is only available on macOS and iOS.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::toCaseFolded() const

Returns the case folded equivalent of the string. For most Unicode characters this is the same as [toLower](https://doc.qt.io/qt-6/qstring.html#toLower)().

### double QString::toDouble(bool **ok* = nullptr) const

Returns the string converted to a `double` value.

Returns an infinity if the conversion overflows or 0.0 if the conversion fails for other reasons (e.g. underflow).

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

```
QString str = "1234.56";
double val = str.toDouble();   // val == 1234.56
```

**Warning:** The [QString](https://doc.qt.io/qt-6/qstring.html) content may only contain valid numerical characters which includes the plus/minus sign, the character e used in scientific notation, and the decimal point. Including the unit or additional characters leads to a conversion error.

```
bool ok;
double d;

d = QString( "1234.56e-02" ).toDouble(&ok); // ok == true, d == 12.3456

d = QString( "1234.56e-02 Volt" ).toDouble(&ok); // ok == false, d == 0
```

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toDouble](https://doc.qt.io/qt-6/qlocale.html#toDouble)()

```
d = QString( "1234,56" ).toDouble(&ok); // ok == false
d = QString( "1234.56" ).toDouble(&ok); // ok == true, d == 1234.56
```

For historical reasons, this function does not handle thousands group separators. If you need to convert such numbers, use [QLocale::toDouble](https://doc.qt.io/qt-6/qlocale.html#toDouble)().

```
d = QString( "1,234,567.89" ).toDouble(&ok); // ok == false
d = QString( "1234567.89" ).toDouble(&ok); // ok == true
```

This function ignores leading and trailing whitespace.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [QLocale::setDefault](https://doc.qt.io/qt-6/qlocale.html#setDefault)(), [QLocale::toDouble](https://doc.qt.io/qt-6/qlocale.html#toDouble)(), and [trimmed](https://doc.qt.io/qt-6/qstring.html#trimmed)().

### `[since 6.6]`emscripten::val QString::toEcmaString() const

Converts this object to an [ECMAScript string](https://262.ecma-international.org/#sec-string-object).

This function was introduced in Qt 6.6.

**See also** [fromEcmaString](https://doc.qt.io/qt-6/qstring.html#fromEcmaString)().

### float QString::toFloat(bool **ok* = nullptr) const

Returns the string converted to a `float` value.

Returns an infinity if the conversion overflows or 0.0 if the conversion fails for other reasons (e.g. underflow).

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

**Warning:** The [QString](https://doc.qt.io/qt-6/qstring.html) content may only contain valid numerical characters which includes the plus/minus sign, the character e used in scientific notation, and the decimal point. Including the unit or additional characters leads to a conversion error.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toFloat](https://doc.qt.io/qt-6/qlocale.html#toFloat)()

For historical reasons, this function does not handle thousands group separators. If you need to convert such numbers, use [QLocale::toFloat](https://doc.qt.io/qt-6/qlocale.html#toFloat)().

Example:

```
QString str1 = "1234.56";
str1.toFloat();             // returns 1234.56

bool ok;
QString str2 = "R2D2";
str2.toFloat(&ok);          // returns 0.0, sets ok to false

QString str3 = "1234.56 Volt";
str3.toFloat(&ok);          // returns 0.0, sets ok to false
```

This function ignores leading and trailing whitespace.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toDouble](https://doc.qt.io/qt-6/qstring.html#toDouble)(), [toInt](https://doc.qt.io/qt-6/qstring.html#toInt)(), [QLocale::toFloat](https://doc.qt.io/qt-6/qlocale.html#toFloat)(), and [trimmed](https://doc.qt.io/qt-6/qstring.html#trimmed)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::toHtmlEscaped() const

Converts a plain text string to an HTML string with HTML metacharacters `< `, `>`, `&`, and `"` replaced by HTML entities.

Example:

```
QString plain = "#include < QtCore>"
QString html = plain.toHtmlEscaped();
// html == "#include &lt;QtCore&gt;"
```

### int QString::toInt(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to an `int` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toInt](https://doc.qt.io/qt-6/qlocale.html#toInt)()

Example:

```
QString str = "FF";
bool ok;
int hex = str.toInt(&ok, 16);       // hex == 255, ok == true
int dec = str.toInt(&ok, 10);       // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toUInt](https://doc.qt.io/qt-6/qstring.html#toUInt)(), [toDouble](https://doc.qt.io/qt-6/qstring.html#toDouble)(), and [QLocale::toInt](https://doc.qt.io/qt-6/qlocale.html#toInt)().

### [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) QString::toLatin1() const

Returns a Latin-1 representation of the string as a [QByteArray](https://doc.qt.io/qt-6/qbytearray.html).

The returned byte array is undefined if the string contains non-Latin1 characters. Those characters may be suppressed or replaced with a question mark.

**See also** [fromLatin1](https://doc.qt.io/qt-6/qstring.html#fromLatin1)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), and [QStringEncoder](https://doc.qt.io/qt-6/qstringencoder.html).

### [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) QString::toLocal8Bit() const

Returns the local 8-bit representation of the string as a [QByteArray](https://doc.qt.io/qt-6/qbytearray.html).

On Unix systems this is equivalent to [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(). Note that on Apple systems this function does not take `\l{https://developer.apple.com/documentation/foundation/nsstring/1410091-defaultcstringencoding?language=objc}` {NSString.defaultCStringEncoding} or `\l{https://developer.apple.com/documentation/corefoundation/1541720-cfstringgetsystemencoding?language=objc}` {CFStringGetSystemEncoding()} into account, as these functions typically return the legacy "Western (Mac OS Roman)" encoding, which should not be used on modern Apple operating systems. On Windows the system's current code page is used.

If this string contains any characters that cannot be encoded in the local 8-bit encoding, the returned byte array is undefined. Those characters may be suppressed or replaced by another.

**See also** [fromLocal8Bit](https://doc.qt.io/qt-6/qstring.html#fromLocal8Bit)(), [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), and [QStringEncoder](https://doc.qt.io/qt-6/qstringencoder.html).

### long QString::toLong(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to a `long` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toLongLong](https://doc.qt.io/qt-6/qlocale.html#toLongLong)()

Example:

```
QString str = "FF";
bool ok;

long hex = str.toLong(&ok, 16);     // hex == 255, ok == true
long dec = str.toLong(&ok, 10);     // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toULong](https://doc.qt.io/qt-6/qstring.html#toULong)(), [toInt](https://doc.qt.io/qt-6/qstring.html#toInt)(), and [QLocale::toInt](https://doc.qt.io/qt-6/qlocale.html#toInt)().

### [qlonglong](https://doc.qt.io/qt-6/qttypes.html#qlonglong-typedef) QString::toLongLong(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to a `long long` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toLongLong](https://doc.qt.io/qt-6/qlocale.html#toLongLong)()

Example:

```
QString str = "FF";
bool ok;

qint64 hex = str.toLongLong(&ok, 16);      // hex == 255, ok == true
qint64 dec = str.toLongLong(&ok, 10);      // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toULongLong](https://doc.qt.io/qt-6/qstring.html#toULongLong)(), [toInt](https://doc.qt.io/qt-6/qstring.html#toInt)(), and [QLocale::toLongLong](https://doc.qt.io/qt-6/qlocale.html#toLongLong)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::toLower() const

Returns a lowercase copy of the string.

```
QString str = "The Qt PROJECT";
str = str.toLower();        // str == "the qt project"
```

The case conversion will always happen in the 'C' locale. For locale-dependent case folding use [QLocale::toLower](https://doc.qt.io/qt-6/qlocale.html#toLower)()

**See also** [toUpper](https://doc.qt.io/qt-6/qstring.html#toUpper)() and [QLocale::toLower](https://doc.qt.io/qt-6/qlocale.html#toLower)().

### NSString *QString::toNSString() const

Creates a NSString from a [QString](https://doc.qt.io/qt-6/qstring.html).

The NSString is autoreleased.

**Note:** this function is only available on macOS and iOS.

### short QString::toShort(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to a `short` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toShort](https://doc.qt.io/qt-6/qlocale.html#toShort)()

Example:

```
QString str = "FF";
bool ok;

short hex = str.toShort(&ok, 16);   // hex == 255, ok == true
short dec = str.toShort(&ok, 10);   // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toUShort](https://doc.qt.io/qt-6/qstring.html#toUShort)(), [toInt](https://doc.qt.io/qt-6/qstring.html#toInt)(), and [QLocale::toShort](https://doc.qt.io/qt-6/qlocale.html#toShort)().

### std::string QString::toStdString() const

Returns a std::string object with the data contained in this [QString](https://doc.qt.io/qt-6/qstring.html). The Unicode data is converted into 8-bit characters using the [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)() function.

This method is mostly useful to pass a [QString](https://doc.qt.io/qt-6/qstring.html) to a function that accepts a std::string object.

**See also** [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), and [QByteArray::toStdString](https://doc.qt.io/qt-6/qbytearray.html#toStdString)().

### std::u16string QString::toStdU16String() const

Returns a std::u16string object with the data contained in this [QString](https://doc.qt.io/qt-6/qstring.html). The Unicode data is the same as returned by the [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)() method.

**See also** [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)(), [toStdWString](https://doc.qt.io/qt-6/qstring.html#toStdWString)(), and [toStdU32String](https://doc.qt.io/qt-6/qstring.html#toStdU32String)().

### std::u32string QString::toStdU32String() const

Returns a std::u32string object with the data contained in this [QString](https://doc.qt.io/qt-6/qstring.html). The Unicode data is the same as returned by the [toUcs4](https://doc.qt.io/qt-6/qstring.html#toUcs4)() method.

**See also** [toUcs4](https://doc.qt.io/qt-6/qstring.html#toUcs4)(), [toStdWString](https://doc.qt.io/qt-6/qstring.html#toStdWString)(), and [toStdU16String](https://doc.qt.io/qt-6/qstring.html#toStdU16String)().

### std::wstring QString::toStdWString() const

Returns a std::wstring object with the data contained in this [QString](https://doc.qt.io/qt-6/qstring.html). The std::wstring is encoded in utf16 on platforms where wchar_t is 2 bytes wide (e.g. windows) and in ucs4 on platforms where wchar_t is 4 bytes wide (most Unix systems).

This method is mostly useful to pass a [QString](https://doc.qt.io/qt-6/qstring.html) to a function that accepts a std::wstring object.

**See also** [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)(), [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), [toStdU16String](https://doc.qt.io/qt-6/qstring.html#toStdU16String)(), and [toStdU32String](https://doc.qt.io/qt-6/qstring.html#toStdU32String)().

### [uint](https://doc.qt.io/qt-6/qttypes.html#uint-typedef) QString::toUInt(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to an `unsigned int` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toUInt](https://doc.qt.io/qt-6/qlocale.html#toUInt)()

Example:

```
QString str = "FF";
bool ok;

uint hex = str.toUInt(&ok, 16);     // hex == 255, ok == true
uint dec = str.toUInt(&ok, 10);     // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toInt](https://doc.qt.io/qt-6/qstring.html#toInt)(), and [QLocale::toUInt](https://doc.qt.io/qt-6/qlocale.html#toUInt)().

### [ulong](https://doc.qt.io/qt-6/qttypes.html#ulong-typedef) QString::toULong(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to an `unsigned long` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toULongLong](https://doc.qt.io/qt-6/qlocale.html#toULongLong)()

Example:

```
QString str = "FF";
bool ok;

ulong hex = str.toULong(&ok, 16);   // hex == 255, ok == true
ulong dec = str.toULong(&ok, 10);   // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)() and [QLocale::toUInt](https://doc.qt.io/qt-6/qlocale.html#toUInt)().

### [qulonglong](https://doc.qt.io/qt-6/qttypes.html#qulonglong-typedef) QString::toULongLong(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to an `unsigned long long` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toULongLong](https://doc.qt.io/qt-6/qlocale.html#toULongLong)()

Example:

```
QString str = "FF";
bool ok;

quint64 hex = str.toULongLong(&ok, 16);    // hex == 255, ok == true
quint64 dec = str.toULongLong(&ok, 10);    // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toLongLong](https://doc.qt.io/qt-6/qstring.html#toLongLong)(), and [QLocale::toULongLong](https://doc.qt.io/qt-6/qlocale.html#toULongLong)().

### [ushort](https://doc.qt.io/qt-6/qttypes.html#ushort-typedef) QString::toUShort(bool **ok* = nullptr, int *base* = 10) const

Returns the string converted to an `unsigned short` using base *base*, which is 10 by default and must be between 2 and 36, or 0. Returns 0 if the conversion fails.

If *ok* is not `nullptr`, failure is reported by setting **ok* to `false`, and success by setting **ok* to `true`.

If *base* is 0, the C language convention is used: if the string begins with "0x", base 16 is used; otherwise, if the string begins with "0b", base 2 is used; otherwise, if the string begins with "0", base 8 is used; otherwise, base 10 is used.

The string conversion will always happen in the 'C' locale. For locale-dependent conversion use [QLocale::toUShort](https://doc.qt.io/qt-6/qlocale.html#toUShort)()

Example:

```
QString str = "FF";
bool ok;

ushort hex = str.toUShort(&ok, 16);     // hex == 255, ok == true
ushort dec = str.toUShort(&ok, 10);     // dec == 0, ok == false
```

This function ignores leading and trailing whitespace.

**Note:** Support for the "0b" prefix was added in Qt 6.4.

**See also** [number](https://doc.qt.io/qt-6/qstring.html#number)(), [toShort](https://doc.qt.io/qt-6/qstring.html#toShort)(), and [QLocale::toUShort](https://doc.qt.io/qt-6/qlocale.html#toUShort)().

### [QList](https://doc.qt.io/qt-6/qlist.html)< [uint](https://doc.qt.io/qt-6/qttypes.html#uint-typedef)> QString::toUcs4() const

Returns a UCS-4/UTF-32 representation of the string as a [QList](https://doc.qt.io/qt-6/qlist.html)< uint>.

UCS-4 is a Unicode codec and therefore it is lossless. All characters from this string will be encoded in UCS-4. Any invalid sequence of code units in this string is replaced by the Unicode's replacement character ([QChar::ReplacementCharacter](https://doc.qt.io/qt-6/qchar.html#SpecialCharacter-enum), which corresponds to `U+FFFD`).

The returned list is not \0'-terminated.

**See also** [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), [QStringEncoder](https://doc.qt.io/qt-6/qstringencoder.html), [fromUcs4](https://doc.qt.io/qt-6/qstring.html#fromUcs4)(), and [toWCharArray](https://doc.qt.io/qt-6/qstring.html#toWCharArray)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::toUpper() const

Returns an uppercase copy of the string.

```
QString str = "TeXt";
str = str.toUpper();        // str == "TEXT"
```

The case conversion will always happen in the 'C' locale. For locale-dependent case folding use [QLocale::toUpper](https://doc.qt.io/qt-6/qlocale.html#toUpper)()

**See also** [toLower](https://doc.qt.io/qt-6/qstring.html#toLower)() and [QLocale::toLower](https://doc.qt.io/qt-6/qlocale.html#toLower)().

### [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) QString::toUtf8() const

Returns a UTF-8 representation of the string as a [QByteArray](https://doc.qt.io/qt-6/qbytearray.html).

UTF-8 is a Unicode codec and can represent all characters in a Unicode string like [QString](https://doc.qt.io/qt-6/qstring.html).

**See also** [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)(), [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), and [QStringEncoder](https://doc.qt.io/qt-6/qstringencoder.html).

### qsizetype QString::toWCharArray(wchar_t **array*) const

Fills the *array* with the data contained in this [QString](https://doc.qt.io/qt-6/qstring.html) object. The array is encoded in UTF-16 on platforms where wchar_t is 2 bytes wide (e.g. windows) and in UCS-4 on platforms where wchar_t is 4 bytes wide (most Unix systems).

*array* has to be allocated by the caller and contain enough space to hold the complete string (allocating the array with the same length as the string is always sufficient).

This function returns the actual length of the string in *array*.

**Note:** This function does not append a null character to the array.

**See also** [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)(), [toUcs4](https://doc.qt.io/qt-6/qstring.html#toUcs4)(), [toLatin1](https://doc.qt.io/qt-6/qstring.html#toLatin1)(), [toUtf8](https://doc.qt.io/qt-6/qstring.html#toUtf8)(), [toLocal8Bit](https://doc.qt.io/qt-6/qstring.html#toLocal8Bit)(), [toStdWString](https://doc.qt.io/qt-6/qstring.html#toStdWString)(), and [QStringView::toWCharArray](https://doc.qt.io/qt-6/qstringview.html#toWCharArray)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::trimmed() const

Returns a string that has whitespace removed from the start and the end.

Whitespace means any character for which [QChar::isSpace](https://doc.qt.io/qt-6/qchar.html#isSpace)() returns `true`. This includes the ASCII characters '\t', '\n', '\v', '\f', '\r', and ' '.

Example:

```
QString str = "  lots\t of\nwhitespace\r\n ";
str = str.trimmed();
// str == "lots\t of\nwhitespace"
```

Unlike [simplified](https://doc.qt.io/qt-6/qstring.html#simplified)(), trimmed() leaves internal whitespace alone.

**See also** [simplified](https://doc.qt.io/qt-6/qstring.html#simplified)().

### void QString::truncate(qsizetype *position*)

Truncates the string at the given *position* index.

If the specified *position* index is beyond the end of the string, nothing happens.

Example:

```
QString str = "Vladivostok";
str.truncate(4);
// str == "Vlad"
```

If *position* is negative, it is equivalent to passing zero.

**See also** [chop](https://doc.qt.io/qt-6/qstring.html#chop)(), [resize](https://doc.qt.io/qt-6/qstring.html#resize)(), [first](https://doc.qt.io/qt-6/qstring.html#first)(), and [QStringView::truncate](https://doc.qt.io/qt-6/qstringview.html#truncate)().

### const [QChar](https://doc.qt.io/qt-6/qchar.html) *QString::unicode() const

Returns a Unicode representation of the string. The result remains valid until the string is modified.

**Note:** The returned string may not be '\0'-terminated. Use [size](https://doc.qt.io/qt-6/qstring.html#size)() to determine the length of the array.

**See also** [setUnicode](https://doc.qt.io/qt-6/qstring.html#setUnicode)(), [utf16](https://doc.qt.io/qt-6/qstring.html#utf16)(), and [fromRawData](https://doc.qt.io/qt-6/qstring.html#fromRawData)().

### const [ushort](https://doc.qt.io/qt-6/qttypes.html#ushort-typedef) *QString::utf16() const

Returns the [QString](https://doc.qt.io/qt-6/qstring.html) as a '\0'-terminated array of unsigned shorts. The result remains valid until the string is modified.

The returned string is in host byte order.

**See also** [setUtf16](https://doc.qt.io/qt-6/qstring.html#setUtf16)() and [unicode](https://doc.qt.io/qt-6/qstring.html#unicode)().

### `[static]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) QString::vasprintf(const char **cformat*, va_list *ap*)

Equivalent method to [asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)(), but takes a va_list *ap* instead a list of variable arguments. See the [asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)() documentation for an explanation of *cformat*.

This method does not call the va_end macro, the caller is responsible to call va_end on *ap*.

**See also** [asprintf](https://doc.qt.io/qt-6/qstring.html#asprintf)().

### bool QString::operator!=(const char **other*) const

This function overloads operator!=().

The *other* const char pointer is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator!=(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*other*) const

This function overloads operator!=().

The *other* byte array is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function. If any NUL characters ('\0') are embedded in the byte array, they will be included in the transformation.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*)

Appends the string *other* onto the end of this string and returns a reference to this string.

Example:

```
QString x = "free";
QString y = "dom";
x += y;
// x == "freedom"
```

This operation is typically very fast ([constant time](https://doc.qt.io/qt-6/containers.html#constant-time)), because [QString](https://doc.qt.io/qt-6/qstring.html) preallocates extra space at the end of the string data so it can grow without reallocating the entire string each time.

**See also** [append](https://doc.qt.io/qt-6/qstring.html#append)() and [prepend](https://doc.qt.io/qt-6/qstring.html#prepend)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This function overloads operator+=().

Appends the character *ch* to the string.

### `[since 6.0]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=([QStringView](https://doc.qt.io/qt-6/qstringview.html) *str*)

This function overloads operator+=().

Appends the string view *str* to this string.

This function was introduced in Qt 6.0.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*)

This function overloads operator+=().

Appends the Latin-1 string viewed by *str* to this string.

### `[since 6.5]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=([QUtf8StringView](https://doc.qt.io/qt-6/qutf8stringview.html) *str*)

This function overloads operator+=().

Appends the UTF-8 string view *str* to this string.

This function was introduced in Qt 6.5.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=(const char **str*)

This function overloads operator+=().

Appends the string *str* to this string. The const char pointer is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this function by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator+=(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*ba*)

This function overloads operator+=().

Appends the byte array *ba* to this string. The byte array is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function. If any NUL characters ('\0') are embedded in the *ba* byte array, they will be included in the transformation.

You can disable this function by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator< (const char **other*) const

Returns `true` if this string is lexically less than string *other*. Otherwise returns `false`.

This function overloads operator< ().

The *other* const char pointer is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator< (const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*other*) const

This function overloads operator< ().

The *other* byte array is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function. If any NUL characters ('\0') are embedded in the byte array, they will be included in the transformation.

You can disable this operator [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator< =(const char **other*) const

This function overloads operator< =().

The *other* const char pointer is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator< =(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*other*) const

This function overloads operator< =().

The *other* byte array is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function. If any NUL characters ('\0') are embedded in the byte array, they will be included in the transformation.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### `[noexcept]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator=(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*other*)

Assigns *other* to this string and returns a reference to this string.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator=([QChar](https://doc.qt.io/qt-6/qchar.html) *ch*)

This function overloads operator=().

Sets the string to contain the single character *ch*.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator=([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *str*)

This function overloads operator=().

Assigns the Latin-1 string viewed by *str* to this string.

### `[noexcept]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator=([QString](https://doc.qt.io/qt-6/qstring.html#QString) &&*other*)

Move-assigns *other* to this [QString](https://doc.qt.io/qt-6/qstring.html) instance.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator=(const char **str*)

This function overloads operator=().

Assigns *str* to this string. The const char pointer is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) or [QT_RESTRICTED_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_RESTRICTED_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) &QString::operator=(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*ba*)

This function overloads operator=().

Assigns *ba* to this string. The byte array is converted to Unicode using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator==(const char **other*) const

This function overloads operator==().

The *other* const char pointer is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator==(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*other*) const

This function overloads operator==().

The *other* byte array is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

Returns `true` if this string is lexically equal to the parameter string *other*. Otherwise returns `false`.

### bool QString::operator>(const char **other*) const

This function overloads operator>().

The *other* const char pointer is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator>(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*other*) const

This function overloads operator>().

The *other* byte array is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function. If any NUL characters ('\0') are embedded in the byte array, they will be included in the transformation.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator>=(const char **other*) const

This function overloads operator>=().

The *other* const char pointer is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### bool QString::operator>=(const [QByteArray](https://doc.qt.io/qt-6/qbytearray.html) &*other*) const

This function overloads operator>=().

The *other* byte array is converted to a [QString](https://doc.qt.io/qt-6/qstring.html) using the [fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function. If any NUL characters ('\0') are embedded in the byte array, they will be included in the transformation.

You can disable this operator by defining [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII) when you compile your applications. This can be useful if you want to ensure that all user-visible strings go through [QObject::tr](https://doc.qt.io/qt-6/qobject.html#tr)(), for example.

### [QChar](https://doc.qt.io/qt-6/qchar.html) &QString::operator[](qsizetype *position*)

Returns the character at the specified *position* in the string as a modifiable reference.

Example:

```
QString str;

if (str[0] == QChar('?'))
    str[0] = QChar('_');
```

**See also** [at](https://doc.qt.io/qt-6/qstring.html#at)().

### const [QChar](https://doc.qt.io/qt-6/qchar.html) QString::operator[](qsizetype *position*) const

This function overloads operator[]().

## Related Non-Members

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) operator+([QString](https://doc.qt.io/qt-6/qstring.html#QString) &&*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) operator+(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns a string which is the result of concatenating *s1* and *s2*.

### `[since 6.1]`template < typename T> qsizetype erase([QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s*, const T &*t*)

Removes all elements that compare equal to *t* from the string *s*. Returns the number of elements removed, if any.

This function was introduced in Qt 6.1.

**See also** [erase_if](https://doc.qt.io/qt-6/qstring.html#erase_if-1).

### `[since 6.1]`template < typename Predicate> qsizetype erase_if([QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s*, Predicate *pred*)

Removes all elements for which the predicate *pred* returns true from the string *s*. Returns the number of elements removed, if any.

This function was introduced in Qt 6.1.

**See also** [erase](https://doc.qt.io/qt-6/qstring.html#erase).

### `[noexcept]`bool operator!=(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if string *s1* is not equal to string *s2*; otherwise returns `false`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator!=(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*)

Returns `true` if string *s1* is not equal to string *s2*. Otherwise returns `false`.

This function overloads operator!=().

### bool operator!=(const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if *s1* is not equal to *s2*; otherwise returns `false`.

For *s1* != 0, this is equivalent to `compare(` *s1*, *s2* `) != 0`. Note that no string is equal to *s1* being 0.

### `[noexcept, since 6.4]`[QString](https://doc.qt.io/qt-6/qstring.html#QString) operator""_s(const char16_t **str*, size_t *size*)

Literal operator that creates a [QString](https://doc.qt.io/qt-6/qstring.html) out of the first *size* characters in the char16_t string literal *str*.

The [QString](https://doc.qt.io/qt-6/qstring.html) is created at compile time, and the generated string data is stored in the read-only segment of the compiled object file. Duplicate literals may share the same read-only memory. This functionality is interchangeable with [QStringLiteral](https://doc.qt.io/qt-6/qstring.html#QStringLiteral), but saves typing when many string literals are present in the code.

The following code creates a [QString](https://doc.qt.io/qt-6/qstring.html):

```
using namespace Qt::Literals::StringLiterals;

auto str = u"hello"_s;
```

This function was introduced in Qt 6.4.

**See also** [Qt::Literals::StringLiterals](https://doc.qt.io/qt-6/qt-literals-stringliterals.html).

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) operator+(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const char **s2*)

Returns a string which is the result of concatenating *s1* and *s2* (*s2* is converted to Unicode using the [QString::fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function).

**See also** [QString::fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

### [QString](https://doc.qt.io/qt-6/qstring.html#QString) operator+(const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns a string which is the result of concatenating *s1* and *s2* (*s1* is converted to Unicode using the [QString::fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)() function).

**See also** [QString::fromUtf8](https://doc.qt.io/qt-6/qstring.html#fromUtf8)().

### `[noexcept]`bool operator< (const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator< ().

Returns `true` if string *s1* is lexically less than string *s2*; otherwise returns `false`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator< (const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*)

This function overloads operator< ().

Returns `true` if *s1* is lexically less than *s2*; otherwise returns `false`.

### `[noexcept]`bool operator< ([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator< ().

Returns `true` if *s1* is lexically less than *s2*; otherwise returns `false`.

### bool operator< (const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if *s1* is lexically less than *s2*; otherwise returns `false`. For *s1* != 0, this is equivalent to `compare(s1, s2) <  0`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### [QDataStream](https://doc.qt.io/qt-6/qdatastream.html) &operator< < ([QDataStream](https://doc.qt.io/qt-6/qdatastream.html) &*stream*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*string*)

Writes the given *string* to the specified *stream*.

**See also** [Serializing Qt Data Types](https://doc.qt.io/qt-6/datastreamformat.html).

### `[noexcept]`bool operator< =(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if string *s1* is lexically less than or equal to string *s2*; otherwise returns `false`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator< =(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*)

This function overloads operator< =().

Returns `true` if *s1* is lexically less than or equal to *s2*; otherwise returns `false`.

### `[noexcept]`bool operator< =([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator< =().

Returns `true` if *s1* is lexically less than or equal to *s2*; otherwise returns `false`.

### bool operator< =(const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if *s1* is lexically less than or equal to *s2*; otherwise returns `false`. For *s1* != 0, this is equivalent to `compare(s1, s2) < = 0`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator==(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator==().

Returns `true` if string *s1* is equal to string *s2*; otherwise returns `false`.

**Note:** This function treats null strings the same as empty strings, for more details see [Distinction Between Null and Empty Strings](https://doc.qt.io/qt-6/qstring.html#distinction-between-null-and-empty-strings).

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator==(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*)

This function overloads operator==().

Returns `true` if *s1* is equal to *s2*; otherwise returns `false`.

### `[noexcept]`bool operator==([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator==().

Returns `true` if *s1* is equal to *s2*; otherwise returns `false`.

### bool operator==(const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator==().

Returns `true` if *s1* is equal to *s2*; otherwise returns `false`. Note that no string is equal to *s1* being 0.

Equivalent to `s1 != 0 && compare(s1, s2) == 0`.

### `[noexcept]`bool operator>(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if string *s1* is lexically greater than string *s2*; otherwise returns `false`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator>(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*)

This function overloads operator>().

Returns `true` if *s1* is lexically greater than *s2*; otherwise returns `false`.

### `[noexcept]`bool operator>([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator>().

Returns `true` if *s1* is lexically greater than *s2*; otherwise returns `false`.

### bool operator>(const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if *s1* is lexically greater than *s2*; otherwise returns `false`. Equivalent to `compare(s1, s2) > 0`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator>=(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if string *s1* is lexically greater than or equal to string *s2*; otherwise returns `false`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### `[noexcept]`bool operator>=(const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s1*, [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s2*)

This function overloads operator>=().

Returns `true` if *s1* is lexically greater than or equal to *s2*; otherwise returns `false`.

### `[noexcept]`bool operator>=([QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) *s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

This function overloads operator>=().

Returns `true` if *s1* is lexically greater than or equal to *s2*; otherwise returns `false`.

### bool operator>=(const char **s1*, const [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*s2*)

Returns `true` if *s1* is lexically greater than or equal to *s2*; otherwise returns `false`. For *s1* != 0, this is equivalent to `compare(s1, s2) >= 0`.

**See also** [Comparing Strings](https://doc.qt.io/qt-6/qstring.html#comparing-strings).

### [QDataStream](https://doc.qt.io/qt-6/qdatastream.html) &operator>>([QDataStream](https://doc.qt.io/qt-6/qdatastream.html) &*stream*, [QString](https://doc.qt.io/qt-6/qstring.html#QString) &*string*)

Reads a string from the specified *stream* into the given *string*.

**See also** [Serializing Qt Data Types](https://doc.qt.io/qt-6/datastreamformat.html).

## Macro Documentation

### QStringLiteral(*str*)

The macro generates the data for a [QString](https://doc.qt.io/qt-6/qstring.html) out of the string literal *str* at compile time. Creating a [QString](https://doc.qt.io/qt-6/qstring.html) from it is free in this case, and the generated string data is stored in the read-only segment of the compiled object file.

If you have code that looks like this:

```
// hasAttribute takes a QString argument
if (node.hasAttribute("http-contents-length")) //...
```

then a temporary [QString](https://doc.qt.io/qt-6/qstring.html) will be created to be passed as the `hasAttribute` function parameter. This can be quite expensive, as it involves a memory allocation and the copy/conversion of the data into [QString](https://doc.qt.io/qt-6/qstring.html)'s internal encoding.

This cost can be avoided by using QStringLiteral instead:

```
if (node.hasAttribute(QStringLiteral(u"http-contents-length"))) //...
```

In this case, [QString](https://doc.qt.io/qt-6/qstring.html)'s internal data will be generated at compile time; no conversion or allocation will occur at runtime.

Using QStringLiteral instead of a double quoted plain C++ string literal can significantly speed up creation of [QString](https://doc.qt.io/qt-6/qstring.html) instances from data known at compile time.

**Note:** [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) can still be more efficient than QStringLiteral when the string is passed to a function that has an overload taking [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) and this overload avoids conversion to [QString](https://doc.qt.io/qt-6/qstring.html). For instance, QString::operator==() can compare to a [QLatin1StringView](https://doc.qt.io/qt-6/qlatin1stringview.html) directly:

```
if (attribute.name() == "http-contents-length"_L1) //...
```

**Note:** Some compilers have bugs encoding strings containing characters outside the US-ASCII character set. Make sure you prefix your string with `u` in those cases. It is optional otherwise.

**See also** [QByteArrayLiteral](https://doc.qt.io/qt-6/qbytearray.html#QByteArrayLiteral).

### QT_NO_CAST_FROM_ASCII

Disables automatic conversions from 8-bit strings (`char *`) to Unicode QStrings, as well as from 8-bit `char` types (`char` and `unsigned char`) to [QChar](https://doc.qt.io/qt-6/qchar.html).

**See also** [QT_NO_CAST_TO_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_TO_ASCII), [QT_RESTRICTED_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_RESTRICTED_CAST_FROM_ASCII), and [QT_NO_CAST_FROM_BYTEARRAY](https://doc.qt.io/qt-6/qbytearray.html#QT_NO_CAST_FROM_BYTEARRAY).

### QT_NO_CAST_TO_ASCII

Disables automatic conversion from [QString](https://doc.qt.io/qt-6/qstring.html) to 8-bit strings (`char *`).

**See also** [QT_NO_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_NO_CAST_FROM_ASCII), [QT_RESTRICTED_CAST_FROM_ASCII](https://doc.qt.io/qt-6/qstring.html#QT_RESTRICTED_CAST_FROM_ASCII), and [QT_NO_CAST_FROM_BYTEARRAY](https://doc.qt.io/qt-6/qbytearray.html#QT_NO_CAST_FROM_BYTEARRAY).

### QT_RESTRICTED_CAST_FROM_ASCII