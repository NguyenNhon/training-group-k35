#include "Decompression.h"

#include <stdio.h>

//Run-Length Decoding algorithm
void RLE_Decompression ()
{
	////////////////////////////////////////////////////
	//Open encode file and read all content to buffer
	FILE *f = fopen ("encode.rye", "rb");

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
		for (int i = 0; i < p[0]; i++)
		{
			sprintf (des + des_length, "%c", p[1]);
			des_length++;
		}

		p += 2;
	}

	////////////////////////////////////////////////////
	//Write from buffer to decode file
	f = fopen ("decode.rye", "wb");

	fwrite (des, 1, des_length, f);

	fclose (f);
	////////////////////////////////////////////////////
}

void Huffman_Decompression ()
{

}