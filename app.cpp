
/**************************************
*                                     *
*   Michal Svoboda's Basecode Example *
*                2002                 *
*                                     *
**************************************/

// Includes
#ifdef WIN32													
#include <windows.h>											
#else															
#include <stdio.h>											
#include <stdlib.h>											
#endif														

#include <math.h>	
#include <time.h>										
#include <GL/gl.h>											
#include <GL/glu.h>		
#include <gl/glaux.h>
#include "GLFont.h"	
#include "fmod.h"								


#include <SDL.h>											

#include "main.h"											

#ifdef WIN32												
#pragma comment( lib, "opengl32.lib" )						
#pragma comment( lib, "glu32.lib" )							
#pragma comment( lib, "glaux.lib" )							

#pragma comment( lib, "SDLmain.lib" )						
#pragma comment( lib, "SDL.lib" )								
#pragma comment( lib, "fmodvc.lib" )								
#endif														


extern S_AppStatus AppStatus;								

// User Defined Variables
float		angle;											
float		alfa;											
float		cnt1, cnt2;										
int			rot1, rot2;									
GLuint       texture[4];
AUX_RGBImageRec *Texs[4];
GLFont  font;
GLFont  font1;

static int aktivni = 1;
int stavapp = 1;

/* For FPS */
char temp[128]="FPS: 0.000000";
int frame_counter=0;
time_t curtime;
clock_t last_time;
float cur_time;
float total_frames;
/////////////////////pro tetris///////////////////
#define SIRKA 10
#define VYSKA 19
#define V_POLOHAX 2
#define V_POLOHAY 0

/// promene a data
int pole[VYSKA][SIRKA];
bool hra = false;
bool kosticka = false;
bool zmena;
int typ_kost = 0;
int generkost = 0;
//          poc. rot. 4x4
int pole_kost[6][4][4][4];
int poloha_x = V_POLOHAX, npoloha_x;
int poloha_y = V_POLOHAY;

int rotace = 0, nrotace = 0; // nabyva hodnot 0,1,2,3

bool breakpoint = false;
int pocbodu = 0;
int level = 1, levcitac;

int napis[6][4][4];
///////pro SOUND/////////////////////////////////
FSOUND_SAMPLE *pSound;
FSOUND_SAMPLE *pSound1;
FSOUND_SAMPLE *pSound2;
FSOUND_SAMPLE *pSound3;
int soundChannel = 0;
////// pro GL////////////////////////////////////
Uint32 timecounter = 0; // casovy citac
/////////////////////////////////////////////////
void cube(void) {
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

}
void poly(void) {
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();
}
void poly1(void) {
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 2.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f,  1.0f,  1.0f);
	glEnd();
}

void nacistkostky(void) {
FILE *fr;

fr = fopen("kostky.cub", "r");
if (fr == NULL) {
	printf("Chyba: soubor napis.cub nelze otevrit");
}
char znak;
for (int a = 0; a < 6; a++) {
  for (int b = 0; b < 4; b++) {
    for (int c = 0; c < 4; c++) {
      for (int d = 0; d < 4; d++) {
         fscanf(fr, "%c\n", &znak);
		if (znak == 'k') {
			d--;
			continue;
		}
		if (znak == '1') {
			pole_kost[a][b][c][d] = 1;
			printf("a");
		}
		else
			printf("n");
        //Caption = citac;
      }
    }
  }
}

printf("\nkostky: Nacteny\n");
fclose(fr);

}
void nacistnapis(void) {
FILE *fr;

fr = fopen("napis.cub", "r");
if (fr == NULL) {
	printf("Chyba: soubor napis.cub nelze otevrit");
}
char znak;

for (int a = 0; a < 6; a++) {
    for (int c = 0; c < 4; c++) {
      for (int d = 0; d < 4; d++) {
        fscanf(fr, "%c\n", &znak);
		if (znak == 'T') {
			d--;
			continue;
		}
		if (znak == '1') {
			napis[a][c][d] = 1;
			printf("a");
		}
		else
			printf("n");
        //Caption = citac;
      }
    }
}

printf("\nNapis: Nacten\n");
fclose(fr);

}
void napisdraw(void) {
	
for (int a = 0; a < 6; a++) {
    for (int c = 0; c < 4; c++) {
      for (int d = 0; d < 4; d++) {
		  if (napis[a][c][d] == 1) {
			//printf("Pisu\n");
			glLoadIdentity();				  
			glTranslatef(-20+a*7.5+2.1*d,+15-c*2.1f,-45.0f);
			if (stavapp ==  3)
				glTranslatef(-25, +18,-40.0f);

			if (a == 4)
				glRotatef(angle,0.0f,1.0f,0.0f);
			//glRotatef(angle, 0.0f,1.0f,0.0f);
			cube();
		  }
			
        //Caption = citac;
      }
    }
}
}

// NAKRESLIT POLE
void nakreslit_pole(void) {
	glNewList(1, GL_COMPILE_AND_EXECUTE);
	glDisable(GL_BLEND);										
	for (int i = -1; i < VYSKA+1; i++) {
		for (int j = -1; j < SIRKA+1; j++) {
			if (i < VYSKA && j > -1 && j < SIRKA)
				continue;
			glLoadIdentity();				  
			glColor4f(1.0f,0.0f,0.0f, 1.0);
			glTranslatef(5+2.0*j,+20-i*2.0f,-60.0f);
			cube();
		}
	}
	/// lajna kolem 4 radku
	glBegin(GL_LINES);
	glEnd();
	
		
	glEnable(GL_BLEND);																		
	glEndList();
}
/////////////////
// nakreslit kostky
void drawkostky() {
// nakreslit pole
	for (int i = 0; i < VYSKA; i++) {
		for (int j = 0; j < SIRKA; j++) {
			glLoadIdentity();				  
			glColor4f(1.0f,0.0f,0.0f, 1.0);
			if (pole[i][j] > 0) {
				glTranslatef(5+2.0*j,+20-i*2.0f,-60.0f);
				cube();
			}	
		}
	}
}
//// nakreslit aktualni ///
void drawaktual(void) {
	if (kosticka == true) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			glLoadIdentity();				  
			glColor3f(0.0f,0.5f,1.0f);
			if (pole_kost[typ_kost][rotace][i][j] > 0) {
				glTranslatef(5+2*poloha_x+2.0*j,+20-2*poloha_y-i*2.0f,-60.0f);
				cube();
			}	
		}
	}
	}
}
// nakresli aktualni kostku na levo na obrazovku
void drawthis() {
for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
		glLoadIdentity();				  
		glColor3f(1.0f,1.0f,0.0f);
		if (pole_kost[generkost][0][i][j] > 0) {
			glTranslatef(-8+2.0*j,6-i*2.0f,-30.0f);
			cube();
		}	
	}
}

}

///// INIT SOUND ///////////
void MyInitSound(void) {
  if (FSOUND_GetVersion() < FMOD_VERSION)
    printf("\nSpatna verze FMOD\n");
  if (!FSOUND_Init(44100, 32, FSOUND_INIT_GLOBALFOCUS))
	 printf("\nNelze inicializovat FMOD\n");
  pSound = FSOUND_Sample_Load(FSOUND_FREE, "data/start.wav",0,0);
  if (!pSound)
	printf("\nSoubor se nepodarilo nacist.");
  pSound1 = FSOUND_Sample_Load(FSOUND_FREE, "data/konec.wav",0,0);
  if (!pSound1)
	printf("\nSoubor se nepodarilo nacist.");
  pSound2 = FSOUND_Sample_Load(FSOUND_FREE, "data/cyberspc.wav",0,0);
  if (!pSound2)
	printf("\nSoubor se nepodarilo nacist.");
  pSound3 = FSOUND_Sample_Load(FSOUND_FREE, "data/btn.wav",0,0);
  if (!pSound3)
	printf("\nSoubor se nepodarilo nacist.");

  soundChannel = FSOUND_PlaySound(FSOUND_FREE,pSound2);
  FSOUND_SetLoopMode(soundChannel, FSOUND_LOOP_OFF);
        
}
////////////////////////////
//////////////////////////

// cas
static float gettime(void)
{
  clock_t time_new, time_raz;

  time_new=clock();
  time_raz=time_new-last_time;
  last_time=time_new;

  return(time_raz/(float)CLOCKS_PER_SEC);
}


// Code
bool InitGL(SDL_Surface *S)										// Any OpenGL Initialization Code Goes Here
{
	

	// Init FONT
	Texs[0]=auxDIBImageLoad("Data/bitava.bmp");					// Load Font Texture
	glGenTextures(1, &texture[0]);							
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Texs[0]->sizeX , Texs[0]->sizeY , 0, GL_RGB, GL_UNSIGNED_BYTE, Texs[0]->data);
    if(Texs[0]->data != NULL) free(Texs[0]->data);			

	Texs[1]=auxDIBImageLoad("Data/tex3.bmp");					// Load Font Texture
	glGenTextures(2, &texture[1]);							
    glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Texs[1]->sizeX , Texs[1]->sizeY , 0, GL_RGB, GL_UNSIGNED_BYTE, Texs[1]->data);
    if(Texs[1]->data != NULL) free(Texs[1]->data);			

	Texs[2]=auxDIBImageLoad("Data/logo.bmp");					// Load Font Texture
	glGenTextures(3, &texture[2]);							
    glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Texs[2]->sizeX , Texs[2]->sizeY , 0, GL_RGB, GL_UNSIGNED_BYTE, Texs[2]->data);
    if(Texs[2]->data != NULL) free(Texs[2]->data);			

	Texs[3]=auxDIBImageLoad("Data/ramecek.bmp");					// Load Font Texture
	glGenTextures(4, &texture[3]);							
    glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Texs[3]->sizeX , Texs[3]->sizeY , 0, GL_RGB, GL_UNSIGNED_BYTE, Texs[3]->data);
    if(Texs[3]->data != NULL) free(Texs[3]->data);			

	
	font.SetTexture(texture[0],16,16);
	// Set Font Width and Font Height in Texture, and Character Spacing
	font.SetFontProperties(16,16,10);
	// Adjust Fonts 2D Drawing Rectangle Size 
	font.SetDisplayMode(SCREEN_W, SCREEN_H);
	font.BuildFont(2);      
	
	font1.SetTexture(texture[0],16,16);
	// Set Font Width and Font Height in Texture, and Character Spacing
	font1.SetFontProperties(16,16,10);
	// Adjust Fonts 2D Drawing Rectangle Size 
	font1.SetDisplayMode(SCREEN_W, SCREEN_H);
	font1.BuildFont(1);      

	
	glClearColor(0.0f,0.0f,0.0f,0.5f);						
	glClearDepth(1.0f);										
	glDepthFunc(GL_LEQUAL);									
	glEnable(GL_DEPTH_TEST);								
	glShadeModel(GL_SMOOTH);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);						
	glEnable(GL_TEXTURE_2D);								
	glEnable(GL_BLEND);										
	
	return true;											
}


bool Initialize(void)											// Any Application & User Initialization Code Goes Here
{
	AppStatus.Visible		= true;								// At The Beginning, Our App Is Visible
	AppStatus.MouseFocus	= true;								// And Have Both Mouse
	AppStatus.KeyboardFocus = true;								// And Input Focus

	// Start Of User Initialization
	angle		= 0.0f;											// Set The Starting Angle To Zero
	cnt1		= 0.0f;											// Set The Cos(for the X axis) Counter To Zero
	cnt2		= 0.0f;											// Set The Sin(for the Y axis) Counter To Zero

	return true;												// Return TRUE (Initialization Successful)
}


void Deinitialize(void)											// Any User Deinitialization Goes Here
{
	return;														// We Have Nothing To Deinit Now
}

void Update(Uint32 Milliseconds, Uint8 *Keys)					// Perform Motion Updates Here
{
	if(Keys)													// If We're Sent A Key Event With The Update
	{
		///////////////////////

		///////////////////////
		if(Keys[SDLK_ESCAPE])									// And If The Key Pressed Was ESC
		{
				TerminateApplication();								// Terminate The Application
			

			Keys[SDLK_ESCAPE] = false;
		}
		if(Keys[SDLK_a])										// If The Key Pressed Was F1
		{
			level = 1;
			hra = true;
			rotace = 0;
			pocbodu = 0;
			for (int i = 0; i < VYSKA; i++) {
				for (int j = 0; j < SIRKA; j++) {
					pole[i][j] = 0;
				}
			}
			stavapp = 3;
		}
		if(Keys[SDLK_n])										// If The Key Pressed Was F1
		{
			if (stavapp == 4)
				stavapp = 1;
		}

		if(Keys[SDLK_F1])										// If The Key Pressed Was F1
		{
			ToggleFullscreen();									// Use SDL Function To Toggle Fullscreen Mode (But Not In Windows :) )
		}
		if(Keys[SDLK_UP])										// If The Key Pressed Was F1
		{
		if (stavapp == 1) {
		aktivni--;
		if (aktivni < 1)
			aktivni = 3;
		soundChannel = FSOUND_PlaySound(FSOUND_FREE,pSound3);
		FSOUND_SetLoopMode(soundChannel, FSOUND_LOOP_OFF);
		}
		if (stavapp == 3) {
			rotace++;
			for (int i = 0; i <4; i++) {
				for (int j = 0; j < 4; j++) {
					if ((pole_kost[typ_kost][rotace][i][j] > 0) && (poloha_x+j < 0 || poloha_x+j >= SIRKA || poloha_y+i >= VYSKA-1)) {
						rotace--;
						break;
					}
				}
			}
			if (rotace < 0)
				rotace = 3;
			if (rotace > 3)
				rotace = 0;
		}
		Keys[SDLK_UP] = false;
		}
		if(Keys[SDLK_DOWN])										// If The Key Pressed Was F1
		{
		if (stavapp == 1) {
			aktivni++;
			if (aktivni > 3)
				aktivni = 1;
			soundChannel = FSOUND_PlaySound(FSOUND_FREE,pSound3);
			FSOUND_SetLoopMode(soundChannel, FSOUND_LOOP_OFF);
		}
		Keys[SDLK_DOWN] = false;
		}

		if (Keys[SDLK_RETURN]) {
			if (stavapp == 2) {
				stavapp = 1;
				Keys[SDLK_RETURN] = false;
				return;
			}
			if (aktivni == 1)  {
				for (int i = 0; i < VYSKA; i++) {
					for (int j = 0; j < SIRKA; j++) {
						pole[i][j] = 0;
					}
				}
				stavapp = 3;
				hra = true;
				level = 1;
				pocbodu = 0;
				rotace = 0;
			}
			if (aktivni == 2) 
				stavapp = 2;
			if (aktivni == 3)
				TerminateApplication();								// Terminate The Application	

			Keys[SDLK_RETURN] = false;
		}
		if (Keys[SDLK_LEFT]) {
		    poloha_x--;
			for (int i = 0; i <4 ; i++) {
				for (int j = 0; j < 4; j++) {
					if ((pole_kost[typ_kost][rotace][i][j] > 0 && poloha_x+j < 0) || (pole_kost[typ_kost][rotace][i][j] > 0 && pole_kost[typ_kost][rotace][i][j] == pole[poloha_y+i][poloha_x+j])) {
						poloha_x++;
						break;
					}
				}
			}
		Keys[SDLK_LEFT] = false;
		}
		if (Keys[SDLK_RIGHT]) {
			poloha_x++;
			/// test//
			for (int i = 0; i <4; i++) {
				for (int j = 0; j < 4; j++) {
					if ((pole_kost[typ_kost][rotace][i][j] > 0 && poloha_x+j >= SIRKA) || (pole_kost[typ_kost][rotace][i][j] > 0 && pole_kost[typ_kost][rotace][i][j] == pole[poloha_y+i][poloha_x+j])) {
						poloha_x--;
						break;
					}
				}
			}
		Keys[SDLK_RIGHT] = false;
		}
	}

	angle += (float)(Milliseconds) / 50.0f;	// Update Angle Based On The Clock
	if (alfa < 1)
		alfa += (float)(Milliseconds) / 5000.0f;	// Update Angle Based On The Clock




	cnt1  += 0.007f;											// Update the Cos Counter Based On The Clock
	cnt2  += 0.004f;// And The Same Thing For The Sin Counter

	return;		
}

void Draw(void)													// Our Drawing Code
{

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();										
	font.SetBase(32);										
	font1.SetBase(32);										
	//font.Print(20,50,"Sky Lights studio - TETRIS");		

	// menu
	glColor3f(0.0f,0.5f,1.0f);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslatef(0.0f,0.0f,0.0f);
	//glRotatef(angle,1.0f,0.0f,0.0f);
	//glRotatef(angle, 0.0f,1.0f,0.0f);
	//cube();
	napisdraw();
	glLoadIdentity();										
	// MENU
if (stavapp == 1) {
  // LOGO
	glColor4f(1.0f,1.0f,1.0f, alfa);
	glTranslatef(-3.0f,-2.9f,-9.0f);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	poly();
	glLoadIdentity();										
	glTranslatef(0.0, -0.5, 0.0f);
	glTranslatef(0,0,-6.0f);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glColor3f(0.0f,0.5f,1.0f);
	poly1();
	
  if (aktivni == 1)
 	 glColor3f(1.0f,1.0f,0.0f);
  else
	 glColor3f(1.0f,1.0f,1.0f);
	
  font.Print(280,250,"New GAME");
  
  if (aktivni == 2)
 	 glColor3f(1.0f,1.0f,0.0f);
  else
	 glColor3f(1.0f,1.0f,1.0f);

  font.Print(240,300,"Credits");
  
  if (aktivni == 3)
 	 glColor3f(1.0f,1.0f,0.0f);
  else
	 glColor3f(1.0f,1.0f,1.0f);

  font.Print(270,350,"EXIT");


}

if (stavapp == 2) {
	//glRotatef(angle,1.0f,0.0f,0.0f);
	//glColor3f(1.0f,1.0f,1.0f);
	//cube();
	glLoadIdentity();										
	glTranslatef(0.0, -0.5, 0.0f);
	glTranslatef(0,0,-6.0f);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	poly1();
	glColor3f(1.0f,1.0f,1.0f);
	font1.Print(150,210,"Created by");
	glColor3f(1.0f,1.0f,0.0f);
	font1.Print(150,240,"Michal Svoboda");
	font1.Print(150,260,"miskyn@centrum.cz");
	font1.Print(150,280,"sky lights studio");
	font1.Print(150,300,"2002  freeware");

	glColor3f(1.0f,1.0f,1.0f);
	font1.Print(150,400,"stiskni enter");
	
}

  /* FPS Calculations */
  frame_counter++;
  if((frame_counter % 40) == 0)
  {
    frame_counter = 0;
    cur_time=gettime();
    sprintf(temp, "FPS: %.1f", 40.0/cur_time);
  }
  

if (stavapp == 3) {
if (timecounter++ >= (40.0/cur_time)/(2*level) && hra == true) {	
	poloha_y++;	
	timecounter = 0;
}
/////// HRA PREPOCTY ////////////
static int last = -1;
/// pokud neni kostiscka v poli, tak ji tam umistime
if (kosticka == false && hra == true) {
  poloha_x = V_POLOHAX;
  poloha_y = V_POLOHAY;

  kosticka = true;
  // vygenerovat, kerou kosticku
  //typ_kost = 0;
  //srand(50);
  typ_kost = generkost;
  while ((generkost = rand()/10000) == last || generkost > 5);
	
  last = generkost;



}

///// TEST NA POSLEDNI RADEK, JESTLI KOSTICKA NA NECO NENARAZILA////
bool prepinac = false;
for (int i = 0; i < 4; i++) {
  for (int j = 0; j < 4; j++) {
    if ((pole_kost[typ_kost][rotace][i][j]) > 0 && poloha_y+i >= VYSKA-1)
      kosticka = false;
    if (pole_kost[typ_kost][rotace][i][j] > 0 && pole[poloha_y+i][poloha_x+j] == pole_kost[typ_kost][rotace][i][j]) {
       prepinac = true;
       kosticka = false;
    }
  }
}
///////////////////////////////////////////
// znehybnet kosticku /////////////////////
if (kosticka == false) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (prepinac == false) {
        if (pole_kost[typ_kost][rotace][i][j] > 0)
          pole[poloha_y+i][poloha_x+j] = pole_kost[typ_kost][rotace][i][j];
      }
      else {
        if (pole_kost[typ_kost][rotace][i][j] > 0)
          pole[poloha_y+i-1][poloha_x+j] = pole_kost[typ_kost][rotace][i][j];
      }
    }
  }
  
  if (poloha_y <= 1) {
    
	if (hra == true)
		printf("\nGAME OVER");
	glColor3f(1.0f,1.0f,0.0f);
	font1.Print(5,160,"GAME OVER");

	hra = false;
	stavapp = 4;
    //DXTimer1->Enabled = false;
  }
  if (hra == true) {
	pocbodu += 10;
	levcitac  += 10;
	soundChannel = FSOUND_PlaySound(FSOUND_FREE,pSound);
	FSOUND_SetLoopMode(soundChannel, FSOUND_LOOP_OFF);
  }

}
///////////////////////////////////////////
// ZOBRAZIT POLE
//DrawGrid1->Repaint();
///////////////////////////////////////////

////// TEST PLNEHO RADKU //////////////////
bool stav = false;
if (kosticka == false && hra == true) {
  for (int i = 0; i < VYSKA; i++) {
    stav = false;
    for (int j = 0; j < SIRKA; j++) {
      if (pole[i][j] == 0) {
        stav = true;
        break;
      }
    }
    if (stav == true)
       continue;

    for (int c = i; c >= 0; c--) {
      for (int p = 0; p < SIRKA; p++)
        pole[c][p] = pole[c-1][p];
    }
	for (int i = 0; i < SIRKA; i++)
		pole[0][i] = 0;
    
  }
  if (stav == false) {
	pocbodu += 50;
	levcitac += 50;
	soundChannel = FSOUND_PlaySound(FSOUND_FREE,pSound1);
	FSOUND_SetLoopMode(soundChannel, FSOUND_LOOP_OFF);
  }
  //Sleep(200);
  //DrawGrid1->Repaint();
  if (levcitac > 1000) {
	 level++;
	 levcitac = 0;
  }

}
///////////////////////////////////////////
//DrawGrid1->Repaint();
//poloha_y++;
//LabBody->Caption = pocbodu;
	/////////////////////////////////
  char bod[32];
  sprintf(bod, "BODY: %d", pocbodu);
  glColor3f(1.0f,1.0f,1.0f);
  font1.Print(5,100,bod);
  sprintf(bod, "LEVEL: %d", level);
  font1.Print(5,120,bod);
  
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  drawthis();
  glCallList(1);
  drawaktual();
  drawkostky();
}
  

  
  glColor3f(1.0f,1.0f,1.0f);
  font1.Print(540,472,temp);
    

if (stavapp == 4) {
	 char bod[32];
	//glRotatef(angle,1.0f,0.0f,0.0f);
	//glColor3f(1.0f,1.0f,1.0f);
	//cube();
	glColor3f(0.0f,0.5f,1.0f);

	glLoadIdentity();										
	glTranslatef(0.0, -0.5, 0.0f);
	glTranslatef(0,0,-6.0f);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	poly1();
	glColor3f(1.0f,1.0f,1.0f);
	font1.Print(150,210,"Chcete novou hru?");
	sprintf(bod, "BODY: %d", pocbodu);
	glColor3f(1.0f,1.0f,1.0f);
	font1.Print(150,240,bod);
	sprintf(bod, "LEVEL: %d", level);
	font1.Print(150,270,bod);
	glColor3f(1.0f,1.0f,1.0f);
	font1.Print(150,300,"stiskni (a/n)");
	
}


	glFlush ();	
	return;													
}
