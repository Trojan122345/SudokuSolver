//
// Created by Troja on 09/04/2024.
//

#include "objects/Object.h"

int Object::NextID = 0;

Object::Object():ID(getNextID())
{
  mouseIn = false;
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

bool Object::compare(Object *object) const
{
  return this->ID == object->ID;
}
