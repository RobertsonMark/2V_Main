/*

1.Drive   (int ForwardTicks, int TargetPower = 127, int WheelBrake =-10, int xtime= 15000)
2.DriveDP (int direction = 1, int ForwardTicks, int TargetPower = 127, int WheelBrake = -10 ,int xtime = 15000 , float K = 0.25)
3.DriveADP(int direct ion = 1, int ForwardTicks, int TargetPower = 127,int WheelBrake = -10, int xtime = 15000, float Kd = 0.30, float Ka = 0.45)
4.Turn    (int turndirection, int ForwardTicks, int TargetPower = 60,int xtime = 15000, int slowspeed  = -10)
5.TurnDP  (int turndirection , int ForwardTicks, int speed = 127, float K = 0.35)
6.TurnADP (int turndirection , int ForwardTicks, int speed = 90, int xtime = 15000, float Kd = 0.15, float Ka = 0.30, int minspeed = 30)
8.Arm     (int Height, int Speed = 100)

9.ArmHeight =
C(0,1) = Cube Height
G(1-3) = Goal Height
S(0-7) = Skyrise Height
P      = pag holder height

10.Directions
Left Turn East  = 525
Left Turn South = 1050
Right Turn West = 600
Right Turn South= 1200

11.Pneumatics                                         Natural
SensorValue[section] = 0; (unlock)                  = claw()
SensorValue[Unlocker]= 0; (lock)                    = intake ()
SensorValue[Pivot] = 0;   (off)                     = brake  ()
*/
//~~~~~~~~~~~~~~~~~~~~~~~ TURN LEFT Blue~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TurnL()
{
	ArmHeight = C1+10;
	untilPotentiometerGreaterThan(C1-50,pot);
	ArmHeight = C1-190;
	DriveADP(F,620);
	ArmHeight = S0-110;
	wait1Msec(300);
	intake();
	ArmHeight = G2-50;
	DriveADP(F,420); //2nd forward for cube //
	wait1Msec(150);
	Turn(SL,1620,127,2500);                        // SR Turn
	DriveADP(F,100,90,190);
	DriveADP(B,160,100); //60
	ArmHeight = G2-210;
	wait1Msec(100);
	intake(1);                // outake the cubes
	wait1Msec(200);
	DriveAP(B,250,90);
	ArmHeight = C1-190;
	DriveDP(B,595);
	wait1Msec(100);
	SensorValue[Pivot] = 1;
	TurnADP(L,1406,90,4000,0.13,0.4,40);                      // Turn for cube~~~~~~~~~~~~~~~~~~~TURN
	wait1Msec(150);
	SensorValue[Pivot] = 0;
	DriveADP(F,550); // driveforward for 1st cube
	ArmHeight = S0-40;
	wait1Msec(340);
	intake();
	wait1Msec(20);
	ArmHeight = H2-10;
	untilPotentiometerGreaterThan(H2-100,pot);
	ArmHeight = SensorValue[pot];
	DriveADP(F,370,90,2000,0.3,0.4,40);                       // drive forward for 2nd cube
	ArmHeight = C0;
	intake(1);
	wait1Msec(430);
	intake();
	ArmHeight = G2-30;
	DriveADP(B,1000);
	wait1Msec(250);
	brake(1);
	TurnADP(L,1416,90,4000,0.13,0.4,40); //2nd turn
	wait1Msec(120);// 2nd turn back
	brake(0);
	DriveADP(F,770,90,150000,-10,0.20,0.40,50);
	wait1Msec(300);
	//ArmHeight = G2-300;
	intake(1);
	wait1Msec(400);
	DriveDP(B,400);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~ TURN RIGHT FOR RED~~~~~~~~~~~~~~~~~~~~~~~~~~~~NEW VERSON~~~~~~~~

void TurnR()
{
	ArmHeight = C1+10;
	untilPotentiometerGreaterThan(C1-50,pot);
	ArmHeight = C1-190;
	DriveADP(F,590);
	ArmHeight = S0-110;
	wait1Msec(300);
	intake();
	ArmHeight = G2-50;
	DriveADP(F,470); //2nd forward for cube //
	wait1Msec(150);
	Turn(SR,1630,127,2500);                        // SR Turn
	DriveADP(F,200,90,200);
	DriveADP(B,180,100); //60
	ArmHeight = G2-140;
	wait1Msec(170);
	intake(1);                // outake the cubes
	wait1Msec(200);
	DriveAP(B,230,90);
	ArmHeight = C1-190;
	DriveDP(B,595);
	wait1Msec(100);
	SensorValue[Pivot] = 1;
	TurnADP(R,1387,90,4000,0.13,0.4,40);                      // Turn for cube~~~~~~~~~~~~~~~~~~~TURN
	wait1Msec(150);
	SensorValue[Pivot] = 0;
	DriveADP(F,540); // driveforward for 1st cube //560
	ArmHeight = S0-40;
	wait1Msec(340);
	intake();
	wait1Msec(20);
	ArmHeight = H2-10;
	untilPotentiometerGreaterThan(H2-100,pot);
	ArmHeight = SensorValue[pot];
	DriveADP(F,370,90,2000,0.3,0.4,40);                       // drive forward for 2nd cube
	ArmHeight = C0;
	intake(1);
	wait1Msec(430);
	intake();
	ArmHeight = G2-30;
	DriveADP(B,1000);
	wait1Msec(250);
	brake(1);
	TurnADP(R,1416,90,4000,0.13,0.4,40); //2nd turn
	wait1Msec(120);// 2nd turn back
	brake(0);
	DriveADP(F,700,90,150000,-10,0.16,0.40,50);
	wait1Msec(100);
	ArmHeight = G2-200;
	wait1Msec(100);
	intake(1);
	wait1Msec(400);
	ArmHeight = G2+100;
	wait1Msec(100);
	DriveDP(B,400);
}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~RED SECTION SKYRISE GOING FOR 6~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RedSkyrise()
{
	brake(1);
	wing(1);
	ArmHeight = S2+30;             //arm up to release claw and turn

	//~~~~~~~~~~~~~~~ 1st skyrise~~~~~~~~~~~~~~~~
	TurnADP(R,260,90,1500,0.20,0.4,35);
	ArmHeight = C0+80;
	untilPotentiometerLessThan(C0+90,pot);
	claw(1);                 // grab skyrise
	wait1Msec(150);
	ArmHeight = S2-30;
	wait1Msec(150);
	TurnADP(L,630,90,1500);
	wait1Msec(200);
	ArmHeight = C0-10;
	untilPotentiometerLessThan(C0,pot);
	wait1Msec(300);
	claw();     //score

	////~~~~~~~~~~~~~~~ 2nd skyrise~~~~~~~~~~~~~~~~

	TurnADP(R,560,90,1500,0.20,0.4,35);   //turn back to skyrise
	claw(1);
	wait1Msec(50);
	ArmHeight = S2+10;
	wait1Msec(100);
	TurnADP(L,590,1500);
	wait1Msec(100);
	ArmHeight = S2-170;
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	////	////~~~~~~~~~~~~~~~ 3rd skyrise~~~~~~~~~~~~~~~~

	TurnADP(R,540,90,1500,0.30,0.4,40);
	claw(1);
	wait1Msec(50);
	ArmHeight = S3+25;
	wait1Msec(100);
	TurnADP(L,570,1500);
	wait1Msec(100);
	ArmHeight = S3-130;
	wait1Msec(200);
	claw();
	wait1Msec(50);
	ArmHeight = C0-20;

	////	////~~~~~~~~~~~~~~~ 4th skyrise~~~~~~~~~~~~~~~~

	TurnADP(R,532,90,1500,0.30,0.4,40);
	claw(1);
	wait1Msec(50);
	ArmHeight = S4-10;
	wait1Msec(100);
	TurnADP(L,580,90,2000);
	wait1Msec(100);
	ArmHeight = S4-130;
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	////	////~~~~~~~~~~~~~~~ 5th skyrise~~~~~~~~~~~~~~~~

	TurnADP(R,530,90,1500,0.30,0.4,40);
	claw(1);
	wait1Msec(50);
	ArmHeight = S5-60;
	wait1Msec(100);
	TurnADP(L,560,90,2000);
	wait1Msec(100);
	ArmHeight = S5-170;
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	////	//////~~~~~~~~~~~~~~~6th skyrise~~~~~~~~~~~~~~~~

	TurnADP(R,490,90,1500,0.30,0.4,40);
	claw(1);
	wait1Msec(50);
	ArmHeight = S6-90;
	wait1Msec(100);
	TurnADP(L,580,90,2000);
	wait1Msec(100);
	ArmHeight = S6-180;
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;
	brake();
	wing();
	TurnADP(R,200,127,1500,0.30,0.4,50);
	TurnADP(L,50);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BLUE SECTION SKYRISE GOING FOR 6~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void BlueSkyrise()
{
	brake(1);
	wing(1);
	ArmHeight = S2+30;             //arm up to release claw and turn

	//~~~~~~~~~~~~~~~BLUE  1st skyrise~~~~~~~~~~~~~~~~
	TurnADP(L,300,90,1500,0.20,0.4,35); //295
	ArmHeight = C0+90;
	untilPotentiometerLessThan(C0+100,pot);
	claw(1);                 // grab skyrise
	wait1Msec(150);
	ArmHeight = S2-10;
	wait1Msec(150);
	TurnADP(R,610,90,1500);
	wait1Msec(300);
	ArmHeight = C0-15;
	wait1Msec(500);
	claw();     //score

	////~~~~~~~~~~~~~~~BLUE  2nd skyrise~~~~~~~~~~~~~~~~

	TurnADP(L,550,90,1500,0.20,0.4,35);    //turn back to skyrise
	wait1Msec(50);
	claw(1);
	ArmHeight = S2+10;
	wait1Msec(100);
	TurnADP(R,630,90,1500);
	ArmHeight = S2-190;//-150
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	//~~~~~~~~~~~~~~~BLUE  3rd skyrise~~~~~~~~~~~~~~~~

	TurnADP(L,550,90,1500,0.30,0.4,40);
	wait1Msec(50);
	claw(1);
	//wait1Msec(50);
	ArmHeight = S3+40;
	wait1Msec(100);
	TurnADP(R,620,90,1500);
	wait1Msec(80);
	ArmHeight = S3-130;//-80
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	//////	////~~~~~~~~~~~~~~~BLUE  4th skyrise~~~~~~~~~~~~~~~~

	TurnADP(L,550,90,1500,0.30,0.4,40);
	claw(1);
	wait1Msec(50);
	ArmHeight = S4-10;
	wait1Msec(100);
	TurnADP(R,585,90,2000);
	wait1Msec(100);
	ArmHeight = S4-190; //-150
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	//////	////~~~~~~~~~~~~~~~BLUE 5th skyrise~~~~~~~~~~~~~~~~

	TurnADP(L,550,90,1500,0.30,0.4,40);
	claw(1);
	ArmHeight = S5-30;
	wait1Msec(100);
	TurnADP(R,580,90,1500);
	wait1Msec(200);
	ArmHeight = S5-230; //-180
	wait1Msec(250);
	claw();
	ArmHeight = C0-10;

	//////	//////~~~~~~~~~~~~~~~BLUE 6th skyrise~~~~~~~~~~~~~~~~

	TurnADP(L,540,90,1500,0.30,0.4,40);
	claw(1);
	ArmHeight = S6-40;
	wait1Msec(100);
	TurnADP(R,570,90,1500);
	wait1Msec(100);
	ArmHeight = S6-160;
	wait1Msec(250);
	claw();
	ArmHeight = C0-20;
	brake();
	wing();
	TurnADP(L,200,127,1500,0.30,0.4,50);
}



//~~~~~~~~~~~~~~~~~~~~~~~ TURN LEFT Blue~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void TurnLN()
{
	ArmHeight = C1+10;
	untilPotentiometerGreaterThan(C1-50,pot);
	ArmHeight = C1-190;
	DriveADP(F,620);
	ArmHeight = S0-110;
	wait1Msec(300);
	intake();
	ArmHeight = G2-50;
	DriveADP(F,420); //2nd forward for cube //
	wait1Msec(150);
	Turn(SL,1620,127,2500);                        // SR Turn
	DriveADP(F,100,90,190);
	DriveADP(B,160,100); //60
	ArmHeight = G2-210;
	wait1Msec(100);
	intake(1);                // outake the cubes
	//wait1Msec(200);
	//DriveAP(B,250,90);
	//ArmHeight = C1-190;
	//DriveDP(B,595);
	//wait1Msec(100);
	//SensorValue[Pivot] = 1;
	//TurnADP(L,1406,90,4000,0.13,0.4,40);                      // Turn for cube~~~~~~~~~~~~~~~~~~~TURN
	//wait1Msec(150);
	//SensorValue[Pivot] = 0;
	//DriveADP(F,550); // driveforward for 1st cube
	//ArmHeight = S0-40;
	//wait1Msec(340);
	//intake();
	//wait1Msec(20);
	//ArmHeight = H2-10;
	//untilPotentiometerGreaterThan(H2-100,pot);
	//ArmHeight = SensorValue[pot];
	//DriveADP(F,370,90,2000,0.3,0.4,40);                       // drive forward for 2nd cube
	//ArmHeight = C0;
	//intake(1);
	//wait1Msec(430);
	//intake();
	//ArmHeight = G2-30;
	//DriveADP(B,1000);
	//wait1Msec(250);
	//brake(1);
	//TurnADP(L,1416,90,4000,0.13,0.4,40); //2nd turn
	//wait1Msec(120);// 2nd turn back
	//brake(0);
	//DriveADP(F,770,90,150000,-10,0.20,0.40,50);
	//wait1Msec(300);
	////ArmHeight = G2-300;
	//intake(1);
	//wait1Msec(400);
	//DriveDP(B,400);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~ TURN RIGHT FOR RED~~~~~~~~~~~~~~~~~~~~~~~~~~~~NEW VERSON~~~~~~~~

void TurnRN()
{
	ArmHeight = C1+10;
	untilPotentiometerGreaterThan(C1-50,pot);
	ArmHeight = C1-190;
	DriveADP(F,590);
	ArmHeight = S0-110;
	wait1Msec(300);
	intake();
	ArmHeight = G2-50;
	DriveADP(F,470); //2nd forward for cube //
	wait1Msec(150);
	Turn(SR,1630,127,2500);                        // SR Turn
	DriveADP(F,200,90,200);
	DriveADP(B,180,100); //60
	ArmHeight = G2-140;
	wait1Msec(170);
	intake(1);                // outake the cubes
	//wait1Msec(200);
	//DriveAP(B,230,90);
	//ArmHeight = C1-190;
	//DriveDP(B,595);
	//wait1Msec(100);
	//SensorValue[Pivot] = 1;
	//TurnADP(R,1387,90,4000,0.13,0.4,40);                      // Turn for cube~~~~~~~~~~~~~~~~~~~TURN
	//wait1Msec(150);
	//SensorValue[Pivot] = 0;
	//DriveADP(F,540); // driveforward for 1st cube //560
	//ArmHeight = S0-40;
	//wait1Msec(340);
	//intake();
	//wait1Msec(20);
	//ArmHeight = H2-10;
	//untilPotentiometerGreaterThan(H2-100,pot);
	//ArmHeight = SensorValue[pot];
	//DriveADP(F,370,90,2000,0.3,0.4,40);                       // drive forward for 2nd cube
	//ArmHeight = C0;
	//intake(1);
	//wait1Msec(430);
	//intake();
	//ArmHeight = G2-30;
	//DriveADP(B,1000);
	//wait1Msec(250);
	//brake(1);
	//TurnADP(R,1416,90,4000,0.13,0.4,40); //2nd turn
	//wait1Msec(120);// 2nd turn back
	//brake(0);
	//DriveADP(F,700,90,150000,-10,0.16,0.40,50);
	//wait1Msec(100);
	//ArmHeight = G2-200;
	//wait1Msec(100);
	//intake(1);
	//wait1Msec(400);
	//ArmHeight = G2+100;
	//wait1Msec(100);
	//DriveDP(B,400);
}
