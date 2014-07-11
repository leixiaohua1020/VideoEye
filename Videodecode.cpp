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
#include "Videodecode.h"
#include "afxdialogex.h"


// Videodecode 对话框

IMPLEMENT_DYNAMIC(Videodecode, CDialogEx)

Videodecode::Videodecode(CWnd* pParent /*=NULL*/)
	: CDialogEx(Videodecode::IDD, pParent)
{

}

Videodecode::~Videodecode()
{
}

void Videodecode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DECODEFRAME_V, m_decodeframe_v);
}


BEGIN_MESSAGE_MAP(Videodecode, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Videodecode::OnBnClickedCancel)
	ON_NOTIFY ( NM_CUSTOMDRAW,IDC_DECODEFRAME_V, OnCustomdrawMyList )
END_MESSAGE_MAP()


// Videodecode 消息处理程序
BOOL Videodecode::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString resloader;
	resloader.LoadString(IDS_VIDEODECODE);
	SetWindowText(resloader);
	//整行选择；有表格线；表头；单击激活
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	//报表风格；单行选择；高亮显示选择行
	//视频
	m_decodeframe_v.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_decodeframe_v.SetExtendedStyle(dwExStyle);
	
	resloader.LoadString(IDS_VIDEODECODE_DECODEFRAME_V_FRAMENUM);
	m_decodeframe_v.InsertColumn(0,resloader,LVCFMT_CENTER,60,0);
	resloader.LoadString(IDS_VIDEODECODE_DECODEFRAME_V_FRAMETYPE);
	m_decodeframe_v.InsertColumn(1,resloader,LVCFMT_CENTER,60,0);
	resloader.LoadString(IDS_VIDEODECODE_DECODEFRAME_V_ISKEY);
	m_decodeframe_v.InsertColumn(2,resloader,LVCFMT_CENTER,60,0);
	resloader.LoadString(IDS_VIDEODECODE_DECODEFRAME_V_CODEDNUM);
	m_decodeframe_v.InsertColumn(3,resloader,LVCFMT_CENTER,70,0);
	resloader.LoadString(IDS_VIDEODECODE_DECODEFRAME_V_PTS);
	m_decodeframe_v.InsertColumn(4,resloader,LVCFMT_CENTER,60,0);
	return TRUE;
}

void Videodecode::OnBnClickedCancel()
{
	ShowWindow(SW_HIDE);
}

void Videodecode::SystemClear(){
	m_decodeframe_v.DeleteAllItems(); 
}


//ListCtrl加颜色
void Videodecode::OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//This code based on Michael Dunn's excellent article on
	//list control custom draw at http://www.codeproject.com/listctrl/lvcustomdraw.asp

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{

		COLORREF clrNewTextColor, clrNewBkColor;

		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

		CString strTemp = m_decodeframe_v.GetItemText(nItem,1);
		if(strTemp.Compare(_T("I"))==0){
			clrNewTextColor = RGB(0,0,0);		//Set the text
			clrNewBkColor = RGB(255,0,0);		//背景设置成红色
		}
		else if(strTemp.Compare(_T("P"))==0){
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor = RGB(0,255,255);		//背景设置成青色
		}
		else if(strTemp.Compare(_T("B"))==0){
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor = RGB(0,255,0);		//背景设置成绿色
		}else{
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor = RGB(255,255,255);
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;


		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;


	}
}