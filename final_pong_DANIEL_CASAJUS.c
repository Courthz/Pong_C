/*******************************************************************************************
*
*   raylib FINAL PONG - Basic Game Structure
*    Developed by Daniel Casajús Martínez
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include "raylib.h"
#include <time.h>

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    char windowTitle[30] = "PONG";
    
    GameScreen screen = LOGO;
    
    // TODO: Define required variables here..........................(0.5p)
    // NOTE: Here there are some useful variables (should be initialized)
	
	int height = 80;
	
	int playerPosX = 0;
    int playerPosY = (screenHeight/2) - (height/2);
    int playerSpeedY = 3;
    
    int enemyPosX = screenWidth - 20;
    int enemyPosY = (screenHeight/2) - (height/2);
    int enemySpeedY = 3;
    
	srand(time(NULL));
	
    int ballPosX = screenWidth/2;
    int ballPosY = screenHeight/2;
    int ballRadius = 15;
    int ballSpeedX = rand() % 3 + 3;
    int ballSpeedY = rand() % 3 + 3;
	if (rand()%2) ballSpeedX *= -1;
	if (rand()%2) ballSpeedY *= -1;       // La bola tomará una velocidad (x,y) entre 3->5 o -5->-3
    
    int playerLife = 200;
    int enemyLife = 200;
	
	bool parpadeo = 0;
	
	Color LogoColor = BLACK;
	LogoColor.a = 0;
	Color TitleColor = GREEN;
	TitleColor.a = 0;
	Color EnterColor = LIME;
	EnterColor.a = 0;
	Color endingColor = GREEN;
    
	bool pause = 0;
	bool choque = 0;
	
    int secondsCounter = 99;
    
    int framesCounter = 0;            // General pourpose frames counter
    
    InitWindow(screenWidth, screenHeight, windowTitle);
    
    // NOTE: If using textures, declare Texture2D variables here (after InitWindow)
    // NOTE: If using SpriteFonts, declare SpriteFont variables here (after InitWindow)
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(screen) 
        {
            case LOGO: 
            {
                // Update LOGO screen data here!
                
                // TODO: Logo fadeIn and fadeOut logic...............(0.5p)
                framesCounter++;
				
				if (framesCounter <= 90) LogoColor.a++;
				if (framesCounter > 90 && framesCounter <= 210) LogoColor.a = LogoColor.a;
				if (framesCounter > 210 && framesCounter <= 300) LogoColor.a--;
				if (framesCounter > 300) screen = TITLE;
				
            } break;
            case TITLE: 
            {
                // Update TITLE screen data here!
                
                // TODO: Title animation logic.......................(0.5p)
			 
				if (TitleColor.a != 255) TitleColor.a++;
				
                // TODO: "PRESS ENTER" logic.........................(0.5p)
				framesCounter++;
				
				if ((parpadeo == 0) && (framesCounter >= 30))
				{
					framesCounter = 0;
					EnterColor.a = 0;
					parpadeo = !parpadeo;
				}
				if ((parpadeo == 1) && (framesCounter >= 30))
				{
					framesCounter = 0;
					EnterColor.a = 255;
					parpadeo = !parpadeo;
				}
				if (IsKeyPressed(KEY_ENTER)) screen = GAMEPLAY;
				
            } break;
            case GAMEPLAY:
            { 
                // Update GAMEPLAY screen data here!
                
                // TODO: Player movement logic.......................(0.2p)
                
				if (!pause)
				{
					if (IsKeyDown(KEY_UP)) playerPosY -= playerSpeedY;
					if (IsKeyDown(KEY_DOWN)) playerPosY += playerSpeedY;
				}
                // TODO: Enemy movement logic (IA)...................(1p)
                
				if (!pause)
				{
					if (ballSpeedY < 0) enemySpeedY = rand() %5 - 5;
					if (ballSpeedY > 0) enemySpeedY = rand() %5 + 1;
					
					enemyPosY += enemySpeedY;
				}
			
                // TODO: Collision detection (ball-player) logic.....(0.5p) [*Cada vez que choca, la bola aumenta su velocidad (quería hacerlo añadiendo ballSpeedY++ y ballSpeedX++,
				//pero al alcanzar una velocidad muy alta, la bola escapa de los limites de la ventana)]
                
				if (((ballPosX - ballRadius) <= 20) && ((ballPosY + ballRadius) >= playerPosY) && ((ballPosY - ballRadius) <= (playerPosY + height))) ballSpeedX = -ballSpeedX;
                // TODO: Collision detection (ball-enemy) logic......(0.5p)
                
				if (((ballPosX + ballRadius) >= (screenWidth - 20)) && ((ballPosY + ballRadius) >= enemyPosY) && ((ballPosY - ballRadius) <= (enemyPosY + height))) ballSpeedX = -ballSpeedX;
                // TODO: Collision detection (ball-limits) logic.....(1p)
                
				if (((ballPosY - ballRadius) <= 0) || ((ballPosY + ballRadius) >= screenHeight)) ballSpeedY = -ballSpeedY;
				if (((ballPosX - ballRadius) <= 0) || ((ballPosX + ballRadius) >= screenWidth)) ballSpeedX = -ballSpeedX;
				
				// TODO: Collision detection (bars-limits) logic.....(??p)
				
				if (playerPosY <= 0) playerPosY = 0;
				if ((playerPosY + height) >= screenHeight) playerPosY = screenHeight - height;
				
				if (enemyPosY <= 0) enemyPosY = 0;
				if ((enemyPosY + height) >= screenHeight) enemyPosY = screenHeight - height;
                // TODO: Life bars decrease logic....................(1p)
				
				if ((ballPosX - ballRadius) <= 0) playerLife -= 20;
				if ((ballPosX + ballRadius) >= screenWidth) enemyLife -= 20;
				
                // TODO: Time counter logic..........................(0.2p)
				
				if (!pause)
				{
					framesCounter++;
					if ((framesCounter == 60) && (secondsCounter != 0))
					{
						framesCounter = 0;					
						secondsCounter--;
					}	
				}
                // TODO: Game ending logic...........................(0.2p)
                
				if ((enemyLife == 0) || (playerLife == 0) || (secondsCounter == 0)) screen = ENDING;
				
                // TODO: Pause button logic..........................(0.2p)
                
				if (IsKeyPressed('P')) pause = !pause;

				 // TODO: Ball movement logic.........................(0.2p)
				 
				if (!pause)
				{
					ballPosX += ballSpeedX;
					ballPosY += ballSpeedY;
				}
				
				//El color del mensaje cambiará según el mensaje que salga, WIN = GREEN, LOSE = RED, DRAW = YELLOW [ ** P.]
				
				if ((playerLife == 0) || ((enemyLife > playerLife) && (secondsCounter == 0))) endingColor = RED;
				if ((playerLife == enemyLife) && (secondsCounter == 0)) endingColor = YELLOW;
				
            } break;
            case ENDING: 
            {
                // Update END screen data here!
                
                // TODO: Replay / Exit game logic....................(0.5p)
                
				if (IsKeyPressed('R'))
				{
				secondsCounter = 99;
				framesCounter = 0;
				playerLife = 200;
				enemyLife = 200;
				ballPosX = screenWidth/2;
				ballPosY = screenHeight/2;
				playerPosY = (screenHeight/2) - (height/2);
				enemyPosY = (screenHeight/2) - (height/2);
				screen = GAMEPLAY;
				}
				//Exit game logic se contiene en la funcion WindowShouldClose.
				//Para que el mensaje de WIN, LOSE y DRAW vaya desapareciendo a partir de los 4 segundos hasta que el canal alfa del color llegue a 0. [** P.]
				
				framesCounter++;
				if ((framesCounter >= 240) && (endingColor.a > 0)) endingColor.a--;
				
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            switch(screen) 
            {
                case LOGO: 
                {
                    // Draw LOGO screen here!
                    
                    // TODO: Draw Logo...............................(0.2p)
		
					DrawText ("DANIEL GAMES", screenWidth/2 - 310, screenHeight/2 - 50, 80, LogoColor);
                    
                } break;
                case TITLE: 
                {
                    // Draw TITLE screen here!
                    
                    // TODO: Draw Title..............................(0.2p)
                    
					DrawText ("EPILEPTIC BALL", screenWidth/2 - 250, screenHeight/2 - 100, 60, TitleColor);
					
                    // TODO: Draw "PRESS ENTER" message..............(0.2p)
                    
					DrawText ("PRESS ENTER", screenWidth/2 - 150, screenHeight/2 + 100, 40, EnterColor);
					
                } break;
                case GAMEPLAY:
                { 
                    // Draw GAMEPLAY screen here!
                    
                    // TODO: Draw player and enemy...................(0.2p)
                    
					DrawRectangle (playerPosX, playerPosY, 20, height, BLACK);
					DrawRectangle (enemyPosX, enemyPosY, 20, height, BLACK);
					
					// TODO: Draw Ball...............................(***p)
					
					DrawCircle (ballPosX, ballPosY, ballRadius, BLACK);
					
                    // TODO: Draw player and enemy life bars.........(0.5p)
                    
					DrawRectangle (99, 9, 202, 22, BLACK);
					DrawRectangle (100, 10, 200, 20, RED);
					DrawRectangle (100, 10, playerLife, 20, GREEN);
					DrawRectangle (499, 9, 202, 22, BLACK);
					DrawRectangle (500, 10, 200, 20, RED);
					DrawRectangle (500, 10, enemyLife, 20, GREEN);
					
                    // TODO: Draw time counter.......................(0.5p)
                    
					DrawText(FormatText("%02i", secondsCounter), screenWidth/2 - 40, 5, 80, BLACK); //"%02i" para que la variable int tenga 2 digitos (01,02,03...)
					
                    // TODO: Draw pause message when required........(0.5p)
                    
					if (pause) DrawText("PAUSE", screenWidth/2 - 150, screenHeight/2 - 50, 100, BLACK);
					
                } break;
                case ENDING: 
                {
                    // Draw END screen here!
                    
                    // TODO: Draw ending message (win or loose)......(0.2p)
                    
					DrawText("IF YOU WANT TO PLAY AGAIN, PRESS 'R'", screenWidth/2 - 200, screenHeight/2 - 50, 20, BLACK);
					DrawText("IF YOU WANT TO EXIT, PRESS 'ESCAPE'", screenWidth/2 - 200, screenHeight /2 + 50, 20, BLACK);
					if ((enemyLife == 0) || ((enemyLife < playerLife) && (secondsCounter == 0))) DrawText("YOU WIN", screenWidth/2 - 250, screenHeight/2 - 50, 100, endingColor);
					if ((playerLife == 0) || ((enemyLife > playerLife) && (secondsCounter == 0))) DrawText("YOU LOSE", screenWidth/2 - 250, screenHeight/2 - 50, 100, endingColor);
					if ((playerLife == enemyLife) && (secondsCounter == 0)) DrawText("DRAW", screenWidth/2 - 200, screenHeight/2 - 50, 100, endingColor);
					
                } break;
                default: break;
            }
        
            DrawFPS(10, 10);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // NOTE: Unload any Texture2D or SpriteFont loaded here
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}