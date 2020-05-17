#pragma once

template <class T>
class Element {
public:
	T key;
	Element() :key() {}
	Element(T key) :key(key) {}
};
