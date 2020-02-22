#pragma once

#include "Common.h"

class LZHashTable
{
public:
	LZHashTable(USH size);
	~LZHashTable();
	void Insert(USH& matchHead, UCH ch, USH pos, USH& hashAddr);
	void HashFunc(USH& hashAddr, UCH ch); //计算三个字符的hash值

private:
	
	USH H_SHIFT();
private:
	USH* _prev;
	USH* _head;
};