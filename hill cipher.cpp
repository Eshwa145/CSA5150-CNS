#include<stdio.h>
#include<string.h>
main()
{
	unsigned int a[10][10];
	int c[20],d[20];
	int i,j,n,t=0;
	char pt[100],ct[100];
	printf("enter matrix size:");
	scanf("%d",&n);
	printf("enter elements for matrix:");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	printf("\n enter plain text:");
	scanf("%s",pt);
	printf("ascii value of plain text is:");
	for(i=0;i<strlen(pt);i++)
	{
		c[i]=pt[i]-65;
		printf("%d\t",c[i]);
	}
	printf("\n encrypted text is:");
	for(i=0;i<n;i++)
	{
		t=0;
		for(j=0;j<n;j++)
		{
			t=t+(a[i][j]*c[j]);
		}
		d[i]=t%26;
	}
	for(i=0;i<n;i++)
	{
		printf("%c",d[i]+65);
	}
}