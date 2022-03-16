// Bigint implementation for 1024 bits
// operations: addition,subtraction ,multiplication
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 500
// 309 decimal digits are needed to represent the largest 1024 bit number.

void str_reverse(char result[]);
void remove_zeros(char result[]);
int compare(char bigint_1[], char bigint_2[]);


void add_BigInts(char bigint_1[],char bigint_2[],int flag);
void subtract_BigInts(char bigint_1[],char bigint_2[]);
void multiply_BigInts(char bigint_1[],char bigint_2[]);

int main()
{
	int option;
	do{
		
		printf("\n What operation You want to perform?");
		printf("\n Select the correct option number.Enter 0 if you want to exit");
		printf("\n 1. Addition of two numbers");
		printf("\n 2. Subtraction of two numbers");
		printf("\n 3. Multiplication of two numbers");
	
		
		scanf("%d",&option);
		if(option==0)
		{
			return 0;
		}

		char bigint_1[MAX];
		char bigint_2[MAX];
		printf("\n Enter the first integer: ");
		scanf("%s",bigint_1);
		printf("\n Enter the second integer: ");
		scanf("%s",bigint_2);
		
		switch (option)
		{
			case 1:
				printf("\n");
				add_BigInts(bigint_1,bigint_2,0);
				printf("\n");
				break;
			case 2:
				printf("\n");
				subtract_BigInts(bigint_1,bigint_2);
				printf("\n");
				break;
			case 3:
				printf("\n");
				multiply_BigInts(bigint_1,bigint_2);
				printf("\n");
				break;			
			default:
				printf("\n Enter the correct option number\n");
				break;
		}
	}while (option != 0);
	return 0;
}

// it returns 1 if first integer<second integer and 0 if the opposite is true
int compare(char bigint_1[], char bigint_2[])
{
    int l1 = strlen(bigint_1);
	int l2 = strlen(bigint_2);
    if(l1 < l2)       
    {
        return 1;
    }
    if(l2 < l1)
    {
        return 0;
    }
    for (int i = 0; i < l1; i++) 
    {
        if (bigint_1[i] < bigint_2[i])
        {
            return 1;
        }
        else if (bigint_1[i] > bigint_2[i])
        {
            return 0;
        }
    }
    return 0;
}


void str_reverse(char result[])
{
    int l = strlen(result);
    for(int i = 0; i < l/2; ++i)
    {
        char temp = result[i];    
        result[i] = result[l - i - 1];
        result[l - i - 1] = temp;
    }
}

// this functions removes the starting zeros
void remove_zeros(char result[])
{
	int l=strlen(result);
    int n = strspn(result, "0");
    char copy[l-n];
    int j = 0;
    for(int i = n; result[i] != '\0'; ++i)
    {
        copy[j++] = result[i];
    }
    copy[j] = '\0';
    strcpy(result, copy);
}


void add_BigInts(char bigint_1[],char bigint_2[],int flag)
{
	int flag_1 = 0, flag_2= 0;
    if(bigint_1[0] == '-' && bigint_2[0] == '-')
    {
    	bigint_1[0]='0';
    	bigint_2[0]='0'; 
        flag_1 = 1;
        flag_2 = 1;
    }
    else if(bigint_1[0] == '-')
    {
        bigint_1[0] = '0';
        remove_zeros(bigint_1);
        subtract_BigInts(bigint_2, bigint_1);// bigint_2 - bigint_1
        return;
    }
    else if(bigint_2[0] == '-')
    {
        bigint_2[0] = '0';
        remove_zeros(bigint_2);
        subtract_BigInts(bigint_1, bigint_2); // bigint_1 -bigint_2
        return;
    }
	int n; 
	int l1=strlen(bigint_1);
	int l2=strlen(bigint_2);
	if(l1>=l2) 
	{
		n=l1;
	}
	else
	{
		n=l2;
	}
	char result[n];
	int carry=0,j=0;
	while(l1>0 && l2>0)
	{
		int term_1 = bigint_1[l1 - 1] - '0';  
        int term_2 = bigint_2[l2 - 1] - '0';
        int r = term_1 + term_2 + carry;
        carry = r / 10;
        r = r % 10;
        char term = r+ '0';
        result[j] = term;
        j++;
        l1--;
        l2--;
        if(j > 309)
        {
            printf("\n Overflow ");
            return ;
        }
	}
	if(l1==0)
	{
		while(l2>0)
		{
			int term_2=bigint_2[l2-1]-'0';
			int r=term_2+carry;
			carry=r/10;
			r=r%10;
			char term=r+'0';
			result[j]=term;
			l2--;
			j++;
			if(j > 309)
        	{
            	printf("\n Overflow ");
            	return ;
        	}
		}
	}
	else if(l2==0)
	{
		while(l1>0)
		{
			int term_1=bigint_1[l1-1]-'0';
			int r=term_1+carry;
			carry=r/10;
			r=r%10;
			char term=r+'0';
			result[j]=term;
			l1--;
			j++;
			
			if(j > 309)
        	{
            	printf("\n Overflow ");
            	return ;
        	}
		}
	}
	if(carry > 0)
    {
        result[j] = carry + '0'; 
        j++;
        if(j > 309)
        {
            printf("Overflow\n");
            return ;
        }
    }
	result[j]='\0'; 
	str_reverse(result);
	remove_zeros(result);
	printf("\n The result is: ");
	if((flag_1 == 1 && flag_2 == 1) || flag==1)
	{
        printf("-");
	}
	printf("%s",result);
}


void subtract_BigInts(char bigint_1[],char bigint_2[])
{
	int flag = 0;
    if(bigint_2[0] == '-' && bigint_1[0] != '-')    //n1-(-n2)=n1+n2
    {
        bigint_2[0] = '0';
        remove_zeros(bigint_2);
        add_BigInts(bigint_1,bigint_2, 0);
    }
    else if(bigint_1[0] == '-' && bigint_2[0] != '-') //-n1-n2=-(n1+n2)
    {
        bigint_1[0] = '0';
        remove_zeros (bigint_1);
        add_BigInts(bigint_1, bigint_2, 1);
    }
    else
    {
        if(bigint_1[0] == '-' && bigint_2[0] == '-') // -n1-(-n2)=-n1+n2=n2-n1
        {
            bigint_1[0] = '0';
            bigint_2[0] = '0';
            remove_zeros (bigint_1);
            remove_zeros (bigint_2);
            subtract_BigInts(bigint_2, bigint_1);
        }
        else //n1-n2
        {
            if (compare(bigint_1, bigint_2)) 
            {
            	// swaping
                char temp[MAX];
                strcpy(temp, bigint_1); 
                strcpy(bigint_1, bigint_2);
                strcpy(bigint_2, temp);
                flag = 1; // since now the answer will be negative
            }
            char bigint[MAX] = "";
            int l1 = strlen(bigint_1);
			int l2 = strlen(bigint_2); 
            str_reverse(bigint_1)
            str_reverse(bigint_2);
            int carry = 0;
            int j = 0;
           
            for (int i=0;i<l2;i++)
            {
                int dif = ((bigint_1[i] - '0') - (bigint_2[i] - '0') - carry); 
                if (dif < 0)
                {
                    dif = dif + 10;
                    carry = 1;
                }    
                else
                {
                    carry = 0;
                }
                bigint[j] = dif + '0'; 
                j++;
                if(j > 309)
                {
                    printf("Overflow\n");
                    return ;
                }
            }
            for (int i = l2; i < l1; i++)
            {
                int dif = ((bigint_1[i] - '0') - carry);

               
                if (dif < 0)
                {
                    dif = dif + 10;
                    carry = 1;
                }
                else
                {
                	carry = 0;
                }
                bigint[j] = dif + '0';
                j++;
                if(j > 309)
                {
                    printf("Overflow\n");
                    return ;
                }
            }
            bigint[j] = '\0';
            
            str_reverse(bigint);
            remove_zeros (bigint);
            printf("Answer is: \n");
            if(flag == 1)
                printf("-");
            printf("%s\n", bigint);
        }
    }
}


void multiply_BigInts(char bigint_1[],char bigint_2[])  
{
	int flag = 0;
    int l1 = strlen(bigint_1);
    int l2 = strlen(bigint_2);
    if(l1 + l2 > 309)
    {
        printf("Overflow\n");
        return;
    }
    if((l1 == 1 && bigint_1[0] == '0') || (l2 == 1 && bigint_2[0] == '0'))
    {
        printf("0\n");// 0*n1=0
        return;
    }
    else
    {
        if(bigint_1[0] == '-' && bigint_2[0] == '-')// -n1*-n2=n1*n2
        {
            bigint_1[0] = '0';
            bigint_2[0] = '0';
            flag = 0;
        }
        else if(bigint_1[0] == '-')// -n1*n2=-(n1*n2)
        {
            bigint_1[0] = '0';
            flag = 1;
        }
        else if(bigint_2[0] == '-')//n1*(-n2)=-(n1*n2)
        {
            bigint_2[0] = '0';
            flag = 1;
        }
        remove_zeros (bigint_1);
        remove_zeros (bigint_2);
        l1 = strlen(bigint_1); 
        l2 = strlen(bigint_2);
        int result[l1+l2] = {0};
        for(int i = l1 - 1; i >= 0; i--)
        {
            for(int j = l2 - 1; j >= 0; j--)
            {
                result[i+j+1] = result[i+j+1] + (bigint_1[i]-'0')*(bigint_2[j]-'0');
                result[i+j] = result[i+j] + result[i+j+1]/10;
                result[i+j+1] = result[i+j+1] % 10;
            }
        }
        int i = 0;
        while(i < l1 + l2 && result[i] == 0)
        {
            i++;
        }
        
    	char temp[MAX];
        int j = 0;
        while(i < l1 + l2)
        {
            temp[j++] = result[i++] + '0';
        }
        temp[j] = '\0';
        remove_zeros(temp);
        if(strlen(temp)  == 0)
        {
            printf("0\n");
            return;
        }
        printf("Answer is: \n");
        if(flag == 1)
        {
            printf("-");
    	}
        printf("%s\n", temp); 
        
    }
    
    return;
}
  
