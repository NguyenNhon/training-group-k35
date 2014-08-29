#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

typedef struct HuffNode
{
	char m_name;
	int m_quantity;
	HuffNode *pLeft;
	HuffNode *pRight;
};

typedef HuffNode* HuffTree;

void HuffmanCompression ();
void HuffmanDecompression ();

int CountCharacter (char*, int);
HuffNode* CreateNode (char*, int, int);
void SortList (HuffNode *&, int);
HuffTree CreateTree (HuffNode*, int);

#endif