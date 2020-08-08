
// VerificationDlg.h : ͷ�ļ�
//

#pragma once
#include<vector>

// CVerificationDlg �Ի���
class CVerificationDlg : public CDialogEx
{
// ����
public:
	CVerificationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERIFICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
private:
	int CharToDigital(wchar_t c);
	wchar_t DigitalToChar(int d);
	int GetCheckSum(const CString &str);
	int GetCheckSum(const std::vector<int> &ids);
	int Weight[17] = { 1,3,9,27,19,26,16,17,20,29,25,13,8,24,10,30,28 };
	std::vector<int> m_edit_ids;
public:
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnEnChangeEdit2();
//	afx_msg void OnEnChangeEdit3();
//	afx_msg void OnEnChangeEdit4();
//	afx_msg void OnEnChangeEdit5();
//	afx_msg void OnEnChangeEdit6();
//	afx_msg void OnEnChangeEdit7();
//	afx_msg void OnEnChangeEdit8();
//	afx_msg void OnEnChangeEdit9();
//	afx_msg void OnEnChangeEdit10();
//	afx_msg void OnEnChangeEdit11();
//	afx_msg void OnEnChangeEdit12();
//	afx_msg void OnEnChangeEdit13();
//	afx_msg void OnEnChangeEdit14();
//	afx_msg void OnEnChangeEdit15();
//	afx_msg void OnEnChangeEdit16();
//	afx_msg void OnEnChangeEdit17();
	afx_msg void OnBnClickedButton2();
};
