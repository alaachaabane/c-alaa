# REAL DRIVE — La route des Crêtes

Prototype de conduite en 3D WebGL, dans un seul fichier HTML et sans dépendance externe. Il comprend une route côtière sinueuse, un relief stylisé, un coupé aux roues et vitrages détaillés, du trafic, trois caméras, trois ambiances lumineuses, la pluie, une mini-carte, des collisions et un son moteur synthétisé. L’accélération et le freinage ont été réglés pour une montée en vitesse et une décélération plus progressives.

## Lancer le jeu

Ouvrir `index.html` dans un navigateur récent avec WebGL activé. Le jeu ne nécessite ni installation ni connexion réseau.

## Commandes

- **Z / W / ↑** : accélérer (AZERTY, QWERTY ou flèche)
- **S / ↓** : freiner
- **Q / A / D / ← →** : diriger (AZERTY et QWERTY)
- **Espace** : frein à main
- **C** : changer de caméra
- **N** : changer l’ambiance lumineuse
- **M** : activer ou désactiver la pluie
- **R** : revenir sur la route
- **Échap** : pause

Après avoir pris le volant, les boutons à l’écran permettent aussi d’accélérer, freiner et diriger en maintenant la pression.

Le jeu utilise un vrai rendu 3D WebGL. Si WebGL est désactivé ou indisponible, un message l'explique au lieu de basculer vers un jeu en 2D. La direction artistique est stylisée et légère : ce prototype n'a pas encore le rendu photoréaliste d'un jeu AAA.
