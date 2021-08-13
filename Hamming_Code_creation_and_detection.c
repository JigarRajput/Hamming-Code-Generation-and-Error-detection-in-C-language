#include <stdio.h>
#include <conio.h>
#include <math.h>


void main()
{
	int choice;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 1 for sender side ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 2 for receiver side ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	scanf("%d",&choice);
	switch(choice)
	{
	case 1: 
	{
	
	int m,i,j;
    printf("Enter Number of bits in a message:\t");
	scanf("%d",&m);
	int message[m];
	fflush(stdin);
	
//Input Message
	printf("Enter Binary message:\t");
	for(i=0;i<m;i++)
	scanf("%1d",&message[i]);
	fflush(stdin);
	
//Reverse Message
   // message is reversed because right most bit is considered as first bit 
   int mid = (int)(0+m)/2;
   for(i=0,j=m-1; i<=mid,j>=mid; j--,i++)
   {
   	int temp = message[i];
   	message[i] = message[j];
   	message[j] = temp;
   }	
   
	
//Calculate Number of Redundant bits
    int r=1;
	while(pow(2,r) < (m+r+1))
	r++;

// parity array is of 2 dimensions 1st row will store parity bit value(0 or 1) and second row will store parity bit position
    int parity[2][r];
    int size = m+r;
    printf("\n\nSize of code word = %d",size);

	for(i=0;i<r;i++)
	parity[1][i] = pow(2,i);
	
	for(i=0;i<r;i++)
	parity[0][i] = 0;
	

// codeword formatting before parity bits assignment

  //Assigning all zero initially 
	int codeword[size];
	for(i=0;i<size;i++)
	codeword[i] = 0;

//Temporary assigning all bit positions value 5
  i=0,j=0;
  while(i<r && j<size)
  {
	codeword[j] = 5;
	j = j+pow(2,i);
	i++;
  }  
  
//Assigning Message bits to rest positions
  
    i=0;
    j=0;
    
    while(i<size && j<m)
    {
    	if(codeword[i] == 0)
    	{
    		codeword[i] = message[j];
    		j++;
		}
		
		i++;
	}



// Parity Generation
int	in=0;
	while(in<r)
	{
		int x = parity[1][in];

		int count = 0;
		
		j=x-1;
		while(j<size)
		{
			for(i=j;i<=j+x-1 && i<size;i++)
			{
				if(codeword[i] == 1)
				count++;
				
			}
		 j= j+2*x;	
		}
		
		printf("\n");
		if(count%2 == 0){
		parity[0][in] = 0;
	    printf("parity bit position %d = %d",parity[1][in],parity[0][in]); 
		}
		
		else{
		parity[0][in] = 1;
		printf("parity bit position %d = %d",parity[1][in],parity[0][in]); 
        }
		in++;
	}

//Printing parity bits	
	printf("\n\nParity pairs generated according to even parity:\t");
	for(i=0;i<r;i++)
	printf("%d",parity[0][i]);
	printf("\n\n");
	printf("\n\n");
		
	
//putting parity bits in their position	
  i=0,j=0;
  while(i<r && j<size)
  {
  	if(codeword[j] == 5)
	codeword[j] = parity[0][i];
	j = j+pow(2,i);
	i++;
  }  
    
	
//reversing the codeword again
   mid = (int)(size)/2;
   for(i=0,j=size-1; i<=mid,j>mid; j--,i++)
   {
   	int temp = codeword[i];
   	codeword[i] = codeword[j];
   	codeword[j] = temp;
   }
	
	

	printf("Final codeword generated:\t");
	for(i=0;i<size;i++)
	printf("%d",codeword[i]);
	break;
		
} // case 1 completes
		
		
		
		case 2:
			{
				int size,i,j;
    printf("Enter Number of bits in a codeword received:\t");
	scanf("%d",&size);
	int code_received[size];
	fflush(stdin);	
	
	
//Input Message
	printf("Enter Binary message:\t");
	for(i=0;i<size;i++)
	scanf("%1d",&code_received[i]);
	fflush(stdin);
	
//Reverse Message
   // message is reversed because right most bit is considered as first bit 
   int mid = (int)(0+size)/2;
   for(i=0,j=size-1; i<=mid,j>=mid; j--,i++)
   {
   	int temp = code_received[i];
   	code_received[i] = code_received[j];
   	code_received[j] = temp;
   }	

   
   //Calculate Number of checking bits
    int cb=1;
	while(pow(2,cb) < (size))
	cb++;
   	printf("Number of checking bits is :\t%d",cb);
   	
   	// checking bits array is of 2 dimensions 1st row will store parity bit value(0 or 1) and second row will store parity bit position
    int checking_bits[2][cb];

	for(i=0;i<cb;i++)
	checking_bits[1][i] = pow(2,i);
	
	for(i=0;i<cb;i++)
	checking_bits[0][i] = 0;
	
	// Parity Generation
int	in=0;
	while(in<cb)
	{
		int x = checking_bits[1][in];

		int count = 0;
		
		j=x-1;
		while(j<size)
		{
			for(i=j;i<=j+x-1 && i<size;i++)
			{
				if(code_received[i] == 1)
				count++;
			}
		 j= j+2*x;	
		}
		
		printf("\n");
		if(count%2 == 0){
		checking_bits[0][in] = 0;
	    printf("checking bit C%d = %d",in+1,checking_bits[0][in]); 
		}
		
		else{
		checking_bits[0][in] = 1;
		printf("checking bit C%d = %d",in+1,checking_bits[0][in]); 
        }
		in++;
	}
	
// Checking error position

int value = 0;
for(i=0;i<cb;i++)
{
if(checking_bits[0][i] == 1)
value = value + pow(2,i)*checking_bits[0][i];
}
	
if(value == 0)
printf("\n\nNo error in received codeword");
else
printf("\n\nError at position %d",value);	
 break;
			}
		
		default :
			printf("Enter valid choice please");
			break;
		
	}
	
}
