//credits: https://github.com/frk1/hazedumper/blob/master/csgo.hpp

#include <cstdint>

// 地址偏移
namespace offset
{
    constexpr ::std::ptrdiff_t OFFSET_START = 0x53B0EE8;        //玩家列表起始
    constexpr ::std::ptrdiff_t PLAYER_LIST = 0xB0;              //玩家列表
    constexpr ::std::ptrdiff_t LOCAL_PLAYER = 0x20;             //本地玩家
    constexpr ::std::ptrdiff_t PLAYER_OFFSET = 0x8;             //玩家列表偏移
    constexpr ::std::ptrdiff_t PLAYER_ID = 0xB8;                //玩家ID
    constexpr ::std::ptrdiff_t PLAYER_DATA = 0x700 ;            //玩家数据[指针]
    constexpr ::std::ptrdiff_t VEHICLE_DATA = 0x1288;           //载具信息
    constexpr ::std::ptrdiff_t VEHICLE_ID = 0x20;               //载具名称
    constexpr ::std::ptrdiff_t VEHICLE_TYPE = 0x38;             //载具类型
    constexpr ::std::ptrdiff_t BBMIN = 0x218;                   //BBMin
    constexpr ::std::ptrdiff_t BBMAX = 0x224;                   //BBMax
    // constexpr ::std::ptrdiff_t RELOAD = 0x770;               //装填时间
    constexpr ::std::ptrdiff_t ROTATION = 0xAAC;                //单位旋转矩阵
    constexpr ::std::ptrdiff_t LOCATION = 0xAD0;                //坐标起始
    constexpr ::std::ptrdiff_t LOCATION_OFFSET = 0x4;           //坐标偏移
    //constexpr ::std::ptrdiff_t PROTECT = 0xFC8;               //无敌状态
    constexpr ::std::ptrdiff_t PLANE = 0xAE8;                   //空中载具信息
    constexpr ::std::ptrdiff_t PLANE_VELOCITY = 0xB28;          //空中载具速度
    constexpr ::std::ptrdiff_t PLAYER_STATE = 0x11E8;           //玩家状态
    constexpr ::std::ptrdiff_t TEAM = 0x1278;                   //玩家队伍
    constexpr ::std::ptrdiff_t MATRIX = 0x541C338;              //矩阵地址
}
