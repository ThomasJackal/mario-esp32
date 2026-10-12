#pragma once

// Entrées du joueur pour une frame (découplé du clavier/manette).
struct PlayerInput {
    bool left  = false;
    bool right = false;
    bool jumpPressed = false;  // front montant (vient d'être pressé)
    bool jumpHeld    = false;  // maintenu
    bool sprint      = false;  // course (Shift maintenu)
};

// Simule la physique de plateformer du joueur.
// Volontairement indépendant du moteur (pas de Renderer, pas de clavier) :
// on lui passe la position, les dimensions et les bornes du monde, il met
// tout à jour. Facile à régler et à tester isolément.
class PlayerPhysicsManager {
public:
    // --- État physique (exposé pour debug / animation) ---
    float vx = 0.0f;        // vitesse horizontale (px/s)
    float vy = 0.0f;        // vitesse verticale   (px/s, positif = bas)
    bool  onGround = false;

    // Remet l'état à zéro.
    void reset();

    // Fait avancer la simulation d'un pas.
    //   x, y     : coin haut-gauche, modifiés sur place
    //   w, h     : dimensions de l'entité
    //   worldW/H : bornes de la zone jouable
    //   in       : entrées du joueur pour cette frame
    //   deltaMs  : durée de la frame (millisecondes)
    void step(float& x, float& y, int w, int h,
              int worldW, int worldH,
              const PlayerInput& in, unsigned long deltaMs);

private:
    // --- Aides au "game feel" (millisecondes) ---
    float coyoteTimer     = 0.0f;  // sauter juste après avoir quitté le sol
    float jumpBufferTimer = 0.0f;  // mémoriser un appui un peu en avance
    bool  prevJumpHeld    = false; // état du bouton à la frame précédente
};
