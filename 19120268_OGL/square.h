#pragma once
#include "shape.h"

class square : public shape {
public:
	square(float x1,float y1,float x2,float y2, ShapeProperties properties) {
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
		float x1, x2, x3, x4, y1, y2, y3, y4;

		float xlength, ylength;

		x1 = this->x1;
		y1 = this->y1;

		//để vẽ hình vuông, dùng phương pháp này để lấy cạnh dài nhất, và bắt đầu cộng toạ độ các đỉnh
		//theo 2 toạ độ đầu cuối và độ dài cạnh dài nhất

		xlength = abs(this->x1 - this->x2);
		ylength = abs(this->y1 - this->y2);
		float result;
		xlength < ylength ? result = ylength : result = xlength;

		/*
			^ y
			|	2	***************** 3
			|		*				*
			|		*				*
			|		*				*
			|	1	***************** 4
			|___________> x
		*/
		
		if (this->x1 < this->x2) {
			x3 = this->x1 + result;
			x4 = this->x1 + result;
		}
		else {
			x3 = this->x1 - result;
			x4 = this->x1 - result;
		}

		if (this->y1 < this->y2) {
			y2 = this->y1 + result;
			y3 = this->y1 + result;
		}
		else {
			y2 = this->y1 - result;
			y3 = this->y1 - result;
		}
		
		x2 = this->x1;
		y4 = this->y1;

		this->x2 = x3;
		this->y2 = y3;

		float vertic[] = {
			x1, y1, 0.0,
			x2, y2, 0.0,
			x3, y3, 0.0,
			x4, y4, 0.0,
			x1, y1, 0.0
		};

		// 4 dinh, +1 de danh cho fillmode
		//mảng màu
		GLfloat color[3 * 5];

		for (int i = 0; i  < 5; i++) {
			color[i * 3] = this->shapeProperties.color[0];
			color[(i * 3) + 1] = this->shapeProperties.color[1];
			color[(i * 3) + 2] = this->shapeProperties.color[2];
		}


		//vẽ hình
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_LINE_STIPPLE);

		glLineWidth(this->shapeProperties.thickness);
		this->shapeProperties.dashedMode ? glLineStipple(1, 0xE0E0) : glLineStipple(1, 0xFFFF);
		glVertexPointer(3, GL_FLOAT, 0, vertic);
		glColorPointer(3, GL_FLOAT, 0, color);
		this->shapeProperties.fillMode ? glDrawArrays(GL_QUADS, 0, 4) : glDrawArrays(GL_LINE_STRIP, 0, 5);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_LINE_STIPPLE);
	}
};

