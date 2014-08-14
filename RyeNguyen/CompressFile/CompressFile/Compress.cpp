#include "Compress.h"

#include <stdio.h>
#include <string>

using namespace std;

//Run-Length Encoding algorithm
void Compressed2 ()
{
	FILE *f = fopen ("source.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, 1, f);

	fclose (f);

	char *p = buff;

	f = fopen ("source.rye", "wb");

	while (p != NULL)
	{
		char character = *p;
		int count = 1;
		p++;

		while (p[0] == character)
		{
			count++;
			p++;
		}

		if (count < 2)
		{
			
		}
		else
		{
			
		}
	}

	char *b = new char[10];
}

//Huffman algorithm
void Compressed1 ()
{
	FILE *f = fopen ("source.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, 1, f);

	fclose (f);

	Node character_list[256];
	for (int i = 0; i < 256; i++)
	{
		character_list[i].m_name = NULL;
		character_list[i].m_quantity = 0;
		character_list[i].m_sign = NULL;
	}

	int count_character = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= count_character + 1; j++)
		{
			if (*(buff + i) == character_list[j].m_name)
			{
				character_list[j].m_quantity++;
				break;
			}
			else if (character_list[j].m_name == NULL)
			{
				character_list[j].m_name = *(buff + i);
				character_list[j].m_quantity++;
				count_character++;
				break;
			}
		}
	}

	SortList (character_list, count_character);
	
	//UNDONE!!!
}

void SortList (Node list[], int count)
{
	int i, j, max;
	for (i = 0; i < count - 1; i++)
	{
		max = i;
		for (j = i + 1; j < count; j++)
		{
			if (list[j].m_quantity > list[max].m_quantity)
			{
				max = j;
			}
		}

		Node temp = list[i];
		list[i] = list[max];
		list[max] = temp;
	}

	return;
}