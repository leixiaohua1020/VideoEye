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
//OpenCV
#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
// Rawanalysis 对话框

//-----------
#define MR(Y,U,V) (Y + (1.403)*(V-128))  
#define MG(Y,U,V) (Y - (0.344) * (U-128) - (0.714) * (V-128) )   
#define MB(Y,U,V) (Y + ((1.773) * (U-128))) 

//主对话框------
class CVideoEyeDlg;
//-----------
class Rawanalysis : public CDialogEx
{
	DECLARE_DYNAMIC(Rawanalysis)

public:
	Rawanalysis(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Rawanalysis();
	//自己添加的，初始化
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_RAWANALYSIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRawanalysisOpen();
	//------------------
	CVideoEyeDlg *maindlg;
	//帧号
	int frame_index;
	//YUV转IplImage的两种方法-----------
	//存放非压缩域
	char *y_data;
	char *u_data;
	char *v_data;
	int y_width;
	int y_height;
	//存放转换后的图像
	IplImage *result_image;
	IplImage *yuvimage;
	//-----------------
	//保护临界段
	CCriticalSection critical_section;
	int YUVtoIpl1();
	void YUV420_C_RGB( char* pY,char* pU,char* pV, unsigned char* pRGB, int height, int width);
	int YUVtoIpl2();
	//----------------
	int LoadFromMemory();
	int LoadFromURL();
	//算法函数------------------------------------
	//颜色分布直方图
	int Color_Histogram();
	//边缘检测
	int Canny();
	//轮廓检测
	int Contour();
	//二维傅里叶变换
	void cvShiftDFT(CvArr * src_arr, CvArr * dst_arr );
	int DFT();
	//人脸识别
	CvMemStorage* storage;
	CvHaarClassifierCascade* cascade;
	void detect_and_draw( IplImage* img );
	int face_detect();


	int m_rawanalysismethod;
	void SystemClear();
	afx_msg void OnBnClickedCancel();
	//-------------------------
	enum {SHOW_R_COMP,SHOW_G_COMP,SHOW_B_COMP,SHOW_Y_COMP,SHOW_U_COMP,SHOW_V_COMP};
	//显示颜色分量
	int show_color_component(int nameid);
	int m_rawanalysisautointerframenum;
	CButton m_rawanalysisauto;
	afx_msg void OnBnClickedRawanalysisAuto();
	afx_msg void OnKillfocusRawanalysisAutoInterframenum();
	CButton m_rawanalysisoutpicfolder;
	CMFCEditBrowseCtrl m_rawanalysisoutpicfolderurl;
	afx_msg void OnClickedRawanalysisOutpicfolder();
	int m_rawanalysiscolorhbin;
	int m_rawanalysiscolorsbin;
	int m_rawanalysiscontourthres;
	int m_rawanalysiscannythres1;
	int m_rawanalysiscannythres2;
	CString m_rawanalysisfacexmlurl;
};
