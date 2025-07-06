#pragma once
#include "vector"

class CCustomCircle
{
public:
	// Bresenham's circle algorithm ±¸Çö
	static void DrawPoint(CDC* pDC, int centerX, int centerY, int radius);
	static void DrawCircle(CDC* pDC, std::vector<CPoint> points);
	static std::vector<CPoint> GetCirclePoints(int centerX, int centerY, int radius);
	static std::vector<CPoint> GetThickCirclePoints(CWnd* pCtrl, int centerX, int centerY, int radius, int thickness);

private:
	static void PlotCirclePoints(CDC* pDC, int centerX, int centerY, int x, int y, int thickness);
	static void PlotCircleLines(CDC* pDC, int centerX, int centerY, int x, int y);
	static void DrawThickPixel(CDC* pDC, int x, int y, int thickness);
};