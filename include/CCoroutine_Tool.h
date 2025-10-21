#pragma once

#define DLL_EXPORTS extern "C" __declspec(dllexport)
#define DLL_CLASSEXP __declspec(dllexport)

//��ȡ�궨����ʵ�ù�����
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

	int updataini();//��������ini�ļ�

	//��ȡ�Խ����ĵ�PEG��
	//objNum�ﾵ����"1X","2X"
	//isExcellent�Ƿ���focusBasePosλ������������
	//depthRatio����
	//fixtureExist�Ƿ����ξ�
	//zPosArray����λ��
	//flyfirstpos�������
	//flyendpos�����յ�
	int getCalcFocusZPos(std::string objNum, bool isExcellent, double depthRatio, bool fixtureExist,std::vector<double> &zPosArray, double &flyfirstpos, double &flyendpos,double focusBasePos=0.0);

	//��ȡ����Խ������ٶ�
	//objNum�ﾵ����"1X","2X"
	double getFocusZflyspeed(std::string objNum);

	//��ȡ��̨�ͺ�
	AoiMachineType aoiMachineType();

	//��ȡ�ξ�̧���߶�
	double getfixturesHeight(std::string objNum);

	//��ȡ�Խ���Ϸ�ʽ
	int getfocusFitType();	//0�·�ʽ 1�Ϸ�ʽ

	//��ȡ����ƽʱ�ƶ�ʱ���ٶ�
	void getAxisIniSpeed(AoiAxisIniType type, AoiAxisIniSpeedMode,double &SpeedHigh,double &SpeedAcc, double &SpeedDcc);

	//��ȡaxis_ini��Ϣ
	const char *get_axis_ini(const char *Section,const char *key, const char *default);

	//��ȡproduct_ini��Ϣ
	const char *get_product_ini(const char *Section, const char *key, const char *default);

	//��ȡdevicesetting_ini��Ϣ
	const char *get_devicesetting_ini(const char *Section, const char *key, const char *default);

	//��ȡget_setting_ini��Ϣ
	const char *get_setting_ini(const char *Section, const char *key, const char *default);
private:
	CCoroutine_Tool();
	~CCoroutine_Tool();

	CCoroutine_ToolParam *p;
};

#define CCoroutine_Tool_Get CCoroutine_Tool::instance()
