#pragma once

enum class Hazzard : uint8_t {
  None,
  Pit,
  Bat,
  Wumpus
};

enum class GameState{
  MainMenu,
  StartGame,
  Update,
  Wumpus,
  Pit,
  Win,
}gamestate = GameState::MainMenu;
