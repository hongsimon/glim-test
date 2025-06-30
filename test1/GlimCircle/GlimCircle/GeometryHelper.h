#pragma once
class CGeometryHelper
{
public:
    // 3점을 지나는 외접원의 중심과 반지름 계산
    static BOOL CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3,
        CPoint& center, int& radius);

    // 점과 점 사이의 거리 계산
    static double Distance(CPoint p1, CPoint p2);

    // 점이 원 내부에 있는지 확인
    static BOOL IsPointInCircle(CPoint point, CPoint center, int radius);

private:
    // 행렬 계산 헬퍼
    static double Determinant2x2(double a, double b, double c, double d);
    static double Determinant3x3(double matrix[3][3]);
};