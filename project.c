//In the billing section it checks if the item is in the list but it is your
//responsibility to provide correct name price and quantity

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define USER_NAME "admin"
#define PASS "project"
//to use goto function
COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x; coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void title();
void home();
void add();
void update();
void deleterec();
void view();
void bill();


struct details
{
    int id;
    char name[20];
    int price;
    int qty;
};

struct details item;

int main()
{
    int i;
    char username[10]=USER_NAME;
    char user[10];
    char pass[10]=PASS;
    char password[10];

    title();
    gotoxy(36,6);
    printf("::::::Please LogIn to continue:::::::");

    relogin:

    printf("\n\n\nEnter username:");
    fflush(stdin);
    scanf("%s",&user);

    printf("\nEnter passcode:");
    scanf (" %s", &password);

    if((strcmp(user,username)==0)&&(strcmp(pass,password)==0))
    {
        printf("\nLogin Successful!!");
        getch();


        home();


    }

    else
    {
        printf("\nLogin Unsuccessful!!\nPlease try again:");
        goto relogin; //avoid goto if possible
    }

    return 0;
}


void home()
{

    system("cls");

    printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::\n\n\n\t\t\t");

    gotoxy(40,9);
    printf("You can do any one of the following:");
    gotoxy(40,11);
    printf("1. View available items");
    gotoxy(40,12);
    printf("2. Add items");
    gotoxy(40,13);
    printf("3. Update all the items");
    gotoxy(40,14);
    printf("4. Delete items in the store");
    gotoxy(40,15);
    printf("5. Calculate My Bill");
    gotoxy(40,16);
    printf("6. Exit");

    rechoose:
    gotoxy(40,20);
    printf(" Choose any of the above options:");

    int x;
    scanf("%d",&x);

    switch(x)
    {

    case 1:
        view();
        break;

    case 2:
        add();
        break;

    case 3:
        update();
        break;

    case 4:
        deleterec();
        break;

    case 5:
        bill();
        break;

    case 6:
        exit(1);

    default:
        printf("Enter above choice only:");

        goto rechoose;

    }

}
//Add records
void add()
{

    FILE *fp=fopen("items.dat","ab+");

    if(fp==NULL)
    {
        printf("Error opening file");
        return;
    }

while(1)
{

    system("cls");

    printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");

    gotoxy(50,8);
    printf ("ADD ITEMS IN THE STORE");

        fflush(stdin);
        gotoxy(40,10);
        printf("Name of item: ");
        gets(item.name);

        gotoxy(40,11);
        printf ("Enter unique ID of the item: ");
        scanf ("%d",&item.id);

        gotoxy(40,12);
        printf("Quantity of item: ");
        scanf("%d",&item.qty);

        gotoxy(40,13);
        printf("Price of item: ");
        scanf("%d",&item.price);

        fseek(fp,0,SEEK_END);
        fwrite(&item,sizeof(struct details),1,fp);
        fflush(stdin);
        gotoxy(40,16);
        printf("Continue? (Y/N)");
        char ch = getch();
        if(ch=='N'|| ch=='n')
            break;
    }

    fclose(fp);
    gotoxy(40,18);
    printf("Your items has been added successfully.");

    getch();

    home();
}

//update records from start

void update()
{
    FILE *fp=fopen("items.dat","wb+");

    if(fp==NULL)
    {
        printf("Error opening file");
        return;
    }



while(1)
{

    system("cls");

    printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");

    gotoxy(50,8);
    printf ("UPDATE ITEMS IN THE STORE");

    fflush(stdin);
    gotoxy(40,10);
    printf("Name of item: ");
    gets(item.name);

    gotoxy(40,11);
    printf ("Enter unique ID of the item: ");
    scanf (" %d",&item.id);

    gotoxy(40,12);
    printf("Quantity of item: ");
    scanf("%d",&item.qty);

    gotoxy(40,13);
    printf("Price of item: ");
    scanf("%d",&item.price);


    fseek(fp,0,SEEK_END);

    fwrite(&item,sizeof(struct details),1,fp);
    fflush(stdin);
    gotoxy(40,16);
    printf("Continue? (Y/N)");
    char ch = getch();
    if(ch=='N'|| ch=='n')
        break;
    }

    fclose(fp);
    gotoxy(40,18);
    printf("Your items has been added successfully.");

    getch();


    home();

}
//delete record using itemid
void deleterec()
{
    while (1)
    {
        system("cls");
        int itemid;
        int flag=0;
        char ch;
        printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");

        gotoxy(50,8);
        printf ("DELETE ITEMS IN THE STORE");

        gotoxy(40,10);
        printf ("Enter the Id of the item you want to delete:");
        scanf ("%d",&itemid);
        FILE *fp;
        FILE *ft;
        fp=fopen("items.dat","rb");
        ft=fopen("temp.dat","wb+");
        rewind(fp);
        while(fread(&item,sizeof(struct details),1,fp))
        {
            if (item.id==itemid)
            {
                //item is found. so when  the item is found in file then hold the program otherwise printing to a new file
                flag=1;
                gotoxy(40,18);
                printf ("Record found and deleted successfully");
            }
          else
            {
                fseek(ft,0,SEEK_END);
                fwrite(&item,sizeof(struct details),1,ft);
            }
        }
        if (flag==0)
        {
            gotoxy(40,18);
            printf ("Record not found");
        }
        fclose(fp);
        fclose(ft);
        remove("items.dat");
        rename("temp.dat","items.dat");

    getch();


    home();

}
}

//view items in the store

void view()
{
    system("cls");
    int x=0;
    printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");

    gotoxy(45,8);
    printf ("ITEMS AVAILABLE IN THE STORE");
    gotoxy(40,10);
    printf("ID\tName\t\t Quantity\tPrice");
    gotoxy(38,11);
    printf("----------------------------------------------------------");


    FILE *fp = fopen("items.dat", "rb");

    if(fp==NULL)
    {
        printf("Error opening file");
    }

    fseek(fp,0,SEEK_SET);
    while(fread(&item,sizeof(struct details),1,fp))
    {
        gotoxy(40,13+x);
        printf("%d\t%s\t\t %d\t\t%d\t\t\n",item.id,item.name,item.qty,item.price);
        x++;

    }

     fclose(fp);

 getch();

home();

}


void bill()
{

    int cur=0,x,y,i,sum=0,flag;
    system("cls");

    printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");
    FILE *fp = fopen("items.dat","rb");
    struct details purchase[20]={0};
    gotoxy(50,8);
    printf ("BILLING SECTION");
    gotoxy(40,10);
    printf("How many items do you want to purchase?\t");
    scanf("%d",&x);
    for(i=0;i<x;i++)
   {
        flag=0;
        system("cls");

        printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");

        fflush(stdin);
        gotoxy(50,8);
        printf("BILLING SECTION");
        gotoxy(40,11);
        printf ("Enter Id of item:\t");
        scanf ("%d",&purchase[i].id);
        rewind(fp);
        while(fread(&item,sizeof(struct details),1,fp))
            {
                if (item.id==purchase[i].id)
                {
                    flag=1;
                }
            }
        if(flag==1)
        {
            fflush(stdin);
            gotoxy(40,12);
            printf("Name of item:\t");
            gets(purchase[i].name);

            gotoxy(40,13);
            printf("Quantity of item:\t");
            scanf("%d", &purchase[i].qty);

            gotoxy(40,14);
            printf("Price of item:\t");
            scanf("%d", &purchase[i].price);
        }
        if(flag==0)
        {
            gotoxy(40,12);
            printf("Record not found.");
            gotoxy(20,13);
            printf("Please view all the items first and use the item code,name,quantity available in the list.\n");
            break;
    }
   }
   if(flag==1)
   {
        getch();
        fflush(stdin);
        system("cls");
        printf ("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::");

        gotoxy(50,6);
        printf("BILL");

        gotoxy(30,8);
        printf("Id\t Name\t Quantity\t Price\t   Total");

        for(i=0;i<x;i++)
        {
            gotoxy(30,12+cur);
            printf("%d\t %s\t %d\t\t %d\t    %d\t",purchase[i].id,purchase[i].name,purchase[i].qty,purchase[i].price,(purchase[i].qty*purchase[i].price));

            sum+=(purchase[i].qty*purchase[i].price);
            cur++;
        }

        printf("\n-----------------------------------------------------------------------------------------------------------------------\n");


        printf("\nYour total cost is Rs. %d",sum);

        printf("\nEnter money received from customer:");
        fflush(stdin);
        scanf("%d",&y);

        printf("Please return Rs.%d",y-sum);
        getch();
       }
}

//animated title

void title()
{
    int i,j,k,l;
    char title[]=("\t\t\t:::::::::::::::::KATHMANDU DEPARTMENT STORE:::::::::::::::::\n\n\n\t\t\t  :::::::::::::::::Welcome To Our System::::::::::::::::::\n\n\n\t\t\t");
    char fn[]=("Developed By:");
    char fn1[]=("Sandeep Acharya");
    char fn2[]=("Saujan Tiwari");

    for (i=0;i<strlen(title);i++)
    {
        putchar(title[i]);
        Sleep(25);
    }
    for (j=0;j<strlen(fn);j++)
    {
        gotoxy(75+j,21);
        putchar(fn[j]);
        Sleep(25);
    }
    for (k=0;k<strlen(fn1);k++)
    {
        gotoxy(85+k,22);
        putchar(fn1[k]);
        Sleep(25);
    }
    for (l=0;l<strlen(fn2);l++)
    {
        gotoxy(85+l,23);
        putchar(fn2[l]);
        Sleep(25);
    }
}
