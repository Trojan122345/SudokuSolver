//
// Created by Troja on 09/04/2024.
//

#include "objects/Object.h"

int Object::NextID = 0;

Object::Object() : ID(getNextID()), locked(nullptr), didLock(false)
{
  mouseIn = false;
  mouseDown = false;
}

Object::~Object()
= default;

int Object::getNextID()
{
  return Object::NextID++;
}

int Object::getID() const
{
  return ID;
}

bool Object::compare(Object* object) const
{
  return this->ID == object->ID;
}

void Object::setLock(bool *lock)
{
  this->locked = lock;
}

void Object::update()
{
  if (locked != nullptr)
  {
    if (*locked && !didLock)
    {
      didLock = true;
      onLock();
    }
    else if(!*locked && didLock)
    {
      didLock = false;
      onUnLock();
    }
  }
}
