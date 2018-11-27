#ifndef __SETUP_H__
#define __SETUP_H__
/*****************************************************************************
 *        Robot公共变量及Robot系统文件操作类                                 *
 *        SCUT, 2011                                                         *
 *        Author :                                                           *
 *        Version number :  0.10                                             *
 *        Date :            2011-04-22                                       *
 *****************************************************************************/
#include "Robot.h"

//#include "TaskControl.h"
//#include "ServoControl.h"
//#include "Monitor.h"
//#include "PumpControl.h"
//#include "masterdlg.h"

#define unchar  unsigned char


#define USING_CBUTTONST  // CButtonST使能
//#define USING_DAQ_FSR  // FSR使能

#define WM_MY_MESSAGE            WM_USER + 101  // 消息 - 测试用
#define WM_WELCOME_HIDE_MESSAGE  WM_USER + 102  // 消息 - Welcome界面
#define WM_MAIN_DLG_MESSAGE      WM_USER + 103  // 消息 - 主界面
#define WM_SETUPDLG_MESSAGE      WM_USER + 104  // 消息 - 参数设置
#define WM_FILE_OPERATE_MESSAGE  WM_USER + 105  // 消息 - 文件操作

#define SW_WELCOME_HIDE        1   // 消息参数 - Welcome界面显示
#define SW_WELCOME_SHOW        2   // 消息参数 - Welcome界面隐藏
#define SW_WELCOME_EXIT        3   // 消息参数 - Welcome界面退出

#define MY_FILE_NEW            1   // 消息参数 - 新建文件
#define MY_FILE_OPEN           2   // 消息参数 - 打开文件
#define MY_FILE_CLOSE          3   // 消息参数 - 关闭文件
#define MY_FILE_SAVE           4   // 消息参数 - 保存文件
#define MY_FILE_SAVEAS         5   // 消息参数 - 文件另存为

#define MY_FILE_GET_STARPOINT  7   // 消息参数 - 获取五角星顶点
#define MY_FILE_MOVE_SINGLE    8   // 消息参数 - 单步运动
#define MY_FILE_MOVE_ALL       9   // 消息参数 - 启动再现运动
#define MY_FILE_MOVE_FROMHERE 10   // 消息参数 - 从当前位置启动再现运动
#define MY_FILE_MOVE_STOP     11   // 消息参数 - 停止运动

#define MY_TEST_MOVES         15


#define MY_MONITORDLG_CLOSE 1
#define MY_TOLLDLG_CLOSE    2
#define MY_OPENGLDLG_CLOSE  3
#define MY_FSRDLG_CLOSE     4 
#define MY_MASTERDLG_CLOSE  5
#define MY_WHEELDLG_CLOSE	6


#define WRITE_MODE_ROBOTLEN  1   // 写文件类型 - 杆长
#define WRITE_MODE_MOTORRAT  2   // - 减速比
#define WRITE_MODE_JPOSLIM   3   // - 正极限
#define WRITE_MODE_JNEGLIM   4   // - 负极限
#define WRITE_MODE_TEACHLIM  5   // - 示教参数
#define WRITE_MODE_AUTOLIM   6   // - 再现参数

#define ROBOT_FILE_FOLDER  "D:/Robot/"                   // 系统文件夹路径
#define ROBOT_FILE_PATH    "D:/Robot/RobotPara/"         // 系统文件路径
#define ROBOT_FILE_CME2    "D:/Program Files/Copley Motion/CME 2/CME2.exe" // 模块调式软件路径
#define ROBOT_PATH_CME2    "D:/Program Files/Copley Motion/CME 2/"         // 模块调式软件文件夹路径

// 全局静态变量
/*class Robot
{
public:
/////////////////////////////////////////////////////////////////////////// 属性
// [[ 公共静态类对象
	static ServoControl I_Servo; // 伺服控制类
	static Monitor      I_Monit; // 监控类
	static TaskControl  I_Task;  // Task队列
	static PumpControl  I_Pump;  // 吸盘气泵控制类
//	static CMasterDlg	I_Master;// 主机器人类
// ]] 公共静态类对象

// [[ 公共静态变量
	static unchar axisNum;
	static unchar robotMode;  // 模式, 1爬杆,2爬壁,3机械手
	static unchar robotEndMode;	//末端执行器类型
	static unchar actualTool; // 当前手爪, #1, #2
	static unchar runMode;    // 运动模式, 1示教, 2再现
	static unchar teachMode;  // 示教模式, 1关节示教, 2笛卡尔示教
	static bool ifMonitor;	  // 开机是否监控
	static bool ifTool;
	static bool ifMaster;
	static bool ifWheel;
	static double robotLen[7]; // 机器人杆长
	static double motorRat[MAX_AXIS_NUM]; // 减速比
	static double posLim[MAX_AXIS_NUM];   // 正极限
	static double negLim[MAX_AXIS_NUM];   // 负极限
	// 示教限制参数, 关节速度|加速度|笛卡尔线速度|线加速度|角速度|角加速度
	static double teachLim[6];
	static double autoLim[7];
// ]] 公共静态变量
};*/

// 系统文件操作
class RobotFile
{
public:
///////////////////////////////////////////////////////////// 构造、析构、初始化
	RobotFile();
	~RobotFile();	
	bool Init();  // 初始化全局变量

public:
/////////////////////////////////////////////////////////////////////// 公用方法
// [[ 设置
	bool Set_RobotMode(IN unchar cMode);   // 设置机器人构型模式
	bool Set_ActTool(IN unchar cTool);     // 设置当前工具
	bool Set_RunMode(IN unchar cMode);     // 设置运动模式
	bool Set_TeachMode(IN unchar cMode);   // 设置示教模式
	bool Set_IfStartDlg(IN int nDlg, IN bool bIf);// 设置是否打开窗体
	bool Set_RobotLen(IN double dLen[]);   // 设置机器人杆长
	bool Set_MotorRat(IN double dRat[]);   // 设置减速比
	bool Set_JPosLim(IN double dLim[]);    // 设置正极限
	bool Set_JNegLim(IN double dLim[]);    // 设置负极限
	bool Set_TeachLim(IN double dLim[]);   // 设置示教限制
	bool Set_AutoLim(IN double dLim[]);    // 设置再现限制
	bool Set_SecZeroPos(IN double dPos[]); // 设置复位位置
	bool Set_ZeroVel(IN int vel);          // 设置回零复位速度等级
// ]] 设置

// [[ 读取
	/*
	unchar Get_RobotMode() const;
	unchar Get_ActTool() const;
	unchar Get_RunMode() const;
	unchar Get_TeachMode() const;
	bool Get_IfStartMonitor() const;	
	void Get_RobotLen(OUT double dLen[]) const;
	void Get_MotorRat(OUT double dRat[]) const;
	void Get_JPosLim(OUT double dLim[]) const;
	void Get_JNegLim(OUT double dLim[]) const;
	*/
	//bool Get_SecZeroPos(OUT double dPos[]); // 获取复位位置
	//bool Get_SecZeroPos(OUT CString str[]); // 获取复位位置字符串
	//bool Get_ZeroVel(OUT int& vel);         // 获取回零复位速度等级
// ]] 读取

/*private:
	/////////////////////////////////////////////////////////////////////// 私有方法
	CStdioFile m_file;
	bool Read_File(IN CString path, OUT CString& str);
	bool Read_File(IN CString path, OUT CString str[], IN int num, IN int mode);
	bool Write_File(IN CString path, IN CString str);
	bool Write_File(IN CString path, IN CString str[], IN int num);*/
};

#endif
