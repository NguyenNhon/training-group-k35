#include "Decompress.h"
#include <stdio.h>

void Decompressed2 ()
{
	FILE *f = fopen ("encode.rye", "rb");

	fseek (f, 0, SEEK_END);
	int size = ftell (f);
	fseek (f, 0, SEEK_SET);

	char *buff = new char[size];
	fread (buff, size, 1, f);

	fclose (f);

	char *p = buff;

	/*f = fopen ("decode.rye", "wb");

	while (p != NULL)
	{
		if (p[0] >= 128)
		{
			int length = (int)p[0] - 128;
			p++;
			for (int i = 0; i < length; i++)
			{
				fprintf (f, "%c", p[0]);
			}

			p++;
		}
		else
		{
			fprintf (f, "%c", p[0]);
			p++;
		}
	}

	fclose (f);*/
}

void Decompressed1 ()
{

}