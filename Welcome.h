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


// Welcome

class Welcome : public CWnd
{
	DECLARE_DYNAMIC(Welcome)

public:
	Welcome();
	virtual ~Welcome();

protected:
	DECLARE_MESSAGE_MAP()
public:   
	CBitmap m_bitmap;   
	//  void Create(void);   
	void Create(UINT nBitmapID);   
	afx_msg void OnPaint();   
	afx_msg void OnTimer(UINT_PTR nIDEvent);   

};


