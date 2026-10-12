archi:
clavier -> serveur socket -> wiFi -> esp32 -> OLED

serveur:
Juste un serveur socket qui écoute le clavier et qui envoie les events à l'esp

étapes:
x- moteur (collision, entities, scene, renderer)
x- clavier
x- physique mario
- environnement static (entities on layer STATIC)
- caméra (follow player, don't render outside camera)
- map matrice
- enemies
- game over
- bitmaps
- environnement intératif

Documentation engine:
https://github.com/nbourre/ESP32-Game-Engine

Documentation mario:
https://web.archive.org/web/20130807122227/http://i276.photobucket.com/albums/kk21/jdaster64/smb_playerphysics.png
https://nesmaps.com/maps/SuperMarioBrothers/SuperMarioBrosMap1-1.png
