/*
	MSSV: 19120268
	HCMUS 19CTT2
*/

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

//classes
#include "cursor.h"
#include "shape.h"
#include "line.h"
#include "squad.h"
#include "triangle.h"
#include "circle.h"

#define windowWidth 900
#define windowHeight 900


void main() {

	// khởi tạo thư viện glfw
	if (!glfwInit()) {
		std::cout << "Cannot Init gl";
	};

	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// khởi tạo cửa sổ chương trình
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL paint - 19120268 - by faewulf", NULL, NULL);

	// kiểm tra nếu xảy ra lỗi trong lúc tạo của sổ chương trình thì thoát chương trình
	if (window == NULL) {
		std::cout << "error while creating window.";
		glfwTerminate();
	}

	// gán cửa sổ cho thư viện glfw
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// khởi tạo ImGui, dùng để tạo giao diện menu setting
	// imGui things
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// khởi tạo class cursor 
	cursor* appCursor = new cursor(window);

	// khởi tạo các hàm trả về cho các loại sự kiện của glfw
	//event thay đổi kích thước của sổ chương trình
	glfwSetWindowSizeCallback(window, appCursor->windowSizeCallback);

	// event khi chuột di chuyển
	glfwSetCursorPosCallback(window,appCursor->cursorPositionCallback);

	// event khi chuột đang ở trong của sổ chương trình
	glfwSetCursorEnterCallback(window, appCursor->cursorEnterCallback);

	// event khi có input nút từ chuột
	glfwSetMouseButtonCallback(window, appCursor->cursorButtonCallback);
	
	//dùng để bình thường hoá lại toạ độ x, y trong màn hình chương trình
	glViewport(0, 0, windowWidth, windowHeight);

	/*  khai báo các biến
	*	thickness, dùng để lấy độ dày 	 
	*	shapeMode là dạng hình học cần vẽ (0: chấm, 1: đường thẳng, 2: tam giác, 3: hình vuông, 4: tứ giác vuông, 5: hình tròn) 
	*	fillMode: vẽ chỉ viền hay đặc
	*	dashedMode: chế độ đường kẻ
	*	editMode: chế độ chỉnh sửa
	*	selectedObject, dùng để chọn vị trí của hình vẽ trong danh sách các hình vẽ
	*	shapeDisplay dùng để chứa tên các dạng hình
	*/
	int thickness = 1;
	float color[] = { 1,1,1 };
	int shapeMode = 0;
	bool fillMode = true;
	bool dashedMode = false;
	bool editMode = false;
	int selectedObject = -1;
	std::string shapeDisplay[] = {
		"Dot",
		"Line",
		"Triangle",
		"Square",
		"Squad",
		"Circle"
	};


	//vòng lặp cho đến khi người dùng đóng của sổ chương trình
	while (!glfwWindowShouldClose(window)) {

		//xoá hết các dữ liệu trên màn hình
		glClear(GL_COLOR_BUFFER_BIT);

		//render things

		// đây là phần khởi tạo menu setting
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Options");
		{
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			ImGui::Text("Current shape: "); ImGui::SameLine();
			ImGui::Text(shapeDisplay[shapeMode].c_str());
			ImGui::Dummy(ImVec2(0.0f, 10.0f));

			//tạo các nút chọn loại hình vẽ
			if (ImGui::Button("Dot", ImVec2(75,20))) shapeMode = 0; ImGui::SameLine();
			if (ImGui::Button("Line", ImVec2(75,20))) shapeMode = 1;ImGui::SameLine();
			if (ImGui::Button("Triangle", ImVec2(75,20))) shapeMode = 2;ImGui::SameLine();
			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			if (ImGui::Button("Square", ImVec2(75,20))) shapeMode = 3;ImGui::SameLine();
			if (ImGui::Button("Squad", ImVec2(75,20))) shapeMode = 4;ImGui::SameLine();
			if (ImGui::Button("Circle", ImVec2(75,20))) shapeMode = 5;ImGui::SameLine();

			//tạo nút bật tắt các chế độ Fill, dash outline
			ImGui::Dummy(ImVec2(0.0f, 40.0f));
			ImGui::Checkbox("Fill mode", &fillMode);
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			ImGui::Checkbox("Dashed outline mode", &dashedMode);
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			// tạo thanh kéo lấy giá trị gán vào biến thickness
			ImGui::Text("Thickness");
			ImGui::SliderInt("", &thickness, 1, 30);
			ImGui::Dummy(ImVec2(0.0f, 10.0f));

			// tạo bảng lấy màu
			ImGui::Text("Color");
			ImGui::ColorEdit3("", color);
			ImGui::Dummy(ImVec2(0.0f, 10.0f));

			//tạo nút undo draw, pop phần tử cuối cùng trong mảng shapeList
			if (ImGui::Button("Undo draw")) {
				if(appCursor->getShapeList().size() > 0)
					appCursor->shapeList.pop_back();
				selectedObject = -1;
			}

			// tạo nút bật tắt edit toạ độ các hình vẽ
			ImGui::Dummy(ImVec2(0.0f, 10.0f));
			ImGui::Checkbox("Edit mode", &editMode);
			
			//lấy danh sách tên các hình vẽ cho vào vector string
			std::vector<std::string> vectorString = appCursor->shapeListForBoxList();
			// khai báo biến char** dùng để chứa tên các hình vẽ
			char** list = (char**)malloc(sizeof(char*) * (vectorString.size() + 1));

			//gán tên vào list
			for (size_t i = 0; i < vectorString.size(); ++i)
				list[i] = _strdup(vectorString[i].c_str());
			list[vectorString.size()] = nullptr;

			// tạo danh sách các hình đã vẽ, có thể chọn để dùng trong chế độ sủa hoặc xoá đi hình
			ImGui::Text("Objects List");
			ImGui::ListBox("", &selectedObject, list, appCursor->getShapeList().size(), 4);
			// tạo nút xoá hình trong Shapelist
			if (ImGui::Button("Delete selected object")) {
				if (selectedObject >= 0 && selectedObject <= appCursor->getShapeList().size() - 1 && appCursor->getShapeList().size() != 0)
					appCursor->shapeList.erase(appCursor->shapeList.begin() + selectedObject);
				selectedObject = -1;
			};
			//giải phóng bộ nhớ từ biến list sau khi dùng xong để tránh bị memory leak
			for (size_t i = 0; i < vectorString.size(); ++i)
				free(list[i]);
			free(list);
	
			//căn lề cho cửa sổ menu
			ImGuiStyle* style = &ImGui::GetStyle();
			style->WindowTitleAlign = ImVec2(0.5, 0.5);
		}
		ImGui::End();

		//tạo struct ShapeProperties rồi gán dữ liệu lấy được từ menu ImGui trên
		ShapeProperties properties;
		properties.thickness = thickness;
		properties.color[0] = color[0];
		properties.color[1] = color[1];
		properties.color[2] = color[2];
		properties.shapeMode = shapeMode;
		properties.fillMode = fillMode;
		properties.dashedMode = dashedMode;
	
		//cập nhật dữ liệu vào appCursor
		appCursor->setEditMode(editMode, selectedObject);
		appCursor->setProperties(properties);
		//kiểm tra xem con chuột đang dùng menu hay không, để tránh trường hợp vẽ hình trong khi đang
		//thao tác với menu
		appCursor->setIsOnMenu(io.WantCaptureMouse);


		//gọi hàm render của tất cả các hình được lưu trong ShapeList
		for (auto v : appCursor->getShapeList()) {
			v->render();
		}

		//gọi hàm vẽ hình review khi đang kéo vẽ, hoặc hàm vẽ khung đỏ cho chế độ edit
		appCursor->getReviewShape()->render();

		// vẽ menu
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	//thoát chương trình

	//xoá ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	//xoá glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}