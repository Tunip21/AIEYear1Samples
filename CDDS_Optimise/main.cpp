/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "Critter.h"
#include <random>
#include <time.h>
#include <iostream>

#include "AABB.h"


float SquareDist(Vector2 a, Vector2 b)
{
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Critter BeginOfArray(Critter critterArray[], int CRITTER_COUNT, int critterAlive)
{
    Critter alive = critterArray[critterAlive];
    for (int n = critterAlive; n > 0; --n)
    {
        critterArray[n] = critterArray[n - 1];
    }
    critterArray[0] = alive;
    return critterArray[0];
}
Critter EndOfArray(Critter critterArray[], int CRITTER_COUNT, int critterDead)
{
    Critter dead = critterArray[critterDead];
    for (int n = critterDead; n < CRITTER_COUNT; ++n)
    {
        critterArray[n] = critterArray[n + 1];
    }
    critterArray[CRITTER_COUNT - 1] = dead;
    return critterArray[CRITTER_COUNT - 1];
}



int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D critterTexture = LoadTexture("res/10.png");
    Texture2D destroyerTexture = LoadTexture("res/9.png");


    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));

    Critter critters[1000];
    AABB particians[16];
    int n = 0;

    for (int x = 0; x < 4; x++)
    {
	    for (int y = 0; y < 4; y++, n++)
	    {
            MathClasses::Vector3 a = {200.f * x, 113.f * y, 1};
			MathClasses::Vector3 b = {200.f * (x + 1), 113.f * (y + 1), 1};
		    particians[n].min = a;
		    particians[n].max = b;
	    }
    }

    // create some critters
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    int crittersAlive = CRITTER_COUNT;
    int crittersDead = 0;

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        // create a random direction vector for the velocity
        Vector2 velocity = {-100 + (rand() % 200), -100 + (rand() % 200)};
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
        // create a critter in a random location

        critters[i].Init(
            {(float)(5+rand() % (screenWidth-10)), (float)(5+(rand() % screenHeight-10))},
            velocity,
            12, critterTexture);
    }

    Critter destroyer;
    Vector2 velocity = {-100 + (rand() % 200), -100 + (rand() % 200)};
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{(float)(screenWidth >> 1), (float)(screenHeight >> 1)}, velocity, 20, destroyerTexture);

    float timer = 1;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

    	float delta = GetFrameTime();

        // update the destroyer
        destroyer.Update(delta);
        // check each critter against screen bounds
        if (destroyer.GetX() < 0)
        {
            destroyer.SetX(0);
            destroyer.SetVelocity(Vector2{-destroyer.GetVelocity().x, destroyer.GetVelocity().y});
        }
        if (destroyer.GetX() > screenWidth)
        {
            destroyer.SetX(screenWidth);
            destroyer.SetVelocity(Vector2{-destroyer.GetVelocity().x, destroyer.GetVelocity().y});
        }
        if (destroyer.GetY() < 0)
        {
            destroyer.SetY(0);
            destroyer.SetVelocity(Vector2{destroyer.GetVelocity().x, -destroyer.GetVelocity().y});
        }
        if (destroyer.GetY() > screenHeight)
        {
            destroyer.SetY(screenHeight);
            destroyer.SetVelocity(Vector2{destroyer.GetVelocity().x, -destroyer.GetVelocity().y});
        }

        // update the critters
        // (dirty flags will be cleared during update)
        for (int i = 0; i < CRITTER_COUNT - crittersDead; i++)
        {
            critters[i].Update(delta);

            //assign pointers to grid location for critters
            n = 0;
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 4; y++, n++)
                {
		            if (particians[n].Overlaps({critters[i].m_position.x, critters[i].m_position.y, 1}))
		            {
                        critters[i].gridPosition = &particians[n];
		                //DrawRectangleLines(200 * x, 113 * y, 200, 113, BLUE);
		            }
                }
            }
            //assign pointers to grid location for destroyer
            n = 0;
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 4; y++, n++)
                {
		            if (particians[n].Overlaps({destroyer.m_position.x, destroyer.m_position.y, 1}))
		            {
                        destroyer.gridPosition = &particians[n];
		                //DrawRectangleLines(200 * x, 113 * y, 200, 113, BLUE);
		            }
                }
            }

        	// check each critter against screen bounds
            if (critters[i].GetX() < 0)
            {
                critters[i].SetX(0);
                critters[i].SetVelocity(Vector2{-critters[i].GetVelocity().x, critters[i].GetVelocity().y});
            }
            if (critters[i].GetX() > screenWidth)
            {
                critters[i].SetX(screenWidth);
                critters[i].SetVelocity(Vector2{-critters[i].GetVelocity().x, critters[i].GetVelocity().y});
            }
            if (critters[i].GetY() < 0)
            {
                critters[i].SetY(0);
                critters[i].SetVelocity(Vector2{critters[i].GetVelocity().x, -critters[i].GetVelocity().y});
            }
            if (critters[i].GetY() > screenHeight)
            {
                critters[i].SetY(screenHeight);
                critters[i].SetVelocity(Vector2{critters[i].GetVelocity().x, -critters[i].GetVelocity().y});
            }
            // kill any critter touching the destroyer
            // simple circle-to-circle collision check
            if (destroyer.gridPosition == critters[i].gridPosition)
            {
	            float dist = SquareDist(critters[i].GetPosition(), destroyer.GetPosition());
	            if (dist < critters[i].GetRadius() * critters[i].GetRadius() + destroyer.GetRadius() * destroyer.GetRadius())
	            {
	                critters[i].Destroy();
	                crittersDead++;
	                // this would be the perfect time to put the critter into an object pool
	                critters[CRITTER_COUNT - 1] = EndOfArray(critters, CRITTER_COUNT, i);
	            }
            }
        }

        for (int i = 0; i < CRITTER_COUNT - crittersDead; i++)
        {
	        for (int j = 0; j < CRITTER_COUNT - crittersDead; j++)
	        {
		        if (critters[i].gridPosition == critters[j].gridPosition)
		        {
                    if (i == j || critters[i].IsDirty())
                    {
                        continue;
                    }
                    float dist = SquareDist(critters[i].GetPosition(), critters[j].GetPosition());
                    if (dist < critters[i].GetRadius() * critters[i].GetRadius() + critters[j].GetRadius() * critters[j].GetRadius())
                    {
                        Vector2 normal = Vector2Normalize(Vector2Subtract(critters[j].GetPosition(), critters[i].GetPosition()));

                        critters[i].SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));

                        critters[i].SetDirty();

                        if (!critters[j].IsDirty())
                        {
                            critters[j].SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                            critters[j].SetDirty();
                        }
                        break;
                    }
		        }
	        }
        }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

            // find any dead critters and spit them out (respawn)
            if (critters[CRITTER_COUNT - 1].IsDead())
            {
            	//new code, the last element of the array should always be a dead critter
                Vector2 normal = Vector2Normalize(destroyer.GetVelocity());
                // get a position behind the destroyer, and far enough away that the critter won't bump into it again
                Vector2 pos = destroyer.GetPosition();
                pos = Vector2Add(pos, Vector2Scale(normal, -50));
                // its pretty ineficient to keep reloading textures. ...if only there was something else we could do

                critters[0] = BeginOfArray(critters, CRITTER_COUNT, CRITTER_COUNT - 1);

                critters[0].Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, critterTexture);
                crittersDead--;

                nextSpawnPos = destroyer.GetPosition();
            }
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the critters
        for (int i = 0; i < CRITTER_COUNT; i++)
        {
            critters[i].Draw();
        }
        // draw the destroyer
        // (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
        // destroyer, it's because the origin is at the top-left. ...you could fix that!) 
        destroyer.Draw();

        /*for (int x = 0; x < 4; x++) //visual representation only
        {
	        for (int y = 0; y < 4; y++)
	        {
                DrawRectangleLines(200 * x, 113 * y, 200, 113, RED);
	        }
        }*/

        DrawFPS(10, 10);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (int i = 0; i < CRITTER_COUNT - crittersDead; i++)
    {
        critters[i].Destroy();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}