#ifndef Illumination_h
#define Illumination_h
#include "arduino.h"

//SSR port const
#define SSR_1 2
#define SSR_2 3
#define SSR_3 4
#define SSR_4 5
#define SSR_5 6
#define SSR_6 7
#define SSR_7 8
#define SSR_8 9

struct PatternList{
public:
 void (*FunctionAddress)();
 char ControlWord;
};

class Illumination{
public:
    Illumination();
    static bool ChageMode;
    static char Mode;
    static int RunningFunctionNumber;
    static void setup(bool PortMode);
    static void loopAction();
    static void wait();
    static void Run();
    static void SerialLoop();
    static void delay(unsigned long Ms);
    static bool setPattern(void (*PatternFunction)(),char SelectWord);
    static void ssrOn(int Num);
    static void ssrOff(int Num);
    static PatternList list[];
private:
};

#endif