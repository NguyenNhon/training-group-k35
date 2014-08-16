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
		//Control characters for sure
		if ((p[0] == '\r' && p[1] == '\n') || (p[0] == '\n' && p[-1] == '\r'))
		{
			str += p[0];
		}
		//Check if there're 2 same character next to each other.
		//The first of 2 is counts. For example: "AA" mean 65 characters 'A'
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