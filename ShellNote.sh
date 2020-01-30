#!/bin/sh

####双引号里可以有变量可以出现转义字符
your_name='qinjx'
str="Hello, I know your are \"$your_name\"! \n"

####拼接字符串
your_name="qinjx"
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"

echo $greeting $greeting_1

####获取字符串长度：
string="abcd"
echo ${#string} #输出：4

####提取子字符串
string="alibaba is a great company"
echo ${string:1:4} #输出：liba

####查找子字符串
string="alibaba is a great company"
#echo `expr index "$string" is`#输出：3，这个语句的意思是：找出字母i在这名话中的位置，要在linux下运行，mac下会报错???


#还要注意，sh里的if [ $foo -eq 0 ]，这个方括号跟Java/PHP里if后面的圆括号大不相同，它是一个可执行程序（和ls, grep一样），想不到吧？在CentOS上，它在/usr/bin目录下：

####if else
#if condition
#then
#	command1 
#	command2
#	...
#	commandN
 
#elif condition2
#	command0

#else
#	commandN+1
#fi

#if `ps -ef | grep ssh`;  then echo hello; fi

#####for while

#for var in item1 item2 ... itemN
#do
#	command1
#	command2
#	...
#	commandN
#done

#while condition
#do
#	command
#done

#####OR

#while true
#do
#	command
#done

####如果function.sh是用户传入的参数，如何获得它的绝对路径呢？方法是：

#real_path=`readlink -f $1`#$1是用户输入的参数，如function.sh
#. $real_path

####Bash变量都是字符串。但是依赖于上下文，Bash也允许比较操作和算术操作。决定这些的关键因素是变量中的值是否只有数字，只有当变量是纯数字时，该变量才是“数字类型的”，否则就是字符串类型的

a=1234
let "a+=1"
echo ${a}

####局部变量(local variables)：这种变量只有在变量所在的代码块或者函数中才可见，需要使用local声明；

####环境变量(environmental variables)：所有的程序（包括shell启动的程序）都能访问环境变量。
####如果一个shell脚本设置了环境变量,需要用 export 命令来通知脚本的环境。

####函数的定义

function func_name()
{
    # 函数体
    echo something
}

##### Calling func1
func_name


####有参函数的调用
function func2()
{
    echo "This is func2"
    
    a=$1
    b=$2
    echo "a is : $a"
    echo "b is : $b"
}

# Calling func2,and pass two parameters
func2 "aaa" "bbb"















