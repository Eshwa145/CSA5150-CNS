#include<stdio.h>
#include<string.h>
void railfence(char *msg,int depth,char *cipher)
{
	int len=strlen(msg);
	int matrix[depth][len];
	for(int i=0;i<depth;i++)
	{
		for(int j=0;j<len;j++)
		{
			matrix[i][j]='0';
		}
	}
	int r=0,dir=1;
	for(int i=0;i<len;i++)
	{
		matrix[r][i]=msg[i];
		if(r==depth-1)
		{
			dir=-1;
		}
		else if(r==0)
		{
			dir=1;
		}
		r+=dir;
	}
	int index=0;
	for(int i=0;i<depth;i++)
	{
		for(int j=0;j<len;j++)
		{
			if(matrix[i][j]!='0')
			{
				cipher[index++]=matrix[i][j];
			}
		}
	}
	cipher[index]='\0';
}
int main()
{
	char msg[100],cipher[100];
	int depth;
	printf("enter the message:");
	fgets(msg,sizeof(msg),stdin);
	msg[strcspn(msg,"\n")]='\0';
	printf("\n enter depth:");
	scanf("%d",&depth);
	railfence(msg,depth,cipher);
	printf("encrypted message:%s\n",cipher);
}