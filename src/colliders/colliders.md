# Colliders

## General overview

Colliders are components, so none can exist on their own.
In order to assign a collider as a gameobject component you must
pass the gameobject's pointer to the collider's constructor.
The collider will then have a global transform of its parent
and a local transform of its own.

Colliders' default constructors register them to the scene.

## Circle collider

Local and global scaling for circle colliders might have unwanted
consequences if the scaling is applied unevenly among the axes.
The real radius formula is as follows:

```
real radius = radius * avg global scale * avg local scale
```

For the collider's real position we add the parent's position with the
collider's local position.