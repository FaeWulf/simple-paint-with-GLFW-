#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#include "faewulfLib.h"

//class shape là cha của các class con (là hình cụ thể)

class shape {
protected: 
	//toạ độ điểm đầu và điểm cuối
	float x1, x2, y1, y2;
	//cũng là toạ độ đầu và cuối, nhưng dùng để lưu lại cho edit mode, di chuyển hình
	float backupX1, backupY1, backupX2, backupY2;
	//thuộc tính của hình
	ShapeProperties shapeProperties;
public:
	//constructor
	shape() {
		x1 = NULL;
		x2 = NULL;
		y1 = NULL;
		y2 = NULL;
		backupX1 = NULL;
		backupY1 = NULL;
		backupX2 = NULL;
		backupY2 = NULL;
	}

	shape(float x1, float y1, float x2, float y2, ShapeProperties propeties) {
		this->x1 = x1;
		this->x2 = x1;
		this->y1 = y1;
		this->y2 = y2;
		this->backupX1 = x1;
		this->backupY1 = y1;
		this->backupX2 = x2;
		this->backupY2 = y2;
		this->shapeProperties = propeties;
	}

	//hàm dùng để di chuyển toạ độ của hình
	void moveTo(float x, float y) {
		this->x1 = backupX1 + x;
		this->y1 = backupY1 + y;
		this->x2 = backupX2 + x;
		this->y2 = backupY2 + y;
	}

	//hàm dùng để lưu lại toạ độ sau khi di chuyển
	void saveEdit() {
		backupX1 = this->x1;
		backupY1 = this->y1;
		backupX2 = this->x2;
		backupY2 = this->y2;

	}

	//trả về mảng chứa hệ toạ độ của hình
	std::vector<float> getPos() {
		std::vector<float> result;
		result.push_back(x1);
		result.push_back(y1);
		result.push_back(x2);
		result.push_back(y2);
		return result;
	}

	//trả về thuộc tính của hình
	ShapeProperties getShapeProperties() {
		return this->shapeProperties;
	}

	//hàm virtual render mặc định, từng class hình sẽ có kiểu render khác nhau
	virtual void render() {
		return;
	}
};

