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
#include "resource.h"
#include "stdafx.h"
#include "afxcmn.h"
// Videodecode 对话框

class Videodecode : public CDialogEx
{
	DECLARE_DYNAMIC(Videodecode)

public:
	Videodecode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Videodecode();

// 对话框数据
	enum { IDD = IDD_VIDEODECODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//自己添加的，初始化Teechart
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_decodeframe_v;
	afx_msg void OnBnClickedCancel();
	void SystemClear();
	void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
};
