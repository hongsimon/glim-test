#include "pch.h"
#include "CustomCircle.h"

// 원 그리기
void CCustomCircle::DrawPoint(CDC* pDC, int centerX, int centerY, int radius)
{
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;

	PlotCircleLines(pDC, centerX, centerY, x, y);

	while (y >= x)
	{
		x++;

		if (d > 0)
		{
			y--;
			d = d + 2 * (x - y) + 5;
		}
		else
		{
			d = d + 2 * x + 3;
		}

		PlotCircleLines(pDC, centerX, centerY, x, y);
	}
}

std::vector<CPoint> CCustomCircle::GetCirclePoints(int centerX, int centerY, int radius)
{
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;

	std::vector<CPoint> circlePoints;

	auto AddCirclePoints = [&](int cx, int cy, int x, int y)
		{
			circlePoints.push_back(CPoint(cx + x, cy + y));
			circlePoints.push_back(CPoint(cx - x, cy + y));
			circlePoints.push_back(CPoint(cx + x, cy - y));
			circlePoints.push_back(CPoint(cx - x, cy - y));
			circlePoints.push_back(CPoint(cx + y, cy + x));
			circlePoints.push_back(CPoint(cx - y, cy + x));
			circlePoints.push_back(CPoint(cx + y, cy - x));
			circlePoints.push_back(CPoint(cx - y, cy - x));
		};

	AddCirclePoints(centerX, centerY, x, y);

	while (y >= x)
	{
		x++;

		if (d > 0)
		{
			y--;
			d = d + 2 * (x - y) + 5;
		}
		else
		{
			d = d + 2 * x + 3;
		}

		AddCirclePoints(centerX, centerY, x, y);
	}

	return circlePoints;
}

std::vector<CPoint> CCustomCircle::GetThickCirclePoints(CWnd* pCtrl, int centerX, int centerY, int radius, int thickness)
{
	CRect rc;
	pCtrl->GetClientRect(&rc);
	int width = rc.Width();
	int height = rc.Height();

	std::vector<CPoint> circlePoints;

	int rOuter = radius + thickness / 2;
	int rInner = radius - thickness / 2;
	if (rInner < 0) rInner = 0;

	int rOuterSq = rOuter * rOuter;
	int rInnerSq = rInner * rInner;

	int yStart = max(0, centerY - rOuter);
	int yEnd = min(height - 1, centerY + rOuter);

	int xStart = max(0, centerX - rOuter);
	int xEnd = min(width - 1, centerX + rOuter);

	for (int y = yStart; y <= yEnd; ++y)
	{
		int dy = y - centerY;
		int dySq = dy * dy;

		int dxMax = (int)sqrt(max(0, rOuterSq - dySq));
		int dxMin = (int)sqrt(max(0, rInnerSq - dySq));

		int xLeft = max(xStart, centerX - dxMax);
		int xRight = min(xEnd, centerX + dxMax);

		for (int x = xLeft; x <= xRight; ++x)
		{
			int dx = x - centerX;
			int distSq = dx * dx + dySq;

			if (distSq >= rInnerSq && distSq <= rOuterSq)
			{
				circlePoints.push_back(CPoint(x, y));
			}
		}
	}

	return circlePoints;
}


void CCustomCircle::DrawCircle(CDC* pDC, std::vector<CPoint> points)
{
	for (const CPoint& pt : points)
	{
		pDC->SetPixel(pt.x, pt.y, RGB(0, 0, 0));
	}
}

void CCustomCircle::PlotCircleLines(CDC* pDC, int centerX, int centerY, int x, int y)
{
	pDC->MoveTo(centerX - x, centerY + y);
	pDC->LineTo(centerX + x, centerY + y);

	pDC->MoveTo(centerX - x, centerY - y);
	pDC->LineTo(centerX + x, centerY - y);

	pDC->MoveTo(centerX - y, centerY + x);
	pDC->LineTo(centerX + y, centerY + x);

	pDC->MoveTo(centerX - y, centerY - x);
	pDC->LineTo(centerX + y, centerY - x);
}