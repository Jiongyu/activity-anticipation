/*****************************************************************************
 *        Robot公共变量及Robot系统文件操作类                                 *
 *        SCUT, 2011                                                         *
 *        Author :                                                           *
 *        Version number :  0.10                                             *
 *        Date :            2011-04-22                                       *
 *****************************************************************************/

#include "Setup.h"
//#include "File.h"

///////////////////////////////////////////////////////////////// 静态变量预定义
ServoControl Robot::I_Servo; // 伺服控制类
Monitor Robot::I_Monit;      // 监控类
TaskControl Robot::I_Task;   // Task队列
PumpControl Robot::I_Pump;   // 吸盘气泵控制类

unchar Robot::axisNum = 5;
unchar Robot::robotMode = ROBOT_MODE_CR_P; // 机器人构型 - 爬杆
unchar Robot::actualTool = GRIP_FIRST;     // 当前工具 - #1
unchar Robot::runMode = RUNMODE_TEACH;     // 当前示教坐标系 - 示教
unchar Robot::teachMode = COORDINATE_JOINT;// 当前示教模式 - 关节
bool Robot::ifMonitor = true;              // 开机监控
bool Robot::ifTool = true;
bool Robot::ifMaster = true;
bool Robot::ifWheel = true;

//double Robot::robotLen[7] = { 250, 375, 200, 175, 100, 100, 100};	// 杆长
//double Robot::motorRat[MAX_AXIS_NUM] = {-225.0, 375, 375, 375, -450.0, 375};// 各轴减速比
//double Robot::posLim[MAX_AXIS_NUM] = { 270, 110,  110, 270,  110}; // 正极限
//double Robot::negLim[MAX_AXIS_NUM] = {-270, -110, -110, -270, -110}; // 负极限
//double Robot::teachLim[6] = {10, 30, 20, 60, 5, 20};           // 示教限制参数
//double Robot::autoLim[7] = {30, 50, 100, 150, 10, 40, 500};

/////////////////////////////////////////////////////////////////////////////////////////
double Robot::robotLen[7] = { 210.4, 93.4, 293.2, 254, 131, 248.5, 100};	// 杆长
double Robot::motorRat[MAX_AXIS_NUM] = {457.14, 480, 480, 188.24, 200, 375};// 各轴减速比
double Robot::posLim[MAX_AXIS_NUM] = { 360, 210,  210, 360,  120}; // 正极限
double Robot::negLim[MAX_AXIS_NUM] = {-360, -30, -30, -360, -120}; // 负极限
double Robot::teachLim[6] = {10, 30, 20, 60, 5, 20};           // 示教限制参数
double Robot::autoLim[7] = {30, 5, 100, 150, 10, 40, 500};
//////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////// 静态变量预定义

/******************************************************************************
 * 函数：Robot()
 * 功能：构造函数
 ******************************************************************************/
RobotFile::RobotFile()
{}

/******************************************************************************
 * 函数：~Robot()
 * 功能：析构函数
 ******************************************************************************/
RobotFile::~RobotFile()
{}

/******************************************************************************
 * 函数：Read_File()
 * 功能：读文件
 *
 * 输入：CString path  - 文件路径
 * 输出：CString str[] - 文件内容, String
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Read_File(IN CString path, OUT CString& str)
{
	if (m_file.Open( _T(path), CFile::modeNoTruncate | CFile::modeRead | CFile::typeText ))
	{
		m_file.ReadString(str);
		m_file.Close();
	}
	else if (m_file.Open( _T(path), CFile::modeCreate | CFile::modeWrite | CFile::typeText ))
	{
		str = "1";
		m_file.WriteString(str);
		m_file.Close();
	}
	else
		return false;

	return true;
}

/******************************************************************************
 * 函数：Read_File()
 * 功能：读文件
 *
 * 输入：CString path  - 文件路径
 *       int num       - 行数
 *       int mode      - 机器人构型模式
 * 输出：CString str[] - 文件内容数组, 行String
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Read_File(IN CString path, OUT CString str[], IN int num, IN int mode)
{
	if (m_file.Open( _T(path), CFile::modeNoTruncate | CFile::modeRead | CFile::typeText ))
	{
		for (int i=0; i<num; i++)
		{
			m_file.ReadString(str[i]);
		}
		m_file.Close();
	}
	else if (m_file.Open( _T(path), CFile::modeCreate | CFile::modeWrite | CFile::typeText ))
	{
		for (int i=0; i<num; i++)
		{
			double val;
			switch(mode)
			{
			case WRITE_MODE_ROBOTLEN:
				val = Robot::robotLen[i];
				break;
			case WRITE_MODE_MOTORRAT:
				val = Robot::motorRat[i];
				break;
			case WRITE_MODE_JPOSLIM:
				val = Robot::posLim[i];
				break;
			case WRITE_MODE_JNEGLIM:
				val = Robot::negLim[i];
				break;
			case WRITE_MODE_TEACHLIM:
				val = Robot::teachLim[i];
				break;
			case WRITE_MODE_AUTOLIM:
				val = Robot::autoLim[i];
				break;
			default:
				val = 0;
				break;
			}
			str[i].Format("%f", val);
			m_file.WriteString(str[i]);
			m_file.WriteString("\n");
		}
		m_file.Close();
	}
	else
		return false;
	
	return true;
}

/******************************************************************************
 * 函数：Write_File()
 * 功能：写文件
 *
 * 输入：CString path - 文件路径
 *       CString str  - 文件内容
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Write_File(IN CString path, IN CString str)
{
	if (m_file.Open( _T(path), CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText ))
	{
		m_file.WriteString(str);
		m_file.Close();
	}
	else if (m_file.Open( _T(path), CFile::modeCreate | CFile::modeWrite | CFile::typeText ))
	{
		m_file.WriteString(str);
		m_file.Close();
	}
	else
		return false;

	return true;
}

/******************************************************************************
 * 函数：Write_File()
 * 功能：写文件
 *
 * 输入：CString path  - 文件路径
 *       CString str[] - 文件内容数组, 行String
 *       int num       - 行数
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Write_File(IN CString path, IN CString str[], IN int num)
{
	if (m_file.Open( _T(path), CFile::modeNoTruncate | CFile::modeCreate 
		| CFile::modeWrite | CFile::typeText ))
	{
		for (int i=0; i<num; i++)
		{
			m_file.WriteString(str[i]);
			m_file.WriteString("\n");
		}

		m_file.Close();
	}
	else
		return false;
	
	return true;
}

/******************************************************************************
 * 函数：Init()
 * 功能：初始化
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Init()
{
	CString buf;
	CString str[7];
	int i;

	// 检查目录是否存在
	FileOperate file;
	if (! file.FileExist(ROBOT_FILE_FOLDER))
	{
		// 创建目录
		file.CreateFolder(ROBOT_FILE_FOLDER);
	}
	if (! file.FileExist(ROBOT_FILE_PATH))
	{
		// 创建目录
		file.CreateFolder(ROBOT_FILE_PATH);
	}

	// RobotMode
	if (! Read_File((CString)ROBOT_FILE_PATH + "RobotMode.rcs", buf))
		return false;
	Robot::robotMode = atoi(buf);

	// ActTool
	if (! Read_File((CString)ROBOT_FILE_PATH + "ActTool.rcs", buf))
		return false;
	Robot::actualTool = atoi(buf);

	// RunMode
	if (! Read_File((CString)ROBOT_FILE_PATH + "RunMode.rcs", buf))
		return false;
	Robot::runMode = atoi(buf);

	// TeachMode
	Read_File((CString)ROBOT_FILE_PATH + "TeachMode.rcs", buf);
	Robot::teachMode = atoi(buf);

	// IfMonitor
	if (! Read_File((CString)ROBOT_FILE_PATH + "IfStartMonitor.rcs", buf))
		return false;
	Robot::ifMonitor = (atoi(buf)) ? true : false;

	// IfTool
	if (! Read_File((CString)ROBOT_FILE_PATH + "IfStartTool.rcs", buf))
		return false;
	Robot::ifTool = (atoi(buf)) ? true : false;

	// IfMaster
	if (! Read_File((CString)ROBOT_FILE_PATH + "IfStartMaster.rcs", buf))
		return false;
	Robot::ifMaster = (atoi(buf)) ? true : false;

	// IfWheel
	if (! Read_File((CString)ROBOT_FILE_PATH + "IfStartWheel.rcs", buf))
		return false;
	Robot::ifWheel = (atoi(buf)) ? true : false;

	// RobotLen, WRITE_MODE_ROBOTLEN
	Read_File((CString)ROBOT_FILE_PATH + "RobotLen_CR.rcs", str, 7, WRITE_MODE_ROBOTLEN);
	Read_File((CString)ROBOT_FILE_PATH + "RobotLen_IR.rcs", str, 7, WRITE_MODE_ROBOTLEN);
	Read_File((CString)ROBOT_FILE_PATH + "RobotLen_BR.rcs", str, 7, WRITE_MODE_ROBOTLEN);
	Read_File((CString)ROBOT_FILE_PATH + "RobotLen_WR.rcs", str, 7, WRITE_MODE_ROBOTLEN);
	CString strFile;
	switch(Robot::robotMode)
	{
	case ROBOT_MODE_SM:
	case ROBOT_MODE_DM:
	case ROBOT_MODE_CR_P:
	case ROBOT_MODE_CR_W:
		strFile = "RobotLen_CR.rcs";
		break;
	case ROBOT_MODE_IR_5:
	case ROBOT_MODE_IR_6:
		strFile = "RobotLen_IR.rcs";
		break;
	case ROBOT_MODE_BR:
		strFile = "RobotLen_BR.rcs";
		break;
	case ROBOT_MODE_WR:
		strFile = "RobotLen_WR.rcs";
		break;
	default:
		break;
	}

	// 
	if (! Read_File((CString)ROBOT_FILE_PATH + strFile, str, 7, WRITE_MODE_ROBOTLEN))
		return false;
	for (i=0; i<7; i++)
		Robot::robotLen[i] = atof(str[i]);

	// MotorRat, WRITE_MODE_MOTORRAT
	if (! Read_File((CString)ROBOT_FILE_PATH + "MotorRat.rcs", str, MAX_AXIS_NUM, WRITE_MODE_MOTORRAT))
		return false;
	for (i=0; i<MAX_AXIS_NUM; i++)
		Robot::motorRat[i] = atof(str[i]);

	// JPosLim, WRITE_MODE_JPOSLIM
	if (! Read_File((CString)ROBOT_FILE_PATH + "JPosLim.rcs", str, MAX_AXIS_NUM, WRITE_MODE_JPOSLIM))
		return false;
	for (i=0; i<MAX_AXIS_NUM; i++)
		Robot::posLim[i] = atof(str[i]);

	// JNegLim, WRITE_MODE_JNEGLIM
	if (! Read_File((CString)ROBOT_FILE_PATH + "JNegLim.rcs", str, MAX_AXIS_NUM, WRITE_MODE_JNEGLIM))
		return false;
	for (i=0; i<MAX_AXIS_NUM; i++)
		Robot::negLim[i] = atof(str[i]);

	// TeachLim, WRITE_MODE_TEACHLIM
	if (! Read_File((CString)ROBOT_FILE_PATH + "TeachLim.rcs", str, 6, WRITE_MODE_TEACHLIM))
		return false;
	for (i=0; i<6; i++)
		Robot::teachLim[i] = atof(str[i]);

	// AutoLim, WRITE_MODE_AUTOLIM
	if (! Read_File((CString)ROBOT_FILE_PATH + "AutoLim.rcs", str, 7, WRITE_MODE_AUTOLIM))
		return false;
	for (i=0; i<7; i++)
		Robot::autoLim[i] = atof(str[i]);


	return true;
}

/******************************************************************************
 * 函数：Set_RobotMode()
 * 功能：设置机器人构型模式
 *
 * 输入：unchar cMode - 机器人构型模式
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_RobotMode(IN unchar cMode)
{
	Robot::robotMode = cMode;

	// 根据构型不同，设置关节数目
	switch (cMode)
	{
	case ROBOT_MODE_SM:
		Robot::axisNum = 1;
		break;
	case ROBOT_MODE_DM:
		Robot::axisNum = 2;
		break;
	case ROBOT_MODE_CR_P:
	case ROBOT_MODE_CR_W:
	case ROBOT_MODE_IR_5:
	case ROBOT_MODE_WR:
		Robot::axisNum = 5;
		break;
	case ROBOT_MODE_IR_6:
	case ROBOT_MODE_BR:
		Robot::axisNum = 6;
		break;
	default:
		break;
	}

	// 设置机器人模式，即初始化一些变量
	CString str;
	str.Format("%d", cMode);
	if (Write_File((CString)ROBOT_FILE_PATH + "RobotMode.rcs", str))
	{
		Robot::I_Task.Set_RobotMode(Robot::robotMode);
		Robot::I_Monit.Set_RobotMode(Robot::robotMode);
		return true;
	}
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_ActTool()
 * 功能：设置当前工具
 *
 * 输入：unchar cTool - 当前工具
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_ActTool(IN unchar cTool)
{
	Robot::actualTool = cTool;

	CString str;
	str.Format("%d", cTool);
	if (Write_File((CString)ROBOT_FILE_PATH + "ActTool.rcs", str))
	{
		// 初始化Monitor
		Robot::I_Monit.Set_Grip(Robot::actualTool);
		Robot::I_Task.Set_GripNum(Robot::actualTool);
		return true;
	}
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_RunMode()
 * 功能：设置运动模式
 *
 * 输入：unchar cMode - 运动模式: 示教、再现
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_RunMode(IN unchar cMode)
{
	Robot::runMode = cMode;

	CString str;
	str.Format("%d", cMode);
	if (Write_File((CString)ROBOT_FILE_PATH + "RunMode.rcs", str))
	{
		Robot::I_Task.Set_RunMode(cMode);
		return true;
	}
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_TeachMode()
 * 功能：设置示教方式
 *
 * 输入：unchar cMode - 示教方式: 关节示教、笛卡儿示教
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_TeachMode(IN unchar cMode)
{
	Robot::teachMode = cMode;

	CString str;
	str.Format("%d", cMode);
	if (Write_File((CString)ROBOT_FILE_PATH + "TeachMode.rcs", str))
		return true;
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_IfStartDlg()
 * 功能：设置开始是否启动对话框(监控、工具)
 *
 * 输入：int nDlg - 对话框编号
 *       bool bIf - 启动标志
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_IfStartDlg(IN int nDlg, IN bool bIf)
{
	CString str = (bIf) ? "0" : "1";
	CString strPath;

	switch(nDlg)
	{
	case ID_MYDIALOG_MONITOR:
		Robot::ifMonitor = bIf;
		strPath = (CString)ROBOT_FILE_PATH + "IfStartMonitor.rcs";
		break;
	case ID_MYDIALOG_TOOL:
		Robot::ifTool = bIf;
		strPath = (CString)ROBOT_FILE_PATH + "IfStartTool.rcs";
		break;
	case ID_MYDIALOG_MASTER:
		Robot::ifMaster = bIf;
		strPath = (CString)ROBOT_FILE_PATH + "IfStartMaster.rcs";
		break;
	case ID_MYDIALOG_WHEEL:
		Robot::ifWheel = bIf;
		strPath = (CString)ROBOT_FILE_PATH + "IfStartWheel.rcs";
		break;
	default:
		break;
	}

	if (Write_File(strPath, str))
		return true;
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_RobotLen()
 * 功能：设置机器人杆长
 *
 * 输入：double dLen[] - 机器人杆长
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_RobotLen(IN double dLen[])
{
	CString str[7];
	int i;
	
	for (i=0; i<7; i++)
	{
		Robot::robotLen[i] = dLen[i];

		str[i].Format("%f", Robot::robotLen[i]);
	}

	CString strFile;
	switch(Robot::robotMode)
	{
	case ROBOT_MODE_CR_P:
	case ROBOT_MODE_CR_W:
		strFile = "RobotLen_CR.rcs";
		break;
	case ROBOT_MODE_IR_5:
	case ROBOT_MODE_IR_6:
		strFile = "RobotLen_IR.rcs";
		break;
	case ROBOT_MODE_BR:
		strFile = "RobotLen_BR.rcs";
		break;
	case ROBOT_MODE_WR:
		strFile = "RobotLen_WR.rcs";
		break;
	default:
		break;
	}

	if(Write_File((CString)ROBOT_FILE_PATH + strFile, str, 7))
	{
		// 重新初始化全局变量
		Robot::I_Task.Init(Robot::robotLen, Robot::motorRat);
		Robot::I_Monit.Init(Robot::robotLen);

		return true;
	}
	else
		return false;
}

/*****************************************************************************
 * 函数：Set_MotorRat()
 * 功能：设置减速比
 *
 * 输入：double dRat[] - 减速比
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_MotorRat(IN double dRat[])
{
	CString str[MAX_AXIS_NUM];
	int i;
	
	for (i=0; i<MAX_AXIS_NUM; i++)
	{
		if (i < JOINT_NUM)
		Robot::motorRat[i] = dRat[i];
		str[i].Format("%f", Robot::motorRat[i]);
	}
	
	if(Write_File((CString)ROBOT_FILE_PATH + "MotorRat.rcs", str, MAX_AXIS_NUM))
	{
		// 重新初始化全局变量
		Robot::I_Servo.Servo_Init(Robot::motorRat);
		Robot::I_Task.Init(Robot::robotLen, Robot::motorRat);
		
		return true;
	}
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_JPosLim()
 * 功能：设置关节正极限
 *
 * 输入：double dLim[] - 关节正极限
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_JPosLim(IN double dLim[])
{
	CString str[MAX_AXIS_NUM];
	int i;
	
	for (i=0; i<MAX_AXIS_NUM; i++)
	{
		if (i < JOINT_NUM)
			Robot::posLim[i] = dLim[i];
		str[i].Format("%f", Robot::posLim[i]);
	}
	
	if(Write_File((CString)ROBOT_FILE_PATH + "JPosLim.rcs", str, MAX_AXIS_NUM))
	{
		// 重新初始化全局变量
		Robot::I_Task.Set_Lim(Robot::posLim, Robot::negLim);
		
		return true;
	}
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_JNegLim()
 * 功能：设置关节负极限
 *
 * 输入：double dLim[] - 关节负极限
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_JNegLim(IN double dLim[])
{
	CString str[MAX_AXIS_NUM];
	int i;
	
	for (i=0; i<JOINT_NUM; i++)
	{
		if (i < JOINT_NUM)
			Robot::negLim[i] = dLim[i];
		str[i].Format("%f", Robot::negLim[i]);
	}
	
	if(Write_File((CString)ROBOT_FILE_PATH + "JNegLim.rcs", str, MAX_AXIS_NUM))
	{
		// 重新初始化全局变量
		Robot::I_Task.Set_Lim(Robot::posLim, Robot::negLim);
		
		return true;
	}
	else
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_TeachLim()
 * 功能：设置示教限制参数
 *
 * 输入：double dLim[] - 示教限制参数
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_TeachLim(IN double dLim[])
{
	CString str[6];
	int i;
	
	for (i=0; i<6; i++)
	{
		Robot::teachLim[i] = dLim[i];
		str[i].Format("%f", dLim[i]);
	}
	
	if(Write_File((CString)ROBOT_FILE_PATH + "TeachLim.rcs", str, 6))
	{		
		return true;
	}
	else
		return false;
	
	return true;
}

/*****************************************************************************
 * 函数：Set_AutoLim()
 * 功能：设置再现限制参数
 *
 * 输入：double dLim[] - 再现限制参数
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_AutoLim(IN double dLim[])
{
	CString str[7];
	int i;
	
	for (i=0; i<7; i++)
	{
		Robot::autoLim[i] = dLim[i];
		str[i].Format("%f", dLim[i]);
	}
	
	if(Write_File((CString)ROBOT_FILE_PATH + "AutoLim.rcs", str, 7))
	{		
		return true;
	}
	else
		return false;
	
	return true;
}

/*****************************************************************************
 * 函数：Set_SecZeroPos()
 * 功能：设置复位位置
 *
 * 输入：double dPos[] - 复位位置
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_SecZeroPos(IN double dPos[])
{
	CString str[MAX_AXIS_NUM];

	for(int i=0; i<MAX_AXIS_NUM; i++)
	{
		if (i<JOINT_NUM)
			str[i].Format("%f", dPos[i]);
		else
			str[i] = "0";
	}

	if (Write_File((CString)ROBOT_FILE_PATH + "SecZeroPos.rcs", str, MAX_AXIS_NUM))
	{
		return true;
	}
	else
		return false;
}

/*****************************************************************************
 * 函数：Get_SecZeroPos()
 * 功能：获取复位位置
 *
 * 输出：double dPos[] - 复位位置
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Get_SecZeroPos(OUT double dPos[])
{
	CString buf;
	CString str[MAX_AXIS_NUM];
	int i;

	// SecZeroPos, 0
	if (! Read_File((CString)ROBOT_FILE_PATH + "SecZeroPos.rcs", str, MAX_AXIS_NUM, 0))
		return false;
	for (i=0; i<MAX_AXIS_NUM; i++)
		dPos[i] = atof(str[i]);

	return true;
}

/*****************************************************************************
 * 函数：Get_SecZeroPos()
 * 功能：获取复位位置
 *
 * 输出：CString str[] - 复位位置, 字符串表示
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Get_SecZeroPos(OUT CString str[])
{
	if (! Read_File((CString)ROBOT_FILE_PATH + "SecZeroPos.rcs", str, MAX_AXIS_NUM, 0))
		return false;

	return true;
}

/*****************************************************************************
 * 函数：Set_ZeroVel()
 * 功能：设置回零复位速度
 *
 * 输入：int& vel - 回零复位速度, %表示
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Set_ZeroVel(IN int vel)
{
	CString str;
	str.Format("%d", vel);

	if (Write_File((CString)ROBOT_FILE_PATH + "ZeroVel.rcs", str))
		return true;
	else
		return false;
	
	return true;
}

/*****************************************************************************
 * 函数：Get_ZeroVel()
 * 功能：获取回零复位速度, %表示
 *
 * 输出：int& vel - 回零复位速度
 *
 * 返回：bool - true成功
 *****************************************************************************/
bool RobotFile::Get_ZeroVel(OUT int& vel)
{
	CString str;

	if (! Read_File((CString)ROBOT_FILE_PATH + "ZeroVel.rcs",str))
		return false;
	vel = atoi(str);

	return true;
}
