﻿#pragma once
// HSChatDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "HSChat.h"
#include "HSChatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHSChatDlg 대화 상자



CHSChatDlg::CHSChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HSCHAT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHSChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}

BEGIN_MESSAGE_MAP(CHSChatDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHSChatDlg 메시지 처리기

BOOL CHSChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	AllocForm();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CHSChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHSChatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHSChatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHSChatDlg::AllocForm()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect rectOfPanelArea;

	GetDlgItem(IDC_PICTURE_CONTROL)->GetWindowRect(&rectOfPanelArea);
	ScreenToClient(&rectOfPanelArea);
	m_pSigninForm = new CSigninForm();
	m_pSigninForm->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORMVIEW_SIGNIN, &context);
	m_pSigninForm->OnInitialUpdate();
	m_pSigninForm->ShowWindow(SW_SHOW);

	m_pWatingForm = new CWaitingForm();
	m_pWatingForm->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORMVIEW_WAITING, &context);
	m_pWatingForm->OnInitialUpdate();
	m_pWatingForm->ShowWindow(SW_HIDE);

	m_pChatRoomForm = new CChatRoomForm();
	m_pChatRoomForm->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORMVIEW_CHATROOM, &context);
	m_pChatRoomForm->OnInitialUpdate();
	m_pChatRoomForm->ShowWindow(SW_HIDE);

	m_pSearchIDForm = new CSearchIDForm();
	m_pSearchIDForm->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORMVIEW_SEARCHID, &context);
	m_pSearchIDForm->OnInitialUpdate();
	m_pSearchIDForm->ShowWindow(SW_HIDE);



	GetDlgItem(IDC_PICTURE_CONTROL)->DestroyWindow();
}


void CHSChatDlg::ShowForm(int idx)
{
	switch (idx)
	{
	case 0:		// 로그인 화면
		m_pSigninForm->ShowWindow(SW_SHOW);
		m_pSearchIDForm->ShowWindow(SW_HIDE);
		m_pWatingForm->ShowWindow(SW_HIDE);
		m_pChatRoomForm->ShowWindow(SW_HIDE);
		break;
	case 2:		// ID찾기 화면
		m_pSigninForm->ShowWindow(SW_HIDE);
		m_pSearchIDForm->ShowWindow(SW_SHOW);
		m_pWatingForm->ShowWindow(SW_HIDE);
		m_pChatRoomForm->ShowWindow(SW_HIDE);
		break;

	case 5:		// 대기실 화면
		m_pSigninForm->ShowWindow(SW_HIDE);
		m_pWatingForm->ShowWindow(SW_SHOW);
		m_pChatRoomForm->ShowWindow(SW_HIDE);
		break;

	case 6:
		m_pSigninForm->ShowWindow(SW_HIDE);
		m_pSearchIDForm->ShowWindow(SW_HIDE);
		m_pWatingForm->ShowWindow(SW_HIDE);
		m_pChatRoomForm->ShowWindow(SW_SHOW);
		CEdit* p_EditSend = NULL;
		if ((p_EditSend = (CEdit*)m_pChatRoomForm->GetDlgItem(IDC_EDIT_CHATROOM_SENDMSG)) == NULL)
		{
			AfxMessageBox(_T("ERROR[GetDlgItem()] : Failed to get IDC_EDIT_CHATROOM_SENDMSG"));
		}
		p_EditSend->SetSel(-1);
		p_EditSend->SetFocus();
		break;

	}

}


void CHSChatDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 창 크기 변화할 때 호출

}


//BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	return CDialogEx::PreTranslateMessage(pMsg);
//}
