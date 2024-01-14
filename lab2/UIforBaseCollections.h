#pragma once

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Deque.h"

#include <limits>

template<typename T>
DynamicArray<T>* ObjectCreatingDynamicArray();

template<typename T>
LinkedList<T>* ObjectCreatingLinkedList();

template<typename T>
Deque<T>* ObjectCreatingDeque();

template<typename T>
void ObjectDeletion(T object);

template<typename T>
void UIBase();

void UIforBaseCollections();