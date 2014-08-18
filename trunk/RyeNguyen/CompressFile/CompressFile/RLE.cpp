#include "RLE.h"

#include <stdio.h>

void RLE_Compression ()
{
	//Open source file and read all content to buffer
	FILE *f = fopen ("source.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, sizeof(char), f);

	fclose (f);
	////////////////////////////////////////////////////

	char *p = buff;
	int des_length = 0;
	int count_character = 0;

	while (p != buff + size)
	{
		char character = p[0];
		int count = 1;
		p++;

		while (*p == character)
		{
			p++;
		}

		count_character++;
		des_length += 2;
	}

	char *des = new char[des_length];
	int count_length = 0;

	p = buff;

	while (count_length < count_character * 2)
	{
		char character = *p;
		int count = 1;
		p++;

		//Count characters same with p[0]
		while (*p == character)
		{
			count++;
			p++;
		}

		des[count_length] = count;
		des[count_length + 1] = character;
		count_length += 2;
	}

	//Write from buffer to encode file
	f = fopen ("encode.rye", "wb");

	fwrite (des, sizeof(char), des_length, f);

	fclose (f);
	////////////////////////////////////////////////////
}

void RLE_Decompression ()
{
	//Open encode file and read all content to buffer
	FILE *f = fopen ("encode.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, sizeof(char), f);
	buff[size] = NULL;

	fclose (f);
	////////////////////////////////////////////////////

	char *p = buff;
	int des_length = 0;

	while (p != buff + size)
	{
		des_length += *p;
		p += 2;
	}

	char *des = new char[des_length];
	int char_position = 0;

	p = buff;

	while (p != buff + size)
	{
		for (int i = 0; i < *p; i++)
		{
			des[char_position++] = *(p + 1);
		}

		p += 2;
	}

	//Write from buffer to decode file
	f = fopen ("decode.rye", "wb");

	fwrite (des, sizeof(char), des_length, f);

	fclose (f);
	////////////////////////////////////////////////////
}