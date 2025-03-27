# Peugeot-308-t9-Cluster-simhub
Sketch pour utiliser un compteur de peugeot 308 t9 sur simhub. (peut etre compatible avec d'autres compteurs PSA peugeot/citroen/opel)


#### Francais:
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
* Limiteur/Régulateur de vitesse 🟧Actif sur ets2/ats mais il me manque des cancodes pour qu'ils soit correctement fonctionnels
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
isnull([GameRawData.TruckValues.CurrentValues.DashboardValues.CruiseControlSpeed.Kph],'0') + ';'
```
comme ça:  
![simhubcode](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub/blob/main/img/simhubcode.png)

18. Maintenant connecte les fils sur ton compteur comme indiqué dans la section [Pinout]([https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/](https://github.com/naunaud84820/Peugeot-308-t9-Cluster-simhub?tab=readme-ov-file#pinout))  
19. Si tout est bon, tu devrais voirs ton compteur réagir. Si il reçois bien le signal CanBus, celui-ci est complètement eteint.  
20. Si il est allumé avec des voyants partout, il y à un problème! RDV sur ce [Discord](https://discord.gg/t5xhpxeHpS)  
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
Working
