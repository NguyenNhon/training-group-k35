#include <stdio.h>
#include <stdlib.h>
#define PathFile "Text.txt"
#define PathFileEncode "FileEncode.bin"
#define PathFileDeEncode "DeEncode.txt"

char* Buffer;//biến dùng để lưu dữ liệu đọc vào từ file

int ReadFileBinary()
{
	  FILE *f=NULL;
	  char k;
	  int iSize,i;

	  f=fopen(PathFile,"rb");

	  if(f==NULL)
	  {
		perror("Error");
		exit(1);
	  }

	  fseek(f, 0, SEEK_END);
	  iSize = (ftell(f) ) / sizeof(char);
	  Buffer = new char[iSize];
	  i = 0;
	  fseek(f, 0, SEEK_SET);

	  while(!feof(f))
		  fread(&Buffer[i],iSize,1,f);

	  fclose(f);
	  return iSize;
}

int Count(int n)
{
	  int i, j, k;
	  i = j = 0;
	  while(i <n )
	  {
		j++;
		k=Buffer[i];
		while(Buffer[i]==k)
		  i++;
	  }
	  return j;
}

void Encode(char* ArrCPS, int iSizeFile, int iSizeArrEncode)
{
	int i, iDem, k, j;
	i = j = 0;
	while (i < iSizeFile)
	{
		iDem = 0;
		k = Buffer[i];
		while (Buffer[i] == k)
		{
			i++;
			iDem++;
		}
		ArrCPS[j] = iDem;
		ArrCPS[++j] = k;
		j++;
	}
	FILE *fw;
	fw = fopen(PathFileEncode, "wb");
	fwrite(ArrCPS, iSizeArrEncode, 1, fw);
	fclose(fw);
}

void DeEncode(char* Arrtemp)
{
	  FILE *fwt=NULL;
	  char k;
	  int iSize,i;
	  char *ArrEncode;

	  fwt=fopen(PathFileEncode,"r");

	  if(fwt==NULL)
	  {
		perror("Error");
		exit(1);
	  }

	  fseek(fwt, 0, SEEK_END);
	  iSize = (ftell(fwt) ) / sizeof(char);
	  ArrEncode = new char[iSize];
	  i = 0;
	  fseek(fwt, 0, SEEK_SET);

	  while(!feof(fwt))
		  fread(&ArrEncode[i],iSize,1,fwt);

	  fclose(fwt);

	  int iDem = -1;
	  for(int i = 0; i < iSize;)
	  {
		  for(int k = 0; k < ArrEncode[i]; k++)
			  Arrtemp[++iDem] = ArrEncode[i+1];
		  i += 2;
	  }
}

int main(void)
{
	//iSizeFile dùng để lưu kích thước file đọc vào
	//iSizeComPression kích thước file sau khi ta nén
	//ArrCompression dùng để lưu file nén
	//ArrTemp dùng để lưu file giải nén ra
	int iSizeFile, iSizeComPression;
	char *ArrCompression, *ArrTemp;
	
	iSizeFile = ReadFileBinary();
	iSizeComPression = Count(iSizeFile)*2;
	ArrTemp = new char[iSizeComPression];

	printf("\nKich thuoc file truoc khi nen : %d\n",iSizeFile);

	ArrCompression = new char[iSizeComPression];

	//gọi hàm nén file
	Encode(ArrCompression, iSizeFile, iSizeComPression);

	//gọi hàm giải nén file
	DeEncode(ArrTemp);

	//ghi ra file vừa giải nén vào file DeEncode.txt
	FILE *fDeencode = fopen(PathFileDeEncode,"w");
	fwrite(ArrTemp, iSizeFile, 1, fDeencode);
	fclose(fDeencode);

	printf("\nKich thuoc file sau khi nen : %d\n",iSizeComPression);
	return 0;
}