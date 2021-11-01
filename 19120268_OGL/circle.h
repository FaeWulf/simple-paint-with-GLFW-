#pragma once
#define _USE_MATH_DEFINES
#include "shape.h"
#include <math.h>

#include <iostream>
//class circle kế thừa class shape
class circle : public shape { 
public:
	//contructor
	circle(float x1,float y1,float x2,float y2, ShapeProperties properties) {
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


	//khai hàm render cụ thể vẽ hình tròn
	void render() {
		//sides tương ứng với 260 độ của hình tròn
		const int sides = 360;
		// vì sẽ sử dụng hệ các điểm để vẽ, nên để vẽ hoàn thiện hình tròn, điểm đầu phải trùng với điểm cuối -> +2 điểm
		const int vertices = sides + 2;
		
		//toạ độ tâm
		float x = this->x1;
		float y = this->y1;
		float z = 0;
		//dựa vào toạ độ đầu, cuối để tính bán kính
		float radius = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
		//số pi
		float doublePi = 2.0f * M_PI;
		
		//mảng hệ toạ độ các điểm thuộc đường tròn
		float xCords[vertices];
		float yCords[vertices];
		float zCords[vertices];

		xCords[0] = x;
		yCords[0] = y;
		zCords[0] = z;
	
		//chạy góc từ 0 -> 360, dựa vào giá trị của góc ta có toạ độ của điểm sẽ được tính ra
		// bằng toạ độ gốc + ( dựa vào công thức lương giác và bán kính sẽ tính ra khoảng x', y' )
		for (int i = 0; i < vertices; i++) {
			xCords[i] = x + (radius * cos(doublePi  * i / sides));
			yCords[i] = y + (radius * sin(doublePi  * i / sides));
			zCords[i] = z;
		}
		// tạo mảng color chứa giá trị màu cho các điểm
		// tạo mảng vertic chứa toạ độ xyz các điểm 
		float vertic[vertices * 3];
		float color[vertices * 3];
		for (int i = 0; i  < vertices; i++) {
			vertic[i * 3] = xCords[i];
			vertic[(i * 3) + 1] = yCords[i];
			vertic[(i * 3) + 2] = zCords[i];

			color[i * 3] = this->shapeProperties.color[0];
			color[(i * 3) + 1] = this->shapeProperties.color[1];
			color[(i * 3) + 2] = this->shapeProperties.color[2];
		}

		// bắt đầu vẽ 
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_LINE_STIPPLE);
		//chế độ vẽ nét đứt hoặc nét liền
		this->shapeProperties.dashedMode ? glLineStipple(1, 0xE0E0) : glLineStipple(1, 0xFFFF);

		//dộ dày nét
		glLineWidth(this->shapeProperties.thickness);

		glColorPointer(3, GL_FLOAT, 0, color);
		glVertexPointer(3, GL_FLOAT, 0, vertic);

		//fill hay vẽ viền
		this->shapeProperties.fillMode ? glDrawArrays(GL_TRIANGLE_FAN, 0, vertices) : glDrawArrays(GL_LINE_STRIP, 0, vertices);

		glDisable(GL_LINE_STIPPLE);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
};

