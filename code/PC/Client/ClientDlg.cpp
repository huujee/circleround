// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include <shellapi.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
	, m_devIP(DEV_IP)
	, m_devPort(DEV_PORT)
	, m_strPwd(DEV_PWD)
	, m_pClientSock(NULL)
	, m_bControl(FALSE)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_devIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_devPort);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Control(pDX, IDC_LIST_STATUS, m_listStatus);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CClientDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_localIP = getMyAddress();

	CString strTmp = "[Info] Local IP Address" + m_localIP;
	m_listStatus.InsertString(0, strTmp);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::ConnectView()
{
	CString strPara = m_strIP + " -password=pass";

	ShellExecute(NULL, "open", "C:\\CircleRound\\TightVNC\\tvnviewer.exe", strPara, NULL, SW_SHOW);

	CString strTmp = "[Command] ConnectView to " + m_strIP;
	m_listStatus.InsertString(0, strTmp);
}

void CClientDlg::ConnectViewWithControl()
{
	CString strPara = m_strIP + " -password=gbaosldj";

	ShellExecute(NULL, "open", "C:\\CircleRound\\TightVNC\\tvnviewer.exe", strPara, NULL, SW_SHOW);

	CString strTmp = "[Command] ConnectViewWithControl to " + m_strIP;
	m_listStatus.InsertString(0, strTmp);
}


void CClientDlg::DisconnectView()
{
	ShellExecute(NULL, "open", "c:\\windows\\system32\\taskkill.exe", "/IM tvnviewer.exe", NULL, SW_HIDE);

	CString strTmp = "[Command] DisconnectView to " + m_strIP;
	m_listStatus.InsertString(0, strTmp);

	Sleep(300);
}

void CClientDlg::OnReceive()
{
	TCPPacket pPacket;

	m_pClientSock->Receive(&pPacket, sizeof(TCPPacket));

	if (pPacket.nMode == (int)TcpMode::SetDirection)
	{
		if (pPacket.nRet == (int)TcpRet::SAMEDIRECTION)
		{
			CString strTmp = "[Receive] Already Same Direction";
			m_listStatus.InsertString(0, strTmp);
		}
		else
		{
			CString strTmp = "[Receive] SetDirection";
			m_listStatus.InsertString(0, strTmp);
		}
	}
	else if (pPacket.nMode == (int)TcpMode::SetNone)
	{
		DisconnectView();

		CString strTmp = "[Receive] ClearView";
		m_listStatus.InsertString(0, strTmp);
	}

	if (m_localIP.Compare(pPacket.strIp) != 0)
	{
		if (pPacket.nMode == (int)TcpMode::SetView)
		{
			DisconnectView();

			m_strIP = pPacket.strIp;

			ConnectView();
		}
		else if (pPacket.nMode == (int)TcpMode::SetViewControl)
		{
			DisconnectView();

			m_strIP = pPacket.strIp;

			ConnectViewWithControl();
		}
	}
	/*
	else
	{
		if (pPacket.nMode == (int)TcpMode::SetView || pPacket.nMode == (int)TcpMode::SetViewControl)
		{
			DisconnectView();
			m_bControl = false;
		}
		else if (pPacket.nMode == (int)TcpMode::SetControl)
		{
			if (m_bControl == true)
			{
				DisconnectView();

				m_bControl = false;

				ConnectView();
			}
		}
	}
	*/
}

void CClientDlg::SendToDevice(int nMode) 
{
	TCPPacket pPacket;
	pPacket.nMode = nMode;

	m_pClientSock->Send(&pPacket, sizeof(TCPPacket));
}


void CClientDlg::OnBnClickedBtnConnect()
{
	UpdateData(TRUE);

	if (m_pClientSock == NULL)
	{
		m_pClientSock = new CClientSock();
		m_pClientSock->Create();
		bool bRes = m_pClientSock->Connect(m_devIP, atoi(m_devPort));

		SetDlgItemText(IDC_BTN_CONNECT, DEV_DISCONN);

		CString strTmp = "[Connect] to device";
		m_listStatus.InsertString(0, strTmp);
	}
	else
	{
		m_pClientSock->Close();

		delete m_pClientSock;
		m_pClientSock = NULL;

		SetDlgItemText(IDC_BTN_CONNECT, DEV_CONNECT);

		CString strTmp = "[Disconnect] to device";
		m_listStatus.InsertString(0, strTmp);
	}
}

void CClientDlg::OnBnClickedButton1()
{
	if (m_pClientSock != NULL)
	{
		SendToDevice(TcpMode::SetDirection);

		CString strTmp = "[Set Direction]";
		m_listStatus.InsertString(0, strTmp);
	}
	else
	{
		CString strTmp = "[Error] Not Connected to device";
		m_listStatus.InsertString(0, strTmp);
	}
}

void CClientDlg::OnBnClickedButton2()
{
	if (m_pClientSock != NULL)
	{
		SendToDevice(TcpMode::DeleteDirection);

		CString strTmp = "[Delete Direction]";
		m_listStatus.InsertString(0, strTmp);
	}
	else
	{
		CString strTmp = "[Error] Not Connected to device";
		m_listStatus.InsertString(0, strTmp);
	}
}



void CClientDlg::OnBnClickedCancel()
{
	DisconnectView();

	if (m_pClientSock)
	{
		delete m_pClientSock;
		m_pClientSock = NULL;
	}

	CDialog::OnCancel();
}


CString CClientDlg::getMyAddress()
{
	char hostn[400]; //placeholder for the hostname
	struct hostent *hostIP; //placeholder for the IP address
	CString tmpIP = "";

	//if the gethostname returns a name then the program will get the ip address using gethostbyname
	if ((gethostname(hostn, sizeof(hostn))) == 0)
	{
		hostIP = gethostbyname(hostn); //the netdb.h function gethostbyname
		tmpIP = inet_ntoa(*(struct in_addr*)hostIP->h_addr);

		CString strTmp = "Local IP address: " + tmpIP + "\n";
	}
	else
	{
		//OutputDebugString("ERROR:FC4539 - IP Address not found.\n"); //error if the hostname is not found
		CString strTmp = "[Error] IP Address not found.";
		m_listStatus.InsertString(0, strTmp);
	}

	return tmpIP;
}





