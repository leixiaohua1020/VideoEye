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
#include "Rawanalysis.h"
#include "afxdialogex.h"


// Rawanalysis 对话框

IMPLEMENT_DYNAMIC(Rawanalysis, CDialogEx)

Rawanalysis::Rawanalysis(CWnd* pParent /*=NULL*/)
	: CDialogEx(Rawanalysis::IDD, pParent)
{

	m_rawanalysismethod = 0;
	m_rawanalysisautointerframenum = 0;
	m_rawanalysiscolorhbin = 0;
	m_rawanalysiscolorsbin = 0;
	m_rawanalysiscontourthres = 0;
	m_rawanalysiscannythres1 = 0;
	m_rawanalysiscannythres2 = 0;
	m_rawanalysisfacexmlurl = _T("");
}

Rawanalysis::~Rawanalysis()
{
}

void Rawanalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RAWANALYSIS_METHOD, m_rawanalysismethod);
	DDX_Text(pDX, IDC_RAWANALYSIS_AUTO_INTERFRAMENUM, m_rawanalysisautointerframenum);
	DDX_Control(pDX, IDC_RAWANALYSIS_AUTO, m_rawanalysisauto);
	DDX_Control(pDX, IDC_RAWANALYSIS_OUTPICFOLDER, m_rawanalysisoutpicfolder);
	DDX_Control(pDX, IDC_RAWANALYSIS_OUTPICFOLDER_URL, m_rawanalysisoutpicfolderurl);
	DDX_Text(pDX, IDC_RAWANALYSIS_COLOR_HBIN, m_rawanalysiscolorhbin);
	DDX_Text(pDX, IDC_RAWANALYSIS_COLOR_SBIN, m_rawanalysiscolorsbin);
	DDX_Text(pDX, IDC_RAWANALYSIS_CONTOUR_THRES, m_rawanalysiscontourthres);
	DDX_Text(pDX, IDC_RAWANALYSIS_CANNY_THRES1, m_rawanalysiscannythres1);
	DDX_Text(pDX, IDC_RAWANALYSIS_CANNY_THRES2, m_rawanalysiscannythres2);
	DDX_Text(pDX, IDC_RAWANALYSIS_FACE_XMLURL, m_rawanalysisfacexmlurl);
}


BEGIN_MESSAGE_MAP(Rawanalysis, CDialogEx)
	ON_BN_CLICKED(IDC_RAWANALYSIS_OPEN, &Rawanalysis::OnBnClickedRawanalysisOpen)
	ON_BN_CLICKED(IDCANCEL, &Rawanalysis::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RAWANALYSIS_AUTO, &Rawanalysis::OnBnClickedRawanalysisAuto)
	ON_EN_KILLFOCUS(IDC_RAWANALYSIS_AUTO_INTERFRAMENUM, &Rawanalysis::OnKillfocusRawanalysisAutoInterframenum)
	ON_BN_CLICKED(IDC_RAWANALYSIS_OUTPICFOLDER, &Rawanalysis::OnClickedRawanalysisOutpicfolder)
END_MESSAGE_MAP()


// Rawanalysis 消息处理程序
BOOL Rawanalysis::OnInitDialog(){
	CDialogEx::OnInitDialog();
	m_rawanalysismethod=0;
	m_rawanalysisautointerframenum=25;
	y_width=0;
	y_height=0;
	UpdateData(FALSE);
	GetDlgItem(IDC_RAWANALYSIS_AUTO_INTERFRAMENUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAWANALYSIS_AUTO_OK)->EnableWindow(FALSE);
	y_data=NULL;
	u_data=NULL;
	v_data=NULL;
	//
	m_rawanalysisoutpicfolderurl.EnableFolderBrowseButton();
	
	TCHAR realpath[MAX_URL_LENGTH]={0};
	//生成文件路径
	GetCurrentDirectory(MAX_URL_LENGTH,realpath);
	CString realpath1(realpath);
	realpath1.Append(_T("\\rawanalysispic"));

	m_rawanalysisoutpicfolderurl.SetWindowText(realpath1);


	

	m_rawanalysisoutpicfolderurl.EnableWindow(FALSE);
	//----------------------
	m_rawanalysiscolorhbin=16;
	m_rawanalysiscolorsbin=8;
	m_rawanalysiscontourthres=60;
	m_rawanalysiscannythres1=50;
	m_rawanalysiscannythres2=150;
	m_rawanalysisfacexmlurl.Format(_T("haarcascade_frontalface_alt2.xml"));
	UpdateData(FALSE);
	//----------------------
	return TRUE;
}

void Rawanalysis::OnBnClickedRawanalysisOpen()
{
	//检查内存中yuv数据是否合适
	//如果不合适，通过catch来弹出警告
	

	try{
		YUVtoIpl1();
	}catch(...){
		CString resloader;
		resloader.LoadString(IDS_MSGBOX_NODATA);
		AfxMessageBox(resloader);
		return;
	}
	//检查文件夹路径是否存在
	if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
		CString folder_url;
		m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);
		CreateDirectory(folder_url,NULL);
	}

	//-------

	UpdateData(TRUE);


	switch(m_rawanalysismethod){
	case 0:
		Color_Histogram();
		break;
	case 1:
		Canny();
		break;
	case 2:
		Contour();
		break;
	case 3:
		DFT();
		break;
	case 4:
		face_detect();
		break;
	case 5:
		show_color_component(SHOW_R_COMP);
		break;
	case 6:
		show_color_component(SHOW_G_COMP);
		break;
	case 7:
		show_color_component(SHOW_B_COMP);
		break;
	case 8:
		show_color_component(SHOW_Y_COMP);
		break;
	case 9:
		show_color_component(SHOW_U_COMP);
		break;
	case 10:
		show_color_component(SHOW_V_COMP);
		break;
	default:
		Color_Histogram();
		break;
	}
}


// Rearrange the quadrants of Fourier image so that the origin is at
// the image center
// src & dst arrays of equal size & type
void Rawanalysis::cvShiftDFT(CvArr * src_arr, CvArr * dst_arr )
{
	CvMat * tmp;
	CvMat q1stub, q2stub;
	CvMat q3stub, q4stub;
	CvMat d1stub, d2stub;
	CvMat d3stub, d4stub;
	CvMat * q1, * q2, * q3, * q4;
	CvMat * d1, * d2, * d3, * d4;

	CvSize size = cvGetSize(src_arr);
	CvSize dst_size = cvGetSize(dst_arr);
	int cx, cy;

	if(dst_size.width != size.width || 
		dst_size.height != size.height){
			cvError( CV_StsUnmatchedSizes, "cvShiftDFT", "Source and Destination arrays must have equal sizes", __FILE__, __LINE__ );   
	}

	if(src_arr==dst_arr){
		tmp = cvCreateMat(size.height/2, size.width/2, cvGetElemType(src_arr));
	}

	cx = size.width/2;
	cy = size.height/2; // image center

	q1 = cvGetSubRect( src_arr, &q1stub, cvRect(0,0,cx, cy) );
	q2 = cvGetSubRect( src_arr, &q2stub, cvRect(cx,0,cx,cy) );
	q3 = cvGetSubRect( src_arr, &q3stub, cvRect(cx,cy,cx,cy) );
	q4 = cvGetSubRect( src_arr, &q4stub, cvRect(0,cy,cx,cy) );
	d1 = cvGetSubRect( dst_arr, &d1stub, cvRect(0,0,cx,cy) );
	d2 = cvGetSubRect( dst_arr, &d2stub, cvRect(cx,0,cx,cy) );
	d3 = cvGetSubRect( dst_arr, &d3stub, cvRect(cx,cy,cx,cy) );
	d4 = cvGetSubRect( dst_arr, &d4stub, cvRect(0,cy,cx,cy) );

	if(src_arr!=dst_arr){
		if( !CV_ARE_TYPES_EQ( q1, d1 )){
			cvError( CV_StsUnmatchedFormats, "cvShiftDFT", "Source and Destination arrays must have the same format", __FILE__, __LINE__ ); 
		}
		cvCopy(q3, d1, 0);
		cvCopy(q4, d2, 0);
		cvCopy(q1, d3, 0);
		cvCopy(q2, d4, 0);
	}
	else{
		cvCopy(q3, tmp, 0);
		cvCopy(q1, q3, 0);
		cvCopy(tmp, q1, 0);
		cvCopy(q4, tmp, 0);
		cvCopy(q2, q4, 0);
		cvCopy(tmp, q2, 0);
	}
}

int Rawanalysis::DFT()
{

	CString folder_url,folder_url1,folder_url2,pic_name,pic_name1,pic_name2;
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url1);
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url2);

	IplImage * im;

	IplImage * realInput;
	IplImage * imaginaryInput;
	IplImage * complexInput;
	int dft_M, dft_N;
	CvMat* dft_A, tmp;
	IplImage * image_Re;
	IplImage * image_Im;
	double m, M;
	//-------------
	//im = cvLoadImage(fileurl, CV_LOAD_IMAGE_GRAYSCALE );

	im=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	cvCvtColor(result_image,im,CV_RGB2GRAY);
	//-------------
	if( !im )
		return -1;

	realInput = cvCreateImage( cvGetSize(im), IPL_DEPTH_64F, 1);
	imaginaryInput = cvCreateImage( cvGetSize(im), IPL_DEPTH_64F, 1);
	complexInput = cvCreateImage( cvGetSize(im), IPL_DEPTH_64F, 2);

	cvScale(im, realInput, 1.0, 0.0);
	cvZero(imaginaryInput);
	cvMerge(realInput, imaginaryInput, NULL, NULL, complexInput);

	dft_M = cvGetOptimalDFTSize( im->height - 1 );
	dft_N = cvGetOptimalDFTSize( im->width - 1 );

	dft_A = cvCreateMat( dft_M, dft_N, CV_64FC2 );
	image_Re = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);
	image_Im = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);

	// copy A to dft_A and pad dft_A with zeros
	cvGetSubRect( dft_A, &tmp, cvRect(0,0, im->width, im->height));
	cvCopy( complexInput, &tmp, NULL );
	if( dft_A->cols > im->width )
	{
		cvGetSubRect( dft_A, &tmp, cvRect(im->width,0, dft_A->cols - im->width, im->height));
		cvZero( &tmp );
	}

	// no need to pad bottom part of dft_A with zeros because of
	// use nonzero_rows parameter in cvDFT() call below

	cvDFT( dft_A, dft_A, CV_DXT_FORWARD, complexInput->height );

	cvNamedWindow("win", 0);
	cvNamedWindow("magnitude", 0);
	cvNamedWindow("im", 0);
	cvShowImage("win", im);

	// Split Fourier in real and imaginary parts
	cvSplit( dft_A, image_Re, image_Im, 0, 0 );

	// Compute the magnitude of the spectrum Mag = sqrt(Re^2 + Im^2)
	cvPow( image_Re, image_Re, 2.0);
	cvPow( image_Im, image_Im, 2.0);
	cvAdd( image_Re, image_Im, image_Re, NULL);
	cvPow( image_Re, image_Re, 0.5 );

	// Compute log(1 + Mag)
	cvAddS( image_Re, cvScalarAll(1.0), image_Re, NULL ); // 1 + Mag
	cvLog( image_Re, image_Re ); // log(1 + Mag)


	// Rearrange the quadrants of Fourier image so that the origin is at
	// the image center
	cvShiftDFT( image_Re, image_Re );

	cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);
	cvScale(image_Re, image_Re, 1.0/(M-m), 1.0*(-m)/(M-m));
	cvShowImage("magnitude", image_Re);
	cvShowImage("im", image_Im);

	if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
		pic_name.Format(_T("pic_%d.jpg"),frame_index);
		pic_name1.Format(_T("pic_%d_dft_magnitude.jpg"),frame_index);
		pic_name2.Format(_T("pic_%d_dft_im.jpg"),frame_index);
		folder_url.AppendFormat(_T("\\%s"),pic_name);
		folder_url1.AppendFormat(_T("\\%s"),pic_name1);
		folder_url2.AppendFormat(_T("\\%s"),pic_name2);
#ifdef _UNICODE
		USES_CONVERSION;
		cvSaveImage(W2A(folder_url),im);
		cvSaveImage(W2A(folder_url1),image_Re);
		cvSaveImage(W2A(folder_url2),image_Im);
#else
		cvSaveImage(folder_url,im);
		cvSaveImage(folder_url1,image_Re);
		cvSaveImage(folder_url2,image_Im);
#endif
	}


	cvWaitKey(-1);
	return 0;
}

int Rawanalysis::Color_Histogram()
{
	CString folder_url,folder_url1,pic_name,pic_name1;
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url1);

	IplImage * src;
	src=result_image;

	IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* planes[] = { h_plane, s_plane };

	/** H 分量划分为16个等级，S分量划分为8个等级 */
	int h_bins = m_rawanalysiscolorhbin, s_bins = m_rawanalysiscolorsbin;
	int hist_size[] = {h_bins, s_bins};

	/** H 分量的变化范围 */
	float h_ranges[] = { 0, 180 }; 

	/** S 分量的变化范围*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };

	/** 输入图像转换到HSV颜色空间 */
	cvCvtColor( src, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );

	/** 创建直方图，二维, 每个维度上均分 */
	CvHistogram * hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
	/** 根据H,S两个平面数据统计直方图 */
	cvCalcHist( planes, hist, 0, 0 );

	/** 获取直方图统计的最大值，用于动态显示直方图 */
	float max_value;
	cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );


	/** 设置直方图显示图像 */
	int height = 240;
	int width = (h_bins*s_bins*6);
	IplImage* hist_img = cvCreateImage( cvSize(width,height), 8, 3 );
	cvZero( hist_img );

	/** 用来进行HSV到RGB颜色转换的临时单位图像 */
	IplImage * hsv_color = cvCreateImage(cvSize(1,1),8,3);
	IplImage * rgb_color = cvCreateImage(cvSize(1,1),8,3);
	int bin_w = width / (h_bins * s_bins);
	for(int h = 0; h < h_bins; h++)
	{
		for(int s = 0; s < s_bins; s++)
		{
			int i = h*s_bins + s;
			/** 获得直方图中的统计次数，计算显示在图像中的高度 */
			float bin_val = cvQueryHistValue_2D( hist, h, s );
			int intensity = cvRound(bin_val*height/max_value);

			/** 获得当前直方图代表的颜色，转换成RGB用于绘制 */
			cvSet2D(hsv_color,0,0,cvScalar(h*180.f / h_bins,s*255.f/s_bins,255,0));
			cvCvtColor(hsv_color,rgb_color,CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color,0,0);

			cvRectangle( hist_img, cvPoint(i*bin_w,height),
				cvPoint((i+1)*bin_w,height - intensity),
				color, -1, 8, 0 );
		}
	}

	cvNamedWindow( "Source", 1 );
	cvShowImage( "Source", src );

	cvNamedWindow( "H-S Histogram", 1 );
	cvShowImage( "H-S Histogram", hist_img );

	if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
		pic_name.Format(_T("pic_%d.jpg"),frame_index);
		pic_name1.Format(_T("pic_%d_histogram.jpg"),frame_index);
		folder_url.AppendFormat(_T("\\%s"),pic_name);
		folder_url1.AppendFormat(_T("\\%s"),pic_name1);
#ifdef _UNICODE
		USES_CONVERSION;
		cvSaveImage(W2A(folder_url),src);
		cvSaveImage(W2A(folder_url1),hist_img);
#else
		cvSaveImage(folder_url,src);
		cvSaveImage(folder_url1,hist_img);
#endif
	}


	cvWaitKey(0);
	return 0;
}

int Rawanalysis::Canny(){

	CString folder_url,folder_url1,pic_name,pic_name1;
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url1);

	//声明IplImage指针
	IplImage* pImg = NULL; 
	IplImage* pCannyImg = NULL;

	//载入图像，强制转化为Gray

	pImg=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	cvCvtColor(result_image,pImg,CV_RGB2GRAY);
	
	//-------------------------
	//pImg = cvLoadImage( fileurl, 0);
	//为canny边缘图像申请空间
	pCannyImg = cvCreateImage(cvGetSize(pImg),
		IPL_DEPTH_8U,
		1);
	//canny边缘检测
	cvCanny(pImg, pCannyImg, m_rawanalysiscannythres1, m_rawanalysiscannythres2, 3);

	//创建窗口
	cvNamedWindow("src", 1);
	cvNamedWindow("canny",1);


	//显示图像
	cvShowImage( "src", pImg );
	cvShowImage( "canny", pCannyImg );

	//保存
	if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
		pic_name.Format(_T("pic_%d.jpg"),frame_index);
		pic_name1.Format(_T("pic_%d_canny.jpg"),frame_index);
		folder_url.AppendFormat(_T("\\%s"),pic_name);
		folder_url1.AppendFormat(_T("\\%s"),pic_name1);
#ifdef _UNICODE
		USES_CONVERSION;
		cvSaveImage(W2A(folder_url),pImg);
		cvSaveImage(W2A(folder_url1),pCannyImg);
#else
		cvSaveImage(folder_url,pImg);
		cvSaveImage(folder_url1,pCannyImg);
#endif
	}
	
	cvWaitKey(0); //等待按键

	//销毁窗口
	cvDestroyWindow( "src" );
	cvDestroyWindow( "canny" );
	//释放图像
	cvReleaseImage( &pImg ); 
	cvReleaseImage( &pCannyImg ); 

	return 0;
}


 
int Rawanalysis::face_detect()
{
	CString folder_url,pic_name;
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);
    //opencv装好后haarcascade_frontalface_alt2.xml的路径,
#ifdef _UNICODE
	USES_CONVERSION;
	cascade = (CvHaarClassifierCascade*)cvLoad(W2A(m_rawanalysisfacexmlurl), 0, 0, 0 );
#else
	cascade = (CvHaarClassifierCascade*)cvLoad(m_rawanalysisfacexmlurl, 0, 0, 0 );
#endif
    
 
    if( !cascade )
    {
        AfxMessageBox(_T("Error: Can't load classifier cascade"));
        return -1;
    }
    storage = cvCreateMemStorage(0);
 
    cvNamedWindow( "result", 1 );
	//-----------
	IplImage* image;
	//-------------
	UpdateData(TRUE);

	image=result_image;
	
	//-------------
    
 
    if( image )
    {
        detect_and_draw( image );

		//保存
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_facedetect.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			USES_CONVERSION;
			cvSaveImage(W2A(folder_url),image);
#else
			cvSaveImage(folder_url,image);
#endif
		}

        cvWaitKey(0);
        cvReleaseImage( &image );
    }
 
    cvDestroyWindow("result");
 
    return 0;
}
 
void Rawanalysis::detect_and_draw( IplImage* img )
{
    static CvScalar colors[] = 
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };
 
    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),
                     8, 1 );
    int i;
 
    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );
 
    if( cascade )
    {
        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
        t = (double)cvGetTickCount() - t;
        printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvPoint center;
            int radius;
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
        }
    }
 
    cvShowImage( "result", img );
    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
}

int Rawanalysis::Contour()
{
	CString folder_url,folder_url1,pic_name,pic_name1;
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url1);
	//声明IplImage指针
	IplImage* pImg = NULL; 
	IplImage* pContourImg = NULL;


	CvMemStorage * storage = cvCreateMemStorage(0);
	CvSeq * contour = 0;
	//int mode = CV_RETR_EXTERNAL;
	int mode = CV_RETR_CCOMP; //内外轮廓都检测


	//创建窗口
	cvNamedWindow("src", 1);
	cvNamedWindow("contour",1);


	pImg=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	cvCvtColor(result_image,pImg,CV_RGB2GRAY);

	//载入图像，强制转化为Gray
	if(pImg != 0 )
	{

		cvShowImage( "src", pImg );

		//为轮廓显示图像申请空间
		//3通道图像，以便用彩色显示
		pContourImg = cvCreateImage(cvGetSize(pImg),
			IPL_DEPTH_8U,
			3);
		//copy source image and convert it to BGR image
		cvCvtColor(pImg, pContourImg, CV_GRAY2BGR);

		//图像二值化，设置门限60
		cvThreshold(pImg,pImg,m_rawanalysiscontourthres, 255.0, CV_THRESH_BINARY);
		//查找contour
		cvFindContours( pImg, storage, &contour, sizeof(CvContour), 
			mode, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
		

	}
	else
	{
		//销毁窗口
		cvDestroyWindow( "src" );
		cvDestroyWindow( "contour" );
		cvReleaseMemStorage(&storage);

		return -1;
	}




	//将轮廓画出    
	cvDrawContours(pContourImg, contour, 
		CV_RGB(0,0,255), CV_RGB(255, 0, 0), 
		2, 2, 8, cvPoint(0,0));
	//显示图像
	cvShowImage( "contour", pContourImg );

	//保存
	if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
		pic_name.Format(_T("pic_%d.jpg"),frame_index);
		pic_name1.Format(_T("pic_%d_contour.jpg"),frame_index);
		folder_url.AppendFormat(_T("\\%s"),pic_name);
		folder_url1.AppendFormat(_T("\\%s"),pic_name1);
#ifdef _UNICODE
		USES_CONVERSION;
		cvSaveImage(W2A(folder_url),pImg);
		cvSaveImage(W2A(folder_url1),pContourImg);
#else
		cvSaveImage(folder_url,pImg);
		cvSaveImage(folder_url1,pContourImg);
#endif
	}

	cvWaitKey(0);


	//销毁窗口
	cvDestroyWindow( "src" );
	cvDestroyWindow( "contour" );
	//释放图像
	cvReleaseImage( &pImg ); 
	cvReleaseImage( &pContourImg ); 

	cvReleaseMemStorage(&storage);

	return 0;
}


//简单的方法
int Rawanalysis::YUVtoIpl1(){
	IplImage *yimg,*uimg,*vimg,*uuimg,*vvimg;
	//先检查一下是否有数据（以及相应的属性是否被赋值）如果没有，抛出异常
	if(y_width==0||y_height==0){
		throw 123;
	}
	//转换结果（RGB）
	result_image = cvCreateImage(cvSize(y_width, y_height),IPL_DEPTH_8U,3);
	//转换之源（YUV）
	yuvimage = cvCreateImage(cvSize(y_width,y_height),IPL_DEPTH_8U,3);

	yimg = cvCreateImageHeader(cvSize(y_width, y_height),IPL_DEPTH_8U,1);
	uimg = cvCreateImageHeader(cvSize(y_width/2, y_height/2),IPL_DEPTH_8U,1);
	vimg = cvCreateImageHeader(cvSize(y_width/2, y_height/2),IPL_DEPTH_8U,1);

	uuimg = cvCreateImage(cvSize(y_width, y_height),IPL_DEPTH_8U,1);
	vvimg = cvCreateImage(cvSize(y_width, y_height),IPL_DEPTH_8U,1);
	//保护临界段
	critical_section.Lock();
	cvSetData(yimg,y_data, y_width);
	cvSetData(uimg,u_data, y_width/2);
	cvSetData(vimg,v_data, y_width/2);

	cvResize(uimg,uuimg,CV_INTER_LINEAR);
	cvResize(vimg,vvimg,CV_INTER_LINEAR);

	cvMerge(yimg,uuimg,vvimg,NULL,yuvimage);
	//cvCvtColor(yuvimage,result_image,CV_YCrCb2BGR);
	cvCvtColor(yuvimage,result_image,CV_YCrCb2RGB);
	critical_section.Unlock();

	return 0;
}
//比较复杂的方法
int Rawanalysis::YUVtoIpl2(){
	unsigned char* pRGB = NULL;

	pRGB = (unsigned char*)malloc(y_height*y_width*sizeof(unsigned char)*3);

	YUV420_C_RGB(y_data,u_data,v_data,pRGB,y_height,y_width);

	result_image = cvCreateImageHeader(cvSize(y_width, y_height),IPL_DEPTH_8U,3);
	cvSetData(result_image,pRGB,y_width*3);
	return 0;
}

void Rawanalysis::YUV420_C_RGB( char* pY,char* pU,char* pV, unsigned char* pRGB, int height, int width){

    unsigned char* pBGR = NULL;
    unsigned char R = 0;
    unsigned char G = 0;
    unsigned char B = 0;
    char Y = 0;
    char U = 0;
    char V = 0;
    double tmp = 0;
    for ( int i = 0; i < height; ++i )
    {
        for ( int j = 0; j < width; ++j )
        {
            pBGR = pRGB+ i*width*3+j*3;

            Y = *(pY+i*width+j);
            U = *pU;
            V = *pV;

            //B
            tmp = MB(Y, U, V);
            //B = (tmp > 255) ? 255 : (char)tmp;
            //B = (B<0) ? 0 : B;
			B = (unsigned char)tmp;
            //G
            tmp = MG(Y, U, V);
            //G = (tmp > 255) ? 255 : (char)tmp;
           // G = (G<0) ? 0 : G;
			G = (unsigned char)tmp;
            //R
            tmp = MR(Y, U, V);
            //R = (tmp > 255) ? 255 : (char)tmp;
            //R = (R<0) ? 0 : R;
			R = (unsigned char)tmp;


            *pBGR     = R;            
            *(pBGR+1) = G;        
            *(pBGR+2) = B;
        

            if ( i%2 == 0 && j%2 == 0)
            {
                *pU++;
				//*pV++;
            }
            else
            {
                if ( j%2 == 0 )
                {
                    *pV++ ;
                }
			}
        }
    
    }
}

void Rawanalysis::SystemClear(){
	m_rawanalysiscolorhbin=16;
	m_rawanalysiscolorsbin=8;
	m_rawanalysiscontourthres=60;
	m_rawanalysiscannythres1=50;
	m_rawanalysiscannythres2=150;
	m_rawanalysisfacexmlurl.Format(_T("haarcascade_frontalface_alt2.xml"));
	UpdateData(FALSE);
}

void Rawanalysis::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//关闭
	SystemClear();
	//关闭所有窗口
	cvDestroyAllWindows();
	m_rawanalysisauto.SetCheck(0);
	//CDialogEx::OnCancel();
	ShowWindow(FALSE);
}

int Rawanalysis::show_color_component(int nameid){
	//YUVtoIpl1();
	//分量
	IplImage *r_comp=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	IplImage *g_comp=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	IplImage *b_comp=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	IplImage *y_comp=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	IplImage *u_comp=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	IplImage *v_comp=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,1);
	//注意顺序：BGR
	cvSplit(result_image,b_comp,g_comp,r_comp,NULL);
	cvSplit(yuvimage,y_comp,u_comp,v_comp,NULL);
	//RGB分量转成彩色图片
	IplImage *img_r=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,3);
	IplImage *img_g=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,3);
	IplImage *img_b=cvCreateImage(cvGetSize(result_image),IPL_DEPTH_8U,3);
	cvZero(img_b);
	cvZero(img_g);
	cvZero(img_r);
	cvMerge(b_comp,0,0,0,img_b);
	cvMerge(0,g_comp,0,0,img_g);
	cvMerge(0,0,r_comp,0,img_r);

#ifdef _UNICODE
	USES_CONVERSION;
#endif


	CString folder_url,pic_name;
	m_rawanalysisoutpicfolderurl.GetWindowText(folder_url);

	switch(nameid){
	case SHOW_R_COMP:{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", img_r );//显示图像
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_r.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			cvSaveImage(W2A(folder_url),img_r);
#else
			cvSaveImage(folder_url,img_r);
#endif

		}
		break;
					 }
	case SHOW_G_COMP:{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", img_g );//显示图像
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_g.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			cvSaveImage(W2A(folder_url),img_g);
#else
			cvSaveImage(folder_url,img_g);
#endif
		}
		break;
					 }
	case SHOW_B_COMP:{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", img_b );//显示图像
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_b.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			cvSaveImage(W2A(folder_url),img_b);
#else
			cvSaveImage(folder_url,img_b);
#endif
		}
		break;
					 }
	case SHOW_Y_COMP:{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", y_comp );//显示图像
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_y.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			cvSaveImage(W2A(folder_url),y_comp);
#else
			cvSaveImage(folder_url,y_comp);
#endif
		}
		break;
					 }
	case SHOW_U_COMP:{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", u_comp );//显示图像
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_u.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			cvSaveImage(W2A(folder_url),u_comp);
#else
			cvSaveImage(folder_url,u_comp);
#endif
		}
		break;
					 }
	case SHOW_V_COMP:{
		cvNamedWindow( "Image", 1 );//创建窗口
		cvShowImage( "Image", v_comp );//显示图像
		if(m_rawanalysisoutpicfolder.GetCheck()==TRUE){
			pic_name.Format(_T("pic_%d_v.jpg"),frame_index);
			folder_url.AppendFormat(_T("\\%s"),pic_name);
#ifdef _UNICODE
			cvSaveImage(W2A(folder_url),v_comp);
#else
			cvSaveImage(folder_url,v_comp);
#endif
		}
		break;
					 }
	}

	

	cvReleaseImage(&img_r);
	cvReleaseImage(&img_g);
	cvReleaseImage(&img_b);
	cvReleaseImage(&r_comp);
	cvReleaseImage(&g_comp);
	cvReleaseImage(&b_comp);
	cvReleaseImage(&v_comp);
	cvReleaseImage(&u_comp);
	cvReleaseImage(&v_comp);
	return 0;
}

void Rawanalysis::OnBnClickedRawanalysisAuto()
{
	if(m_rawanalysisauto.GetCheck()==1){
		GetDlgItem(IDC_RAWANALYSIS_AUTO_INTERFRAMENUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_RAWANALYSIS_AUTO_OK)->EnableWindow(TRUE);
	}else{
		GetDlgItem(IDC_RAWANALYSIS_AUTO_INTERFRAMENUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_RAWANALYSIS_AUTO_OK)->EnableWindow(FALSE);
	}
}

void Rawanalysis::OnKillfocusRawanalysisAutoInterframenum()
{
	UpdateData(TRUE);
}



void Rawanalysis::OnClickedRawanalysisOutpicfolder()
{
	if(m_rawanalysisoutpicfolder.GetCheck()==FALSE){
		m_rawanalysisoutpicfolderurl.EnableWindow(FALSE);
	}else{
		m_rawanalysisoutpicfolderurl.EnableWindow(TRUE);
	}
}
