#include "pch.h"
#include "GeometryHelper.h"

BOOL CGeometryHelper::CalculateCircumcircle(CPoint p1, CPoint p2, CPoint p3,
    CPoint& center, int& radius) 
{    
    // �� ���� �������� �ִ��� Ȯ�� (�������� �������� ����)
    double det = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if (fabs(det) < 1e-10) {
        return FALSE;  // �� ���� �������� ����
    }

    // �������� �߽� ����� ���� ��Ľ� ���
    double x1 = p1.x, y1 = p1.y;
    double x2 = p2.x, y2 = p2.y;
    double x3 = p3.x, y3 = p3.y;

    // ��Ľ��� �̿��� ������ �߽� ���
    double a = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    if (fabs(a) < 1e-10) {
        return FALSE;  // ��� �Ұ�
    }

    double bx = -(y1 * (x2 * x2 - x3 * x3 + y2 * y2 - y3 * y3) +
        y2 * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) +
        y3 * (x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2));

    double by = x1 * (x2 * x2 - x3 * x3 + y2 * y2 - y3 * y3) +
        x2 * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) +
        x3 * (x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2);

    // �������� �߽� ��ǥ
    double cx = bx / (2 * a);
    double cy = by / (2 * a);

    center.x = (int)(cx + 0.5);  // �ݿø�
    center.y = (int)(cy + 0.5);  // �ݿø�

    // ������ ���
    double r = Distance(CPoint((int)cx, (int)cy), p1);
    radius = (int)(r + 0.5);  // �ݿø�

    return TRUE;
}

double CGeometryHelper::Distance(CPoint p1, CPoint p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}