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


// VideoEyeDlg.h : 头文件
//

#pragma once
//TeeChart
//Tchart
#include "stdafx.h"

#include "ve_play.h"

//系统对话框
#include "Welcome.h"
#include "InputList.h"
#include "Videodecode.h"
#include "Audiodecode.h"
#include "Sysinfo.h"
#include "Dataoutput.h"
#include "Rawanalysis.h"
#include "Assistantmediainfo.h"
#include "Optplayer.h"
#include "Dfanalysis.h"

//多线程
UINT Thread_Play(LPVOID lpParam);
//存储播放地址


// CVideoEyeDlg 对话框
class CVideoEyeDlg : public CDialogEx
{
// 构造
public:
	CVideoEyeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INTERNETVE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CWinThread *pThreadPlay;


	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	//自绘按钮
	CBitmapButton okbutton;
	CBitmapButton seek_bbutton;
	CBitmapButton seek_fbutton;
	CBitmapButton pausebutton;
	CBitmapButton stopbutton;
	CBitmapButton seekstepbutton;
	CBitmapButton fullscreenbutton;
	CBitmapButton aboutbutton;
	CBitmapButton exitbutton;

	afx_msg void OnBnClickedOk();
	int GetURL();
	char url[MAX_URL_LENGTH];


	CEdit m_decoder_name;
	CEdit m_pix_fmt;
	CEdit m_wxh;
	CEdit m_bitrate;
	CEdit m_extention;
	CEdit m_metadata;
	afx_msg void OnClickedStop();
	CSpinButtonCtrl m_spin_delay;
	int m_edit_delay;
	afx_msg void OnChangeEditDelaytime();
	afx_msg void OnClickedOutput();
	afx_msg void OnBnClickedAbout();

	CEdit m_framerate;
	afx_msg void OnBnClickedPause();
	int pause_flag;
	void SystemClear();
	void OnTimer(UINT nIDEvent);
	//----------
	int buffer_remain;
	int buffer_ptr_location;
	int buffer_end;
	int packet_size;
	CEdit m_timelong;
	afx_msg void OnBnClickedInputurlbutton();

	CEdit m_input_format;
	CEdit m_input_protocol;

	//对话框对象--------

	InputList *inputlist;
	Videodecode *videodecode;
	Audiodecode *audiodecode;
	Dataoutput *dataoutput;
	Sysinfo *sysinfo;
	Rawanalysis *rawanalysis;
	Assistantmediainfo *assistantmi;
	Optplayer *optplayer;
	Dfanalysis *dfanalysis;

	//------------------
	CEdit m_decoder_name_au;
	CEdit m_sample_rate_au;
	afx_msg void OnDropFiles(HDROP hDropInfo);

	CEdit m_inputurl;
	afx_msg void OnBnClickedOpenInputlist();
	afx_msg void OnBnClickedVideodecode();
	afx_msg void OnBnClickedAudiodecode();
	afx_msg void OnHelpDoc();
	afx_msg void OnHelpHomepage();

	afx_msg void OnSysinfoSPixformat();
	afx_msg void OnBnClickedFullscreen();
	afx_msg void OnBnClickedSeekF();
	afx_msg void OnBnClickedSeekB();
	afx_msg void OnBnClickedSeekStep();
	afx_msg void OnSeekF10();
	afx_msg void OnSeekB10();
	afx_msg void OnSeekF600();
	afx_msg void OnSeekB600();
	afx_msg void OnResize50();
	afx_msg void OnResize75();
	afx_msg void OnResize100();
	afx_msg void OnResize125();
	afx_msg void OnResize150();
	afx_msg void OnResize175();
	afx_msg void OnResize200();
	afx_msg void OnResize300();
	afx_msg void OnResize400();
	afx_msg void OnReaspect11();
	afx_msg void OnReaspect32();
	afx_msg void OnReaspect43();
	afx_msg void OnReaspect54();
	afx_msg void OnReaspect149();
	afx_msg void OnReaspect1410();
	afx_msg void OnReaspect169();
	afx_msg void OnReaspect1610();
	afx_msg void OnReaspect235100();
	afx_msg void OnWindowYuv();
	afx_msg void OnWindowY();
	afx_msg void OnWindowU();
	afx_msg void OnWindowV();
	afx_msg void OnWindowRgb();
	afx_msg void OnWindowR();
	afx_msg void OnWindowG();
	afx_msg void OnWindowB();
	afx_msg void OnWindowAWave();
	afx_msg void OnWindowARdft();
	afx_msg void OnDataOutputMA();
	afx_msg void OnDataOutputMV();
	afx_msg void OnDataOutputMO();
	afx_msg void OnDataOutputRYuv();
	afx_msg void OnDataOutputRY();
	afx_msg void OnDataOutputRU();
	afx_msg void OnDataOutputRV();
	afx_msg void OnDataOutput();
	afx_msg void OnSpecialPRtmp();

	CEdit m_channels_au;
	afx_msg void OnAssistantMediainfo();
	afx_msg void OnSpecialVIJpg();
	afx_msg void OnRawanalysisHistogram();
	afx_msg void OnRawanalysisCanny();
	afx_msg void OnRawanalysisContour();
	afx_msg void OnRawanalysis2ddft();
	afx_msg void OnRawanalysis();
	afx_msg void OnRawanalysisFaceDetect();
	afx_msg void OnSpecialFFlv();

	afx_msg void OnSpecialAAac();
	afx_msg void OnSpecialFTs();
	afx_msg void OnSpecialVH264();
	void ResetBtn();
	void ActiveBtn();
	afx_msg void OnOptPlayer();
	CSliderCtrl m_playprogress;
	void InitBitmapButton();
	void InitSubWindow();
	void FreeSubWindow();
	CEdit m_aqsize;
	CEdit m_vqsize;
	CEdit m_duration;
	CEdit m_currentclock;

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_avdiff;

	CToolTipCtrl m_tooltip;
	void InitTooltip();
	afx_msg void OnDfanalysis();
	afx_msg void OnRawanalysisY();
	afx_msg void OnRawanalysisU();
	afx_msg void OnRawanalysisV();
	afx_msg void OnRawanalysisR();
	afx_msg void OnRawanalysisG();
	afx_msg void OnRawanalysisB();
	afx_msg void OnTopmostAlways();
	afx_msg void OnTopmostNever();
	//是否处于播放阶段
	int is_playing;
//	afx_msg void OnSpecialAbout();
	afx_msg void OnLangCn();
	afx_msg void OnLangEn();

	afx_msg void OnCancel();
	afx_msg void OnSysinfo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnWindowstretchKeepratio();
	afx_msg void OnWindowstretchResize();
};
