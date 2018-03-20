echo off

#0help功能测试
start wc.exe wc.exe -help

#1基本功能测试
start wc.exe wc.exe -c -w -l test.c

#2基本功能测试---输出到指定的文件
start wc.exe wc.exe -c -w -l test.c -o output1.txt

#3检测用户的恶意输入（想输出全部结果但是没有输入-s） 
start wc.exe wc.exe -c *.c -o output2.txt

#4检测用户的恶意输入（没有输入待检测的.c文件）
start wc.exe wc.exe -w -c -l 

#5当前路径全部文件是否读取成功测试
start wc.exe wc.exe -s -c -w -l *.c -o output3.txt 

#6检测用户输入错误的文件名
start wc.exe wc.exe -s -c -w -l finally.c -o output4.txt 

#7复杂数据类型检测
start wc.exe wc.exe -s -a -c -w -l *.c -o output5.txt 

#8停用词表检测
start wc.exe wc.exe -s -c -w -l *.c -o output6.txt -e stoplist.txt 

#9检测使用停用词表命令出错
start wc.exe wc.exe -s -c -w -l *.c -o output7.txt stoplist.txt

#10检测输出到指定文件命令出错
start wc.exe wc.exe -s -c -w -l *.c  output8.txt 

#11全部功能集成测试
start wc.exe wc.exe -s -a -c -w -l *.c -o output9.txt -e stoplist.txt







