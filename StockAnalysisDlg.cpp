
// StockAnalysisDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "StockAnalysis.h"
#include "StockAnalysisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CGraph.h"


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


// CStockAnalysisDlg 대화 상자



CStockAnalysisDlg::CStockAnalysisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STOCKANALYSIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_JONGMOK, m_jongmok);
}

BEGIN_MESSAGE_MAP(CStockAnalysisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CStockAnalysisDlg::OnBnClickedButtonRun)
	ON_CBN_SELCHANGE(IDC_COMBO_JONGMOK, &CStockAnalysisDlg::OnCbnSelchangeComboJongmok)
END_MESSAGE_MAP()


// CStockAnalysisDlg 메시지 처리기

BOOL CStockAnalysisDlg::OnInitDialog()
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
	stock = new CStock();
	flagPaint = false;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStockAnalysisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStockAnalysisDlg::OnPaint()
{
	if (flagPaint)
	{
		DrawGraph();
	}
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
HCURSOR CStockAnalysisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStockAnalysisDlg::OnBnClickedButtonRun()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i;

	stock->Run();
	

	m_jongmok.ResetContent();

	for (i = 0; i < stock->selectedCompanies.quantity; i++)
	{
		m_jongmok.AddString(stock->selectedCompanies.companies[i]->strName);
	}
	
	m_jongmok.SetCurSel(0);
	UpdateData(FALSE); // 값 -> 컨트롤 (UI 반영)

	if (i == 0)
	{
		return;
	}

	stock->ptrCompany = stock->selectedCompanies.companies[0];
	flagPaint = true;

	RedrawWindow(); 
}


void CStockAnalysisDlg::DrawGraph()
{
	int i;

	PointData* ptData = CGraph::GetPointData(stock->ptrCompany);

	CPaintDC dc(this);

	// rect 그리기
	CBrush whiteBrush(RGB(255, 255, 255));
	CBrush* oldBrush;
	CRect rect = {
		X_START_GRAPH, Y_START_GRAPH, 
		X_START_GRAPH + WIDTH_GRAPH, Y_START_GRAPH + HEIGHT_GRAPH};
	dc.FillRect(&rect, &whiteBrush);

	CPen bluePen, redPen, bluePenThick, redPenThick;
	CPen* oldPen;
	bluePen.CreatePen(PS_SOLID, WIDTH_LINE, RGB(0, 0, 255));
	redPen.CreatePen(PS_SOLID, WIDTH_LINE, RGB(255, 0, 0));
	bluePenThick.CreatePen(PS_SOLID, WIDTH_THICK_LINE, RGB(0, 0, 255));
	redPenThick.CreatePen(PS_SOLID, WIDTH_THICK_LINE, RGB(255, 0, 0));
	
	for ( i = 0; i < stock->ptrCompany->quantity; i++)
	{
		// y좌표는 아래로 갈수록 큰 값을 가진다.
		// 즉, 아래 데이터는 시가가 종가보다 작으므로 양봉이다.
		bool isBull = ptData->startVal.point[i].Y > ptData->lastVal.point[i].Y;
		
		if (isBull)
		{
			dc.SelectObject(redPen);
		}
		else
		{
			dc.SelectObject(bluePen);
		}
		dc.MoveTo(ptData->highVal.point[i].X, ptData->highVal.point[i].Y);
		dc.LineTo(ptData->lowVal.point[i].X, ptData->lowVal.point[i].Y);
		
		if (isBull)
		{
			dc.SelectObject(redPenThick);
		}
		else
		{
			dc.SelectObject(bluePenThick);
		}
		dc.MoveTo(ptData->startVal.point[i].X, ptData->startVal.point[i].Y);
		dc.LineTo(ptData->lastVal.point[i].X, ptData->lastVal.point[i].Y);
	}

	// volume chart
	int yOriginVolume = Y_START_GRAPH + HEIGHT_GRAPH + GAP_GRAPH_VOLUME + HEIGHT_VOLUME;
	CRect rect2 = {
		X_START_GRAPH, Y_START_GRAPH + HEIGHT_GRAPH + GAP_GRAPH_VOLUME,
		X_START_GRAPH + WIDTH_GRAPH, yOriginVolume
	};
	dc.FillRect(&rect2, &whiteBrush);

	for ( i = 0; i < stock->ptrCompany->quantity - 1; i++)
	{
		if (ptData->volume.point[i].Y < ptData->volume.point[i + 1].Y)
		{
			dc.SelectObject(redPenThick);
		}
		else
		{
			dc.SelectObject(bluePenThick);
		}
		dc.MoveTo(ptData->volume.point[i].X, yOriginVolume);
		dc.LineTo(ptData->volume.point[i].X, ptData->volume.point[i].Y);
	}

	// write text
	int maxVal, minVal, maxVol;
	int quantity = stock->ptrCompany->quantity;
	
	maxVal = 0;
	for (i = 0; i < quantity; i++)
	{
		if (stock->ptrCompany->data[i].highVal > maxVal)
		{
			maxVal = stock->ptrCompany->data[i].highVal;
		}
	}

	minVal = maxVal;
	for ( i = 0; i < quantity; i++)
	{
		if (stock->ptrCompany->data[i].lowVal < minVal)
		{
			minVal = stock->ptrCompany->data[i].lowVal;
		}
	}

	maxVol = 0;
	for ( i = 0; i < quantity; i++)
	{
		if (stock->ptrCompany->data[i].vol > maxVol)
		{
			maxVol = stock->ptrCompany->data[i].vol;
		}
	}

	CString str;
	str.Format("- %d 원", maxVal);
	dc.TextOutA(WIDTH_GRAPH + 13, 5, str, str.GetLength());
	

	str.Format("- %d 원", minVal);
	dc.TextOutA(WIDTH_GRAPH + 13, HEIGHT_GRAPH, str, str.GetLength());

	str.Format("- %d", maxVol);
	dc.TextOutA(WIDTH_GRAPH + 13, HEIGHT_GRAPH + GAP_GRAPH_VOLUME, str, str.GetLength());
}

void CStockAnalysisDlg::OnCbnSelchangeComboJongmok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_jongmok.GetCurSel();
	stock->ptrCompany = stock->selectedCompanies.companies[index];
	RedrawWindow();
}
