#include "HuffmanTree.hpp"



int main()
{
	Haffman_Tree<character> t;
	vector<character> arr{ {'A',6}, {'B',8}, {'C',3}, {'D',4} };
	t.HaffmanBuilt(arr);
	return 0;
}