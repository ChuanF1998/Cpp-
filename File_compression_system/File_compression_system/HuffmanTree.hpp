#pragma once
#include <vector>
#include <queue>
using namespace std;

template<class T>
struct Haffman_node
{
	T _value;
	Haffman_node* _Lchild;
	Haffman_node* _Rchild;
	Haffman_node* _Parent;
	Haffman_node()
		:_Lchild(nullptr)
		, _Rchild(nullptr)
		, _Parent(nullptr)
	{}
};


struct character
{
	char _ch;
	int _count;
};

struct cmp
{
	bool operator () (const Haffman_node<character>* a, const Haffman_node<character>* b)
	{
		return a->_value._count > b->_value._count;
	}
};


template<class T>
class Haffman_Tree
{
public:
	Haffman_Tree()
		:_root(nullptr)
	{}

	//¹þ·òÂüÊ÷µÄ¹¹Ôì
	bool HaffmanBuilt(const vector<T>& array)
	{
		if (_root == nullptr) {
			priority_queue<Haffman_node<character>*, vector<Haffman_node<character>*>, cmp> min_heap;
			for (int i = 0; i < array.size(); ++i) {
				Haffman_node<character>* p = new Haffman_node<character>;
				p->_value = array[i];
				min_heap.push(p);
			}
			while (min_heap.size() > 1) {
				Haffman_node<character>* left = min_heap.top();
				min_heap.pop();
				Haffman_node<character>* right = min_heap.top();
				min_heap.pop();
				Haffman_node<character>* parent = new Haffman_node<character>;
				parent->_value._count = left->_value._count + right->_value._count;
				parent->_Lchild = left;
				parent->_Rchild = right;
				min_heap.push(parent);
			}
			_root = min_heap.top();
			return true;
		}
		return false;
	}
private:
	Haffman_node<T>* _root;
};