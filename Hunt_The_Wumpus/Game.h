#pragma once


void Wumpdeath(){
  if (Usable == 0){
    Usable = 64;
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
    }
}

