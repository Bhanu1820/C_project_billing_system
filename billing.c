#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct items{
       char item[20];
       float price;
       int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//funtions for bill genretion
void generateBillHader(char name [50],char date [30]){
    printf("\n\n");
    printf("\t    Adv.Restaurant");
    printf("\n\t   ================");
    printf("\n Date:%s",date);
    printf("\nInvoice To:%s",name);
    printf("\n");
    printf("======================================\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n======================================");
    printf("\n\n");  
}
void generateBillbody(char item [30],int qty,float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}


void generateBillFooter(float total){
     printf("\n");
     float dis=0.1*total;
     float nettotal=total-dis;
     float cgst=0.09*nettotal,grandTotal=nettotal+2*cgst;
     printf("======================================\n");
     printf("Sub Total\t\t\t%.2f",total);
     printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
     printf("\n\t\t\t\t=======");
     printf("\nNet Total\t\t\t%.2f", nettotal);
     printf("\nCGST 09%s\t\t\t%.2f","%",cgst);
     printf("\nSGST 09%s\t\t\t%.2f", "%",cgst);
     printf("\n======================================");
     printf("\nGrand Total\t\t\t%.2f",grandTotal);
     printf("\n======================================\n");
}
int main(){
    
    int opt,n;
    struct orders ord;
    struct orders order; 
    char saveBill='y',contFlag='y';
    char name[50];
    FILE *fp;
     //dashbord
     while(contFlag == 'y'){
        system("cls");
        float total=0;
        int invoiceFound=0;

    printf("\t===========ADV. RESTAURANT============");
    printf("\n\n Please select your operation\t");
    printf("\n\n1. Generate Invoice");
    printf("\n2. Show all Invoices");
    printf("\n3. Search Invoice");
    printf("\n4. Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin); //to consume \n from buffer
    switch(opt){
        case 1:
        
        system("cls");
        printf("name of costomer");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;//to remove \n from string
        strcpy(ord.date,__DATE__);//__DATE__ gives date 
        printf("enter no. items\t");
        scanf("%d",&n);
        ord.numOfItems=n;

        for (int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("enter quantity\t");
            scanf("%d",&ord.itm[i].qty);
            printf("price\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }

        generateBillHader(ord.customer,ord.date);
        for (int i = 0; i < ord.numOfItems; i++) {
           generateBillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);
        printf("want to save?\n");
        scanf("%s",&saveBill);

        if(saveBill=='y'){
            fp=fopen("RestaurentBill.txt","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0){
            printf("\n Successfully saved");}
            else
            printf("\n error saving");
            fclose(fp);
        }
        break;
       
        case 2:
        system("cls");
        //int t;
       // t=fread(&order,sizeof(struct orders),1,fp);
       // printf("%d",t);
        fp=fopen("RestaurentBill.txt","rb");
        if(fp==NULL){
            printf("error");
        }
        printf("\nold in voice\n");
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float tot=0;
            generateBillHader(order.customer,order.date);
            for (int i=0;i<order.numOfItems;i++)
            {  
                generateBillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFooter(tot);
            
        }
        fclose(fp);
        break;

    

   case 3:
    printf("\nenter the name of the customer:\t");
   // fgetc(stdin);
    //fgetc(stdin);
    fgets(name,50,stdin);
    name[strlen(name)-1]=0;
     system("cls");
        //int t;
      // t=fread(&order,sizeof(struct orders),1,fp);
      // printf("%d",t);
        fp=fopen("RestaurentBill.txt","rb");
        if(fp==NULL){
            printf("error");
        }
        printf("\n*****Invoice of %s*****\n",name);
        while(fread(&order,sizeof(struct orders),1,fp))
        {
            float tot=0;
            if(!strcmp(order.customer,name)){
            generateBillHader(order.customer,order.date);
            for (int i=0;i<order.numOfItems;i++){   
                generateBillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty*order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound=1;
            }
            if(!invoiceFound){
                printf("sorry the invoice for %s dosenot exists",name);
            }
        
            
        }
        fclose(fp);
        break;

        case 4:
        printf("\n\t\t Bye Bye....");
        exit(0);
        break;

        default:
        printf("sorry invalid option");
        break;
    }
    printf("\n do ypunt to continue[y/n]");
    scanf("%s",&contFlag);
     }


    printf("\n\n");
    
    return 0;
}
