# REAL DRIVE — prototype de conduite

REAL DRIVE est une première tranche jouable de jeu de conduite pour ordinateur. Le prototype est autonome : il ne télécharge aucune bibliothèque et peut être ouvert directement en double-cliquant sur `index.html`.

## Ce qui est jouable

- Route côtière sinueuse à génération continue, reliefs, mer, falaises, arbres, rochers, glissières et panneaux.
- Voiture sportive originale dessinée avec carrosserie, vitrage, roues, feux et détails de cockpit.
- Accélération, freinage, transfert latéral, perte d'adhérence sous la pluie, frein à main et glisse.
- Circulation légère avec dépassements et contacts qui ralentissent la voiture.
- Caméra poursuite, capot et cockpit ; compteur, rapports, régime moteur, mini-carte et score de glisse.
- Son moteur synthétisé en temps réel, pluie activable et trois ambiances lumineuses.
- Menu d'accueil, commandes, pause et repositionnement sur la route.

## Lancer

Ouvre `index.html` dans Safari, Chrome ou Edge. Le jeu fonctionne depuis `file://` et ne nécessite ni installation, ni serveur, ni accès Internet.

## Commandes

| Touche | Action |
| --- | --- |
| W / ↑ | Accélérer |
| S / ↓ | Freiner |
| A / D / ← / → | Diriger |
| Espace | Frein à main et glisse |
| C | Changer de caméra |
| M | Activer ou couper la pluie |
| N | Changer l'ambiance lumineuse |
| R | Se repositionner sur la route |
| Échap | Pause |

## Portée et limites

Le rendu utilise une projection perspective 2.5D en Canvas 2D dessinée dans un seul fichier, afin de démarrer de façon fiable par double-clic. Ce n'est pas encore un environnement 3D WebGL ni une simulation automobile de niveau AAA. Le modèle de conduite reste arcade. Les voitures sous licence, la circulation dense, les courses et circuits, les réglages mécaniques, les dégâts, une vraie météo, les piétons, la progression et le mode photo ne sont pas encore implémentés.
