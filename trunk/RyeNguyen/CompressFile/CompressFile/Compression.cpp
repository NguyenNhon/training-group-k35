#include "Compression.h"

#include <stdio.h>

//Run-Length Encoding algorithm
void RLE_Compression ()
{
	////////////////////////////////////////////////////
	//Open source file and read all content to buffer
	FILE *f = fopen ("source.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, 1, f);
	buff[size] = NULL;

	fclose (f);
	////////////////////////////////////////////////////

	char *p = buff;
	char *des = new char[size * 1000];
	int des_length = 0;


	while (p[0] != NULL)
	{
		char character = p[0];
		int count = 1;
		p++;

		//Count characters same with p[0]
		while (p != NULL && *p == character)
		{
			count++;
			p++;
		}

		//Write to buffer
		sprintf (des + des_length, "%c%c", count, character);
		des_length += 2;
	}

	////////////////////////////////////////////////////
	//Write from buffer to encode file
	f = fopen ("encode.rye", "wb");

	fwrite (des, 1, des_length, f);

	fclose (f);
	////////////////////////////////////////////////////
}

//Huffman algorithm
void Huffman_Compression ()
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