#include "arduino.h"
#include "Illumination.h"
#include <Scheduler.h>

#define func_max 256

bool Illumination::ChageMode=false;
char Illumination::Mode= '0';
int Illumination::RunningFunctionNumber = 0;
PatternList Illumination::list[func_max];

jmp_buf buf_data;

Illumination::Illumination(){
    ;
}

void Illumination::SerialLoop(){
    if(Serial.available() > 0){
        char recieve = Serial.read();
        if(recieve != Mode){
            for(int i=0;i<func_max;i++){
                if(list[i].ControlWord == recieve){
                    ChageMode = true;
                    RunningFunctionNumber = i;
                    Mode = recieve;
                    break;
                }
                if(list[i].FunctionAddress == NULL){
                    break;
                }
            }
        }
    }
    Scheduler.yield();
}

void Illumination::Run(){
    setjmp(buf_data);
    if(list[RunningFunctionNumber].FunctionAddress != NULL)
        list[RunningFunctionNumber].FunctionAddress();
    Scheduler.yield();
}

void Illumination::setup(bool PortMode){
    for(int i=0;i<func_max;i++)
        list[i].FunctionAddress = NULL;
    if(PortMode)
        for(int i=2;i<=9;i++)
            pinMode(i,OUTPUT);
    Serial.begin(9600);
    Scheduler.startLoop(Illumination::SerialLoop);
    Scheduler.startLoop(Illumination::Run);
}

void Illumination::loopAction(){
    Scheduler.yield();
}


void Illumination::wait(){
    while(true){
        if(ChageMode){
            ChageMode = false;
            longjmp(buf_data,1);
        }
        Scheduler.yield();
    }
}

void Illumination::ssrOn(int Num){
    digitalWrite(Num,HIGH);
}

void Illumination::ssrOff(int Num){
    digitalWrite(Num,HIGH);
}


void Illumination::delay(unsigned long Ms){
    unsigned long start_time = millis();
    while(true){
        if(ChageMode){
            ChageMode = false;
            longjmp(buf_data,1);
        }
        if(start_time + Ms <= millis())
            break;
        Scheduler.yield();
    }
}

bool Illumination::setPattern(void (*PatternFunction)(),char SelectWord){
    for(int i=0;i<func_max;i++){
        if(list[i].FunctionAddress == NULL){
            list[i].FunctionAddress = PatternFunction;
            list[i].ControlWord = SelectWord;
            return true;
        }
        else if(list[i].ControlWord == SelectWord){
            list[i].FunctionAddress = PatternFunction;
            return true;
        }
    }
    return false;
}

