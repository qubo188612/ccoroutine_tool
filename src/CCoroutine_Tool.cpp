#include "CCoroutine_Tool.h"
#include "SimpleIni.h"

CCoroutine_Tool::CCoroutine_Tool()
{

}

CCoroutine_Tool::~CCoroutine_Tool()
{

}

int CCoroutine_Tool::getCalcFocusZPos(std::string objNum, bool isExcellent, double depthRatio, bool fixtureExist,std::vector<double> &zPosArray,double &flyfirstpos,double &flyendpos,double focusBasePos)
{
	std::vector<double> rc_zPosArray;
	double intervalLelft=0, intervalRight=0;
	double step=0.1;

	CSimpleIniA setting_ini;

	// ����ini�ļ�
	SI_Error rc;
	rc = setting_ini.LoadFile("CustomData/motion/device/setting.ini");	// ��һ�ַ�ʽ��SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("���� setting_ini �ļ�ʧ�ܣ�\n");
		return -1;
	}
	
	std::string strhead = "main-settings.lensFocusPar.";
	std::string str = strhead + objNum;
	std::string str_axisNLimit = str + ".axisNLimit";//�Խ�����
	std::string str_axisPLimit = str + ".axisPLimit";//�Խ��Ҽ���
	std::string str_depthField = str + ".depthField";//�ﾵ����
	std::string str_focusstep = str + ".step";//�ﾵ����

	double axisNLimit = std::stod(setting_ini.GetValue("General", str_axisNLimit.c_str(), "0.0"));
	double axisPLimit = std::stod(setting_ini.GetValue("General", str_axisPLimit.c_str(), "0.0"));
	double depthField = std::stod(setting_ini.GetValue("General", str_depthField.c_str(), "0.0"));
	double focusstep = std::stod(setting_ini.GetValue("General", str_focusstep.c_str(), "2.0"));

	double FocusExpandDistance = std::stod(setting_ini.GetValue("General", "main-settings.flayscanPar.FocusExpandDistance", "0.4"));

	if (isExcellent==true)
	{
		double depth = depthField / 1000.0;
		if (depthRatio > 0) {
			intervalLelft = focusBasePos - depth * depthRatio;
			intervalRight = focusBasePos + depth * depthRatio;
		}
		else {
			intervalLelft = focusBasePos - depth;
			intervalRight = focusBasePos + depth;
		}
	}
	else {
		if (fixtureExist == false) {
			intervalLelft = axisNLimit;
			intervalRight = axisPLimit;
		}
		else {
			double difpos = getfixturesHeight(objNum);
			intervalLelft = axisNLimit + difpos;
			intervalRight = axisPLimit + difpos;
		}
	}
	step = depthField / 1000.0;
	step = step / focusstep;

	if (!(intervalLelft < intervalRight)) {
		printf("�Խ��������Ҽ������ô���(�������� < �Ҽ���)");
		return -1;
	}
	if (step <= 0) {
		printf("�ﾵ�������ô���");
		return -2;
	}
	//�������Zλ�ã���������
	for (int i = 0;; i++) {
		double p = intervalLelft + i * step;
		if (p > intervalRight) {
			break;
		}
		rc_zPosArray.push_back(p);
	}
	zPosArray = rc_zPosArray;
	flyfirstpos = intervalLelft - step * 3 - FocusExpandDistance;
	flyendpos=intervalRight + step * 3 + FocusExpandDistance;
	return 0;
}

AoiMachineType CCoroutine_Tool::aoiMachineType()
{
	CSimpleIniA devicesetting_ini;

	// ����ini�ļ�
	SI_Error rc;
	rc = devicesetting_ini.LoadFile("CustomData/hal/deviceSetting.ini");	// ��һ�ַ�ʽ��SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("���� deviceSetting �ļ�ʧ�ܣ�\n");
		return OWL1000_XYZT;
	}
	int aoiMachineType = std::stoi(devicesetting_ini.GetValue("General", "deviceconfigNode.functionSel.aoiMachineType", "0"));
	
	AoiMachineType result = static_cast<AoiMachineType>(aoiMachineType);
	return result;
}

double CCoroutine_Tool::getfixturesHeight(std::string objNum)
{
	CSimpleIniA product_ini;

	// ����ini�ļ�
	SI_Error rc;
	rc = product_ini.LoadFile("CustomData/motion/device/product.ini");	// ��һ�ַ�ʽ��SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("���� setting_ini �ļ�ʧ�ܣ�\n");
		return 0;
	}

	std::string strhead = "main-product.axisPos.fixtures.fixturesHeightGroup.";
	std::string str = strhead + objNum;
	std::string str_dif_fixturesHeight = str + ".dif_fixturesHeight";//�ξ�̧���߶�

	double fixturesHeight = std::stod(product_ini.GetValue("default", str_dif_fixturesHeight.c_str(), "0.0"));
	return fixturesHeight;
}

double CCoroutine_Tool::getFocusZflyspeed(std::string objNum)
{
	CSimpleIniA setting_ini;

	// ����ini�ļ�
	SI_Error rc;
	rc = setting_ini.LoadFile("CustomData/motion/device/setting.ini");	// ��һ�ַ�ʽ��SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("���� setting_ini �ļ�ʧ�ܣ�\n");
		return 1;
	}

	std::string strhead = "main-settings.lensFocusPar.";
	std::string str = strhead + objNum;
	std::string str_speed = str + ".speed";//�Խ��ٶ�

	double speed = std::stod(setting_ini.GetValue("General", str_speed.c_str(), "1"));
	return speed;
}