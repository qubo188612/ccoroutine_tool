#include "CCoroutine_Tool.h"
#include "SimpleIni.h"

class CCoroutine_ToolParam
{
public:
	CCoroutine_ToolParam() {};
	~CCoroutine_ToolParam() {};

	CSimpleIniA setting_ini;
	CSimpleIniA devicesetting_ini;
	CSimpleIniA product_ini;
};

CCoroutine_Tool::CCoroutine_Tool()
{
	p = new CCoroutine_ToolParam;
	updataini();
}

CCoroutine_Tool::~CCoroutine_Tool()
{
	delete p;
}

CCoroutine_Tool *CCoroutine_Tool::instance()
{
	static CCoroutine_Tool obj;
	return &obj;
}

int CCoroutine_Tool::updataini()//重新载入ini文件
{
	SI_Error rc;
	rc = p->setting_ini.LoadFile("CustomData/motion/device/setting.ini");	// 另一种方式：SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("加载 setting_ini 文件失败！\n");
		return -1;
	}
	rc = p->devicesetting_ini.LoadFile("CustomData/hal/deviceSetting.ini");	// 另一种方式：SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("加载 deviceSetting 文件失败！\n");
		return -1;
	}
	rc = p->product_ini.LoadFile("CustomData/motion/device/product.ini");	// 另一种方式：SI_Error LoadFile(FILE * a_fpFile);
	if (rc < 0) {
		printf("加载 setting_ini 文件失败！\n");
		return -1;
	}
	return 0;
}

int CCoroutine_Tool::getCalcFocusZPos(std::string objNum, bool isExcellent, double depthRatio, bool fixtureExist,std::vector<double> &zPosArray,double &flyfirstpos,double &flyendpos,double focusBasePos)
{
	std::vector<double> rc_zPosArray;
	double intervalLelft=0, intervalRight=0;
	double step=0.1;
	
	std::string strhead = "main-settings.lensFocusPar.";
	std::string str = strhead + objNum;
	std::string str_axisNLimit = str + ".axisNLimit";//对焦左极限
	std::string str_axisPLimit = str + ".axisPLimit";//对焦右极限
	std::string str_depthField = str + ".depthField";//物镜景深
	std::string str_focusstep = str + ".step";//物镜景深

	double axisNLimit = std::stod(p->setting_ini.GetValue("General", str_axisNLimit.c_str(), "0.0"));
	double axisPLimit = std::stod(p->setting_ini.GetValue("General", str_axisPLimit.c_str(), "0.0"));
	double depthField = std::stod(p->setting_ini.GetValue("General", str_depthField.c_str(), "0.0"));
	double focusstep = std::stod(p->setting_ini.GetValue("General", str_focusstep.c_str(), "2.0"));

	double FocusExpandDistance = std::stod(p->setting_ini.GetValue("General", "main-settings.flayscanPar.FocusExpandDistance", "0.4"));

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
		printf("对焦区间左右极限设置错误(必须左极限 < 右极限)");
		return -1;
	}
	if (step <= 0) {
		printf("物镜景深设置错误");
		return -2;
	}
	//计算飞拍Z位置，从下向上
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
	int aoiMachineType = std::stoi(p->devicesetting_ini.GetValue("General", "deviceconfigNode.functionSel.aoiMachineType", "0"));
	
	AoiMachineType result = static_cast<AoiMachineType>(aoiMachineType);
	return result;
}

double CCoroutine_Tool::getfixturesHeight(std::string objNum)
{
	std::string strhead = "main-product.axisPos.fixtures.fixturesHeightGroup.";
	std::string str = strhead + objNum;
	std::string str_dif_fixturesHeight = str + ".dif_fixturesHeight";//治具抬升高度

	double fixturesHeight = std::stod(p->product_ini.GetValue("default", str_dif_fixturesHeight.c_str(), "0.0"));
	return fixturesHeight;
}

double CCoroutine_Tool::getFocusZflyspeed(std::string objNum)
{
	std::string strhead = "main-settings.lensFocusPar.";
	std::string str = strhead + objNum;
	std::string str_speed = str + ".speed";//对焦速度

	double speed = std::stod(p->setting_ini.GetValue("General", str_speed.c_str(), "1"));
	return speed;
}

int CCoroutine_Tool::getfocusFitType()
{
	int focusFitType = std::stoi(p->setting_ini.GetValue("General", "main-settings.focusFitType", "0"));
	return focusFitType;
}