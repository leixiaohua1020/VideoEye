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
#include "Dfanalysis.h"
#include "afxdialogex.h"


// Dfanalysis 对话框

IMPLEMENT_DYNAMIC(Dfanalysis, CDialogEx)

	Dfanalysis::Dfanalysis(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dfanalysis::IDD, pParent)
{

	m_dfanalysisnum16x16 = 0;
	m_dfanalysisnum16x8 = 0;
	m_dfanalysisnum8x16 = 0;
	m_dfanalysisnum8x8 = 0;
	m_dfanalysisnumavgq = 0;
	m_dfanalysisnumintra16x16 = 0;
	m_dfanalysisnumintra4x4 = 0;
	m_dfanalysisnumskip = 0;
	m_dfanalysisnummaxq = 0;
	m_dfanalysisnumminq = 0;
	m_dfanalysisnuml0 = 0;
	m_dfanalysisnuml1 = 0;
	m_dfanalysisautointerframenum = 0;
}

Dfanalysis::~Dfanalysis()
{
}

void Dfanalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DFANALYSIS_METHOD, m_dfanalysismethod);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_HEIGHT, m_dfanalysismbheight);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_SUM, m_dfanalysismbsum);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_WIDTH, m_dfanalysismbwidth);
	DDX_Control(pDX, IDC_DFANALYSIS_MV_SUBSAMPLE, m_dfanalysismvsubsample);
	DDX_Control(pDX, IDC_DFANALYSIS_OPTION, m_dfanalysisoption);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_16X16, m_dfanalysisnum16x16);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_16X8, m_dfanalysisnum16x8);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_8X16, m_dfanalysisnum8x16);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_8X8, m_dfanalysisnum8x8);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_AVGQ, m_dfanalysisnumavgq);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_INTRA16X16, m_dfanalysisnumintra16x16);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_INTRA4X4, m_dfanalysisnumintra4x4);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_SKIP, m_dfanalysisnumskip);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_MAXQ, m_dfanalysisnummaxq);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_MINQ, m_dfanalysisnumminq);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_L0, m_dfanalysisnuml0);
	DDX_Text(pDX, IDC_DFANALYSIS_NUM_L1, m_dfanalysisnuml1);
	//  DDX_Control(pDX, IDC_DFANALYSIS_MB_PACKETSIZE, m_dfanalysismbpacketsize);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_PICTTYPE, m_dfanalysismbpictype);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_PTIME, m_dfanalysismbptime);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_PTS, m_dfanalysismbpts);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_REF, m_dfanalysismbref);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_FRAMEINDEX, m_dfanalysismbframeindex);
	DDX_Control(pDX, IDC_DFANALYSIS_MB_QTYPE, m_dfanalysismbqtype);
	DDX_Text(pDX, IDC_DFANALYSIS_AUTO_INTERFRAMENUM, m_dfanalysisautointerframenum);
	DDX_Control(pDX, IDC_DFANALYSIS_AUTO, m_dfanalysisauto);
	DDX_Control(pDX, IDC_DFANALYSIS_OUTPICFOLDER, m_dfanalysisoutpicfolder);
	DDX_Control(pDX, IDC_DFANALYSIS_OUTPICFOLDER_URL, m_dfanalysisoutpicfolderurl);
	DDX_Control(pDX, IDC_DFANALYSIS_OUTDATAFOLDER, m_dfanalysisoutdatafolder);
	DDX_Control(pDX, IDC_DFANALYSIS_OUTDATAFOLDER_URL, m_dfanalysisoutdatafolderurl);
}


BEGIN_MESSAGE_MAP(Dfanalysis, CDialogEx)
	ON_BN_CLICKED(IDC_DFANALYSIS_OPEN, &Dfanalysis::OnBnClickedDfanalysisOpen)
	ON_BN_CLICKED(IDC_DFANALYSIS_AUTO, &Dfanalysis::OnBnClickedDfanalysisAuto)
	ON_EN_KILLFOCUS(IDC_DFANALYSIS_AUTO_INTERFRAMENUM, &Dfanalysis::OnKillfocusDfanalysisAutoInterframenum)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &Dfanalysis::OnBnClickedCancel)
//	ON_WM_CLOSE()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_DFANALYSIS_OUTPICFOLDER, &Dfanalysis::OnClickedDfanalysisOutpicfolder)
ON_BN_CLICKED(IDC_DFANALYSIS_OUTDATAFOLDER, &Dfanalysis::OnClickedDfanalysisOutdatafolder)
END_MESSAGE_MAP()


// Dfanalysis 消息处理程序
BOOL Dfanalysis::OnInitDialog(){
	CDialogEx::OnInitDialog();
	//默认不开启自动分析
	m_dfanalysisautointerframenum=20;
	UpdateData(FALSE);
	GetDlgItem(IDC_DFANALYSIS_AUTO_INTERFRAMENUM)->EnableWindow(FALSE);
	m_dfanalysisauto.SetCheck(0);
	//-----------------
	//加载StringTable
	CString resloader;
	resloader.LoadString(IDS_DFANALYSIS_PARAMETER_QP);
	m_dfanalysismethod.InsertString(0,resloader);
	resloader.LoadString(IDS_DFANALYSIS_PARAMETER_MBTYPE);
	m_dfanalysismethod.InsertString(1,resloader);
	resloader.LoadString(IDS_DFANALYSIS_PARAMETER_MV0);
	m_dfanalysismethod.InsertString(2,resloader);
	resloader.LoadString(IDS_DFANALYSIS_PARAMETER_MV1);
	m_dfanalysismethod.InsertString(3,resloader);
	resloader.LoadString(IDS_DFANALYSIS_PARAMETER_REF0);
	m_dfanalysismethod.InsertString(4,resloader);
	resloader.LoadString(IDS_DFANALYSIS_PARAMETER_REF1);
	m_dfanalysismethod.InsertString(5,resloader);
	m_dfanalysismethod.SetCurSel(0);
	//-----------------
	m_dfanalysisoption.EnableDescriptionArea();
	m_dfanalysisoption.SetVSDotNetLook();
	m_dfanalysisoption.MarkModifiedProperties();
	m_dfanalysisoption.EnableHeaderCtrl(FALSE);
	//把第一列调整宽一些-----------------------
	HDITEM item; 
	item.cxy=120; 
	item.mask=HDI_WIDTH; 
	//m_dfanalysisoption.GetHeaderCtrl().SetItem(0, new HDITEM(item)); 
	m_dfanalysisoption.GetHeaderCtrl().SetItem(0, &item); 
	resloader.LoadString(IDS_DFANALYSIS_OPT_GLOBAL);
	prop_global=new CMFCPropertyGridProperty(resloader);
	resloader.LoadString(IDS_DFANALYSIS_OPT_Q);
	prop_q=new CMFCPropertyGridProperty(resloader);
	resloader.LoadString(IDS_DFANALYSIS_OPT_MBTYPE);
	prop_mb_type=new CMFCPropertyGridProperty(resloader);
	resloader.LoadString(IDS_DFANALYSIS_OPT_MV0);
	prop_mv0=new CMFCPropertyGridProperty(resloader);
	resloader.LoadString(IDS_DFANALYSIS_OPT_MV1);
	prop_mv1=new CMFCPropertyGridProperty(resloader);
	resloader.LoadString(IDS_DFANALYSIS_OPT_GLOBAL_MBBORDER);
	prop_global_showmbedge=new CMFCPropertyGridProperty(resloader,(_variant_t) true, _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_GLOBAL_MBBORDER_COLOR);
	prop_global_showmbedge_color=new CMFCPropertyGridColorProperty(resloader,RGB(0, 0, 0), NULL,_T(""));
	//字体
	//LOGFONT lf;
	//CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	//font->GetLogFont(&lf);
	//resloader.LoadString(IDS_DFANALYSIS_OPT_GLOBAL_FONT);
	//prop_global_font=new CMFCPropertyGridFontProperty(resloader, lf, CF_EFFECTS | CF_SCREENFONTS, "画图时的字体");

	resloader.LoadString(IDS_DFANALYSIS_OPT_GLOBAL_WINSIZE);
	prop_global_winsize=new CMFCPropertyGridProperty(resloader,(_variant_t) 120, _T(""));
	prop_global_winsize->EnableSpinControl(TRUE,80,200);

	resloader.LoadString(IDS_DFANALYSIS_OPT_Q_SHOWVAL);
	prop_q_shownum=new CMFCPropertyGridProperty(resloader,(_variant_t) true, _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_Q_SHOWCOLOR);
	prop_q_showcolor=new CMFCPropertyGridProperty(resloader, (_variant_t) false,  _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MBTYPE_SHOWSUBMB);
	prop_mb_type_showsubmb=new CMFCPropertyGridProperty(resloader,(_variant_t) true, _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MBTYPE_SHOWCOLOR);
	prop_mb_type_showcolor=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MBTYPE_SHOWSKIP);
	prop_mb_type_showskip=new CMFCPropertyGridProperty(resloader,(_variant_t) true, _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MBTYPE_SHOWLIST);
	prop_mb_type_showlist=new CMFCPropertyGridProperty(resloader,(_variant_t) false, _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MV0_COLOR);
	prop_mv0_colortype=new CMFCPropertyGridColorProperty(resloader,RGB(255, 0, 0), NULL, _T(""));
	prop_mv0_colortype->EnableOtherButton(_T("Other..."));
	prop_mv0_colortype->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MV0_STYLE);
	prop_mv0_linetype=new CMFCPropertyGridProperty(resloader,(_variant_t) "line", _T(""));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MV1_COLOR);
	prop_mv1_colortype=new CMFCPropertyGridColorProperty(resloader,RGB(0, 0, 255), NULL, _T(""));
	prop_mv1_colortype->EnableOtherButton(_T("Other..."));
	prop_mv1_colortype->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	resloader.LoadString(IDS_DFANALYSIS_OPT_MV1_STYLE);
	prop_mv1_linetype=new CMFCPropertyGridProperty(resloader,(_variant_t) "line", _T(""));
	prop_global->AddSubItem(prop_global_showmbedge);
	prop_global->AddSubItem(prop_global_showmbedge_color);
	//prop_global->AddSubItem(prop_global_font);
	prop_global->AddSubItem(prop_global_winsize);
	prop_q->AddSubItem(prop_q_shownum);
	prop_q->AddSubItem(prop_q_showcolor);
	prop_mb_type->AddSubItem(prop_mb_type_showsubmb);
	prop_mb_type->AddSubItem(prop_mb_type_showcolor);
	prop_mb_type->AddSubItem(prop_mb_type_showskip);
	prop_mb_type->AddSubItem(prop_mb_type_showlist);
	prop_mv0->AddSubItem(prop_mv0_colortype);
	prop_mv0->AddSubItem(prop_mv0_linetype);
	prop_mv0->AddOption(_T("line"));
	prop_mv0->AddOption(_T("arrow"));
	prop_mv0->AllowEdit(FALSE);
	prop_mv1->AddSubItem(prop_mv1_colortype);
	prop_mv1->AddSubItem(prop_mv1_linetype);
	prop_mv1->AddOption(_T("line"));
	prop_mv1->AddOption(_T("arrow"));
	prop_mv1->AllowEdit(FALSE);
	m_dfanalysisoption.AddProperty(prop_global);
	m_dfanalysisoption.AddProperty(prop_q);
	m_dfanalysisoption.AddProperty(prop_mb_type);
	m_dfanalysisoption.AddProperty(prop_mv0);
	m_dfanalysisoption.AddProperty(prop_mv1);
	//------------------
	m_dfanalysisoutpicfolderurl.EnableFolderBrowseButton();
	m_dfanalysisoutdatafolderurl.EnableFolderBrowseButton();
	
	TCHAR realpathpic[MAX_URL_LENGTH]={0};   	
	TCHAR realpathdata[MAX_URL_LENGTH]={0};   	
	

	//生成文件路径
	GetCurrentDirectory(MAX_URL_LENGTH,realpathpic);
	GetCurrentDirectory(MAX_URL_LENGTH,realpathdata);

	CString realpathpic1(realpathpic);
	CString realpathdata1(realpathdata);

	realpathpic1.Append(_T("\\dfanalysispic"));
	realpathdata1.Append(_T("\\dfanalysisdata"));


	m_dfanalysisoutpicfolderurl.SetWindowText(realpathpic1);
	m_dfanalysisoutpicfolderurl.EnableWindow(FALSE);

	m_dfanalysisoutdatafolderurl.SetWindowText(realpathdata1);
	m_dfanalysisoutdatafolderurl.EnableWindow(FALSE);

	//------------------
	picdlg=new Dfanalysispic;
	picdlg->Create(IDD_DFANALYSIS_PIC,NULL);
	picdlg->dfanalysisdlg=this;
	//------------------
	dffinish=FALSE;
	//------------------
	return TRUE;
}

void Dfanalysis::GetOption(){
	prop_global_showmbedge_val=prop_global_showmbedge->GetValue().boolVal;
	prop_q_shownum_val=prop_q_shownum->GetValue().boolVal;
	prop_q_showcolor_val=prop_q_showcolor->GetValue().boolVal;
	prop_mb_type_showsubmb_val=prop_mb_type_showsubmb->GetValue().boolVal;
	prop_mb_type_showcolor_val=prop_mb_type_showcolor->GetValue().boolVal;
	prop_mb_type_showskip_val=prop_mb_type_showskip->GetValue().boolVal;
	prop_mb_type_showlist_val=prop_mb_type_showlist->GetValue().boolVal;
	prop_mv0_colortype_val=prop_mv0_colortype->GetColor();
	prop_mv1_colortype_val=prop_mv1_colortype->GetColor();

	prop_global_showmbedge_color_val=prop_global_showmbedge_color->GetColor();
	prop_global_winsize_val=(float)(prop_global_winsize->GetValue().intVal)/100.0;
	/*
	LOGFONT lf;
	lf=*prop_global_font->GetLogFont();
	if(prop_global_font_val!=NULL){
		prop_global_font_val=new CFont;
	}
	prop_global_font_val->CreateFontIndirect(&lf);
	*/
	//字符串比较，稍后实现
	//prop_mv0_linetype;
	//prop_mv1_linetype;
}

void Dfanalysis::OnBnClickedDfanalysisOpen(){
	try{
		DrawPic();
	}catch(...){
		CString resloader;
		resloader.LoadString(IDS_MSGBOX_ERROR);
		AfxMessageBox(resloader);
		return;
	}
}

void Dfanalysis::DrawPic(){
	dffinish=FALSE;
	//本窗口重画
	//Invalidate();
	//如果没有播放，就不分析
	if(maindlg->is_playing==0){
		CString resloader;
		resloader.LoadString(IDS_MSGBOX_NOPLAYING);
		AfxMessageBox(resloader);
		return ;
	}
	//显示窗口---
	picdlg->ShowWindow(TRUE);
		//选项----
	GetOption();
	//设置参数------------------
	CString temp;
	temp.Format(_T("%d"),mb_width);
	m_dfanalysismbwidth.SetWindowText(temp);
	temp.Format(_T("%d"),mb_sum/mb_width);
	m_dfanalysismbheight.SetWindowText(temp);
	temp.Format(_T("%d"),mb_sum);
	m_dfanalysismbsum.SetWindowText(temp);
	//每个宏块包含的运动矢量
	int mv_sample_log2_temp= 4 - motion_subsample_log2;
	temp.Format(_T("%d"),1<<(mv_sample_log2_temp*2));
	m_dfanalysismvsubsample.SetWindowText(temp);
	//后添加的几个参数---------------------
	temp.Format(_T("%d"),frame_index);
	m_dfanalysismbframeindex.SetWindowText(temp);
	temp.Format(_T("%ld"),pts);
	m_dfanalysismbpts.SetWindowText(temp);
	temp.Format(_T("%.3fs"),ptime);
	m_dfanalysismbptime.SetWindowText(temp);
	switch(pict_type){
	case AV_PICTURE_TYPE_I:
		temp.Format(_T("I"));
		m_dfanalysismbpictype.SetWindowText(temp);
		break;
	case AV_PICTURE_TYPE_B:
		temp.Format(_T("B"));
		m_dfanalysismbpictype.SetWindowText(temp);
		break;
	case AV_PICTURE_TYPE_P:
		temp.Format(_T("P"));
		m_dfanalysismbpictype.SetWindowText(temp);
		break;
	default:
		temp.Format(_T("Other"));
		m_dfanalysismbpictype.SetWindowText(temp);
		break;
	}
	temp.Format(_T("%d"),refs);
	m_dfanalysismbref.SetWindowText(temp);
	switch(qscale_type){
	case FF_QSCALE_TYPE_MPEG1:
		temp.Format(_T("MPEG1"));break;
	case FF_QSCALE_TYPE_MPEG2:
		temp.Format(_T("MPEG2"));break;
	case FF_QSCALE_TYPE_H264:
		temp.Format(_T("H.264"));break;
	case FF_QSCALE_TYPE_VP56:
		temp.Format(_T("VP5,VP6"));break;
	default:
		temp.Format(_T("Unknown"));break;
	}
	m_dfanalysismbqtype.SetWindowText(temp);
	
	CRect rect;
	CWnd *dcd=NULL;
	HWND phWnd=NULL;
	//dcd = picdlg->GetDlgItem(IDD_DFANALYSIS_PIC); // 获取控件句柄
	//晕。。。没想到竟然可以强制类型转换
	dcd=(CWnd *)picdlg;

	CDC *pDC = dcd->GetDC();  // 获取控件设备
	dcd->Invalidate();
	//这一句会触发cdc的OnPaint()
	dcd->UpdateWindow();
	//窗口设置大点，看着方便
	picdlg->SetWindowPos(NULL,0,0,(int)(width*prop_global_winsize_val),(int)(height*prop_global_winsize_val),SWP_NOMOVE);
	dcd->GetClientRect(&rect);
	//加载画面
	DrawFrame();

	pDC->SetWindowExt(rect.Width(), rect.Height());     // 设置窗口范围
	//保证绘图不画到框框外面
	CRgn rgn;
	rgn.CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);
	pDC->SelectClipRgn(&rgn,RGN_AND);
	//统计一下--------------------------
	int total_intra4x4=0;
	int total_intra16x16=0;
	int total_16x16=0;
	int total_16x8=0;
	int total_8x16=0;
	int total_8x8=0;
	int total_skip=0;
	int total_l0=0;
	int total_l1=0;
	int avgq=0;
	int totalq=0;
	int maxq=0;
	int minq=100;
	//输出数据----------------------------------
	CString datastat;

	//画网格图
	//step_w,step_h网格的宽和高
	float step_h=(float)rect.Height()/(float)(mb_sum/mb_stride); 
	//改：最后一列数值总为0，先不输出
	float step_w=(float)rect.Width()/(float)(mb_stride-1); 
	//x,y代表了屏幕坐标
	float i,x,y,j;
	//输出时候用到的变量
	int qval,qvalt,mbtype,refval,refvalt;
	//存放运动矢量（x,y）
	short mv[2];
	CString qval_s,refval_s;
	//画刷-------------------
	pBrush=new CBrush();
	//循环输出
	for(j=0;j<(mb_sum/mb_stride);j++){
		//for(i=0;i<mb_stride;i++){
		//最右侧一行总为0，先不输出
		for(i=0;i<mb_width;i++){
			//生成一个Rect
			CRect rect(i*step_w,j*step_h,(i+1)*step_w,(j+1)*step_h);
			//宏块个数
			int num=j*mb_stride+i;
			//运动矢量个数
			//q值
			switch(m_dfanalysismethod.GetCurSel()){
			case DRAW_Q:{
				qval=qscale_table[num];
				qval_s.Format(_T("%d"),qval);
				//输出数据
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("%d,"),qval);
				
				//等比拉伸一下
				//qp取值范围0-51，颜色取值范围0-255
				if(prop_q_showcolor_val!=FALSE){
					qvalt=qval*255/51;
					//会导致内存泄露
					//pDC->FillRect(rect,new CBrush(RGB(qvalt,qvalt,qvalt)));
					//先创建一个，然后每次Create一个画笔，还要记得DeleteObject
					pBrush->CreateSolidBrush(RGB(qvalt,qvalt,qvalt));
					pDC->FillRect(rect,pBrush);
					pBrush->DeleteObject();
				}
				//输出字符
				if(prop_q_shownum_val!=FALSE){
					//背景色透明
					//if(prop_global_font_val!=NULL){
					//	pDC->SelectObject(prop_global_font_val);
					//}
					pDC->SetBkMode(TRANSPARENT);
					pDC->TextOut(rect.left+2,rect.top+2,qval_s);
				}
				//在指定的矩形内画出字符,(没看出有什么区别)
				//pDC->DrawText(qval_s,2,rect,DT_CENTER);
				//统计量-------
				if(maxq<qval){
					maxq=qval;
				}
				//边缘上总有一个q=0的宏块
				if(minq>qval&&qval!=0){
					minq=qval;
				}
				totalq=totalq+qval;
				//-------
				break;
						}
			case DRAW_MB_TYPE:{
				//防止图片，音频等没有此类信息
				if(mb_type==NULL){
					return;
				}
				CPen pen;
				pen.CreatePen(PS_SOLID,0,prop_global_showmbedge_color_val);
				pDC->SelectObject(pen);

				mbtype=mb_type[num];
				if(mbtype&MB_TYPE_INTRA4x4){
					//输出数据
					if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
						datastat.AppendFormat(_T("intra4x4,"));
					

					//4x4宏块
					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(255,0,0));
						pDC->FillRect(rect,pBrush);
						pBrush->DeleteObject();
					}
					if(prop_mb_type_showsubmb_val!=FALSE){
						//画3条横线和竖线
						
						int m;
						//竖线
						for(m=1;m<4;m++){
							pDC->MoveTo(rect.left+m*rect.Width()/4,rect.top);
							pDC->LineTo(rect.left+m*rect.Width()/4,rect.bottom);
						}
						//横线
						for(m=1;m<4;m++){
							pDC->MoveTo(rect.left,rect.top+m*rect.Height()/4);
							pDC->LineTo(rect.right,rect.top+m*rect.Height()/4);
						}
					}
					//-----
					total_intra4x4++;
					//-----
				}
				if(mbtype&MB_TYPE_INTRA16x16){

					//输出数据
					if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
						datastat.AppendFormat(_T("intra16x16,"));
					


					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(128,0,0));
						pDC->FillRect(rect,pBrush);
						pBrush->DeleteObject();
					}
					//-----
					total_intra16x16++;
					//-----
				}
				if(mbtype&MB_TYPE_INTRA_PCM){
					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(166,0,0));
						pDC->FillRect(rect,pBrush);
						pBrush->DeleteObject();
					}
				}
				if(mbtype&MB_TYPE_16x16){

					//输出数据
					if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
						datastat.AppendFormat(_T("16x16,"));
					

					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(255,99,0));
						pDC->FillRect(rect,pBrush);//棕黄
						pBrush->DeleteObject();
					}
					//-----
					total_16x16++;
					//-----
				}
				if(mbtype&MB_TYPE_16x8){

					//输出数据
					if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
						datastat.AppendFormat(_T("16x8,"));
					

					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(0,99,0));
						pDC->FillRect(rect,pBrush);
						pBrush->DeleteObject();
					}
					if(prop_mb_type_showsubmb_val!=FALSE){
						//画1条横线
						int m;
						//横线
						for(m=1;m<2;m++){
							pDC->MoveTo(rect.left,rect.top+m*rect.Height()/2);
							pDC->LineTo(rect.right,rect.top+m*rect.Height()/2);
						}
					}
					//-----
					total_16x8++;
					//-----
				}
				if(mbtype&MB_TYPE_8x16){

					//输出数据
					if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
						datastat.AppendFormat(_T("8x16,"));
					


					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(255,99,255));
						pDC->FillRect(rect,pBrush);
						pBrush->DeleteObject();
					}
					if(prop_mb_type_showsubmb_val!=FALSE){
						//画1条竖线
						int m;
						//竖线
						for(m=1;m<2;m++){
							pDC->MoveTo(rect.left+m*rect.Width()/2,rect.top);
							pDC->LineTo(rect.left+m*rect.Width()/2,rect.bottom);
						}
					}
					//-----
					total_8x16++;
					//-----
				}
				if(mbtype&MB_TYPE_8x8){

					//输出数据
					if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
						datastat.AppendFormat(_T("8x8,"));
					

					if(prop_mb_type_showcolor_val!=FALSE){
						pBrush->CreateSolidBrush(RGB(0,99,255));
						pDC->FillRect(rect,pBrush);
						pBrush->DeleteObject();
					}
					if(prop_mb_type_showsubmb_val!=FALSE){
						//画1条横线和竖线
						int m;
						//竖线
						for(m=1;m<2;m++){
							pDC->MoveTo(rect.left+m*rect.Width()/2,rect.top);
							pDC->LineTo(rect.left+m*rect.Width()/2,rect.bottom);
						}
						//横线
						for(m=1;m<2;m++){
							pDC->MoveTo(rect.left,rect.top+m*rect.Height()/2);
							pDC->LineTo(rect.right,rect.top+m*rect.Height()/2);
						}
					}
					//-----
					total_8x8++;
					//-----
				}

				if(mbtype&MB_TYPE_SKIP){
					//“跳过”宏块
					if(prop_mb_type_showskip_val!=FALSE){
						//背景色透明
						pDC->SetBkMode(TRANSPARENT);
						//输出字符
						pDC->TextOut(rect.left+2,rect.top+2,_T("s"));
					}
					//-----
					total_skip++;
					//-----
				}
				//是否使用list0或者list1进行预测
				//画斜线
				if(mbtype&MB_TYPE_L0&&(prop_mb_type_showlist_val!=FALSE)){
					pDC->SetBkMode(TRANSPARENT);
					pDC->MoveTo(rect.left,rect.top);
					pDC->LineTo(rect.right,rect.bottom);
					total_l0++;
				}
				if(mbtype&MB_TYPE_L1&&(prop_mb_type_showlist_val!=FALSE)){
					pDC->SetBkMode(TRANSPARENT);
					pDC->MoveTo(rect.left,rect.bottom);
					pDC->LineTo(rect.right,rect.top);
					total_l1++;
				}

				/*
				//没弄懂~
				
				
				//宏块其他特性
				if(mbtype&MB_TYPE_INTERLACED){
				pDC->FillRect(rect,new CBrush(RGB(0,255,0)));}
				if(mbtype&MB_TYPE_DIRECT2){pDC->FillRect(rect,new CBrush(RGB(0,200,0)));
				}
				if(mbtype&MB_TYPE_ACPRED){
				pDC->FillRect(rect,new CBrush(RGB(0,166,0)));}
				if(mbtype&MB_TYPE_GMC){pDC->FillRect(rect,new CBrush(RGB(0,133,0)));
				}
				if(mbtype&MB_TYPE_QUANT){
				pDC->FillRect(rect,new CBrush(RGB(0,0,66)));
				}
				if(mbtype&MB_TYPE_CBP){
				pDC->FillRect(rect,new CBrush(RGB(0,0,33)));
				}
				*/

				break;
							  }
			case DRAW_MV0:{
				//防止图片，音频，MPEG2等没有此类信息
				if(motion_val0==NULL){
					CString resloader;
					resloader.LoadString(IDS_MSGBOX_NODATA);
					AfxMessageBox(resloader);
					return;
				}
				//注意:FFMPEG中运动矢量是单独存放的，与宏块并没有直接的关系
				//但是在此处，我们需要通过宏块单元来显示
				//例如8x8划分的运动矢量与宏块的关系：
				//-------------------------
				//|			 |			  |
				//|mv[x]	 |mv[x+1]	  |
				//-------------------------
				//|			 |			  |
				//|mv[x+line]|mv[x+line+1]|
				//-------------------------
				//因此要费不少周折= =
				//运动适量加箭头-------------
				//ARROWSTRUCT a;
				//a.bFill=FALSE;
				//a.nWidth=5;
				//a.fTheta=60;
				//-------------
				int mv_sample_log2= 4 - motion_subsample_log2;
				//一行MV的个数
				//FIX:目前发现H.264的mv_stride和MPEG4，RMVB不一样
				//只能区别处理
				int mv_stride=0;
				if(codec_id==AV_CODEC_ID_H264){
					mv_stride=(mb_width << mv_sample_log2);
				}else{
					mv_stride=(mb_width << mv_sample_log2)+1;
				}
				//一排宏块包含的MV个数
				int mv_mb_stride= mv_stride<<mv_sample_log2;
				//一个宏块一行或一列MV个数
				int mv_sample=1<<mv_sample_log2;
				//当前宏块第一个MV索引值
				int mv_num=j*mv_mb_stride+i*mv_sample;
				//画运动矢量
				CPen pen;
				//加载颜色
				//pen.CreatePen(PS_SOLID,0,RGB(255,0,0));//设为红色
				pen.CreatePen(PS_SOLID,0,prop_mv0_colortype_val);
				pDC->SelectObject(pen);
				int m,n;
				//输出数据[宏块边界]
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("[,"));
				
				//按行和列画出m代表列，n代表行
				for(m=0;m<mv_sample;m++){
					for(n=0;n<mv_sample;n++){
						mv[0]=motion_val0[mv_num+n+m*mv_stride][0];
						mv[1]=motion_val0[mv_num+n+m*mv_stride][1];
						pDC->MoveTo(rect.left+n*rect.Width()/mv_sample,rect.top+m*rect.Height()/mv_sample);
						pDC->LineTo(rect.left+n*rect.Width()/mv_sample+mv[0],rect.top+m*rect.Height()/mv_sample+mv[1]);
						//画出来的是箭头而不是直线
						//ArrowTo1(pDC->m_hDC,rect.left+n*rect.Width()/mv_sample+mv[0],rect.top+m*rect.Height()/mv_sample+mv[1],&a);
						//输出数据
						if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
							datastat.AppendFormat(_T("(%d-%d),"),mv[0],mv[1]);
						
					}
				}
				//输出数据[宏块边界]
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("],"));
				
				break;
						  }
			case DRAW_MV1:{
				//防止图片，音频，MPEG2等没有此类信息
				if(motion_val1==NULL){
					CString resloader;
					resloader.LoadString(IDS_MSGBOX_NODATA);
					AfxMessageBox(resloader);
					return;
				}
				//因此要费不少周折= =
				int mv_sample_log2= 4 - motion_subsample_log2;
				//一行MV的个数
				int mv_stride= (mb_width << mv_sample_log2);
				//一排宏块包含的MV个数
				int mv_mb_stride= mv_stride<<mv_sample_log2;
				//一个宏块一行或一列MV个数
				int mv_sample=1<<mv_sample_log2;
				//当前宏块第一个MV索引值
				int mv_num=j*mv_mb_stride+i*mv_sample;
				//画运动矢量
				CPen pen;
				//pen.CreatePen(PS_SOLID,0,RGB(0,0,255));//设为蓝色
				pen.CreatePen(PS_SOLID,0,prop_mv1_colortype_val);
				pDC->SelectObject(pen);
				int m,n;

				//输出数据[宏块边界]
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("[,"));
				

				//按行和列画出m代表列，n代表行
				for(m=0;m<mv_sample;m++){
					for(n=0;n<mv_sample;n++){
						mv[0]=motion_val1[mv_num+n+m*mv_stride][0];
						mv[1]=motion_val1[mv_num+n+m*mv_stride][1];
						pDC->MoveTo(rect.left+n*rect.Width()/mv_sample,rect.top+m*rect.Height()/mv_sample);
						pDC->LineTo(rect.left+n*rect.Width()/mv_sample+mv[0],rect.top+m*rect.Height()/mv_sample+mv[1]);

						//输出数据
						if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
							datastat.AppendFormat(_T("(%d-%d),"),mv[0],mv[1]);
						
					}
				}

				//输出数据[宏块边界]
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("],"));
				

				break;
						  }
			case DRAW_REFINDEX0:{
				//防止图片，音频，MPEG2等没有此类信息
				if(ref_index0==NULL){
					CString resloader;
					resloader.LoadString(IDS_MSGBOX_NODATA);
					AfxMessageBox(resloader);
					return;
				}
				//ref_index根据源码判断，每个宏块有4个
				//此处只提取第一个
				//如果提取四个的话，屏幕会显示不下的= =
				refval=ref_index0[num*4];
				refval_s.Format(_T("%d"),refval);

				//输出数据
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("%d,"),refval);

				//等比拉伸一下
				//假设参考帧最大值是16帧
				//拉伸，平移
				//refvalt=refval*255/16;
				//获取参考帧的最大值refs
				refvalt=refval*128/refs;
				refvalt=refvalt+128;
				pBrush->CreateSolidBrush(RGB(refvalt,refvalt,refvalt));
				pDC->FillRect(rect,pBrush);
				pBrush->DeleteObject();
				//显示
				pDC->SetBkMode(TRANSPARENT);
				pDC->TextOut(rect.left+2,rect.top+2,refval_s);
				break;
						  }
			case DRAW_REFINDEX1:{
				//防止图片，音频，MPEG2等没有此类信息
				if(ref_index1==NULL){
					CString resloader;
					resloader.LoadString(IDS_MSGBOX_NODATA);
					AfxMessageBox(resloader);
					return;
				}
				//ref_index根据源码判断，每个宏块有4个
				//此处只提取第一个
				//如果提取四个的话，屏幕会显示不下的= =
				refval=ref_index1[num*4];
				refval_s.Format(_T("%d"),refval);

				//输出数据
				if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
					datastat.AppendFormat(_T("%d,"),refval);

				//等比拉伸一下
				//假设参考帧最大值是16帧
				//拉伸，平移
				//refvalt=refval*255/16;
				//获取参考帧的最大值refs
				refvalt=refval*128/refs;
				refvalt=refvalt+128;
				pBrush->CreateSolidBrush(RGB(refvalt,refvalt,refvalt));
				pDC->FillRect(rect,pBrush);
				pBrush->DeleteObject();
				//显示
				pDC->SetBkMode(TRANSPARENT);
				pDC->TextOut(rect.left+2,rect.top+2,refval_s);
				break;
								}
			}
		}
		//数据输出，统计完一行宏块
		if(m_dfanalysisoutdatafolder.GetCheck()==TRUE)
			datastat.AppendFormat(_T("\n"));
		
	}
	//输出统计量----------------
	if(m_dfanalysismethod.GetCurSel()==DRAW_MB_TYPE){
		m_dfanalysisnumintra4x4=total_intra4x4;
		m_dfanalysisnumintra16x16=total_intra16x16;
		m_dfanalysisnum16x16=total_16x16;
		m_dfanalysisnum16x8=total_16x8;
		m_dfanalysisnum8x16=total_8x16;
		m_dfanalysisnum8x8=total_8x8;
		m_dfanalysisnumskip=total_skip;
		m_dfanalysisnuml0=total_l0;
		m_dfanalysisnuml1=total_l1;
		//其他线程中调用，不支持UpdateData
		if(m_dfanalysisauto.GetCheck()!=1)
			UpdateData(FALSE);
	}
	//---------------------------
	if(m_dfanalysismethod.GetCurSel()==DRAW_Q){
		m_dfanalysisnumavgq=totalq/((mb_sum/mb_stride)*mb_width);
		m_dfanalysisnummaxq=maxq;
		m_dfanalysisnumminq=minq;
		//其他线程中调用，不支持UpdateData
		if(m_dfanalysisauto.GetCheck()!=1)
		UpdateData(FALSE);
	}
	//----------------
	//把宏块画成网格图
	if(prop_global_showmbedge_val!=FALSE){
		CPen pen_default;
		//pen_default.CreatePen(PS_SOLID,0,RGB(0,0,0));//设为黑色
		pen_default.CreatePen(PS_SOLID,0,prop_global_showmbedge_color_val);
		pDC->SelectObject(pen_default);
		//画竖线
		x=0;
		y=0;
		for(i=0;i<mb_stride;i++){
			x=x+step_w;
			pDC->MoveTo(x, 0);
			pDC->LineTo(x,rect.Height());
		}
		//划横线
		x=0;
		y=0;
		for(j=0;j<(mb_sum/mb_stride);j++){
			y=y+step_h;
			pDC->MoveTo(0, y);
			pDC->LineTo(rect.Width(),y);
		}
	}
	delete pBrush;
	//-----------

	//------------------
	ReleaseDC(pDC); 
	//------
	dffinish=TRUE;
	//最后结果要保存成BMP，以备万一
	hpic=CopyDCToBitmap(picdlg->GetDC()->GetSafeHdc(),rect);
	//保存图像
	if(m_dfanalysisoutpicfolder.GetCheck()==TRUE){
		CString folder_url,pic_name;
		m_dfanalysisoutpicfolderurl.GetWindowText(folder_url);
		//检查文件夹路径是否存在
		CreateDirectory(folder_url,NULL);

		switch(m_dfanalysismethod.GetCurSel()){
		case DRAW_Q:pic_name.Format(_T("qp_%d.bmp"),frame_index);break;
		case DRAW_MB_TYPE:pic_name.Format(_T("mbtype_%d.bmp"),frame_index);break;
		case DRAW_MV0:pic_name.Format(_T("mv0_%d.bmp"),frame_index);break;
		case DRAW_MV1:pic_name.Format(_T("mv1_%d.bmp"),frame_index);break;
		case DRAW_REFINDEX0:pic_name.Format(_T("refindex_%d.bmp"),frame_index);break;
		case DRAW_REFINDEX1:pic_name.Format(_T("refindex_%d.bmp"),frame_index);break;
		}

		folder_url.AppendFormat(_T("\\%s"),pic_name);
		SaveBmp(hpic, folder_url);
	}

	//保存数据
	if(m_dfanalysisoutdatafolder.GetCheck()==TRUE){
		CString folder_url,data_name;
		m_dfanalysisoutdatafolderurl.GetWindowText(folder_url);
		//检查文件夹路径是否存在
		CreateDirectory(folder_url,NULL);

		switch(m_dfanalysismethod.GetCurSel()){
		case DRAW_Q:data_name.Format(_T("qp_%d.csv"),frame_index);break;
		case DRAW_MB_TYPE:data_name.Format(_T("mbtype_%d.csv"),frame_index);break;
		case DRAW_MV0:data_name.Format(_T("mv0_%d.csv"),frame_index);break;
		case DRAW_MV1:data_name.Format(_T("mv1_%d.csv"),frame_index);break;
		case DRAW_REFINDEX0:data_name.Format(_T("refindex_%d.csv"),frame_index);break;
		case DRAW_REFINDEX1:data_name.Format(_T("refindex_%d.csv"),frame_index);break;
		}

		folder_url.AppendFormat(_T("\\%s"),data_name);
		CFile mFile(folder_url,CFile::modeReadWrite|CFile::modeCreate);
		mFile.Write(datastat,datastat.GetLength()*sizeof(TCHAR));
		mFile.Close();
	}
}



void Dfanalysis::ArrowTo1(HDC hDC, int x, int y, ARROWSTRUCT *pA) {

	POINT ptTo = {x, y};

	ArrowTo(hDC, &ptTo, pA);
}

void Dfanalysis::ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA) {

	POINT pFrom;
	POINT pBase;
	POINT aptPoly[3];
	float vecLine[2];
	float vecLeft[2];
	float fLength;
	float th;
	float ta;

	// get from point
	MoveToEx(hDC, 0, 0, &pFrom);

	// set to point
	aptPoly[0].x = lpTo->x;
	aptPoly[0].y = lpTo->y;

	// build the line vector
	vecLine[0] = (float) aptPoly[0].x - pFrom.x;
	vecLine[1] = (float) aptPoly[0].y - pFrom.y;

	// build the arrow base vector - normal to the line
	vecLeft[0] = -vecLine[1];
	vecLeft[1] = vecLine[0];

	// setup length parameters
	fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
	th = pA->nWidth / (2.0f * fLength);
	ta = pA->nWidth / (2.0f * (tanf(pA->fTheta) / 2.0f) * fLength);

	// find the base of the arrow
	pBase.x = (int) (aptPoly[0].x + -ta * vecLine[0]);
	pBase.y = (int) (aptPoly[0].y + -ta * vecLine[1]);

	// build the points on the sides of the arrow
	aptPoly[1].x = (int) (pBase.x + th * vecLeft[0]);
	aptPoly[1].y = (int) (pBase.y + th * vecLeft[1]);
	aptPoly[2].x = (int) (pBase.x + -th * vecLeft[0]);
	aptPoly[2].y = (int) (pBase.y + -th * vecLeft[1]);

	MoveToEx(hDC, pFrom.x, pFrom.y, NULL);

	// draw we're fillin'...
	if(pA->bFill) {
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		Polygon(hDC, aptPoly, 3);
	}

	// ... or even jes chillin'...
	else {
		LineTo(hDC, pBase.x, pBase.y);
		LineTo(hDC, aptPoly[1].x, aptPoly[1].y);
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		LineTo(hDC, aptPoly[2].x, aptPoly[2].y);
		LineTo(hDC, pBase.x, pBase.y);
		MoveToEx(hDC, aptPoly[0].x, aptPoly[0].y, NULL);
	}
}


void Dfanalysis::OnBnClickedDfanalysisAuto()
{
	if(m_dfanalysisauto.GetCheck()==1){
		CString resloader;
		GetDlgItem(IDC_DFANALYSIS_AUTO_INTERFRAMENUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_DFANALYSIS_AUTO_OK)->EnableWindow(TRUE);
	}else{
		GetDlgItem(IDC_DFANALYSIS_AUTO_INTERFRAMENUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_DFANALYSIS_AUTO_OK)->EnableWindow(FALSE);
	}
}


void Dfanalysis::OnKillfocusDfanalysisAutoInterframenum()
{
	UpdateData(TRUE);
}


void Dfanalysis::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//画图不能添加到OnInitDialog否则无效
	//而应该添加到OnPaint函数中
	DrawSample();
}




void Dfanalysis::DrawSample(){
	//-----------------
	CDC *pDC=NULL;
	CRect rect;
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_INTRA4X4)->GetDC();
	//4x4宏块
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_INTRA4X4)->GetClientRect(&rect);
	pBrush=new CBrush();
	pBrush->CreateSolidBrush(RGB(255,0,0));
	pDC->FillRect(rect,pBrush);
	pBrush->DeleteObject();
	//画3条横线和竖线
	int m;
	//竖线
	for(m=1;m<4;m++){
		pDC->MoveTo(rect.left+m*rect.Width()/4,rect.top);
		pDC->LineTo(rect.left+m*rect.Width()/4,rect.bottom);
	}
	//横线
	for(m=1;m<4;m++){
		pDC->MoveTo(rect.left,rect.top+m*rect.Height()/4);
		pDC->LineTo(rect.right,rect.top+m*rect.Height()/4);
	}
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_INTRA16X16)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_INTRA16X16)->GetClientRect(&rect);
	pBrush->CreateSolidBrush(RGB(128,0,0));
	pDC->FillRect(rect,pBrush);
	pBrush->DeleteObject();
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_16X16)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_16X16)->GetClientRect(&rect);
	pBrush->CreateSolidBrush(RGB(255,99,0));
	pDC->FillRect(rect,pBrush);//棕黄
	pBrush->DeleteObject();
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_16X8)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_16X8)->GetClientRect(&rect);
	pBrush->CreateSolidBrush(RGB(0,99,0));
	pDC->FillRect(rect,pBrush);
	pBrush->DeleteObject();

	//画1条横线
	//横线
	for(m=1;m<2;m++){
		pDC->MoveTo(rect.left,rect.top+m*rect.Height()/2);
		pDC->LineTo(rect.right,rect.top+m*rect.Height()/2);
	}
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_8X16)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_8X16)->GetClientRect(&rect);
	pBrush->CreateSolidBrush(RGB(255,99,255));
	pDC->FillRect(rect,pBrush);
	pBrush->DeleteObject();

	//画1条竖线
	//竖线
	for(m=1;m<2;m++){
		pDC->MoveTo(rect.left+m*rect.Width()/2,rect.top);
		pDC->LineTo(rect.left+m*rect.Width()/2,rect.bottom);
	}
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_8X8)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_8X8)->GetClientRect(&rect);
	pBrush->CreateSolidBrush(RGB(0,99,255));
	pDC->FillRect(rect,pBrush);
	pBrush->DeleteObject();

	//画1条横线和竖线
	//竖线
	for(m=1;m<2;m++){
		pDC->MoveTo(rect.left+m*rect.Width()/2,rect.top);
		pDC->LineTo(rect.left+m*rect.Width()/2,rect.bottom);
	}
	//横线
	for(m=1;m<2;m++){
		pDC->MoveTo(rect.left,rect.top+m*rect.Height()/2);
		pDC->LineTo(rect.right,rect.top+m*rect.Height()/2);
	}
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_SKIP)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_SKIP)->GetClientRect(&rect);
	//背景色透明
	pDC->SetBkMode(TRANSPARENT);
	//输出字符
	pDC->TextOut(rect.left+2,rect.top+2,_T("s"));
	//画线-------
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_L0)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_L0)->GetClientRect(&rect);
	//斜线
	pDC->MoveTo(rect.left,rect.top);
	pDC->LineTo(rect.right,rect.bottom);
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_L1)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_L1)->GetClientRect(&rect);
	//斜线
	pDC->MoveTo(rect.left,rect.bottom);
	pDC->LineTo(rect.right,rect.top);
	//填充渐变颜色----------
	//CDC和HDC区别
	//CDC是MFC的DC的一个类 
	//HDC是DC的句柄,API中的一个类似指针的数据类型.
	//CDC等设备上下分类,都含有一个类的成员变量:m_nHdc;即HDC类型的句柄. 
	pDC=GetDlgItem(IDC_DFANALYSIS_SAMPLE_Q)->GetDC();
	GetDlgItem(IDC_DFANALYSIS_SAMPLE_Q)->GetClientRect(&rect);
	HDC hDC = pDC->m_hDC;
	//颜色结构----
	//本处是白色到黑色
	TRIVERTEX rcVertex[2];
	rcVertex[0].x=rect.left;
	rcVertex[0].y=rect.top;
	rcVertex[0].Red=255<<8; // color values from 0x0000 to 0xff00 !!!!
	rcVertex[0].Green=255<<8;
	rcVertex[0].Blue=255<<8;
	rcVertex[0].Alpha=0x0000;
	rcVertex[1].x=rect.right; 
	rcVertex[1].y=rect.bottom;
	rcVertex[1].Red=0;
	rcVertex[1].Green=0;
	rcVertex[1].Blue=0;
	rcVertex[1].Alpha=0;
	//颜色结构TRIVERTEX与图像方框的对应关系--------
	GRADIENT_RECT rect1;
	rect1.UpperLeft=0;
	rect1.LowerRight=1;

	//画渐变的函数
	GradientFill(hDC,rcVertex,2,&rect1,1,GRADIENT_FILL_RECT_V);
	//----
	delete(pBrush);
	ReleaseDC(pDC); 
}

void Dfanalysis::DrawFrame(){
	//先将解码后的数据转换成RGB格式的，以方便显示
	AVFrame	*pFrameYUV=NULL;
	pFrameYUV=avcodec_alloc_frame();
	uint8_t *out_buffer=NULL;
	struct SwsContext *img_convert_ctx=NULL;
	out_buffer=new uint8_t[avpicture_get_size(PIX_FMT_BGR24, width, height)];
	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_BGR24, width, height);
	img_convert_ctx = sws_getContext(width, height, pix_fmt, width, height, PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL); 
	sws_scale(img_convert_ctx, (const uint8_t* const*)data, linesize, 0, height, pFrameYUV->data, pFrameYUV->linesize);
	sws_freeContext(img_convert_ctx);


	//----------------------------------
	CRect rect;
	CWnd *dcd=NULL;
	HWND phWnd=NULL;
	//dcd = picdlg->GetDlgItem(IDD_DFANALYSIS_PIC); // 获取控件句柄
	//晕。。。没想到竟然可以强制类型转换
	dcd=(CWnd *)picdlg;

	CDC *pDC = dcd->GetDC();  // 获取控件设备
	dcd->GetClientRect(&rect);
	HDC m_hdc=pDC->GetSafeHdc();

	pDC->SetWindowExt(rect.Width(), rect.Height());     // 设置窗口范围
	//BMP文件头
	BITMAPINFO *m_bmphdr=NULL;
	DWORD dwBmpHdr = sizeof(BITMAPINFO);
	m_bmphdr = new BITMAPINFO[dwBmpHdr];
	m_bmphdr->bmiHeader.biBitCount = 24;
	m_bmphdr->bmiHeader.biClrImportant = 0;
	m_bmphdr->bmiHeader.biSize = dwBmpHdr;
	m_bmphdr->bmiHeader.biSizeImage = 0;
	m_bmphdr->bmiHeader.biWidth = width;
	//注意BMP在y方向是反着存储的，一次必须设置一个负值，才能使图像正着显示出来
	m_bmphdr->bmiHeader.biHeight = -height;
	m_bmphdr->bmiHeader.biXPelsPerMeter = 0;
	m_bmphdr->bmiHeader.biYPelsPerMeter = 0;
	m_bmphdr->bmiHeader.biClrUsed = 0;
	m_bmphdr->bmiHeader.biPlanes = 1;
	m_bmphdr->bmiHeader.biCompression = BI_RGB;
	//将RGB数据画在控件上
	//图像数据是反的？Why？
	int nResult = ::StretchDIBits(m_hdc,
		0,0,
		rect.Width(),//rc.right - rc.left,
		rect.Height(),//rc.top,
		0, 0,
		width, height,
		pFrameYUV->data[0],
		m_bmphdr,
		DIB_RGB_COLORS,
		SRCCOPY);

	free(m_bmphdr);
	free(out_buffer);
	av_free(pFrameYUV);
}

void Dfanalysis::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_dfanalysisauto.SetCheck(0);
	ShowWindow(FALSE);
}

HBITMAP Dfanalysis::CopyDCToBitmap(HDC hScrDC, LPRECT lpRect)
{
	if(hScrDC==NULL || lpRect==NULL || IsRectEmpty(lpRect)){
		AfxMessageBox(_T("Parameter Error"));
		return NULL;
	}

	HDC hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP    hBitmap,hOldBitmap;   
	// 位图句柄
	int  nX, nY, nX2, nY2;      
	// 选定区域坐标
	int  nWidth, nHeight;      
	// 位图宽度和高度
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	//为指定设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 创建一个与指定设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	StretchBlt(hMemDC,0,0,nWidth,nHeight,hScrDC,nX,nY,nWidth,nHeight,SRCCOPY);
	//BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄

	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//清除 

	DeleteDC(hMemDC);
	DeleteObject(hOldBitmap);
	// 返回位图句柄
	return hBitmap;
}

BOOL Dfanalysis::SaveBmp(HBITMAP hBitmap, CString FileName) 
{ 
	HDC hDC; 
	//当前分辨率下每象素所占字节数 
	int iBits; 
	//位图中每象素所占字节数 
	WORD wBitCount; 
	//定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数 
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0; 
	//位图属性结构 
	BITMAP Bitmap; 
	//位图文件头结构 
	BITMAPFILEHEADER bmfHdr; 
	//位图信息头结构 
	BITMAPINFOHEADER bi; 
	//指向位图信息头结构 
	LPBITMAPINFOHEADER lpbi; 
	//定义文件，分配内存句柄，调色板句柄 
	HANDLE fh, hDib, hPal,hOldPal=NULL; 

	//计算位图文件每个像素所占字节数 
	hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL); 
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
	DeleteDC(hDC); 
	if (iBits <= 1) wBitCount = 1; 
	else if (iBits <= 4) wBitCount = 4; 
	else if (iBits <= 8) wBitCount = 8; 
	else wBitCount = 24; 

	GetObject( hBitmap, sizeof( Bitmap ), ( LPSTR )&Bitmap ); 
	bi.biSize = sizeof( BITMAPINFOHEADER ); 
	bi.biWidth = Bitmap.bmWidth; 
	bi.biHeight = Bitmap.bmHeight; 
	bi.biPlanes = 1; 
	bi.biBitCount = wBitCount; 
	bi.biCompression = BI_RGB; 
	bi.biSizeImage = 0; 
	bi.biXPelsPerMeter = 0; 
	bi.biYPelsPerMeter = 0; 
	bi.biClrImportant = 0; 
	bi.biClrUsed = 0; 

	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight; 

	//为位图内容分配内存 
	hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 

	// 处理调色板 
	hPal = GetStockObject(DEFAULT_PALETTE); 
	if (hPal) 
	{ 
		hDC = ::GetDC(NULL); 
		//hDC = m_pDc->GetSafeHdc(); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	} 
	// 获取该调色板下新的像素值 
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS); 

	//恢复调色板 
	if (hOldPal) 
	{ 
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 


	//创建位图文件 
	fh = CreateFile(FileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 

	if (fh == INVALID_HANDLE_VALUE) return FALSE; 

	// 设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize; 
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
	// 写入位图文件头 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 
	// 写入位图文件其余内容 
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL); 
	//清除 
	GlobalUnlock(hDib); 
	GlobalFree(hDib); 
	CloseHandle(fh); 

	return TRUE; 
} 



void Dfanalysis::OnDestroy()
{
	delete picdlg;
	CDialogEx::OnDestroy();
}


void Dfanalysis::OnClickedDfanalysisOutpicfolder()
{
	if(m_dfanalysisoutpicfolder.GetCheck()==FALSE){
		m_dfanalysisoutpicfolderurl.EnableWindow(FALSE);
	}else{
		m_dfanalysisoutpicfolderurl.EnableWindow(TRUE);
	}
}


void Dfanalysis::OnClickedDfanalysisOutdatafolder()
{
	if(m_dfanalysisoutdatafolder.GetCheck()==FALSE){
		m_dfanalysisoutdatafolderurl.EnableWindow(FALSE);
	}else{
		m_dfanalysisoutdatafolderurl.EnableWindow(TRUE);
	}
}
