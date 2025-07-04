#pragma once
class CGeometryHelper
{
public:
    // 3점을 지나는 외접원의 중심과 반지름 계산
    static BOOL CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3,
        CPoint& center, int& radius);

private:
    // 점과 점 사이의 거리 계산
    static double Distance(CPoint p1, CPoint p2);
};