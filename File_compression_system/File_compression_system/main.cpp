/*
文件压缩：
1.什么是文件压缩？
2.为什么要对文件进行压缩？
   文件太大，节省空间
   提高数据在网络上传输的效率
   对数据保护的作用--加密
3.文件压缩分类？
    无损压缩：
	有损压缩：解压缩之后不能将其还原成与源文件完全相同的格式
4.如何进行压缩？
*/

/*
压缩文件包含两部分：压缩信息：源文件后缀，编码行数, 字符次数信息
                    压缩数据：
*/

#if 0
#include "FileCompressHuff.h"



int main()
{
	FileCompressHuff fc;
	fc.CompressFile("1.txt");
	fc.UncompressFile("2.txt");
	return 0;
}

#endif


#include "LZ77.h"
#include <string>

int main()
{
	LZ77 lz;

	std::string postFix;
	lz.CompressFile("1.txt", postFix);
	lz.UncompressFile("1.lzp", postFix);
	return 0;
}

/*
问题1：不能用char形，要用unsiged char
问题2：多写入了一个空格到压缩文件
*/

/*
1.压缩数据格式
2.汉字-->定位问题？如何解决？
3.文件压缩或者解压缩一部分
4.如何保证压缩的正确性？？---beyond compare
5.压缩比率
6.是不是每次压缩之后都会变小？会变大吗
7.文本文件，视频文件，音频，图片
8.改进的方式
*/

/*
LZ77:
1.缓冲区的问题
*/