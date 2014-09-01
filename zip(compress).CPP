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

/*--------------------------Global Variables Declarations-----------------------------------*/

int countleaf=0,used=0;
int scancode[256][256],binary=0,nocount=0;
int savelengthbinary[256];
int m=0,loopcheck=0,success=0,my=0,countunzip=0,ind=0;
char compare=128,check;
int bitsfrombyte[8];

/*--------------------------Global Variables Declarations For Main-------------------------*/

char already[256],ch;
int tell=0, total=0;
int rememberindexmin1=0,rememberindexmin2=0,totalnulls=0;
int lentcount[30];
float charcount[256],frequency[256];
long double min1,min2,totalbytes=0;
long double sumfreqind[30];

/*--------------------------File Pointers Declarations--------------------------------------*/

FILE  *getptr,*getptr1,*writeptr;

/*--------------------------File Read And Write Variables Declarations----------------------*/

char  readfile[30] , writefile[30];


/*--------------------------Functions Descriptions-----------------------------------------*/


void preorder(node *root1)
{
if(root1!=NULL)
	{
   if(root1->left==NULL && root1->right==NULL && (root1->leftchild!=NULL || root1->rightchild!=NULL) )
   {  leafnodes[countleaf++]=root1;
    nocount++;
   }
	preorder(root1->left);
	preorder(root1->right);
   }
}

/*--------------------------Functions Descriptions-----------------------------------------*/

void code(node * bott_to_top,int used)
{
if(bott_to_top->leftchild==NULL && bott_to_top->rightchild==NULL)
{
return ;}

else if(bott_to_top->leftchild!=NULL)
{
scancode[used][binary++]=0;
code(bott_to_top->leftchild,used);}

else if(bott_to_top->rightchild!=NULL)
{
scancode[used][binary++]=1;
code(bott_to_top->rightchild,used);}

else
{ nocount++;}

}

/*--------------------------Functions Descriptions-----------------------------------------*/


void placezero()
{
for(int l=0;l<256;l++)
{   charcount[l]=0;}

}

/*--------------------------Functions Descriptions-----------------------------------------*/


void getfilenames()
{
cout<<"\n Enter File Name To Zip=";
cin>>readfile;
cout<<"\n Enter Name Of Zipped File=";
cin>>writefile;
}

/*--------------------------Functions Descriptions-----------------------------------------*/


void openfiles()
{
if((getptr=fopen(readfile,"rb"))==NULL)
	{  cout<<"\n Unable To Open File="<<readfile;
   exit(1);          }


if((writeptr=fopen(writefile,"wb"))==NULL)
	{
     cout<<"\n Unable To Write File="<<writefile;
     exit(1);
   }


if((getptr1=fopen(readfile,"rb"))==NULL)
	{  cout<<"\n Unable To Open File="<<readfile;
   exit(1);	        }


   }


/*--------------------------Functions Descriptions-----------------------------------------*/

void readbytes()
{

while(!feof(getptr))
{   totalbytes++;
    ch=fgetc(getptr);
  tell=0;
   for(int l=0;l<total;l++)
   {    if(ch==already[l])
            {  charcount[l]+=1;
            tell++ ;    }
           }
   if(tell==0)
   {  charcount[total]+=1;
     already[total++]=ch;  }

    }   // end of while

cout<<"\n Fine 1.";

}

/*--------------------------Functions Descriptions-----------------------------------------*/

void constructtree()
{
 for(int l=0;l<total;l++)
 {      frequency[l]=(charcount[l]/totalbytes);

 newnode=new node;
 newnode->frequency=frequency[l];
 newnode->alphabet=already[l];
 allfrequency[l]=newnode;
 }

 // start of a while loop which continues until the complete tree is generated.
while(totalnulls!=(total-1))
{  //cout<<"\n Total Nulls="<<totalnulls;
 min1=900000;
 for(int find=0;find<total;find++)
 {      if(allfrequency[find]!=NULL)
      if(allfrequency[find]->frequency<min1 )//&& allfrequency[find]!=NULL)
         { min1=allfrequency[find]->frequency;
           allfrequency[rememberindexmin1]->mark=0;   // previous mark set to zero
           rememberindexmin1=find;
           allfrequency[find]->mark=1;
         }
         }
 min2=900000;

 for(int find=0;find<total;find++)
 {      if(allfrequency[find]!=NULL)
      if(allfrequency[find]->frequency<min2 && allfrequency[find]->mark!=1)
         { min2=allfrequency[find]->frequency;
           rememberindexmin2=find;
         }
         }

newnode=new node;
newnode->frequency=min1+min2; // sum goes into the new node.
allfrequency[rememberindexmin1]->leftchild=newnode;
allfrequency[rememberindexmin2]->rightchild=newnode;
newnode->left=allfrequency[rememberindexmin1];
newnode->right=allfrequency[rememberindexmin2];
allfrequency[rememberindexmin1]=newnode;
allfrequency[rememberindexmin2]=NULL;
 totalnulls++;

}      // end of while loop bracket

for(int a=0;a<total;a++)
{   if(allfrequency[a]!=NULL)
    {
    root=allfrequency[a];
    }
}

cout<<"\n Fine 2.";

}

/*--------------------------Functions Descriptions-----------------------------------------*/


void writealphabets()
{
part.records_written=total;
fwrite(&part,sizeof(part),1,writeptr);
cout<<"\n Fine 3.";
}

/*--------------------------Functions Descriptions-----------------------------------------*/

void writetable()
{   int feedcount,bit,specialcount=0,specialcount1=0,specialcount2=0;
     nocount=0;
 for(int getcode=0;getcode<total;getcode++)
{  if(leafnodes[getcode]!=NULL)
	binary=0;
	code(leafnodes[getcode],getcode);    // generates binary code.
	savelengthbinary[getcode]=binary;     // saves the length of binary code.
	binary=0;
// cout<<"\n";
 //getch();
//////////// object creation for writing to disk later.
newnodde.alphabet=leafnodes[getcode]->alphabet;
newnodde.binarylength=savelengthbinary[getcode];
newnodde.binary1=0;
newnodde.binary2=0;
newnodde.binary3=0;
for(int display=(savelengthbinary[getcode]-1);display>-1;display--)
{  //   cout<<scancode[getcode][display];
   if(feedcount<=7)
       {    bit=scancode[getcode][display];
            newnodde.binary1=newnodde.binary1 | bit;
            specialcount2++;
            if(feedcount<=6)
            { newnodde.binary1<<=1; }
         }
      else if(feedcount>7 && feedcount<=15)
       {  bit=scancode[getcode][display];
          newnodde.binary2=newnodde.binary2 | bit;
              specialcount++;
              if(feedcount<=14)
               { newnodde.binary2<<=1;}
        }

      else if(feedcount>16 && feedcount<=23)
       {  bit=scancode[getcode][display];
          newnodde.binary3=newnodde.binary3 | bit;
              specialcount1++;
              if(feedcount<=22)
               { newnodde.binary3<<=1;}
        }

    feedcount++;
//newnodde->binary[display]=scancode[getcode][display];
}

for(int t=specialcount;t<7;t++)
{  newnodde.binary2<<=1; }
specialcount=0;

for(int t=specialcount1;t<7;t++)
{  newnodde.binary3<<=1; }
specialcount1=0;

for(int t=specialcount2;t<7;t++)
{  newnodde.binary1<<=1; }
specialcount2=0;



fwrite(&newnodde,sizeof(newnodde),1,writeptr);    // table written to disk
/////////// end of object creation

lentcount[(savelengthbinary[getcode])]++;     // saves length of bits  reference end
sumfreqind[(savelengthbinary[getcode])]+=leafnodes[getcode]->frequency;

feedcount=0;
}
cout<<"\n Fine 4.";

}


/*--------------------------Functions Descriptions-----------------------------------------*/


void identification()
{
fputc('A',writeptr);
fputc('s',writeptr);
fputc('a',writeptr);
fputc('d',writeptr);
cout<<"\n Fine 5.";
}


/*--------------------------Functions Descriptions-----------------------------------------*/

void writerestfile()
{
char byte;
int remembercompare;
char bit;
int cnbit=0,count=0;



while(!feof(getptr1))
{
    ch=fgetc(getptr1);
     for(int compare=0;compare<total;compare++)
     {   if(ch==leafnodes[compare]->alphabet)
         {   remembercompare=compare; }   }

                                     /// }   // end of while
 for(int scan=(savelengthbinary[remembercompare]-1);scan>-1;scan--)
{
count++;
bit=scancode[remembercompare][scan];
byte =byte | bit;
if(count<=7)
{ byte<<=1; }

cnbit++;
    if(cnbit == 8)
    {

       ///////////// actual
      fputc(byte,writeptr);
        cnbit=0;						// flush it to the stream
        byte=0;
        count=0;
      ////////////// end of actual
    }

    }
       }// end of while

 if(cnbit<8)
 {  REPEAT:
 count++;
     if(count<=7)
        { byte<<=1;
        goto REPEAT;} }
 fputc(byte,writeptr);
cout<<"\n Fine 6.";
}

/*--------------------------Functions Descriptions-----------------------------------------*/
void closepointers()
{
fclose(getptr);
fclose(getptr1);
fclose(writeptr);
cout<<"\n Fine 7.";
}


/*--------------------------Functions Descriptions-----------------------------------------*/


void message()
{
cout<<"\n Compressed Successfully.";
}


/*--------------------------Functions Descriptions-----------------------------------------*/


void main()
{

placezero();       // initialization
getfilenames();     // getfile names from user
openfiles();         // open the file pointers
readbytes();         // read the file once and count alphabets
constructtree();    //  construct the tree by finding minimum each time
preorder(root);      // check the tree by performing pre-order traversal
writealphabets();    // writes the total number of alphabets read from original file.(Table)
writetable();        // writes the alphabets with there short codes to file.(Table)
identification();    // writes the file identification mark.
writerestfile();     // compresses the original file and rewrites it to disk.
closepointers();     // all opened file pointers are closed.
message();           // sucessfull message is displayed.
getch();

 }