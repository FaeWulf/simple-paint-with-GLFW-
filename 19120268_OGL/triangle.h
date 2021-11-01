#pragma once
#include "shape.h"
// kế thừa class shape
class triangle : public shape {
public: 

	triangle(float x1,float y1,float x2,float y2, ShapeProperties properties) {
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

 	void render() {
			
		//dựa vào toạ độ điểm đầu, cuối theo đường chéo
		//ta tính được toạ độ 3 đỉnh còn lại

		float x1, x2, x3, y1, y2, y3;

		x1 = this->x1;
		y1 = this->y1;

		x2 = this->x2;
		y2 = this->y1;

		/*
		*	y^
		*	 |		   * 3
		*	 |		  * *
		*	 |		 *   * 
		*	 |		*	  *
		*	 |    1********* 2
		*	 |
		*    |______________> x
		*/

	
		//toạ độ đỉnh tam giác sẽ là x = 1/2 khoảng cách giữa x1, x2
		//							y = khoảng cách của y1 và y2
		x3 = (this->x1 + this->x2) / 2;
		y3 = this->y2;

		//thực tế, để vẽ chúng ta cần 4 điểm, điểm đầu và điểm cuối sẽ trùng lên nhau để vẽ ra 1 hình toàn vẹn
		float vertic[] = {
			x1, y1, 0.0,
			x2, y2, 0.0,
			x3, y3, 0.0,
			x1, y1, 0.0
		};

		//mảng màu cho các đỉnh
		GLfloat color[3 * 4];

		for (int i = 0; i  < 4; i++) {
			color[i * 3] = this->shapeProperties.color[0];
			color[(i * 3) + 1] = this->shapeProperties.color[1];
			color[(i * 3) + 2] = this->shapeProperties.color[2];
		}

		glEnable(GL_LINE_STIPPLE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glLineWidth(this->shapeProperties.thickness);
		this->shapeProperties.dashedMode ? glLineStipple(1, 0xE0E0) : glLineStipple(1, 0xFFFF);
		glVertexPointer(3, GL_FLOAT, 0, vertic);
		glColorPointer(3, GL_FLOAT, 0, color);
		this->shapeProperties.fillMode ? glDrawArrays(GL_TRIANGLES, 0, 3) : glDrawArrays(GL_LINE_STRIP, 0, 4);

		glDisable(GL_LINE_STIPPLE);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
};

