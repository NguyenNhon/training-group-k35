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

	int des_size = 0;

	char *p = buff;

	while (p != buff + size)
	{
		char character = *p;
		int count = 1;
		p++;

		while (*p == character)
		{
			p++;
		}

		des_size += 2;
	}

	char *des = new char[des_size];
	int des_current_size = 0;

	p = buff;

	while (des_current_size < des_size)
	{
		char character = *p;
		int count = 1;
		p++;

		while (*p == character)
		{
			count++;
			p++;
		}

		des[des_current_size] = count;
		des[des_current_size + 1] = character;
		des_current_size += 2;
	}

	//Write from buffer to encode file
	f = fopen ("encode.rye", "wb");

	fwrite (des, sizeof(char), des_size, f);

	fclose (f);
	////////////////////////////////////////////////////

	delete[] buff;
	buff = NULL;
	p = NULL;

	delete[] des;
	des = NULL;

	f = NULL;
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

	fclose (f);
	////////////////////////////////////////////////////

	int des_size = 0;

	char *p = buff;

	while (p != buff + size)
	{
		des_size += *p;
		p += 2;
	}

	char *des = new char[des_size];
	int des_current_size = 0;

	p = buff;

	while (p != buff + size)
	{
		for (int i = 0; i < *p; i++)
		{
			des[des_current_size++] = *(p + 1);
		}

		p += 2;
	}

	//Write from buffer to decode file
	f = fopen ("decode.rye", "wb");

	fwrite (des, sizeof(char), des_size, f);

	fclose (f);
	////////////////////////////////////////////////////

	delete[] buff;
	buff = NULL;
	p = NULL;

	delete[] des;
	des = NULL;

	f = NULL;
}