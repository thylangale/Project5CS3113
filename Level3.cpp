#include "Level3.h"

#define LEVEL3_WIDTH 14
#define LEVEL3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 1

unsigned int level3_data[] =
{
 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 17, 0, 0, 0, 0, 0, 0, 67, 67, 67, 0, 0, 0, 0,
 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 75,
 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 89,
 17, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1,
 17, 1, 1, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3,
 17, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3
};

void Level3::Initialize() {

    state.nextScene = -1;
    if (LIVES <= 2) level3_data[23] = 39;
    if (LIVES <= 1) level3_data[22] = 39;
    if (LIVES == 0) level3_data[21] = 39;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet@2.png");
    state.map = new Map(LEVEL3_WIDTH, LEVEL3_HEIGHT, level3_data, mapTextureID, 1.0f, 14, 7);
    // Move over all of the player and enemy code from initialization.
    // Initialize player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, 0.0f, 0.0f);
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
    state.enemies->movement = glm::vec3(0);
    state.enemies->speed = 0.75;
    state.enemies->acceleration = glm::vec3(0, -9.81f, 0);

    state.enemies->aiType = WAITANDGO;
    state.enemies->aiState = IDLE;
}

void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    state.enemies->Update(deltaTime, state.enemies, state.player, 1, state.map);

    //Switch scenes
    if (state.player->position.x >= 12) {
        state.nextScene = 4;
    }
    if (state.player->killedEnemy) { //player beat enemy
        state.enemies->isActive = false;
    }

    else if (state.enemies->lastCollision == state.player || state.player->position.y < -6.5) { //lose a life

        LIVES -= 1;

        //Restart level
        if (LIVES == -1) state.nextScene = 5;
        else state.nextScene = 2;
    }
}

void Level3::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);
    state.enemies->Render(program);
}