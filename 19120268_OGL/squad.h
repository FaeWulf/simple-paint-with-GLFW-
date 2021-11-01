#pragma once
#include "shape.h"
//class squad kế thừa class shape
class squad : public shape {
public:
	squad(float x1,float y1,float x2,float y2, ShapeProperties properties) {
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
		//toạ độ 4 đỉnh
		float x1, x2, x3, x4, y1, y2, y3, y4;

		//dựa vào toạ độ 2 đỉnh chéo ta có thể suy ra toạ độ 4 đỉnh

		/*	^ y
			|	2	***************** 3
			|		*				*
			|		*				*
			|		*				*
			|	1	***************** 4
			|___________> x
		*/
		x1 = this->x1;
		y1 = this->y1;

		x2 = this->x1;
		y2 = this->y2;

		x3 = this->x2;
		y3 = this->y2;

		x4 = this->x2;
		y4 = this->y1;

		float vertic[] = {
			x1, y1, 0.0,
			x2, y2, 0.0,
			x3, y3, 0.0,
			x4, y4, 0.0,
			x1, y1, 0.0
		};

		// 4 dinh, +1 de danh cho fillmode
		GLfloat color[3 * 5];

		for (int i = 0; i  < 5; i++) {
			color[i * 3] = this->shapeProperties.color[0];
			color[(i * 3) + 1] = this->shapeProperties.color[1];
			color[(i * 3) + 2] = this->shapeProperties.color[2];
		}


		// vẽ hình
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

