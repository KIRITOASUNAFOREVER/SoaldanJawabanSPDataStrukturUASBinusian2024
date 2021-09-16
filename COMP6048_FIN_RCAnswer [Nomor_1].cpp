#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Items{
 int codes;
 char description[21];
 int quantity;
 int price;
 struct Items *next;
};

struct Items *head;
struct Items *tail;
struct Items *curr;

struct Items *newItems(int codes, char *description, int quantity, int price)
{
    struct Items *item = (struct Items *)malloc(sizeof(Items));
    item->codes=codes;
    strcpy(item->description, description);
    item->quantity=quantity;
    item->price=price;
    item->next = NULL;
    return item;
}

void pushHead(int codes, char *description, int quantity, int price)
{
    struct Items *item = newItems(codes, description, quantity, price);
    if (head == NULL)
    {
        head = tail = item;
    }
    else
    {
        item->next = head;
        head = item;
    }
}

void pushTail(int codes, char *description, int quantity, int price)
{
    struct Items *item = newItems(codes, description, quantity, price);
    if (tail == NULL)
    {
        head = tail = item;
    }
    else
    {
        tail->next = item;
        tail = item;
    }
}

void pushMid(int codes, char *description, int quantity, int price)
{
    struct Items *item = newItems(codes, description, quantity, price);
    if (head == NULL)
    {
        head = tail = item;
    }
    else if (codes < head->codes)
    {
        pushHead(codes, description, quantity, price);
    }
    else if (codes > tail->codes)
    {
        pushTail(codes, description, quantity, price);
    }
    else
    {
        curr = head;
        while (curr->next->codes < item->codes)
        {
            curr = curr->next;
        }
        item->next = curr->next;
        curr->next = item;
    }
}

void popHead()
{
    if (head == NULL)
    {
        return;
    }
    else if (head == tail)
    {
        free(head);
        head = tail = NULL;
    }
    else
    {
        curr = head;
        head = head->next;
        free(curr);
        curr = NULL;
    }
}

void popTail()
{
    if (tail == NULL)
    {
        return;
    }
    else if (head == tail)
    {
        free(tail);
        head = tail = NULL;
    }
    else
    {
        curr = head;
        while (curr->next != tail)
        {
            curr = curr->next;
        }
        tail = curr;
        curr = curr->next;
        free(curr);
        tail->next = NULL;
    }
}

void popSearch(int codes)
{
    if (head == NULL)
    {
        return;
    }
    else if (head->codes == codes)
    {
        popHead();
    }
    else if (tail->codes == codes)
    {
        popTail();
    }
    else
    {
        curr = head;
        int tanda = -1;
        while (curr->codes != codes)
        {
            if(curr->next ==NULL){
        		tanda = 0;
        		break;
			}else{
				curr = curr->next;
			}
        }
        if (tanda==0)
        {
            printf("The item doesn't exist\n");
            getchar();
        }
        else
        {
            struct Items *temp = curr->next;
            curr->next = temp->next;
            free(temp);
        }
    }
}

void searchEdit(int codes)
{
    if (head == NULL)
    {
        return;
    }
    else if (head->codes == codes)
    {
     curr = head;
        printf("Edit quantity to : ");
        scanf("%d", &curr->quantity); getchar();
        printf("Edit price to : ");
        scanf("%d", &curr->price); getchar();
        printf("Success Edit!"); getchar();
    }
    else if (tail->codes == codes)
    {
     curr = tail;
        printf("Edit quantity to : ");
        scanf("%d", &curr->quantity); getchar();
        printf("Edit price to : ");
        scanf("%d", &curr->price); getchar();
        printf("Success Edit!"); getchar();
    }
    else
    {
        curr = head;
        int tanda = -1;
        while (curr->codes != codes)
        {
        	if(curr->next ==NULL){
        		tanda = 0;
        		break;
			}else{
				curr = curr->next;
			}
        }
        if (tanda==0)
        {
            printf("The item doesn't exist\n");
            getchar();
        }
        else
        {
            printf("Edit quantity to : ");
            scanf("%d", &curr->quantity); getchar();
            printf("Edit price to : ");
            scanf("%d", &curr->price); getchar();
            printf("Success Edit!"); getchar();
        }
    }
}


void view()
{
    curr = head;
    while (curr != NULL)
    {
        printf("%d | %s | %d | %d |\n", curr->codes, curr->description, curr->quantity, curr->price);
        curr = curr->next;
    }
}


int main(){
 int opt, src;
 int codes,quantity,price;
 char description[21];
 do
 {
  system("cls");
  printf("*****MAIN MENU *****\n");
  printf("1. Add Items\n");
  printf("2. Display Items\n");
  printf("3. Edit Items\n");
  printf("4. Delete Items\n");
  printf("5. Exit\n");
  printf("\n");
  printf("Enter your option : ");
  scanf("%d",&opt); getchar();
  
  switch(opt)
  {
   case 1:
    printf("Item Codes : ");
    scanf("%d", &codes); getchar();
    printf("Item Description : ");
    scanf("%[^\n]", &description); getchar();
    printf("Item Quantity : ");
    scanf("%d", &quantity); getchar();
    printf("Item Price : ");
    scanf("%d", &price); getchar();
    pushMid(codes, description, quantity, price);
    printf("Add Items success!"); 
    getchar();
    break;
    
   case 2:
    view(); getchar();
    break;
    
   case 3:
   	if(head==NULL){
   		printf("No Item");
   		getchar();
	}else{
		printf("Input item codes : ");
    	scanf("%d", &src); getchar();
    	searchEdit(src);
	}
    
    break;
    
   case 4:
   	if(head==NULL){
   		printf("No Item");
   		getchar();
	}else{
		printf("Input item codes : ");
   		scanf("%d", &src); getchar();
    	popSearch(src);
	}
    
    break;
  }
 }while(opt!=5);
 return 0;
}
