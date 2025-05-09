#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <random>
#include <chrono>
#include <iostream>
#include <cfloat>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "memory.h"
#include <GL/glew.h>   // 包含GLEW头文件
#include <GL/gl.h>     // 包含OpenGL头文件
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <GL/glut.h>
#include <sstream>
#include <iomanip>

using namespace std;

// 定义wt类
Memory wt_mem;
// 矩阵数组
float matrix[16];

// 屏幕和窗口尺寸
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
// 点尺寸
const int POINT_SIZE = 6;

// 玩家结构体
struct PlayerValues
{
	std::string play_id = "Unknow";
	std::string vehicle_id = "Unknow";
    std::string type = "Unknow";
    int vehicle_type = 1;
	uint32_t reload = 0;
	uint32_t team = 0;
	uint32_t state = 4;
	uint32_t protect = 0;
	float player_x = 0;
	float player_y = 0;
	float player_z = 0;
	float rotation[9];
	float bbmin[3];
	float bbmax[3];
	//float bbcenter[3];

	float super_time = 0;//无敌时间
};
// 屏幕坐标结构体
struct View
{
	int draw_x = -1;
	int draw_y = -1;
	int draw_z = -1;
};
// 64字节字符串
union Int256 
{
	struct 
	{
		uint64_t lower_lower = 0;
		uint64_t lower_upper = 0;
		uint64_t upper_lower = 0;
		uint64_t upper_upper = 0;
	};
	uint64_t value[4];
};
// 颜色结构体
struct Color
{
	float R;
	float G;
	float B;
};
// 载具类型
struct Type
{
    std::string type_1 = "exp_bomber";
    std::string type_2 = "exp_assault";
    std::string type_3 = "exp_fighter";
    std::string type_4 = "exp_SPAA";
    std::string type_5 = "exp_helicopter";
};

bool active = true;
uint64_t aces_base; //aces.exe base-address
//TriggerBot Settings
bool trigger_t = false; //to exit thread
bool trigger_bot_enable = true;	//triggerbot key down

int RandomInt(int max, int min) {
    int result = min + rand() % (max - min + 1);
    return result;
}

// 玩家ID读取
std::string playerName(uint64_t playerData)
{
	uint64_t playerID_1, playerID_2, playerID_3, playerID_4;
	wt_mem.ReadData<uint64_t>(playerData + offset::PLAYER_ID, playerID_1);
	wt_mem.ReadData<uint64_t>(playerData + offset::PLAYER_ID + 0x8, playerID_2);
	wt_mem.ReadData<uint64_t>(playerData + offset::PLAYER_ID + 0x10, playerID_3);
	wt_mem.ReadData<uint64_t>(playerData + offset::PLAYER_ID + 0x18, playerID_4);

	//将 4 个 64 位 long long int 的值连接成一个 256 位变量并存储
	Int256 combined;
	combined.lower_lower = playerID_1;
	combined.lower_upper = playerID_2;
	combined.upper_lower = playerID_3;
	combined.upper_upper = playerID_4;

	//重解释转换
	std::string id(reinterpret_cast<char*>(&combined), sizeof(combined));

	return id;
}

// 载具型号读取
std::string vehicleName(uint64_t vehicleID)
{
	uint64_t vehicleID_1, vehicleID_2, vehicleID_3, vehicleID_4;
	wt_mem.ReadData<uint64_t>(vehicleID, vehicleID_1);
	//std::cout << "[Info]vehicleID_1 Out Base: " << std::hex << vehicleID_1 << std::endl;
	wt_mem.ReadData<uint64_t>(vehicleID + 0x8, vehicleID_2);
    //std::cout << "[Info]vehicleID_2 Out Base: " << std::hex << vehicleID_2 << std::endl;
	wt_mem.ReadData<uint64_t>(vehicleID + 0x10, vehicleID_3);
	wt_mem.ReadData<uint64_t>(vehicleID + 0x18, vehicleID_4);

	//将 4 个 64 位 long long int 的值连接成一个 256 位变量并存储
	Int256 combined;
	combined.lower_lower = vehicleID_1;
	combined.lower_upper = vehicleID_2;
	combined.upper_lower = vehicleID_3;
	combined.upper_upper = vehicleID_4;

	//重解释转换
	std::string vehicle(reinterpret_cast<char*>(&combined), sizeof(combined));

	//std::cout << "vehicle_ID: " << vehicle.c_str() << std::endl;

	const char* vehicle_id = vehicle.c_str();
	std::string newString;
	int index = 0;
	while (vehicle_id[index] != '\0') 
	{
		char currentChar = vehicle_id[index];
		// 将字符添加到新的字符串中
		newString += currentChar;
		index++;
	}

	//std::cout << newString << std::endl;
	return newString;
}

// 载具类型判断
int playerVehicleType(std::string vehicle_type)
{
    Type type;
    if(vehicle_type == type.type_1)
    {
        return 2;
    }
    else if(vehicle_type == type.type_2)
    {
        return 2;
    }
    else if(vehicle_type == type.type_3)
    {
        return 2;
    }
    else if(vehicle_type == type.type_4)
    {
        return 3;
    }
    else if(vehicle_type == type.type_5)
    {
        return 4;
    }
    else
    {
        return 1;
    }
}

// 遍历玩家数据
PlayerValues playerValues(uint64_t aces, int number, int localplayer)
{
	PlayerValues data;
	uint64_t playerData;
    uint64_t vehicle_data;
	uint64_t vehicleID;
    uint64_t vehicleType;
	// 进入玩家列表
	//wt_mem.ReadData<long int>(offset_wt::dwLocalPlayer + aces_base, localplayer_wt_1);
	//wt_mem.ReadData<uint64_t>(offset::OFFSET_START + aces + offset::LOCAL_PLAYER, playerData);
	//printf("[Info]localplayer Out Base: %lp\n", playerData);
	//如果索引值小于0，则取绝对值
	//playerData = abs(playerData);

	//进入本地玩家列表或者全部实体列表
	if(localplayer == 1)
	{
		wt_mem.ReadData<uint64_t>(offset::OFFSET_START + aces + offset::LOCAL_PLAYER, playerData);
	}
	else
	{
		wt_mem.ReadData<uint64_t>(offset::OFFSET_START + aces + offset::PLAYER_LIST, playerData);
	}
	//printf("[Info]localplayer Out Base: %lp\n", playerData);


	// 进入玩家的堆
	//wt_mem.ReadData<long int>(localplayer_wt_1, localplayer_wt_1);
	if(localplayer == 0)
	{
		wt_mem.ReadData<uint64_t>(playerData + (offset::PLAYER_OFFSET * number), playerData);
	}
	//wt_mem.ReadData<uint64_t>(playerData, playerData);
	//printf("[Info]localplayer In Base: %lp\n", playerData);

	// 玩家ID
	//wt_mem.ReadData<long int>(playerData + offset::PLAYER_ID, playerID);
	data.play_id = playerName(playerData);

	// 玩家数据指针
    // 进入玩家数据列表
	wt_mem.ReadData<uint64_t>(playerData + offset::PLAYER_DATA, playerData);
    //std::cout << "[Info]PlayerData In Base: " << playerData << std::endl;

	// 载具数据
	//wt_mem.ReadData<uint64_t>(playerData + offset::PLAYER_ID, vehicleID);
	wt_mem.ReadData<uint64_t>(playerData + offset::VEHICLE_DATA, vehicle_data);
    //std::cout << "vehicle_data: " << std::hex <<  vehicle_data << std::endl;
    // 载具ID
    wt_mem.ReadData<uint64_t>(vehicle_data + offset::VEHICLE_ID, vehicleID);
    //std::cout << "vehicleID: " << std::hex <<  vehicleID << std::endl;
	data.vehicle_id = vehicleName(vehicleID);
    // 载具类型
    wt_mem.ReadData<uint64_t>(vehicle_data + offset::VEHICLE_TYPE, vehicleType);
	data.type = vehicleName(vehicleType);
    data.vehicle_type = playerVehicleType(data.type);
    //std::cout << "vehicleType: " << data.type << std::endl;

	// 玩家单位旋转矩阵
	uint32_t float_data;
	for (int i = 0; i < 9; i++)
	{
		wt_mem.ReadFloat<uint32_t>(playerData + offset::ROTATION + (offset::LOCATION_OFFSET * i), float_data);
		float* data_p = reinterpret_cast<float*>(&float_data);
		float value = *data_p;
		//std::cout << value << std::endl;
		data.rotation[i] = value;
	}

	//BBMin
	for (int i = 0; i < 3; i++)
	{
		wt_mem.ReadFloat<uint32_t>(playerData + offset::BBMIN + (offset::LOCATION_OFFSET * i), float_data);
		float* data_p = reinterpret_cast<float*>(&float_data);
		float value = *data_p;
		//std::cout << value << std::endl;
		data.bbmin[i] = value;
	}
	//BBMax
	for (int i = 0; i < 3; i++)
	{
		wt_mem.ReadFloat<uint32_t>(playerData + offset::BBMAX+ (offset::LOCATION_OFFSET * i), float_data);
		float* data_p = reinterpret_cast<float*>(&float_data);
		float value = *data_p;
		//std::cout << value << std::endl;
		data.bbmax[i] = value;
	}

	// 玩家坐标
	uint32_t x, z, y;
	wt_mem.ReadFloat<uint32_t>(playerData + offset::LOCATION, x);
	wt_mem.ReadFloat<uint32_t>(playerData + offset::LOCATION + offset::LOCATION_OFFSET, y);
	wt_mem.ReadFloat<uint32_t>(playerData + offset::LOCATION + (offset::LOCATION_OFFSET * 2), z);
	// 重解释转换
	float* x1 = reinterpret_cast<float*>(&x);
	float* y1 = reinterpret_cast<float*>(&y);
	float* z1 = reinterpret_cast<float*>(&z);
	data.player_x = *x1;
	data.player_y = *y1;
	data.player_z = *z1;

	uint32_t hex8 = 0;

	// 装填状态
	wt_mem.ReadFloat<uint32_t>(playerData + offset::RELOAD, hex8);
	// 将team转换为一个指向字节的指针
    uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&hex8);
    // 提取最前端的一个字节
    uint8_t frontByte = *bytePtr;
    // 输出提取的字节的十六进制表示
    data.reload = frontByte;

	// 无敌时间
	wt_mem.ReadFloat<uint32_t>(playerData + offset::SUPER_TIME, float_data);
	// 重解释转换
	float* st = reinterpret_cast<float*>(&float_data);
	data.super_time = *st;

	// 无敌状态
	wt_mem.ReadFloat<uint32_t>(playerData + offset::PROTECT, hex8);
	// 将team转换为一个指向字节的指针
    bytePtr = reinterpret_cast<uint8_t*>(&hex8);
    // 提取最前端的一个字节
    frontByte = *bytePtr;
    // 输出提取的字节的十六进制表示
    data.protect = frontByte;

	// 玩家状态
	wt_mem.ReadFloat<uint32_t>(playerData + offset::PLAYER_STATE, hex8);
	// 将team转换为一个指向字节的指针
    bytePtr = reinterpret_cast<uint8_t*>(&hex8);
    // 提取最前端的一个字节
    frontByte = *bytePtr;
    // 输出提取的字节的十六进制表示
    data.state = frontByte;

	// 玩家队伍
	wt_mem.ReadFloat<uint32_t>(playerData + offset::TEAM, hex8);
	// 将team转换为一个指向字节的指针
    bytePtr = reinterpret_cast<uint8_t*>(&hex8);
    // 提取最前端的一个字节
    frontByte = *bytePtr;
    // 输出提取的字节的十六进制表示
    data.team = frontByte;

	return data;
}

// 玩家矩阵
void ViewMatrix(uint64_t aces, float* matrix)
{	
	uint32_t data;
	for (int i = 0; i < 16; i++)
	{
		wt_mem.ReadFloat<uint32_t>(aces + offset::MATRIX +(offset::LOCATION_OFFSET * i), data);
		float* data_p = reinterpret_cast<float*>(&data);
		float value = *data_p;
		//std::cout << value << std::endl;
		matrix[i] = value;
	}
}

// 矩阵计算
View WorldtoScreen(float* matrix, PlayerValues player, int screen_length, int screen_height)
{
	View out;
	// 不绘制无坐标玩家
	if (player.player_x == 0.0f && player.player_y == 0.0f && player.player_z == 0.0f)
	{
		out.draw_x = -1;
		out.draw_y = -1;
		return out;
	}
	// 后方绘制避免
	float screen_z = matrix[3] * player.player_x + matrix[7] * player.player_y + matrix[11] * player.player_z + matrix[15];
	if (screen_z <= 0.1f)
	{
		out.draw_x = -1;
		out.draw_y = -1;
		return out;
	}

	const float inv_width = 1.0f / screen_z;
	out.draw_x = (screen_length / 2) * (player.player_x * matrix[0] + player.player_y * matrix[4] + player.player_z * matrix[8] + matrix[12]) * inv_width + (screen_length / 2);
	out.draw_y = -(screen_height / 2) * (player.player_x * matrix[1] + player.player_y * matrix[5] + player.player_z * matrix[9] + matrix[13]) * inv_width + (screen_height / 2);
	out.draw_z = (player.player_x * matrix[2] + player.player_y * matrix[6] + player.player_z * matrix[8] + matrix[12]) * inv_width;

	return out;
}

// 距离计算
void Distance(PlayerValues player, PlayerValues enemy,std::string* result, float* distance)
{
	*distance = std::sqrt(std::pow(enemy.player_x - player.player_x, 2) + 
		std::pow(enemy.player_y - player.player_y, 2) + std::pow(enemy.player_z - player.player_z, 2));
	
	// 距离换算为Km
	*distance /= 1000.0;
	std::ostringstream dis;
    dis << std::fixed << std::setprecision(2) << *distance;
	// 距离字符串result
    *result = dis.str();
}

// 颜色判断
Color color(float distance, int player_type, int enemy_type)
{
    // 2 飞机
    // 3 AA
    // 4 直升机
    // 1 Tank
    Color draw;
    // 如果玩家plane，敌方plane || helicopter，敌方plane
    if((player_type == 2 && enemy_type == 2) || (player_type == 4 && enemy_type == 2))
	{
        // 黄色（Yellow）：(1, 1, 0)
        draw.R = 1.0f;
		draw.G = 1.0f;
		draw.B = 0.0f;
    }
    // 如果玩家AA，敌方plane || 玩家helicopter，敌方tank || 玩家plane，敌方tank || 玩家tank，敌方plane
    else if((player_type == 3 && enemy_type == 2) || 
            (player_type == 4 && enemy_type == 1) ||
            (player_type == 2 && enemy_type == 1) ||
            (player_type == 1 && enemy_type == 2))
	{
        // 青色（Cyan）：(0, 1, 1)
        draw.R = 0.0f;
		draw.G = 1.0f;
		draw.B = 1.0f;
    }
    // 如果玩家AA，敌方helicopter || 玩家helicopter，敌方AA || plane，敌方AA
    else if((player_type == 3 && enemy_type == 4) || 
        	(player_type == 4 && enemy_type == 3) || 
        	(player_type == 2 && enemy_type == 3))
	{
        // 红色（Red）：(1, 0, 0)
        draw.R = 1.0f;
		draw.G = 0.0f;
		draw.B = 0.0f;
    }
    else
    {
        if(distance <= 0.1f)
		{
		// 红色（Red）：(1, 0, 0)
		draw.R = 1.0f;
		draw.G = 0.0f;
		draw.B = 0.0f;
		}
		else if(0.1f < distance && distance <= 2.0f)
		{
		// 黄色（Yellow）：(1, 1, 0)
		draw.R = 1.0f;
		draw.G = distance/2;
		draw.B = 0.0f;
		}
		else if(2.0f < distance && distance <= 4.0f)
		{
		// 绿色（Green）：(0, 1, 0)
		draw.R = (4.0f - distance)/2;
		draw.G = 1.0f;
		draw.B = 0.0f;
		}
		else if(4.0f < distance && distance <= 6.0f)
		{
		// 青色（Cyan）：(0, 1, 1)
		draw.R = 0.0f;
		draw.G = 1.0f;
		draw.B = (distance - 4.0f)/2;
		}
		else
		{
		// 青色（Cyan）：(0, 1, 1)
		draw.R = 0.0f;
		draw.G = 1.0f;
		draw.B = 1.0f;
		}
    }
    /*
	红色（Red）：(1, 0, 0)
	绿色（Green）：(0, 1, 0)
	蓝色（Blue）：(0, 0, 1)
	黄色（Yellow）：(1, 1, 0)
	青色（Cyan）：(0, 1, 1)
	品红（Magenta）：(1, 0, 1)
	白色（White）：(1, 1, 1)
	黑色（Black）：(0, 0, 0)
	灰色（Gray）：(0.5, 0.5, 0.5)
	*/
	return draw;
}

// 矩形体绘制
struct Vector3
{
	float x, y, z;
};
Vector3 Scale(float rotation_1, float rotation_2, float rotation_3, float bb)
{
	Vector3 ax;
	ax.x = rotation_1 * bb;
	ax.y = rotation_2 * bb;
	ax.z = rotation_3 * bb;
	// std::cout << "ax.x" << ax.x << std::endl;
	// std::cout << "ax.y" << ax.y << std::endl;
	// std::cout << "ax.z" << ax.z << std::endl;
	return ax;
}
Vector3 Add(Vector3 temp, Vector3 ax)
{
	Vector3 result;
	result.x = temp.x + ax.x;
	result.y = temp.y + ax.y;
	result.z = temp.z + ax.z;
	// std::cout << "temp.x " << temp.x << std::endl;
	// std::cout << "ax.x " << ax.x << std::endl;
	// std::cout << "result.x " << result.x << std::endl;

	// std::cout << "temp.y " << temp.y << std::endl;
	// std::cout << "ax.y " << ax.y << std::endl;
	// std::cout << "result.y " << result.y << std::endl;

	// std::cout << "temp.z " << temp.z << std::endl;
	// std::cout << "ax.z " << ax.z << std::endl;
	// std::cout << "result.z " << result.z << std::endl;
	return result;
}
// 矩阵计算
View PointtoScreen(float* matrix, Vector3 point, int screen_length, int screen_height)
{
	View out;
	// 不绘制无坐标玩家
	if (point.x == 0.0f && point.y == 0.0f && point.z == 0.0f)
	{
		out.draw_x = -1;
		out.draw_y = -1;
		return out;
	}
	// 后方绘制避免
	float screen_z = matrix[3] * point.x + matrix[7] * point.y + matrix[11] * point.z + matrix[15];
	if (screen_z <= 0.1f)
	{
		out.draw_x = -1;
		out.draw_y = -1;
		return out;
	}

	const float inv_width = 1.0f / screen_z;
	out.draw_x = (screen_length / 2) * (point.x * matrix[0] + point.y * matrix[4] + point.z * matrix[8] + matrix[12]) * inv_width + (screen_length / 2);
	out.draw_y = -(screen_height / 2) * (point.x * matrix[1] + point.y * matrix[5] + point.z * matrix[9] + matrix[13]) * inv_width + (screen_height / 2);
	out.draw_z = (point.x * matrix[2] + point.y * matrix[6] + point.z * matrix[8] + matrix[12]) * inv_width;

	return out;
}
View* DrawBox(PlayerValues enemy, float* matrix, int screen_length, int screen_height)
{
	Vector3 ax[6];
	ax[0] = Scale(enemy.rotation[0], enemy.rotation[1], enemy.rotation[2], enemy.bbmin[0]);
	ax[1] = Scale(enemy.rotation[3], enemy.rotation[4], enemy.rotation[5], enemy.bbmin[1]);
	ax[2] = Scale(enemy.rotation[6], enemy.rotation[7], enemy.rotation[8], enemy.bbmin[2]);
	ax[3] = Scale(enemy.rotation[0], enemy.rotation[1], enemy.rotation[2], enemy.bbmax[0]);
	ax[4] = Scale(enemy.rotation[3], enemy.rotation[4], enemy.rotation[5], enemy.bbmax[1]);
	ax[5] = Scale(enemy.rotation[6], enemy.rotation[7], enemy.rotation[8], enemy.bbmax[2]);
	// for (int i = 0; i < 6; i++) 
	// {
	// 	std::cout << "ax[" << i << "].x " << ax[i].x << std::endl;
	// 	std::cout << "ax[" << i << "].y " << ax[i].y << std::endl;
	// 	std::cout << "ax[" << i << "].z " << ax[i].z << std::endl;
	// }

	Vector3 temp[7];
	temp[6].x = enemy.player_x;
	temp[6].y = enemy.player_y;
	temp[6].z = enemy.player_z;
	// temp[0] = temp[6] + ax[2];
	// temp[1] = temp[6] + ax[5];
	// temp[2] = temp[0] + ax[3];
	// temp[3] = temp[1] + ax[3];
	// temp[4] = temp[0] + ax[0];
	// temp[5] = temp[1] + ax[0];
	temp[0] = Add(temp[6], ax[2]);
	temp[1] = Add(temp[6], ax[5]);
	temp[2] = Add(temp[0], ax[3]);
	temp[3] = Add(temp[1], ax[3]);
	temp[4] = Add(temp[0], ax[0]);
	temp[5] = Add(temp[1], ax[0]);

	Vector3 v[8];
	// v[0] = temp[2] + ax[1];
	// v[1] = temp[2] + ax[4];
	// v[2] = temp[3] + ax[4];
	// v[3] = temp[3] + ax[1];
	// v[4] = temp[4] + ax[1];
	// v[5] = temp[4] + ax[4];
	// v[6] = temp[5] + ax[4];
	// v[7] = temp[5] + ax[1];
	v[0] = Add(temp[2], ax[1]);
	v[1] = Add(temp[2], ax[4]);
	v[2] = Add(temp[3], ax[4]);
	v[3] = Add(temp[3], ax[1]);
	v[4] = Add(temp[4], ax[1]);
	v[5] = Add(temp[4], ax[4]);
	v[6] = Add(temp[5], ax[4]);
	v[7] = Add(temp[5], ax[1]);
	// for (int i = 0; i < 8; i++) 
	// {
	// 	std::cout << "v[" << i << "].x " << v[i].x << std::endl;
	// 	std::cout << "v[" << i << "].y " << v[i].y << std::endl;
	// 	std::cout << "v[" << i << "].z " << v[i].z << std::endl;
	// }

	View* point = new View[8];
	point[0] = PointtoScreen(matrix, v[0], screen_length, screen_height);
	point[1] = PointtoScreen(matrix, v[1], screen_length, screen_height);
	point[2] = PointtoScreen(matrix, v[2], screen_length, screen_height);
	point[3] = PointtoScreen(matrix, v[3], screen_length, screen_height);
	point[4] = PointtoScreen(matrix, v[4], screen_length, screen_height);
	point[5] = PointtoScreen(matrix, v[5], screen_length, screen_height);
	point[6] = PointtoScreen(matrix, v[6], screen_length, screen_height);
	point[7] = PointtoScreen(matrix, v[7], screen_length, screen_height);
	// for (int i = 0; i < 8; i++) 
	// {
	// 	std::cout << "point[" << i << "].draw_x" << point[i].draw_x << std::endl;
	// 	std::cout << "point[" << i << "].draw_y" << point[i].draw_y << std::endl;
	// }

	int point_x[8], point_y[8];
	for (int i = 0; i < 8; i++) 
	{
		point_x[i] = point[i].draw_x;
		point_y[i] = point[i].draw_y;
	}

	int max_x = point_x[0];
    int min_x = point_x[0];
    for (int i = 1; i < 8; i++) {
        if (point_x[i] > max_x) {
            max_x = point_x[i];
        }
        if (point_x[i] < min_x) {
            min_x = point_x[i];
        }
    }
	
	int max_y = point_y[0];
    int min_y = point_y[0];
    for (int i = 1; i < 8; i++) {
        if (point_y[i] > max_y) {
            max_y = point_y[i];
        }
        if (point_y[i] < min_y) {
            min_y = point_y[i];
        }
	}

	View* point_xy = new View[4];
	point_xy[0] = {(min_x - 5), (min_y - 5), 0};
	point_xy[1] = {(max_x + 5), (min_y - 5), 0};
	point_xy[2] = {(min_x - 5), (max_y + 5), 0};
	point_xy[3] = {(max_x + 5), (max_y + 5), 0};

	return point_xy;
}
// 超视野预警
struct ScreenPoint {
    float x;
    float y;
};
bool isPointOnSegment(ScreenPoint p, ScreenPoint start, ScreenPoint end) {
    // Check if the point is within the range of the segment
    return (p.x >= std::min(start.x, end.x) && p.x <= std::max(start.x, end.x) &&
            p.y >= std::min(start.y, end.y) && p.y <= std::max(start.y, end.y));
}
bool doSegmentsIntersect(ScreenPoint p1, ScreenPoint p2, ScreenPoint p3, ScreenPoint p4) {
    // Calculate the orientation of three points (p1, p2, p3)
    float orientation1 = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    // Calculate the orientation of three points (p1, p2, p4)
    float orientation2 = (p2.y - p1.y) * (p4.x - p2.x) - (p2.x - p1.x) * (p4.y - p2.y);
    // Calculate the orientation of three points (p3, p4, p1)
    float orientation3 = (p4.y - p3.y) * (p1.x - p4.x) - (p4.x - p3.x) * (p1.y - p4.y);
    // Calculate the orientation of three points (p3, p4, p2)
    float orientation4 = (p4.y - p3.y) * (p2.x - p4.x) - (p4.x - p3.x) * (p2.y - p4.y);

    // Check if the orientations are different and the segments are not collinear
    if (orientation1 * orientation2 < 0 && orientation3 * orientation4 < 0) {
        return true; // Segments intersect
    }

    // Check if any of the endpoints of one segment lie on the other segment
    if (orientation1 == 0 && isPointOnSegment(p1, p3, p4)) {
        return true; // Segments intersect
    }
    if (orientation2 == 0 && isPointOnSegment(p2, p3, p4)) {
        return true; // Segments intersect
    }
    if (orientation3 == 0 && isPointOnSegment(p3, p1, p2)) {
        return true; // Segments intersect
    }
    if (orientation4 == 0 && isPointOnSegment(p4, p1, p2)) {
        return true; // Segments intersect
    }

    return false; // Segments do not intersect
}
ScreenPoint calculateIntersection(ScreenPoint A, ScreenPoint B, ScreenPoint C, ScreenPoint D) {
    if (!doSegmentsIntersect(A, B, C, D)) {
        // Segments do not intersect
        return { -1, -1 }; // Return a default point
    }

    // Calculate the intersection point using line-line intersection formula
    float x1 = A.x, y1 = A.y;
    float x2 = B.x, y2 = B.y;
    float x3 = C.x, y3 = C.y;
    float x4 = D.x, y4 = D.y;

    float x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
              ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
    float y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
              ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    return { x, y };
}
View DrawOverWatch(View origin)
{
	View out;
	if (0 < origin.draw_x && origin.draw_x < WINDOW_WIDTH && origin.draw_y < WINDOW_HEIGHT && origin.draw_y > 0)
	{
		return out;
	}
	// 计算屏幕中心点坐标
	float screen_w = static_cast<float>(WINDOW_WIDTH);
	float screen_h = static_cast<float>(WINDOW_HEIGHT);
	float o_x = static_cast<float>(origin.draw_x);
	float o_y = static_cast<float>(origin.draw_y);

	ScreenPoint center = {screen_w / 2, screen_h / 2};
	ScreenPoint origin_point = {o_x, o_y};

	// 屏幕边缘线段
	ScreenPoint point[6];
	point[0] = {0,0};
	point[1] = {screen_w,0};
	point[2] = {screen_w,screen_h};
	point[3] = {0,screen_h};
	point[4] = {0,0};
	int i = 0;
	for (i=0;i<4;i++)
	{	
		point[5] = calculateIntersection(center, origin_point, point[i], point[i+1]);
		if (point[5].x > -1 && point[5].y > -1)
		{
			i = 4;
		}
	}

	int x = std::round(point[5].x);
	int y = std::round(point[5].y);
	if (x > (WINDOW_WIDTH - 20))
	{x = (WINDOW_WIDTH - 100);}
	else if (x < 20)
	{x = 20;}
	if (y > (WINDOW_HEIGHT - 20))
	{y = (WINDOW_HEIGHT - 20);}
	else if (y < 20)
	{y = 20;}
	out.draw_x = x;
	out.draw_y = y;
	return out;
}
