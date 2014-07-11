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


// Assistantmediainfo 对话框
#include "resource.h"
#include "stdafx.h"
#include "MediaInfoDLL.h"

class CVideoEyeDlg;

class Assistantmediainfo : public CDialogEx
{
	DECLARE_DYNAMIC(Assistantmediainfo)

public:
	Assistantmediainfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Assistantmediainfo();

// 对话框数据
	enum { IDD = IDD_ASSISTANTMEDIAINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//自己添加的
	virtual BOOL OnInitDialog();
	BOOL mediainfo();
	CString fileurl;
	//要显示的信息
	CString To_Display;
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_mediainfodisplay;
	CVideoEyeDlg *maindlg;
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnIdcancel();
};
