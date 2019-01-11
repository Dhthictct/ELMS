// Register.cpp : 实现文件
//

#include "stdafx.h"
#include "ELMSClient.h"
#include "Register.h"
#include "afxdialogex.h"

#include "ELMSClientDlg.h"

// CRegister 对话框

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTER, pParent)
	, m_Edt_Reg_UserName(_T(""))
	, m_Edt_Reg_PassWord(_T(""))
	, m_Edt_Reg_OncePassWord(_T(""))
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_Edt_Reg_UserName);
	DDV_MaxChars(pDX, m_Edt_Reg_UserName, 16);
	DDX_Text(pDX, IDC_EDT_REGPASSEWORD, m_Edt_Reg_PassWord);
	DDV_MaxChars(pDX, m_Edt_Reg_PassWord, 16);
	DDX_Text(pDX, IDC_EDT_REGONCEPASSWORD, m_Edt_Reg_OncePassWord);
	DDV_MaxChars(pDX, m_Edt_Reg_OncePassWord, 16);
	DDX_Control(pDX, IDC_COMBO1, m_cbtable);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_REGISTER, &CRegister::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDCANCEL, &CRegister::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRegister 消息处理程序


void CRegister::OnBnClickedBtnRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加注册代码
	USES_CONVERSION;
	UpdateData(TRUE); //获取控件的值
	if (m_Edt_Reg_UserName.IsEmpty() || m_Edt_Reg_PassWord.IsEmpty() || m_Edt_Reg_OncePassWord.IsEmpty())
	{
		//如果有一项为空，就全部置为空了，并返回
		MessageBox(_T("输入的数据或许为空，请重新输入！"), _T("注册提示"), MB_OK | MB_ICONWARNING);
		m_Edt_Reg_UserName = _T("");
		m_Edt_Reg_PassWord = _T("");
		m_Edt_Reg_OncePassWord = _T("");
		UpdateData(FALSE);
		return;
	}


	//判断密码组成
	int nUserl, nPwdl, nOPwdl;
	nUserl= m_Edt_Reg_UserName.GetLength();
	nPwdl = m_Edt_Reg_PassWord.GetLength();
	nOPwdl = m_Edt_Reg_OncePassWord.GetLength();
	if (nPwdl < 6 || nOPwdl < 6)
	{
		MessageBox(_T("密码至少为六位\r\n请检查密码"));
		return;
	}
	for (int i = 0; i < nUserl; ++i)
	{
		/*if (('a' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= 'z') || 
			('A' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= 'Z') || 
			('0' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= '9'))
		{
		}*/
		if ('!' <= m_Edt_Reg_PassWord[i] && m_Edt_Reg_PassWord[i] <= '~')
		{

		}
		else
		{
			MessageBox(_T("密码只能由字母、数字和标点符号组成组成\r\n请重新输入密码"));
			m_Edt_Reg_PassWord = _T("");
			m_Edt_Reg_OncePassWord = _T("");
			UpdateData(FALSE);
			return;
		}
	}
	

	//比较两次密码是否一致
	if (m_Edt_Reg_PassWord != m_Edt_Reg_OncePassWord)
	{
		MessageBox(_T("两次的密码输入不一致，请重新输入！"), _T("注册提示"), MB_OK | MB_ICONWARNING);
		//m_Edt_Reg_UserName = _T("");
		m_Edt_Reg_PassWord = _T("");
		m_Edt_Reg_OncePassWord = _T("");
		UpdateData(FALSE);
		return;
	}

	//转换，并构造CUser对象信息
	CUser userInfo;
	userInfo.setUserName(T2A(m_Edt_Reg_UserName));
	userInfo.setPassWord(T2A(m_Edt_Reg_PassWord));

	///得到父窗口的窗口句柄
	//因为这里是创建的模态对话框，所以可以使用这个函数
	//当然也可以使用视频中的AfxGetMainWnd()函数，但是要注意哪一个是主窗口
	CELMSClientDlg* mainDlg = (CELMSClientDlg*)(this->GetParent());//获取父窗口的窗口句柄
	//构建协议
	int MSGTYPE = MYMSG_REGISTER;
	//发送内容，先发送协议，在将用户对象信息发送过去
	mainDlg->m_SockClient.Send(&MSGTYPE, sizeof(MSGTYPE));
	mainDlg->m_SockClient.Send(&userInfo, sizeof(CUser));

	//定义这一个变量，用来接收服务器端传过来的内容
	bool bRes = false;
	//接收内容，得到主窗口（对话框，控件等也是窗口）中的套接字
	mainDlg->m_SockClient.Receive(&bRes, sizeof(bRes));
	if (bRes)
	{
		//进行判断
		MessageBox(_T("注册成功，请牢记用户名和密码"), _T("注册提示"), MB_OK | MB_ICONINFORMATION);
		EndDialog(1001); //该函数用来关闭模态对话框，参数为关闭的参数，这个参数就是DoModal()函数的返回值
	}
	else
	{
		//如果没成功并且还要继续注册，就进行处理
		if (IDYES == MessageBox(_T("注册失败，是否需要继续注册"), _T("注册提示"), MB_YESNO | MB_ICONERROR))
		{
			m_Edt_Reg_UserName = _T("");
			m_Edt_Reg_PassWord = _T("");
			m_Edt_Reg_OncePassWord = _T("");
			UpdateData(FALSE);
		}
		else
		{
			//没成功，不注册，就关闭这个模态对话框
			EndDialog(1002);
		}

	}
}


void CRegister::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK == MessageBox(_T("注册尚未成功，真的要退出吗？"), _T("注册提示"), MB_OKCANCEL | MB_ICONQUESTION))
		CDialogEx::OnCancel();
}


void CRegister::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CImage img1;
	img1.Load(_T("theme\\1.jpg"));
	CRect clientRect;//区域大小类
	GetClientRect(&clientRect);//获取客户区的大小
	img1.Draw(dc, 0, 0, clientRect.Width(), clientRect.Height());
}


BOOL CRegister::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cbtable.AddString(_T("会员用户"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
