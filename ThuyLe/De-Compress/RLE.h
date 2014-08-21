#include <stdio.h>

namespace RLE
{
	int m_size;
	FILE *f;
	void Compress();
	void Decompress();
};
void RLE::Compress()
{
	//Find size of f
	f = fopen("Source.tat", "rb");
	fseek(f, 0, SEEK_END);
	m_size = ftell(f);

	//Transform from file to string
	char* buf = new char[m_size];
	fseek(f, 0, SEEK_SET);
	fread(buf, 1, m_size, f);
	fclose(f);

	//Compress file
	int count = 0;//count the number of a char present
	FILE*f1 = fopen("Compress", "wb");
	for (int i = 1; i <= m_size; i++)
	{
		i = i + count - 1;
		count = 1;
		for (int j = i; j < m_size; j++)
		{
			if (buf[j] == buf[j + 1])
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if (count != 1)
		{
			_putw(count, f1);//write the number of a char present in file by int
		}
		if (i != m_size)
		{
			fputc(buf[i], f1);
		}
	}
	fclose(f1);
}
void RLE::Decompress()
{
	//Find size of f
	f = fopen("Compress", "rb");
	fseek(f, 0, SEEK_END);
	m_size = ftell(f);

	//Transform from file to string
	char* buf = new char[m_size];
	fseek(f, 0, SEEK_SET);
	fread(buf, 1, m_size, f);

	//Decompress
	int k = 0;//save index of temp[]
	int count;
	char* temp;
	char* temp2;
	temp = new char[m_size];//array is used for save the information content of decompress file

	for (int i = 0; i < m_size; i++)
	{
		if ((buf[i + 1] == NULL) && (i != m_size - 1))
		{
			count = int(buf[i]);//the number of char buf[i] present
			for (int j = 0; j < count; j++)
			{
				if (k >= m_size)
				{
					m_size++;

					temp2 = new char[m_size];
					for (int i = 0; i < m_size; i++)
					{
						temp2[i] = temp[i];
					}
					temp = NULL;
					delete[] temp;

					temp = new char[m_size];
					for (int i = 0; i < m_size; i++)
					{
						temp[i] = temp2[i];
					}
					temp2 = NULL;
					delete[] temp2;

				}
				temp[k] = buf[i + 4];
				k++;
			}
			i += 4;
		}
		else
		{
			temp[k] = buf[i];
			k++;
		}
	}
	
	FILE* f1 = fopen("Decompress", "wb");
	fwrite(temp, 1, m_size, f1);
	_fcloseall();
}