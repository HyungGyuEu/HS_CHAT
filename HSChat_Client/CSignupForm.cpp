#include "pch.h"
#include "HSChat.h"
#include "HSChatDlg.h"
#include "CSignupForm.h"
#include "json/json.h"



IMPLEMENT_DYNAMIC(CSignupForm, CFormView)

CSignupForm::CSignupForm()
	: CFormView(IDD_FORMVIEW_SIGNUP)
{
	m_pDlg = (CHSChatDlg*)::AfxGetMainWnd();
}

CSignupForm::CSignupForm(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}

CSignupForm::~CSignupForm()
{
}

void CSignupForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSignupForm, CFormView)
	
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP_OK, &CSignupForm::OnBnClickedButtonSignupOK)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP_CANCEL, &CSignupForm::OnBnClickedButtonSignupCancel)
END_MESSAGE_MAP()


// CMyForm 메시지 처리기


BOOL CSignupForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CSignupForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


}


void CSignupForm::OnBnClickedButtonSignupOK()
{	
	CString strName, strBirth, strPhone, strID, strNickname, strPW, strPWOK;
	string name, birth, phone, id, pw, nickname;
	Json::Value root;
	Json::StyledWriter writer;

	GetDlgItemText(IDC_EDIT_SIGNUP_NAME, strName);
	GetDlgItemText(IDC_DATETIMEPICKER_BIRTH, strBirth);
	GetDlgItemText(IDC_EDIT_SIGNUP_PHONE, strPhone);
	GetDlgItemText(IDC_EDIT_SIGNUP_ID, strID);
	GetDlgItemText(IDC_EDIT_SIGNUP_NICKNAME, strNickname);
	GetDlgItemText(IDC_EDIT_SIGNUP_PW, strPW);
	GetDlgItemText(IDC_EDIT_SIGNUP_PWOK, strPWOK);

	((CEdit*)GetDlgItem(IDC_EDIT_SIGNUP_NAME))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT_SIGNUP_PHONE))->SetLimitText(11);
	((CEdit*)GetDlgItem(IDC_EDIT_SIGNUP_ID))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDC_EDIT_SIGNUP_NICKNAME))->SetLimitText(20);

	if (strName.GetLength() == 0 || strName.GetLength() > 20)
		AfxMessageBox(_T("이름을 확인해주세요(1~20자)!"), MB_ICONSTOP);
	else if (strBirth.GetLength() == 0)
		AfxMessageBox(_T("생년월일을 입력하세요!"), MB_ICONSTOP);
	else if (strPhone.GetLength() == 0 || strPhone.GetLength() > 11)
		AfxMessageBox(_T("전화번호를 입력하세요(11자)!"), MB_ICONSTOP);
	else if (strID.GetLength() == 0 || strID.GetLength() > 20)
		AfxMessageBox(_T("아이디를 입력하세요(1~20자)!"), MB_ICONSTOP);
	else if (strNickname.GetLength() == 0 || strNickname.GetLength() > 20)
		AfxMessageBox(_T("닉네임을 입력하세요(1~20자)!"), MB_ICONSTOP);
	else if (strPW.GetLength() == 0)
		AfxMessageBox(_T("비밀번호를 입력하세요!"), MB_ICONSTOP);
	else if (strPW != strPWOK)
		AfxMessageBox(_T("비밀번호를 확인하세요!"), MB_ICONSTOP);
	else {
		name = std::string(CT2CA(strName));
		birth = std::string(CT2CA(strBirth));
		phone = std::string(CT2CA(strPhone));
		id = std::string(CT2CA(strID));
		nickname = std::string(CT2CA(strNickname));
		pw = std::string(CT2CA(strPW));

		if (m_pDlg->pw_check(pw))
		{
			pw = m_pDlg->pw_salting(pw);
			pw = m_pDlg->sha256(pw);
		}
		else
			AfxMessageBox(_T("비밀번호 정책 오류입니다!"), MB_ICONSTOP);



		name = m_pDlg->MultiByteToUtf8(name);
		nickname = m_pDlg->MultiByteToUtf8(nickname);

		root["action"] = "signup";

		root["name"] = name;
		root["birth"] = birth;
		root["phone"] = phone;
		root["id"] = id;
		root["nickname"] = nickname;
		root["pw"] = pw;


		m_pDlg->m_pClient->m_data.msg = writer.write(root);
		m_pDlg->m_pClient->m_data.size = static_cast<int>(m_pDlg->m_pClient->m_data.msg.size());

		m_pDlg->m_pClient->m_SendData();

	}
}


void CSignupForm::OnBnClickedButtonSignupCancel()
{
	m_pDlg->m_ShowForm(0);
}


BOOL CSignupForm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN))
	{
		OnBnClickedButtonSignupOK();
		return TRUE;
	}
	return CFormView::PreTranslateMessage(pMsg);
}
