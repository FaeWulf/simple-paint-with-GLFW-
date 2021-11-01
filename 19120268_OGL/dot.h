#pragma once
#include "shape.h"

//class dot kế thừa class shape
class dot : public shape {
public: 
	dot(float x1,float y1,float x2,float y2, ShapeProperties properties) {
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

	//khai hàm render cụ thể vẽ điểm 
	void render() {

		float vertic[] = {
			x1, y1, 0.0
		};

		//gán màu cho toạ độ
		GLfloat color[3];

		for (int i = 0; i < 1; i++) {
			color[i * 3] = this->shapeProperties.color[0];
			color[(i * 3) + 1] = this->shapeProperties.color[1];
			color[(i * 3) + 2] = this->shapeProperties.color[2];
		}

		//bắt đầu vẽ
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glPointSize(this->shapeProperties.thickness);
		glVertexPointer(3, GL_FLOAT, 0, vertic);
		glColorPointer(3, GL_FLOAT, 0, color);
		glDrawArrays(GL_POINTS, 0, 1);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

	}
};

