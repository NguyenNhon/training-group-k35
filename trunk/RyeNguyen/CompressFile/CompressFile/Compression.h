#ifndef __COMPRESSION_H__
#define __COMPRESSION_H__

typedef struct Node
{
	char m_name;
	int m_quantity;
	char m_sign;
};

void RLE_Compression ();

void Huffman_Compression ();
void SortList (Node list[], int count);

#endif