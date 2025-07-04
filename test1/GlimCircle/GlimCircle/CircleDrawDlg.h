
// CCircleDrawDlg.h: 헤더 파일
#include "vector"

#pragma once


// CCircleDrawDlg 대화 상자
class CCircleDrawDlg : public CDialogEx
{
// 생성입니다.
public:
	CCircleDrawDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMCIRCLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:


    // 상태 관리
    BOOL m_bCircleDrawn;                // 정원이 그려졌는지 여부
    BOOL m_bDragging;                   // 드래그 상태
    BOOL m_bNeedRedraw;                 // 드래그 중 새로 그릴지 여부
    int m_nDragIndex;                   // 드래그 중인 점의 인덱스

    // 점 데이터
    std::vector<CPoint> m_clickPoints;  // 클릭한 3개 점
    int m_nPointRadius = 5;             // 클릭 지점 원의 반지름
    int m_nCircleThickness = 3;         // 정원 선 두께
    CPoint* m_pSelectedPoint;

    // 정원 데이터
    CPoint m_circleCenter;              // 정원의 중심
    int m_nCircleRadius;                // 정원의 반지름

    // 스레드
    CWinThread* m_pRandomThread;
    BOOL m_bStopRandom;
    UINT_PTR m_nTimerID = 1;

    // UI 컨트롤
    CEdit m_editPointRadius;
    CEdit m_editCircleThickness;
    CStatic m_drawArea;
    CStatic m_staticCoords[3];
    CButton m_btnReset;
    CButton m_btnRandomMove;

public:
    // 메시지 핸들러
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedReset();
    afx_msg void OnBnClickedRandomMove();
    afx_msg void OnEnChangeEditPointRadius();
    afx_msg void OnEnChangeEditCircleThickness();

    // 사용자 정의 함수
    void DrawCircle(CDC* pDC, CPoint center, int radius, int thickness = 1);
    void DrawClickPoint(CDC* pDC, CPoint point, int radius);
    BOOL IsPointInCircle(CPoint testPoint, CPoint center, int radius);

    // 스레드 관련
    static UINT RandomThreadProc(LPVOID pParam);
    void DoRandom();
};
