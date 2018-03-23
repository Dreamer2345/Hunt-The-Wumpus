#pragma once

void LevelStart(){
  RandomiseRooms();
  Points = 0;
  gamestate = GameState::Update;
}

void Wumpdeath(){
  if (Usable == 0){
    Usable = 32;
  }

  if (Usable > 10){
    uint8_t x = CENTERX-32;
    uint8_t y = CENTERY-Usable;
    uint8_t y1 = CENTERY+Usable-10;
    sprites.drawSelfMasked(x,y,Jaw,0);
    sprites.drawSelfMasked(x,y1,Jaw,1);
    Usable--;
  } else
    {
      sprites.drawSelfMasked(CENTERX-32,CENTERY-10,Jaw,0);
      sprites.drawSelfMasked(CENTERX-32,CENTERY,Jaw,1);
      sprites.drawSelfMasked(CENTERX-15,CENTERY-29,Eye,0);
      sprites.drawSelfMasked(CENTERX+5,CENTERY-29,Eye,0);
      ard.setCursor(CENTERX-51,CENTERY+17);
      ard.print(F("A Wumpus ate you!"));
      if (ard.justPressed(A_BUTTON)){
        gamestate = GameState::StartGame;
        Usable = 0;
      }
      if (ard.justPressed(B_BUTTON)){
        gamestate = GameState::Update;
        Usable = 0;

        bool Place = false;
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
    }
}

void PitDeath(){
  if (Usable == 0){
    Usable = 32;
  }

  if (Usable > 1){
    uint8_t x = CENTERX-6;
    uint8_t y = CENTERY-(Usable*2);
    switch(Usable){
    case 5:sprites.drawSelfMasked(x,CENTERY-5,PitFrames[1],0); break;
    case 4:sprites.drawSelfMasked(x-2,CENTERY-5,PitFrames[2],0); break;
    case 3:sprites.drawSelfMasked(x-6,CENTERY-5,PitFrames[3],0); break;
    case 2:sprites.drawSelfMasked(x-7,CENTERY-5,PitFrames[4],0); break;
    case 1:sprites.drawSelfMasked(x-7,CENTERY-5,PitFrames[5],0); break;
    default: sprites.drawSelfMasked(x,y,PitFrames[0],0); break;
    }
    Usable--;
  } else
  {
    sprites.drawSelfMasked(CENTERX-6,CENTERY-5,PitFrames[1],0);
    ard.setCursor(CENTERX-54,CENTERY+17);
      ard.print(F("You Fell in a Pit!"));
      if (ard.justPressed(A_BUTTON)){
        gamestate = GameState::StartGame;
        Usable = 0;
      }
      if (ard.justPressed(B_BUTTON)){
        gamestate = GameState::Update;
        Usable = 0;

        bool Place = false;
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
  }
}

void CheckMove(){
  Hazzard rhzd = GetHazzard(CurRoom.Room);
  switch(rhzd){
    case Hazzard::Pit:gamestate = GameState::Pit; break;
    case Hazzard::Wumpus:gamestate = GameState::Wumpus; break;
    case Hazzard::Bat:if(random(0,10) == 0){bool Place = false;
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
  }
}

void Draw(){
  ard.drawCircle(CENTERX-20,CENTERY-20,10);
  ard.drawCircle(CENTERX+20,CENTERY-20,10);
  ard.drawCircle(CENTERX,CENTERY+20,10);
  ard.drawCircle(CENTERX,CENTERY-5,10);
  ard.setCursor(CENTERX-26,CENTERY-23);
  ard.print(CurRoom.con[0]);
  ard.setCursor(CENTERX+16,CENTERY-23);
  ard.print(CurRoom.con[1]);
  ard.setCursor(CENTERX-5,CENTERY-8);
  ard.print(CurRoom.Room);
  ard.setCursor(CENTERX-6,CENTERY+18);
  ard.print(CurRoom.con[2]);

  for (uint8_t i=0;i<3;i++){
    if(GetHazzard(CurRoom.con[i]) == Hazzard::Pit){
        sprites.drawSelfMasked(CENTERX+20,CENTERY,Snowflake,0);
        break;
    }
  }
  for (uint8_t i=0;i<3;i++){
    if(GetHazzard(CurRoom.con[i]) == Hazzard::Wumpus){
        sprites.drawSelfMasked(CENTERX-30,CENTERY,Stink,0);
        break;
    }
  }
}

void MovePlayer(){
      if (ard.justPressed(LEFT_BUTTON)){
        SetNextRoom(0);
      } else
      if (ard.justPressed(RIGHT_BUTTON)){
        SetNextRoom(1);
      } else
      if (ard.justPressed(DOWN_BUTTON)){
        SetNextRoom(2);
      }
      if (ard.justPressed(A_BUTTON)){
        bool Done = false;
        do{
            if(ard.nextFrame())
              {    
              ard.pollButtons();
              Hazzard k = Hazzard::None;
              if (ard.justPressed(LEFT_BUTTON)){
                k = GetHazzard(CurRoom.con[0]);
                Done = true;
              } else
              if (ard.justPressed(RIGHT_BUTTON)){
                k = GetHazzard(CurRoom.con[1]);
                Done = true;
              } else
              if (ard.justPressed(DOWN_BUTTON)){
                k = GetHazzard(CurRoom.con[2]);
                Done = true;
              }
              
              if((k == Hazzard::Wumpus)&&(Done == true)){
                gamestate = GameState::Win;
              } else {
                gamestate = GameState::Wumpus;
              }
              Draw();
              ard.display(CLEAR_BUFFER);
              }
        }while(Done == false);
      }
}


void Update(){
  MovePlayer();
  CheckMove();
  Draw();
}


