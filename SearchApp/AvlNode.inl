#pragma once

template<class KeyType>
void AvlNode<KeyType>::treeprint(map<KeyType, pair<KeyType, KeyType>>& keys, int l, int& h, enum class Order order)
{
	if (this) {
		switch (order) {
		case Order::IN_ORDER:
			(this->LeftChild)->treeprint(keys, l + 1, h, order);
			h += 1;
#ifdef TREE_PRINT_TEST
			for (int i = 1; i <= l; i++) cout << "   ";
			cout << this->data.key << "(" << l << "," << h << ")" << "\n";
#endif
			keys.insert(make_pair<>(this->data.key, make_pair<>(l, h)));
			keys.at(this->data.key) = make_pair<>(l, h);
			(this->RightChild)->treeprint(keys, l + 1, h, order);
			break;
		case Order::PRE_ORDER:
			h += 1;
#ifdef TREE_PRINT_TEST
			for (int i = 1; i <= l; i++) cout << "   ";
			cout << this->data.key << "(" << l << "," << h << ")" << "\n";
#endif
			keys.insert(make_pair<>(this->data.key, make_pair<>(l, h)));
			keys.at(this->data.key) = make_pair<>(l, h);
			(this->LeftChild)->treeprint(keys, l + 1, h, order);
			(this->RightChild)->treeprint(keys, l + 1, h, order);
			break;
		}
	};
};

