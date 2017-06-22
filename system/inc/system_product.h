/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

#ifndef SYSTEM_PRODUCT_H_
#define SYSTEM_PRODUCT_H_

#include <stdint.h>
#include <string.h>
#include "intorobot_macros.h"

#ifndef DEFAULT_PRODUCT_SOFTWARE_VERSION
#define DEFAULT_PRODUCT_SOFTWARE_VERSION
#endif

#ifndef DEFAULT_PRODUCT_HARDWARE_VERSION
#define DEFAULT_PRODUCT_HARDWARE_VERSION
#endif

#ifndef DEFAULT_PRODUCT_ID
#define DEFAULT_PRODUCT_ID
#endif

#ifndef DEFAULT_PRODUCT_SECRET
#define DEFAULT_PRODUCT_SECRET
#endif

typedef enum
{
    PRODUCT_TYPE_NOTE = 0,
    PRODUCT_TYPE_GATEWAY
} product_type_t;

typedef enum
{
    SYSTEM_PRODUCT_PARAM_SOFTWARE_VERSION = 0,
    SYSTEM_PRODUCT_PARAM_HARDWARE_VERSION,
    SYSTEM_PRODUCT_PARAM_ID,
    SYSTEM_PRODUCT_PARAM_SECRET,
    SYSTEM_PRODUCT_PARAM_BOARD_ID,
    SYSTEM_PRODUCT_PARAM_BOARD_NAME
} system_product_param_t;

typedef enum
{
    SYSTEM_FEATURE_SEND_INFO_ENABLED = 0,           //发送设备信息  0:关闭  1:打开
    SYSTEM_FEATURE_OTA_UPDATE_ENABLED,              //OTA升级       0:关闭  1:打开
    SYSTEM_FEATURE_CONFIG_SAVE_ENABLED,             //配置模式保存  0:关闭  1:打开
    SYSTEM_FEATURE_AUTO_CONFIG_PROCESS_ENABLED,     //自动配置处理  0:关闭  1:打开
    SYSTEM_FEATURE_AUTO_TIME_SYN_ENABLED,           //自动时间同步  0:关闭  1:打开
    SYSTEM_FEATURE_DATAPOINT_ENABLED,               //数据点处理    0:关闭  1:打开
    SYSTEM_FEATURE_REGISTER_ENABLED,                //设备注册      0:关闭  1:打开
    SYSTEM_FEATURE_ACTIVATE_ENABLED,                //设备激活      0:关闭  1:打开
    SYSTEM_FEATURE_MAX
} system_feature_t;

class IntoRobotProduct
{
public:
    IntoRobotProduct() {
        product_type = PRODUCT_TYPE_NOTE;                                       //产品类型  节点类型
        strcpy(product_software_version, stringify(DEFAULT_PRODUCT_SOFTWARE_VERSION));  //产品软件版本号
        strcpy(product_hardware_version, stringify(DEFAULT_PRODUCT_HARDWARE_VERSION));  //产品硬件版本号
        strcpy(product_id, stringify(DEFAULT_PRODUCT_ID));                      //产品ID
        strcpy(product_secret, stringify(DEFAULT_PRODUCT_SECRET));              //产品密钥
        strcpy(board_id, stringify(PLATFORM_ID));                               //模组ID
        strcpy(board_name, stringify(PLATFORM_NAME));                           //模组名称

        feature_send_info_enable = true;            //发送设备信息  0:关闭  1:打开
        feature_ota_update_enable = true;           //OTA升级       0:关闭  1:打开
        feature_config_save_enable = true;          //配置模式保存  0:关闭  1:打开
        feature_auto_config_process_enable = true;  //自动配置处理  0:关闭  1:打开
        feature_auto_time_syn_enable = true;        //自动时间同步  0:关闭  1:打开
        feature_datapoint_enable = true;            //数据点处理    0:关闭  1:打开
        feature_register_enable = true;             //设备注册      0:关闭  1:打开
        feature_activater_enable = true;            //设备激活      0:关闭  1:打开
    }
    ~IntoRobotProduct(){}

    product_type_t get_product_type(void) {
        return product_type;
    }

    int set_product_type(product_type_t type) {
        product_type = type;
        return 0;
    }

    uint16_t get_product_param(system_product_param_t param, char *buffer, uint16_t len) {
        uint16_t templen = 0;

        if (buffer!=NULL && len>0) {
            memset(buffer, 0, len);
            switch(param) {
                case SYSTEM_PRODUCT_PARAM_SOFTWARE_VERSION:
                    templen = MIN(strlen(product_software_version), len-1);
                    memcpy(buffer, product_software_version, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_HARDWARE_VERSION:
                    templen = MIN(strlen(product_hardware_version), len-1);
                    memcpy(buffer, product_hardware_version, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_ID:
                    templen = MIN(strlen(product_id), len-1);
                    memcpy(buffer, product_id, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_SECRET:
                    templen = MIN(strlen(product_secret), len-1);
                    memcpy(buffer, product_secret, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_BOARD_ID:
                    templen = MIN(strlen(board_id), len-1);
                    memcpy(buffer, board_id, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_BOARD_NAME:
                    templen = MIN(strlen(board_name), len-1);
                    memcpy(buffer, board_name, templen);
                    break;
                default:
                    break;
            }
            return templen;
        }
        return 0;
    }

    int set_product_param(system_product_param_t param, char *buffer) {
        uint16_t templen;

        if (buffer!=NULL) {
            switch(param) {
                case SYSTEM_PRODUCT_PARAM_SOFTWARE_VERSION:
                    templen = MIN(sizeof(product_software_version)-1, strlen(buffer));
                    memset(product_software_version, 0, sizeof(product_software_version));
                    memcpy(product_software_version, buffer, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_HARDWARE_VERSION:
                    templen = MIN(sizeof(product_hardware_version)-1, strlen(buffer));
                    memset(product_hardware_version, 0, sizeof(product_hardware_version));
                    memcpy(product_hardware_version, buffer, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_ID:
                    templen = MIN(sizeof(product_id)-1, strlen(buffer));
                    memset(product_id, 0, sizeof(product_id));
                    memcpy(product_id, buffer, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_SECRET:
                    templen = MIN(sizeof(product_secret)-1, strlen(buffer));
                    memset(product_secret, 0, sizeof(product_secret));
                    memcpy(product_secret, buffer, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_BOARD_ID:
                    templen = MIN(sizeof(board_id)-1, strlen(buffer));
                    memset(board_id, 0, sizeof(board_id));
                    memcpy(board_id, buffer, templen);
                    break;
                case SYSTEM_PRODUCT_PARAM_BOARD_NAME:
                    templen = MIN(sizeof(board_name)-1, strlen(buffer));
                    memset(board_name, 0, sizeof(board_name));
                    memcpy(board_name, buffer, templen);
                    break;
                default:
                    break;
            }
            return 0;
        }
        return -1;
    }

    bool get_system_feature(system_feature_t feature) {
        switch(feature) {
            case SYSTEM_FEATURE_SEND_INFO_ENABLED:
                return feature_send_info_enable;            //发送设备信息  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_OTA_UPDATE_ENABLED:
                return feature_ota_update_enable;           //OTA升级       0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_CONFIG_SAVE_ENABLED:
                return feature_config_save_enable;          //配置模式保存  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_AUTO_CONFIG_PROCESS_ENABLED:
                return feature_auto_config_process_enable;  //配置自动处理  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_AUTO_TIME_SYN_ENABLED:
                return feature_auto_time_syn_enable;        //自动时间同步  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_DATAPOINT_ENABLED:
                return feature_datapoint_enable;            //数据点处理    0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_REGISTER_ENABLED:
                return feature_register_enable;             //设备注册      0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_ACTIVATE_ENABLED:
                return feature_activater_enable;            //设备激活      0:关闭  1:打开
                break;
            default:
                break;
        }
        return false;
    }

    int set_system_feature(system_feature_t feature, bool enabled) {
        switch(feature) {
            case SYSTEM_FEATURE_SEND_INFO_ENABLED:
                feature_send_info_enable = enabled;            //发送设备信息  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_OTA_UPDATE_ENABLED:
                feature_ota_update_enable = enabled;           //OTA升级       0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_CONFIG_SAVE_ENABLED:
                feature_config_save_enable = enabled;          //配置模式保存  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_AUTO_CONFIG_PROCESS_ENABLED:
                feature_auto_config_process_enable = enabled;  //配置自动处理  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_AUTO_TIME_SYN_ENABLED:
                feature_auto_time_syn_enable = enabled;        //自动时间同步  0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_DATAPOINT_ENABLED:
                feature_datapoint_enable = enabled;            //数据点处理    0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_REGISTER_ENABLED:
                feature_register_enable = enabled;             //设备注册      0:关闭  1:打开
                break;
            case SYSTEM_FEATURE_ACTIVATE_ENABLED:
                feature_activater_enable = enabled;            //设备激活      0:关闭  1:打开
                break;
            default:
                break;
        }
        return 0;
    }

private:
    product_type_t product_type;              //产品类型  节点设备(主模式和从模式)/网关设备
    char product_software_version[17];        //产品程序版本号
    char product_hardware_version[17];        //产品硬件版本号
    char product_id[33];                      //产品ID
    char product_secret[33];                  //产品密钥
    char board_id[17];                        //模块ID
    char board_name[17];                      //模块名称

    bool feature_send_info_enable;            //发送设备信息  0:关闭  1:打开
    bool feature_ota_update_enable;           //OTA升级       0:关闭  1:打开
    bool feature_config_save_enable;          //配置模式保存  0:关闭  1:打开
    bool feature_auto_config_process_enable;  //自动配置处理  0:关闭  1:打开
    bool feature_auto_time_syn_enable;        //自动时间同步  0:关闭  1:打开
    bool feature_datapoint_enable;            //数据点处理    0:关闭  1:打开
    bool feature_register_enable;             //设备注册      0:关闭  1:打开
    bool feature_activater_enable;            //设备激活      0:关闭  1:打开
};

extern IntoRobotProduct &system_product_instance(void);

#endif

