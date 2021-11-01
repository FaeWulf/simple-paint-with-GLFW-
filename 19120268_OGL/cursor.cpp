#include "cursor.h"
//khởi tạo giá trị ban đầu
/*
* isOnApp		: Có đang trong cửa sổ chương trình hay không?
* isOnMenu		: Có đang trỏ vào menu setting hay không?
* isHoldClick	: Có đang giữ chuột trái hay không?
* lbuttonClick	: Có nhấn chuột trái hay không?
* isEditMode	: Đang là chế độ edit hay không?
* shapeMode		: loại hình vẽ  (0: chấm, 1: đường thẳng, 2: tam giác, 3: hình vuông, 4: tứ giác vuông, 5: hình tròn) 
* shapeID		: vị trí của hình trong shapeList
* rootX, rootY	: toạ độ điểm đầu
* targerX, targetY: toạ độ điểm cuối
* shapeList		: danh sách các hình đã vẽ
* reviewshape	: 
* shapeProperties: các thuộc tính của hình, như độ dày, chế độ fill hay outline, loại hình tròn, đường thẳng hay chấm.
*/
bool cursor::isOnApp = false;
bool cursor::isOnMenu = false;
bool cursor::isHoldClick = false;
bool cursor::lbuttonClick = false;
bool cursor::isEditMode = false;
int cursor::shapeMode = 0;
int cursor::shapeID = -1;
float cursor::rootX = NULL;
float cursor::rootY = NULL;
float cursor::targetX = NULL;
float cursor::targetY = NULL;
std::vector<shape*> cursor::shapeList;
shape* cursor::reviewShape = new shape();
ShapeProperties cursor::shapeProperties;

//constructor class
cursor::cursor(GLFWwindow* window) {
	isOnApp = false;
	cursor::shapeMode = 0;
}

//hàm set IsOnMenu
void cursor::setIsOnMenu(bool i) {
	cursor::isOnMenu = i;
}

//hàm set ShapeProperties
void cursor::setProperties(ShapeProperties properties) {
	cursor::shapeProperties = properties;
}

//hàm set ShapeMode
void cursor::setShapeMode(int mode) {
	cursor::shapeMode = mode;
}

// hàm trả về shapemode
int cursor::getShapeMode() {
	return cursor::shapeMode;
}

//hàm set editMode
void cursor::setEditMode(bool mode, int shapeID) {
	cursor::isEditMode = mode;
	cursor::shapeID = shapeID;
}

//hàm trả về hình review trong lúc vẽ
shape* cursor::getReviewShape() {
	return cursor::reviewShape;
}

//hàm call back cho event chuột ra vào màn hình chương trình 
void cursor::cursorEnterCallback(GLFWwindow* window, int entered) {
//	entered ? std::cout << "entered" << std::endl : std::cout << "exited" << std::endl;
	//dùng để set IsOnApp, dùng cho việc nếu kéo chuột ra khỏi màn hình sẽ kết thúc việc vẽ, tránh lỗi
	entered ? cursor::isOnApp = true : cursor::isOnApp = false;
}

//hàm call back cho event input từ nút trên chuột
void cursor::cursorButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	//nếu chuột đang trỏ vào Menu setting thì không thực hiện hàm	
	if (cursor::isOnMenu)
		return;
	
	// để check nếu chuột nhấn giữ chuột trái
	bool lbutton_down = false;

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (GLFW_PRESS == action)
			lbutton_down = true;
		else if (GLFW_RELEASE == action)
			lbutton_down = false;
	}

	
	// nếu nhấn giữ chuột trái thì biến IsHoldClick = true
	if (lbutton_down) {
		cursor::isHoldClick = true;
	} else {
		//nếu thả chuột trái thì thực hiện tính toán theo loại hình input 
		// Editmode hoặc drawmode
		cursor::isHoldClick = false;

		// nếu là editmode thì cập nhật vị trí mới của hình và thoát hàm
		if (cursor::isEditMode) {
			if (shapeID < 0 || shapeID > shapeList.size() - 1 || shapeList.size() == 0)
				return;
			shapeList[shapeID]->saveEdit();
			return;
		}

		
		// nếu không phải editMode, thì chính là mode vẽ, thực hiện vẽ hình theo input

		//khởi tạo class shape
		shape* temp;
		//dựa vào dữ liệu của shapeMode mà khai báo class hình cụ thể
		/*
			0: chấm, 
			1: đường thẳng, 
			2: tam giác, 
			3: hình vuông, 
			4: tứ giác vuông, 
			5: hình tròn
		*/
		switch (cursor::shapeProperties.shapeMode) {
		case 0: {
			temp = new dot(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 1: {
			temp = new line(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 2: {
			temp = new triangle(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 3: {
			temp = new square(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 4: {
			temp = new squad(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 5: {
			temp = new circle(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		default:
			temp = new line(rootX, rootY, targetX, targetY, cursor::shapeProperties);
			break;
		};

		//thêm vào shapeList, hình vẽ trong shapeList được render() trong hàm main dòng 205
		cursor::shapeList.push_back(temp);
	}
}

//hàm trả về shapeList
std::vector<shape*> cursor::getShapeList() {
	return cursor::shapeList;
}

//hàm callback cho event chuột di chuyển
void cursor::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
	int width, height;
	//lấy chiều dài chiều rộng của cửa sổ chương trình
	glfwGetWindowSize(window, &width, &height);

	// cập nhật toạ độ điểm cuối mỗi khi nhấn giữ kéo chuột
	cursor::targetX = getPos(xPos, width);
	cursor::targetY = -getPos(yPos, height);
	
	// reviewShape is for current mouse position

	if (cursor::isEditMode) {
		//nếu là chế độ edit, thì reviewShape sẽ là viền đỏ của hình được chọn để sửa
		if (shapeID >= 0 || shapeID <= shapeList.size() - 1 && shapeList.size() != 0) {
			//lấy hình dựa vào vị trí (shapeID) trong danh sách ShapeList
			auto currentEditShape = cursor::getShapeList()[cursor::shapeID];
			//lấy toạ độ của hình
			auto pos = currentEditShape->getPos();
			//nhập dữ liệu cho shapemode
			reviewShape = new squad(pos[0], pos[1], pos[2], pos[3], {
				false,
				true,
				4,
				5,
				{ 255, 0, 0 }
			});
		}
	}
	else {
		//nếu là chế độ vẽ thì tiến hành tạo hình vẽ review khi nhấn giữ chuột 

		//cũng vậy, tạo hình tương ứng như hình đang chọn để bắt đầu vẽ khi giữ kéo chuột

		switch (cursor::shapeProperties.shapeMode) {
		case 0: {
			reviewShape = new dot(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 1: {
			reviewShape = new line(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 2: {
			reviewShape = new triangle(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 3: {
			reviewShape = new square(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 4: {
			reviewShape = new squad(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		case 5: {
			reviewShape = new circle(rootX, rootY, targetX, targetY, cursor::shapeProperties);
		}
			  break;
		default:
			reviewShape = new line(rootX, rootY, targetX, targetY, cursor::shapeProperties);
			break;
		};
	};


	if (cursor::isHoldClick) {
	//nếu đang giữ chuột thì thực hiện kiểm tra có phải đang là chế độ edit hình không
		if (cursor::isEditMode) {
			//kiểm tra để vị trí của hình trong ShapeList luôn đúng, tránh bị lỗi chương trình
			if (shapeID < 0 || shapeID > shapeList.size() - 1 || shapeList.size() == 0)
				return;
			//di chuyển hình theo giữ chuột
			shapeList[shapeID]->moveTo(targetX - rootX, targetY - rootY);
		}

	}
	else {
		//nếu không phải giữ chuột
		//mỗi khi bắt đầu nhấn giữ chuột sẽ lấy vị trí toạ độ đầu tiên cho việc tính toán
		cursor::rootX = getPos(xPos, width);
		cursor::rootY = -getPos(yPos, height);
	}
}

//hàm callback event cửa sổ mỗi khi thay đổi kích thước cửa sổ
void cursor::windowSizeCallback(GLFWwindow* window, int width, int height) {
	std::cout << width << " " << height << std::endl;

	// keep the screen ratio scale with screen size 1:1
	glViewport(0, 0, width, height);
}

//hàm trả về danh sách tên các hình trong shapeList
std::vector<std::string> cursor::shapeListForBoxList() {
	const int size = cursor::shapeList.size();
	std::vector<std::string> strings;
	std::string shapeDisplay[] = {
		"Dot",
		"Line",
		"Triangle",
		"Square",
		"Squad",
		"Circle"
	};

	int count[] = {
		1, 1, 1, 1, 1, 1
	};

	for (int i = 0; i < cursor::shapeList.size(); i++) {
		std::stringstream ss;
		ss << shapeDisplay[shapeList[i]->getShapeProperties().shapeMode] << " #" << count[shapeList[i]->getShapeProperties().shapeMode]++;
		strings.push_back(ss.str());
	}

	return strings;
}
