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
	std::vector<std::string> buffer;		// 撤销缓冲区字符串
	std::vector<std::string> undo;		//恢复缓冲区字符串
	Buffer undo_buffer;			// 恢复缓冲区
	int max_lenth = 10;		// 最长撤销距离，越长缓冲区占用内存空间越多
	bool paint_end = false;		// 判断鼠标是否完成绘制
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