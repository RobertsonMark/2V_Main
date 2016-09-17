void intake(int x = 0)
{
	SensorValue[Unlocker] = x;
}

void brake(int x = 0)
{
	SensorValue[Pivot] = x;
}

void claw(int x = 0)
{
	SensorValue[section] = x;
}

void wing (int x = 0)
{
	SensorValue[Wings] = x;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DRIVE ACCLERATION AND DECELERATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`



void DriveADP (int direction = 1, int ForwardTicks, int TargetPower = 127,int xtime = 15000, int WheelBrake = -18, float Kd = 0.18, float Ka = 0.35 ,
int move = 25, float Kf = 0.15)
{
	float error = 0;
	float derivitive = 0;
	float previous_error =0;
	clearTimer(T1);
	float pSpeed = 0; // set extra speed to 0
	SensorValue [RightEncoder]= SensorValue [LeftEncoder] = 0;

	while (((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder]))/2) < ForwardTicks && time1[T1] < xtime)
	{
		error = ForwardTicks-SensorValue[LeftEncoder];
		if (((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder]))/2)< (ForwardTicks*0.5))
		{
			pSpeed = ((((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder])) / 2))*Ka);
			int Adjustment = ((SensorValue[RightEncoder]) - (SensorValue[LeftEncoder])) * 1.0;
			if (abs(pSpeed+minMovePower)>TargetPower)
			{

			RPower =((direction > 0)? TargetPower - Adjustment: -TargetPower - Adjustment);
			LPower =((direction > 0)? TargetPower + Adjustment: -TargetPower + Adjustment);
			}
			else
			{
				RPower = (direction*minMovePower) + (direction*pSpeed) - Adjustment;
				LPower = (direction*minMovePower) + (direction*pSpeed) + Adjustment;
			}
		}
		else
		{
			pSpeed = ((ForwardTicks - ((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder])) / 2))*Kd);
			int Adjustment = ((SensorValue[RightEncoder]) - (SensorValue[LeftEncoder])) * 1.0;
			if (abs(pSpeed+move+Adjustment)>TargetPower)
			{

			RPower =((direction > 0)? TargetPower - Adjustment: -TargetPower - Adjustment);
			LPower =((direction > 0)? TargetPower + Adjustment: -TargetPower + Adjustment);
			}
			else
			{
				RPower = (direction*move) + (direction*pSpeed) - Adjustment+(direction*derivitive*Kf);
				LPower = (direction*move) + (direction*pSpeed) + Adjustment+(direction*derivitive*Kf);
			}
		}
	}
	RPower = LPower = direction*WheelBrake;
	pSpeed = 0;

}

//~~~~~~~~~~~~~~~~~~~~~~~~Turns~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Turn (int turndirection, int ForwardTicks, int TargetPower = 127,int xtime = 15000, int slowspeed  = -10)
{
	SensorValue[RightEncoder] = SensorValue[LeftEncoder] = 0;
	clearTimer(T1);
	if (turndirection == 8)
	{
		while (abs(SensorValue[RightEncoder]) < ForwardTicks && time1[T1] < xtime)
		{
			RPower = TargetPower;
			LPower = -TargetPower;
		}
	}
	else if(turndirection == 9)
	{
		while (abs(SensorValue [LeftEncoder]) < ForwardTicks && time1[T1] < xtime)
		{
			RPower = -TargetPower;
			LPower = TargetPower;
		}
	}
	else if (turndirection == 10) //swingLEFT
	{
		while(abs(SensorValue[LeftEncoder]) < ForwardTicks && time1[T1] < xtime)
		{
			RPower = slowspeed;
			LPower = TargetPower;
		}
		RPower = -0.1*slowspeed;
		LPower = -0.1*TargetPower;
	}
	else if (turndirection == 11) //swingRIGHT
	{
		while(abs(SensorValue[RightEncoder]) < ForwardTicks && time1[T1] < xtime)
		{
			RPower = TargetPower;
			LPower = slowspeed;
		}
		LPower = -0.1*slowspeed;
		RPower = -0.1*TargetPower;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ACCELERATION,DECELERATION TURN~~~~~~~~~~~~~~~~~~~~~~~~
void TurnADP(int turndirection , int ForwardTicks, int speed = 127, int xtime = 15000, float Kd = 0.14, float Ka = 0.35, int minspeed = 25, float Kf = 0.15)// find Kf value
{
	SensorValue[RightEncoder] = 0;
	SensorValue[LeftEncoder] = 0;
	float pSpeed = 0;
	clearTimer(T1);
	int error = 0;
	int derivitive = 0;
	int previous_error = 0;

	if(turndirection == 9) //RIGHT
	{
		while(abs(SensorValue[LeftEncoder]) < ForwardTicks && time1[T1]<xtime)
		{
			error = ForwardTicks-SensorValue[LeftEncoder];
			if(abs(SensorValue[LeftEncoder])<ForwardTicks*0.5) // start to accelerate with a minimum motor value
			{
				pSpeed = minMovePower+(abs(SensorValue[LeftEncoder])*Ka); // if you drive to fast you cap it
				if(pSpeed>speed)
				{
					RPower= -speed;
					LPower= +speed;
				}
				else
				{
					RPower = -pSpeed; // if the speed isn't to high, use that
					LPower = +pSpeed;
				}
			}
			else
			{
				pSpeed = minspeed+(ForwardTicks - (abs(SensorValue[LeftEncoder])))*Kd; // after reaching half the distance, you start to deaccelerate
				if (pSpeed>speed) // if it's driving too fast, it gets capped
				{
					RPower = -speed;
					LPower = +speed;
				}
				else
				{
					RPower = -pSpeed+(derivitive*Kf); // if it's driving under the capped value, just use that
					LPower = +pSpeed+(derivitive*Kf);
				}
				derivitive = error-previous_error;
				previous_error = error;
			}
		}
		RPower = 18; // brake, then stop
		LPower = -18;
	}
	if(turndirection == 8) //Left
	{
		while(abs(SensorValue[RightEncoder]) < ForwardTicks && time1(T1)<xtime)
		{
			if(abs(SensorValue[RightEncoder])<ForwardTicks*0.5)
			{
				pSpeed = minMovePower+(abs(SensorValue[RightEncoder])*Ka);
				if(pSpeed>speed)
				{
					RPower= +speed;
					LPower= -speed;
				}
				else
				{
					RPower = +pSpeed;
					LPower = -pSpeed;
				}
			}
			else
			{
				pSpeed = minspeed+((ForwardTicks - (abs(SensorValue[RightEncoder])))*Kd);
				if (pSpeed>speed)
				{
					RPower = +speed;
					LPower = -speed;
				}
				else
				{
					RPower = +pSpeed+(derivitive*Kf);
					LPower = -pSpeed+(derivitive*Kf);
				}
				derivitive = error-previous_error;
				previous_error = error;
			}
		}
		RPower = -18;
		LPower = +18;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DRIVE ACCLERATION ONLY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void DriveAP(int direction = 1, int ForwardTicks, int TargetPower = 127, int WheelBrake = -10 ,int xtime = 15000, float Ka = 0.35)
{
	clearTimer(T1);
	float pSpeed = 0;
	SensorValue[LeftEncoder] = SensorValue[RightEncoder] = 0;

	while(((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder])) / 2) < ForwardTicks && time1[T1] < xtime)
	{
		pSpeed = ((((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder])) / 2))*Ka);
		int Adjustment = (SensorValue[RightEncoder] - SensorValue[LeftEncoder]) * 1.0;
		if (abs(pSpeed+minMovePower)>TargetPower)
		{

		RPower =((direction > 0)? TargetPower - Adjustment: -TargetPower + Adjustment); // direction > 0? if so, do the first line
		LPower =((direction > 0)? TargetPower + Adjustment: -TargetPower - Adjustment);
		}
		else
		{
			RPower = (direction*minMovePower) + (direction*pSpeed) - Adjustment;
			LPower = (direction*minMovePower) + (direction*pSpeed) + Adjustment;
		}
	}
	RPower = LPower = direction*WheelBrake;
	wait1Msec(100);
	RPower = 0;
	LPower = 0;
	pSpeed = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DRIVE DECELERATION ONLY~~~~~~~~~~~~~~~~~~~~~~~~~

void DriveDP(int direction = 1, int ForwardTicks, int TargetPower = 127, int WheelBrake = -18 ,int xtime = 15000 , float K = 0.15)
{
	clearTimer(T1);
	float pSpeed = 0;
	SensorValue[LeftEncoder] = SensorValue[RightEncoder] = 0;
	while(((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder])) / 2) < ForwardTicks && time1[T1] < xtime)
	{
		pSpeed = ((ForwardTicks - ((abs(SensorValue[RightEncoder]) + abs(SensorValue[LeftEncoder])) / 2))*K);
		int Adjustment = ((SensorValue[RightEncoder]) - (SensorValue[LeftEncoder])) * 1.0;
		if (abs(pSpeed+minMovePower)>TargetPower)
		{

		RPower =((direction > 0)? TargetPower - Adjustment: -TargetPower - Adjustment);
		LPower =((direction > 0)? TargetPower + Adjustment: -TargetPower + Adjustment);
		}
		else
		{
			RPower = (direction*minMovePower) + (direction*pSpeed) - Adjustment;
			LPower = (direction*minMovePower) + (direction*pSpeed) + Adjustment;
		}

	}
	RPower = LPower = WheelBrake*direction;
	pSpeed = 0;
}
