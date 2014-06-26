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

#include "stdafx.h"
#include "Audiodecode.h"
#include "afxdialogex.h"


// Audiodecode 对话框

IMPLEMENT_DYNAMIC(Audiodecode, CDialogEx)

Audiodecode::Audiodecode(CWnd* pParent /*=NULL*/)
	: CDialogEx(Audiodecode::IDD, pParent)
{

}

Audiodecode::~Audiodecode()
{
}

void Audiodecode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DECODEFRAME_A, m_decodeframe_a);
}


BEGIN_MESSAGE_MAP(Audiodecode, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Audiodecode::OnBnClickedCancel)
END_MESSAGE_MAP()


// Audiodecode 消息处理程序
BOOL Audiodecode::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString resloader;
	resloader.LoadString(IDS_AUDIODECODE);
	SetWindowText(resloader);
	//整行选择；有表格线；表头；单击激活
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	m_decodeframe_a.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_decodeframe_a.SetExtendedStyle(dwExStyle);

	resloader.LoadString(IDS_AUDIODECODE_NUM);
	m_decodeframe_a.InsertColumn(0,resloader,LVCFMT_CENTER,60,0);
	resloader.LoadString(IDS_AUDIODECODE_SIZE);
	m_decodeframe_a.InsertColumn(1,resloader,LVCFMT_CENTER,60,0);
	resloader.LoadString(IDS_AUDIODECODE_PTS);
	m_decodeframe_a.InsertColumn(2,resloader,LVCFMT_CENTER,60,0);
	resloader.LoadString(IDS_AUDIODECODE_DTS);
	m_decodeframe_a.InsertColumn(3,resloader,LVCFMT_CENTER,60,0);
	

	return TRUE;
}

void Audiodecode::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}

void Audiodecode::SystemClear(){
	m_decodeframe_a.DeleteAllItems();
}

