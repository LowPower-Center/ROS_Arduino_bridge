# ROS_Arduino_bridge
原始文件来自https://github.com/hbrobotics/ros_arduino_bridge

本程序
+ 适配了淘宝TB6612驱动板以及对应的直流电机
+ 只适用于Python3版本，Python2只需使用原作者代码。基于Python3版本的ros-noetic可以使用，测试通过。

硬件组成
+ 树莓派4B ubuntu-mate20.04
+ arduino mega2560
+ TB6612驱动板
+ 直流减速电机
+ 万向轮


一些debug的细节
+ pyserial库可能读写速度比较快，程序串口调试一致失败，后来在串口通讯前调用一次readline解决问题
+ python2和python3语法不协同，包括但不限于thread库命名、dict.items遍历、str编码
+ 尝试使用arduino nano板子去代替mega2560，但是nano上可以自由控制的引脚数量不足，而且使用两个中断后，板子的pwm似乎不好用，该方案待解决。
+ 报错error encoder出现与数据类型，map无法使用list操作（解包，取长度等等），把返回值map改成list可行（很可能是从Python3语法与2不兼容导致）
