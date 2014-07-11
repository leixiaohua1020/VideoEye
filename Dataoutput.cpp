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
#include "Dataoutput.h"
#include "afxdialogex.h"


// Dataoutput 对话框

IMPLEMENT_DYNAMIC(Dataoutput, CDialogEx)

Dataoutput::Dataoutput(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dataoutput::IDD, pParent)
{

}

Dataoutput::~Dataoutput()
{
}

void Dataoutput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUT_DIR_M_A, m_outdirma);
	DDX_Control(pDX, IDC_OUT_DIR_M_O, m_outdirmo);
	DDX_Control(pDX, IDC_OUT_DIR_M_V, m_outdirmv);
	DDX_Control(pDX, IDC_OUT_DIR_R_U, m_outdirru);
	DDX_Control(pDX, IDC_OUT_DIR_R_V, m_outdirrv);
	DDX_Control(pDX, IDC_OUT_DIR_R_Y, m_outdirry);
	DDX_Control(pDX, IDC_OUT_DIR_R_YUV, m_outdirryuv);
	DDX_Control(pDX, IDC_OUT_CHECK_M_A, m_outcheckma);
	DDX_Control(pDX, IDC_OUT_CHECK_M_O, m_outcheckmo);
	DDX_Control(pDX, IDC_OUT_CHECK_M_V, m_outcheckmv);
	DDX_Control(pDX, IDC_OUT_CHECK_R_U, m_outcheckru);
	DDX_Control(pDX, IDC_OUT_CHECK_R_V, m_outcheckrv);
	DDX_Control(pDX, IDC_OUT_CHECK_R_Y, m_outcheckry);
	DDX_Control(pDX, IDC_OUT_CHECK_R_YUV, m_outcheckryuv);
	DDX_Control(pDX, IDC_OUT_CHECK_R_PCM, m_outcheckrpcm);
	DDX_Control(pDX, IDC_OUT_DIR_R_PCM, m_outdirrpcm);
	DDX_Control(pDX, IDC_OUT_CHECK_M_A_AAC, m_outcheckmaaac);
	DDX_Control(pDX, IDC_OUT_CHECK_M_V_H264, m_outcheckmvh264);
	DDX_Control(pDX, IDC_OUT_DIR_M_A_AAC, m_outdirmaaac);
	DDX_Control(pDX, IDC_OUT_DIR_M_V_H264, m_outdirmvh264);
}


BEGIN_MESSAGE_MAP(Dataoutput, CDialogEx)
	ON_BN_CLICKED(IDC_OUT_DIR_M_V_D, &Dataoutput::OnBnClickedOutDirMVD)
	ON_BN_CLICKED(IDC_OUT_DIR_M_A_D, &Dataoutput::OnBnClickedOutDirMAD)
	ON_BN_CLICKED(IDC_OUT_DIR_M_O_D, &Dataoutput::OnBnClickedOutDirMOD)
	ON_BN_CLICKED(IDC_OUT_DIR_R_YUV_D, &Dataoutput::OnBnClickedOutDirRYuvD)
	ON_BN_CLICKED(IDC_OUT_DIR_R_Y_D, &Dataoutput::OnBnClickedOutDirRYD)
	ON_BN_CLICKED(IDC_OUT_DIR_R_U_D, &Dataoutput::OnBnClickedOutDirRUD)
	ON_BN_CLICKED(IDC_OUT_DIR_R_V_D, &Dataoutput::OnBnClickedOutDirRVD)
	ON_BN_CLICKED(IDC_OUT_CHECK_M_V, &Dataoutput::OnBnClickedOutCheckMV)
	ON_BN_CLICKED(IDC_OUT_DIR_R_PCM_D, &Dataoutput::OnBnClickedOutDirRPcmD)
	ON_BN_CLICKED(IDC_OUT_DIR_M_V_H264_D, &Dataoutput::OnBnClickedOutDirMVH264D)
	ON_BN_CLICKED(IDC_OUT_DIR_M_A_AAC_D, &Dataoutput::OnBnClickedOutDirMAAacD)
END_MESSAGE_MAP()


// Dataoutput 消息处理程序
BOOL Dataoutput::OnInitDialog(){
	CDialogEx::OnInitDialog();
	m_outcheckma.SetCheck(0);
	m_outcheckmv.SetCheck(0);
	m_outcheckmo.SetCheck(0);
	m_outcheckryuv.SetCheck(0);
	m_outcheckry.SetCheck(0);
	m_outcheckru.SetCheck(0);
	m_outcheckrv.SetCheck(0);
	m_outcheckmvh264.SetCheck(0);
	m_outcheckmaaac.SetCheck(0);
	//-------------
	TCHAR realpath[MAX_URL_LENGTH]={0};   
	//生成文件路径
	GetCurrentDirectory(MAX_URL_LENGTH,realpath);
	CString outdirma,outdirmv,outdirmo,outdirryuv,outdirry,outdirru,outdirrv,outdirrpcm,outdirmvh264,outdirmaaac;
	//-----------------

	outdirma.Format(_T("%s\\output"),realpath);
	outdirmv.Format(_T("%s\\output"),realpath);
	outdirmo.Format(_T("%s\\output"),realpath);
	outdirryuv.Format(_T("%s\\output.yuv"),realpath);
	outdirry.Format(_T("%s\\output.y"),realpath);
	outdirru.Format(_T("%s\\output.u"),realpath);
	outdirrv.Format(_T("%s\\output.v"),realpath);
	outdirrpcm.Format(_T("%s\\output.pcm"),realpath);
	outdirmvh264.Format(_T("%s\\output.264"),realpath);
	outdirmaaac.Format(_T("%s\\output.aac"),realpath);


	m_outdirma.SetWindowText(outdirma);
	m_outdirmv.SetWindowText(outdirmv);
	m_outdirmo.SetWindowText(outdirmo);
	m_outdirryuv.SetWindowText(outdirryuv);
	m_outdirry.SetWindowText(outdirry);
	m_outdirru.SetWindowText(outdirru);
	m_outdirrv.SetWindowText(outdirrv);
	m_outdirrpcm.SetWindowText(outdirrpcm);
	m_outdirmvh264.SetWindowText(outdirmvh264);
	m_outdirmaaac.SetWindowText(outdirmaaac);
	return TRUE;
}

void Dataoutput::OnBnClickedOutDirMVD()
{
	CString FilePathName;
	CFileDialog dlg(FALSE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirmv.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirMAD()
{
	CString FilePathName;
	CFileDialog dlg(FALSE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirma.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirMOD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("YUV (*.yuv;*.y;*.u;*.v)|*.yuv;*.y;*.u;*.v|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("yuv"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirmo.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirRYuvD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("YUV (*.yuv;*.y;*.u;*.v)|*.yuv;*.y;*.u;*.v|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("yuv"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirryuv.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirRYD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("YUV (*.yuv;*.y;*.u;*.v)|*.yuv;*.y;*.u;*.v|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("y"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirry.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirRUD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("YUV (*.yuv;*.y;*.u;*.v)|*.yuv;*.y;*.u;*.v|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("u"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirru.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirRVD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("YUV (*.yuv;*.y;*.u;*.v)|*.yuv;*.y;*.u;*.v|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("v"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirrv.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutCheckMV()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Dataoutput::OnBnClickedOutDirRPcmD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("PCM (*.pcm)|*.pcm|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("pcm"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirrpcm.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirMVH264D()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("H.264 (*.264)|*.264|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("264"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirmvh264.SetWindowText(FilePathName);
}


void Dataoutput::OnBnClickedOutDirMAAacD()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("AAC (*.aac)|*.aac|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("aac"),_T("output"),NULL,lpszfilter);
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	if(FilePathName.IsEmpty()==FALSE)
		m_outdirmaaac.SetWindowText(FilePathName);
}
