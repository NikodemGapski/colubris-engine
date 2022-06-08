# Colliders

## General overview

Colliders are components, so none can exist on their own.
In order to assign a collider as a gameobject component you must
pass the gameobject's pointer to the collider's constructor.
The collider will then have a global transform of its parent
and a local transform of its own.

Colliders' default constructors register them to the scene.