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
#include "InputList.h"
#include "afxdialogex.h"


// InputList 对话框

IMPLEMENT_DYNAMIC(InputList, CDialogEx)

InputList::InputList(CWnd* pParent /*=NULL*/)
	: CDialogEx(InputList::IDD, pParent)
{

}

InputList::~InputList()
{
}
BOOL InputList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString resloader;
	resloader.LoadString(IDS_INPUTLIST);
	SetWindowText(resloader);

	//CTreeCtrl---------------------------------------------------------------------------------------
	//CRect rect;
	const DWORD dwViewStyle =TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_EDITLABELS|TVS_SHOWSELALWAYS|TVS_DISABLEDRAGDROP;
	//m_urllist.Create(dwViewStyle,rect,this,0);
	m_urllist.ModifyStyle(NULL,dwViewStyle);
	//加载默认播放列表
	//播放列表路径
	char playlist_path[500]={0};
	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)playlist_path,500);//
	//获得exe文家夹路径
	strrchr( playlist_path, '\\')[0]= '\0';//
	printf("%s",playlist_path);
	strcat(playlist_path,"\\InputList.xspf");
	//-----------------
	CString playlist_path1;

#ifdef _UNICODE
	USES_CONVERSION;
	playlist_path1.Format(_T("%s"),A2W(playlist_path));
#else
	playlist_path1.Format(_T("%s"),playlist_path);
#endif

	XSPFImport(playlist_path1);
	RefreshList();

	return TRUE;
}
void InputList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_URLLIST, m_urllist);
}


BEGIN_MESSAGE_MAP(InputList, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN, &InputList::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CANCEL, &InputList::OnBnClickedCancel)
	ON_NOTIFY(NM_DBLCLK, IDC_URLLIST, &InputList::OnDblclkUrllist)
	ON_COMMAND(ID_INPUTLIST_EXPORT, &InputList::OnInputlistExport)
	ON_COMMAND(ID_INPUTLIST_IMPORT, &InputList::OnInputlistImport)
//	ON_COMMAND(ID_INPUTLIST_HELP, &InputList::OnInputlistHelp)
	ON_COMMAND(ID_M3U_IMPORT, &InputList::OnM3uImport)
	ON_COMMAND(ID_M3U_EXPORT, &InputList::OnM3uExport)
END_MESSAGE_MAP()


// InputList 消息处理程序


void InputList::OnBnClickedOpen()
{
		HTREEITEM m_SelNode=m_urllist.GetSelectedItem();//取得当前选中节点	
		CString url;
		if(m_SelNode==NULL){
			CString resloader;
			resloader.LoadString(IDS_MSGBOX_NOSEL);
			AfxMessageBox(resloader);
			return;
		}
		HTREEITEM m_SelNode_p=m_urllist.GetParentItem(m_SelNode);
		HTREEITEM m_root=m_urllist.GetRootItem();
		int url_index=0;
		//如果选中的是“名称”节点（二级节点）
		if(m_root==m_SelNode_p){
			url_index= m_urllist.GetItemData(m_SelNode);
		}else if(m_root==m_urllist.GetParentItem(m_SelNode_p)){
			//三级节点
			url_index= m_urllist.GetItemData(m_SelNode_p);
		}
		url=GetURLByIndex(url_index);
		ShowWindow(SW_HIDE);
	
}


void InputList::OnBnClickedCancel()
{
	ShowWindow(SW_HIDE);
}


void InputList::OnDblclkUrllist(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM m_SelNode=m_urllist.GetSelectedItem();//取得当前选中节点	
	CString url;
	HTREEITEM m_SelNode_p=m_urllist.GetParentItem(m_SelNode);
	int url_index=0;

	//HTREEITEM m_root=m_urllist.GetRootItem();
	
	

	//	//如果选中的是“名称”节点（二级节点）
	//if(m_root==m_SelNode_p){
	//	url_index= m_urllist.GetItemData(m_SelNode);
	//}else if(m_root==m_urllist.GetParentItem(m_SelNode_p)){
	//	//三级节点
	//	url_index= m_urllist.GetItemData(m_SelNode_p);
	//}

		//如果选中的是“名称”节点（二级节点）
	if(m_SelNode_p==0){
		url_index= m_urllist.GetItemData(m_SelNode);
	}else {
		//三级节点
		url_index= m_urllist.GetItemData(m_SelNode_p);
	}


	url=GetURLByIndex(url_index);

	maindlg->m_inputurl.SetWindowText(url);
	*pResult = 0;
}

CString InputList::GetURLByIndex(int data_index){
	if(tracklist.size()==0){
		return NULL;
	}else{
		return tracklist[data_index].location;
	}
}

void InputList::OnInputlistExport()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("XSPF PlayList (*.xspf)|*.xspf|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("xspf"),_T("InputList.xspf"),NULL,lpszfilter);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	XSPFExport(FilePathName);
}
void InputList::OnInputlistImport()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("XSPF PlayList (*.xspf)|*.xspf|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,_T("xspf"),_T("InputList.xspf"),NULL,lpszfilter);//TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) {
		//清空
		SystemClear();
		FilePathName=dlg.GetPathName();
		if(FilePathName.IsEmpty()==FALSE){
			XSPFImport(FilePathName);
			RefreshList();
		}
	}
}

void InputList::XSPFImport(CString filepath)
{
	if(filepath.IsEmpty()==TRUE){
		CString resloader;
		resloader.LoadString(IDS_MSGBOX_NOURL);
		AfxMessageBox(resloader);
		return;
	}


#ifdef _UNICODE
	USES_CONVERSION;
	TiXmlDocument *myDocument = new TiXmlDocument(W2A(filepath));
#else if
	TiXmlDocument *myDocument = new TiXmlDocument(filepath);
#endif

	//创建一个XML的文档对象。
	
	myDocument->LoadFile();

	//获得根元素，即playlist。
	TiXmlElement *RootElement = myDocument->RootElement();

	if(RootElement==NULL){
		return;
	}


	//获得xml声明信息，重点是获得编码信息。如果是utf-8则需要转换
	int utf8_encode=0;
	TiXmlDeclaration *dec=myDocument->FirstChild()->ToDeclaration();
	if(lstrcmpiA(dec->Encoding(),"utf-8")==0){
		utf8_encode=1;
	}

	//输出根元素名称，即输出URLlist。
	//比较
	//if(strcmp(RootElement->Value(),"playlist")==0){
	//strcmp区分大小写。lstrcmpiA不区分大小写
	if(lstrcmpiA(RootElement->Value(),"playlist")==0){
		TiXmlElement *trackListElement;
		int root_ft=1;

		do{
			if(root_ft==1){
				trackListElement=RootElement->FirstChildElement();
				root_ft=0;
			}else{
				trackListElement=trackListElement->NextSiblingElement();
			}

		if(lstrcmpiA(trackListElement->Value(),"trackList")==0){
			//获得第一个URL节点
			TiXmlElement *trackElement,*trackchildElement;
			//是否第一次执行？
			int tracklist_ft=1;
			do{
				if(tracklist_ft==1){
					trackElement= trackListElement->FirstChildElement();
					tracklist_ft=0;
				}else{
					trackElement= trackElement->NextSiblingElement();
				}

					//Track-----------------------------
					Track track;
					//得到Track几个属性值
					int track_ft=1;
					do{
						if(track_ft==1){
							trackchildElement= trackElement->FirstChildElement();
							track_ft=0;
						}else{
							//消除内存泄露
							trackchildElement=trackchildElement->NextSiblingElement();
						}

#ifdef _UNICODE
						//逐一比较
						if(lstrcmpiA(trackchildElement->Value(),"location")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.location.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.location.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"title")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.title.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.title.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"creator")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.creator.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.creator.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"album")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.album.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.album.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"trackNum")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.trackNum.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.trackNum.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"annotation")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.annotation.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.annotation.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"duration")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.duration.Format(_T("%s"),A2W(val_gb));
								free(val_gb);
							}else{
								track.duration.Format(_T("%s"),A2W(trackchildElement->FirstChild()->Value()));
							}
						}
#else
						if(lstrcmpiA(trackchildElement->Value(),"location")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.location.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.location.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"title")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.title.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.title.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"creator")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.creator.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.creator.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"album")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.album.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.album.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"trackNum")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.trackNum.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.trackNum.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"annotation")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.annotation.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.annotation.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}else if(lstrcmpiA(trackchildElement->Value(),"duration")==0){
							if(utf8_encode==1){
								char *val_gb=U2G(trackchildElement->FirstChild()->Value());
								track.duration.Format(_T("%s"),val_gb);
								free(val_gb);
							}else{
								track.duration.Format(_T("%s"),trackchildElement->FirstChild()->Value());
							}
						}
#endif
					}while(trackchildElement->NextSiblingElement()!=NULL);
					
					tracklist.push_back(track);


				}while(trackElement->NextSiblingElement()!=NULL);
			}

		}while(trackListElement->NextSiblingElement()!=NULL);
	}
	//TinyXML：new出了很多对象而不见一个delete？
	//TinyXml用了一个很巧妙的方法来析构每一个结点所对应的对象 ---- 每个结点的析构任务都委托给了它的父亲, 
	//这样只要保证父亲被正确析构, 或者调用了父亲的Clear函数, 它的所有后代都会被正确的析构, 所以对整个文
	//档来说只要TiXmlDocument对象被正确析构, 那就万无一失了, 这棵树会先从叶子销毁, 一直到树根。
	delete myDocument;
}

void InputList::XSPFExport(CString filepath){
	if(filepath.IsEmpty()==TRUE){
		return;
	}

#ifdef _UNICODE
	USES_CONVERSION;
#endif



	TiXmlDocument *myDocument = new TiXmlDocument();
	//xml声明信息
	TiXmlDeclaration *dec=new TiXmlDeclaration("1.0","gb2312","");
	myDocument->LinkEndChild(dec);
	//创建一个根元素并连接。
	TiXmlElement *RootElement = new TiXmlElement("playlist");
	myDocument->LinkEndChild(RootElement);
	TiXmlElement *trackListElement = new TiXmlElement("trackList");
	RootElement->LinkEndChild(trackListElement);

	for(int i=0;i<tracklist.size();i++){
		//创建一个track元素并连接。
		TiXmlElement *trackElement = new TiXmlElement("track");
		trackListElement->LinkEndChild(trackElement);
		//创建location元素、title元素并连接。
		TiXmlElement *locationElement = new TiXmlElement("location");
		TiXmlElement *titleElement = new TiXmlElement("title");

		trackElement->LinkEndChild(locationElement);
		trackElement->LinkEndChild(titleElement);
		//
#ifdef _UNICODE
		TiXmlText *locationContent = new TiXmlText(W2A(tracklist[i].location));
		TiXmlText *titleContent = new TiXmlText(W2A(tracklist[i].title));
#else
		TiXmlText *locationContent = new TiXmlText(tracklist[i].location);
		TiXmlText *titleContent = new TiXmlText(tracklist[i].title);
#endif

		

		locationElement->LinkEndChild(locationContent);
		titleElement->LinkEndChild(titleContent);
	}


#ifdef _UNICODE
	myDocument->SaveFile(W2A(filepath));
#else
	myDocument->SaveFile(filepath);//保存到文件
#endif
	
	//TinyXml用了一个很巧妙的方法来析构每一个结点所对应的对象 ---- 每个结点的析构任务都委托给了它的父亲, 
	//这样只要保证父亲被正确析构, 或者调用了父亲的Clear函数, 它的所有后代都会被正确的析构, 所以对整个文
	//档来说只要TiXmlDocument对象被正确析构, 那就万无一失了, 这棵树会先从叶子销毁, 一直到树根。
	delete myDocument;
}



//解析m3u类型的播放列表
//m3u格式文件每行代表一个文件路径
void InputList::OnM3uImport()
{
	//清空
	SystemClear();
	CString FilePathName;
	LPCTSTR lpszfilter=_T("M3U PlayList (*.m3u;*.m3u8)|*.m3u;*.m3u8|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,_T("m3u"),NULL,NULL,lpszfilter);//TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK){
		FilePathName=dlg.GetPathName();
		M3UImport(FilePathName);
		RefreshList();
	}
}

void InputList::M3UImport(CString filepath)
{
	if(filepath.IsEmpty()==TRUE){
		CString resloader;
		resloader.LoadString(IDS_MSGBOX_NOURL);
		AfxMessageBox(resloader);
	}

#ifdef _UNICODE
	USES_CONVERSION;
	FILE* fp=fopen(W2A(filepath),"r+");
#else
	FILE* fp=fopen(filepath,"r+");
#endif

	char *buffer=(char *)malloc(MAX_URL_LENGTH);
	int i=0;
	char x=NULL;
	while(!feof(fp)){
		//读取一整行
		if((x = getc(fp))!='\n'){
			buffer[i]=x;
			i++;
		}else{
			//读完后存储
			buffer[i]='\0';
			//当一行以#开头的时候，代表该行是注释，不插入
			if(buffer[0]!='#'){
				Track track;
#ifdef _UNICODE
				track.location.Format(_T("%s"),A2W(buffer));
				track.title.Format(_T("%s"),A2W(buffer));
#else
				track.location.Format(_T("%s"),buffer);
				track.title.Format(_T("%s"),buffer);
#endif				
				tracklist.push_back(track);
			}
			i=0;
		}
	}
	free(buffer);
	fclose(fp);

}

void InputList::M3UExport(CString filepath)
{
	if(filepath.IsEmpty()==TRUE){
		return;
	}

#ifdef _UNICODE
	USES_CONVERSION;
	FILE* fp=fopen(W2A(filepath),"wb+");
#else
	FILE* fp=fopen(filepath,"wb+");
#endif

	for(int i=0;i<tracklist.size();i++){
		fprintf(fp,"#%s\n",tracklist[i].title);
		fprintf(fp,"%s\n",tracklist[i].location);
	}
	fclose(fp);
}

void InputList::RefreshList(){

#ifdef _UNICODE
	USES_CONVERSION;
#endif

	HTREEITEM hItem,hSubItem;
	m_urllist.DeleteAllItems();
	//hItem= m_urllist.InsertItem(_T("List"),TVI_ROOT);
	for(int i=0;i<tracklist.size();i++){
		//插入名称
		hSubItem=m_urllist.InsertItem(tracklist[i].title,TVI_ROOT);
		//自定义数据，存储索引值
		m_urllist.SetItemData(hSubItem,i);
		//插入三级目录
		CString text;
		//插入URL（名称和URL不同的时候）
		if(tracklist[i].title.Compare(tracklist[i].location)!=0){
			text.Format(_T("location: %s"),tracklist[i].location);
			m_urllist.InsertItem(text,hSubItem);
		}
		//还包含其他信息的时候
		if(tracklist[i].album.IsEmpty()==FALSE){
			text.Format(_T("album: %s"),tracklist[i].album);
			m_urllist.InsertItem(text,hSubItem);
		}
		if(tracklist[i].creator.IsEmpty()==FALSE){
			text.Format(_T("creator: %s"),tracklist[i].creator);
			m_urllist.InsertItem(text,hSubItem);
		}
		if(tracklist[i].trackNum.IsEmpty()==FALSE){
			text.Format(_T("trackNum: %s"),tracklist[i].trackNum);
			m_urllist.InsertItem(text,hSubItem);
		}
		if(tracklist[i].annotation.IsEmpty()==FALSE){
			text.Format(_T("annotation: %s"),tracklist[i].annotation);
			m_urllist.InsertItem(text,hSubItem);
		}
		if(tracklist[i].duration.IsEmpty()==FALSE){
			text.Format(_T("duration: %s"),tracklist[i].duration);
			m_urllist.InsertItem(text,hSubItem);
		}
	}
	//展开根节点
	//m_urllist.Expand(hItem,TVE_EXPAND);
}

void InputList::SystemClear(){
	tracklist.clear();
	RefreshList();
}

//UTF-8转GB2312
char* InputList::U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}

void InputList::OnM3uExport()
{
	CString FilePathName;
	LPCTSTR lpszfilter=_T("M3U PlayList (*.m3u)|*.m3u|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE,_T("m3u"),_T("InputList.m3u"),NULL,lpszfilter);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) 
		FilePathName=dlg.GetPathName();
	M3UExport(FilePathName);
}
