#pragma once
#include <vector>
#include <queue>
using namespace std;

template<class T>
struct Huffman_node
{
	T _value;
	Huffman_node* _Lchild;  //左孩子
	Huffman_node* _Rchild;  //右孩子
	Huffman_node* _Parent;  //双亲
	Huffman_node(const T& value = T())
		: _value(value)
		, _Lchild(nullptr)
		, _Rchild(nullptr)
		, _Parent(nullptr)
	{}
};

template<class T>
class Less //优先级队列比较方式重写
{
	typedef Huffman_node<T> node;
public:
	bool operator () (const node* a, const node* b)
	{
		return a->_value > b->_value;
	}
};


template<class T>
class Huffman_Tree
{
	typedef Huffman_node<T> node;
public:
	Huffman_Tree()
		: _root(nullptr)
	{}
	Huffman_Tree(const vector<T>& arr)
	{
		HuffmanBuilt(arr);
	}
	node* get()
	{
		return _root;
	}

	//哈夫曼树的构造
	bool HuffmanBuilt(const vector<T>& array)
	{
		if (_root == nullptr) {
			priority_queue<node*, vector<node*>, Less<T>> min_heap;
			for (size_t i = 0; i < array.size(); ++i) {
				if (array[i]._count == 0) {
					continue;
				}
				node* p = new node;
				p->_value = array[i];
				min_heap.push(p);
			}
			while (min_heap.size() > 1) {
				node* left = min_heap.top();
				min_heap.pop();
				node* right = min_heap.top();
				min_heap.pop();
				node* parent = new node;
				parent->_value = left->_value + right->_value;
				parent->_Lchild = left;
				parent->_Rchild = right;
				left->_Parent = parent;
				right->_Parent = parent;
				min_heap.push(parent);
			}
			_root = min_heap.top();
			return true;
		}
		return false;
	}

	~Huffman_Tree()
	{
		destroy(_root);
	}

private:
	Huffman_node<T>* _root;

	//销毁
	void destroy(node*& _root)
	{
		if (_root) {
			destroy(_root->_Lchild);
			destroy(_root->_Rchild);
			delete _root;
			_root = nullptr;
		}
	}
};