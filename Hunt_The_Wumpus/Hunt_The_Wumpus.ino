#include <Arduboy2.h>
Arduboy2 ard;
Sprites sprites;
uint8_t Usable = 0;
uint8_t Points = 0;
#include "Bitmaps.h"
#include "ENums.h"
#include "Rooms.h"
#include "Game.h"

void setup() {
  ard.boot();
  ard.flashlight();
  ard.setFrameRate(30);
}

void loop() {
  if(!ard.nextFrame())
      return;
  ard.pollButtons();
  switch(gamestate){
    case GameState::MainMenu: MainMenu(); break;
    case GameState::StartGame: LevelStart(); break;
    case GameState::Update: Update(); break;
    case GameState::Pit: PitDeath(); break;
    case GameState::Wumpus: Wumpdeath(); break;
    case GameState::Win: Win(); break;
  }
  ard.display(CLEAR_BUFFER);
}
