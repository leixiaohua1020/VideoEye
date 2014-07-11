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
#include "Assistantmediainfo.h"
#include "afxdialogex.h"
//更改命名空间-----------------
using namespace MediaInfoDLL;
// Assistantmediainfo 对话框

IMPLEMENT_DYNAMIC(Assistantmediainfo, CDialogEx)

Assistantmediainfo::Assistantmediainfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(Assistantmediainfo::IDD, pParent)
{

	//  m_mediainfodatasource = 0;
}

Assistantmediainfo::~Assistantmediainfo()
{
}

void Assistantmediainfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MEDIAINFO_DISPLAY, m_mediainfodisplay);
}


BEGIN_MESSAGE_MAP(Assistantmediainfo, CDialogEx)
//	ON_WM_SHOWWINDOW()
	ON_COMMAND(IDCANCEL, &Assistantmediainfo::OnIdcancel)
END_MESSAGE_MAP()


// Assistantmediainfo 消息处理程序
BOOL Assistantmediainfo::OnInitDialog(){
	CDialogEx::OnInitDialog();
	maindlg->m_inputurl.GetWindowText(fileurl);
	mediainfo();
	m_mediainfodisplay.SetWindowText(To_Display);
	return TRUE;
}

BOOL Assistantmediainfo::mediainfo()
{
	//Information about MediaInfo
	MediaInfo MI;
	To_Display.Format(_T(""));
	MI.Option(__T("Info_Version"), __T("0.7.13;MediaInfoDLL_Example_MSVC;0.7.13")).c_str();

	//To_Display += __T("\r\n\r\nInfo_Parameters\r\n");
	//To_Display += MI.Option(__T("Info_Parameters")).c_str();

	//To_Display += __T("\r\n\r\nInfo_Codecs\r\n");
	//To_Display += MI.Option(__T("Info_Codecs")).c_str();
	MI.Open(fileurl.GetBuffer());

	MI.Option(__T("Complete"));
	To_Display += MI.Inform().c_str();

	//To_Display += __T("\r\n\r\nInform with Complete=true\r\n");
	//MI.Option(__T("Complete"), __T("1"));
	//To_Display += MI.Inform().c_str();
	MI.Close();

	return 0;
}





void Assistantmediainfo::OnIdcancel()
{
	CDialogEx::OnCancel();
	DestroyWindow();
	delete this;
}



