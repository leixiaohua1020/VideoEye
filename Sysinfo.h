/* 
 *
 * 
 * VideoEye
 *
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 */


#pragma once


extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
};


// Sysinfosubac 对话框

class Sysinfosubac : public CDialogEx
{
	DECLARE_DYNAMIC(Sysinfosubac)

public:
	Sysinfosubac(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sysinfosubac();

	// 对话框数据
	enum { IDD = IDD_SYSINFOSUB_AC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sysinfoac;
};


// Sysinfosubif 对话框

class Sysinfosubif : public CDialogEx
{
	DECLARE_DYNAMIC(Sysinfosubif)

public:
	Sysinfosubif(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sysinfosubif();

	// 对话框数据
	enum { IDD = IDD_SYSINFOSUB_IF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sysinfoif;
};


// Sysinfosuboc 对话框

class Sysinfosuboc : public CDialogEx
{
	DECLARE_DYNAMIC(Sysinfosuboc)

public:
	Sysinfosuboc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sysinfosuboc();

	// 对话框数据
	enum { IDD = IDD_SYSINFOSUB_OC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sysinfooc;
};



// Sysinfosubup 对话框

class Sysinfosubup : public CDialogEx
{
	DECLARE_DYNAMIC(Sysinfosubup)

public:
	Sysinfosubup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sysinfosubup();

	// 对话框数据
	enum { IDD = IDD_SYSINFOSUB_UP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sysinfoup;
};


// Sysinfosubvc 对话框

class Sysinfosubvc : public CDialogEx
{
	DECLARE_DYNAMIC(Sysinfosubvc)

public:
	Sysinfosubvc(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sysinfosubvc();

	// 对话框数据
	enum { IDD = IDD_SYSINFOSUB_VC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_sysinfovc;
};



// Sysinfo 对话框

class Sysinfo : public CDialogEx
{
	DECLARE_DYNAMIC(Sysinfo)

public:
	Sysinfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Sysinfo();

// 对话框数据
	enum { IDD = IDD_SYSINFO };
	//选项卡
	Sysinfosubup sysinfosubup;
	Sysinfosubif sysinfosubif;
	Sysinfosubvc sysinfosubvc;
	Sysinfosubac sysinfosubac;
	Sysinfosuboc sysinfosuboc;
	CDialog* pDialog[5];  //用来保存对话框对象指针

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_sysinfotab;

	int m_CurSelTab;
	//读取输入文件协议的时候使用；来自ffmpeg源码
	typedef struct URLContext {
		const AVClass *av_class; ///< information for av_log(). Set by url_open().
		struct URLProtocol *prot;
		int flags;
		int is_streamed;  /**< true if streamed (no seek possible), default = false */
		int max_packet_size;  /**< if non zero, the stream is packetized with this max packet size */
		void *priv_data;
		char *filename; /**< specified URL */
		int is_connected;
		AVIOInterruptCB interrupt_callback;
	} URLContext;
	typedef struct URLProtocol {
		const char *name;
		int (*url_open)(URLContext *h, const char *url, int flags);
		int (*url_read)(URLContext *h, unsigned char *buf, int size);
		int (*url_write)(URLContext *h, const unsigned char *buf, int size);
		int64_t (*url_seek)(URLContext *h, int64_t pos, int whence);
		int (*url_close)(URLContext *h);
		struct URLProtocol *next;
		int (*url_read_pause)(URLContext *h, int pause);
		int64_t (*url_read_seek)(URLContext *h, int stream_index,
			int64_t timestamp, int flags);
		int (*url_get_file_handle)(URLContext *h);
		int priv_data_size;
		const AVClass *priv_data_class;
		int flags;
		int (*url_check)(URLContext *h, int mask);
	} URLProtocol;
	//存储支持格式的链表的第一个单元
	typedef struct SystemInfo {
		URLProtocol *first_up;
		AVInputFormat *first_if;
		AVCodec *first_c;
	}SystemInfo;

	SystemInfo si;

	void GetSysinfo();
	afx_msg void OnSelchangeSysinfoTab(NMHDR *pNMHDR, LRESULT *pResult);
};
