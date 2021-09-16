#include<stdio.h>
#include<stdlib.h>

struct data{
	int number;
	data *left,*right;
}*root=NULL;

struct list{
	int angka;
	list *next;
}*head, *tail, *current;

data* push(data* node,int number)
{
	if(node==NULL)
	{
		data* current=(data*)malloc(sizeof(struct data));
		current->number=number;
		current->left=current->right=NULL;
		printf("Data Berhasil Diinput");getchar();
		return current;
	}
	else if(node->number==number)
	{
		printf("Insert gagal, data sudah ada");getchar();
		return node;
	}
	else if(number < node->number)
	{
		node->left=push(node->left,number);
	}
	else if(number > node->number)
	{
		node->right = push(node->right,number);
	}
	return node;
}

int hitungList = 1;
void listSearch(int angka)
{
	list *test = head;
	
    if ( test == NULL)
    {
        return;
    }
    else
    {
        test = head;
        int tanda = -1;
        while (test->angka != angka)
        {
            if(test->next ==NULL){
        		tanda = 0;
        		break;
			}else{
				test = test->next;
				hitungList++;
			}
        }
        if (tanda==0)
        {
            printf("The item doesn't exist\n");
            getchar();
        }
        else
        {
            printf("Angka %d ditemukan dalam List dengan %d pencarian", angka, hitungList);
            getchar();
        }
    }
    hitungList = 0;
}

int hitungTree = 1;
int search(data **node, int number){
	//jika pointer current memiliki data
	if((*node)!=NULL){
		//cek, apakah datanya lebih kecil. Jika iya, belok ke kiri
		if(number<(*node)->number){
			hitungTree++;
			search(&(*node)->left,number);
		//jika lebih besar, maka belok ke kanan
		}else if(number>(*node)->number){
			hitungTree++;
			search(&(*node)->right,number);
		//jika sama dengan, maka angka ketemu
		}else{
			printf("Angka %d ditemukan dalam Tree dengan %d pencarian", (*node)->number,hitungTree);
		}
	//jika tidak ada data lagi (not found)
	}else{
		printf("Tidak Ditemukan.");
	}
	hitungTree = 0;
}

void preOrder(data *node) 
{
	if(node==NULL)
	{
		return;
	}
	printf("%d ",node->number); 
	preOrder(node->left); 
	preOrder(node->right); 
}

void inOrder(data *node) 
{
	if(node==NULL)
	{
		return;
	}
	
	inOrder(node->left); 
	printf("%d ",node->number); 
	inOrder(node->right); 
}

void postOrder(data *node)
{
	if(node==NULL)
	{
	return;
	}
	
	postOrder(node->left); 
	postOrder(node->right); 
	printf("%d ",node->number);
}

void pushHead(int angka){
	//alokasi memory untuk data baru
	current = (list*)malloc(sizeof(struct list));
	//assign data ke dalam struct
	current->angka = angka;

	//apabila linked list kosong/tidak ada data
	if(head == NULL){
		head = tail = current;
	}
	//kondisi tidak kosong
	else{
		current->next = head;
		head = current;
	}	
}

void pushTail(int angka){
	//alokasi memory untuk data baru
	current = (list*)malloc(sizeof(struct list));
	//assign data ke dalam struct
	current->angka = angka;

	//apabila linked list kosong/tidak ada data
	if(head == NULL){
		head = tail = current;
	}
	//kondisi tidak kosong
	else{
		tail->next = current;
		tail = current;
	}
	tail->next = NULL;
}

void pushMid(int angka){
	//alokasi memory untuk data baru
	current = (list*)malloc(sizeof(struct list));
	//assign data ke dalam struct
	current->angka = angka;

	//apabila linked list kosong/tidak ada data
	if(head == NULL){
		head = tail = current;
	}
	//jika umur data yang barusan dimasukkan lebih kecil dari umur data pertama (head)
	else if(current->angka < head->angka){
		pushHead(angka);
	}
	//jika umur data yang barusan dimasukkan lebih besar dari umur data terakhir (tail)
	else if(current->angka > tail->angka){
		pushTail(angka);
	}
	//push ditengah-tengah
	else{
		list *temp = head;
		//mencari posisi data yang sesuai untuk diselipkan
		while(temp->next->angka < current->angka){
			temp = temp->next;
		}
		current->next = temp->next;
		//mengarahkan penunjuk ke alamat data baru
		temp->next = current;
	}
}


int main()
{
	int choose;
	int number;
	
	do{
		system("cls");
		printf("***** COMPARE SEARCHING USING LINKED LIST AND BINARY SEARCH TREE *****\n");
		printf("1: Add Items to the linked list and the BST\n");
		printf("2: Display Items\n");
		printf("3: Find Item\n");
		printf("4: EXIT\n");
		printf("\n");
		printf("Enter your option : ");
		scanf("%d",&choose);fflush(stdin);
		
		switch(choose)
		{
			case 1:
				printf("Masukkan Angka : ");
				scanf("%d",&number);fflush(stdin);
				pushMid(number);
				root = push(root,number);
				
				printf("\n\n");
				break;
			case 2:
				if(root==NULL){
					printf("TIDAK ADA DATA\n");
					printf("Press Enter to Continue...");
				}else{
					printf("Preorder   : ");preOrder(root);printf("\n");	
					printf("Inorder    : ");inOrder(root);printf("\n");
					printf("Postorder  : ");postOrder(root);printf("\n");		
					printf("Press Enter to Continue...");
				}
				getchar();
				break;
			case 3:
				if(root==NULL){
					printf("TIDAK ADA DATA\n");
					printf("Press Enter to Continue...");
					getchar();
				}else{
					printf("Masukkan Angka yang ingin dicari : ");
			    	scanf("%d",&number);fflush(stdin);
			    	search(&root,number);getchar();
			    	listSearch(number);
			    	printf("Press Enter to Continue...");
				}
				break;
			case 4:
				printf("Thank You Using this Program");
				break;
		}
	}while(choose!=4);
}
