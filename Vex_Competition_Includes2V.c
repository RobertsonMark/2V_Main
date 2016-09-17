void allMotorsOff();
void pre_auton();
task autonomous();
task usercontrol();
task motorControl();
task LCDControl();



task main()
{
	clearLCDLine(0);
	clearLCDLine(1);
	displayLCDPos(0, 0);
	displayNextLCDString("Now Booting: ");
	displayLCDCenteredString(1, "ROBOSAVAGES 2eZ");
	wait1Msec(300);
	startTask(LCDControl);




	pre_auton();
	wait1Msec(300);


	while (true)
	{
		while (bIfiRobotDisabled)
		{

		}

		if (bIfiAutonomousMode)
		{


			startTask(autonomous);
			startTask(motorControl);


			while (bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (!bVEXNETActive)
				{
					if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
						allMotorsOff();
				}
				wait1Msec(25);               // Waiting for autonomous phase to end
			}

			stopTask(autonomous);

		}

		else
		{

			startTask(usercontrol);
			startTask(motorControl);


			// Here we repeat loop waiting for user control to end and (optionally) start
			// of a new competition run
			while (!bIfiAutonomousMode && !bIfiRobotDisabled)
			{
				if (nVexRCReceiveState == vrNoXmiters) // the transmitters are powered off!!
					allMotorsOff();
				wait1Msec(25);
			}
			stopTask(usercontrol);
			stopTask(motorControl);


		}
	}
}


void allMotorsOff()
{
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
#if defined(VEX2) || defined(VEX2_Simulator)
	motor[port9] = 0;
	motor[port10] = 0;
#endif
}
