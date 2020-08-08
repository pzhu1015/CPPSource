
// VerificationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Verification.h"
#include "VerificationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable:4996)


// CVerificationDlg �Ի���



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
							error += "��һλ: ͳһ������ô����еǼǹ����Ŵ������\n";
						}
						if (i == 1 && one_str != "1" && one_str != "2" && one_str != "3" && one_str != "9")
						{
							error += "�ڶ�λ: ͳһ������ô����л������������\n";
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


// CVerificationDlg ��Ϣ�������

BOOL CVerificationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVerificationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVerificationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVerificationDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox(L"����Ĵ���");
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
		//   �����ڴ�ռ�   
		hMem = GlobalAlloc(GHND | GMEM_SHARE, (str.GetLength() + 1) * 2);
		pStr = (LPTSTR)GlobalLock(hMem);
		wcsncpy_s(pStr, 40, a, 40);
		GlobalUnlock(hMem);

		EmptyClipboard();
		//   ���ü������ı�   
		SetClipboardData(CF_UNICODETEXT, hMem);
		CloseClipboard();
		//   �ͷ��ڴ�ռ�   
		GlobalFree(hMem);
	}
}
