#include "glass.h"
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>


/*
->AliA                       ->Faseih Saad                ->Sharjeel Ahmed
  Merit# : 378                Merit# : 218                  Merit# : 1171
*/





/////////////////////////////////////////////////////////
///                  INITIALIZATIONS                  ///   
/////////////////////////////////////////////////////////

GLuint police;

GLuint level1;
GLuint level1LAYER;

GLuint level2;
GLuint level2LAYER;

GLuint level2start;

GLuint menu;

GLuint gameover1;
GLuint gameover2;

GLuint tutorial1;
GLuint credits;

GLuint gunSprite1;
GLuint gunSprite2;
GLuint gunSprite3;
GLuint gunSprite4;
GLuint gunSprite5;
GLuint gunSprite6;
GLuint gunSprite7;
GLuint gunSprite8;

GLuint gunBurst;

int myshot = 0;        // FLAG TO SHOW GUNFIRE

int gunSprite = 1;     // TRACKS SPRITES OF OUR CHARACTER

float loadingbar[5] = { 2, 2, 2, 2, 2 };  //EVERY VARIABLE IS USED TO MOVE THE BAR TOWARDS RIGHT i.e 'TO LOAD'

int currentScreen = 0;  // TRACKS SCREENS

int newscreenflag = 1;  // FLAG TO DISPLAY IMAGES OF NEXT LEVEL

int posX[5] = { 480, 797, 477, 328, 933 };  // COORDINATES OF FIRST LEVEL
int posY[5] = { 33, 192, 182, 45, 194 };

int pos1X[5] = { 62, 225, 792, 609, 445 };  // COORDINATES OF SECOND LEVEL
int pos1Y[5] = { 93, 95, 76, 81, 86 };

int score = 0; int highscore = 0;

int posDecider = 3;   // SHUFFLES THROUGH DIFFERENT POSITIONS

int bandaX[5] = { 480, 797, 477, 328, 933 };     // COORDINATES WHERE THE TARGETES APPEAR IN START
int bandaY[5] = { 33, 192, 182, 45, 194 };       // (LAST TWO ARE NOT BEING USED ANYMORE)

//int hitBanda[5] = { 0 }; SAFDF NSMBDF, MSBFMB, BFJDMSBFHDBSF;

int a, b;              // VARIABLES USED FOR PASSIVE MOUSE FUNCTION


enum screens
{
	MENU,
	TUTORIAL,
	CREDITS,
	LEVEL1,
	LEVEL2,
	GAMEOVER1,
	GAMEOVER2,
	LEVEL2START,
};


void Mouse(int button, int state, int mouseX, int mouseY);
void PassiveMouse(int x, int y);

void main(int argc, char**argv)
{
	printf("If you liked it, buy us a samosa!");
	
	mainWindowLoop(argc, argv, "Kill-Thirst", 512, 1024);


	/////////////////////////////////////////////////////////
	///                   LOADING IMAGES                  ///   
	/////////////////////////////////////////////////////////

	menu = LoadImage("menu.tga");

	police = LoadImage("police_lastHD.tga");
	level1 = LoadImage("lvl3HD.tga");
	level2 = LoadImage("lvl4HD.tga");
	level1LAYER = LoadImage("lvl3layer.tga");
	level2LAYER = LoadImage("lvl4layer.tga");

	level2start = LoadImage("level2start.tga");

	tutorial1 = LoadImage("tutorial1.tga");
	credits = LoadImage("credits.tga");


	gunSprite1 = LoadImage("1.tga");
	gunSprite2 = LoadImage("2.tga");
	gunSprite3 = LoadImage("3.tga");
	gunSprite4 = LoadImage("4.tga");
	gunSprite5 = LoadImage("5.tga");
	gunSprite6 = LoadImage("6.tga");
	gunSprite7 = LoadImage("7.tga");
	gunSprite8 = LoadImage("8.tga");

	gunBurst = LoadImage("explosion.tga");

	gameover1 = LoadImage("gameover1.tga");
	gameover2 = LoadImage("gameover2.tga");

	///////////////////////////// - LOADING SOUND - \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC || SND_NOSTOP);

	///////////////////////////// - SETTING CURSOR - \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);


	glutPassiveMotionFunc(PassiveMouse);

	glutMouseFunc(Mouse);

	EndLoop();


}

///////////////////////////// - FUNCTION TO RENDER TEXT - \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


void renderBitmapString(
	float x,
	float y,
	char *string) {

	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

///////////////////////////// - GUNFIRE ANIMATION - \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void gunburst(int x, int y, int z)
{
	if (loadingbar[z] >= 36)
	{
		UploadImage(gunBurst, x, y + 20, 25, 25);
	}
}



void reset()
{
	/*if ((a >= 339 && a <= 685) && (b >= 197 && b <= 254))
	{
	currentScreen = MENU;
	}
	*/
	newscreenflag = 1; // REESETTING NEXT LEVEL FLAG TO DEFAULT WHEN THE GAME IS OVER

	posDecider = 0;

	if (currentScreen == LEVEL1)
	{
		//Sleep(600);
		currentScreen = GAMEOVER1;

	}
	else if (currentScreen == LEVEL2)
		currentScreen = GAMEOVER2;

	//RESETTING DEFAULT POSITIONS

	bandaX[0] = { 480 }; bandaX[1] = { 797 }; bandaX[2] = { 477 }; bandaX[3] = { 328 }, bandaX[4] = { 933 };
	bandaY[0] = { 33 }; bandaY[1] = { 192 }; bandaY[2] = { 182 }; bandaY[3] = { 45 }, bandaY[4] = { 194 };

	//RESETTING BAR FILLS

	loadingbar[0] = 2;
	loadingbar[1] = 2;
	loadingbar[2] = 2;
	loadingbar[3] = 2;
	loadingbar[4] = 2;

	//hitBanda[0] = { 0 }; hitBanda[1] = { 0 }; hitBanda[2] = { 0 }; hitBanda[3] = { 0 }; hitBanda[4] = { 0 };
}

void loading(int x, int y, int z)
{

	CreateRectangle(x + 5, y, 2, 40, "Black", "Hollow");
	CreateRectangle(x + 5, y, 2, (int)loadingbar[z], "Red", "Filled");


	loadingbar[z] += 0.1;       // CONTROLS BAR FILL SPEED


	if (currentScreen == LEVEL1 || currentScreen == LEVEL2)   // GAME IS OVER ONCE BAR IS FILLED
	{
		if (loadingbar[z] >= 40)
		{
			loadingbar[z] = 40;
			reset();
		}
	}
}

void myDisplayFunction()
{
	ScreenClear();


	char scores[10];  //FOR PRINTING STRING


	if (currentScreen == MENU)
	{
		UploadImage(menu, 0, 0, 512, 1024);
		score = 0;

	}
	if (currentScreen == LEVEL1 || currentScreen == LEVEL2)  // LOAD SECIFIC IMAGES FOR SPECIFIC LEVELS
	{
		if (currentScreen == LEVEL1)
		{
			UploadImage(level1, 0, 0, 512, 1024);
			UploadImage(police, bandaX[0], bandaY[0], 128, 64);
			UploadImage(police, bandaX[1], bandaY[1], 128, 64);
			UploadImage(police, bandaX[2], bandaY[2], 128, 64);
			UploadImage(level1LAYER, 0, 0, 512, 1024);     // LAYER BEHIND WHICH TARGETS ARE HIDDEN

			SetColor("White");
			renderBitmapString(10, 500, "Score:");
			renderBitmapString(80, 500, _itoa(score, scores, 10));
		}
		else if (currentScreen == LEVEL2)
		{
			UploadImage(level2, 0, 0, 512, 1024);
			UploadImage(police, bandaX[0], bandaY[0], 128, 64);
			UploadImage(police, bandaX[1], bandaY[1], 128, 64);
			UploadImage(police, bandaX[2], bandaY[2], 128, 64);
			UploadImage(level2LAYER, 0, 0, 512, 1024);

			SetColor("White");
			renderBitmapString(140, 490, _itoa(score, scores, 10));
		}

		/////////////////////////////////////////////////////////
		///                   PISTOL SPRITES                  ///   
		/////////////////////////////////////////////////////////


		if (a < 100)      // REGION OF SCREEN
		{
			UploadImage(gunSprite8, 0, 0, 512, 1024);
			if (myshot == 1)  // GUNFIRE IMAGE FLAG
			{
				UploadImage(gunBurst, 785, 255, 50, 50);
				UploadImage(gunSprite8, 0, 0, 512, 1024);  // OVERLAPS GUNFIRE IMAGE
				myshot = 0;   // GUNFIRE SHOWN, NOW RESET TO NULL
			}
		}
		else if (a < 200 & a > 100)
		{
			UploadImage(gunSprite7, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 795, 255, 50, 50);
				UploadImage(gunSprite7, 0, 0, 512, 1024);
				myshot = 0;
			}
		}
		else if (a < 300 & a > 200)
		{
			UploadImage(gunSprite6, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 803, 250, 50, 50);
				UploadImage(gunSprite6, 0, 0, 512, 1024);
				myshot = 0;
			}
		}
		else if (a < 400 & a > 300)
		{
			UploadImage(gunSprite5, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 812, 250, 50, 50);
				UploadImage(gunSprite5, 0, 0, 512, 1024);
				myshot = 0;
			}
		}
		else if (a < 500 & a > 400)
		{
			UploadImage(gunSprite4, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 815, 250, 50, 50);
				UploadImage(gunSprite4, 0, 0, 512, 1024);
				myshot = 0;
			}
		}
		else if (a < 600 & a > 500)
		{
			UploadImage(gunSprite3, 0, 0, 512, 1024);
			UploadImage(gunSprite3, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 825, 250, 50, 50);
				UploadImage(gunSprite3, 0, 0, 512, 1024);
				myshot = 0;
			}
		}
		else if (a < 700 & a > 600)
		{
			UploadImage(gunSprite2, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 837, 250, 50, 50);
				UploadImage(gunSprite2, 0, 0, 512, 1024);
				myshot = 0;
			}
		}
		else if (a > 600)
		{
			UploadImage(gunSprite1, 0, 0, 512, 1024);
			if (myshot == 1)
			{
				UploadImage(gunBurst, 845, 250, 50, 50);
				UploadImage(gunSprite1, 0, 0, 512, 1024);
				myshot = 0;
			}
		}


		loading(bandaX[0], bandaY[0], 0);  // LOADING THREE TARGETS AT A TIME
		loading(bandaX[1], bandaY[1], 1);
		loading(bandaX[2], bandaY[2], 2);

		gunburst(bandaX[0], bandaY[0], 0);  // FUNTION CALL TO SHOW GUNFIRED BY TARGETS
		gunburst(bandaX[1], bandaY[1], 1);
		gunburst(bandaX[2], bandaY[2], 2);
	}


	/////////////////////////////////////////////////////////
	///       LOADING IMAGES FOR SPECIFIC SCREEENS        ///   
	/////////////////////////////////////////////////////////


	if (currentScreen == TUTORIAL)
	{
		UploadImage(tutorial1, 0, 0, 512, 1024);
	}

	if (currentScreen == CREDITS)
	{
		UploadImage(credits, 0, 0, 512, 1024);
	}
	if (currentScreen == GAMEOVER1)
	{
		UploadImage(gameover1, 0, 0, 512, 1024);
		Sleep(500);        // SINCE THE USER IS CLICKING MOUSE QUICKLY, THEY MISTAKENLY CLICK ON THE GAME OVER SCREEN TOO AND IT VANISHES VERY QUICKLY SO WE CAN NOT SEE IT SOMETIMES. SO WE ADD SLEEP FUNCTION
	}
	if (currentScreen == GAMEOVER2)
	{
		Sleep(500);
		UploadImage(gameover2, 0, 0, 512, 1024);
		SetColor("White");
		renderBitmapString(720, 325, _itoa(score, scores, 10));
		SetColor("White");
		renderBitmapString(450, 325, _itoa(highscore, scores, 10));
		Sleep(500); // SINCE THE USER IS CLICKING MOUSE QUICKLY, THEY MISTAKENLY CLICK ON THE GAME OVER SCREEN TOO AND IT VANISHES VERY QUICKLY SO WE CAN NOT SEE IT SOMETIMES. SO WE ADD SLEEP FUNCTION
	}
	if (currentScreen == LEVEL2START)
	{
		UploadImage(level2start, 0, 0, 512, 1024);
	}

	if (score > 18 && score < 21)
	{
		bandaX[0] = pos1X[0];
		bandaY[0] = pos1Y[0];
		bandaX[1] = pos1X[1];
		bandaY[1] = pos1Y[1];
		bandaX[2] = pos1X[2];
		bandaY[2] = pos1Y[2];
		if (newscreenflag)
		{   // FLAG TO GO TO NEW SCREEN
			currentScreen = LEVEL2START;
			newscreenflag = 0;
		}
	}

	if (score > highscore)
		highscore = score;   // SET THE HIGHSCORE IF SCORE INCREASES

	RefreshScreen();

	
}

void hit(int mouseX, int mouseY, int z)
{
	myshot = 1;                              //ACTS AS A FLAG, WHEN 1 GUNFIRE IS SHOWN
	if (currentScreen == LEVEL1 || currentScreen == LEVEL2)
	{
		if ((mouseX >= bandaX[z] + 15 && mouseX <= bandaX[z] + 50) && (mouseY >= bandaY[z] + 12 && mouseY <= bandaY[z] + 73))
		{
			bandaY[z] -= 5;

			if (currentScreen == LEVEL1)
			{
				bandaX[z] = posX[posDecider];
				bandaY[z] = posY[posDecider];

			}
			else if (currentScreen == LEVEL2)
			{
				bandaX[z] = pos1X[posDecider];
				bandaY[z] = pos1Y[posDecider];

			}
			loadingbar[z] = 2;

			myshot = 1;


			score++;
			posDecider++;
			if (posDecider == 5)
			{									// SHUFFLE THROUGH POSITIONS
				posDecider = 0;
				

			}
		}
	}
}


void Mouse(int button, int state, int mouseX, int mouseY)
{
	a = mouseX; b = mouseY;

	if ((mouseX >= 339 && mouseX <= 685) && (mouseY >= 197 && mouseY <= 254) & (currentScreen == MENU))
	{
		currentScreen = LEVEL1;
	}

	if (currentScreen == MENU)
	{
		if ((mouseX >= 338 && mouseX <= 685) && (mouseY >= 378 && mouseY <= 434) & (currentScreen == MENU))
		{
			exit(0);
		}
	}

	if (currentScreen == TUTORIAL)
	{
		currentScreen = MENU;
	}

	if (currentScreen == CREDITS)
	{
		currentScreen = MENU;
	}


	if ((mouseX >= 339 && mouseX <= 685) && (mouseY >= 286 && mouseY <= 344) & (currentScreen == MENU))
	{
		currentScreen = TUTORIAL;
	}

	if ((mouseX >= 955 && mouseX <= 1024) && (mouseY >= 455 && mouseY <= 512) & (currentScreen == MENU))
	{
		currentScreen = CREDITS;
	}

	if (currentScreen == LEVEL2START)
	{
		currentScreen = LEVEL2;
		Sleep(1500);
	}



	if (currentScreen == GAMEOVER1 || currentScreen == GAMEOVER2)
	{
		currentScreen = MENU;
		Sleep(2000);
	}



	

	hit(mouseX, mouseY, 0);
	hit(mouseX, mouseY, 1);
	hit(mouseX, mouseY, 2);

}
void PassiveMouse(int x, int y)
{
	a = x;
	b = y;
}


