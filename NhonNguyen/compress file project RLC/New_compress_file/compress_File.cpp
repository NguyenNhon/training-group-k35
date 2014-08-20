#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <vector>

using namespace std;

struct LetterCounter
{
	char	m_letter;
	int		m_count;
};

int CountElementOfCompressFile(char* _fileContent, int _Count);

int main()
{
	/*Compress file code block*/
	FILE* fp = fopen("Input.txt", "rb");
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char* fileContent = new char[fileSize+1]();//clear allocate
	fileContent[fileSize] = 0;

	fread(fileContent, sizeof(char), fileSize, fp);
	fclose(fp);

	int sizeList = CountElementOfCompressFile( fileContent, fileSize);
	LetterCounter* list = new LetterCounter[sizeList];
	int dem = 1;
	LetterCounter temp;
	int index = 0;
	for(int i=0; i<fileSize; i++)
	{
		if(fileContent[i] == fileContent[i+1])
		{
			dem++;
		}
		else
		{
			temp.m_letter = fileContent[i];
			temp.m_count = dem;
			list[index] = temp;
			index ++;
			dem = 1;
		}
	}

	int* OutputFileContent = new int [sizeList+1]();//e chong len no rồi mà, thì gán lại thôi
	for (int i = 0; i < index; i++)
	{
		OutputFileContent[i] = list[i].m_count;
		OutputFileContent[i] = OutputFileContent[i] << 8;
		OutputFileContent[i] = OutputFileContent[i] | list[i].m_letter;
	}
	
	FILE* fo = fopen("compressed.txt", "wb");
	fwrite(OutputFileContent, sizeof(int), sizeList, fo);
	fclose(fo);

	

	return 0;
}

int CountElementOfCompressFile(char* _fileContent, int _Count)
{
	int result = 1;
	for (int i = 0; i < _Count; i++)
	{
		if(_fileContent[i] != _fileContent[i+1])
		{
			result ++;
		}
	}
	return result;
}