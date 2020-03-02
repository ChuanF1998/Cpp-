#include "LZHashTable.h"
#include <string.h>

const USH HASH_BITS = 15;
const USH HASH_SIZE = 1 << (HASH_BITS);
const USH HASH_MASK = HASH_SIZE - 1;

LZHashTable::LZHashTable(USH size)
:_prev(new USH[size * 2])
, _head(_prev + size)
{
	memset(_prev, 0, size * 2 * sizeof(USH));
}

LZHashTable::~LZHashTable()
{
	delete[] _prev;
	_prev = nullptr;
}

//���������ַ���hashֵ
//HashAddr��ǰһ�μ����hash��ַ
//ch������ƥ�������ַ������һ���ַ�
void LZHashTable::HashFunc(USH& hashAddr, UCH ch)
{
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK;
}
USH LZHashTable::H_SHIFT()
{
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}

void LZHashTable::Insert(USH& macthHead, UCH ch, USH pos, USH& hashAddr)
{
	HashFunc(hashAddr, ch);

	//�ҵ�ǰ�����ַ��ڲ��һ������������һ������ƥ������ͷ
	macthHead = _head[hashAddr];
	
	//pos���ܻᳬ��32768,���������ֹԽ��
	_prev[pos & HASH_MASK] = _head[hashAddr];
	_head[hashAddr] = pos;
}

USH LZHashTable::GetNext(USH matchHead)
{
	return _prev[matchHead & HASH_MASK];
}

void LZHashTable::Update()
{
	for (USH i = 0; i < WSIZE; ++i) {
		//�ȸ���head
		if (_head[i] >= WSIZE) {
			_head[i] -= WSIZE;
		}
		else {
			_head[i] = 0;
		}

		//����prev
		if (_prev[i] >= WSIZE) {
			_prev[i] -= WSIZE;
		}
		else {
			_prev[i] = 0;
		}
	}
	

}
