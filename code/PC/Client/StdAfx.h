// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B5527F1F_C934_4C8B_A6C2_F40EE9DD6CE9__INCLUDED_)
#define AFX_STDAFX_H__B5527F1F_C934_4C8B_A6C2_F40EE9DD6CE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

#define _AFXDLL

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#define DEV_IP				_T("192.168.0.21")
#define DEV_PORT			_T("23")
#define DEV_PWD				_T("pass")

#define DEV_CONNECT			_T("Connect")
#define DEV_DISCONN			_T("Disconnect")
#define SET_DIRECTION		_T("Set Direction")
#define DELETE_DIRECTION	_T("Delete Direction")



enum TcpMode
{
	Default, Connect, Disconnect, Enable, Unable, Reset,
	SetDirection, DeleteDirection, SetNone, SetView, SetViewControl
};

struct TCPPacket
{
	int nMode;
	int nRet;
	char strIp[17];
};

enum TcpRet
{
	OK, SAMEDIRECTION
};



#endif // !defined(AFX_STDAFX_H__B5527F1F_C934_4C8B_A6C2_F40EE9DD6CE9__INCLUDED_)
