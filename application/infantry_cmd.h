/****************************************************************************
 *  Copyright (C) 2020 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef __INFANTRY_H__
#define __INFANTRY_H__

#include "sys.h"

#define FIRMWARE_VERSION_0 1u
#define FIRMWARE_VERSION_1 0u
#define FIRMWARE_VERSION_2 0u
#define FIRMWARE_VERSION_3 3u

#define FIRMWARE_VERSION ((FIRMWARE_VERSION_3 << 24) | (FIRMWARE_VERSION_2 << 16) | (FIRMWARE_VERSION_1 << 8) | FIRMWARE_VERSION_0)

#define MANIFOLD2_ADDRESS      0x00
#define CHASSIS_ADDRESS        0x01
#define GIMBAL_ADDRESS         0x02

#define GIMBAL_CAN_ID         0x500
#define CHASSIS_CAN_ID        0x600

/* cmd id can not be set 0xffff */
#pragma pack(push,1)

#define CMD_MANIFOLD2_HEART                 (0x0001u)
#define CMD_REPORT_VERSION                  (0x0002u)

#define CMD_STUDENT_DATA                    (0x0101u)

#define CMD_PUSH_CHASSIS_INFO               (0x0201u)
struct cmd_chassis_info
{
    int16_t gyro_angle;
    int16_t gyro_palstance;
    int32_t position_x_mm;
    int32_t position_y_mm;
    int16_t angle_deg;
    int16_t v_x_mm;
    int16_t v_y_mm;
};

#define CMD_SET_CHASSIS_MODE                (0x0202u)
#define CMD_SET_CHASSIS_SPEED               (0x0203u)
struct cmd_chassis_speed
{
    int16_t vx; // forward/back
    int16_t vy; // left/right
    int16_t vw; // anticlockwise/clockwise
    int16_t rotate_x_offset;
    int16_t rotate_y_offset;
};

#define CMD_GET_CHASSIS_PARAM               (0x0204u)
struct cmd_chassis_param
{
    uint16_t wheel_perimeter; /* the perimeter(mm) of wheel */
    uint16_t wheel_track;     /* wheel track distance(mm) */
    uint16_t wheel_base;      /* wheelbase distance(mm) */
    int16_t rotate_x_offset;
    int16_t rotate_y_offset;
};

#define CMD_SET_CHASSIS_SPD_ACC             (0x0205u)
struct cmd_chassis_spd_acc
{
    int16_t   vx;
    int16_t   vy;
    int16_t   vw;

    int16_t   ax;
    int16_t   ay;
    int16_t   wz;

    int16_t rotate_x_offset;
    int16_t rotate_y_offset;
};

#define CMD_PUSH_GIMBAL_INFO                (0x0301u)
struct cmd_gimbal_info
{
    uint8_t   mode;
    /* unit: degree */
    int16_t pitch_ecd_angle;
    int16_t yaw_ecd_angle;
    int16_t pitch_gyro_angle;
    int16_t yaw_gyro_angle;
    /* uint: degree/s */
    int16_t yaw_rate;
    int16_t pitch_rate;
};

#define CMD_SET_GIMBAL_MODE                 (0x0302u)
#define CMD_SET_GIMBAL_ANGLE                (0x0303u)
struct cmd_gimbal_angle
{
    union
    {
        uint8_t flag;
        struct
        {
            uint8_t yaw_mode: 1; // 0 code angle
            uint8_t pitch_mode: 1;
        } bit;
    } ctrl;
    int16_t pitch;
    int16_t yaw;
};

#define CMD_SET_FRICTION_SPEED              (0x0304u)
struct cmd_firction_speed
{
    uint16_t left;
    uint16_t right;
};

#define CMD_SET_SHOOT_FREQUENTCY            (0x0305u)
struct cmd_shoot_num
{
    uint8_t  shoot_cmd;
    uint32_t shoot_add_num;
    uint16_t shoot_freq;
};
#define CMD_SET_GIMBAL_CMD                      (0x0306u)
struct cmd_set_gimbal_cmd
{
		float pitch;
		float yaw;
		float yaw_diff;
		float pitch_diff;
		float distance;
		uint8_t fire_advice;
};

#define CMD_SET_TARGET                      (0x0307u)
struct cmd_set_target
{
		uint8_t tracking : 2; // 代表当前是否锁定目标
		uint8_t id : 3;          // 0-outpost 6-guard 7-base
		uint8_t armors_num : 3;  // 2-balance 3-outpost 4-normal
		float x; // 目标在世界坐标系下的 x 坐标
		float y; // 目标在世界坐标系下的 Y 坐标
		float z; //目标在世界坐标系下的 Z 坐标
		float yaw; // 目标在世界坐标系下的倾斜角度
		float vx; // 目标在世界坐标系下 x 方向的速度
		float vy; // 目标在世界坐标系下 y 方向的速度
		float vz; // 目标在世界坐标系下 z 方向的速度
		float v_yaw; // 目标旋转的角速度
		float r1; // 目标其中一组装甲板相对中心的半径
		float r2; // 目标另一组装甲板相对中心的半径
		float dz; // tracking 中的装甲板的上一块装甲板的 z 轴位置
};
#define GIMBAL_INFO_SET_TARGET_RPY													(0x0308u)
struct gimbal_info_set_rpy
{
		int16_t roll;
		int16_t pitch;
		int16_t yaw;
};

#define GIMBAL_INFO_SET_AIM_POSITION												(0x0309u)
struct gimbal_info_set_aim_position
{
		int32_t aim_x;
		int32_t aim_y;
		int32_t aim_z;
};

#define SET_TRACKER_RESET   																(0x030Au)
struct set_tracker_reset
{
		uint8_t reset_tracker;
};
#define CMD_RC_DATA_FORWORD                 (0x0401u)
#define CMD_PUSH_UWB_INFO                   (0x0402u)
#define CMD_GIMBAL_ADJUST                   (0x0403u)

#pragma pack(pop)

#endif // __INFANTRY_H__
