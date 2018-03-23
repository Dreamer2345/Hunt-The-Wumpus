#pragma once
#include "ENums.h"

#define CENTERX 63
#define CENTERY 31
#define MAXHAZZARDS 5

const uint8_t PROGMEM Cons[] = {
                          7,5,1,      
                          2,0,9,      
                          3,1,11,     
                          4,13,2,     
                          5,3,0,
                          4,14,6,
                          5,16,7,
                          10,6,0,
                          11,9,18,
                          8,1,10,
                          9,19,7,
                          2,12,8,
                          11,13,17,
                          3,14,12,
                          5,15,13,
                          16,14,17,
                          6,15,19,
                          12,15,18,
                          17,8,19,
                          16,18,10
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
  CurRoom.Room = CurRoom.con[Choice];
  CurRoom.con[0] = pgm_read_byte(&Cons[Index++]);
  CurRoom.con[1] = pgm_read_byte(&Cons[Index++]);
  CurRoom.con[2] = pgm_read_byte(&Cons[Index++]);
}

void RandomiseRooms(){
  for (uint8_t i=0;i<20;i++){RoomHaz[i] = Hazzard::None;}
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

  Place = false;
  do {
    uint8_t r = random(0,19);
    if (RoomHaz[r] == Hazzard::None)
      {
      CurRoom.Room = r;
      uint8_t Index = 3*r;
      CurRoom.con[0] = pgm_read_byte(&Cons[Index++]);
      CurRoom.con[1] = pgm_read_byte(&Cons[Index++]);
      CurRoom.con[2] = pgm_read_byte(&Cons[Index++]);
      Place = true;
      }
  } while(Place != true);
  
}

Hazzard GetHazzard(uint8_t Room){
  return RoomHaz[Room];
}

