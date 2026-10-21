# REAL DRIVE — prototype Unreal Engine 5

Projet C++ original pour Unreal Engine 5.4. Le moteur Unreal n’est pas installé sur la machine de création : ce projet source n’a donc pas pu être compilé ou lancé ici. Il est fourni comme point de départ à ouvrir dans Unreal, pas comme un exécutable AAA validé.

## Prototype prévu

- Un coupé pilotable avec un châssis physique, quatre suspensions simulées indépendamment, effort moteur arrière, freinage, grip latéral et traînée aérodynamique.
- Caméra poursuite avec amortissement et vue cockpit basculable avec **C**.
- Route côtière sinueuse procédurale avec collision.
- Commandes AZERTY/QWERTY : **Z/W/↑** accélérer, **S/↓** freiner, **Q/A/D/←/→** diriger, **C** caméra, **R** réinitialiser.

## Ouvrir

Ouvrir `RealDrive.uproject` dans Unreal Engine 5.4, laisser le projet générer ses fichiers IDE, compiler le module `RealDrive`, puis lancer en mode Play. Le GameMode génère la route et place la voiture au démarrage.

## Portée actuelle

Ce dépôt est un prototype de conduite jouable en C++, pas un jeu AAA terminé. La route et les primitives de voiture sont générées à l’exécution ; les modèles détaillés, matériaux PBR, sons enregistrés, circulation, météo, courses, garage et progression restent à produire. Le moteur Unreal et ses dépendances doivent être présents pour compiler et vérifier le projet.
