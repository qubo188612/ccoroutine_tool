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

class DLL_CLASSEXP CCoroutine_Tool
{
public:
	CCoroutine_Tool();
	~CCoroutine_Tool();

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
private:
	
};
