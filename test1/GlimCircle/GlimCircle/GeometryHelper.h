#pragma once
class CGeometryHelper
{
public:
    // 3���� ������ �������� �߽ɰ� ������ ���
    static BOOL CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3,
        CPoint& center, int& radius);

private:
    // ���� �� ������ �Ÿ� ���
    static double Distance(CPoint p1, CPoint p2);
};