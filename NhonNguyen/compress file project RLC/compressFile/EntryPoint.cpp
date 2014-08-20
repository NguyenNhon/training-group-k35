#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct LetterCounter
{
	char	m_letter;
	int		m_count;
};

int CountElementOfCompressFile(char* _fileContent, int _Count);
void compressFile();
void uncompressFile();

int main()
{
	int choose;
	printf("Please choose compress file(1) or extract file(2): \n");
	do
	{
		scanf("%d", &choose);
		if(choose != 1 && choose != 2)
		{
			printf("You false. Please choose again! \n");
		}
	}
	while(choose != 1 && choose != 2);
	switch(choose)
	{
	case 1:
		{
			compressFile();
			break;
		}
	case 2:
		{
			uncompressFile();
			break;
		}
	}
}


void compressFile()
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

	int* OutputFileContent = new int [sizeList+1]();
	for (int i = 0; i < index; i++)
	{
		OutputFileContent[i] = list[i].m_count;
		OutputFileContent[i] = OutputFileContent[i] << 8;
		OutputFileContent[i] = OutputFileContent[i] | list[i].m_letter;
	}
	
	FILE* fo = fopen("compressed.txt", "wb");
	fwrite(OutputFileContent, sizeof(int), sizeList, fo);
	fclose(fo);
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

void uncompressFile()
{
	FILE* fp = fopen("compressed.txt","rb");
	fseek(fp, 0, SEEK_END);

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
}


//#include <stdio.h>
//
//class file
//{
//public:
//	file();
//	void compressFile();
//	~file();
//};
//
//file::file()
//{
//	printf("Nhap file du lieu: %s", );
//
//}
//
//
//
//file::~file()
//{}
//
//int main()
//{
//
//
//	return 0;
//}