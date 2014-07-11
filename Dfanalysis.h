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

#include "stdafx.h"
#include "resource.h"
#include "Dfanalysispic.h"
// Dfanalysis 对话框
class CVideoEyeDlg;

class Dfanalysis : public CDialogEx
{
	DECLARE_DYNAMIC(Dfanalysis)

public:
	Dfanalysis(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dfanalysis();

// 对话框数据
	enum { IDD = IDD_DFANALYSIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//自己添加的，初始化
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CComboBox m_dfanalysismethod;
	afx_msg void OnBnClickedDfanalysisOpen();
	void DrawPic();

	enum {DRAW_Q,DRAW_MB_TYPE,DRAW_MV0,DRAW_MV1,DRAW_REFINDEX0,DRAW_REFINDEX1};
	//保护临界段
	CCriticalSection critical_section;
	
	//宽高
	int width;
	int height;
	//每行宏块数
	int mb_stride;
	//宏块总数
	int mb_sum;
	//Qtable
	char *qscale_table;
	int qscale_type;
	//宏块类型
	int *mb_type;
	//运动矢量
	short (*motion_val0)[2];
	short (*motion_val1)[2];
	//参考帧
	char *ref_index0;
	char *ref_index1;
	//其他相关的系数
	int frame_index;
	int pict_type;
	int packet_size;
	long pts;
	int refs;
	//显示时间
	float ptime;
	/**
     * log2 of the size of the block which a single vector in motion_val represents:
     * (4->16x16, 3->8x8, 2-> 4x4, 1-> 2x2)
     * - encoding: unused
     * - decoding: Set by libavcodec.
     */
	int motion_subsample_log2;
	int codec_id;
	int mb_width;
	//像素数据
	uint8_t *data[AV_NUM_DATA_POINTERS];
	int linesize[AV_NUM_DATA_POINTERS];
	enum AVPixelFormat pix_fmt;


	CEdit m_dfanalysismbheight;
	CEdit m_dfanalysismbsum;
	CEdit m_dfanalysismbwidth;
	CEdit m_dfanalysismvsubsample;
	//画箭头
	typedef struct tARROWSTRUCT {
		int nWidth;     // width (in pixels) of the full base of the arrowhead
		float fTheta;   // angle (in radians) at the arrow tip between the two
		//  sides of the arrowhead
		bool bFill;     // flag indicating whether or not the arrowhead should be
		//  filled
	} ARROWSTRUCT;
	void ArrowTo1(HDC hDC, int x, int y, ARROWSTRUCT *pA);
	void ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA);

	CMFCPropertyGridCtrl m_dfanalysisoption;
	
	CMFCPropertyGridProperty *prop_global;
	CMFCPropertyGridProperty *prop_global_showmbedge;
	CMFCPropertyGridColorProperty *prop_global_showmbedge_color;
	CMFCPropertyGridFontProperty *prop_global_font;
	CMFCPropertyGridProperty *prop_global_winsize;

	CMFCPropertyGridProperty *prop_q;
	CMFCPropertyGridProperty *prop_q_shownum;

	CMFCPropertyGridProperty *prop_q_showcolor;
	CMFCPropertyGridProperty *prop_q_colortype;
	CMFCPropertyGridProperty *prop_mb_type;
	CMFCPropertyGridProperty *prop_mb_type_showsubmb;
	CMFCPropertyGridProperty *prop_mb_type_showcolor;
	CMFCPropertyGridProperty *prop_mb_type_showskip;
	CMFCPropertyGridProperty *prop_mb_type_showlist;
	CMFCPropertyGridProperty *prop_mv0;
	CMFCPropertyGridColorProperty *prop_mv0_colortype;
	CMFCPropertyGridProperty *prop_mv0_linetype;
	CMFCPropertyGridProperty *prop_mv1;
	CMFCPropertyGridColorProperty *prop_mv1_colortype;
	CMFCPropertyGridProperty *prop_mv1_linetype;
	//------------------
	BOOL prop_global_showmbedge_val;
	CFont *prop_global_font_val;
	BOOL prop_q_shownum_val;
	BOOL prop_q_showcolor_val;
	BOOL prop_mb_type_showsubmb_val;
	BOOL prop_mb_type_showcolor_val;
	BOOL prop_mb_type_showskip_val;
	BOOL prop_mb_type_showlist_val;
	COLORREF prop_mv0_colortype_val;
	int prop_mv0_linetype_val;
	COLORREF prop_mv1_colortype_val;
	int prop_mv1_linetype_val;

	float prop_global_winsize_val;

	COLORREF prop_global_showmbedge_color_val;
	//-------------------
	void GetOption();
	int m_dfanalysisnum16x16;
	int m_dfanalysisnum16x8;
	int m_dfanalysisnum8x16;
	int m_dfanalysisnum8x8;
	int m_dfanalysisnumavgq;
	int m_dfanalysisnumintra16x16;
	int m_dfanalysisnumintra4x4;
	int m_dfanalysisnumskip;
	int m_dfanalysisnummaxq;
	int m_dfanalysisnumminq;
	int m_dfanalysisnuml0;
	int m_dfanalysisnuml1;
//	CEdit m_dfanalysismbpacketsize;
	CEdit m_dfanalysismbpictype;
	CEdit m_dfanalysismbptime;
	CEdit m_dfanalysismbpts;
	CEdit m_dfanalysismbref;
	CEdit m_dfanalysismbframeindex;
	CEdit m_dfanalysismbqtype;
	int m_dfanalysisautointerframenum;
	CButton m_dfanalysisauto;
	afx_msg void OnBnClickedDfanalysisAuto();
	afx_msg void OnKillfocusDfanalysisAutoInterframenum();
	//画刷
	CBrush *pBrush;
	afx_msg void OnPaint();
	CVideoEyeDlg *maindlg;

	void DrawSample();
	//画面对话框
	Dfanalysispic *picdlg;

	void DrawFrame();
	
	afx_msg void OnBnClickedCancel();
	
	//画的那张图
	HBITMAP hpic;
	//用来保存屏幕到图像文件。
	HBITMAP CopyDCToBitmap(HDC hScrDC, LPRECT lpRect);

	BOOL SaveBmp(HBITMAP hBitmap, CString FileName);
	//分析是否结束？
	BOOL dffinish;
	afx_msg void OnDestroy();
	CButton m_dfanalysisoutpicfolder;
	CMFCEditBrowseCtrl m_dfanalysisoutpicfolderurl;
	afx_msg void OnClickedDfanalysisOutpicfolder();
	CButton m_dfanalysisoutdatafolder;
	CMFCEditBrowseCtrl m_dfanalysisoutdatafolderurl;
	afx_msg void OnClickedDfanalysisOutdatafolder();
};
