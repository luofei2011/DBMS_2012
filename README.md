2012-10-15更新：
1.新加入insertInto()函数，执行过程如下：
（1）先在model文件中找到当前要插入表的表结构；
（2）并在判断的过程中写入数据字典中：属性个数+元组长度+属性所占字节（N）；
（3）判断数据类型与存取长度；
（4）接下来是写表：直接遍历判断过程中存取的一个保存类型的数组，按此顺序依次读入用户输入的数据，并调用相应的函数进行判断
数据类型是否正确（int与double型暂未判断），进而把正确的写入表中。
2.使用问题：
（1）int与double型数据未做判断直接插入；
（2）char型数据有长度限制（用户自定义的，读取过程中保存在num_of_int数组中），若用户输入的数据长度超过自己定义的长度则
不做提示按先前定义好的长度插入！

2012-10-26
property_sort.dat文件中存储的内容：属性个数+表名+属性类型（按序）int(1),char(2),double(3),date(4),time(5)

next:
缺主键检测
//property_name.dat文件每插入一次就重写一次，需要在建表的时候写一次就够.
//dictionary.dat有问题.
//delete 
//display
//discribe

使用注意：
//1.不能使用ASCII值小于‘A’的字符
2.日期及时间类型未提供正确性检测，正确输入格式"2012-10-17","09:39:46".
3."select XX from XX where XX"中from,where需要小写（未转换格式）.
4.当插入的时候生成dictionary.dat和property_name.dat文件.
5.不能有多余的空格，如:
select age from man where name="XX"
create table XX (name char(6),age int)
6.表名中不能含有0.
7.select语句使用时：条件后面的值必须严格按照:char+date+time需要包含在'"'中，int+double只写出数字即可！
8.select语句中where后面的条件中，and not or只允许出现一次。且and or两边的条件必须一致.
where name="XX" and(or) age=XX;
9.做投影连接的时候select后面的表顺序要与where条件后面的一致.

设计技巧：
select语句后面的条件无外乎包括'<=>'这3个比较不等式.其ASCII值分别为:60.61.62.

