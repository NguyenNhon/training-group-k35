#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>

using namespace std;

struct LetterCounter
{
	char	m_letter;
	int		m_count;
};

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

	vector<LetterCounter> list;
	int dem = 1;
	LetterCounter temp;
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
			list.push_back(temp);
			dem = 1;
		}
	}

	int* OutputFileContent = new int [list.size()+1]();
	OutputFileContent[0] = list.size();
	for (int i = 0; i < list.size(); i++)
	{
		OutputFileContent[i + 1] = list.at(i).m_count;
		OutputFileContent[i + 1] = OutputFileContent[i + 1] << 8;
		OutputFileContent[i + 1] = OutputFileContent[i + 1] | list.at(i).m_letter;
	}
	
	FILE* fo = fopen("compressed.txt", "wb");
	fwrite(OutputFileContent, sizeof(int), list.size()+1, fo);
	fclose(fo);

	

	return 0;
}

