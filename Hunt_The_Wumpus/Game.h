#pragma once


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
        gamestate = GameState::Pit;
        Usable = 0;
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
        gamestate = GameState::Wumpus;
        Usable = 0;
      }
  }
}

