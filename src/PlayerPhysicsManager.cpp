#include "PlayerPhysicsManager.h"

// ---------------------------------------------------------------------------
//  Constantes de physique (réglables).
//  Unités : pixels et secondes. La zone jouable fait ~128 x 46, donc les
//  valeurs sont volontairement petites pour rester lisibles à l'écran.
// ---------------------------------------------------------------------------

// Déplacement horizontal
#define MOVE_SPEED       55.0f   // vitesse horizontale max (px/s)
#define GROUND_ACCEL     420.0f  // accélération au sol
#define GROUND_FRICTION  600.0f  // freinage au sol quand aucune touche pressée
#define AIR_ACCEL        260.0f  // accélération en l'air (contrôle réduit)
#define AIR_FRICTION     120.0f  // freinage en l'air

// Saut / gravité
#define GRAVITY          360.0f  // gravité quand on monte
#define FALL_GRAVITY     520.0f  // gravité plus forte en chute -> saut plus "pêchu"
#define JUMP_VELOCITY    125.0f  // impulsion de saut (px/s vers le haut)
#define JUMP_CUT         0.45f   // coupe la vitesse si on relâche tôt (saut variable)
#define MAX_FALL_SPEED   260.0f  // vitesse de chute max (anti tunneling)

// Confort de jeu
#define COYOTE_TIME      90.0f   // ms : sauter encore un peu après le bord
#define JUMP_BUFFER      100.0f  // ms : un appui en avance est mémorisé

// ---------------------------------------------------------------------------

void PlayerPhysicsManager::reset() {
    vx = 0.0f;
    vy = 0.0f;
    onGround = false;
    coyoteTimer = 0.0f;
    jumpBufferTimer = 0.0f;
    prevJumpHeld = false;
}

void PlayerPhysicsManager::step(float& x, float& y, int w, int h,
                                int worldW, int worldH,
                                const PlayerInput& in, unsigned long deltaMs) {
    float dt = deltaMs / 1000.0f;
    if (dt <= 0.0f) return;

    // --- Mouvement horizontal : accélération + friction ------------------
    float accel    = onGround ? GROUND_ACCEL    : AIR_ACCEL;
    float friction = onGround ? GROUND_FRICTION : AIR_FRICTION;

    float dir = (in.right ? 1.0f : 0.0f) - (in.left ? 1.0f : 0.0f);
    if (dir != 0.0f) {
        vx += dir * accel * dt;
        if (vx >  MOVE_SPEED) vx =  MOVE_SPEED;
        if (vx < -MOVE_SPEED) vx = -MOVE_SPEED;
    } else {
        // On ralentit vers 0 sans dépasser.
        if (vx > 0.0f)      { vx -= friction * dt; if (vx < 0.0f) vx = 0.0f; }
        else if (vx < 0.0f) { vx += friction * dt; if (vx > 0.0f) vx = 0.0f; }
    }

    // --- Timers de confort ------------------------------------------------
    if (onGround) coyoteTimer = COYOTE_TIME;
    else if (coyoteTimer > 0.0f) coyoteTimer -= (float)deltaMs;

    if (in.jumpPressed) jumpBufferTimer = JUMP_BUFFER;
    else if (jumpBufferTimer > 0.0f) jumpBufferTimer -= (float)deltaMs;

    // --- Déclenchement du saut -------------------------------------------
    if (jumpBufferTimer > 0.0f && coyoteTimer > 0.0f) {
        vy = -JUMP_VELOCITY;
        onGround = false;
        coyoteTimer = 0.0f;
        jumpBufferTimer = 0.0f;
    }

    // --- Saut à hauteur variable : couper si on relâche en montant -------
    if (!in.jumpHeld && prevJumpHeld && vy < 0.0f) {
        vy *= JUMP_CUT;
    }
    prevJumpHeld = in.jumpHeld;

    // --- Gravité ----------------------------------------------------------
    float g = (vy > 0.0f) ? FALL_GRAVITY : GRAVITY;
    vy += g * dt;
    if (vy > MAX_FALL_SPEED) vy = MAX_FALL_SPEED;

    // --- Intégration de la position --------------------------------------
    x += vx * dt;
    y += vy * dt;

    // --- Collisions avec les bords du monde ------------------------------
    if (x < 0.0f)           { x = 0.0f;         vx = 0.0f; }
    if (x + w > worldW)     { x = worldW - w;   vx = 0.0f; }

    // Plafond
    if (y < 0.0f) { y = 0.0f; if (vy < 0.0f) vy = 0.0f; }

    // Sol = bas de la zone jouable (pas encore de plateformes).
    float floorY = (float)(worldH - h);
    if (y >= floorY) {
        y = floorY;
        vy = 0.0f;
        onGround = true;
    } else {
        onGround = false;
    }
}
