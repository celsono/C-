#include"DrawWidget.h"
#include<qvector.h>
#include<qapplication.h>
#include<QColorDialog>


DrawWidget::DrawWidget()
{
	temp_pattern_ellipse.color = Qt::black;
	temp_pattern_ellipse.width = draw_width;
	temp_pattern_rect.color = Qt::black;
	temp_pattern_rect.width = draw_width;
	temp_pattern_line_curve.color = Qt::black;
	temp_pattern_line_curve.width = draw_width;

	flag["curve"] = false;
	flag["line"] = false;
	flag["ellipse"] = false;
	flag["rect"] = false;

}

void DrawWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);		// this是绘制的设备，就是控件

	if (!paint_end)
	{
		painter.setPen(QPen(temp_pattern_line_curve.color, temp_pattern_line_curve.width));
		painter.drawLine(temp_pattern_line_curve.shape);
		painter.setPen(QPen(temp_pattern_ellipse.color, temp_pattern_ellipse.width));
		painter.drawEllipse(temp_pattern_ellipse.shape);
		painter.setPen(QPen(temp_pattern_rect.color, temp_pattern_rect.width));
		painter.drawRect(temp_pattern_rect.shape);
	}
	
	for (auto & it:pattern_curve)
	{
		painter.setPen(QPen(it.color, it.width));
		painter.drawLine(it.shape);
	}

	for (auto& it : pattern_line)
	{
		painter.setPen(QPen(it.color, it.width));
		painter.drawLine(it.shape);
	}
	for (auto& it : pattern_ellipse)
	{
		painter.setPen(QPen(it.color, it.width));
		painter.drawEllipse(it.shape);
	}
	for (auto& it : pattern_rect)
	{
		painter.setPen(QPen(it.color, it.width));
		painter.drawRect(it.shape);
	}

}

void DrawWidget::mousePressEvent(QMouseEvent* event)
{
	lastPos = event->pos();
	paint_end = false;
	update();
}


void DrawWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
	QPoint curPos = event->pos();
	points.append(curPos);
	update();
}

void DrawWidget::mouseMoveEvent(QMouseEvent* event)
{
	QPoint curPos = event->pos();
	QLine line(lastPos, curPos);
	QRect ellipse_rect(lastPos.x(), lastPos.y(), event->x() - lastPos.x(), event->y() - lastPos.y());

	if (flag["curve"])
	{
		temp_pattern_line_curve.shape = line;
		pattern_curve.push_back(temp_pattern_line_curve);
		lastPos = curPos;
	}
	else if (flag["line"] && event->buttons() & Qt::LeftButton)
		temp_pattern_line_curve.shape = line;
	else if (flag["ellipse"] && event->buttons() & Qt::LeftButton)
		temp_pattern_ellipse.shape = ellipse_rect;
	else if (flag["rect"] && event->buttons() & Qt::LeftButton)
		temp_pattern_rect.shape = ellipse_rect;
	update();
}

void DrawWidget::mouseReleaseEvent(QMouseEvent* event)
{
	std::string temp_type;
	bool valid= false;
	paint_end = true;
	if (flag["line"])
	{
		valid = true;
		temp_type = "line";
		pattern_line.push_back(temp_pattern_line_curve);
	}	
	else if (flag["ellipse"])
	{
		valid = true;
		temp_type = "ellipse";
		pattern_ellipse.push_back(temp_pattern_ellipse);
	}
	else if (flag["rect"])
	{
		valid = true;
		temp_type = "rect";
		pattern_rect.push_back(temp_pattern_rect);
	}
	if (valid)
	{
		buffer.push_back(temp_type);
		if (buffer.size() == max_lenth)
			buffer.erase(buffer.begin());
	}
	temp_pattern_line_curve.shape.setLine(-100, -100, -100, -100);
	temp_pattern_ellipse.shape.setRect(-100, -100, 0, 0);
	temp_pattern_rect.shape.setRect(-100, -100, 0, 0);
	update();
}

void DrawWidget::slotChangePntColor()
{
	QColor t_color = QColorDialog::getColor(Qt::white, this);
	if (t_color.isValid())
	{
		temp_pattern_ellipse.color = t_color;
		temp_pattern_rect.color = t_color;
		temp_pattern_line_curve.color = t_color;

	}	
	else return;
}

void DrawWidget::slotDrawCurve()
{
	if (flag["curve"])
		flag["curve"] = false;
	else
	{
		for (auto &it:flag)
			it.second = false;
		flag["curve"] = true;
	}
	update();
}

void DrawWidget::slotDrawRect()
{
	if (flag["rect"])
		flag["rect"] = false;
	else
	{
		for (auto& it : flag)
			it.second = false;
		flag["rect"] = true;
	}
	update();
}

void DrawWidget::slotClearPoint()
{
	temp_pattern_line_curve.shape.setLine(-100, -100, -100, -100);
	temp_pattern_ellipse.shape.setRect(-100, -100, 0, 0);
	temp_pattern_rect.shape.setRect(-100, -100, 0, 0);
	buffer.clear();
	pattern_curve.clear();
	pattern_ellipse.clear();
	pattern_rect.clear();
	pattern_line.clear();
	points.clear();
	update();
}

void DrawWidget::slotDrawLine()
{
	if (flag["line"])
		flag["line"] = false;
	else
	{
		for (auto &it : flag)
			it.second = false;
		flag["line"] = true;
	}
	update();
}

void DrawWidget::slotDrawEllipse()
{
	if (flag["ellipse"])
		flag["ellipse"] = false;
	else
	{
		for (auto &it : flag)
			it.second = false;
		flag["ellipse"] = true;
	}
	update();
}


// 功能：撤销已经绘制的图形
void DrawWidget::slotCancel() {
	std::string temp_type;
	if (buffer.size() > 0)
	{
		temp_type = buffer.back();
		undo.push_back(temp_type);
		buffer.pop_back();
	}
	if (temp_type == "line")
	{
		undo_buffer.line.push_back(pattern_line.back());
		pattern_line.pop_back();
	}
	else if (temp_type == "ellipse")
	{
		undo_buffer.ellipse.push_back(pattern_ellipse.back());
		pattern_ellipse.pop_back();
	}
	else if (temp_type == "rect")
	{
		undo_buffer.rect.push_back(pattern_rect.back());
		pattern_rect.pop_back();
	}
	update();
}

// 功能：恢复撤销了的图形
void DrawWidget::slotUndo() {
	std::string temp_type;
	if (undo.size())
	{
		temp_type = undo.back();
		buffer.push_back(temp_type);
		undo.pop_back();

	}
	if (temp_type == "line")
	{
		pattern_line.push_back(undo_buffer.line.back());
		undo_buffer.line.pop_back();
	}

	else if (temp_type == "ellipse")
	{
		pattern_ellipse.push_back(undo_buffer.ellipse.back());
		undo_buffer.ellipse.pop_back();
	}
	else if (temp_type == "rect")
	{
		pattern_rect.push_back(undo_buffer.rect.back());
		undo_buffer.rect.pop_back();
	}
	update();
}


void DrawWidget::transmit(int width) {
	draw_width = width;
	temp_pattern_line_curve.width = draw_width;
	temp_pattern_rect.width = draw_width;
	temp_pattern_ellipse.width = draw_width;
}

DrawWidget::~DrawWidget()
{

}
