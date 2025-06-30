#pragma once
class CGeometryHelper
{
public:
    // 3���� ������ �������� �߽ɰ� ������ ���
    static BOOL CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3,
        CPoint& center, int& radius);

    // ���� �� ������ �Ÿ� ���
    static double Distance(CPoint p1, CPoint p2);

    // ���� �� ���ο� �ִ��� Ȯ��
    static BOOL IsPointInCircle(CPoint point, CPoint center, int radius);

private:
    // ��� ��� ����
    static double Determinant2x2(double a, double b, double c, double d);
    static double Determinant3x3(double matrix[3][3]);
};