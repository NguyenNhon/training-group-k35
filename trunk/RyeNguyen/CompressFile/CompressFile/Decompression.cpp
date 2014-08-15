#include "Decompression.h"

#include <stdio.h>
#include <string>

using namespace std;

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
	buff[size] = NULL;
	fread (buff, size, 1, f);

	fclose (f);
	////////////////////////////////////////////////////

	char *p = buff;
	string str;

	while (p[0] != NULL)
	{
		//Decide it's counts or control characters
		if (p[0] == 10 || p[0] == 13)
		{
			//Control characters
			if (p[1] < 'A' || (p[1] > 'Z' && p[1] < 'a') || p[1] > 'z')
			{
				str += p[0];
			}
			else if (p[2] == p[1])
			{
				str += p[0];
			}
			//Counts
			else
			{
				for (int i = 0; i < p[0]; i++)
				{
					str += p[1];
				}

				p++;
			}
		}
		//Check if there're 2 same character next to each other.
		//The first of 2 character is counts.
		else if ((p[0] >= 'A' && p[0] <= 'Z') || (p[0] >= 'a' && p[0] <= 'z'))
		{
			if (p[1] == p[0])
			{
				for (int i = 0; i < p[0]; i++)
				{
					str += p[1];
				}

				p++;
			}
			//There's only one character or 2 different characters
			else
			{
				str += p[0];
			}
		}
		//It's counts for sure
		else
		{
			for (int i = 0; i < p[0]; i++)
			{
				str += p[1];
			}

			p++;
		}

		p++;
	}

	////////////////////////////////////////////////////
	//Write from buffer to decode file
	char *des = (char *)str.c_str ();

	f = fopen ("decode.rye", "wb");

	fwrite (des, 1, str.size (), f);

	fclose (f);
	////////////////////////////////////////////////////
}

void Huffman_Decompression ()
{

}