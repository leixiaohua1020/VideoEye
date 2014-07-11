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
#include "Optplayer.h"
#include "afxdialogex.h"


// Optplayer 对话框

IMPLEMENT_DYNAMIC(Optplayer, CDialogEx)

Optplayer::Optplayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(Optplayer::IDD, pParent)
{

}

Optplayer::~Optplayer()
{
}

void Optplayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPT_PLAYER_GRID, m_optplayergrid);
}


BEGIN_MESSAGE_MAP(Optplayer, CDialogEx)
	ON_STN_CLICKED(IDC_OPT_PLAYER_GRID, &Optplayer::OnClickedOptPlayerGrid)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL Optplayer::OnInitDialog(){
	CDialogEx::OnInitDialog();

	CString resloader;
	resloader.LoadString(IDS_OPTPLAYER);
	SetWindowText(resloader);
	resloader.LoadString(IDS_BTN_OK);
	GetDlgItem(IDOK)->SetWindowText(resloader);
	resloader.LoadString(IDS_BTN_CANCEL);
	GetDlgItem(IDCANCEL)->SetWindowText(resloader);

	m_optplayergrid.EnableDescriptionArea();
	m_optplayergrid.SetVSDotNetLook();
	m_optplayergrid.MarkModifiedProperties();
	//把第一列调整宽一些-----------------------
	HDITEM item; 
	item.cxy=150; 
	item.mask=HDI_WIDTH; 
	m_optplayergrid.GetHeaderCtrl().SetItem(0, &item); 

	resloader.LoadString(IDS_OPTPLAYER_ENABLESIZE);
	enable_size=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_X);
	x=new CMFCPropertyGridProperty(resloader,(_variant_t)640, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_Y);
	y=new CMFCPropertyGridProperty(resloader,(_variant_t)480, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_FS);
	fs=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_AN);
	an=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_VN);
	vn=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLESS);
	enable_ss=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_SS);
	ss=new CMFCPropertyGridProperty(resloader,(_variant_t)20, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLET);
	enable_t=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_T);
	t=new CMFCPropertyGridProperty(resloader,(_variant_t) 20, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_BYTES);
	bytes=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_NODISP);
	nodisp=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLEF);
	enable_f=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_F);
	f=new CMFCPropertyGridProperty(resloader,(_variant_t)1, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLEPIXFMT);
	enable_pix_fmt=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_PIXFMT);
	pix_fmt=new CMFCPropertyGridProperty(resloader,(_variant_t)1, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLEIDCT);
	enable_idct=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_IDCT);
	idct=new CMFCPropertyGridProperty(resloader,(_variant_t)1, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLEEC);
	enable_ec=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_EC);
	ec=new CMFCPropertyGridProperty(resloader,(_variant_t)1, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLESYNC);
	enable_sync=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_SYNC);
	sync=new CMFCPropertyGridProperty(resloader,(_variant_t)"ext", _T(""));
	resloader.LoadString(IDS_OPTPLAYER_AUTOEXIT);
	autoexit=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLELOOP);
	enable_loop=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_LOOP);
	loop=new CMFCPropertyGridProperty(resloader,(_variant_t)10, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_FRAMEDROP);
	framedrop=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_INFBUF);
	infbuf=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLEWINTITLE);
	enable_window_title=new CMFCPropertyGridProperty(resloader,(_variant_t)false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_WINTITLE);
	window_title=new CMFCPropertyGridProperty(resloader,(_variant_t) "Custom", _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLERDFTSPEED);
	enable_rdftspeed=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_RDFTSPEED);
	rdftspeed=new CMFCPropertyGridProperty(resloader,(_variant_t) 100, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLESHOWMODE);
	enable_showmode=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_SHOWMODE);
	showmode=new CMFCPropertyGridProperty(resloader,(_variant_t)"video", _T(""));
	resloader.LoadString(IDS_OPTPLAYER_ENABLECODEC);
	enable_codec=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_OPTPLAYER_CODEC);
	codec=new CMFCPropertyGridProperty(resloader,(_variant_t) 1, _T(""));
	
	m_optplayergrid.AddProperty(enable_size);
	x->EnableSpinControl(TRUE,0,5000);
	m_optplayergrid.AddProperty(x);
	y->EnableSpinControl(TRUE,0,5000);
	m_optplayergrid.AddProperty(y);
	m_optplayergrid.AddProperty(fs);
	m_optplayergrid.AddProperty(an);
	m_optplayergrid.AddProperty(vn);
	
	m_optplayergrid.AddProperty(enable_ss);
	ss->EnableSpinControl(TRUE,0,5000);
	m_optplayergrid.AddProperty(ss);
	m_optplayergrid.AddProperty(enable_t);
	t->EnableSpinControl(TRUE,0,5000);
	m_optplayergrid.AddProperty(t);
	m_optplayergrid.AddProperty(bytes);
	m_optplayergrid.AddProperty(nodisp);
	
	m_optplayergrid.AddProperty(enable_f);
	f->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(f);
	m_optplayergrid.AddProperty(enable_pix_fmt);
	pix_fmt->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(pix_fmt);
	
	m_optplayergrid.AddProperty(enable_idct);
	idct->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(idct);
	m_optplayergrid.AddProperty(enable_ec);
	ec->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(ec);
	m_optplayergrid.AddProperty(enable_sync);
	sync->AddOption(_T("audio"));
	sync->AddOption(_T("video"));
	sync->AddOption(_T("ext"));
	m_optplayergrid.AddProperty(sync);
	m_optplayergrid.AddProperty(autoexit);
	
	m_optplayergrid.AddProperty(enable_loop);
	loop->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(loop);
	m_optplayergrid.AddProperty(framedrop);
	m_optplayergrid.AddProperty(infbuf);
	
	m_optplayergrid.AddProperty(enable_window_title);
	m_optplayergrid.AddProperty(window_title);
	m_optplayergrid.AddProperty(enable_rdftspeed);
	rdftspeed->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(rdftspeed);
	m_optplayergrid.AddProperty(enable_showmode);
	showmode->AddOption(_T("video"));
	showmode->AddOption(_T("waves"));
	showmode->AddOption(_T("rdft"));
	m_optplayergrid.AddProperty(showmode);
	m_optplayergrid.AddProperty(enable_codec);
	codec->EnableSpinControl(TRUE,0,300);
	m_optplayergrid.AddProperty(codec);
	CheckPropertyEnable();
	
	return TRUE;
}
// Optplayer 消息处理程序


void Optplayer::OnClickedOptPlayerGrid()
{
	CheckPropertyEnable();
}

void Optplayer::CheckPropertyEnable(){
	if(enable_size->GetValue()==(_variant_t)false){
		x->Enable(FALSE);
		y->Enable(FALSE);
	}else{
		x->Enable(TRUE);
		y->Enable(TRUE);
	}
	if(enable_ss->GetValue()==(_variant_t)false){
		ss->Enable(FALSE);
	}else{
		ss->Enable(TRUE);
	}
	if(enable_t->GetValue()==(_variant_t)false){
		t->Enable(FALSE);
	}else{
		t->Enable(TRUE);
	}
	if(enable_f->GetValue()==(_variant_t)false){
		f->Enable(FALSE);
	}else{
		f->Enable(TRUE);
	}
	if(enable_pix_fmt->GetValue()==(_variant_t)false){
		pix_fmt->Enable(FALSE);
	}else{
		pix_fmt->Enable(TRUE);
	}
	if(enable_idct->GetValue()==(_variant_t)false){
		idct->Enable(FALSE);
	}else{
		idct->Enable(TRUE);
	}
	if(enable_ec->GetValue()==(_variant_t)false){
		ec->Enable(FALSE);
	}else{
		ec->Enable(TRUE);
	}
	if(enable_sync->GetValue()==(_variant_t)false){
		sync->Enable(FALSE);
	}else{
		sync->Enable(TRUE);
	}
	if(enable_loop->GetValue()==(_variant_t)false){
		loop->Enable(FALSE);
	}else{
		loop->Enable(TRUE);
	}
	if(enable_window_title->GetValue()==(_variant_t)false){
		window_title->Enable(FALSE);
	}else{
		window_title->Enable(TRUE);
	}
	if(enable_rdftspeed->GetValue()==(_variant_t)false){
		rdftspeed->Enable(FALSE);
	}else{
		rdftspeed->Enable(TRUE);
	}
	if(enable_showmode->GetValue()==(_variant_t)false){
		showmode->Enable(FALSE);
	}else{
		showmode->Enable(TRUE);
	}
	if(enable_codec->GetValue()==(_variant_t)false){
		codec->Enable(FALSE);
	}else{
		codec->Enable(TRUE);
	}
}
//生成argv参数
char** Optplayer::generate_opt_argv(){
	//参数数组
	opt_argv.clear();
	CString temp1;
	//参数字符串中有文件名和程序名-----------------
	temp1.Format(_T("dummy.exe"));
	opt_argv.push_back(temp1);
	temp1.Format(_T("dummy.avi"));
	opt_argv.push_back(temp1);
	//------------------------
	if(enable_size->GetValue()==(_variant_t)true){
		temp1.Format(_T("-x"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(x->GetValue());
		opt_argv.push_back(temp1);//将_variant_t类型变量vcount通过函数-bstr-（）转换为cstring类型
		temp1.Format(_T("-y"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(y->GetValue());
		opt_argv.push_back(temp1);
	};
	if(fs->GetValue()==(_variant_t)true){
		temp1.Format(_T("-fs"));
		opt_argv.push_back(temp1);
	}
	if(an->GetValue()==(_variant_t)true){
		temp1.Format(_T("-an"));
		opt_argv.push_back(temp1);
	}
	if(vn->GetValue()==(_variant_t)true){
		temp1.Format(_T("-vn"));
		opt_argv.push_back(temp1);
	}
	if(enable_ss->GetValue()==(_variant_t)true){
		temp1.Format(_T("-ss"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(ss->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_t->GetValue()==(_variant_t)true){
		temp1.Format(_T("-t"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(t->GetValue());
		opt_argv.push_back(temp1);
	}

	if(bytes->GetValue()==(_variant_t)true){
		temp1.Format(_T("-bytes"));
		opt_argv.push_back(temp1);
	}
	if(nodisp->GetValue()==(_variant_t)true){
		temp1.Format(_T("-nodisp"));
		opt_argv.push_back(temp1);
	}
	if(enable_f->GetValue()==(_variant_t)true){
		temp1.Format(_T("-f"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(f->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_pix_fmt->GetValue()==(_variant_t)true){
		temp1.Format(_T("-pix_fmt"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(pix_fmt->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_idct->GetValue()==(_variant_t)true){
		temp1.Format(_T("-idct"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(idct->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_ec->GetValue()==(_variant_t)true){
		temp1.Format(_T("-ec"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(ec->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_sync->GetValue()==(_variant_t)true){
		temp1.Format(_T("-sync"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(sync->GetValue());
		opt_argv.push_back(temp1);
	}
	if(autoexit->GetValue()==(_variant_t)true){
		temp1.Format(_T("-autoexit"));
		opt_argv.push_back(temp1);
	}

	if(enable_loop->GetValue()==(_variant_t)true){
		temp1.Format(_T("-loop"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(loop->GetValue());
		opt_argv.push_back(temp1);
	}
	if(framedrop->GetValue()==(_variant_t)true){
		temp1.Format(_T("-framedrop"));
		opt_argv.push_back(temp1);
	}
	if(infbuf->GetValue()==(_variant_t)true){
		temp1.Format(_T("-infbuf"));
		opt_argv.push_back(temp1);
	}
	if(enable_window_title->GetValue()==(_variant_t)true){
		temp1.Format(_T("-window_title"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(window_title->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_rdftspeed->GetValue()==(_variant_t)true){
		temp1.Format(_T("-rdftspeed"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(rdftspeed->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_showmode->GetValue()==(_variant_t)true){
		temp1.Format(_T("-showmode"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(showmode->GetValue());
		opt_argv.push_back(temp1);
	}
	if(enable_codec->GetValue()==(_variant_t)true){
		temp1.Format(_T("-codec"));
		opt_argv.push_back(temp1);
		temp1=(char *)_bstr_t(codec->GetValue());
		opt_argv.push_back(temp1);
	}
	//将Vecter<CString>转换成char**;
	int i;
	//分配内存-------------
	char** opt_argv_array=(char **)malloc(200);
	for(i=0;i<opt_argv.size();i++){
		opt_argv_array[i]=(LPSTR)(LPCTSTR)opt_argv[i];
	}
	return opt_argv_array;
}
//生成argc参数
int Optplayer::generate_opt_argc(){
	counter=0;
	//参数中包含文件名和程序名---------
	counter++;
	counter++;
	//--------
	if(enable_size->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	};
	if(fs->GetValue()==(_variant_t)true){
		counter++;
	}
	if(an->GetValue()==(_variant_t)true){
		counter++;
	}
	if(vn->GetValue()==(_variant_t)true){
		counter++;
	}
	if(enable_ss->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_t->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}

	if(bytes->GetValue()==(_variant_t)true){
		counter++;
	}
	if(nodisp->GetValue()==(_variant_t)true){
		counter++;
	}
	if(enable_f->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_pix_fmt->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_idct->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_ec->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_sync->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(autoexit->GetValue()==(_variant_t)true){
		counter++;
	}

	if(enable_loop->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(framedrop->GetValue()==(_variant_t)true){
		counter++;
	}
	if(infbuf->GetValue()==(_variant_t)true){
		counter++;
	}
	if(enable_window_title->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_rdftspeed->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_showmode->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	if(enable_codec->GetValue()==(_variant_t)true){
		counter++;
		counter++;
	}
	return counter;
}

//释放argv参数
void Optplayer::free_opt_argv(char** charlist,int charlist_size){
	for(int i=0;i<charlist_size;i++){
		free(charlist[i]);
	}
	free(charlist);
}
//
//
void Optplayer::OnDestroy()
{
	
	CDialogEx::OnDestroy();
}
