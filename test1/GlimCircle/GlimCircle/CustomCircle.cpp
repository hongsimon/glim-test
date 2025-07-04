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

void CCustomCircle::DrawCircle(CDC* pDC, std::vector<CPoint> points, int thickness)
{
    int halfThick = thickness / 2;

    for (const CPoint& pt : points)
    {
        CRect rect(pt.x - halfThick, pt.y, pt.x + halfThick + 1, pt.y + 1);
        pDC->FillSolidRect(&rect, RGB(0, 0, 0));
        rect = CRect(pt.x, pt.y - halfThick, pt.x + 1, pt.y + halfThick + 1);
        pDC->FillSolidRect(&rect, RGB(0, 0, 0));
    }
}

void CCustomCircle::PlotCirclePoints(CDC* pDC, int centerX, int centerY, int x, int y, int thickness)
{
    DrawThickPixel(pDC, centerX + x, centerY + y, thickness);
    DrawThickPixel(pDC, centerX - x, centerY + y, thickness);
    DrawThickPixel(pDC, centerX + x, centerY - y, thickness);
    DrawThickPixel(pDC, centerX - x, centerY - y, thickness);
    DrawThickPixel(pDC, centerX + y, centerY + x, thickness);
    DrawThickPixel(pDC, centerX - y, centerY + x, thickness);
    DrawThickPixel(pDC, centerX + y, centerY - x, thickness);
    DrawThickPixel(pDC, centerX - y, centerY - x, thickness);

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

void CCustomCircle::DrawThickPixel(CDC* pDC, int x, int y, int thickness)
{
    int halfThickness = thickness / 2;
    for (int i = -halfThickness; i <= halfThickness; i++) {
        for (int j = -halfThickness; j <= halfThickness; j++) {
            pDC->SetPixel(x + i, y + j, RGB(0, 0, 0));
        }
    }
}