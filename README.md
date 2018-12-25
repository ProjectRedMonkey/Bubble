Petit projet personnel fortement inspiré du jeu du même nom sur Sega Master System II.
Le jeu utilise la librairie SDL 1.2 ainsi que SDL_Mixer.
Le CMake permet de compiler sous Windows.

![Screenshot](https://raw.githubusercontent.com/ProjectRedMonkey/Bubble/master/resources/images/screenshot.png)

On se déplacer avec q/d/space, et on tire avec f.
Notre dino possède 3 vies.

INFO SUPP :
Les sauts sont parfois buggés.
Pour l'instant on ne peut tirer qu'une bulle à la fois malgrès l'utilisation d'un tableau, donc c'est en cours.
Il n'y a pas encore de changement de map dans le cas de l'élimination de tous les ennemis.
J'ai utilisé la couleur du fond pour gérer les collisions donc attention à la couleur du fond en cas de création d'une autre map.
