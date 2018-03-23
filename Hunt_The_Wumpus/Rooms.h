#pragma once
#include "ENums.h"

#define CENTERX 63
#define CENTERY 31
#define MAXHAZZARDS 5

const uint8_t PROGMEM Cons[] = {1,4,7,
                          0,2,9,
                          1,3,11,
                          2,13,4,
                          0,3,5,
                          14,4,6,
                          5,7,16,
                          0,6,10,
                          11,18,9,
                          8,1,10,
                          19,7,9,
                          2,12,8,
                          11,13,17,
                          13,15,5,
                          14,17,16,
                          19,6,15,
                          15,12,18,
                          8,17,19,
                          10,18,16
                          };

Hazzard RoomHaz[20];
                          
struct Room{
  uint8_t con[3];
  uint8_t Room;
  Hazzard Haz;
} CurRoom;

void SetNextRoom(uint8_t Choice){
  uint8_t Index = 3*CurRoom.con[Choice];
  CurRoom.Haz = RoomHaz[CurRoom.con[Choice]];
  CurRoom.con[0] = pgm_read_byte(&Cons[Index++]);
  CurRoom.con[1] = pgm_read_byte(&Cons[Index++]);
  CurRoom.con[2] = pgm_read_byte(&Cons[Index++]);
}

void RandomiseRooms(){
  uint8_t Hazzards = 0;
  do {
    uint8_t r = random(0,19);
    if (RoomHaz[r] == Hazzard::None)
      {
      RoomHaz[r] = static_cast<Hazzard>(random(1,2));
      Hazzards++;
      }
  } while(Hazzards != MAXHAZZARDS);
  bool Place = false;
  do {
    uint8_t r = random(0,19);
    if (RoomHaz[r] == Hazzard::None)
      {
      RoomHaz[r] = Hazzard::Wumpus;
      Place = true;
      }
  } while(Place != true);
}

Hazzard GetHazzard(uint8_t Room){
  return RoomHaz[Room];
}

