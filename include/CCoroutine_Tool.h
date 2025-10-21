#pragma once

#define DLL_EXPORTS extern "C" __declspec(dllexport)
#define DLL_CLASSEXP __declspec(dllexport)

//读取标定参数实用工具类
#include "dataStructure.h"
#include <vector>
#include <string>

enum AoiMachineType {
	OWL1000_XYZT = 0,
	OWL1000P_XYZ = 1,
	OWL1000P_XYZZT = 2,
	OWL1000R = 3,
	OWL1000PTDI_XYZT = 4,
	OWL1000_XYZT_S = 5,
};

enum AoiAxisIniType {
	AOI_AxisIni_X = 0,
	AOI_AxisIni_Y = 1,
	AOI_AxisIni_Z = 2,
	AOI_AxisIni_T = 3,
};

enum AoiAxisIniSpeedMode {
	AOI_AxisIni_AUTO = 0,
	AOI_AxisIni_MANUAL = 1,
};

class CCoroutine_ToolParam;

class DLL_CLASSEXP CCoroutine_Tool
{
public:
	static CCoroutine_Tool *instance();

	int updataini();//重新载入ini文件

	//获取对焦飞拍的PEG点
	//objNum物镜倍率"1X","2X"
	//isExcellent是否用focusBasePos位置做飞拍中心
	//depthRatio景深
	//fixtureExist是否有治具
	//zPosArray触发位置
	//flyfirstpos飞拍起点
	//flyendpos飞拍终点
	int getCalcFocusZPos(std::string objNum, bool isExcellent, double depthRatio, bool fixtureExist,std::vector<double> &zPosArray, double &flyfirstpos, double &flyendpos,double focusBasePos=0.0);

	//获取相机对焦飞拍速度
	//objNum物镜倍率"1X","2X"
	double getFocusZflyspeed(std::string objNum);

	//获取机台型号
	AoiMachineType aoiMachineType();

	//获取治具抬升高度
	double getfixturesHeight(std::string objNum);

	//获取对焦拟合方式
	int getfocusFitType();	//0新方式 1老方式

	//获取轴在平时移动时的速度
	void getAxisIniSpeed(AoiAxisIniType type, AoiAxisIniSpeedMode,double &SpeedHigh,double &SpeedAcc, double &SpeedDcc);

	//获取axis_ini信息
	const char *get_axis_ini(const char *Section,const char *key, const char *default);

	//获取product_ini信息
	const char *get_product_ini(const char *Section, const char *key, const char *default);

	//获取devicesetting_ini信息
	const char *get_devicesetting_ini(const char *Section, const char *key, const char *default);

	//获取get_setting_ini信息
	const char *get_setting_ini(const char *Section, const char *key, const char *default);
private:
	CCoroutine_Tool();
	~CCoroutine_Tool();

	CCoroutine_ToolParam *p;
};

#define CCoroutine_Tool_Get CCoroutine_Tool::instance()
