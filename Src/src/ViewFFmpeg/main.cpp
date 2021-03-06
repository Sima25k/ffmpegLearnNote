/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               创建：夏曹俊，此代码可用作为学习参考                       **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project       : FFmpeg
** Description   : FFMPEG项目创建示例
** Contact       : xiacaojun@qq.com
**        博客   : http://blog.csdn.net/jiedichina
**		视频课程 
**网易云课堂	http://study.163.com/u/xiacaojun
**腾讯课堂		https://jiedi.ke.qq.com/
**csdn学院		http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961
**51cto学院	    http://edu.51cto.com/lecturer/index/user_id-12016059.html
**下载最新的ffmpeg版本 http://www.ffmpeg.club
**
**   ffmpeg+qt播放器 学员群 ：462249121 加入群下载代码和交流
**   微信公众号  : jiedi2007
**		头条号	 : 夏曹俊
**
*******************************************************************************/
//！！！！！！！！！ 学员加群462249121下载代码和交流

#include <iostream>
using namespace std;
//要引用c语言函数
extern "C"{
	#include <libavcodec/avcodec.h>
}
//预处理指令导入库
#pragma comment(lib,"avcodec.lib")
int main(int argc,char *argv[])
{
	//显示ffmpeg的编译配置
	cout << "Test FFmpeg.club" << endl;
#ifdef _WIN64 //64位 win
	cout << "Windows X64" << endl;
#endif
#ifdef WIN32 //32位 win
	cout << "Windows X86" << endl;
#endif
#ifdef _WIN32 //32位和64位 win
#else
	cout << "Linux" << endl;
#endif
	cout << avcodec_configuration() << endl;
	getchar();
	return 0;
}