//
//  NGCustom8x8RGBMatrixGame.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 18.12.22.
//

#ifndef _NGCustom8x8RGBMatrixGame_h
#define _NGCustom8x8RGBMatrixGame_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomGame.h>
#include <NGColorDotMatrix.h>

class NGCustom8x8RGBMatrixGame : public NGCustomGame {
       
protected:
    NGColorDotMatrix *_cdm;
    
public:
    void registerColorDotMatrix(NGColorDotMatrix *cdm);
};
    

#endif /* _NGCustom8x8RGBMatrixGame_h */
