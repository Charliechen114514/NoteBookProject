# More Effective C++ 1

## Basic Issues

我们现在开始C++的一大名著阅读.在这个sections，更多关注的是基础的C++议题。

### 条款1 区分pointers 和 reference

​		Pointers和reference确实不一样。在使用方式上，我们对Pointers是*（解引用）和`->`的方式来访问Reference确跟对象本身一样，访问成员使用 . 

​		作为Reference，不存在空引用！也就是说，不存在一个引用不指向任何对象。这点上，真是跟指针不大一样！

```C++  
char* pc = 0;
char* pc1 = &aCh; 
```

​		当然，那这样如何呢？

```C++
char *pc = 0;
char& rc = *pc;
```

​		答案是未定义行为！千万别显示的，或者是隐式的做这样的事情！

​		其二，基于上面的阐述，被引用的对象——必须——在引用之前就被初始化！

```C++
string& rs; // 不存在这样的代码！这是非法的
string s("xxyyzz");
string& rs = s;
```

​		相对应的——

```C++ 
string* ps;
```

​		通过编译！但是，比如说我的编译器会警告你没有初始化。于是，有必要对指针的合法性进行判断，而引用从来没有必要关注这件事情。

```C++ 
#include<iostream>

void checkPointersValid(double* pt) {

	if (pt == nullptr) {
		throw "trying to use empty double pointer! that's really bad :(";
		return;
	}
	std::cout << "Got value:> " << *pt << std::endl;
	return;
}

void Processing(double* pt) {

	try {

		checkPointersValid(pt);

	}
	catch (const char* errorStr) {

		std::cout << errorStr << std::endl;

		exit(-1);

	}

	return;
}

int main() {
	double val = 10;

	double* p1 = &val;

	double* null = nullptr;

	Processing(p1);

	Processing(null);
}
```

​		很是复杂。。。

​		另一个重要的区别在于：pointers是可变的，它可以从指向一个内存，原生的话，不加以说明的——指向另一块内存，而不会告诉你这件事情——这是很危险的（对于指向堆内存的话，容易造成泄漏）。但是reference就相当于常指针，总是指向那个对象不会改变。

​		总结来看：当你——需要考虑到“不指向任何对象”的可能性时，或者考虑：在不同时间需要指向不同对象的可能性时，有必要使用指针来完成你的工作，其余的情况下可以使用reference。

### 条款2：最好使用C++转型操作符

​		在旧时的C语言，我们如下转换类型

```C 
(target_type)expression
```

​		然而，这样的作法没有经过检查且辨识度太低了：为了解决这个问题，C++引入了：

```C++ 
static_cast<target_type>(expression)
```

​		来个例子：

```C++
int res1 = 10, res2 = 20;
double do_res = static_cast<double>(res1)/res2;
```

​		static_cast跟旧时的C一样有威力，也拥有一样的限制。甚至不可以移除const修饰符，于是const_cast来干这个事情了。

​		const_cast只可以改变变量的常量性和变易性。其余的都改变不了！

![image-20230514123125051](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More Effective C++ 1\image-20230514123125051.png)

```C++
class widget {
public:
	int a;
};

class specialWidget :public widget {
public:
	int b;
};
void update(specialWidget* psw) {

}
int main() {

	specialWidget sw;
	const specialWidget& csw = sw;

	update(&csw); // invalid

	update(const_cast<specialWidget*>(&csw)); // finish work properly!

	update((specialWidget*)&csw);

	widget* pw = new specialWidget;
	update(pw);//error ： 类型错误，不可以需要孩子传父亲！

	update(const_cast<specialWidget*>(pw)); // error
}
```

​		还有个dynamic_cast，特别用在了安全的向下转性或者跨系转型的动作。也就是说，可以将指向基类的指针或引用转向指向派生或者是兄弟类的类的指针或者是引用。他没有办法用在缺乏虚函数的类型，也不可改变常量性！

### 条款3：不要以多态的方式处理数组

​		继承的最重要的性质之一就是可以通过指向基类的指针或者是引用来操纵派生类。比如说

```C++
class BST{...}
class BalancedBST: public BST{...}
```

​		打印这些东西，我们涉及到：

```C++
void PrintBSTArray(ostream& os,const BSTarray[],int numElems){
    // omit some basic check
    for(int i = 0; i < int numElems; i++){
        os<<array[i]; // pretended that it has already been designed for using <<
    }
}
```

​		但是下一次传入：BalancedBST的时候，我们却依然实际上生成的是：

```C++ 
os << array + sizeof(BST)*i
```

​		而不是

```C++
os << array + sizeof(BalancedBST)*i
```

​		这很麻烦了！倘若这个函数是删除元素的话，就意味着删除是不完全的！因为基类总是不会比派生类小的！而且行为未定义！极易造成程序的崩溃！所以不要一多态的方式来处理数组，是啥就是啥的处理！

### 条款四：非必要不提供默认构造函数

​		Default constructors是C++从无到有的生成一个对象的办法。这个东西你不指定初始化方法，其成员也会拥有一些值——对于数值者是０或者是其他些什么无意义的随机值，对于指针者是nullptr。一些内置的数据结构被初始化作空容器。

​		但是有一些类，倘若我们不提供任何其他信息，是不应该存在的！也就是说：一些可以从无到有的类才适合default constructor.反之不需要。比如说：

```C++
class EquipmentPieces{
    
  public:
    EquipmentPieces(int ID);
};
```

​		于是不难意料到：这样的初始化不可能合法：

```C++
EquipmentPieces EqVec[10];// no Default constructors
```

​		哪有该怎么办嘞，要不我们：

```C++
int IDArray[]={1,2,3,...};// make the Id valid previously
EquipmentPiece eqVec[10] = {
    
    EquipmentPiece(IDArray[0]),
    EquipmentPiece(IDArray[1]),
    ...
};
```

​		但是这没办法解决我们在堆上完成类似的行为。于是，我们不妨先声明指针数组

```C++
typedef EquipmentPieces* PEP;
PEP aPointerArray[10];// in stack
PEP aPointerArrayInHeap[10] = new PEP[10];
for(int i = 0; i < 10; i++){
    
    aPointerArrayInHeap[i] = new EquipmentPieces(ID[i]);
    
}
```

​		麻烦在于，我们必须记住我们在这里开辟了内存，是需要我们手动释放的。其次，可能指针本身还要占据内存，这是不好的。

​		于是还有第三种方法，那就是类似于C式的——先分配空数据，让数组指针指向之！

```C++
void* rawMem = operator new[](10*sizeof(EquipmentPiece));

EquipmentPiece* EPArray = static_cast<EquipmentPiece*> (rawMem);

for(int i = 0; i < 10; i++){
    new(&bestPieces[i]) EquipmentPieces(ID[i]);
}
```

​		就算如此，你会发现还得是要手动初始化！况且，释放掉他需要很麻烦的代码：

```C++
for(int i = 0 i >= 0; i--){
	epVec[i].~EquipmentPieces();
}

operator delete[](rawMem);
```

​		一个没有默认构造器的类很快还会有第二个麻烦，那就是没办法直接调用大部分的模板！你当然可以谨慎的设计之来回避这个问题。但是大部分人只有会在出现问题的时候想起来这回事情。

​		所以要不要它呢？注意到如果一切类都给了默认构造器，我们就必须手动的检查它，否则会产生大量的问题！

​		于是，还是回到这里：倘若我们不提供任何其他信息，是不应该存在的！也就是说：一些可以从无到有的类才适合default constructor.反之不需要！

## 操作符

### 条款5：对定制的类型转换符保持警觉

​		C++自然允许不同类型之间的隐式转换，我是说，比如说

```C++
short a = 10;
double b = a;
```

​		居然是可行的！这还好，C++甚至可以：

```C++
double b = 10.00；
char a = b;
```

​		这样会造成信息丢失的转换都是可以正常运行的！ 这是因为C++编译器会想尽办法的找到

​		于是，在C++的类设计上，有必要专门提供一个转换函数来促使之客户程序员调用，

```C++
class Rational{
public:    
	Rational(double a, double b); // make a/b 
};

Rational r(1,2);
cout << r;
```

​		这居然是可以输出的：0.5！

​		这是因为C++编译器会想尽办法的找到转化方式。这就很容易造成自己不期望你被调用的函数被调用了！

```C++
class Rational{
public:    
	Rational(double a, double b); // make a/b 、
    double asDouble() const;
};
```

​		这样，显示的调用即可：

```C++
cout << r.asDouble()<<endl;
```

​		或者，采用关键字explict来防止隐式转换！

```C++
template<class T>
class Array{
    
public:
    ...
        explicit Array(int num);
    ...
};

Array<int> a(10);
Array<int> b(10);

if(a == b[i])// invalid!!! as it is expicited, you can not transform it underconciously!
```

### 条款6区分前置操作符和后置操作符

​		在很久以前的C++，没办法区分前置＋＋和后置＋＋（或者－－）。于是，我们这样设计类来防止语法混淆：

```C++
#include<iostream>
using namespace std;

class UpInt {

public:
	UpInt(int i) :_val(i) {};
	UpInt& operator++() { this->_val++; return *this; };
	const UpInt operator++(int) { UpInt old = *this; ++(*this); return old; };
	UpInt& operator--(){ this->_val--; return *this; }
	const UpInt operator--(int) { UpInt old = *this; --(*this); return old; };

	int getVal()const { return _val; }
private:
	int _val;
};
ostream& operator<<(ostream& os, const UpInt& my_data) { os << my_data.getVal() << endl; return os; };

int main() {

	UpInt val(10);
	++val;
	cout << val;
	--val;
	cout << val;
	val++;
	cout << val;
	val--;
	cout << val;

}
```

​		为什么:

```C++
const UpInt operator++(int) { UpInt old = *this; ++(*this); return old; };
```

​		因为我们是为了防止:

```C++
int i = 0;
i++++; // invalid! C++ abandon this behaviors
```

​		所以就是直接禁止!只需要加个const将返回的对象常量化!就好了

###  条款7：千万不要重载&&,|| 和 , 操作符

​		继承于C的，C++对真假值的逻辑表达式也是采用“骤死式”的判别表达式。也就是说，针对这样的表达式：

```C++ 
char* p;
...// probably init the string or not

if((p != NULL) && (strlen(p) > 10)){
    ...
}

```

​		不需要担心strlen(p)会使用空指针，事实上，一旦判定 p == NULL，那就意味着这个表达式一定为假，就不需要我们去计算第二个式子。于是第二条甚至不会执行。

​		但是，一旦我们重载了，就无法预期编译器的行为。

​		于是在C++中，一些运算符是不可以重载的：

```C++ 
.	.*		::		?:		 new 	 delete		sizeof		typeid		static_cast		
dynamic_cast		const_cast		reinterpret_cast
```

###  条款8：了解不同含义的new和delete

​		我们必须指出，C++的语言有时候确实令人感到难绷，比如说我们会说new operator和operator new 不是一件事情！

```C++
string* phs = new string("Memory Managements");
```

​		首先，这个new式语言内建的，就是说：首先他分配足够多的内存，放置一个东西。然后调用编译器找到的最合适的初始constructor来完成初始化工作！这样的行为不可以我们改变。

​		我们可以改变什么啥呢？改变operator new。什么意思？我们发现，new在一些适合调用一个函数执行必要的内存分配空间。这个函数我们可以重写！

```C++
void* operator new(size_t size);
```

​		也就是说，这是一个操作符函数，该函数返回一个空的内存！嘿，就像malloc函数一样！

```C++
void* rawMem = operator new(sizeof(string));
```

​		于是，new operator实际上就是operator new + 内存初始化了

```
string* phs = new string("Memory Managements");
```

​		等价于

```
void* tempName = operator new(sizeof(string));
call the func >> string::string("Memory Managements"); on tempmemory
string* ps = static_cast<string*>(memory);
```

​		还有一种有趣的new ，叫placement new. 啥意思？就是我们已经知道了指定了一个地方就要放摸一个类的对象，那就可以用之

```C++
class Widget{
    public:
    	Widget(size_t size);
    ...
};

Widget* constructWidgetInBuffer(void* buffer,size_t size){
 	return new(buffer) Widget(size);   
}
```

​		欸我的嘛，抽象！其实这是在隐式的调用operator new

```C++
void* operator new(size_t size,void* locations){
    
    return locations;
    
}
```

#### Deletion && Deallocation

​		为了避免 resource leak （资源泄露），每一个动态分配行为都必须分配一个。函数operator delete 对于内建的delete operator 对于内建的 delete operator ，好像operator new 对于 new operator 一样。

```C++
string* ps;
//...
delete ps;
```

 		你的编译器必须产生怎样的代码？它必须可以析构ps所指对象。又可以释放该对象占用的内存。

​		内存释放动作由于函数operator delete 执行。通常声明如下：

```C++
void operator delete(void* memoryToBeDeallocated);
```

​		由此delete ps;

​		造成编译器产生这样的代码：

```C++
ps->~string();
operator delete(ps);
```

​		这里呈现的一个暗示就是，如果你只打算处理原始的，未设置初值的内存，应该完全回避new operator 和 delete operators。改用operator new取得内存并以 operator delete 归还给系统。

```C++
void* buffer = operator new(50*sizeof(char));
//...
operator delete(buffer);    
```

 		这组行为在C++相当于malloc和free.

​		如果你使用placement new, 在某内存块中产生的对象，你应该避免对那块内存使用 delete operator. 因为delete operator调用operator delete释放内存，但是该内存含有的对象最初并非是由operator new 分配得来的。毕竟placement new只是返回它所接受的指针而已，谁知道那个指针从哪里来呢？所以为了抵消该对象的构建器的影响，我们选择直接调用对象的destructor。

```C++ 
void* mallocShared(size_t size);
void freeShared(void *memory);
void *sharedMemory = mallocShared(sizeof(Widget));

Widget* pW = constructWidgetInBuffer(sharedMemory,10);
...
// delete pW; 不要这样做！没有意义，因为sharedMemory来自mallocShared函数而不是new 出来的！
pW->~Widget();//可以的！手动调用析构器是允许的
freeShared(pW);// 可以的！释放pW所指向的内存，不调用任何destructor!
```

#### Arrays数组

​		下面，我们考虑一些更远的事情，我是说：

```C++
string* ps = new string[10];
```

​		用的还是new operator，但是这次是数组！于是，我们实际上调用的是它的兄弟oprator new[ ]!当然这也就意味着我们可以重写之，但是往往重写全局的new函数是不明智的，因为其他的new operator也会发生行为的改变而使得程序发生剧烈的变化！

​		类似的，删除使用了new operator

## 异常处理

​		C++增加了Exceptions 之后，改变了太多的事情。比如说原始指针的使用成为了一个高风险事件，资源泄露的风险也是大增。

​		但是为了使程序可以在触发异常后安全的退出程序，就必须使用它来处理推出前的工作！

### 条款9：使用destructor来防止内存泄漏

​		假设我们现在正在书写一个类（Adorable Little Animal）ALA，我们在之后派生出来了小猫和小狗两个类

![image-20230519100041781](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More Effective C++ 1\image-20230519100041781.png)

​		为了实现领养工作，我们在抽象类下书写虚函数：

```C++ 
#include<iostream>
#include<string>
using namespace std;
class ALA {

public:
	virtual void processAdoption() = 0;// 强迫重写

protected:

	string name;
};

class Puppy : public ALA{
public:
	virtual void processAdoption();
};

class Kitten :public ALA {
public:
	virtual void processAdoption();
};
```

​		大致如此

​		现在我们需要读取星系返回一个ALA指针

```C++
ALA* readALA(istream& s);// 不在谈论怎么实现
```

​		于是，我们的收养问题实际上可以这样书写：

```C++
// 框架
void processAdoption(istream& dataSource){
	while(dataSource){
        ALA *pa = readALA(dataSource);
        pa->processAdoption();
        delete pa;
    }
}
```

​		这要求我们函数走遍dataSource，处理所有的信息，显然的——我们调用一次，就必须释放一次！

​		现在出现问题了：假如说我们的 `pa->processAdoption()`抛出了一个异常！麻烦大了，这个异常会追溯到调用端，导致`delete pa;`被跳过了，也就是说，只要触发一次异常，资源泄露一次！

​		这个时候，C++的Exception就可以出马了：

```C++ 
void processAdoption(istream& dataSource){
	while(dataSource){
        ALA *pa = readALA(dataSource);
       try{
           pa->processAdoption();
       }
        catch(...){
            delete pa;
            throw;//再把异常传递出去
        }
        delete pa;
    }
}
```

​		嘿！实在是太麻烦了！为什么不让delete代码剧中于一处呢？这就是智能指针的来源！我们只需要使用智能指针指向之，当发现需要被析构的时候就直接析构就好了。

```C++
void processAdoption(istream& dataSource){
    while(dataSource){
        unique_ptr<ALA> pa(readALA(dataSource));
        pa->processAdoption();
    }
}
```

​		隐藏在智能指针背后的理念是——以一个对象存放“必须自动释放的资源”，并且是依赖他自己的destructor来干这样的事情。

​		下面来看窗口设计，比如说我们来看使用窗口显示信息

```C++
void displayInfo(const Information& info){
    WINDOW_HANDLE w(createWindow());
    
    //displayInfo here
    
    destroyWindow(w);
}
```

​		还是先前的问题，如果允许时发生了exception，我们怎么办？

​		我们设计一个class：

```C++
class WindowHandle{
    public:
    	WindowHnadle(WINDOW_HANDLE handle):w(handle){};
    	~WindowHandle(){destroyWindow(w)};
    	operator WINDOW_HANDLE(){return w;};
    
    private:
    	WINDOW_HANDLE w;
    	WindowHandle(const WindowHandle&);
    	WindowHandle& operator=(const WindowHandle);
};
```

​		我们把复制和赋值行为给静止了，同时还给予了一个隐式操作符！，于是，这个函数的设计变得十分的简单：

```C++ 
void displayInfo(const Information& info){
   	WindowHandle w(createWindow());
    //displayInfo here
}
```

​		现在我们把它作为临时对象可以销毁了！

### 条款10：在constructor内部阻止内存泄漏

​		我们再说一遍，Exception的出现不太好，比如说我们正在写通讯录：

```C++ 
#include<iostream>
#include<string>
#include<list>
using namespace std;
class Image {
public:
	Image(const string& imageDataFileName);
};

class AudioClip {
public:
	AudioClip(const string& audioDataFileName);
};

class PhoneNumber {

};

class BookEntry {
public:
	BookEntry(
		const string& name,
		const string& addr = "",
		const string& imageFile = "",
		const string& audioClipFile = ""
	);
	~BookEntry();

	void addPhoneNumber(const PhoneNumber& phoneNumber);

private:
	string theName;
	string theAddr;
	list<PhoneNumber> thePhone;
	Image* theImage;
	AudioClip* theAudioClip;
};

BookEntry::BookEntry(
	const string& name,
	const string& addr = "",
	const string& imageFile = "",
	const string& audioClipFile = ""
) :theName(name), theAddr(addr), theImage(0), theAudioClip(0) {
	if (imageFile != "") {
		theImage = new Image(imageFile);
	}

	if (audioClipFile != "") {
		theAudioClip = new AudioClip(audioClipFile);
	}
}

BookEntry::~BookEntry() {
	delete theImage;
	delete theAudioClip;
}
```

​		但是当现在有了异常之后，假使我们正在初始化的对象抛出异常，就还会发生资源泄漏，即使使用智能指针也不行，因为其调用的destructor要求对象必须已经构建完整！

​		解决的办法是，在constructor内部就完成异常处理！

​		

```C++
BookEntry::BookEntry(
	const string& name,
	const string& addr = "",
	const string& imageFile = "",
	const string& audioClipFile = ""
) :theName(name), theAddr(addr), theImage(0), theAudioClip(0) {
	try
	{
		if (imageFile != "") {
			theImage = new Image(imageFile);
		}

		if (audioClipFile != "") {
			theAudioClip = new AudioClip(audioClipFile);
		}
	}
	catch (...) {
		delete theImage;
		delete theAudioClip;
		throw;// 
	}
}
```

​		清除这个过程还是可以抽象成一个私有函数！把他放到类里去：

```C++
#include<iostream>
#include<string>
#include<list>
using namespace std;
class Image {
public:
	Image(const string& imageDataFileName);
};

class AudioClip {
public:
	AudioClip(const string& audioDataFileName);
};

class PhoneNumber {

};

class BookEntry {
public:
	BookEntry(
		const string& name,
		const string& addr = "",
		const string& imageFile = "",
		const string& audioClipFile = ""
	);
	~BookEntry();

	void addPhoneNumber(const PhoneNumber& phoneNumber);

private:
	string theName;
	string theAddr;
	list<PhoneNumber> thePhone;
	Image* theImage;
	AudioClip* theAudioClip;
	void cleanUp();
};

void BookEntry::cleanUp() {
	delete theImage;
	delete theAudioClip;
}

BookEntry::BookEntry(
	const string& name,
	const string& addr = "",
	const string& imageFile = "",
	const string& audioClipFile = ""
) :theName(name), theAddr(addr), theImage(0), theAudioClip(0) {
	try
	{
		if (imageFile != "") {
			theImage = new Image(imageFile);
		}

		if (audioClipFile != "") {
			theAudioClip = new AudioClip(audioClipFile);
		}
	}
	catch (...) {
		cleanUp();
		throw;// 
	}
}

BookEntry::~BookEntry() {
	cleanUp();
}
```

​		我们再次改进：

```C++ 
class BookEntry {
public:
	BookEntry(
		const string& name,
		const string& addr = "",
		const string& imageFile = "",
		const string& audioClipFile = ""
	);
	~BookEntry();

	void addPhoneNumber(const PhoneNumber& phoneNumber);

private:
	string theName;
	string theAddr;
	list<PhoneNumber> thePhone;
	Image* const theImage;
	AudioClip* const theAudioClip;
	void cleanUp();
};
```

​		现在外面就必须通过初值链表的方式才会给予之赋值。这样就可以这样给予一个安全的初始化方式

```C++ 
BookEntry::BookEntry(
	const string& name,
	const string& addr = "",
	const string& imageFile = "",
	const string& audioClipFile = ""
) :
theName(name), 
theAddr(addr), 
theImage(imageFile != ""?new Image(ImageFile):0), 
theAudioClip(audioClipFile != ""? new AudioClip(audioClipFile):0)
```

​		但是这又把问题绕回去了！

​		于是，为了使异常不流到外面，外面直接使用组合的方式完成任务：其构造函数放到类私有的地方：

```C++
class BookEntry{
    public:
	BookEntry(
		const string& name,
		const string& addr = "",
		const string& imageFile = "",
		const string& audioClipFile = ""
	);
	~BookEntry();

	void addPhoneNumber(const PhoneNumber& phoneNumber);

private:
	string theName;
	string theAddr;
	list<PhoneNumber> thePhone;
	Image* const theImage;
	AudioClip* const theAudioClip;
	void cleanUp();
    Image* initImage(const string& imageFile);
    AudioClip* initAudioClipFile(const string& audioClipFile);
};
```

​		于是可以改写了：

```C++
BookEntry::BookEntry(
	const string& name,
	const string& addr = "",
	const string& imageFile = "",
	const string& audioClipFile = ""
) :
theName(name), 
theAddr(addr), 
theImage(initImage(imageFile)), 
theAudioClip(initAudioClipFile(audioClipFile))
```

​		把异常处理转换到函数的内部：

```C++
Image* BookEntry::initImage(const string& imageFile){
    if(imageFile != "")
        return new ImageFile(imageFile);
    else return 0;
}//这里不用，因为他是第一个被初始化，出现了其他问题会直接被释放
```

```C++
AudioClip* BookEntry::initAudioClipFile(const string& audioClipFile){
	try{
        if(audioClipFile != ""){
            return new AudioClip(audioClipFile);
        }
       	else return 0;
    }
    catch(...){
        delete theImage;
        throw;
    }
}
```

​		好吧，维护有些困难！那就是用`unique_ptr`!

```C++ 
class BookEntry{
    public:
	BookEntry(
		const string& name,
		const string& addr = "",
		const string& imageFile = "",
		const string& audioClipFile = ""
	);
	~BookEntry();

	void addPhoneNumber(const PhoneNumber& phoneNumber);

private:
	string theName;
	string theAddr;
	list<PhoneNumber> thePhone;
	const unique_ptr<Image> theImage;
	const unique_ptr<AudioClip> theAudioClip;
	void cleanUp();
    Image* initImage(const string& imageFile);
    AudioClip* initAudioClipFile(const string& audioClipFile);
};
```

​		这样，就可以回到上一个设计了：

```C++
BookEntry::BookEntry(
	const string& name,
	const string& addr = "",
	const string& imageFile = "",
	const string& audioClipFile = ""
) :
theName(name), 
theAddr(addr), 
theImage(imageFile != ""?new Image(ImageFile):0), 
theAudioClip(audioClipFile != ""? new AudioClip(audioClipFile):0)
```

​		同时，不在需要构建手写destructor了，直接放：

```C++
BookEntry::~BookEntry()
```

###  条款11 禁止异常流出destructor

​		假设现在外面的析构爆发问题了，我们的办法是：在里头使用try_catch语句接受处理之，甚至是这样：

```C++
Session::~Session(){
    try{
        logDestruction(this);
    }
    catch(...){}
}
```

​		这使得异常直接被吸收，防止程序调用std::abort()造成释放不完全！

### 条款12：了解“抛出一个异常”与“传递一个参数”或者是“调用一个虚函数的区别”

​		首先声明：我们调用函数返回到的是函数的调用端（除非失败了），而异常抛出一定不会回到抛出端！

​		如：

```C++
istream operator<<(istream& s,Widget& w);
void passAndThrowWidget(){
    Widget localWidget;
    cin >> localWidget;
    throw localWidget;
}
```

​		我们把localWidget交到operator>>手里的时候，没有发生复制行为，而是绑定到reference上操作！（passByReference）,但是Exception不一样！无论是值传递还是引用传递，他都会发生复制行为！这是容易理解的：我们一旦调用了`throw localWidget`，程序离开函数，造成了`localWidget`析构，我们的catch如果是reference传递，那传的是一具尸体！好吧，我们就不得不复制了！这造成了throw是很慢的（特别是对象很大的时候）

​		现在事情复杂起来了！假使我们：

```C++
class Widget{};
class SpecialWidget:public Widget{};
void passAndThrowWidget(){
    SpecialWidget localSpecialWidget;
    ...
    Widget& rw = localSpecialWidget;
    throw rw;
}
```

​		不是SpeicalWidget类型！因为这里抛出的是静态类型！复制的永远会是对象的静态类型！这是我们需要注意的：

```C++
catch(Widget& w){
    ...
    throw;
}
// and
catch(Widget& w){
    ...
    throw w;
}
```

​		不是一回事情，前者传入的啥抛出的就是啥！不会发生复制行为。但是第二种就会！于是，有必要对那些就是想要处理的一场样本的对象直接使用

```C++
throw;
```

​		即可！

​		对于继承体制的异常处理：必须指出：一个接受基类的catch会接受基类和其派生类！而接受派生类的catch只管派生类：

```C++
try{
    ...
}
catch(base_error){}
catch(derived_error){}
```

​		上面的这个设计不合适！因为derived_error catch不到任何异常！这跟虚函数：”最吻合调用机制“不同，catch是最先吻合的调用机制。

​		总结一下我们的长篇大论：

​		首先：exception object总是会被复制，使用pass by val会被复制两次！而传递函数的参数则不会

​		其次：跑出去成为exception的对象允许类转换的动作，比被传递到函数去的对象少。

​		最后，catch字句是源码顺序调用优先而不是吻合度调用优先！

### 条款13 以引用传递捕捉异常

​		我们有三种方式传递异常：值传递，引用传递，指针传递。

​		先考虑指针传递：不得不说因为不复制对象而显得十分搞笑，但是不大好，程序员们往往会忘记：

```C++
void someFunc{
    exception ex;
    
    //...
    
    throw &ex;
}
```

​		对象早就被析构了！传递了一个非法指针！

​		好吧，开堆上：

```
void someFunc{
    exception ex;
    
    //...
    
    throw new ex;
}
```

​		那问题更大了，用户程序员没有办法知道：他们什么时候需要释放，什么时候不需要释放！这下麻烦了！还是不要用之为妙。

​		值传递呢？除了低效以外，如果我们传递了派生类指针，那意味着后续的处理下，对象都是基类，调用的虚函数是基类虚函数！程序爆炸了！

​		于是还是引用传递好！避免了上述的问题！

### 条款14：明智使用exception specification

​		谨慎使用他！

​		如：

```C++
void f1();// throw anything
void f2()throw(int){
    ...
    f1();
    ...
}    
```

​		这下麻烦了，我们承诺了f2只会抛出int的意外，但是是事实f1会抛出一堆其他的意外！编译器不会帮助你检查这个事情，他默许了这样非法的行为。

​		同时，不要将template和 特殊异常一起使用！因为我们无法知道template会抛出什么异常，导致未定义行为的发生！

​		其二，如果A函数调用了B函数，若B没有特殊异常，A也不要有！但是很容易出错的：就是回调函数的问题：

```C++
typedef void(*CallBackPtr)(int X,int Y,void* dataToPassBack);

class CallBack{
    public:
    	CallBack(CallBackPtr fPtr,void* dataToPassBack):
    		func(fPtr),data(dataToPassBack);
    void makeCallBack(int X,int Y)const throw();
    private:
    	CallBackPtr func;
    	void* data;
};

void CallBack::makeCallBack(int X,int Y)const throw(){
    func(X,Y,data);
}
```

​		`makeCallBack`函数内部就违反了特殊异常，谁知道func里面抛出了什么异常呢？但是这就可以：

```
typedef void(*CallBackPtr)(int X,int Y,void* dataToPassBack) throw();
```

​		这样就强迫函数必须书写`throw()`后缀保证函数不会跑出任何异常！

​		还有其三：可以使用转化异常的方式防止出事情：

```C++
class UnexpectedExeception{};
void convertException(){
    throw UnexpectedExeception();
}
```

​		这样就好了！

### 条款15：了解异常处理的代价

​		我的评价是简单的：一坨大便，下一个（）

​		好吧，异常处理是能少用就少用的：首先是程序开销巨大，其次：跳转使得程序逻辑结构不再清晰。完事！

## 效率

### 条款16：谨记 80 - 20 法则

​		一个程序80%的资源用在20%的代码上。是的，80%的代码执行时间都花在那20%的代码上，80%的内存都被那20%的代码占去。。。当然，这就给我们的代码优化工作给出了重要的提示！也就是说，我们有必要把精力放在那20%的重要代码上去！

### 条款17：考虑使用缓式评估

​		啥意思，就是拖延战术！

#### 引用计数

​		考虑

```c++
class String{};
String s1 = "Hello";
String s2 = s1;
```

​		急式评估，犹如我们大部分人干的那样，在运行时执行代码

```C++
String s2 = s1;
```

​		时，就立即去调用拷贝构造函数！快速的跑去复制成员和做其他的相关的操作。但事实上，我们也有可能就不会用到他——或者说，不必现在立刻马上的用到他，那为什么不做薄记工作，也就是等到什么时候用到了再说呢？这就是所谓的缓式评估。

​		当然，这里再强调一遍——缓式评估要求数据共享！也就是说——任何需要数据更改的操作，都必须做拷贝备份处理

#### 读还是写？

​		嘛，make a assumption that 我们要对一个字符串处理：

```C++
std::string a = "111";
char a = a[1]; // just read the string
a[1] = '2' // probably make a copy
```

​		显然成本不太一样——如果我们希望做一个备忘录的话，明眼人都知道第一个的工作量远小于第二个。

​		于是，有必要采取相关的行动——直到万不得已的时候，采取决定是怎样操作

#### 缓式读取

​		现在，我们需要从一个数据库读取一些非常大的东西——显然，直接把整个库扔过来（返回拷贝这件事情，嗯，开销太大了）是不合适的。于是，我们有必要先让程序带着空壳跑到需要数据的地方，再通过指针逐步返回完成工作！

#### 缓式表达式的评估

​		假设我们想要整一个——对，矩阵！两个1000 x 1000的矩阵相加！甚至相乘！

```C++
class Mat{
    Mat(int col, int row); // init a matrix;
};

int main(){
    
    Mat a(1000,1000);
    Mat b(1000,1000);
    c = a + b;
    ...
}
```

​		我们要做1000 x 1000次加法！太疯狂了！但事实上，我们更多需要的可能只是里面的某一项，何不直接记录下，等到需要取的时候，根据需求来取呢？是这样的。

### 条款18：分期摊还预期的计算成本

​		辩证的——如果我们遵循机器式的——把一切程序的行为都设计成为缓式运算的话，有时也并不恰当。还有一些时候，急式评估是更好的！

​		这样的情况往往出现在程序的某一个Section下需要频繁的调用，可以先讲一些内容使用一些数据结果存储之。到时候就不必再去重新计算。

​		比如说，在一些程序中，我们应用DynamicArray 来存储数据，当发生存入比存储空间小的时候，不妨一次扩展更多的空间而不是一次就扩展一个，毕竟，大概率下你要存储的东西会比较大的多出原来的空间，不妨开辟更多的元素，防止扩展函数被频繁的调用。

​		可以预见的是——这样的策略往往会要求更多的内存！于是，将条款17和18都好好应用于结合是必要的！

### 条款19：了解临时对象的产生

​		下面来看一个通用的Swap函数：

```C++
template<class T>
void swap(T& object1, T& object2){
    T temp = object1;
    object1 = object2;
    object2 = temp;
}   
```

​		我们习惯上称呼temp是一个临时对象，但事实上它是函数的一个局部对象.而运作产生一个临时对象可能并不会提升程序性能。于是我们在程序运转上，可以考虑“返回值优化”。

### 条款20：完成返回值优化工作

​		函数如果返回对象的话，往往会对程序的性能造成巨大的损伤。下面我们来看一个例子，和程序设计时常见的误区：

```C++
class Rational{
    public:
    	Rational(int numerator = 0, int denominator = 1);
    ...
        int numerator() const;
    	int denominator() const;
}

const Rational operator*(const Rational& lhs,const Rational& rhs);
```

​		好吧，我们大部分真是竭力的不让他返回值：

```C++
// sometime we are trying to return a pointer to the value in heap
const Rational* operator*(const Rational& lhs,const Rational& rhs);
Rational a = 10;
Rational b(1, 2);
Rational c = *(a * b);
```

​		看起来不错，但是有一个问题——用户程序员会记得删除它嘛？不删除则是会导致内存泄漏的！

​		于是还有人写出了更加危险的写法：

```C++
const Rational& operator*(const Rational& lhs,const Rational& rhs){
    Ratioanl result = (lhs.numerator()*rhs.numerator().lhs.denominator()*rhs.denominator());
    
    return result;
}
```

​		恭喜你返回了一具尸体，让程序在未定义的路上一路狂奔。好吧，有一些程序，我们是不得不返回对象的。所以——

```C++
const Rational operator*(const Rational& lhs,const Rational& rhs){
    return Rational(lhs.numerator()*rhs.numerator().lhs.denominator()*rhs.denominator());
}
```

​		这样，你就不必担心释放的问题了！

# More effective C++2

## 条款22 考虑以操作符复合形式（op=）来取代独身形式

​		对于大部分的程序员，他们希望——

```
x = x + y;
x = x - y;
```

​		的同时

```
x += y;
x -= y;
```

​		的形式也可以被接受。

​		为了让复合形式和独身形式都可以很好的运作——我们选则：让前者作为基础来实现

```C++
class Rational{
    public:
    	Rational& operator+=(const Rational& rhs);
    	Rational& operator-=(const Rational& rhs);
}

const Rational operator+(const Rational& lhs,const Rational& rhs){
    return Rational(lhs) += rhs;
}

const Rational operator-(const Rational& lhs,const Rational& rhs){
    return Rational(lhs) -= rhs;
}
```

​		这样的话，我们就只需要维护符合操作符就好了。

​		事实上，为了扩展性更强一些，我们一般的使用模板来完成通用化的工作：

```C++
template<class T>
const T operator+(const T& lhs,const T& rhs){
    return T(lhs) += rhs;
} 
template<class T>
const T operator-(const T& lhs,const T& rhs){
    return T(lhs) -= rhs;
} 
```

​		但是现在为止我们都没有考虑效率的问题。

​		注意到复合操作类型不会花费时间构造一个巨大的对象返回。于是我们这样的设计可以让客户程序员选择效率与方便维护中二选一：

```C++
// 易于维护的
Rational a,b,c,d,result;
result = a + b + c + d;

// 追求效率的
result = a;
result += b;
result += c;
result += d;
```

​		程序的灵活性更好了！

## 条款23：考虑使用其他库

## 条款24：了解virtual functions, multiple functions, virtual base classes runtime type identification的成本

​		当一个虚函数被调用，执行的代码必须对应于调用者的动态类型。我们的编译器可以做到虚函数的处理得益于 virtual table 或 virtual table pointers

​		我们的vtbl 通常是函数指针架构产生的数组。

比如：

```C++
class C1{
    public:
    	C1();
    	virtual ~C1();
    	virtual void f1();
    	void f4() const;
}
```

![image-20230527133400105](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\image-20230527133400105.png)

​		现在，一旦我们的子类继承了父类，并且自己重新实现了一些虚函数，那么——C2（假使它继承了C1）这张虚函数表的新改写函数就会换成子类自己的！

​		避免将虚函数声明为内联的inline,编译器也会自动忽视之。下面我会提到为什么

​		当然，只有虚函数表是不够的——我们的类中往往会增加一个函数数组指针，指向这个表！一旦发生继承，这个表就会被一大堆成员包围。

​		下面来看对于体系类的虚函数调用。还是回到C1，C2类的表

```C++
void makeACall(C1* pC1){
	pC1()->f1();
}
```

​		如果我们只看这点代码，完全不知道程序运行时会调用哪一段代码。编译器是这样处理的：

1. 根据对象的vptr 找到 vtbl

2. 找到被调用的函数在vtbl的指针，然后调用之。

   ```
   (*pC1->vptr[i])(pC1);
   ```

    你瞧！只有在运行的时候我们才会直到究竟是哪个！而inline跟virtual的设计理念完全冲突！这就是为什么不要给虚函数添加inline!

​		下面考虑多重继承（相当恐怖的）

​		这是一个菱形继承：

![image-20230527134602652](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\image-20230527134602652.png)

​		现在，我们视A作为最基本的类：

![image-20230527134822239](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\image-20230527134822239.png)

​		当A内有任何一点虚函数

![image-20230527134941853](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\image-20230527134941853.png)

​		我们看到了虚函数是如何使得对象变大的了

​		RTTI作为运行时获取对象类型，一个class只需要一个就可以了。我们在vtbl的开头加上一个 type_info对象就可以帮助识别。

| 性质     | 对象大小 | Class数据量增加 | 内联几率降低 |
| -------- | -------- | --------------- | ------------ |
| 虚函数   | 是       | 是              | 是           |
| 多重继承 | 是       | 是              | 否           |
| 虚拟基类 | 往往如此 | 有时候          | 否           |
| RTTI     | 否       | 是              | 否           |

## 条款25：将构造函数和非成员函数虚化

​		我们有必要将构造函数和非成员函数虚化——这是因为我们之间有关系的类可以做到一个构造函数完成更多的事情。而且更加的省精力。

​		构造函数的虚化有助于我们在实际调用的时候返回期望对象的构造函数！

## 条款26 限制某个class所能产生的对象数量

### 允许0个或者1 个对象产出

​		阻止一个类的产生的最简单的方法就是把构造器放private里面。

​		那一个呢？配合static和接口函数！

```C++
class PrinterJob;
class Printer{
    public:
    	void submitJob(const PrinterJob& job);
    	void reset();
    	void performSelfTest();
    	friend Printer& thePrinter();
    private:
    	Printer();
    	Printer(const Printer& rhs);
    	...
}

Printer& thePrinter()
{
    static Printer p;
    return p;
}
```

​		这样一调用，我们就总是调用那个在静态区的变量。

​		我们也可以把这一大堆东西放到namespace里去，防止冲突！

​		有一个细节：我们为什么不把这个函数：

```C++
Printer& thePrinter()
{
    static Printer p;
    return p;
}
```

​		设置成inline呢？答案是，防止被复制——因为我们把调用函数这个动作直接改成执行代码，这就意味着——这个对象可能会被复制！不要在带有locale static对象的函数中内联！

​		注意，**一个构造函数是private 的类是不允许被继承的！**（没办法显著的调用构造器）于是，**避免一个具体类继承另一个具体类！**

### 允许对象生生灭灭

​		注意到：

```
create Printer object p1;
use p1;
delete p1;
create Printer object p2;
use p2;
delete p2;
create Printer object p3;
use p3;
delete p3;
```

​		这样的事情不违反只允许一个对象！但是却不被允许，那么我们有必要整一个新办法

​		我们加上一个计数器就好了：

```C++
class Printer{
	public:
    	class TooManyObj{};
    	static Printer* makePrinter();
    	~Printer();
    	void submitJob(const PrinterJob& job);
    	void reset();
    	void performSelfTest();
    
    private:
    	static size_t numObjects;
    	static size_t numObjects = 10;
    	Printer();
    	Printer(const Printer& rhs);
}

	size_t Printer::numObjects = 0;
	Printer::Printer(){
        if(numObjects >= max_obj){
            throw TooManyObj();
        }
        ...
        ++numObjects;
    }
}
```

​		也有程序员使用专门计数的类！但这里就不再展开了。

### 判断对象在哪里（在不在heap?）

​		不应当直接在class里声明一个bool变量，然后塞到operator new这个函数下，因为：

```C++
UPNumber* numArr = new UPNumber[100];
```

​		这下坏了，编译器可能是：先调用operator new在调用构建器！（先开空间，在初始化，我们上面的办法就失效了！）

​		于是，不妨使用计组学的特性?

![image-20230527142543682](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\image-20230527142543682.png)

​		可以给出这样的代码：

```C++
bool onHeap(const void* addr){
	char onStack;
    return address < &onTheStack
}
```

​		但是别忘了，我们还有静态区！它无法区分和heap对象和static对象！

​		事实上，没有通用的办法！

### 静止对象产生在heap上

​		很简单了：直接把operator new 和operator delete直接扔到私有区！

## 条款27：auto_ptr

​		**智能指针主要用于动态内存的管理,同时提供给用户与内置指针一样的使用方法,本条款主要涉及智能指针在构造与析构,复制和赋值,解引等方面的注意点,而非智能指针的实现细节.**

### 		 智能指针的构造,赋值,析构

  	智能指针的copy constructor,assignment operator,destructor对应于不同的观念而有不同的实现,主要有三种选择:
  	
  	不允许对象的共享,在调用copy constructor和assignment时转移对象所有权,这样在调用destructor时就可以直接delete智能指针内含的内置指针,如标准库的auto_ptr,其实现可能像这样:

```C++
template<class T>
class auto_ptr {
public:
    ...
    auto_ptr(auto_ptr<T>& rhs); 
    auto_ptr<T>&  operator=(auto_ptr<T>& rhs); 
    ...
};
template<class T>
auto_ptr<T>::auto_ptr(auto_ptr<T>& rhs)
{
    pointee = rhs.pointee; 
    rhs.pointee = 0; // 转移对象所有权
} 
template<class T>
auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<T>& rhs)
{
    if (this == &rhs) // 自我赋值的情况
        return *this; 
    delete pointee; 
    pointee = rhs.pointee; // 转移对象所有权
    rhs.pointee = 0; 
    return *this;
}
```

  		值得注意的是,由于auto_ptr的copy constructor被调用时,对象所有权便转移了,像这样:

```C++
void printTreeNode(ostream& s, auto_ptr<TreeNode> p)
{ s << *p; }
int main(){
    auto_ptr<TreeNode> ptn(new TreeNode);
    ...
    printTreeNode(cout, ptn); //通过传值方式传递auto_ptr
    ...
}
```

  		调用printTreeNode后,ptn所指向的内存便被释放,内含的内置指针也被置为0,但这并不符合用户的预期.这说明不能使用pass-by-value的方式传递auto_ptr给函数,只能使用pass-by-reference.
  	
  		使用这种策略实现的智能指针的destructor可能像这样:

```C++
template<class T>
SmartPtr<T>::~SmartPtr()
{
    if (*this owns *pointee) {
        delete pointee;
    }
}
```

  	2). 不允许对象的共享,调用copy constructor和assignment operator时进行深度拷贝——产生新对象.这种设计思想较简单,缺点也较明显:新对象的产生需要消耗资源.这里不再讨论
  	
  	3). 允许对象的共享,使用引用计数,调用copy constructor和assignment operator增加引用计数的个数.当引用计数的个数为0时便析构对象并释放内存,如标准库的shared_ptr,关于引用计数的具体实现见[条款29](http://i.cnblogs.com/PostDone.aspx?postid=4857432&actiontip=存为草稿成功).

### 		实现Dereference Operators(解引操作符)

  	主要讨论operator*和operator->的实现,前者放回所指对象的引用,像这样:

```C++
template<class T>
T& SmartPtr<T>::operator*() const
{
    perform "smart pointer" processing;
    return *pointee;
}
```

  	如果程序采用了lazy fetching(见[条款17](http://www.cnblogs.com/reasno/p/4830677.html))策略,就有可能需要为pointers变换出一个新对象.需要注意的是,operator*返回的是引用,如果返回对象,可能会产生由于SmartPtr指向的是T的派生类对象而非T类对象而造成的切割问题.
  	
  	operator->和operator*类似,operator->返回指针.
  	
  	对于使用引用计数的shared_ptr,问题还未停止,它允许多个智能指针共享相同对象,但前提是这些指针所指向的对象相同.由于operator*和operator->返回所指对象的引用和指针,这可能导致其所指对象被更改,但原则上共享同一块内存的其他智能指针却要求所指对象保持不变.因此有必要在调用operator*和operator->的时候开辟一块新内存,使调用operator*和operator->的智能指针指向这块新内存以防止共享内存被篡改,像这样:

```C++
template<class T>
T& SmartPtr<T>::operator*() const{
    if(number of reference!=1){
        pointee=new T(*pointee);
        --reference number of the old object;
        set the reference number of the new object to 1; 
    }
    return *pointee;
}
```

### 测试Smart Pointers是否为Null

  	直接的策略是定义隐式转换操作符operator void*,使得以下操作可以通过编译:

```C++
if (ptn == 0) ... // 正确
if (ptn) ... // 正确
if (!ptn) ... //正确
```

  	但隐式转换操作符很容易被滥用,它使得不同类型的指针可以相比较,以下代码可以通过编译:

```C++
SmartPtr<Apple> pa;
SmartPtr<Orange> po;
...
if (pa == po) ...//可以通过编译
```

  	尽管pa和po是不同类型的智能指针,但由于没有定义Smart<Apple>和Smart<Orange>为参数的operator==,因此编译器默认调用operator void*,使得以上代码通过编译.
  	
  	一种差强人意的方法是允许测试null,但使用!操作符,如果内置指针为null,便返回true,客户端要测试智能指针是否为null,就要像这样:

```C++
SmartPtr<TreeNode> ptn;
...
if (!ptn) { 
    ...
}
else {
    ... 
}
```

  	但以下做法却被禁止:

```C++
if (ptn == 0) ... 
if (ptn) ...
```

  	`iostream`程序库不仅允许隐式类型转换`void*`,还提供`operator!` ,C++标准库中,"隐式转换为void*"已被"隐式转换为bool"取代,而operator bool总是返回operator!的反.

### 将Smart Pointers转换为Dumb Pointers

  	有时要兼容并未使用智能指针的程序库,就要允许智能指针到内置指针的转换,直接的思路还是隐式转换操作符:

```C++ 
template<class T>
class DBPtr {
public:
    ...
    operator T*() { return pointee; }
    ...
};
```

  但是正如多次强调的,隐式转换操作符很容易被滥用,它使得客户可以轻易获得内置指针,从而绕过智能指针的控制,像这样:

```C++ 
class Tuple{...};
void processTuple(DBPtr<Tuple>& pt)
{
    Tuple *rawTuplePtr = pt; // 得到内置指针
    use rawTuplePtr to modify the tuple
}
```

  		像这样的操作也会被通过:

```C++ 
DBPtr<Tuple> pt=new Tuple;
delete pt;//通过,执行隐式类型转换
```

  		但这几乎肯定会造成错误,因为pt的析构函数执行时可能再次delete同一块内存.
  	
  		此外,对于采用引用计数的实现版本来说,"允许clinets直接使用dumb pointers"往往会导致导致簿记方面的错误,造成严重后果,
  	
  		即使实现了隐式转换操作符,但它还是不能做到提供和内置指针完全一样的行为,因为编译器禁止连续隐式调用自定义的隐式类型转换,像这样的使用会失败:

```C++ 
class TupleAccessors {
public:
    TupleAccessors(const Tuple *pt); // Tuple到TupleAccessor的转换
    ... 
};
TupleAccessors merge(const TupleAccessor& ta1,const TupleAccessors& ta2);
DBPtr<Tuple> pt1, pt2;
...
merge(pt1,pt2);//调用会出错
```

  		尽管`DBPtr<Tuple>`到`Tuple*`再到`TupleAccessor`的转换就可以匹配merge的参数,但编译器禁止这么做.

​		  解决方法是使用普通成员函数进行显式转换以代替隐式转换操作符,像这样:

```C++ 
class DBPtr {
public:
    ...
    T* toPrimary() { return pointee; }
    ...
};
```

###  Smart Pointers和"与继承有关的"类型转换

  		两个类之间有继承关系,但以这两个类为参数具现化的类模板却没有继承关系,由于智能指针是类模板,因此智能指针的包装会屏蔽内置指针的继承关系,例如对于以下继承层次:

```C++ 
class MusicProduct {
public:
    MusicProduct(const string& title);
    virtual void play() const = 0;
    virtual void displayTitle() const = 0;
    ...
};
class Cassette: public MusicProduct {
public:
    Cassette(const string& title);
    virtual void play() const;
    virtual void displayTitle() const;
    ...
};
class CD: public MusicProduct {
public:
    CD(const string& title);
    virtual void play() const;
    virtual void displayTitle() const;
    ...
}
void displayAndPlay(const MusicProduct* pmp, int numTimes)
{
    for (int i = 1; i <= numTimes; ++i) {
    pmp->displayTitle();
    pmp->play();
}
```

 	 整个继承体系像这样:

![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\699942-20151006212730503-151239962.png)

  	由于各个类的继承关系,可以利用指针的多态实现面向对象编程,像这样:

```C++ 
Cassette *funMusic = new Cassette("Alapalooza");
CD *nightmareMusic = new CD("Disco Hits of the 70s");
displayAndPlay(funMusic, 10);
displayAndPlay(nightmareMusic, 0);
```

  	但当指针经过封装成为智能指针之后,正如开始所说,以下代码将无法通过编译：

```C++ 
void displayAndPlay(const SmartPtr<MusicProduct>& pmp,int numTimes);
SmartPtr<Cassette> funMusic(new Cassette("Alapalooza"));
SmartPtr<CD> nightmareMusic(new CD("Disco Hits of the 70s"));
displayAndPlay(funMusic, 10); // 错误!
displayAndPlay(nightmareMusic, 0); // 错误!
```

这是由于`MusicProduct,Cassette,CD`之间有继承关系,但智能指`SmartPtr<MusicProduct>,SmartPtr<Cassette>,SmartPtr<CD>`之间却没有内在的继承关系.

  		最直接的解决方法是为每一个智能指针类定义一个隐式类型转换操作符,像这样:

```C++ 
class SmartPtr<Cassette> {
public:
    operator SmartPtr<MusicProduct>()
    { return SmartPtr<MusicProduct>(pointee); }
    ...
private:
    Cassette *pointee;
};
class SmartPtr<CD> {
public:
    operator SmartPtr<MusicProduct>()
    { return SmartPtr<MusicProduct>(pointee); }
    ...
private:
    CD *pointee;
};
```

  	这种方法可以解决类型转换的问题,但是却治标不治本:一方面,必须为每一个智能指针实例定义隐式类型转换操作符,这无疑与模板的初衷背道相驰;另一方面,类的继承层次可能很庞大,采用以上方式,继承层次的最底层类的负担将会非常大——必须为对象直接或间接继承的每一个基类提供隐式类型转换操作符.
  	
  		"将nonvirtual member function声明为templates"是C++后来接入的一个性质,使用它可以从根本上解决饮食类型转换的问题,像这样:

```C++ 
template<class T> 
class SmartPtr { 
public:
    SmartPtr(T* realPtr = 0);
    T* operator->() const;
    T& operator*() const;
    template<class newType> // 模板成员函数
    operator SmartPtr<newType>() 
    {
        return SmartPtr<newType>(pointee);
    }
    ...
};
```

  		这个成员函数模板将智能指针之间的隐式类型转换交由底层内置指针来完成,保证了指针转换的"原生态":如果底层指针能够转换,那么包装后的智能指针也能够进行转换.唯一的缺点是它是通过指针之间的隐式类型转换来实现指针的多态,也就是说,它实际上并不能区分对象之间的继承层次,假如扩充MusicProduct的继承体系,加上一个新的CasSingle class,像这样:

![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\699942-20151006213007737-1835434124.png) 

  那么对于以下代码:

![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\ContractedBlock.gif) ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\ExpandedBlockStart.gif)

```C++ 
template<class T>
class SmartPtr { ... }; 
void displayAndPlay(const SmartPtr<MusicProduct>& pmp,
int howMany);
void displayAndPlay(const SmartPtr<Cassette>& pc,
int howMany);
SmartPtr<CasSingle> dumbMusic(new CasSingle("Achy Breaky Heart"));
displayAndPlay(dumbMusic, 1);//错误，隐式类型转换函数的调用具有二义性
```

  	正如之前所言,使用隐式类型转换操作符实现的指针多态并不能区分对象的继承层次,也就是说将SmartPtr<CasSingle>转为SmartPtr<Cassette>&和转为SmartPtr<MusicProduct>&具有同样的优先级,因此造成二义性.而内置指针却能做到这一点,它优先将CasSingle绑定到Cassette&,因为CaSingle直接继承自Cassette.此外,以上策略还有移植性不高的缺点:有些编译器可能并不支持member templates.
  	
  	对于内置指针,const修饰的含义因其位置而不同:



```C++ 
CD goodCD("Flood");
const CD *p; // p 是一个non-const 指针,指向 const CD 对象
CD * const p = &goodCD; // p 是一个const 指针,指向non-const CD 对象;因为 p 是const,它必须在定义时就被初始化
const CD * const p = &goodCD; // p 是一个const 指针,指向一个 const CD 对象
```

  		但对于智能指针,只有一个地方可以放置const,因此cosnt只能施行于指针之上,而不能施行于指针所指对象之上:

```C++ 
const SmartPtr<CD> p=&goodCD;
```

  		要是const修饰所值对象很简单,像这样:

```C++ 
SmartPtr<const CD> p=&goodCD;
```

 		 由此方法可以实现和内置指针相同的四种指针:

```C++ 
SmartPtr<CD> p; // non-const 对象, non-const 指针
SmartPtr<const CD> p; // const 对象,non-const 指针
const SmartPtr<CD> p = &goodCD; // non-const 对象,const 指针
const SmartPtr<const CD> p = &goodCD; // const 对象,const 指针
```

  		但这种方法仍有缺陷,正如经由模板包装之后,有继承关系的两个类完全没有关系一样,经由智能指针模板包装后的const和non-const对象完全不同,像这样看起来理所当然的代码通不过编译:

```C++ 
SmartPtr<CD> pCD = new CD("Famous Movie Themes");
SmartPtr<const CD> pConstCD = pCD;
```

  		使用之前的隐式类型转换技术可以顺带解决这个问题,但又有所区别:const与non-const的转换是单向的,即可以对const指针做的事也可以对non-const指针进行,但可以对non-const指针做的事未必可以对const指针进行.这与public继承类似,利用这种性质,令每一个smart pointer-to-T-class public继承一个对应的smart pointer-to-const-T class:

```C++ 
template<class T> // 指向const 对象的
class SmartPtrToConst {
protected:
    union {
        const T* constPointee; // 提供给SmartPtrToConst 访问
        T* pointee; // 提供给SmartPtr 访问
    };
};
template<class T> 
class SmartPtr: public SmartPtrToConst<T> {
public:
    template<class constType>
    operator SmartPtrToConst<constType>();
    ... //没有额外数据成员
};
```

   		SmartPtrToConst使用了union,这样constPointee和pointee共享同一块内存SmartPtrToConst使用constPointee,SmartPtr使用pointee.
   	
   		 现在,使用SmartPtrToConst和SmartPtr分别代表指向const和non-const对象的智能指针,以下代码可以通过编译:

```C++ 
SmartPtr<CD> pCD = new CD("Famous Movie Themes");
SmartPtrToConst<CD> pConstCD = pCD;
```

\8. 从2-7的讨论可以看出,智能指针功能强大,但索要付出的代价也很高,此外,智能指针无论如何也不能完全替代内置指针.当然,尽管内置指针在实现和维护方面需要大量技巧,但与其强大的功能相比在多数情况下还是值得的.

## 条款28：引用计数

​		引用计数是这样一个技巧，它允许多个有相同值的对象共享这个值的实现。这个技巧有两个常用动机。第一个是简化跟踪堆中的对象的过程。一旦一个对象通过调用new被分配出来，最要紧的就是记录谁拥有这个对象，因为其所有者－－并且只有其所有者－－负责对这个对象调用delete。但是，所有权可以被从一个对象传递到另外一个对象（例如通过传递指针型参数），所以跟踪一个对象的所有权是很困难的。象auto_ptr（见Item M9）这样的类可以帮助我们，但经验显示大部分程序还不能正确地得到这样的类。引用计数可以免除跟踪对象所有权的担子，因为当使用引用计数后，对象自己拥有自己。当没人再使用它时，它自己自动销毁自己。因此，引用计数是个简单的垃圾回收体系。

​		第二个动机是由于一个简单的常识。如果很多对象有相同的值，将这个值存储多次是很无聊的。更好的办法是让所有的对象共享这个值的实现。这么做不但节省内存，而且可以使得程序运行更快，因为不需要构造和析构这个值的拷贝。

​		和大部分看似简单的主意一样，这个动机也有一个曲折而有趣的细节。在其中必须有一个正确实现的引用计数体系。在开始钻研细节前，让我们掌握一些基础。一个好主意是先着眼于我们将可能如何遇到多个对象有相同的值。这儿有一个：

```C++
class String {                     // the standard string type may

	public:                            // employ the techniques in this Item, but that is not required
  		String(const char *value = "");
  		String& operator=(const String& rhs);
		...

	private:
  		char *data;
};
String a, b, c, d, e;
a = b = c = d = e = "Hello";
```

​		看起来，对象a到e都有相同的值“Hello”。其值的形态取决于String类是怎么实现的，但通常的实现是每个string对象有一个这个值的拷贝。例如，String的赋值操作可能实现为这样：

```C++
String& String::operator=(const String& rhs)
{
  if (this == &rhs) return *this;         // see Item E17

  delete [] data;

  data =   new char[strlen(rhs.data) + 1];

  strcpy(data, rhs.data);

  return *this;                           // see Item E15

}
```

根据这个实现，我们可以推测，这5个对象及其值如下：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\20191114165634252.png)


其冗余是显然的。在一个理想的世界中，我们希望将上图改为这样：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\20191114165703168.png)

 

​		这里，只存储了一个“Hello”的拷贝，所有具有此值的String对象共享其实现。

​		实际世界中，实现这个主意是不可能的，因为我们需要跟踪多少对象共享同一个值。如果上面的对象a被赋了“Hello”以外的另外一个值，我们不能摧毁值“Hello”，因为还有四个对象需要它。另一方面，如果只有一个对象有“Hello”这个值，当其超出生存空间时，没有对象具有这个值了，我们必须销毁这个值以避免资源泄漏。

​		保存当前共享/引用同一个值的对象数目的需求意味着我们的那张图必须增加一个计数值（引用计数）：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\2019111416593759.png)

 

​		（有些人将其叫作use count，但我不是其中之一。C++有很多它自己的特性，最后需要的一个是专业名词的派别之争。）

​		创建一个带引用计数的String类并不困难，但需要注意一些细节，所以我们将略述这样一个类的大部分常用成员函数的实现。然而，在开始之前，认识到“我们需要一个地方来存储这个计数值”是很重要的。这个地方不能在String对象内部，因为需要的是每个String值一个引用计数值，而不是每个String对象一个引用计数。这意味着String值和引用计数间是一一对应的关系，所以我们将创建一个类来保存引用计数及其跟踪的值。我们叫这个类StringValue，又因为它唯一的用处就是帮助我们实现String类，所以我们将它嵌套在String类的私有区内。另外，为了便于Sting的所有成员函数读取其数据区，我们将StringValue申明为struct。需要知道的是：将一个struct内嵌在类的私有区内，能便于这个类的所有成员访问这个结构，但阻止了其它任何人对它的访问（当然，除了友元）。

​		基本设计是这样的：

```C++
class String {
public:

  ... // the usual String member
// functions go here

private:

  struct StringValue { ... };        // holds a reference count and a string value

  StringValue *value;                // value of this String

};
```

​		我们可以给这个类起个其它名字（如RCString）以强调它使用了引用计数，但类的实现不该是类的用户必须关心的东西，用户只关心类的公有接口。而我们带引用计数的String版本与不带引用计数的版本，其接口完全相同，所以为什么要用类的名字来把问题搅混呢？真的需要吗？所以我们没有这么做。

​		这是StringValue的实现：



```C++
class String {
	private:
	struct StringValue {
  		int refCount;
  		char *data;
  		StringValue(const char *initValue);
 		~StringValue();
		};

		...
};

String::StringValue::StringValue(const char *initValue): refCount(1)
{
  	data = new char[strlen(initValue) + 1];
  	strcpy(data, initValue);
}
String::StringValue::~StringValue()
{
  delete [] data;
}
```



​		这是其所有的一切，很清楚，这不足以实现带引用计数的String类。一则，没有拷贝构造函数和赋值运算；

​		二则，没有提供对refCount的操作。别担心，少掉的功能将由String类提供。StringValue的主要目的是提供一个空间将一个特别的值和共享此值的对象的数目联系起来。StringValue给了我们这个，这就足够了。

​		我们现在开始处理String的成员函数。首先是构造函数：

```C++
class String {
public:

  String(const char *initValue = "");

  String(const String& rhs);

  ...

};
```

​		第一个构造函数被实现得尽可能简单。我们用传入的char *字符串创建了一个新的StringValue对象，并将我们正在构造的string对象指向这个新生成的StringValue：

```C++
String::String(const char *initValue): value(new StringValue(initValue))
{

}
```

​		这样的用户代码：

```C++
String s("More Effective C++");
```

​		生成的数据结构是这样的：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\20191114170009545.png)

​		String对象是独立构造的，有同样初始化值的对象并不共享数据，所以，这样的用户代码：

```C++
String s1("More Effective C++");

String s2("More Effective C++");
```

​		产生这样的数据结构：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\2019111417004483.png)

​		消除这样的副本是可能的：通过让String（或StringValue）对象跟踪已存在的StringValue对象，并只在是不同串时才创建新的对象。但这样的改进有些偏离目标。于是，我将它作为习题留给读者。

​		String的拷贝构造函数很高效：新生成的String对象与被拷贝的对象共享相同的StringValue对象：

```C++
String::String(const String& rhs): value(rhs.value)
{
  ++value->refCount;
}
```

这样的代码：

```C++
String s1("More Effective C++");

String s2 = s1;
```

产生这样的数据结构：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\2019111417004483-168517039708711.png)

 

​		这肯定比通常的（不带引用计数的）string类高效，因为不需要为新生成的string值分配内存、释放内存以及将内容拷贝入这块内存。现在，我们只不过是拷贝了一个指针并增加了一次引用计数。

​		String类的析构函数同样容易实现，因为大部分情况下它不需要做任何事情。只要引用计数值不是0，也就是至少有一个String对象使用这个值，这个值就不可以被销毁。只有当唯一的使用者被析构了（也就是引用计数在进入函数前已经为1时），String的析构函数才摧毁StringValue对象：

```C++
class String {
	public:
  		~String();
  		...
};

String::~String()
{
  	if (--value->refCount == 0)
 	{
     	 delete value;
  	}
}
```

​		和没有引用计数的版本比较一下效率。那样的函数总调用delete，当然会有一个相当程度的运行时间的代价。现在提供的String对象们实际上有时具有相同的值，上面的这个实现在此时只需要做一下减少引用计数并与0进行比较。

​		如果在这个问题上引用计数没有向外界表现出来，你就根本不需要花注意力。

​		这就是String的构造和析构，我们现在转到赋值操作：

```C++
class String {
	public:

 	 	String& operator=(const String& rhs);

  		...

};
```

​		当用户写下这样的代码：

```C++
s1 = s2;                              // s1 and s2 are both String objects
```

​		其结果应该是s1和s2指向相同的StringValue对象。对象的引用计数应该在赋值时被增加。并且，s1原来指向的StringValue对象的引用计数应该减少，因为s1不再具有这个值了。如果s1是拥有原来的值的唯一对象，这个值应该被销毁。在C++中，其实现看起来是这样的：

```C++
String& String::operator=(const String& rhs)
{
  	if (value == rhs.value) 
    {         				// do nothing if the values
   	 	return *this;                    			// are already the same; this
	}                                  			   // subsumes the usual test of
												// this against &rhs (see Item E17)

  	if (--value->refCount == 0) 
    {      // destroy *this's value if
    	delete value;                    // no one else is using it
	}

  	value = rhs.value;                 // have *this share rhs's

  	++value->refCount;                 // value

  	return *this;
}
```

  

​		围绕我们的带引用计数的String类，考虑一下数组下标操作（[]），它允许字符串中的单个字符被读或写：

```C++
class String {
	public:

  		const char&

   	 	operator[](int index) const;       // for const Strings

  		char& operator[](int index);           // for non-const Strings

		...

};
```

​		这个函数的const版本的实现很容易，因为它是一个只读操作，String对象的值不受影响：

```C++
const char& String::operator[](int index) const
{
  return value->data[index];
}
```

​	（这个函数实现了C++传统意义上的下标索引（根本不会说“不”）。如果你想加上参数检查，这是非常容易的。）

非const的operator[]版本就是一个完全不同的故事了。它可能是被调用了来读一个字符，也可能被调用了来写一个字符：

```C++
String s;

...

cout << s[3];                        // this is a read

s[5] = 'x';                          // this is a write
```

​		我们希望以不同的方式处理读和写。简单的读操作，可以用与const的operator[]类似的方式实现，而写操作必须用完全不同的方式来实现。

​		当我们修改一个String对象的值时，必须小心防止修改了与它共享相同StringValue对象的其它String对象的值。不幸的是，C++编译器没有办法告诉我们一个特定的operator[]是用作读的还是写的，所以我们必须保守地假设“所有”调用非const operator[]的行为都是为了写操作。（Proxy类可以帮助我们区分读还是写，见Item M30。）

​		为了安全地实现非const的operator[]，我们必须确保没有其它String对象在共享这个可能被修改的StringValue对象。简而言之，当我们返回StringValue对象中的一个字符的引用时，必须确保这个StringValue的引用计数是1。这儿是我们的实现：

```C++
char& String::operator[](int index)

{
  // if we're sharing a value with other String objects,

  // break off a separate copy of the value for ourselves

  if (value->refCount > 1) {
    --value->refCount;                    // decrement current value'srefCount, because we won't be using that value any more
    value =                               // make a copy of the
      new StringValue(value->data);       // value for ourselves
  }
  // return a reference to a character inside our
  // unshared StringValue object
  return value->data[index];
}
```

​		这个“与其它对象共享一个值直到写操作时才拥有自己的拷贝”的想法在计算机科学中已经有了悠久而著名的历史了，尤其是在操作系统中：进程共享内存页直到它们想在自己的页拷贝中修改数据为止。这个技巧如此常用，以至于有一个名字：写时拷贝。它是提高效率的一个更通用方法－－缓式评估原则－－的特例。

​		大部分情况下，写时拷贝可以同时保证效率和正确性。只有一个挥之不去的问题。看一下这样的代码：

```C++
String s1 = "Hello";

char *p = &s1[1];
```

数据结构是这样的：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\20191114170147593.png)

 

​		现在看增加一条语句：

```C++
String s2 = s1;
```

​		String的拷贝构造函数使得s2共享s1的StringValue对象，所以数据结构将是：

 ![img](C:\Users\陈冠豪\Desktop\NowReading\Finish reading as well as noting\More Effective C++\More effective C++2\20191114170246431.png)

 

​		下面这样的语句将有不受欢迎的结果：

```C++
*p = 'x';                     // modifies both s1 and s2!
```

​		String的拷贝构造函数没有办法检测这样的问题，因为它不知道指向s1拥有的StringValue对象的指针的存在。并且，这个问题不局限于指针：它同样存在于有人保存了一个String的非const operator[]的返回值的引用的情况下。

​		至少有三种方法来应付这个问题。第一个是忽略它，假装它不存在。这是实现带引用计数的String类的类库中令人痛苦的常见问题。如果你有带引用计数的String类，试一下上面的例子，看你是否很痛苦。即使你不能确定你操作的是否是带引用计数的String类，也无论如何应该试一下这个例子。由于封装，你可能使用了一个这样的类型而不自知。

​		不是所以的实现都忽略这个问题。稍微好些的方法是明确说明它的存在。通常是将它写入文档，或多或少地说明“别这么做。如果你这么做了，结果为未定义。”无论你以哪种方式这么做了（有意地或无意地），并抱怨其结果时，他们辩解道：“好了，我们告诉过你别这么做的。”这样的实现通常很方便，但它们在可用性方面留下了太多的期望。

​		第三个方法是排除这个问题。它不难实现，但它将降低一个值共享于对象间的次数。它的本质是这样的：在每个StringValue对象中增加一个标志以指出它是否为可共享的。在最初（对象可共享时）将标志打开，在非const的operator[]被调用时将它关闭。一旦标志被设为false，它将永远保持在这个状态（注10）。

​		这是增加了共享标志的修改版本：

```C++
class String {
private:
  struct StringValue {
    	int refCount;

    	bool shareable;                // add this
    
    	char *data;
    
    	StringValue(const char *initValue);
    
   		~StringValue();
  };
	...
};
String::StringValue::StringValue(const char *initValue)
:refCount(1),shareable(true)                // add this
{
  data = new char[strlen(initValue) + 1];
  strcpy(data, initValue);
}

String::StringValue::~StringValue()
{
  delete [] data;
}
```

​		如你所见，并不需要太多的改变；需要修改的两行都有注释。当然，String的成员函数也必须被修改以处理这个共享标志。这里是拷贝构造函数的实现：

```C++
String::String(const String& rhs)

{
  if (rhs.value->shareable) {
    value = rhs.value;
    ++value->refCount;
  }
  else {
    value = new StringValue(rhs.value->data);
  }
}
```

​		所有其它的成员函数也都必须以类似的方法检查这个共享标志。非const的operator[]版本是唯一将共享标志设为false的地方：

```C++
char& String::operator[](int index)
{
  	if (value->refCount > 1) {
    	--value->refCount;
		value = new StringValue(value->data);
  }
  value->shareable = false;           // add this
  return value->data[index];
}
```

​		如果使用Item M30中的proxy类的技巧以区分读写操作，你通常可以降低必须被设为不可共享的StringValue对象的数目。

​		引用计数不只用在字符串类上，只要是多个对象具有相同值的类都可以使用引用计数。改写一个类以获得引用计数需要大量的工作，而我们已经有太的工作需要做了。这样不好吗：如果我们将引用计数的代码写成与运行环境无关的，并能在需要时将它嫁接到其它类上？当然很好。很幸运，有一个方法可以实现它（至少完成了绝大部分必须的工作）。

​		第一步是构建一个基类RCObject，任何需要引用计数的类都必须从它继承。RCObject封装了引用计数功能，如增加和减少引用计数的函数。它还包含了当这个值不再被需要时摧毁值对象的代码（也就是引用计数为0时）。最后，它包含了一个字段以跟踪这个值对象是否可共享，并提供查询这个值和将它设为false的函数。不需将可共享标志设为true的函数，因为所有的值对象默认都是可共享的。如上面说过的，一旦一个对象变成了不可共享，将没有办法使它再次成为可共享。

​		RCObject的定义如下：

```C++
class RCObject {
public:

  	RCObject();

  	RCObject(const RCObject& rhs);

  	RCObject& operator=(const RCObject& rhs);

 	virtual ~RCObject() = 0;

  	void addReference();

  	void removeReference();

	void markUnshareable();

	bool isShareable() const;

	bool isShared() const;

private:

	int refCount;

	bool shareable;

};
```

​		RCObjcet可以被构造（作为派生类的基类部分）和析构；可以有新的引用加在上面以及移除当前引用；其可共享性可以被查询以及被禁止；它们可以报告当前是否被共享了。这就是它所提供的功能。对于想有引用计数的类，这确实就是我们所期望它们完成的东西。注意虚析构函数，它明确表明这个类是被设计了作基类使用的（见Item E14）。同时要注意这个析构函数是纯虚的，它明确表明这个类只能作基类使用。

​		RCOject的实现代码：

```C++
RCObject::RCObject(): refCount(0), shareable(true) {}
RCObject::RCObject(const RCObject&): refCount(0), shareable(true) {}
RCObject& RCObject::operator=(const RCObject&)
{ 
    return *this; 
}
RCObject::~RCObject() {}               // virtual dtors must always

                                       // be implemented, even if
    
                                       // they are pure virtual
    
                                       // and do nothing (see also
    
                                       // Item M33 and Item E14)

void RCObject::addReference() 
{
    ++refCount; 
}
void RCObject::removeReference()

{   
    if (--refCount == 0)
        delete this; 
}

void RCObject::markUnshareable()
{ 
    shareable = false; 
}
bool RCObject::isShareable() const
{ 
    return shareable; 
}
bool RCObject::isShared() const
{ 
    return refCount > 1; 
}
```

​		可能很奇怪，我们在所有的构造函数中都将refCount设为了0。这看起来违反直觉。确实，最少，构造这个RCObject对象的对象引用它！在它构造后，只需构造它的对象简单地将refCount设为1就可以了，所以我们没有将这个工作放入RCObject内部。这使得最终的代码看起来很简短。

​		另一个奇怪之处是拷贝构造函数也将refCount设为0，而不管被拷贝的RCObject对象的refCount的值。这是因为我们正在构造新的值对象，而这个新的值对象总是未被共享的，只被它的构造者引用。再一次，构造者负责将refCount设为正确的值。

​		RCObject的赋值运算看起来完全出乎意料：它没有做任何事情。这个函数不太可能被调用的。RCObject是基于引用计数来共享的值对象的基类，它不该被从一个赋给另外一个，而应该是拥有这个值的对象被从一个赋给另外一个。在我们这个设计里，我们不期望StringValue对象被从一个赋给另外一个，我们期望在赋值过程中只有String对象被涉及。在String参与的赋值语句中，StringValue的值没有发生变化，只是它的引用计数被修改了。

​		不过，可以想象，一些还没有写出来的类在将来某天可能从RCObject派生出来，并希望允许被引用计数的值被赋值（见Item M23和Item E16）。如果这样的话，RCObject的赋值操作应该做正确的事情，而这个正确的事情就是什么都不做。想清楚了吗？假设我们希望允许在StringValue对象间赋值。对于给定的StringValue对象sv1和sv2，在赋值过程中，它们的引用计数值上发生什么？

```C++
sv1 = sv2;                    // how are sv1's and sv2's reference counts affected?
```

​		在赋值之前，已经有一定数目的String对象指向sv1。这个值在赋值过程中没有被改变，因为只是sv1的值被改变了。同样的，一定数目的String对象在赋值之前指向前v2，在赋值后，同样数目的对象指向sv2。sv2的引用计数同样没有改变。当RCObject在赋值过程中被涉及时，指向它的对象的数目没有受影响，因此RCObject::operator=不应该改变引用计数值。上面的实现是正确的。违反直觉？可能吧，但它是正确的。

​		RCObject::removeReference的代码不但负责减少对象的refCount值，还负责当refCount值降到0时析构对象。后者是通过delete this来实现的，如Item M27中解释的，这只当我们知道*this是一个堆对象时才安全。要让这个类正确，我们必须确保RCObject只能被构建在堆中。实现这一点的常用方法见Item M27，但我们这次采用一个特别的方法，这将在本条款最后讨论。

​		为了使用我们新写的引用计数基类，我们将StringValue修改为是从RCObject继承而得到引用计数功能的：

```C++
class String {
private:

  	struct StringValue: public RCObject {
    	char *data;

    	StringValue(const char *initValue);
    
   	 	~StringValue();
	};

...
};
String::StringValue::StringValue(const char *initValue)
{
  	data = new char[strlen(initValue) + 1];

 	strcpy(data, initValue);
}
String::StringValue::~StringValue()
{
  delete [] data;
}
```

​		这个版本的StringValue和前面的几乎一样，唯一改变的就是StringValue的成员函数不再处理refCount字段。RCObject现在接管了这个工作。

​		不用感觉不舒服，如果你注意到嵌套类（StringValue）从一个与包容类（String）无关的类（RCObject）继承而来的话。它第一眼看上去是有些古怪，但完全合理。嵌套类和其它类是完全相同的，所以它有自由从它喜欢的任何其它类继承。以后，你不用第二次思考这种继承关系了。   

​		RCObject类给了我们一个存储引用计数的地方，并提供了成员函数供我们操作引用计数，但调用这些函数的动作还必须被手工加入其它类中。仍然需要在String的拷贝构造函数和赋值运算函数中调用StringValue的addReference和 removeReference函数。这很笨拙。我们想将这些调用也移入一个可重用的类中，以使得String这样的类的作者不用再担心引用计数的任何细节。能实现吗？C++支持这样的重用吗？

​		能。没有一个简单的方法将所有引用计数方面的工作从所有的类中移出来；但有一个方法可以从大部分类中将大部分工作移出来。（在一些类中，你可以消除所有引用计数方面的代码，但我们的String类不是其中之一。有一个成员函数搞坏了这件事，我希望你别吃惊，它是我们的老对头：非const版本的operator[]。别放心上，我们最终制服了这家伙。）

​		每个String对象包含一个指针指向StringValue对象：

```C++
class String {
private:

  struct StringValue: public RCObject { ... };

  StringValue *value;                // value of this String

  ...

};
```

​		我们必须操作StringValue对象的refCount字段，只要任何时候任一个指向它的指针身上发生了任何有趣的事件。“有趣的事件”包括拷贝指针、给指针赋值和销毁指针。如果我们能够让指针自己检测这些事件并自动地执行对refCount字段的必须操作，那么我们就自由了。不幸的是，指针功能很弱，对任何事情作检测并作出反应都是不可能的。还好，有一个办法来增强它们：用行为类似指针的对象替代它们，但那样要多做很多工作了。

​		这样的对象叫灵巧指针，你可以在Item M28这看到它的更多细节。就我们这儿的用途，只要知道这些就足够了：灵巧指针对象支持成员选择（->）和反引用（*）这两个操作符，就象真的指针一样，并和内建指针一样是强类型的：你不能将一个指向T的灵巧指针指向一个非T类型的对象。

​		这儿是供引用计数对象使用的灵巧指针模板：

```C++
// template class for smart pointers-to-T objects. T must

// support the RCObject interface, typically by inheriting

// from RCObject

template<class T>

class RCPtr {
public:

  RCPtr(T* realPtr = 0);

  RCPtr(const RCPtr& rhs);

  ~RCPtr();

  RCPtr& operator=(const RCPtr& rhs);

  T* operator->() const;            // see Item 28

  T& operator*() const;             // see Item 28

private:

  T *pointee;                       // dumb pointer this

                                    // object is emulating

  void init();                      // common initialization

}; 
```

​		这个模板让灵巧指针对象控制在构造、赋值、析构时作什么操作。当这些事件发生时，这些对象可以自动地执行正确的操作来处理它们指向的对象的refCount字段。

​		例如，当一个RCPtr构建时，它指向的对象需要增加引用计数值。现在不需要程序员手工处理这些细节了，因为RCPtr的构造函数自己处理它。两个构造函数几乎相同，除了初始化列表上的不同，为了不写两遍，我们将它放入一个名为init的私有成员函数中供二者调用：

```C++
template<class T>
RCPtr<T>::RCPtr(T* realPtr): pointee(realPtr)
{
  init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs): pointee(rhs.pointee)
{
  init();
}

template<class T>
void RCPtr<T>::init()
{
  	if (pointee == 0) {                // if the dumb pointer is
    	return;                          // null, so is the smart one
  	}
	if (pointee->isShareable() == false) {           // if the value

    	pointee = new T(*pointee);                   // isn't shareable,

  	}                                              // copy it
	pointee->addReference();             // note that there is now a
}                                    // new reference to the value
```

​		将相同的代码移入诸如init这样的一个独立函数是很值得效仿的，但它现在暗淡无光，因为在此处，这个函数的行为不正确。

​		问题是这个：当init需要创建value的一个新拷贝时（因为已存在的拷贝处于不可共享状态），它执行下面的代码：

```C++
pointee = new T(*pointee);
```

​		pointee的类型是指向T的指针,所以这一语句构建了一个新的T对象，并用拷贝构造函数进行了初始化。由于RCPtr是在String类内部，T将是String::StringValue，所以上面的语句将调用String::StringValue的拷贝构造函数。我们没有为这个类申明拷贝构造函数，所以编译器将为我们生成一个。这个生成的拷贝构造函数遵守C++的自动生成拷贝构造函数的原则，只拷贝了StringValue的数据pointer，而没有拷贝所指向的char *字符串。这样的行为对几乎任何类（而不光是引用计数类）都是灾难，这就是为什么你应该养成为所有含有指针的类提供拷贝构造函数（和赋值运算）的习惯（见Item E11）。

​		RCPtr<T>模板的正确行为取决于T含有正确的值拷贝行为（如深拷贝）的拷贝构造函数。我们必须在StringValue中增加这样的一个构造函数：

```C++
class String {
private:
  struct StringValue: public RCObject {
    StringValue(const StringValue& rhs);
    ...
  };
  ...
};
String::StringValue::StringValue(const StringValue& rhs)
{
  	data = new char[strlen(rhs.data) + 1];
  	strcpy(data, rhs.data);
}
```

​		深拷贝的构造函数的存在不是RCPtr<T>的唯一假设。它还要求T从RCObject继承，或至少提供了RCObject的所提供的函数。事实上由于RCPtr对象只是被设计了指向引用计数对象的，这个假设并不过分。不过，这个假设必须被明确写入文档。

​		RCPtr<T>的最后一个假设是它所指向的对象类型为T。这似乎是显然的。毕竟，pointee的类型被申明为T*。但pointee可能实际上指向T的一个派生类。例如，如果我们有一个类SpecialStringValue是从String::StringValue继承的：

```C++
class String {
private:

  struct StringValue: public RCObject { ... };

  struct SpecialStringValue: public StringValue { ... };

  ...

};
```

我们可以生成一个String，包容的RCPtr<StringValue>指向一个SpecialStringValue对象。这时，我们希望init的这句：

```C++
pointee = new T(*pointee);                // T is StringValue, but pointee really points to a SpecialStringValue
```

​		调用的是SpecialStringValue的拷贝构造函数，而不是StringValue的拷贝构造函数。我们可以提供使用虚拷贝构造函数（见Item M25）来实现这一点。对于我们的String类，我们不期望从StringValue派生子类，所以我们忽略这个问题。

​		用这种方式实现了RCPtr的构造函数后，类的其它函数实现得很轻快。赋值运算很简洁明了，虽然“需要测试源对象的可共享状态”将问题稍微复杂化了。幸好，同样的问题已经在我们为构造函数写的init函数中处理了。我们可以爽快地再度使用它：

```C++
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
  	if (pointee != rhs.pointee)
    {          
    	// skip assignments， where the 		value doesn't change
		if (pointee) 
		{
  			pointee->removeReference();        // remove reference to
		}                                    // current value

		pointee = rhs.pointee;               // point to new value

		init();                              // if possible, share it
  	}                                      // else make own copy

  	return *this;
}
```

析构函数很容易。当一个RCPtr被析构时，它只是简单地将它对引用计数对象的引用移除：

```C++
template<class T>
RCPtr<T>::~RCPtr()
{
  	if (pointee)pointee->removeReference();
}
```

​		如果这个RCPtr是最后一个引用它的对象，这个对象将在RCObject的成员函数removeReference中被析构。因此，RCPtr对象无需关心销毁它们指向的值的问题。

​		最后，RCPtr的模拟指针的操作就是你在Item M28中看到的灵巧指针的部分：

```C++
template<class T>

T* RCPtr<T>::operator->() const { return pointee; }

template<class T>

T& RCPtr<T>::operator*() const { return *pointee; }
```

​		够了！完结！最后，我们将各个部分放在一起，构造一个基于可重用的RCObject和RCPtr类的带引用计数的String类。或许，你还没有忘记这是我们的最初目标。

​		每个带引用计数的Sting对象被实现为这样的数据结构：

类的定义是：

```C++
template<class T>                       // template class for smart
class RCPtr {                           // pointers-to-T objects; T

public:                                 // must inherit from RCObject

  RCPtr(T* realPtr = 0);

  RCPtr(const RCPtr& rhs);

  ~RCPtr();

  RCPtr& operator=(const RCPtr& rhs);

  T* operator->() const;

  T& operator*() const;

private:

  T *pointee;

  void init();

};

class RCObject {                       // base class for reference-

public:                                // counted objects

  void addReference();

  void removeReference();

  void markUnshareable();

  bool isShareable() const;

  bool isShared() const;

protected:

  RCObject();

  RCObject(const RCObject& rhs);

  RCObject& operator=(const RCObject& rhs);

  virtual ~RCObject() = 0;

private:

  int refCount;

  bool shareable;

};

class String {                           // class to be used by

public:                                  // application developers

  String(const char *value = "");

  const char& operator[](int index) const;

  char& operator[](int index);

private:

  // class representing string values

  struct StringValue: public RCObject {
    char *data;

StringValue(const char *initValue);

StringValue(const StringValue& rhs);

void init(const char *initValue);

~StringValue();
  };

  RCPtr<StringValue> value;

};
```

​		绝大部分都是我们前面写的代码的翻新，没什么奇特之处。仔细检查后发现，我们在String::StringValue中增加了一个init函数，但，如我们下面将看到的，它的目的和RCPtr中的相同：消除构造函数中的重复代码。

​		这里有一个重大的不同：这个String类的公有接口和本条款开始处我们使用的版本不同。拷贝构造函数在哪里？赋值运算在哪里？析构函数在哪里？这儿明显有问题。

​		实际上，没问题。它工作得很好。如果你没看出为什么，需要重学C++了（prepare yourself for a C++ epiphany）。

​		我们不再需要那些函数了！确实，String对象的拷贝仍然被支持，并且，这个拷贝将正确处理藏在后面的被引用计数的StringValue对象，但String类不需要写下哪怕一行代码来让它发生。因为编译器为String自动生成的拷贝构造函数将自动调用其RCPtr成员的拷贝构造函数，而这个拷贝构造函数完成所有必须的对StringValue对象的操作，包括它的引用计数。RCPtr是一个灵巧指针，所以这是它将完成的工作。它同样处理赋值和析构，所以String类同样不需要写出这些函数。我们的最初目的是将不可重用的引用计数代码从我们自己写的String类中移到一个与运行环境无关的类中以供任何其它类使用。现在，我们完成了这一点（用RCObject和RCPtr两个类），所以当它突然开始工作时别惊奇。它本来就应该能工作的。

​		将所以东西放在一起，这儿是RCObject的实现：

```C++
RCObject::RCObject(): refCount(0), shareable(true) {
    
}
RCObject::RCObject(const RCObject&): refCount(0), shareable(true) {
    
}
RCObject& RCObject::operator=(const RCObject&)
{ 
    return *this; 
}
RCObject::~RCObject() {}
void RCObject::addReference() 
{ 
    ++refCount; 
}
void RCObject::removeReference()
{ 
    if (--refCount == 0) delete this; 
}
void RCObject::markUnshareable()
{ 
    shareable = false;
}

bool RCObject::isShareable() const
{ 
    return shareable; 
}

bool RCObject::isShared() const
{
    return refCount > 1;
}
```

这是RCPtr的实现：

```C++
template<class T>
void RCPtr<T>::init()
{
  if (pointee == 0) 
      return;
  if (pointee->isShareable() == false) 
  {
    	pointee = new T(*pointee);
  }
  pointee->addReference();
}

template<class T>
RCPtr<T>::RCPtr(T* realPtr): pointee(realPtr)
{ init(); }

template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs): pointee(rhs.pointee)
{ init(); }

template<class T>
RCPtr<T>::~RCPtr()
{ if (pointee)pointee->removeReference(); }

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
  	if (pointee != rhs.pointee) 
    {
    	if (pointee) 
        {
            pointee->removeReference();
        }
		pointee = rhs.pointee;

		init();
  	}
	return *this;
}

template<class T>
T* RCPtr<T>::operator->() const { return pointee; }

template<class T>
T& RCPtr<T>::operator*() const { return *pointee; }

```

​		这是String::StringValue的实现：

```C++
void String::StringValue::init(const char *initValue)
{
  data = new char[strlen(initValue) + 1];
  strcpy(data, initValue);
}
String::StringValue::StringValue(const char *initValue)
{ 
    init(initValue); 
}
String::StringValue::StringValue(const StringValue& rhs)
{ 
    init(rhs.data); 
}
String::StringValue::~StringValue()
{ 
    delete [] data; 
}
```

最后，归结到String，它的实现是：

```C++
String::String(const char *initValue): value(new StringValue(initValue)) {}
const char& String::operator[](int index) const
{ 
    return value->data[index]; 
}

char& String::operator[](int index)
{
  	if (value->isShared()) {
    	value = new StringValue(value->data);

  	}

 	value->markUnshareable();

  	return value->data[index];

}
```

​		如果你将它和我们用内建指针实现的版本相比较，你会受到两件事的打击。第一，代码有很多的减少。因为RCPtr完成了大量以前在String内部完成的处理引用计数的担子。第二，剩下的代码几乎没有变化：灵巧指针无缝替换了内建指针。实际上，唯一的变化是在operator[]里，我们用调用isShared函数代替了直接检查refCount的值，并用灵巧指针RCPtr对象消除了写时拷贝时手工维护引用计数值的工作。

​		这当然全都很漂亮。谁能反对减少代码？谁能反对成功的封装？然而，这个全新的String类本身对用户的冲击远胜过它的实现细节，这才是真正的闪光点。如果没有什么消息是好消息的话，这本身就是最好的消息。String的接口没有改变！我们增加了引用计数，我们增加了标记某个String的值为不可共享的能力，我们将引用计数功能移入一个新类，我们增加了灵巧指针来自动处理引用计数，但用户的一行代码都不需要修改。当然，我们改变了String类的定义，所以用户需要重新编译和链接，但他们在自己代码上的投资受到了完全的保护。你看到了吗？封装确实是个很好的东西。

​		到现在为止，我们所讨论的都假设我们能够访问有关类的源码。但如果我们想让一个位于支撑库中而无法修改的类获得引用计数的好处呢？不可能让它们从RCObject继承的，所以也不能对它们使用灵巧指针RCPtr。我们运气不好吗？

​		不是的。只要对我们的设计作小小的修改，我们就可以将引用计数加到任意类型上。

​		首先考虑如果从RCObject继承的话，我们的设计看起来将是什么样子。在这种情况下，我们需要增加一个类RCWidget以供用户使用，而所有的事情都和String/StringValue的例子一样，RCWidget和String相同，Widget和StringValue相同。设计看起来是这样的：

​		**我们现在可以应用这句格言：计算机科学中的绝大部分问题都可以通过增加一个中间层次来解决。**我们增加一个新类CountHolder以处理引用计数，它从RCObject继承。我们让CountHolder包含一个指针指向Widget。然后用等价的灵巧指针RCIPter模板替代RCPtr模板，它知道CountHolder类的存在。（名字中的“i”表示间接“indirect”。）修改后的设计为：

​		如同StringValue一样，CountHolder对用户而言，是RCWidget的实现细节。实际上，它是RCIPtr的实现细节，所以它嵌套在这个类中。RCIPtr的实现如下：

```C++
template<class T>

class RCIPtr {
public:

  RCIPtr(T* realPtr = 0);

  RCIPtr(const RCIPtr& rhs);

  ~RCIPtr();

  RCIPtr& operator=(const RCIPtr& rhs);

  const T* operator->() const;               // see below for an

  T* operator->();                           // explanation of why

  const T& operator*() const;                // these functions are

  T& operator*();                            // declared this way

private:

  struct CountHolder: public RCObject 
  {
    	~CountHolder() { 
       		delete pointee; 
    	}
    T *pointee;
  };
  CountHolder *counter;
  void init();
  void makeCopy();                                // see below

};

template<class T>
void RCIPtr<T>::init()
{
  	if (counter->isShareable() == false)
  	{
    	T *oldValue = counter->pointee;	
		counter = new CountHolder;

		counter->pointee = new T(*oldValue);
 	}

  	counter->addReference();
}
template<class T>
RCIPtr<T>::RCIPtr(T* realPtr): counter(new CountHolder)
{
  counter->pointee = realPtr;
  init();
}
template<class T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs): counter(rhs.counter)
{ 
    init();
}
template<class T>
RCIPtr<T>::~RCIPtr()
{ 
    counter->removeReference(); 
}

template<class T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs)
{
  	if (counter != rhs.counter) 
    {
   		 counter->removeReference();
   	 	 counter = rhs.counter;

		 init();
  	}

  	return *this;

}
template<class T>                          // implement the copy
void RCIPtr<T>::makeCopy()                 // part of copy-on-
{                                          // write (COW)

  	if (counter->isShared()) 
  	{
    	T *oldValue = counter->pointee;
		counter->removeReference();
	
		counter = new CountHolder;

		counter->pointee = new T(*oldValue);

		counter->addReference();  
  }
    

}
template<class T>                           // const access;
const T* RCIPtr<T>::operator->() const      // no COW needed
{
    return counter->pointee; 
}

template<class T>                           // non-const
T* RCIPtr<T>::operator->()                  // access; COW
{ 
    makeCopy(); 
    return counter->pointee; 
}    // needed

template<class T>                           // const access;
const T& RCIPtr<T>::operator*() const       // no COW needed
{ 
    return *(counter->pointee);
}

template<class T>                           // non-const
T& RCIPtr<T>::operator*()                   // access; do the
{
    makeCopy(); 
    return *(counter->pointee); 
} // COW thing
```

​		RCIPtr与RCPtr只两处不同。第一，RCPtr对象直接指向值对象，而RCIptr对象通过中间层的CountHolder对象指向值对象。第二，RCIPtr重载了operator->和operator*，当有对被指向的对象的非const的操作时，写时拷贝自动被执行。

​		有了RCIPtr，很容易实现RCWidget，因为RCWidget的每个函数都是将调用传递给RCIPtr以操作Widget对象。举个例子，如果Widget是这样的：

```C++
class Widget {
public:

  Widget(int size);

  Widget(const Widget& rhs);

  ~Widget();

  Widget& operator=(const Widget& rhs);

  void doThis();

  int showThat() const;

};
```

​		那么RCWidget将被定义为这样：

```C++
class RCWidget {
public:

  RCWidget(int size): value(new Widget(size)) {}

  void doThis() { value->doThis(); }

  int showThat() const { return value->showThat(); }

private:

  RCIPtr<Widget> value;

};
```

​		注意RCWidget的构造函数是怎么用它被传入的参数调用Widget的构造函数的（通过new操作符，见Item M8）；RCWidget的doThis怎么调用Widget的doThis函数的；以及RCWidget的showThat怎么返回Widget的showThat的返回值的。同样要注意RCWidget没有申明拷贝构造函数和赋值操作函数，也没有析构函数。如同String类一样，它不需要这些函数。感谢于RCIPtr的行为，RCWidget的默认版本将完成正确的事情。

​		如果认为生成RCWidget的行为很机械，它应该自动进行，那么你是对的。不难写个小程序接受如Widget这样的类而输出RCWidget这样的类。如果你写了一个这样的程序，请让我知道。



​		让我们从Widget、String、值、灵巧指针和引用计数基类中摆脱一下。给个机会回顾一下，在更广阔的环境下看一下引用计数。在更大的环境下，我们必须处理一个更高层次的问题，也就是什么时候使用引用计数？

​		实现引用计数不是没有代价的。每个被引用的值带一个引用计数，其大部分操作都需要以某种形式检查或操作引用计数。对象的值需要更多的内存，而我们在处理它们时需要执行更多的代码。此外，就内部的源代码而言，带引用计数的类的复杂度比不带的版本高。没有引用计数的String类只依赖于自己，而我们最终的String类如果没有三个辅助类（StringValue、RCObject和RCPtr）就无法使用。确实，我们这个更复杂的设计确保在值可共享时的更高的效率；免除了跟踪对象所有权的需要，提高了引用计数的想法和实现的可重用性。但，这四个类必须写出来、被测试、文档化、和被维护，比单个类要多做更多的工作。即使是管理人员也能看出这点。

​		引用计数是基于对象通常共享相同的值的假设的优化技巧（参见Item M18）。如果假设不成立的话，引用计数将比通常的方法使用更多的内存和执行更多的代码。另一方面，如果你的对象确实有具体相同值的趋势，那么引用计数将同时节省时间和空间。共享的值所占内存越大，同时共享的对象数目越多，节省的内存也就越大。创建和销毁这个值的代价越大，你节省的时间也越多。总之，引用计数在下列情况下对提高效率很有用：

​		少量的值被大量的对象共享。这样的共享通常通过调用赋值操作和拷贝构造而发生。对象/值的比例越高，越是适宜使用引用计数。

​		对象的值的创建和销毁代价很高昂，或它们占用大量的内存。即使这样，如果不是多个对象共享相同的值，引用计数仍然帮不了你任何东西。

​		只有一个方法来确认这些条件是否满足，而这个方法不是猜测或依赖直觉（见Item M16）。这个方法是使用profiler或其它工具来分析。使用这种方法，你可以发现是否创建和销毁值的行为是性能瓶颈，并能得出对象/值的比例。只有当你手里有了这些数据，你才能得出是否从引用计数上得到的好处超过其缺点。

​		即使上面的条件满足了，使用引用计数仍然可能是不合适的。有些数据结构（如有向图）将导致自我引用或环状结构。这样的数据结构可能导致孤立的自引用对象，它没有被别人使用，而其引用计数又绝不会降到零。因为这个无用的结构中的每个对象被同结构中的至少一个对象所引用。商用化的垃圾收集体系使用特别的技术来查找这样的结构并消除它们，但我们现在使用的这个简单的引用计数技术不是那么容易扩充出这个功能的。

​		即使效率不是主要问题，引用计数仍然很吸引人。如果你不放心谁应该去执行删除动作，那么引用计数正是这种让你放下担子的技巧。很多程序员只因为这个原因就使用引用计数。

​		让我们用最后一个问题结束讨论。当RCObject::removeReference减少对象的引用计数时，它检查新值是否为0。如果是，removeReference通过调用delete this销毁对象。这个操作只在对象是通过调用new生成时才安全，所以我们需要一些方法以确保RCObject只能用这种方法产生。

​		此处，我们用习惯方法来解决。RCObject被设计为只作被引用计数的值对象的基类使用，而这些值对象应该只通过灵巧指针RCPtr引用。此外，值对象应该只能由值会共享的对象来实例化；它们不能被按通常的方法使用。在我们的例子中，值对象的类是StringValue，我们通过将它申明为String的私有而限制其使用。只有String可以创建StringValue对象，所以String类的作者应该确保这些值对象都是通过new操作产成的。

​		于是，我们限制RCObject只能在堆上创建的方法就是指定一组满足这个要求的类，并确保只有这些类能创建RCObject对象。用户不可能无意地（或有意地）用一种不恰当的方法创建RCObject对象。我们限制了创建被引用计数对象的权力，当我们交出这个权力时，必须明确其附带条件是满足创建对象的限制条件。

