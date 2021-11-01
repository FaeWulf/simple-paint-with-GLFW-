#include "faewulfLib.h"


//hàm trả về tỉ lệ giữa toạ độ điểm dựa theo độ dài màn hình
//vì chương trình đã dùng màn hình theo chế độ tỉ lệ x, y: từ -1 -> 1
float getPos(int pos, int maxPos)
{
	if (pos < 0)
		return -1.0f;
	else
		if (pos > maxPos)
			return 1.0f;
		else
			return (pos - (maxPos / 2)) * 1.0f / (maxPos / 2);
}