
// VerificationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Verification.h"
#include "VerificationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable:4996)


// CVerificationDlg 对话框



CVerificationDlg::CVerificationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VERIFICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVerificationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CVerificationDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_ESCAPE:
			SetFocus();
			return true;
		case 'V':
			if (::GetKeyState(VK_CONTROL) < 0)
			{
				CString str;
				str.Empty();
				if (::OpenClipboard(NULL))
				{
					UINT nFormat = (sizeof(TCHAR) == sizeof(WCHAR) ? CF_UNICODETEXT : CF_TEXT);
					HGLOBAL hClip = GetClipboardData(nFormat);        // typedef HANDLE HGLOBAL
					if (hClip)
					{
						char *pBuff = (char*)GlobalLock(hClip);
						GlobalUnlock(hClip);
						str.Format(_T("%s"), pBuff);
					}
					CloseClipboard();
				}
				//MessageBox(str);
				if (str.GetLength() == 17 || str.GetLength() == 18)
				{
					//TODO 
					//1. split string to char one by one, and set char to the edit text
					//91350100M000100Y4Z

					CString error;
					for (int i = 0; i < m_edit_ids.size(); i++)
					{
						if (i >= str.GetLength())
						{
							SetDlgItemText(m_edit_ids[i], L"");
							break;
						}
						CString one_str(str.GetAt(i));
						SetDlgItemText(m_edit_ids[i], one_str);
						if (i == 0 && one_str != "1" && one_str != "5" && one_str != "9" && one_str != "Y")
						{
							error += "第一位: 统一社会信用代码中登记管理部门代码错误\n";
						}
						if (i == 1 && one_str != "1" && one_str != "2" && one_str != "3" && one_str != "9")
						{
							error += "第二位: 统一社会信用代码中机构类别代码错误\n";
						}
					}
					if (!error.IsEmpty())
					{
						MessageBox(error);
						break;
					}
					int checksum = GetCheckSum(m_edit_ids);
					wchar_t c = DigitalToChar(checksum);
					CString one_str_19(c);
					SetDlgItemText(IDC_EDIT19, one_str_19);
					if (str.GetLength() == 18)
					{
						if (c != str.GetAt(17))
						{
							//TODO check sum error
						}
					}

					CString valid_str;
					for (int i = 0; i < 17; i++)
					{
						CString str;
						GetDlgItemText(m_edit_ids[i], str);
						valid_str.Append(str);
					}
					valid_str.AppendChar(c);

					//TODO set valid code into text editor for copy used
					SetDlgItemText(IDC_EDIT20, valid_str);
				}
				break;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CVerificationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CVerificationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CVerificationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVerificationDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CVerificationDlg 消息处理程序

BOOL CVerificationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_edit_ids.push_back(IDC_EDIT1);
	m_edit_ids.push_back(IDC_EDIT2);
	m_edit_ids.push_back(IDC_EDIT3);
	m_edit_ids.push_back(IDC_EDIT4);
	m_edit_ids.push_back(IDC_EDIT5);
	m_edit_ids.push_back(IDC_EDIT6);
	m_edit_ids.push_back(IDC_EDIT7);
	m_edit_ids.push_back(IDC_EDIT8);
	m_edit_ids.push_back(IDC_EDIT9);
	m_edit_ids.push_back(IDC_EDIT10);
	m_edit_ids.push_back(IDC_EDIT11);
	m_edit_ids.push_back(IDC_EDIT12);
	m_edit_ids.push_back(IDC_EDIT13);
	m_edit_ids.push_back(IDC_EDIT14);
	m_edit_ids.push_back(IDC_EDIT15);
	m_edit_ids.push_back(IDC_EDIT16);
	m_edit_ids.push_back(IDC_EDIT17);
	m_edit_ids.push_back(IDC_EDIT18);
	for (int i = 0; i < m_edit_ids.size(); i++)
	{
		((CEdit *)GetDlgItem(m_edit_ids[i]))->SetLimitText(1);
	}
	((CEdit *)GetDlgItem(IDC_EDIT19))->SetLimitText(1);
	((CEdit *)GetDlgItem(IDC_EDIT20))->SetLimitText(18);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVerificationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVerificationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVerificationDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

int CVerificationDlg::CharToDigital(wchar_t c)
{
	switch (c)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	case 'G':
		return 16;
	case 'H':
		return 17;
	case 'J':
		return 18;
	case 'K':
		return 19;
	case 'L':
		return 20;
	case 'M':
		return 21;
	case 'N':
		return 22;
	case 'P':
		return 23;
	case 'Q':
		return 24;
	case 'R':
		return 25;
	case 'T':
		return 26;
	case 'U':
		return 27;
	case 'W':
		return 28;
	case 'X':
		return 29;
	case 'Y':
		return 30;
	default:
		return -1;
	}
}

wchar_t CVerificationDlg::DigitalToChar(int d)
{
	switch (d)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'A';
	case 11:
		return 'B';
	case 12:
		return 'C';
	case 13:
		return 'D';
	case 14:
		return 'E';
	case 15:
		return 'F';
	case 16:
		return 'G';
	case 17:
		return 'H';
	case 18:
		return 'J';
	case 19:
		return 'K';
	case 20:
		return 'L';
	case 21:
		return 'M';
	case 22:
		return 'N';
	case 23:
		return 'P';
	case 24:
		return 'Q';
	case 25:
		return 'R';
	case 26:
		return 'T';
	case 27:
		return 'U';
	case 28:
		return 'W';
	case 29:
		return 'X';
	case 30:
		return 'Y';
	default:
		return 'Z';
	}
}

int CVerificationDlg::GetCheckSum(const CString & str)
{
	int check_sum = 0;
	for (int i = 0; i < 17; i++)
	{
		int d = CharToDigital(str.GetAt(i));
		if (d == -1)
		{
			return -1;
		}
		check_sum += Weight[i] * d;
	}
	return (31 - check_sum % 31);
}

int CVerificationDlg::GetCheckSum(const std::vector<int>& ids)
{
	int check_sum = 0;
	for (int i = 0; i < 17; i++)
	{
		CString str;
		GetDlgItemText(ids[i], str);
		int d = CharToDigital(str.GetAt(0));
		if (d == -1)
		{
			return -1;
		}
		check_sum += Weight[i] * d;
	}
	return (31 - check_sum % 31);
}

void CVerificationDlg::OnBnClickedButton1()
{
	int checksum = GetCheckSum(m_edit_ids);
	wchar_t c = DigitalToChar(checksum);
	if (c == 'Z')
	{
		SetDlgItemText(IDC_EDIT19, L"");
		SetDlgItemText(IDC_EDIT20, L"");
		MessageBox(L"错误的代码");
	}
	else
	{
		CString one_str_19(c);
		SetDlgItemText(IDC_EDIT19, one_str_19);
		SetDlgItemText(IDC_EDIT18, one_str_19);

		CString valid_str;
		for (int i = 0; i < 17; i++)
		{
			CString str;
			GetDlgItemText(m_edit_ids[i], str);
			valid_str.Append(str);
		}
		valid_str.AppendChar(c);
		SetDlgItemText(IDC_EDIT20, valid_str);
	}
}


void CVerificationDlg::OnBnClickedButton2()
{
	CString str;
	GetDlgItemText(IDC_EDIT20, str);

	if (OpenClipboard())
	{
		if (str.GetLength() >= 40)
		{
			return;
		}
		TCHAR   a[40];
		memcpy(a, str.GetBuffer(0), (str.GetLength() + 1) * 2);
		HGLOBAL   hMem;
		LPTSTR   pStr;
		//   分配内存空间   
		hMem = GlobalAlloc(GHND | GMEM_SHARE, (str.GetLength() + 1) * 2);
		pStr = (LPTSTR)GlobalLock(hMem);
		wcsncpy_s(pStr, 40, a, 40);
		GlobalUnlock(hMem);

		EmptyClipboard();
		//   设置剪贴板文本   
		SetClipboardData(CF_UNICODETEXT, hMem);
		CloseClipboard();
		//   释放内存空间   
		GlobalFree(hMem);
	}
}
