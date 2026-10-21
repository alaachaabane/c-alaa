# REAL DRIVE — prototype jouable

Un prototype de conduite 3D en monde ouvert, développé avec Three.js. Il propose une voiture contrôlable, une route côtière en boucle, un environnement généré dans la scène, des collisions, trois caméras et un HUD de conduite.

## Lancer le jeu

Le navigateur doit avoir accès à Internet pour charger Three.js depuis jsDelivr.

Depuis ce dossier, lance un serveur web local :

```sh
python3 -m http.server 8000
```

Puis ouvre [http://localhost:8000](http://localhost:8000).

## Commandes

| Touche | Action |
| --- | --- |
| W / ↑ | Accélérer |
| S / ↓ | Freiner ou reculer |
| A / D / ← / → | Diriger |
| Espace | Frein à main |
| C | Changer de caméra |
| R | Repositionner la voiture sur la route |
| Échap | Pause |

## Fonctionnalités implémentées

- Route côtière 3D en boucle, marquages, bas-côtés et glissières dans les virages en hauteur.
- Modèle de voiture construit en meshes Three.js, roues animées, carrosserie métallique et éclairage.
- Accélération, freinage, direction, inertie, frottement, perte d'adhérence hors route et frein à main.
- Détection de collision avec les éléments de décor et ralentissement à l'impact.
- Caméras poursuite, capot et cockpit, compteur km/h, rapport, jauge de régime et mini-carte.
- Menu de démarrage, pause, aide des commandes et remise sur la route.
- Terrain, reliefs lointains, mer, végétation, rochers, maisons, brouillard, ombres et lumière directionnelle.

## Limites actuelles

Ce prototype est une base jouable, pas un jeu AAA. Il utilise une seule voiture originale, un circuit d'exploration, une physique arcade cohérente et des modèles géométriques procéduraux. La circulation, les courses, les intérieurs détaillés, le son moteur, la météo dynamique, les dégâts, la progression et la personnalisation ne sont pas encore implémentés.
