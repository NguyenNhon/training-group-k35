#ifndef __COMPRESS_H__
#define __COMPRESS_H__

typedef struct Node
{
	char m_name;
	int m_quantity;
	char m_sign;
};

void Compressed1 ();
void SortList (Node list[], int count);

void Compressed2 ();

#endif