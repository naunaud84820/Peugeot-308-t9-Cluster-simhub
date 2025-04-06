//Credits: https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/ and SimHub

/* copy paste this in simhub custom protocol
format(round([Rpms], 0),'0') + ';' +
isnull(round([SpeedKmh],0),'0') + ';' +
isnull(round([FuelPercent],0),'0') + ';' +
isnull(round([WaterTemperature], 0), '0') + ';' +
isnull([Gear],'0') + ';' +
isnull([TurnIndicatorLeft],'0') + ';' +
isnull([TurnIndicatorRight],'0') + ';' +
isnull([EngineIgnitionOn],'0') + ';' +
isnull([Handbrake],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.MotorValues.BrakeValues.ParkingBrake],'0') + ';' +
isnull([ABSActive],'0') + ';' +
isnull([TCActive],'0') + ';' +
isnull([GameRawData.ShowLights],'0') + ';' +
if([CarSettings_RPMShiftLight1] > 0, 1, 0) + ';' +
isnull([GameRawData.light_LowBeam],'0') + ';' +
isnull([GameRawData.light_HighBeam],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.LightsValues.BeamLow],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.LightsValues.BeamHigh],'0') + ';' +
isnull([DataCorePlugin.GameRawData.Drivetrain.CruiseControl],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DashboardValues.CruiseControlSpeed.Kph],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.Chassis],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.Engine],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.WheelsAvg],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DashboardValues.Odometer],'0') + ';' +
isnull([GameRawData.NavigationValues.NavigationDistance],'0') + ';'
*/


#ifndef _SHCUSTOMPROTOCOL_H_
#define _SHCUSTOMPROTOCOL_H_
#include <Arduino.h>

String fuel, temp, gear, turnL, turnR, ignition, handbrake, scshandbrake, ABSS, TCS, showLights, shiftLight, lowBeams, highBeams, scslowBeams, scshighBeams, cruisControl, cruisControlspd, chassisdmgscs, enginedmgscs, wheeldmgscs, odo, gps;
int rpm, rpmGate, speed, spdGran, spdTune, parkBrake, turn, beams, ignit, gearex, fuelex, tempint, tempex, dwtemp, lowfuel, battery, warnLightd, shiftL, cruisCtrl, cruisspeed, cruisTune, cruisGran, tyrepressure, odoGran, odoMid, odoLast, gpsGran, gpsMid, gpsLast;
String spdhex1 = "";
String spdhex2 = "";
String cruishex1 = "";
String cruishex2 = "";
String odohex1 = "";
String odohex2 = "";
String odohex3 = "";
String gpshex1 = "";
String gpshex2 = "";
String gpshex3 = "";
class SHCustomProtocol {
private:

public:
  void setup() { // Runs once
  }

  void read() { // Runs on every message sent 
    rpm = FlowSerialReadStringUntil(';').toInt();
    if(rpm > 7000) { //change RPM max here
      rpm = 7000; //and here
    }
    rpmGate = map(rpm, 0, 7000, 0, 220);//and here (7000)
    speed = FlowSerialReadStringUntil(';').toInt();
    if(speed > 254) {
      speed = 254;
    }
    int spddecimalValue = (speed-3)*100;
    if(spddecimalValue < 0) {
      spddecimalValue = 0;
    }
    String spdhexValue = String(spddecimalValue, HEX);
    while (spdhexValue.length() < 4) {
      spdhexValue = "0" + spdhexValue;
    }
    spdhex1 = "0x" + spdhexValue.substring(0, 2);
    spdhex2 = "0x" + spdhexValue.substring(2, 4);
    int spdintHex1 = strtol(spdhex1.substring(2).c_str(), NULL, 16);
    int spdintHex2 = strtol(spdhex2.substring(2).c_str(), NULL, 16);
    float spddecHex1 = (float)spdintHex1;
    float spddecHex2 = (float)spdintHex2;
    spdGran = spddecHex1;
    spdTune = spddecHex2;
    fuel = FlowSerialReadStringUntil(';');
    fuelex = fuel.toInt();
    if(fuelex > 100) {
      fuelex = 100; 
    }
    if(ignition == "1") {
      if (fuelex < 10) {
        lowfuel = 0x80;
      } else {
        lowfuel = 0x00;
      } 
    } else {
      lowfuel = 0x00;
    }
    temp = FlowSerialReadStringUntil(';');
    tempint = temp.toInt();
    tempex = round(tempint*160/100);
    if(ignition == "1") {
      if (tempint > 97) {
        dwtemp = 0x80;
      } else {
        dwtemp = 0x00;
      } 
    } else {
      dwtemp = 0x00;
    }
    gear = FlowSerialReadStringUntil(';');
    //byte 2:0x00 P, 0x10 R, 0x20 N, 0x32 D1, 0x34 D2, 0x36 D3, 0x38 D4, 0x3a D5, 0x3c D6, 0x90 1, 0x80 2, 0x70 3, 0x60 4, 0x50 5, 0x40 6
    if(gear == "N") {
      gearex = 0x20;
    } else if(gear == "1") {
      gearex = 0x90;
    } else if(gear == "2") {
      gearex = 0x80;
    } else if(gear == "3") {
      gearex = 0x70;
    } else if(gear == "4") {
      gearex = 0x60;
    } else if(gear == "5") {
      gearex = 0x50;
    } else if(gear == "6") {
      gearex = 0x40;
    } else if(gear == "R") {
      gearex = 0x10;
    } else {
      gearex = 0x30;
    }
    turnL = FlowSerialReadStringUntil(';');
    turn = 0;
    if(turnL == "1") {
      turn += 0x02;
    } 
    turnR = FlowSerialReadStringUntil(';');
    if(turnR == "1") {
      turn += 0x04;
    }
    ignition = FlowSerialReadStringUntil(';');
    warnLightd = 0;
    if(ignition == "1") {
      if (rpm < 100) {
        warnLightd += 0x02;
        battery = 0x02;
        ignit = 0x8e;
      } else {
        warnLightd += 0x00;
        battery = 0x00;
        ignit = 0x8e;
      }
    } else {
      warnLightd += 0x00;
      battery = 0x00;
      ignit = 0x00;
    }
    handbrake = FlowSerialReadStringUntil(';');
    parkBrake = 0;
    if(handbrake > "10") {
      parkBrake += 0x02;
    } else {
      parkBrake += 0;
    }
    scshandbrake = FlowSerialReadStringUntil(';');
    if(scshandbrake == "True") {
      parkBrake += 0x02;
    } else {
      parkBrake += 0;
    }
    ABSS = FlowSerialReadStringUntil(';');
    if(ABSS == "1") {
      warnLightd += 0x20;
    } else {
      warnLightd += 0x00;
    }
    TCS = FlowSerialReadStringUntil(';');
    showLights = FlowSerialReadStringUntil(';');
    shiftLight = FlowSerialReadStringUntil(';');
    if(shiftLight == "1" ) {//disable here to remove shift light on belt led
      shiftL = 0xff;//disable here to remove shift light on belt led
    } else {//disable here to remove shift light on belt led
      shiftL = 0;//disable here to remove shift light on belt led
    }//disable here to remove shift light on belt led
    lowBeams = FlowSerialReadStringUntil(';');
    if(lowBeams == "1" ) {
      turn += 0xc0;
    } else {
      turn += 0;
    }
    highBeams = FlowSerialReadStringUntil(';');
    if(highBeams == "1" ) {
      turn += 0xe0;
    } else {
      turn += 0;
    }
    scslowBeams = FlowSerialReadStringUntil(';');
    if(scslowBeams == "True" ) {
      turn += 0xc0;
    } else {
      turn += 0;
    }
    scshighBeams = FlowSerialReadStringUntil(';');
    if(scshighBeams == "True" ) {
      turn += 0xe0;
    } else {
      turn += 0;
    }
    cruisControl = FlowSerialReadStringUntil(';');
    if(cruisControl == "True" ) {
      cruisCtrl = 0x48;
    } else {
      cruisCtrl = 0;
    }
    cruisControlspd = FlowSerialReadStringUntil(';');
    cruisspeed = cruisControlspd.toInt();
    if(cruisspeed > 254) {
      cruisspeed = 254;
    }
    int cruisdecimalValue = cruisspeed*100;
    String cruishexValue = String(cruisdecimalValue, HEX);
    while (cruishexValue.length() < 4) {
      cruishexValue = "0" + cruishexValue;
    }
    cruishex1 = "0x" + cruishexValue.substring(0, 2);
    cruishex2 = "0x" + cruishexValue.substring(2, 4);
    int cruisintHex1 = strtol(cruishex1.substring(2).c_str(), NULL, 16);
    int cruisintHex2 = strtol(cruishex2.substring(2).c_str(), NULL, 16);
    float cruisdecHex1 = (float)cruisintHex1;
    float cruisdecHex2 = (float)cruisintHex2;
    cruisGran = cruisdecHex1;
    cruisTune = cruisdecHex2;
    chassisdmgscs = FlowSerialReadStringUntil(';');
    if(chassisdmgscs > "1") {
      chassisdmgscs = "0";
    }
    if(chassisdmgscs > "0.15") {
      parkBrake += 0x80;
    } else {
      parkBrake += 0x00;
    }
    enginedmgscs = FlowSerialReadStringUntil(';');
    if(enginedmgscs > "1") {
      enginedmgscs = "0";
    }
    if(enginedmgscs > "0.15") {
      warnLightd += 0x02;
    } else {
      warnLightd += 0x00;
    }
    wheeldmgscs = FlowSerialReadStringUntil(';');
    if(wheeldmgscs > "1") {
      wheeldmgscs = "0";
    }
    if(wheeldmgscs > "0.50") {
      tyrepressure = 0x80;
    } else {
      tyrepressure = 0x00;
    }
    odo = FlowSerialReadStringUntil(';');
    long odob = odo.toInt()*10;
    long ododecimalValue = odob;
    String odohexValue = String(ododecimalValue, HEX);
    while (odohexValue.length() < 6) {
      odohexValue = "0" + odohexValue;
    }
    odohex1 = "0x" + odohexValue.substring(0, 2);
    odohex2 = "0x" + odohexValue.substring(2, 4);
    odohex3 = "0x" + odohexValue.substring(4, 6);
    int odointHex1 = strtol(odohex1.substring(2).c_str(), NULL, 16);
    int odointHex2 = strtol(odohex2.substring(2).c_str(), NULL, 16);
    int odointHex3 = strtol(odohex3.substring(2).c_str(), NULL, 16);
    float ododecHex1 = (float)odointHex1;
    float ododecHex2 = (float)odointHex2;
    float ododecHex3 = (float)odointHex3;
    odoGran = ododecHex1;
    odoMid = ododecHex2;
    odoLast = ododecHex3;
    gps = FlowSerialReadStringUntil(';');
    long gpsb = gps.toInt();
    long gpsdecimalValue = gpsb;
    String gpshexValue = String(gpsdecimalValue, HEX);
    while (gpshexValue.length() < 6) {
      gpshexValue = "0" + gpshexValue;
    }
    gpshex1 = "0x" + gpshexValue.substring(0, 2);
    gpshex2 = "0x" + gpshexValue.substring(2, 4);
    gpshex3 = "0x" + gpshexValue.substring(4, 6);
    int gpsintHex1 = strtol(gpshex1.substring(2).c_str(), NULL, 16);
    int gpsintHex2 = strtol(gpshex2.substring(2).c_str(), NULL, 16);
    int gpsintHex3 = strtol(gpshex3.substring(2).c_str(), NULL, 16);
    float gpsdecHex1 = (float)gpsintHex1;
    float gpsdecHex2 = (float)gpsintHex2;
    float gpsdecHex3 = (float)gpsintHex3;
    gpsGran = gpsdecHex1;
    gpsMid = gpsdecHex2;
    gpsLast = gpsdecHex3;
    String concate = "";
    int p = 0;
    while(p < showLights.length()) { // This is a parser for the ShowLights raw data from simhub.
      if(showLights[p] == ',') {
        p+=2;
        if(concate == "DL_SHIFT") {

        } else if(concate == "DL_TC") {

        } else if(concate == "DL_OILWARN") {

        } else if(concate == "DL_BATTERY") {
          battery = 0x02;
        } else if(concate == "DL_ABS") {
          warnLightd += 0x20;
        } else if(concate == "DL_HANDBRAKE") {
          parkBrake += 0x02;
        } else if(concate == "DL_FULLBEAM") {
          turn += 0xc0;
          turn += 0xe0;
        }
        concate="";
        continue;
      }
      concate=concate+showLights[p];
      p++;
    }
  }

  void loop() { // Called once per arduino loop
    // Odometer/Ignition/Temp Gauge
    opSend(0x0F6, ignit, tempex, odoGran, odoMid, odoLast, 0xff, 0xff, 0x20); //ignit
    //byte2 coolant t° 90=60°(0) 135=85° 150=90° 160=100°(max)
    //byte345 odometre 10, 13, 17=65870 

    // Speedo and rpm
    opSend(0x0B6, rpmGate, 0, spdGran, spdTune, 0x00, 0x00, 0x00, 0xD0);
    //byte1 rpm: 27=900rpm(ralentis) 220=7000rpm
    //byte3 speed: 100=254km/h 50=131km/h
    //map(Speed, 0, 250, 0, 1680)

    //Dash lights
    opSend(0x128, turn, gearex, 0x00, parkBrake, 0x00, lowfuel, shiftL, 0x00);
    //byte1 ABCDEFGH a=position beam  b=low beam  c=high beam  d=AB AV  e=AB AR  f=right turn  g=left turn  h=?
    //byte2 :0x00 P, 0x10 R, 0x20 N, 0x32 D1, 0x34 D2, 0x36 D3, 0x38 D4, 0x3a D5, 0x3c D6, 0x90 1, 0x80 2, 0x70 3, 0x60 4, 0x50 5, 0x40 6
    //byte3 ABCDEFGH a=? b=? c=S d=? e=? f=? g=enable/disable byte2
    //byte4 ABCDEFGH a=service  b=stop  c=?  d=?  e=startandstopblink  f=startandstop  g=parkbrake  h=autoparkbrakeoff
    //byte6 ABCDEFGH a=lowfuel  b=belt  c=?  d=belt  e=?  f=UREA  g=UREAblink  h=belt

    //Warning lights
    opSend(0x168, dwtemp, tyrepressure, battery, warnLightd, 0x00, 0x00, 0x00, 0x00);
    //byte1 ABCDEFGH a=dangerwatertemp b=? c=? d=? e=? f=(!) g=? h=?
    //byte2 ABCDEFGH a=tyrepressure b=? c=engineblink d=? e=autowipers f=? g=? h=+start
    //byte3 ABCDEFGH a=? b=? c=? d=? e=(!) f=? g=battery h=?
    //byte4 ABCDEFGH a=(p)! b=(p)blink c=(abs) d=esp e=? f=? g=checkengine h=?

    //Backlight
    opSend(0x036, 0X0E, 0x00, 0x00, 0x6f, 0x01, 0x00, 0x00, 0xA0);
    //byte2 ABCDEFGH a= b= c= d=backlight e= f= g= h=

    //Fuel
    opSend(0x161, 0x00, 0x00, 0x32, fuelex, 0x00, 0x00, 0x00, 0x57);
    //Byte4 100=100% 0=0%

    //Display
    opSend(0x221, 0x1, 0xFF, 0xFF, 0x01, 0x72, 0xFF, 0xFF, 0x00);

    //Cruise Control (main)
    opSend(0x228, cruisGran, cruisTune, cruisCtrl, 0x80, 0x00, 0x00, 0x00, 0x00);
    //byte1 0-99 (speed)
    //byte2 0-255 (fine)
    //byte3 0x80=limit(84 on 80 off) 0x40=cruise (48 on 40 off)
    //byte4 00 disabled 80 activated

    //Cruise Control (secondary, wont work without this)
    opSend(0x1A8, 0x00, 0x00, 0x00, 0x00, 0x00, gpsGran, gpsMid, gpsLast);
    //byte678 right odometre

    //Navi stuff
    opSend(0x169, 22, 0x00, 0x00, 0x00, 0x00, 7, 0x00, 0x6f); 
    //byte 7= how much meters
    //8= compass S, 23 final, 22 my position
    //127= calculating route
    //128= autobahn
    //129= sum turn left but not really, 130 same but right
    //131= very hairpin to left, 132 same but to right
    //133= wtf some circle, definetly not a boob
    //134= this time turn left, 135= turn right
    //136-151= car position
    //152= you have destination in front
    //153= you arrived

    //Economy mode
    opSend(0x236, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //19= economy mode

    //Maintenance km
    opSend(0x3e7, 0x10, 0x00, 0x00, 0x03, 0x63, 0x01, 0x31, 0x05);

    //Informational message
    opSend(0x1a1, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);

  }

  // Called once between each byte read on arduino, do not add any code here, unless you know what you are doing.
  void idle() {}
};
#endif
