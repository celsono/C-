#pragma once
#include<QPainter>
#include<QPaintEvent>
#include<QWidget>
#include<QWheelEvent>
#include<QColor>
#include<QPoint>
#include<QLine>
#include<map>
#include <iostream>
#include <vector>
#include <queue>

template<class type>
struct Pattern {
	type shape;
	QColor color;
	int width;
};

struct Buffer {
	std::vector<Pattern<QLine>> line;
	std::vector<Pattern<QRect>> rect;
	std::vector<Pattern<QRect>> ellipse;
};

class DrawWidget :public QWidget
{
	Q_OBJECT;
public:
	DrawWidget();
	~DrawWidget();

private:
	QVector<QPoint> points;
	std::vector<Pattern<QLine>> pattern_line, pattern_curve;
	std::vector<Pattern<QRect>> pattern_ellipse,pattern_rect;
	Pattern<QLine> temp_pattern_line_curve;
	Pattern<QRect> temp_pattern_ellipse,temp_pattern_rect;
	QPoint lastPos;
	std::vector<std::string> buffer;		// �����������ַ���
	std::vector<std::string> undo;		//�ָ��������ַ���
	Buffer undo_buffer;			// �ָ�������
	int max_lenth = 10;		// ��������룬Խ��������ռ���ڴ�ռ�Խ��
	bool paint_end = false;		// �ж�����Ƿ���ɻ���
	int draw_width = 5;
	std::map<std::string, bool> flag;
protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseDoubleClickEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent*);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

public slots:
	void slotChangePntColor();
	void slotClearPoint();
	void slotDrawCurve();
	void slotDrawLine();
	void slotDrawEllipse();
	void slotDrawRect();
	void slotCancel();
	void slotUndo();
	void transmit(int width);
};