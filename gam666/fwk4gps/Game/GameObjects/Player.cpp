#include "Player.h"
#include "..\World.h"
#include "..\PhysicsObject.h"

Player::Player(World* world) : GameObject(world) { 
  physics = new PhysicsObject(&world->physics, this);
};

void Player::update() {
  input.update(world, this);
  GameObject::update();
}