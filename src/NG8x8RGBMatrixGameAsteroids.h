//
//  NG8x8RGBMatrixGameAsteroids.h
//  NGEngineGames
//
//  Created by Nils Grimmer on 07.01.23.
//

#ifndef NG8x8RGBMatrixGameAsteroids_h
#define NG8x8RGBMatrixGameAsteroids_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustom8x8RGBMatrixGame.h>

#define GAMEASTEROIDSCOLORSCOREOFF  { .red = 5, .green = 5, .blue = 5 }
#define GAMEASTEROIDSCOLORSCOREON   COLOR_GREEN

#define GAMEASTEROIDSMAZESIZEX            8
#define GAMEASTEROIDSMAZESIZEY            7
#define GAMEASTEROIDSSCOREDIGITS          8
#define GAMEASTEROIDSSCOREDIGITXPOS       0
#define GAMEASTEROIDSSCOREDIRECTION bddLeft

#define GAMEASTEROIDSMOVEDELAY    500
#define GAMEASTEROIDSFINISHDELAY 1000

#define GAMEASTEROIDSSTARTPOSX 0
#define GAMEASTEROIDSSTARTPOSY 3

#define GAMEASTEROIDSCOLORINDEXSPACECRAFT 1
#define GAMEASTEROIDSCOLORINDEXLASERBEAM  2
#define GAMEASTEROIDSCOLORINDEXASTEROID   3

#define GAMEASTEROIDSOUTRODELAY   100

static byte globalAsteroidsColors[3][3] = {
  {0, 0, 255}, // Spacecraft
  {255, 0, 0}, // Laser
  {30, 30, 30} // Asteroid
};

class NG8x8RGBMatrixGameAsteroids : public NGCustom8x8RGBMatrixGame {
 
private:
    byte _posXSpacecraft = GAMEASTEROIDSSTARTPOSX;
    byte _posYSpacecraft = GAMEASTEROIDSSTARTPOSY;
    int _maze[GAMEASTEROIDSMAZESIZEY][GAMEASTEROIDSMAZESIZEX];
    long _lastAsteroidsMove = 0;
    
    void _resetMaze();
    
    void _computeAsteroids();
    
    bool _computeLaserbeam();
    
    void _spawnAsteroid();
    
    void _spawnLaserbeam();
    
    void _clearSpacecraft();
    
    void _computeSpacecraft();
    
    bool _checkSpacecraft(byte posX, byte posY);
    
    void _ownJoystickLoop();
    
    void _ownRender();
    
    void _ownOutro();
    
protected:
    void _doInitialize();
    
    void _doStartUp();
    
    void _doStartUpDone();
    
    void _doStartGame();
    
    void _doBreakGame();
    
    void _doContinueGame();
    
    void _doFinishGame();
    
    void _doProcessingLoop();
       
public:
    NG8x8RGBMatrixGameAsteroids();
};


#endif /* NG8x8RGBMatrixGameAsteroids_h */
