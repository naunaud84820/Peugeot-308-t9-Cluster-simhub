# Peugeot-308-t9-Cluster-simhub
Sketch pour utiliser un compteur de peugeot 308 t9 sur simhub. (peut etre compatible avec d'autres compteurs PSA peugeot/citroen/opel)


# Francais
### Fonctions
* Vitesse ✅
* Tr/min ✅
* Carburant ✅
* Niveaux carburant faible ✅
* T° Eau ✅
* Voyant T° Eau excessive ✅
* Clignotant ✅
* Feux position/croisement ✅
* Feux de route ✅
* Voyant ABS ✅
* Voyant Batterie (contact mis+0rpm)✅
* Limiteur/Régulateur de vitesse 🟧Actif sur ets2/ats mais il me manque des cancodes pour qu'ils soit correctement fonctionnels
* Extinction Voyant STOP & (!) 🟥Cancode non trouves

### Requis
* [Simhub](https://www.simhubdash.com/download-2/)
* [Arduino IDE](https://www.arduino.cc/en/software/)
* Arduino UNO
* [Can-bus shield v2.0](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/)
* Fils jumpers
* Alim 12v (j'ai utiliser une vielle alim ATX)

### Tutoriel
En cours  

![simhubcfg](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/simhubcfg.png)

```
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
isnull([GameRawData.TruckValues.CurrentValues.DashboardValues.CruiseControlSpeed.Kph],'0') + ';'
```

Beosin d'aide? Rejoins ce discord: https://discord.gg/t5xhpxeHpS

### Remerciement
Albert.c pour l'aide avec les CanCodes
xConnect pour les infos simhub
[Neuros](https://discord.gg/t5xhpxeHpS) pour l'aide

### Partage & Autorisation
Vous pouvez partager ce github partout.  
**INTERDIT** d'heberger mon travail sans mon autorisation.  
Vous pouvez modifier ce code comme bon vous semble, si vous le modifiez, je vous demande juste de m'inclure dans les credits.

# English (google translate)
Working
