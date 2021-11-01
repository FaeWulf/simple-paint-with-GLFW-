#pragma once
//struct chứa các thuộc tính của hình
struct ShapeProperties {
	bool fillMode;
	bool dashedMode;
	int shapeMode;
	float thickness;
	float color[3];
};

float getPos(int pos, int maxPos);
