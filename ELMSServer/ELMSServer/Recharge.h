#pragma once


// CRecharge 对话框

class CRecharge : public CDialogEx
{
	DECLARE_DYNAMIC(CRecharge)

public:
	CRecharge(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecharge();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECHARGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_Username;
	int m_Money;
};
