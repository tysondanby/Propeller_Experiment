#include "HX711.h"
//Pin config
const int revwire = 19;
const int rcsig = 4;
const int ledPin = 2; //PWM out
const int torqueDOUT = 16;
const int torqueSCK = 12;
const int tachPin = 14;


const int freq = 50;
const int ledChannel = 1;
const int resolution = 16;

const int rcdeadzone = 25;
const float motordeadzone = 0.015;
const float throttlesensitivity = 5.0;
float throttle = 0.0;
float absthrottle = 0.0;
int offset = 1382;

const float torqueScaleFactor = 1;
const int nTorqueReadings = 10;
float Q = 0.0;
float Qs[nTorqueReadings];
HX711 torque;


const int prescaler = 8; // .1 microseconds per count
int tout;
float RPM = 0.0;
bool slow = false;
hw_timer_t *RPMTimer_Cfg = NULL;
hw_timer_t *GlobalTimer_Cfg = NULL;
float globaltime;

int ChipSelect = 5;
File dataFile;
int readsperline = 15;//Number of sensor reads before a tare
bool ifwrite = false;