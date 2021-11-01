#pragma once
// khai báo các thư viện cần thiết
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>

#include "shape.h"
#include "dot.h"
#include "line.h"
#include "squad.h"
#include "triangle.h"
#include "circle.h"
#include "square.h"

#include "faewulfLib.h"
//class cursor dùng để xử lý input, và trả về các kết quả như shapeList chứa các hình in ra màn hình
class cursor {
private: 
	static int shapeMode, shapeID;
	static bool isOnApp, isHoldClick, lbuttonClick, isOnMenu, isEditMode;
	static float rootX, rootY, targetX, targetY;
	static shape* reviewShape;
	static ShapeProperties shapeProperties;
public:
	//shapeList chứa danh sách các hình đã vẽ
	static std::vector<shape*> shapeList;

	//constructor khởi tạo class
	cursor(GLFWwindow* window);

	//hàm set ShapeMode
	void setShapeMode(int);

	//hàm trả về ShapeMode
	int getShapeMode();

	//hàm set IsOnMenu
	void setIsOnMenu(bool i);

	//hàm set ShapeProperties
	void setProperties(ShapeProperties);

	//hàm lấy ShapeList
	static std::vector<shape*> getShapeList();

	//hàm lấy hình review trong lúc vẽ
	static shape* getReviewShape();

	//hàm trả về danh sách tên của các hình trong ShapeList
	static std::vector<std::string> shapeListForBoxList();

	//hàm set EditMode
	static void setEditMode(bool, int);
		
	//các hàm callback với mỗi loại event khác nhau, như đã liệt kê ở dòng 56, main.cpp
	static void windowSizeCallback(GLFWwindow* window, int width, int height);

	static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

	static void cursorEnterCallback(GLFWwindow* window, int entered);

	static void cursorButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

