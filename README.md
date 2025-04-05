# Peugeot-308-t9-Cluster-simhub
Sketch pour utiliser un compteur de peugeot 308 t9 sur simhub. (peut etre compatible avec d'autres compteurs PSA peugeot/citroen/opel)


#### Francais:
[English](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/tree/main?tab=readme-ov-file#english-google-translate)
## Disclaimer
Cette page est là pour vous aider à comprendre le fonctionnement du canbus sur simhub!  
Je ne suis pas résponsable de tout problèmes et/ou dommages sur votre materiel quel qu'il soit! 
Vous manipulez votre propre materiel à vos risques et périls!

## Fonctions
Les fonctions ont été testées dans ETS2/ATS et BeamNG, certaines fonctions peuvent ne pas fonctionner dans d'autres jeux!  
* Vitesse ✅
* Tr/min ✅
* Carburant ✅
* Niveaux carburant faible ✅
* T° Eau ✅
* Voyant T° Eau excessive ✅
* Rapports de vitesse R N 1-6 (7 et+ = D-) ✅
* Clignotant ✅
* Feux position/croisement ✅
* Feux de route ✅
* Voyant ABS ✅
* Voyant Batterie (contact mis+0rpm)✅
* Régulateur de vitesse 🟧Actif sur ets2/ats manque la vitesse
* Extinction Voyant STOP & (!) 🟥Cancode non trouves

## Requis
* [Simhub](https://www.simhubdash.com/download-2/)
* [Arduino IDE](https://www.arduino.cc/en/software/)
* Arduino UNO
* [Can-bus shield v2.0](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/)
* Fils jumpers
* Alim 12v (j'ai utiliser une vielle alim ATX)

## Pinout
pin 1 CanH  
Pin 2 CanL  
pin 7 12v  
pin 9 GND  
/!\ Les pins peuvent ne pas correspondre à ton compteur suivant le modèle de clui-ci, renseigne toi avant de faire les branchements, ou démonte le compteur et regarde ou vont les traces du circuit pour détérminés qui est quoi /!\

## Tutoriel
1. Télécharge et installe Arduino IDE  
2. Sur ton PC rend toi dans tes Documents puis Arduino.  
3. Si un dossier libraries est présent, renome le en librariesold, afin de ne pas le perdre au cas ou.  
4. Télécharge et décompresse le dossier libraries du libraries.rar et met le dans: Documents/arduino  
5. Télécharge le dossier psa_308_simhub et met le dans Documents/arduino.  
6. Ouvre le dossier psa_308_simhub puis double clique sur psa_308_simhub.ino  
7. Arduino IDE devrait s'ouvrir.  
8. Branche ton arduino à ton PC  
9. Selectionne en haut le port COM de ton arduino puis le modele d'arduino que tu a (Arduino UNO par exemple)  
10. en haut a droite clique sur la -> en haut à gauche pour envoyer le sketch sur ton arduino.
![ArduinoIDE1](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/ArduinoIDE1.png)
11. si tout ce passe bien tu devrais avoir ce message en bas pour te dire que tout s'est bien passé.  
![ArduinoIDEok](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/ArduinoIDEok.png)

12. Si tout est ok, lance SimHub!  
13. Clique sur "Arduino" à gauche puis sur "My Hardware" En haut.  
14. Selectionne "Signle arduino", SimHub devrais voirs automatiquement ton arduino et le connecté. (si il n'y arrive pas, ferme le logiciel Arduino IDE)  
15. Maintenant, règle les option de ton arduino comme sur ce screen.  
![simhubcfg](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/simhubcfg.png)

16. Clique sur le bouton "edit" à coté de "Custom protocol" puis sur "Computed value en haut de la fenetre qui s'ouvre.  
17. Copie et colle ce code dans la fenetre:
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
isnull([GameRawData.TruckValues.CurrentValues.DashboardValues.CruiseControlSpeed.Kph],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.Chassis],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.Engine],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.WheelsAvg],'0') + ';'
```
comme ça:  
![simhubcode](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/simhubcode.png)

18. Maintenant connecte les fils sur ton compteur comme indiqué dans la section [Pinout](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub?tab=readme-ov-file#pinout)  
19. Si tout est bon, tu devrais voirs ton compteur réagir. Si il reçois bien le signal CanBus, celui-ci est complètement eteint.  
20. Si il est allumé avec des voyants partout, il y à un problème! RDV sur ce [Discord](https://discord.gg/t5xhpxeHpS)  
![clustercannok](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/clustercannok.jpg) ![clustercanok](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/clustercanok.jpg)
21. Lance ton jeu et amuse toi!

Beosin d'aide? Rejoins ce discord: https://discord.gg/t5xhpxeHpS

## Remerciement
Albert.c pour l'aide avec les CanCodes  
[xConnect](https://xconnect.cc/) pour les infos simhub  
[Neuros](https://discord.gg/t5xhpxeHpS) pour l'aide  
[PSA Can](https://autowp.github.io/) pour les codes

## Partage & Autorisation
**INTERDIT** d'heberger mon travail ailleur sans mon autorisation.  
Vous pouvez modifier ce code comme bon vous semble, si vous le modifiez, je vous demande juste de m'inclure dans les credits.

#### English (google translate):
## Disclaimer
This page is here to help you understand how the CAN bus works with SimHub!
I am not responsible for any issues and/or damage to your hardware, whatever it may be!
You handle your own hardware at your own risk!

## Functions
The functions have been tested in ETS2/ATS and BeamNG, some functions may not work in other games!

* Speed ✅
* RPM ✅
* Fuel ✅
* Low fuel levels ✅
* Water temperature ✅
* Excessive water temperature warning ✅
* Gear shifts R N 1-6 (7 and+ = D-) ✅
* Turn signal ✅
* Position/low beam lights ✅
* High beam lights ✅
* ABS light ✅
* Battery light (ignition on + 0rpm) ✅
* Cruise control 🟧 Active in ETS2/ATS, speed is missing
* STOP & (!) light off 🟥 CAN code not found

## Requirements
* [Simhub](https://www.simhubdash.com/download-2/)
* [Arduino IDE](https://www.arduino.cc/en/software/)
* Arduino UNO
* [Can-bus shield v2.0](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/)
* Jumper wires
* 12V power supply (I used an old ATX power supply)

## Pinout
pin 1 CanH  
Pin 2 CanL  
pin 7 12v  
pin 9 GND  
/!\ The pins may not match your display depending on the model, check before making connections or open the display and look at the circuit traces to determine what is what /!\

## Tutorial
1. Download and install Arduino IDE  
2. On your PC, go to your Documents folder, then Arduino.  
3. If a libraries folder exists, rename it to librariesold, so you don’t lose it just in case.  
4. Download and extract the libraries folder from libraries.rar and place it in: Documents/arduino  
5. Download the psa_308_simhub folder and place it in Documents/arduino.  
6. Open the psa_308_simhub folder and double-click on psa_308_simhub.ino  
7. Arduino IDE should open.  
8. Plug your Arduino into your PC  
9. Select the COM port of your Arduino at the top, then the model of your Arduino (e.g., Arduino UNO)  
10. In the top-left corner, click on the arrow to upload the sketch to your Arduino.  
![ArduinoIDE1](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/ArduinoIDE1.png)
11. If everything goes well, you should see this message at the bottom, indicating that everything worked fine.  
![ArduinoIDEok](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/ArduinoIDEok.png)

12. If everything is fine, launch SimHub!  
13. Click on "Arduino" on the left, then "My Hardware" at the top.  
14. Select "Single Arduino", SimHub should automatically detect your Arduino and connect it. (If it fails, close the Arduino IDE software)  
15. Now, set up your Arduino options as shown in this screenshot.  
![simhubcfg](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/simhubcfg.png)

16. Click the "edit" button next to "Custom protocol" then click on "Computed value" at the top of the window that opens.  
17. Copy and paste this code into the window:
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
isnull([GameRawData.TruckValues.CurrentValues.DashboardValues.CruiseControlSpeed.Kph],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.Chassis],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.Engine],'0') + ';' +
isnull([GameRawData.TruckValues.CurrentValues.DamageValues.WheelsAvg],'0') + ';'
```
Like this:  
![simhubcode](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/simhubcode.png)

18. Now connect the wires to your display as shown in the [Pinout] section. [Pinout](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub?tab=readme-ov-file#pinout)  
19. If everything is correct, your display should react. If it receives the CAN bus signal properly, it will be completely off.  
20. If it is on with lights everywhere, there is an issue! Visit this [Discord](https://discord.gg/t5xhpxeHpS)  
![clustercannok](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/clustercannok.jpg) ![clustercanok](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/clustercanok.jpg)
21. Launch your game and have fun!

Need help? Join this Discord: https://discord.gg/t5xhpxeHpS

## Acknowledgements
Albert.c for the help with CAN codes  
[xConnect](https://xconnect.cc/) for SimHub information  
[Neuros](https://discord.gg/t5xhpxeHpS) for help  
[PSA Can](https://autowp.github.io/) for the codes

## Sharing & Permissions
FORBIDDEN to host my work elsewhere without my permission.
You can modify this code as you wish, but if you modify it, I just ask that you include me in the credits.

