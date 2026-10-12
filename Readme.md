archi:
clavier -> serveur socket -> wiFi -> esp32 -> engine -> OLED

serveur:
Juste un serveur socket qui écoute le clavier et qui envoie les events à l'esp

Features:
x- moteur (collision, entities, scene, renderer)
x- clavier
    - serveur socket
x- physique mario
    - marche
    - course
    - saut
        - gravité
        - conservation de la vélocité
- caméra (follow player, don't render outside camera)
- map matrice
- interactibles
    - enemies
        - goomba
        - tortue
    - bonus
        - mushroom
        - 1 up
    - pipe
    - breakable block
    - mystery block
    - unbreakable block
- environement
    - hill
    - bush
    - clouds
- game over
- bitmaps

Gestion des problèmes:


Lib:

Documentation engine:
https://github.com/nbourre/ESP32-Game-Engine

Documentation mario:
https://web.archive.org/web/20130807122227/http://i276.photobucket.com/albums/kk21/jdaster64/smb_playerphysics.png
https://nesmaps.com/maps/SuperMarioBrothers/SuperMarioBrosMap1-1.png
