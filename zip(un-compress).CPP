#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LETH 30


/*--------------------------Structure Declarations-----------------------------------------*/

struct table
{ char binarylength;
  char alphabet;
  char binary1;
  char binary2;
  char binary3;
       } ;

table newnodde,*tfirst=NULL;
table rnode,*rtfirst=NULL;

/*--------------------------Structure Declarations-----------------------------------------*/

struct records
{ int records_written; };
records part;


/*--------------------------Structure Declarations-----------------------------------------*/

struct node
{ long double frequency;
char alphabet;
node *right,*left;
node *leftchild,*rightchild;
int mark;
intialize()
{   right=left=NULL;  frequency=0;
    leftchild=NULL; rightchild=NULL;
    mark=0;  alphabet='\0';
       }
};

node * allfrequency[256],*newnode,*root;
node * leafnodes[256];
node *saveforreuse[256],*rootun,*newnodeun,*downward;
node * update;

/*--------------------------Global Variables Declarations-----------------------------------*/

int countleaf=0,used=0;
int scancode[256][256],binary=0,nocount=0;
int savelengthbinary[256];
int m=0,loopcheck=0,success=0,my=0,countunzip=0,ind=0;
char compare=128,check;
int bitsfrombyte[8];

/*--------------------------Global Variables Declarations For Main-------------------------*/
char byte;
char already[256],ch;
int tell=0, total=0;
int rememberindexmin1=0,rememberindexmin2=0,totalnulls=0;
int lentcount[30];
float charcount[256],frequency[256];
long double min1,min2,totalbytes=0;
long double sumfreqind[30];
int set=0,sim=0;

/*--------------------------File Pointers Declarations--------------------------------------*/

FILE  *getptr,*getptr1,*writeptr;
FILE * stream;

/*--------------------------File Read And Write Variables Declarations----------------------*/

char unreadfile[30];
char unzipfile[30];

/*--------------------------Functions Descriptions-----------------------------------------*/




void unzip(char byt)
{
for(int clr=0;clr<8;clr++)
{ bitsfrombyte[clr]=0; }
countunzip=0;
while(countunzip!=8)
	{
countunzip++;
check=(byt&compare);

  if(check==0)
  {  bitsfrombyte[ind++]=0; }
  else
  { bitsfrombyte[ind++]=1; }

  if(countunzip<=7)
 {  byt<<=1;   }
                   }

for(int replace=0;replace<ind;replace++)
{
      if(downward->left==NULL && downward->right==NULL)
         { fputc(downward->alphabet,stream);
            downward=rootun;
           }

       if(bitsfrombyte[replace]==0)
         { downward=downward->left;}

        if(bitsfrombyte[replace]==1)
         { downward=downward->right;}


         }        // end of for loop



         }    // end of function



/*--------------------------Functions Descriptions-----------------------------------------*/



void check_preorder(node *browse)
{ if(browse!=NULL)
   {
   if(browse->left==NULL && browse->right==NULL)
    {
     nocount++;
      }
    check_preorder(browse->left);
    check_preorder(browse->right);
   }
}


/*--------------------------Functions Descriptions-----------------------------------------*/

void un_getfilenames()
{
cout<<"\n Enter File Name To Unzip=";
cin>>unreadfile;
cout<<"\n Enter Name Of Unzipped File=";
cin>>unzipfile;

}


/*--------------------------Functions Descriptions-----------------------------------------*/


void un_openpointers()
{
if((getptr=fopen(unreadfile,"rb"))==NULL)
	{  cout<<"\n Unable To Open Read File="<<unreadfile;
   exit(1);	}

if((stream=fopen(unzipfile,"wb"))==NULL)
	{ cout<<"\n Unable To Open Write File="<<unzipfile;
   exit(1);	}



   }


/*--------------------------Functions Descriptions-----------------------------------------*/


void readalphabetcount()
{
fread(&part,sizeof(part),1,getptr);    // reads the value of total from file.
}


/*--------------------------Functions Descriptions-----------------------------------------*/

void un_createtree()
{
int binary[24],temp;

newnodeun=new node;
rootun=newnodeun;
rootun->left=NULL;
rootun->right=NULL;
saveforreuse[0]=rootun;
for(int reed=0;reed<part.records_written;reed++)
{      temp=0;
 for(int clr=0;clr<256;clr++)
 { saveforreuse[clr]='\0';}

 saveforreuse[0]=rootun;     /// again added to check
fread(&rnode,sizeof(rnode),1,getptr);
for(int refeed=0;refeed<rnode.binarylength;refeed++)
{
     if(refeed<=7)
     {
    check=(rnode.binary1 &compare );
          if(check==0)
	   	  {  binary[temp++]=0; }
		    else
		     { binary[temp++]=1; }
  if(refeed<=6)
 {  rnode.binary1<<=1;   }
                                }

     if(refeed>7 && refeed<=15)
     {
    check=(rnode.binary2 &compare );
          if(check==0)
	   	  {  binary[temp++]=0; }
		    else
		     { binary[temp++]=1; }
  if(refeed<=14)
 {  rnode.binary2<<=1;   }
                                }


     if(refeed>15 && refeed<=23)
     {
    check=(rnode.binary3 &compare );
          if(check==0)
	   	  {  binary[temp++]=0; }
		    else
		     { binary[temp++]=1; }
  if(refeed<=22)
 {  rnode.binary3<<=1;   }
                                }


}

if(rnode.binarylength==0)
{ loopcheck++;}

for( m=0/*(rnode.binarylength-1)*/,sim=0;m<rnode.binarylength,sim<rnode.binarylength;m++,sim++)
{ // cout<<binary[m];
    newnodeun=NULL;


 if(binary[m]==0 && saveforreuse[sim]->left==NULL)
{     // creates node if not exist's
      newnodeun=new node;
      newnodeun->alphabet='\0';
      newnodeun->left=NULL;
      newnodeun->right=NULL;
      newnodeun->leftchild=saveforreuse[sim];
      saveforreuse[sim]->left=newnodeun;
      saveforreuse[sim+1]=newnodeun;
                       }

else if(binary[m]==1 && saveforreuse[sim]->right==NULL)
{     // creates node if not exist's
      newnodeun=new node;
      newnodeun->alphabet='\0';
      newnodeun->left=NULL;
      newnodeun->right=NULL;
      newnodeun->rightchild=saveforreuse[sim];
      saveforreuse[sim]->right=newnodeun;
      saveforreuse[sim+1]=newnodeun;
                       }

else if(binary[m]==0 && saveforreuse[sim]->left!=NULL)
         {  saveforreuse[sim+1]=saveforreuse[sim]->left;  }

else if(binary[m]==1 && saveforreuse[sim]->right!=NULL)
         {  saveforreuse[sim+1]=saveforreuse[sim]->right;  }


  }
//cout<<"\n";
//getch();
 if(newnodeun->left==NULL && newnodeun->right==NULL)
{   newnodeun->alphabet=rnode.alphabet; success++; }

  }


}

/*--------------------------Functions Descriptions-----------------------------------------*/


void readidentification()
{
byte=fgetc(getptr);
cout<<byte;
byte=fgetc(getptr);
cout<<byte;
byte=fgetc(getptr);
cout<<byte;
byte=fgetc(getptr);
cout<<byte;
nocount=0;
}


/*--------------------------Functions Descriptions-----------------------------------------*/

void calculateandwrite()
{
downward=rootun;
long double times=0,total_size=0;
 fpos_t filepos;
         fgetpos(getptr,&filepos);
    fseek(getptr,0,SEEK_END);   // seeks to the end of file
    total_size=ftell(getptr);   // tells the size of the file
    fseek(getptr,0,SEEK_SET);   // resets the file pointer to beginning
        fsetpos(getptr,&filepos);
        total_size-=((part.records_written-1)*5)+4;
   while(times!=total_size-1)//!feof(getptr))
{  ind=0;   times++;
byte=fgetc(getptr);
      unzip(byte);
        }


}



void un_closepointers()
{
fclose(getptr);
fclose(stream);

}


void main()
{

un_getfilenames();
un_openpointers();
readalphabetcount();
un_createtree();
readidentification();
check_preorder(rootun);
calculateandwrite();
un_closepointers();


cout<<"\n Unzipping of File Complete.";

 getch();
}