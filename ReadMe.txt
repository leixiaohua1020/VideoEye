VideoEye

雷霄骅 Lei Xiaohua
leixiaohua1020@126.com
中国传媒大学/数字电视技术
Communication University of China / Digital TV Technology
http://blog.csdn.net/leixiaohua1020
 
VideoEye是一个开源的视频分析的软件。本软件可以播放和分析视频数据。它支持多种视频流输入方式：HTTP，RTMP，RTSP以及文件等等。该软件可以实时分析视频流并能以图形化的方式呈现其分析结果。目前该软件还处于完善阶段。

VideoEye is an open-source stream analysis software. It can play and make analysis of video bit stream. It supports multiple kind of sources, include: HTTP, RTMP, RTSP and files, etc. The software can make real time stream analysis and show the result graphically. Currently the software is under development yet.


编译说明:
如果编译时(VS2010)遇到错误如下:
nafxcwd.lib(afxglobals.obj) : error LNK2001: 无法解析的外部符号 _IID_IWICImagingFactory

则按如下步骤操作
At project->Properties->Configuration Properties->Linker->Input->Additional Dependencies I added windowscodecs.lib
则可编译成功。
