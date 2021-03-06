/**
 ******************************************************************************
 * @file        : device_config.h
 * @author   : robin
 * @version	: V1.0.0
 * @date       : 6-December-2014
 * @brief       :
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
#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include "firmware_platform_config.h"

#if FIRMWARE_CONFIG_SYSTEM_SETUP

#include "wiring_usbserial.h"
#include "wiring_usartserial.h"
#include "wiring_tcpclient.h"
#include "wiring_tcpserver.h"
#include "wiring_udp.h"
#include "wiring_ajson.h"

//设备配置指令
typedef enum{
    //查询类
    DEVICE_CONFIG_HELLO,                   //获取设备基础信息
    DEVICE_CONFIG_CHECK_WIFI,              //获取wifi状态
    DEVICE_CONFIG_GET_WIFI_LIST,           //获取wifi列表
    DEVICE_CONFIG_GET_NETWORK_STATUS,      //查询网络状态
    DEVICE_CONFIG_GET_INFO,                //获取设备信息
    //设置类
    DEVICE_CONFIG_SEND_WIFI_INFO,          //设置wifi信息
    DEVICE_CONFIG_SET_NETWORK_CREDENTIALS, //设置网络接入凭证
    DEVICE_CONFIG_SET_DEVICE_INFO,         //设置设备信息
    DEVICE_CONFIG_SET_SECURITY,            //设置设备安全信息
    DEVICE_CONFIG_SET_INFO,                //设置设备信息
    //执行类
    DEVICE_CONFIG_RESTART_NETWORK,         //重启网络
    DEVICE_CONFIG_RESET,                   //设备恢复出厂设置
    DEVICE_CONFIG_REBOOT,                  //设备重启
    DEVICE_CONFIG_EXIT,                    //退出配置模式
    //其他
    DEVICE_CONFIG_ERROR
}DeviceConfigCmdType;

class DeviceConfig
{
public:
    aJsonClass aJson;

public:
    DeviceConfig(void){}
    ~DeviceConfig(void){}

    virtual int available(void)=0;
    virtual int read(void)=0;
    virtual String readString(void)=0;
    virtual size_t write(const uint8_t *buffer, size_t size)=0;
    virtual void close(void)=0;
    virtual void sendComfirm(int status);

    DeviceConfigCmdType getMessageType(char *s);

    bool process(void);

    void dealHello(void);
    void dealCheckWifi(void);
    void dealGetNetworkStatus(void);
    void dealGetWifiList(void);
    void dealGetInfo(void);

    void dealSendWifiInfo(aJsonObject* root);
    void dealSetNetworkCredentials(aJsonObject* root);
    void dealSendDeviceInfo(aJsonObject* root);
    void dealSetSecurity(aJsonObject* root);
    void dealSetInfo(aJsonObject* root);

    void dealRestartNetwork(void);
    void dealReset(void);
    void dealReboot(void);
    void dealExit(void);
    void dealTest(aJsonObject* root);
};

#if FIRMWARE_CONFIG_SYSTEM_SETUP_USB
class UsbDeviceConfig : public DeviceConfig
{
public:
    USBSerial &serialusb;

public:
    UsbDeviceConfig(USBSerial &_s = SerialUSB):serialusb(_s){}
    ~UsbDeviceConfig(){}

    void init();
    virtual int available(void);
    virtual int read(void);
    virtual String readString(void);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual void close(void);
    virtual void sendComfirm(int status);
};
#endif

#if FIRMWARE_CONFIG_SYSTEM_SETUP_USART
class UsartDeviceConfig: public DeviceConfig
{
public:
    USARTSerial &serial;

public:
    UsartDeviceConfig(USARTSerial &_s = Serial):serial(_s){}
    ~UsartDeviceConfig(){}

    void init();
    virtual int available(void);
    virtual int read(void);
    virtual String readString(void);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual void close(void);
    virtual void sendComfirm(int status);
};
#endif

#if FIRMWARE_CONFIG_SYSTEM_SETUP_TCP
class TcpDeviceConfig: public DeviceConfig
{
public:
    TCPServer server=TCPServer(80);
    TCPClient client,client_bak;

public:
    TcpDeviceConfig(void){}
    ~TcpDeviceConfig(void){}

    void init(void);
    virtual int available(void);
    virtual int read(void);
    virtual String readString(void);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual void close(void);
    virtual void sendComfirm(int status);
};
#endif

#if FIRMWARE_CONFIG_SYSTEM_SETUP_UDP
class UdpDeviceConfig : public DeviceConfig
{
public:
    UDP Udp;

public:
    UdpDeviceConfig(void){}
    ~UdpDeviceConfig(void){}

    void init(void);
    virtual int available(void);
    virtual int read(void);
    virtual String readString(void);
    virtual size_t write(const uint8_t *buf, size_t size);
    virtual void close(void);
    virtual void sendComfirm(int status);
};
#endif

#if FIRMWARE_CONFIG_SYSTEM_SETUP_USB
extern UsbDeviceConfig DeviceSetupUsbSerial;
#endif
#if FIRMWARE_CONFIG_SYSTEM_SETUP_USART
extern UsartDeviceConfig DeviceSetupUsartSerial;
#endif
#if FIRMWARE_CONFIG_SYSTEM_SETUP_TCP
extern TcpDeviceConfig DeviceSetupAp;
#endif
#if FIRMWARE_CONFIG_SYSTEM_SETUP_UDP
extern UdpDeviceConfig DeviceSetupImlink;
#endif

typedef enum
{
    SYSTEM_CONFIG_TYPE_NONE = 0,       //非配置模式
    SYSTEM_CONFIG_TYPE_IMLINK_SERIAL,  //进入imlink+串口配置模式
    SYSTEM_CONFIG_TYPE_AP_SERIAL,      //进入ap+串口配置模式
    SYSTEM_CONFIG_TYPE_SERIAL,         //进入串口配置模式
    SYSTEM_CONFIG_TYPE_IMLINK,         //进入imlink配置模式
    SYSTEM_CONFIG_TYPE_AP              //进入ap配置模式
}system_config_type_t;


extern volatile uint8_t g_intorobot_system_config;    //配置状态

void set_system_config_type(system_config_type_t config_type);
system_config_type_t get_system_config_type();
bool system_config_process(void);
void system_config_setup(void);
void manage_system_config();

#endif
#endif

