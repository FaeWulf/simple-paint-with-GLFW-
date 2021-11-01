#pragma once
#include "shape.h"
//class line kế thừa class shape
class line : public shape {
public: 
	line(float x1,float y1,float x2,float y2, ShapeProperties properties) {
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
		this->backupX1 = x1;
		this->backupY1 = y1;
		this->backupX2 = x2;
		this->backupY2 = y2;
		this->shapeProperties = properties;
	}

	//hàm render cho vẽ đoạn thẳng
	void render() {

		// dựa vào toạ độ điểm đầu và cuối ta có thể dẽ dàng xác định được hình vẽ

		float vertic[] = {
			x1, y1, 0.0,
			x2, y2, 0.0,
		};

		//mảng màu cho 2 điểm 
		GLfloat color[6];

		for (int i = 0; i < 2; i++) {
			color[i * 3] = this->shapeProperties.color[0];
			color[(i * 3) + 1] = this->shapeProperties.color[1];
			color[(i * 3) + 2] = this->shapeProperties.color[2];
		}

		//vẽ hình
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_LINE_STIPPLE);

		glLineWidth(this->shapeProperties.thickness);
		glVertexPointer(3, GL_FLOAT, 0, vertic);
		glColorPointer(3, GL_FLOAT, 0, color);
		this->shapeProperties.dashedMode ? glLineStipple(1, 0xE0E0) : glLineStipple(1, 0xFFFF);
		glDrawArrays(GL_LINES, 0, 2);

		glDisable(GL_LINE_STIPPLE);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
};

