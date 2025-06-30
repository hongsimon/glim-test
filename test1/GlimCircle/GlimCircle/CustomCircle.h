#pragma once
class CCustomCircle
{
public:
    // Bresenham's circle algorithm ±¸Çö
    static void DrawCircle(CDC* pDC, int centerX, int centerY, int radius);
    static void DrawThickCircle(CDC* pDC, int centerX, int centerY, int radius, int thickness);

private:
    static void PlotCirclePoints(CDC* pDC, int centerX, int centerY, int x, int y);
    static void DrawCircleOutline(CDC* pDC, int centerX, int centerY, int radius);
};