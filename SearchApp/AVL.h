#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "Element.h"

#undef max

using namespace std;

enum class Order {
	IN_ORDER,
	PRE_ORDER,
};

/* AVL Node 클래스의 선언부 */
template <class KeyType> class AVL;
template <class KeyType>
class AvlNode {
	friend class AVL<KeyType>;
public:
	void treeprint(map<KeyType, pair<KeyType, KeyType>>& keys, int l, int& h, enum class Order order);
	AvlNode* getLeftChild(void) { return this->LeftChild; }
	AvlNode* getRightChild(void) { return this->RightChild; }
	KeyType getKey(void) { return this->data.key; }
private:
	Element<KeyType> data;
	AvlNode* LeftChild, * RightChild;
	int bf;
	int lsize;//number of nodes in left subtree plus one
};

/* AVL 클래스의 선언부 */
template <class KeyType>
class AVL {
public:
	stringstream resultStream;
	AVL(AvlNode<KeyType>* init = 0) : root(init) {};
	bool Insert(const Element<KeyType>&);
	void Delete(KeyType key);
	void ListOrder();//list the nodes of an AVL tree in ascending order of data.key
	int max(int a, int b);
	int height();
	AvlNode<KeyType>* search(KeyType data);
	KeyType minimum();
	KeyType maximum();
	void preOrder();
	void inOrder();
	void destroy();
	void print();
	void getTreePoints(std::map<KeyType, pair<KeyType, KeyType>>& keys, enum class Order order) { int h = 0; cout << "\n"; root->treeprint(keys, 1, h, order); }
private:
	AvlNode<KeyType>* root;
	void ListOrder(AvlNode<KeyType>* head);
	void preOrder(AvlNode<KeyType>* head);
	void inOrder(AvlNode<KeyType>* head);
	int height(AvlNode<KeyType>* tree);
	AvlNode<KeyType>* search(AvlNode<KeyType>* x, KeyType data) const;
	AvlNode<KeyType>* minimum(AvlNode<KeyType>* tree);
	AvlNode<KeyType>* maximum(AvlNode<KeyType>* tree);
	AvlNode<KeyType>* leftLeftRotation(AvlNode<KeyType>* k2);
	AvlNode<KeyType>* rightRightRotation(AvlNode<KeyType>* k1);
	AvlNode<KeyType>* leftRightRotation(AvlNode<KeyType>* k3);
	AvlNode<KeyType>* rightLeftRotation(AvlNode<KeyType>* k1);
	AvlNode<KeyType>* Delete(AvlNode<KeyType>*& tree, AvlNode<KeyType>* z);
	void destroy(AvlNode<KeyType>*& tree);
	void print(AvlNode<KeyType>* tree, KeyType key, int direction);
};

#include "AvlNode.inl"
#include "AVL.inl"
