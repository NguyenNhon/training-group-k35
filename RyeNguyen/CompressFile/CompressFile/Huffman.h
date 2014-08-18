#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

typedef struct Node
{
	char m_name;
	int m_quantity;
	char m_sign;
};

void Huffman_Compression ();
void SortList (Node list[], int count);
void Huffman_Decompression ();

#endif