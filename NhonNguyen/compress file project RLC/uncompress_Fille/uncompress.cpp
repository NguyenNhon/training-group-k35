#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <vector>

using namespace std;

struct LetterCounter
{
	char	m_letter;
	int		m_count;
};

int main()
{
	FILE* fp = fopen("compressed.txt","rb");
	
	int size = (ftell(fp))/4;

	fseek(fp, 0, SEEK_SET);

	int* InputFileContent = new int[size]();
	fread(InputFileContent, sizeof(int), size, fp);

	fclose(fp);

	LetterCounter* list = new LetterCounter[size]();
	LetterCounter temp;

	int CharCounter = 0;
	int index = 0;
	for (int i = 0; i < size; i++)
	{

		temp.m_letter = InputFileContent[i];
		temp.m_count = InputFileContent[i] >> 8;
		CharCounter += temp.m_count;
		list[index] = temp;
		index ++;
	}

	char* OutputFileContent = new char[CharCounter + 1]();
	OutputFileContent[CharCounter] = 0;

	CharCounter = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < list[i].m_count; j++)
		{
			OutputFileContent[CharCounter] = list[i].m_letter;
			CharCounter ++;
		} 
	}

	FILE* OutputFile = fopen("uncompressed.txt", "wb");

	fwrite(OutputFileContent, sizeof(char), CharCounter, OutputFile);

	fclose(OutputFile);

	return 0;
}
