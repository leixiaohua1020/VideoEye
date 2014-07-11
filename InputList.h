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
#include "afxcmn.h"
#include "VideoEyeDlg.h"

#include <vector>
using std::vector;

// InputList 对话框
//注意：VideoEyeDlg.h中已经include了inputlist.h
//现在需要在inputlist.h中include VideoEyeDlg.h
//因此会陷入无限死循环中
//解决方法？貌似是在该文件中提前声明一下
//不知道是不是合适的方法，总之编译通过了
class CVideoEyeDlg;

//-------
class InputList : public CDialogEx
{
	DECLARE_DYNAMIC(InputList)

public:
	InputList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InputList();

// 对话框数据
	enum { IDD = IDD_INPUTLIST};
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//自己添加的，初始化InputList
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_urllist;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDblclkUrllist(NMHDR *pNMHDR, LRESULT *pResult);
	CToolBar m_wndToolBar;
	afx_msg void OnInputlistExport();
	afx_msg void OnInputlistImport();
	void XSPFImport(CString filepath);
	void XSPFExport(CString filepath);
	afx_msg void OnM3uImport();
	void M3UImport(CString filepath);
	void M3UExport(CString filepath);


	CString GetURLByIndex(int data_index);

	//设置值的时候用到
	CVideoEyeDlg *maindlg;
//	afx_msg void OnInputlistHelp();

	//一条记录
	typedef struct Track{
		CString location;
		CString title;
		CString album;
		CString creator;
		CString trackNum;
		CString annotation;
		CString duration;
	}Track;
	//播放列表
	vector<Track> tracklist;
	void RefreshList();
	void SystemClear();
	//UTF-8转GB2312
	char* U2G(const char* utf8);
	afx_msg void OnM3uExport();
};
