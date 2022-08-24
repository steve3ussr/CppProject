# C++ TODO

- enum
- 

# C++ Hello World

``` c++
#include <iostream>
// using namespace std;
int main()
{
    printf("Hello, World!\n");
    std::cout << "hello std::" << std::endl;
    return 0;
}
```

> - endl和'\n'差不多，但是endl会flush
>
> - <>先去系统目录中找头文件，如果没有在到当前目录下找。所以像标准的头文件 stdio.h、stdlib.h 等用这个方法。
>
> - **" "** 首先在当前目录下寻找，如果找不到，再到系统目录中寻找。 这个用于 include 自定义的头文件，让系统优先使用当前目录中定义的。
>
> - 真正的开发过程中， 尽量避免使用 **using namespace std;** 等直接引入整个命名空间，否则会因为命名空间污染导致很多不必要的问题， 比如自己写的某个函数，名称正好和 **std** 中的一样， 编译器会不知道使用哪一个， 引起编译报错， 建议使用: `std::cout`
>
> - **.C++** 文件和 **.h** 文件的区别：
>
>   C++文件用于存放类的定义 definition，h 文件用于存放类的声明 declaration。
>
>   在头文件中声明了一个函数或者类，需要定义或者使用这个函数或者类时，需要在 C++ 文件中 include 这个头文件

# L-value, R-value

> 从汇编代码上看，左值引用和右值引用本质都是指向值的地址，那为什么c++里要对2者做出区分? - 高性能架构探索的回答 - 知乎 https://www.zhihu.com/question/360636808/answer/2353439219
>
> https://nettee.github.io/posts/2018/Understanding-lvalues-and-rvalues-in-C-and-C/

C遵循传统的CPL划分方式：左值被定义为标识一个对象的表达式，其他的都是右值（函数和非对象值）。

C++11开始，有了更加细分的分类：

![](https://pic1.zhimg.com/v2-60953ef4f577788e2f96dbcbb960d3a4_r.jpg)

## L-value

左值是表达式（不一定是赋值表达式）后依然存在的持久对象；可以将左值看作是一个关联了名称的内存位置，允许程序的其他部分来访问它。

左值具有以下特征：

- 可通过取地址运算符获取其地址
- 可修改的左值可用作内建赋值和内建符合赋值运算符的左操作数
- 可以用来初始化左值引用(后面有讲)

那么哪些都是左值呢?查了相关资料，做了些汇总，基本覆盖了所有的类型：

- 变量名、函数名以及数据成员名
- 返回左值引用的函数调用
- 由赋值运算符或复合赋值运算符连接的表达式，如(a=b, a-=b等)
- 解引用表达式`*ptr`
- 前置自增和自减表达式(++a, ++b)
- 成员访问（点）运算符的结果
- 由指针访问成员（ -> ）运算符的结果
- 下标运算符的结果([])
- 字符串字面值(`"abc"`)

## Pure Right Value

字面值或者函数返回的非引用都是纯右值。

以下表达式的值都是纯右值：

- 字面值(字符串字面值除外)，例如1，'a', true等
- 返回值为非引用的函数调用或操作符重载，例如：str.substr(1, 2), str1 + str2, or it++
- 后置自增和自减表达式(a++, a--)
- 算术表达式
- 逻辑表达式
- 比较表达式
- 取地址表达式
- lambda表达式

纯右值特征：

- 等同于C++11之前的右值
- 不会是多态
- 不会是抽象类型或数组
- 不会是不完全类型

## eXpiring Value

将亡值，顾名思义即将消亡的值，是C++11新增的跟右值引用相关的表达式，这样表达式通常是将要被移动的对象（移为他用），比如返回右值引用T&&的函数返回值、std::move的返回值，或者转换为T&&的类型转换函数的返回值。

**可以通过右值引用延长生命周期，比如避免在函数返回时销毁。**

xvalue 只能通过两种方式来获得，这两种方式都涉及到将一个左值赋给(转化为)一个右值引用：

- 返回右值引用的函数的调用表达式,如 static_cast<T&&>(t); 该表达式得到一个 xvalue
- 转换为右值引用的转换函数的调用表达式，如：std::move(t)、satic_cast<T&&>(t)

在C++11之前，s = fun();会调用拷贝构造函数，会将整个str复制一份，然后把str销毁。如果str特别大的话，会造成大量额外开销。在这一行中，s是左值，fun()是右值(纯右值)，fun()产生的那个返回值作为一个临时值，一旦str被s复制后，将被销毁，无法获取、也不能修改。

**自C++11开始，引入了move语义，编译器会将这部分优化成move操作**，即不再是之前的复制操作，而是move。此时，str会被进行隐式右值转换，等价于static_cast<std::string&&>(str)，进而此处的 s 会将 foo 局部返回的值进行移动。

>  无论是C++11之前的拷贝，还是C++11的move，str在填充(拷贝或者move)给s之后，将被销毁，而被销毁的这个值，就成为将亡值。  

将[亡值](https://www.zhihu.com/search?q=亡值&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra={"sourceType"%3A"answer"%2C"sourceId"%3A"2353439219"})就定义了这样一种行为：具名的临时值、同时又能够被move。











# C++ 数据类型, typedef, enum

> `sizeof(type), numeric_limits<type>::max/min`可获取下面的值

| 类型               | 位            | 范围                                                         |
| :----------------- | :------------ | :----------------------------------------------------------- |
| char               | 1 个字节      | -128 到 127 或者 0 到 255                                    |
| unsigned char      | 1 个字节      | 0 到 255                                                     |
| signed char        | 1 个字节      | -128 到 127                                                  |
| int                | 4 个字节      | -2147483648 到 2147483647                                    |
| unsigned int       | 4 个字节      | 0 到 4294967295                                              |
| signed int         | 4 个字节      | -2147483648 到 2147483647                                    |
| short int          | 2 个字节      | -32768 到 32767                                              |
| unsigned short int | 2 个字节      | 0 到 65,535                                                  |
| signed short int   | 2 个字节      | -32768 到 32767                                              |
| long int           | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| signed long int    | 8 个字节      | -9,223,372,036,854,775,808 到 9,223,372,036,854,775,807      |
| unsigned long int  | 8 个字节      | 0 到 18,446,744,073,709,551,615                              |
| float              | 4 个字节      | 精度型占4个字节（32位）内存空间，+/- 3.4e +/- 38 (~7 个数字) |
| double             | 8 个字节      | 双精度型占8 个字节（64位）内存空间，+/- 1.7e +/- 308 (~15 个数字) |
| long double        | 16 个字节     | 长双精度型 16 个字节（128位）内存空间，可提供18-19位有效数字。 |
| wchar_t            | 2 或 4 个字节 | 1 个宽字符                                                   |

---

可以自定义类型的别名，如`typedef int zsa; zsa a = 1;`

> 关键字 typedef 在编译阶段有效，由于是在编译阶段，因此 typedef 有类型检查的功能，有自己的作用域。
>
> \#define 则是宏定义，发生在预处理阶段，也就是编译之前，它只进行简单而机械的字符串替换，而不进行任何检查。没有自己的作用域





# C++ 常量

字符串分行：

``` c++
string a = "htrg \
           awd";
```

> C++的字符串：std::string
>
> C的字符串：char *a = "e2131e"

# C++ 函数，lambda

## Call Method

- 传值；
- 指针调用：传入地址给形参；`void func(int *a, int *b)`
- **引用调用**：`void func(int &a, int &b)`

``` c++
# include <stdio.h>

void swapVal(int a, int b) {
    int tmp = a;
    a = b;
    b = a;
    return;
}

void swapPnt(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void swapRef(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
    return;
}

int main() {
    int x = 114; 
    int y = 514;

    swapVal(x, y);
    printf("x = %d, y = %d\n", x, y);

    swapPnt(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    swapRef(x, y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
```

## LAMBDA

创建一个函数对象。

示例：`auto funcName = [](intsa, int b){return a+b;};`

完整表达式的组成：

``` c++
[ capture-list ] ( params ) mutable(optional) exception(optional) attribute(optional) -> return(optional) { body } 
```

- params：和普通函数一样；
- mutable：**默认按值捕获的类型是 const 的， 要修改需要加这个关键字**
- exception
- attribute
- return：可省略，会自动推导
- body：具体逻辑
- 捕获列表：在Lambda表达式内可以访问当前作用域的变量
  - `[]`什么都不捕获
  - `[a]`传值
  - `[&b]`引用
  - `[&]`按值捕获可见范围内的所有局部变量（不建议）
  - `[=]`按引用捕获可见范围内的所有局部变量（不建议）
- 在成员函数中的 Lambda 表达式可以捕获当前对象的 this 指针，让 Lambda 表达式拥有和当前类成员同样的访问权限，可以修改类的成员变量，使用类的成员函数：this 指针只能按值捕获 `[this]` ，不能按引用捕获 `[&this]` 。





# C++数字，随机数，数学运算

## 数学计算

> `#include <cmath>`

| 序号 | 函数 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | **double cos(double);** 该函数返回弧度角（double 型）的余弦。 |
| 2    | **double sin(double);** 该函数返回弧度角（double 型）的正弦。 |
| 3    | **double tan(double);** 该函数返回弧度角（double 型）的正切。 |
| 4    | **double log(double);** 该函数返回参数的自然对数。           |
| 5    | **double pow(double, double);** 假设第一个参数为 x，第二个参数为 y，则该函数返回 x 的 y 次方。 |
| 6    | **double hypot(double, double);** 该函数返回两个参数的平方总和的平方根，也就是说，参数为一个直角三角形的两个直角边，函数会返回斜边的长度。 |
| 7    | **double sqrt(double);** 该函数返回参数的平方根。            |
| 8    | **int abs(int);** 该函数返回整数的绝对值。                   |
| 9    | **double fabs(double);** 该函数返回任意一个浮点数的绝对值。  |
| 10   | **double floor(double);** 该函数返回一个小于或等于传入参数的最大整数。 |

## 随机数

设置种子：`#incliude <ctime>; srand((unsigned)time(NULL))；`

- time() 不需要传入参数，返回时间戳
- (unsigned)，将`time_t`转化为`unsigned`

生成随机数：`rand()`返回0~32767（随系统变化）的数字



# C++ 数组

声明：`type NAME[size];`

定义：`int lst[] = {1, 1, 4, 5, 1, 4};`自动生成长度为6的数组，当然也可以手动定义`lst[6]`

## 二维数组

声明`int lst[4][3];`定义一个4*3的二维数组

初始化可以有两种：

``` c++
int a[3][4] = {  
 {0, 1, 2, 3} ,   /*  初始化索引号为 0 的行 */
 {4, 5, 6, 7} ,   /*  初始化索引号为 1 的行 */
 {8, 9, 10, 11}   /*  初始化索引号为 2 的行 */
};

int a[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
```

![](https://www.runoob.com/wp-content/uploads/2014/09/two_dimensional_arrays.jpg)

## 数组指针

数组标识符可以直接当指针使用。

``` c++
#include <stdio.h>

int main() {
    int lst[6] = {1, 1, 4, 5, 1, 4};
    //int *p = lst;
    printf("%d\n", *(lst+3));  // lst[3] == 5
    return 0;
}
```

如果是二维数组：

``` c++
int main() {
    int lst[3][2] = {1, 1, 4, 5, 1, 4};
    //int *p = lst;
    printf("%d\n", *(lst[0]+1)); // 
    return 0;
}
```

`lst+1`是`lst[1]`的指针

可以改lst对应的值，但是不能更改lst这个指针指向的地址。

## 传递数组至函数

> 就函数而言，数组的长度是无关紧要的，因为 C++ 不会对形式参数执行边界检查。

1. `retType name(elementType *arg);`
2. `retType name(elementType arg[size]);`
3. `retType name(elementType arg[]);`

以上三种方法都一样，因为编译器都会把形参作为一个指针。



## 从函数返回数组

只能返回一个指针：`int * func(){return pnt;};`

**C++ 不支持在函数外返回局部变量的地址，除非定义局部变量为 static 变量，因为return后释放栈上空间了。**

# C++ 字符串

> `\0`为终止符，NULL

`char name[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', '\0'};`

`char name[] = "abcdefg";`

以上两种都很C。

| 序号 | 函数 & 目的                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | **strcpy(s1, s2);** 复制字符串 s2 到字符串 s1。              |
| 2    | **strcat(s1, s2);** 连接字符串 s2 到字符串 s1 的末尾。连接字符串也可以用 **+** 号，例如: `string str1 = "runoob"; string str2 = "google"; string str = str1 + str2;` |
| 3    | **strlen(s1);** 返回字符串 s1 的长度。                       |
| 4    | **strcmp(s1, s2);** 如果 s1 和 s2 是相同的，则返回 0；如果 s1<s2 则返回值小于 0；如果 s1>s2 则返回值大于 0。 |
| 5    | **strchr(s1, ch);** 返回一个指针，指向字符串 s1 中字符 ch 的第一次出现的位置。 |
| 6    | **strstr(s1, s2);** 返回一个指针，指向字符串 s1 中字符串 s2 的第一次出现的位置。 |

---

C++提供了`string`类：`string a = "eewfrg";`

string类提供了一系列针对字符串的操作，比如：

1. append() -- 在字符串的末尾添加字符

2. find() -- 在字符串中查找字符串
3.  insert() -- 插入字符
4. length() -- 返回字符串的长度
5. replace() -- 替换字符串
6. substr() -- 返回某个子字符串

# C++ 引用

> 变量的别名
>
> 类似指针，但是是隐式的

## 声明

- 必须声明时定义；
- 不存在NULL引用，必须指向一个合法的地址。
- 作用和`int const *p = a`差不多



## 把引用作为参数

就和python里的引用一样，只不过在c++所有都是mutable的。

比如定义一个交换函数，只要我在函数声明里写了引用类型，就可以正常交换（不用考虑什么取地址取内容）。

## 把引用作为返回值

和返回指针一样，返回时要看作用域。

1. 不能返回局部变量的引用。主要原因是局部变量会在函数返回后被销毁，因此被返回的引用就成为了"无所指"的引用，程序会进入未知状态。
2. 不能返回函数内部new分配的内存的引用。虽然不存在局部变量的被动销毁问题，可对于这种情况（返回函数内部new分配内存的引用），又面临其它尴尬局面。例如，被函数返回的引用只是作为一 个临时变量出现，而没有被赋予一个实际的变量，那么这个引用所指向的空间（由new分配）就无法释放，造成memory leak。
3. 可以返回类成员的引用，但最好是const。主要原因是当对象的属性是与某种业务规则（business rule）相关联的时候，其赋值常常与某些其它属性或者对象的状态有关，因此有必要将赋值操作封装在一个业务规则当中。如果其它对象可以获得该属性的非常 量引用（或指针），那么对该属性的单纯赋值就会破坏业务规则的完整性。

## const Reference, R-value Reference

经典的引用：

`int a = 1; int &b = a;`

但这样只能引用左值，假如我想引用一个右值，比如一个字面量呢？

`const int &a = "dwa";`常引用，`c-ref`，`const ref`

`int &&a = "dwa";`右值引用

# C/C++ DATE, TIME

`#include <ctime>`

有四个与时间相关的类型：**clock_t、time_t、size_t** 和 **tm**。类型 clock_t、size_t 和 time_t 能够把系统时间和日期表示为某种整数。

``` c++
struct tm {
  int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
  int tm_min;   // 分，范围从 0 到 59
  int tm_hour;  // 小时，范围从 0 到 23
  int tm_mday;  // 一月中的第几天，范围从 1 到 31
  int tm_mon;   // 月，范围从 0 到 11
  int tm_year;  // 自 1900 年起的年数
  int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
  int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
  int tm_isdst; // 夏令时
};
```

# C++ IO

| 头文件     | 函数和描述                                                   |
| :--------- | :----------------------------------------------------------- |
| <iostream> | 该文件定义了 **cin、cout、cerr** 和 **clog** 对象，分别对应于标准输入流、标准输出流、非缓冲标准错误流和缓冲标准错误流。 |
| <iomanip>  | 该文件通过所谓的参数化的流操纵器（比如 **setw** 和 **setprecision**），来声明对执行标准化 I/O 有用的服务。 |
| <fstream>  | 该文件为用户控制的文件处理声明服务。我们将在文件和流的相关章节讨论它的细节 |

``` C++
cin >> var;
cout << var << endl;
// cerr 非缓冲！
// clog 缓冲！
```

