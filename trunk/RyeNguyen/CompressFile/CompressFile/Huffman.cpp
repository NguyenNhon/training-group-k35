#include "Huffman.h"

#include <stdio.h>

//Huffman algorithm
void HuffmanCompression ()
{
	FILE *f = fopen ("source.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, 1, f);

	fclose (f);

	int count_character = CountCharacter (buff, size);
	HuffNode *node_list = CreateNode(buff, size, count_character);

	HuffTree tree = CreateTree (node_list, count_character);

	int a = 0;
}

int CountCharacter (char* p, int size)
{
	int count = 0;
	int character_table[256] = {0};
	for (int i = 0; i < size; i++)
	{
		if (character_table[*(p + i)] == 0)
		{
			character_table[*(p + i)] = 1;
			count++;
		}
	}

	return count;
}

HuffNode* CreateNode (char* p, int size, int list_size)
{
	HuffNode *node_list = new HuffNode[list_size];
	for (int i = 0; i < list_size; i++)
	{
		node_list[i].m_name = NULL;
		node_list[i].m_quantity = 0;
		node_list[i].pLeft = NULL;
		node_list[i].pRight = NULL;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < list_size; j++)
		{
			if (node_list[j].m_name == NULL)
			{
				node_list[j].m_name = *(p + i);
				node_list[j].m_quantity++;
				break;
			}
			else if (node_list[j].m_name == *(p + i))
			{
				node_list[j].m_quantity++;
				break;
			}
		}
	}

	return node_list;
}

void SortList (HuffNode *&list, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int max = i;
		for (int j = i + 1; j < size; j++)
		{
			if (list[j].m_quantity > list[max].m_quantity)
			{
				max = j;
			}
		}

		HuffNode temp = list[i];
		list[i] = list[max];
		list[max] = temp;
	}
}

HuffTree CreateTree (HuffNode *list, int size)
{
	HuffNode *p = new HuffNode;
	SortList (list, size);

	while (size > 1)
	{
		HuffNode *pLeft = new HuffNode;
		pLeft->m_name = list[size - 2].m_name;
		pLeft->m_quantity = list[size - 2].m_quantity;
		pLeft->pLeft = list[size - 2].pLeft;
		pLeft->pRight = list[size - 2].pRight;

		HuffNode *pRight = new HuffNode;
		pRight->m_name = list[size - 1].m_name;
		pRight->m_quantity = list[size - 1].m_quantity;
		pRight->pLeft = list[size - 1].pLeft;
		pRight->pRight = list[size - 1].pRight;

		p->m_name = NULL;
		p->m_quantity = pLeft->m_quantity + pRight->m_quantity;
		p->pLeft = pLeft;
		p->pRight = pRight;

		list[size - 2] = *p;
		size--;

		SortList (list, size);
	}

	return p;
}