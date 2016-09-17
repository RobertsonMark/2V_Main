#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    ArmEncoder,     sensorPotentiometer)
#pragma config(Sensor, in2,    ArmEncoder2,    sensorPotentiometer)
#pragma config(Sensor, in3,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl2,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  Wings,          sensorDigitalOut)
#pragma config(Sensor, dgtl8,  Pivot,          sensorDigitalOut)
#pragma config(Sensor, dgtl9,  Unlocker,       sensorDigitalOut)
#pragma config(Sensor, dgtl10, section,        sensorDigitalOut)
#pragma config(Motor,  port1,           RightBackDrive, tmotorVex393_HBridge, openLoop, driveRight)
#pragma config(Motor,  port2,           StrafeR,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightBottomArm, tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           RightTopArm,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           RightFrontDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           LeftFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LeftTopArm,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LeftBottomArm, tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port9,           StrafeL,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          LeftBackDrive, tmotorVex393_HBridge, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)



// Joystick Driver Control Variables
int LPower =0;
int RPower =0;
int HPower =0;
int driveDirectionF = 0;
int driveDirectionT = 0;
int driveDirectionH = 0;
int pot = 0;

int ArmPower = 0;
int ArmHeight = 0;
int ArmFunc = 0;
int autoNumber = 0;
int last_nLCDButtons_Value = 0;
int last_Btn7D_Value = 0;
int last_Btn5U_Value = 0;
int last_Btn7U_Value = 0;
//aaaaaaaaaaaa
//Arm Height
int A = -150; //-170; arm encoder
int C0 = 1290+A;//lowest arm height
int C1 = 1650+A;//1st cube height (getting ready to pick up)
int G2 = 2540+A;//2nd goal
int S0 = 1140+A;//Verylow
int S2 = 1570+A;
int S3 = 1780+A;
int S4 = 2040+A;
int S5 = 2280+A;
int S6 = 2520+A;
int S7 = 2830+A;

int H1 = 1600+A; // S2 becomes H1
int H2 = 1850+A; // S3 becomes H2

float De = 8.236;
float In = 8.231;

//Constant Varible
const int R = 9; // Right Turn
const int L = 8; // Left Turn
const int SR = 10; // Swing Right
const int SL = 11; // Swing Left
const int F = 1;
const int B = -1;
const int OFF = 0;
const int ON = 1;
const int minMovePower = 55;
const unsigned int TrueSpeed[128] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 0, 0, 0, 0, 22, 22, 23, 24, 24,       //0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

int motorCap(int motorPowervalue)
{

	if (motorPowervalue >= 127)
	{
		return (127);
	}
	else if (motorPowervalue <= -127)
	{
		return (-127);
	}
	return (motorPowervalue);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Vex_Competition_Includes2V.c"   //Main competition background code...do not modify!
#include "2V_AutoFunctions.c"
#include "2VAuto.c"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~Arm HoldPower and Armstates~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void armFunction()
{
	if(ArmFunc == ON)
	{
		int error = ArmHeight - abs(SensorValue[ArmEncoder]);
		float kp = 0.35;
		int Adjustment = error*kp;
		if (abs(Adjustment)>127)

		{
		ArmPower = (Adjustment > 0)? 127: -90; // if it's bigger than 0 then go up 127 if not then -90
		}
		else
		{
			ArmPower = Adjustment;
		}
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string msgTable[] =	 // Autonomous names
{
	"TurnR",
	"TurnL",
	"TurnR Nontg",
	"TurnL Nothg",
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
task motorControl()
{
	while(true)
	{
		motor[LeftBottomArm] = motor[LeftTopArm] = motor[RightBottomArm] = motor[RightTopArm] = ArmPower;
		motor[RightFrontDrive] = motor[RightBackDrive]= RPower;
		motor[LeftFrontDrive] = motor[LeftBackDrive] = LPower;
		motor[StrafeL] = motor [StrafeR] = HPower;
		armFunction();
		int pot = SensorValue[ArmEncoder];
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
task LCDControl()
{

	while(true)
	{

		int curr_nLCDButtons_Value = nLCDButtons;

		if(nLCDButtons == 4 && curr_nLCDButtons_Value != last_nLCDButtons_Value) // Decrease autoNumber
		{
			if (autoNumber < 3) autoNumber++;
		}
		else if(nLCDButtons == 1 && curr_nLCDButtons_Value != last_nLCDButtons_Value) // Increase autoNumber
		{
			if (autoNumber >0) autoNumber--;
		}


		clearLCDLine(0);
		displayLCDPos(0,0);
		displayNextLCDString("Battery:");
		displayLCDPos(0 ,9);
		displayNextLCDNumber(nAvgBatteryLevel);
		displayLCDPos(0,14);
		displayNextLCDString("mV");

		clearLCDLine(1);
		displayLCDPos(1,0);
		displayNextLCDString(msgTable[autoNumber]); // Show current autonomous name in line 2
		bLCDBacklight = true;
		wait1Msec(100);
		last_nLCDButtons_Value = curr_nLCDButtons_Value;

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////


void pre_auton()
{
	ArmHeight = SensorValue[ArmEncoder];
	intake();
	claw();
	brake();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
task autonomous()
{
	ArmFunc = ON;
	ArmHeight = SensorValue[ArmEncoder];
	intake(1);
	claw();
	brake();
	//~~~~~~INSEERT CODE UNDER~~~~~~~~~~~~~~~~~~~~ BBBBBBBBBBB
	//brake(1);
	//TurnADP(R,800,80,15000,0.12,0.30,30,0.15);
	//DriveADP(F,600,80,15000,-18,0.1,0.35,25,0.15);

//~~~~~~~~~~~~~~~~~~~~ from function~~~~~~~~~~~~~
	//TurnADP(R,800,127,15000,0.14,0.35,25,0.15);
	//void TurnADP(int turndirection , int ForwardTicks, int speed, int xtime, float Kd, float Ka, int minspeed, float Kf)

	//DriveADP(F,600,127,15000,-18,0.18,0.35,25,0.15);
	//void DriveADP (int direction, int ForwardTicks, int TargetPower,int xtime, int WheelBrake, float Kd, float Ka,int move, float Kf)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	switch(autoNumber) // Start autonomous based on autoNumber variable
	{
	case 0: TurnR();
		break;
	case 1: TurnL();
		break;
	case 2: TurnRN();
		break;
	case 3: TurnLN();
		break;
	}

	ArmHeight = SensorValue[ArmEncoder];
}

//////////////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	ArmFunc = ON;
	ArmHeight = SensorValue[ArmEncoder];
	brake();
	while (true)
	{
		//~~~~~~~~~~~~~~~~~~ Drive direction for Truespeed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if(vexRT[Ch3] > 10)
		{
			driveDirectionF = 1;
		}
		else if (vexRT[Ch3] < 10)
		{
			driveDirectionF = -1;
		}
		if(vexRT[Ch4] > 10)
		{
			driveDirectionH = 1;
		}
		else if (vexRT[Ch4] < 10)
		{
			driveDirectionH = -1;
		}
		if (vexRT[Ch1]>10)
		{
			driveDirectionT = 1;
		}
		else if (vexRT[Ch1]<10)
		{
			driveDirectionT = -1;
		}
		//~~~~~~~~~Drive Controls~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		LPower = motorCap((TrueSpeed[abs(vexRT[Ch1])]*driveDirectionT)+(TrueSpeed[abs(vexRT[Ch3])]*driveDirectionF));
		RPower = motorCap(-(TrueSpeed[abs(vexRT[Ch1])]*driveDirectionT)+(TrueSpeed[abs(vexRT[Ch3])]*driveDirectionF));
		HPower = motorCap(TrueSpeed[abs(vexRT[Ch4])]*driveDirectionH);

		//~~~~~~~~~~~~~~~~~~~~~~~~~ARM UP~~~~~~~~~~~~~~~~~~~~~~~~~~
		if (vexRT[Btn6U] == 1 && SensorValue[ArmEncoder]>3280+A)
		{
			ArmFunc = OFF;
			ArmPower = 10;
			if (SensorValue[ArmEncoder]> 3280+A)
			{
				ArmHeight = 3280+A;
			}
			else
			{
				ArmHeight = -1;
			}
		}
		else if (vexRT[Btn6U] == 1 && SensorValue[ArmEncoder]<3100+A)
		{

			ArmFunc = OFF;
			ArmPower = 127;
			ArmHeight = -1;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ARM DOWN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		else if (vexRT[Btn6D] == 1 && SensorValue[ArmEncoder]<1290+A)
		{
			ArmFunc = OFF;
			ArmPower = -10;
			ArmHeight = 1580+A;
		}

		else if (vexRT[Btn6D] == 1 && SensorValue[ArmEncoder]>(1290+A))
		{
			ArmFunc = OFF;
			ArmPower = -127;
			ArmHeight = -1;
		}
		else if (vexRT[Btn7R] ==1 && SensorValue[ArmEncoder]<1290+A)
		{
			ArmFunc = OFF;
			ArmPower = -10;
			ArmHeight = -1;
		}
		else if (vexRT[Btn7R] ==1)
		{
			ArmFunc = OFF;
			ArmPower = -70;
			ArmHeight = -1;
		}

		//~~~~~~~~~~~~~~~~~ ARM ELSE~~~~~~~~~~~~~~~~~~~~~
		else
		{
			if (ArmHeight == -1)
			{
				ArmPower = 0;
			}
			else
			{
				ArmFunc = ON;
			}
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ARM STATES MAIN CONTROLLER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~````
		if (vexRT[Btn8U] ==1)
		{
			ArmHeight = 2850+A; // high goal
		}
		if (vexRT[Btn8R] ==1)
		{
			ArmHeight = 2540+A; // medium goal
		}
		if (vexRT[Btn8D] ==1)
		{
			ArmHeight = 2055+A; // lowest goal
		}
		if (vexRT[Btn8L] ==1)
		{
			ArmHeight = 1480+A; // cube height
		}
		if (vexRT[Btn7L] == 1)
		{
			ArmHeight = S7+320; //7TH skyrise
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Automatic Arm Height with claw~~~~~~~~~~~~~~~~~~~bbbbbbbbbbbb~~~~~~~~~~~~~
		if (vexRT[Btn5U] == 1)
		{
			if (vexRT[Btn5UXmtr2] ==1)
			{
				ArmHeight = S2; //1600+A-10; //S1,S2
			}
			else if (vexRT[Btn7UXmtr2] ==1)
			{
				ArmHeight = S3; //1800+A-20; // S3
			}
			else if (vexRT[Btn7RXmtr2] ==1)
			{
				ArmHeight = S4; //2040+A-20; //S4
			}
			else if (vexRT[Btn7DXmtr2] ==1)
			{
				ArmHeight = S5; //2280+A-20; //S5
			}
			else if (vexRT[Btn7LXmtr2] ==1)
			{
				ArmHeight = S6; //2520+A-20; //S6
			}
			else if (vexRT[Btn8UXmtr2] ==1)
			{
				ArmHeight = S7; //2830+A-20; //S7
			}
			else
			{
				ArmHeight = C0-20;
			}
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~CLAW~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int curr_Btn5U_Value = vexRT[Btn5U];
		if (vexRT[Btn5U] ==1 && curr_Btn5U_Value != last_Btn5U_Value && SensorValue[section] ==0)
		{
			SensorValue[section] = 1;
		}
		else if (vexRT[Btn5U] ==1 && curr_Btn5U_Value != last_Btn5U_Value && SensorValue[section] == 1)
		{
			SensorValue[section] = 0;
		}
		last_Btn5U_Value = curr_Btn5U_Value;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~PIVOT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		int curr_Btn7D_Value = vexRT[Btn7D];
		if (vexRT[Btn7D] ==1 && curr_Btn7D_Value != last_Btn7D_Value && SensorValue[Pivot] ==0)
		{
			SensorValue[Pivot] = 1;
		}
		else if (vexRT[Btn7D] ==1 && curr_Btn7D_Value != last_Btn7D_Value && SensorValue[Pivot] == 1)
		{
			SensorValue[Pivot] = 0;
		}
		last_Btn7D_Value = curr_Btn7D_Value;

		//~~~~~~~~~~~~~~~~~~~WING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		int curr_Btn7U_Value = vexRT[Btn7U];
		if (vexRT[Btn7U] ==1 && curr_Btn7U_Value != last_Btn7U_Value && SensorValue[Wings] ==0)
		{
			SensorValue[Wings] = 1;
		}
		else if (vexRT[Btn7U] ==1 && curr_Btn7U_Value != last_Btn7U_Value && SensorValue[Wings] == 1)
		{
			SensorValue[Wings] = 0;
		}
		last_Btn7U_Value = curr_Btn7U_Value;

		//~~~~~~~~~~~~~~~~~~~~~~~~~UNLOCKER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if (vexRT [Btn5D] == 1)
		{
			SensorValue[Unlocker] = 1;
		}
		else
		{
			SensorValue[Unlocker] = 0;
		}
	}
}