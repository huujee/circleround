// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__B58492EE_19F2_439C_8ED1_01B716E2F356__INCLUDED_)
#define AFX_CLIENTDLG_H__B58492EE_19F2_439C_8ED1_01B716E2F356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientSock.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CString m_name;
	void OnReceive();
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	~CClientDlg();
// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CClientSock* m_pClientSock;
	HICON m_hIcon;
	CString m_localIP;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void SendToDevice(int nMode);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_devIP;
	CString m_devPort;
	CString m_strIP;
	CString m_strPort;
	CString m_strPwd;

	bool m_bControl;

	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClose();

	void ConnectView();
	void ConnectViewWithControl();
	void DisconnectView();
	CString getMyAddress();

	afx_msg void OnBnClickedButton1();
	CListBox m_listStatus;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__B58492EE_19F2_439C_8ED1_01B716E2F356__INCLUDED_)
