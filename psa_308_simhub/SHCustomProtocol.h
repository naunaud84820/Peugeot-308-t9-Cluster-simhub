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
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.WheelsAvg],'0') + ';'
*/


#ifndef _SHCUSTOMPROTOCOL_H_
#define _SHCUSTOMPROTOCOL_H_
#include <Arduino.h>

String fuel, temp, gear, turnL, turnR, ignition, handbrake, scshandbrake, ABSS, TCS, showLights, shiftLight, lowBeams, highBeams, scslowBeams, scshighBeams, cruiseControl, cruiseControlspd, chassisdmgscs, enginedmgscs, wheeldmgscs;
int rpm, rpmGate, speed, spdGran, spdTune, parkBrake, turn, beams, ignit, gearex, fuelex, tempint, tempex, dwtemp, lowfuel, battery, warnLightd, shiftL, cruiseCtrl, chassisdmg, enginedmg, tyrepressure;
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
    spdGran = round(speed*100)/265;
    if(spdGran < 0) {
      spdGran = 0;
    }
    spdTune = round((speed*100)/265)+speed;
    if(spdTune < 0) {
      spdTune = 0;
    }
    fuel = FlowSerialReadStringUntil(';');
    fuelex = fuel.toInt();
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
    cruiseControl = FlowSerialReadStringUntil(';');
    if(cruiseControl == "True" ) {
      cruiseCtrl = 0x48;
    } else {
      cruiseCtrl = 0;
    }
    cruiseControlspd = FlowSerialReadStringUntil(';');
    chassisdmgscs = FlowSerialReadStringUntil(';');
    if(chassisdmg > "0.15") {
      parkBrake += 0x80;
    } else {
      parkBrake += 0x00;
    }
    enginedmgscs = FlowSerialReadStringUntil(';');
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
    opSend(0x0F6, ignit, tempex, 10, 13, 17, 0x8e, 0x00, 0x00);
    //byte2 coolant t° 90=60°(0) 135=85° 150=90° 160=100°(max)
    //byte345 odometre 10, 13, 17=65870 

    // Speedo and rpm
    opSend(0x0B6, rpmGate, 0xFF, spdGran, spdTune, 0x00, 0x00, 0x00, 0xD0);
    //byte1 rpm: 27=900rpm(ralentis) 220=7000rpm
    //byte3 speed: 100=254km/h 50=131km/h
    //map(Speed, 0, 250, 0, 1680)

    //Dash lights
    opSend(0x128, turn, gearex, 0x00, parkBrake, 0x00, lowfuel, shiftL, 0x00);
    //byte1 ABCDEFGH a=position beam  b=low beam  c=high beam  d=AB AV  e=AB AR  f=right turn  g=left turn  h=?
    //byte2 :0x00 P, 0x10 R, 0x20 N, 0x32 D1, 0x34 D2, 0x36 D3, 0x38 D4, 0x3a D5, 0x3c D6, 0x90 1, 0x80 2, 0x70 3, 0x60 4, 0x50 5, 0x40 6
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
    opSend(0x228, 0, 255, cruiseCtrl, 0x80, 0x00, 0x00, 0x00, 0x00);
    //byte1 0-99 (speed)
    //byte2 0-255 (fine)
    //byte3 0x80=limit(84 on 80 off) 0x40=cruise (48 on 40 off)
    //byte4 00 disabled 80 activated

    //Cruise Control (secondary, wont work without this)
    opSend(0x1A8, 0x00, 0x00, 0x00, 0x00, 0x00, 5, 5, 5);
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
    
  }

  // Called once between each byte read on arduino, do not add any code here, unless you know what you are doing.
  void idle() {}
};
#endif
