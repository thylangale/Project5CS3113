#include "Game Won.h"

#define Won_WIDTH 11
#define Won_HEIGHT 8

#define Won_ENEMY_COUNT 0

GLuint font1TextureID;

unsigned int Won_data[] =
{
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
};

void GameWon::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("platformPack_tilesheet@2.png");
    state.map = new Map(Won_WIDTH, Won_HEIGHT, Won_data, mapTextureID, 1.0f, 14, 7);
    // Move Won all of the player and enemy code from initialization.
    // Initialize player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5, 0.0f, 0.0f);
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

    font1TextureID = Util::LoadTexture("font1.png");
}

void GameWon::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, NULL, Won_ENEMY_COUNT, state.map);
}

void GameWon::Render(ShaderProgram* program) {
    state.map->Render(program);
    state.player->Render(program);

    //Game Name
    Util::DrawText(program, font1TextureID, "You Won!", 1, -0.2, glm::vec3(2.5, -2, 0));

    //How to start the game
    Util::DrawText(program, font1TextureID, "Press Enter to Exit", 0.5f, -0.2, glm::vec3(2.5, -4, 0));
}