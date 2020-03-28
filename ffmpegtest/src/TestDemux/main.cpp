/*******************************************************************************
**                                                                            **
**                     Jiedi(China nanjing)Ltd.                               **
**	               �������Ĳܿ����˴��������Ϊѧϰ�ο�                       **
*******************************************************************************/

/*****************************FILE INFOMATION***********************************
**
** Project       : FFmpeg
** Description   : FFMPEG��Ŀ����ʾ��
** Contact       : xiacaojun@qq.com
**        ����   : http://blog.csdn.net/jiedichina
**		��Ƶ�γ�
**�����ƿ���	http://study.163.com/u/xiacaojun
**��Ѷ����		https://jiedi.ke.qq.com/
**csdnѧԺ		http://edu.csdn.net/lecturer/lecturer_detail?lecturer_id=961
**51ctoѧԺ	    http://edu.51cto.com/lecturer/index/user_id-12016059.html
**�������µ�ffmpeg�汾 http://www.ffmpeg.club
**
**   ffmpeg+qt������ ѧԱȺ ��462249121 ����Ⱥ���ش���ͽ���
**   ΢�Ź��ں�  : jiedi2007
**		ͷ����	 : �Ĳܿ�
**
*******************************************************************************/
//������������������ ѧԱ��Ⱥ462249121���ش���ͽ���

#include <iostream>
#include <thread>
extern "C"{
#include "libavformat/avformat.h"
}
using namespace std;
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
static double r2d(AVRational r)
{
	return r.den == 0 ? 0:(double)r.num / (double)r.den;
}
void XSleep(int ms)
{
	//c++ 11
	chrono::milliseconds du(ms);
	this_thread::sleep_for(du);
}
int main(int argc, char *argv[])
{
	cout << "Test Demux FFmpeg.club" << endl;
	const char *path = "v1080.mp4";
	//��ʼ����װ��
	av_register_all();

	//��ʼ������� �����Դ�rtsp rtmp http Э�����ý����Ƶ��
	avformat_network_init();

	//��������
	AVDictionary *opts = NULL;
	//����rtsp����tcpЭ���
	av_dict_set(&opts, "rtsp_transport", "tcp", 0);

	//������ʱʱ��
	av_dict_set(&opts, "max_delay", "500", 0);


	//���װ������
	AVFormatContext *ic = NULL;
	int re = avformat_open_input(
		&ic,
		path,
		0,  // 0��ʾ�Զ�ѡ������
		&opts //�������ã�����rtsp����ʱʱ��
	);
	if (re != 0)
	{
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "open " << path << " failed! :" << buf << endl;
		getchar();
		return -1;
	}
	cout << "open " << path << " success! " << endl;

	//��ȡ����Ϣ 
	re = avformat_find_stream_info(ic, 0);
	
	//��ʱ�� ����
	int totalMs = ic->duration / (AV_TIME_BASE / 1000);
	cout << "totalMs = " << totalMs << endl;

	//��ӡ��Ƶ����ϸ��Ϣ
	av_dump_format(ic,0,path,0);

	//����Ƶ��������ȡʱ��������Ƶ
	int videoStream = 0;
	int audioStream = 1;

	//��ȡ����Ƶ����Ϣ ��������������ȡ��
	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVStream *as = ic->streams[i];
		cout << "codec_id = " << as->codecpar->codec_id << endl;
		cout << "format = " << as->codecpar->format << endl;

		//��Ƶ AVMEDIA_TYPE_AUDIO
		if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			cout <<i<< "��Ƶ��Ϣ" << endl;
			cout << "sample_rate = " << as->codecpar->sample_rate << endl;
			//AVSampleFormat;
			cout << "channels = " << as->codecpar->channels << endl;
			//һ֡���ݣ��� ��ͨ�������� 
			cout << "frame_size = " << as->codecpar->frame_size << endl;
			//1024 * 2 * 2 = 4096  fps = sample_rate/frame_size
			
		}
		//��Ƶ AVMEDIA_TYPE_VIDEO
		else if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			cout << i << "��Ƶ��Ϣ" << endl;
			cout << "width=" << as->codecpar->width << endl;
			cout << "height=" << as->codecpar->height << endl;
			//֡�� fps ����ת��
			cout<<"video fps = " <<r2d(as->avg_frame_rate)<<endl;
		}
	}

	//��ȡ��Ƶ��
	videoStream = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	///ic->streams[videoStream]
	//malloc AVPacket����ʼ��
	AVPacket *pkt = av_packet_alloc();
	for (;;)
	{
		int re = av_read_frame(ic, pkt);
		if (re != 0)
		{
			//ѭ������
			cout << "==============================end==============================" << endl;
			int ms = 3000; //����λ�� ����ʱ�������������ת��
			long long pos = (double)ms/ (double)1000*r2d(ic->streams[pkt->stream_index]->time_base);
			av_seek_frame(ic, videoStream, pos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
			continue;
		}
		cout << "pkt->size = "<< pkt->size << endl;
		//��ʾ��ʱ��
		cout << "pkt->pts = " << pkt->pts << endl;
		
		//ת��Ϊ���룬������ͬ��
		cout << "pkt->pts ms = " << pkt->pts * (r2d(ic->streams[pkt->stream_index]->time_base) * 1000) << endl;



		//����ʱ��
		cout << "pkt->dts = " << pkt->dts << endl;
		if (pkt->stream_index == videoStream)
		{
			cout << "ͼ��" << endl;
		}
		if (pkt->stream_index == audioStream)
		{
			cout << "��Ƶ" << endl;
		}


		//�ͷţ����ü���-1 Ϊ0�ͷſռ�
		av_packet_unref(pkt);

		//XSleep(500);
	}

	av_packet_free(&pkt);



	if (ic)
	{
		//�ͷŷ�װ�����ģ����Ұ�ic��0
		avformat_close_input(&ic);
	}

	getchar();
	return 0;
}