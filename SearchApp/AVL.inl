#pragma once
// inline file은 반드시 C/C++ 헤더 파일로 설정해야 한다.

template<class KeyType>
void AVL<KeyType>::preOrder() {
	resultStream.str("");
	preOrder(this->root);
}

template<class KeyType>
void AVL<KeyType>::preOrder(AvlNode<KeyType>* head) {
	if (!head) return;
	cout << head->data.key << " ";
	resultStream << head->data.key << " ";
	preOrder(head->LeftChild);
	preOrder(head->RightChild);
}

template<class KeyType>
void AVL<KeyType>::inOrder() {
	resultStream.str("");
	inOrder(this->root);
	cout << endl;
}

template<class KeyType>
void AVL<KeyType>::inOrder(AvlNode<KeyType>* head) {
	if (!head) return;
	inOrder(head->LeftChild);
	cout << head->data.key << " ";
	resultStream << head->data.key << " ";
	inOrder(head->RightChild);
}

template<class KeyType>
void AVL<KeyType>::ListOrder() {
	resultStream.str("");
	ListOrder(this->root);
}

template<class KeyType>
void AVL<KeyType>::ListOrder(AvlNode<KeyType>* head) {
	if (!head) return;
	cout << head->data.key << ", ";
	resultStream << head->data.key << ", ";
	ListOrder(head->LeftChild);
	ListOrder(head->RightChild);
}

template <class KeyType>
bool AVL<KeyType>::Insert(const Element<KeyType>& x)
{
	AvlNode<KeyType>* a = 0, * b, * c, * pa, * p, * pp, * y, * clchild, * crchild;
	bool Found, Unbalanced;
	int d;
	if (!root) {
		y = new AvlNode<KeyType>;
		y->data = x;
		root = y;
		root->bf = 0;
		root->LeftChild = root->RightChild = 0;
		return true;
	}
	//phase 1: locate insertion point for x
	//a keeps track of the most recent node with balance factor +-1
	//pa is the parent of a
	//p moves through the tree
	//pp parent of p
	pa = 0;
	a = p = root;
	pp = 0;
	Found = false;
	while (p && !Found) { //search for insertion point for x
		if (p->bf) { a = p; pa = pp; }
		if (x.key < p->data.key) { pp = p; p = p->LeftChild; }
		else if (x.key > p->data.key) { pp = p; p = p->RightChild; }
		else { Found = true; }// x already in tree
	}
	if (!Found) {
		//phase 2: insert and rebalance
		// K is not in the tree and may be inserted as the appropriated child of pp
		y = new AvlNode<KeyType>;
		y->data = x;
		y->LeftChild = y->RightChild = 0;
		y->bf = 0;
		if (x.key < pp->data.key) pp->LeftChild = y;//insert as left child
		else pp->RightChild = y;//insert as right child
		// adjust balance factors
		if (x.key > a->data.key) {
			p = a->RightChild; b = p; d = -1;
		}
		else {
			p = a->LeftChild; b = p; d = 1;
		}
		while (p != y)
			if (x.key > p->data.key) {
				p->bf = -1;
				p = p->RightChild;
			}
			else {
				p->bf = 1;
				p = p->LeftChild;
			}
		Unbalanced = true;
		if (!(a->bf) || !(a->bf + d)) {
			a->bf += d; Unbalanced = false;
		}
		if (Unbalanced) {
			if (d == 1) {
				if (b->bf == 1) { //rotation type LL
					a->LeftChild = b->RightChild;
					b->RightChild = a; a->bf = 0; b->bf = 0;
				}
				else { //rotation type LR
					c = b->RightChild;
					b->RightChild = c->LeftChild;
					a->LeftChild = c->RightChild;
					c->LeftChild = b;
					c->RightChild = a;
					switch (c->bf) {
					case 1: //LR(b)
						a->bf = -1; b->bf = 0;
						break;
					case -1://LR(c)
						b->bf = 1; a->bf = 0;
						break;
					case 0: //LR(a)
						b->bf = 0; a->bf = 0;
						break;
					}
					c->bf = 0; b = c;
				} //end of LR
			} //end of left imbalance
			else {
				if (b->bf == -1) {//rotation type RR
					a->RightChild = b->LeftChild;
					b->LeftChild = a;
					a->bf = 0;
					b->bf = 0;
				}
				else {//rotation type RL
					c = b->LeftChild;
					b->LeftChild = c->RightChild;
					a->RightChild = c->LeftChild;
					c->RightChild = b;
					c->LeftChild = a;
					switch (c->bf) {
					case 1: //LR(b)
						a->bf = 1; b->bf = 0;
						break;
					case -1://LR(c)
						b->bf = -1; a->bf = 0;
						break;
					case 0: //LR(a)
						b->bf = 0; a->bf = 0;
						break;
					}
					c->bf = 0; b = c;
				}
			}
			//subtree with root b has been rebalanced
			if (!pa) root = b;
			else if (a == pa->LeftChild) pa->LeftChild = b;
			else if (a == pa->RightChild) pa->RightChild = b;
		}
		return true;
	}
	return false;
}

template <class KeyType>
int AVL<KeyType>::height(AvlNode<KeyType>* tree, int _height)
{
	int leftHeight = 0, rightHeight = 0;
	if (tree) {
		leftHeight = tree->LeftChild != NULL ? height(tree->LeftChild, _height) : 0;
		rightHeight = tree->RightChild != NULL ? height(tree->RightChild, _height) : 0;
		return 1 + max(leftHeight, rightHeight);
	}
	return _height;
}

template <class KeyType>
int AVL<KeyType>::height(AvlNode<KeyType>* tree)
{
	int _height = 0;
		if (tree != NULL) {
			_height = height(tree, 0);
			return _height;
		}
	return 0;
}

template <class KeyType>
int AVL<KeyType>::height() {
	return height(root);
}

template <class KeyType>
int AVL<KeyType>::max(int a, int b)
{
	return (int)(a > b ? a : b);
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::search(AvlNode<KeyType>* x, KeyType key) const
{
	if (x == NULL || x->data.key == key)
		return x;
	if (key < x->data.key)
		return search(x->LeftChild, key);
	else
		return search(x->RightChild, key);
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::search(KeyType key) {
	return search(root, key);
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::minimum(AvlNode<KeyType>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->LeftChild != NULL)
		tree = tree->LeftChild;
	return tree;
}

template <class KeyType>
KeyType AVL<KeyType>::minimum()
{
	AvlNode<KeyType>* p = minimum(root);
	if (p != NULL)
		return p->data;
	return (KeyType)NULL;
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::maximum(AvlNode<KeyType>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->RightChild != NULL)
		tree = tree->RightChild;
	return tree;
}

template <class KeyType>
KeyType AVL<KeyType>::maximum()
{
	AvlNode<KeyType>* p = maximum(root);
	if (p != NULL)
		return p->data;
	return (KeyType)NULL;
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::leftLeftRotation(AvlNode<KeyType>* k2)
{
	AvlNode<KeyType>* k1;
	k1 = k2->LeftChild;
	k2->LeftChild = k1->RightChild;
	k1->RightChild = k2;
	k2->bf = max(height(k2->LeftChild), height(k2->RightChild)) + 1;
	k1->bf = max(height(k1->LeftChild), k2->bf) + 1;
	return k1;
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::rightRightRotation(AvlNode<KeyType>* k1)
{
	AvlNode<KeyType>* k2;
	k2 = k1->RightChild;
	k1->RightChild = k2->LeftChild;
	k2->LeftChild = k1;
	k1->bf = max(height(k1->LeftChild), height(k1->RightChild)) + 1;
	k2->bf = max(height(k2->RightChild), k1->bf) + 1;
	return k2;
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::leftRightRotation(AvlNode<KeyType>* k3)
{
	k3->LeftChild = rightRightRotation(k3->LeftChild);
	return leftLeftRotation(k3);
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::rightLeftRotation(AvlNode<KeyType>* k1)
{
	k1->RightChild = leftLeftRotation(k1->RightChild);
	return rightRightRotation(k1);
}

template <class KeyType>
AvlNode<KeyType>* AVL<KeyType>::Delete(AvlNode<KeyType>*& tree, AvlNode<KeyType>* z)
{
	if (tree == NULL || z == NULL)
		return NULL;
	if (z->data.key < tree->data.key)
	{
		tree->LeftChild = Delete(tree->LeftChild, z);
		if (abs(height(tree->RightChild) - height(tree->LeftChild)) >= 2)
		{
			AvlNode<KeyType>* r = tree->RightChild;
			if (height(r->LeftChild) > height(r->RightChild))
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}
	else if (z->data.key > tree->data.key)
	{
		tree->RightChild = Delete(tree->RightChild, z);
		if (abs(height(tree->LeftChild) - height(tree->RightChild)) >= 2)
		{
			AvlNode<KeyType>* l = tree->LeftChild;
			if (height(l->RightChild) > height(l->LeftChild))
				tree = leftRightRotation(tree);
			else
				tree = leftLeftRotation(tree);
		}
	}
	else
	{
		if ((tree->LeftChild != NULL) && (tree->RightChild != NULL))
		{
			if (height(tree->LeftChild) > height(tree->RightChild))
			{
				AvlNode<KeyType>* max = maximum(tree->LeftChild);
				tree->data.key = max->data.key;
				tree->LeftChild = Delete(tree->LeftChild, max);
			}
			else
			{
				AvlNode<KeyType>* min = minimum(tree->RightChild);
				tree->data.key = min->data.key;
				tree->RightChild = Delete(tree->RightChild, min);
			}
		}
		else
		{
			AvlNode<KeyType>* tmp = tree;
			tree = (tree->LeftChild != NULL) ? tree->LeftChild : tree->RightChild;
			delete tmp;
		}
	}
	return tree;
}

template <class KeyType>
void AVL<KeyType>::Delete(KeyType key)
{
	AvlNode<KeyType>* z;
	if ((z = search(root, key)) != NULL)
		root = Delete(root, z);
}

template <class KeyType>
void AVL<KeyType>::destroy(AvlNode<KeyType>*& tree)
{
	if (tree == NULL)
		return;
	if (tree->LeftChild != NULL)
		destroy(tree->LeftChild);
	if (tree->RightChild != NULL)
		destroy(tree->RightChild);
	delete tree;
}

template <class KeyType>
void AVL<KeyType>::destroy()
{
	destroy(root);
}

template <class KeyType>
void AVL<KeyType>::print(AvlNode<KeyType>* tree, KeyType key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)
			cout << setw(2) << tree->data << " is root" << endl;
		else
			cout << setw(2) << tree->data << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;
		print(tree->LeftChild, tree->data, -1);
		print(tree->RightChild, tree->data, 1);
	}
}

template <class KeyType>
void AVL<KeyType>::print()
{
	if (root != NULL)
		print(root, root->data->key, 0);
}