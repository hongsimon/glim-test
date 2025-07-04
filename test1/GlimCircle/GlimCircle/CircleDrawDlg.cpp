
// CCircleDrawDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimCircle.h"
#include "CircleDrawDlg.h"
#include "CustomCircle.h"
#include "afxdialogex.h"
#include "iostream"

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


// CCircleDrawDlg 대화 상자



CCircleDrawDlg::CCircleDrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMCIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCircleDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_POINT_RADIUS, m_nPointRadius);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_THICKNESS, m_nCircleThickness);
}

BEGIN_MESSAGE_MAP(CCircleDrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT_POINT_RADIUS, &CCircleDrawDlg::OnEnChangeEditPointRadius)
	ON_EN_CHANGE(IDC_EDIT_CIRCLE_THICKNESS, &CCircleDrawDlg::OnEnChangeEditCircleThickness)
END_MESSAGE_MAP()


// CCircleDrawDlg 메시지 처리기

BOOL CCircleDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	AllocConsole();    // stdout
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	// stderr
	freopen_s(&fp, "CONOUT$", "w", stderr);

	// stdin
	freopen_s(&fp, "CONIN$", "r", stdin);

	std::ios::sync_with_stdio(); // C++ iostream 동기화

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
	m_drawArea.SubclassDlgItem(IDC_DRAW_AREA, this);

	CString strText;

	strText.LoadString(IDS_APP_TITLE);
	SetWindowText(strText);

	strText.LoadString(IDS_TEXT_POINT_RADIUS);
	GetDlgItem(IDC_TEXT_POINT_RADIUS)->SetWindowText(strText);

	strText.LoadString(IDS_TEXT_CIRCLE_THICKNESS);
	GetDlgItem(IDC_TEXT_CIRCLE_THICKNESS)->SetWindowText(strText);

	strText.LoadString(IDS_BUTTON_RESET);
	GetDlgItem(IDC_BUTTON_RESET)->SetWindowText(strText);

	strText.LoadString(IDS_BUTTON_RANDOM);
	GetDlgItem(IDC_BUTTON_RANDOM)->SetWindowText(strText);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCircleDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCircleDrawDlg::OnPaint()
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

	
	CClientDC dc(&m_drawArea);
	for (int i = 0; i < m_clickPoints.size(); i++)
	{
		DrawClickPoint(&dc, m_clickPoints[i], m_nPointRadius);

		CString strText;

		strText.LoadString(IDS_TEXT_POINT);
		strText.Format(strText, i + 1, m_clickPoints[i].x, m_clickPoints[i].y);
		GetDlgItem(IDC_TEXT_POINT1 + i)->SetWindowText(strText);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCircleDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCircleDrawDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect drawRect;
	m_drawArea.GetWindowRect(&drawRect);
	ScreenToClient(&drawRect);

	// Picture Control 내부를 클릭했는지 확인
	if (drawRect.PtInRect(point))
	{
		// 클릭 좌표를 Picture Control 기준으로 변환
		CPoint localPos = point;
		localPos.Offset(-drawRect.left, -drawRect.top);

		if (m_clickPoints.size() < 3) 
		{
			for (CPoint p : m_clickPoints) 
			{
				if ((p.x == localPos.x) && (p.y == localPos.y))
				{
					CDialogEx::OnLButtonDown(nFlags, point);
					return;
				}
			}
			m_clickPoints.push_back(localPos);
			Invalidate();
			UpdateWindow();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CCircleDrawDlg::DrawCircle(CDC* pDC, CPoint center, int radius, int thickness) 
{
	std::vector<CPoint> circlePoints = CCustomCircle::GetCirclePoints(center.x, center.y, radius);
	CCustomCircle::DrawCircle(pDC, circlePoints, thickness);
}

void CCircleDrawDlg::DrawClickPoint(CDC* pDC, CPoint point, int radius)
{
	CCustomCircle::DrawPoint(pDC, point.x, point.y, radius);
}

void CCircleDrawDlg::OnEnChangeEditPointRadius()
{
	if (UpdateData(TRUE))
	{
		if (m_nPointRadius == 0)
		{
			m_nPointRadius = 1;
			UpdateData(FALSE);
		}
	}
	Invalidate();
}


void CCircleDrawDlg::OnEnChangeEditCircleThickness()
{
	if (UpdateData(TRUE))
	{
		if (m_nCircleRadius == 0)
		{
			m_nCircleRadius = 1;
			UpdateData(FALSE);
		}
	}
	Invalidate();
}
