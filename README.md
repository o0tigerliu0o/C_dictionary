# C_dictionary 电子词典
### 功能1：单词查询
给定文本文件“dict.txt”，该文件用于存储词库。词库为“英-汉”，“汉-英”双语词典，每个单词和其解释的格式固定，如下所示：

#### 单词

Trans:解释1@解释2@…解释n

每个新单词由“#”开头，解释之间使用“@”隔开。一个词可能有多个解释，解释均存储在一行里，行首固定以“Trans：”开头。下面是一个典型的例子：

#### abyssinian

Trans:a. 阿比西尼亚的@n. 阿比西尼亚人;依索比亚人

该词有两个解释，一个是“a. 阿比西尼亚的”；另一个是“n. 阿比西尼亚人;依索比亚人”。

要求编写程序将词库文件读取到内存中，接受用户输入的单词，在字典中查找单词，并且将解释输出到屏幕上。用户可以反复输入，直到用户输入“exit”字典程序退出。

程序执行格式如下所示：

./app –text

-text表示使用文本词库进行单词查找。

### 功能2：建立索引，并且使用索引进行单词查询
要求建立二进制索引，索引格式如下图所示。将文本文件“dict.txt”文件转换为上图所示索引文件“dict.dat”，使用索引文件实现单词查找。程序执行格式如下：

./app –index

-index表示使用文本词库dict.txt建立二进制索引词库dict.dat

./app –bin

-bin表示使用二进制索引词库进行单词查找。

### 编译安装
gcc find_word_from_index.c find_word_from_text.c main.c process.c -o app

### 项目来源：https://blog.csdn.net/wqx521/article/details/50830573
![C/C++ 学习路线图](https://www.github.com/o0tigerliu0o/C_dictionary/study.jpg)

