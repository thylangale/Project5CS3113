#include "Level1.h"

#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 1
Mix_Chunk* bounce;

unsigned int level1_data[] =
	{
	 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     17, 0, 0, 0, 0, 0, 0, 67, 67, 67, 0, 0, 0, 0,
     17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
     17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89,
     17, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2,
     17, 0, 0, 0, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
     17, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
	};

void Level1::Initialize() {
    
    state.nextScene = -1;
    if (LIVES <= 2) level1_data[23] = 39;
    if (LIVES <= 1) level1_data[22] = 39;
    if (LIVES == 0) level1_data[21] = 39;

	GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet@2.png");
	state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 14, 7);

    bounce = Mix_LoadWAV("bounce.wav");

	// Move over all of the player and enemy code from initialization.

    // Initialize player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2, 0.0f, 0.0f);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("player.png");

    state.player->animRight = new int[4]{ 3, 7, 11, 15 };
    state.player->animLeft = new int[4]{ 1, 5, 9, 13 };
    state.player->animUp = new int[4]{ 2, 6, 10, 14 };
    state.player->animDown = new int[4]{ 0, 4, 8, 12 };

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;

    state.player->height = 0.8f;
    state.player->width = 0.8f;
    state.player->jumpPower = 6.0f;
    


    //Initialize Enemies
    state.enemies = new Entity();
    GLuint enemyTextureID = Util::LoadTexture("enemy.png"); //add enemy

    state.enemies->entityType = ENEMY;
    state.enemies->textureID = enemyTextureID;

    state.enemies->position = glm::vec3(11, -2.25f, 0);
    state.enemies->movement = glm::vec3(-1.0f, 0, 0);
    state.enemies->speed = 1;
    state.enemies->acceleration = glm::vec3(0, -9.81f, 0);

    state.enemies->aiType = WALKER;
    
}

void Level1::Update(float deltaTime) {
	state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    state.enemies->Update(deltaTime, state.enemies, state.player, 1, state.map);
    
    //Switch scenes
    if (state.player->position.x >= 12) {
        state.nextScene = 1;
    }   
    if (state.player->killedEnemy) { //player beat enemy
        Mix_PlayChannel(-1, bounce, 0);
        state.enemies->isActive = false;
        state.player->killedEnemy = false;
    }
    else if (state.enemies->lastCollision == state.player) { //lose a life
        LIVES -= 1;

        //Restart level
        if (LIVES == -1) state.nextScene = 5;
        else state.nextScene = 0;
        
    }
    
}

void Level1::Render(ShaderProgram* program) {
	state.map->Render(program);
	state.player->Render(program);
    state.enemies->Render(program);
}