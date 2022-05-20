#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cm_node_s 
{
	int data;
	int time;
	struct cm_node_s *next;
} cm_node;
static cm_node *cm_offline = NULL;

int add(cm_node* top, int item) { 
    cm_node *newnode, *temp_node;
	temp_node = cm_offline;
	int flag=1;
	while(temp_node != NULL)
	{
		if(temp_node->data == item)
		{
			temp_node->data = item-1;
			flag=0;
		}
		temp_node = temp_node->next;
	}
	if(flag)
	{
		newnode = (cm_node*) malloc(sizeof(cm_node)); 
		if(newnode == NULL) { 
			printf("\n記憶體配置失敗！"); 
			exit(1); 
		} 
		newnode->data = item;
		newnode->time = item; //input item value for time
		newnode->next = top; 
		cm_offline = newnode;
	}
#if 0
	else
	{
		while(temp_node != NULL)
		{
			printf("temp->%d",temp_node->data);
			temp_node = temp_node->next;
		}
	}
#endif
}

void del(cm_node* top, int item) {
	cm_node * ptr = top;
	cm_node * previous;
	while( ptr != NULL )
	{
		if(ptr->data == item)
		{
			if ( ptr == cm_offline)
			{
				printf("******Find CM first node %d OFF Line\n", item);		
				cm_offline = cm_offline->next;
			}
			else
			{
				previous = top;
				while ( previous->next != ptr )
				{
					//printf("*1*****Find Previous CM node %d OFF Line\n", previous->data);
					previous = previous->next;
				}
				printf("******Find CM node %d OFF Line\n", item);
				previous->next = ptr->next;
				while ( previous!=NULL)
				{
					//printf("*2*****Find Previous CM node %d OFF Line\n", previous->data);
					previous = previous->next;
				}

				top= previous;
			}
			free(ptr);
			break;
		}
		ptr = ptr->next;
	}
}

void del_all(void)
{
	cm_node* temp;
	if(cm_offline != NULL)
	{
		while(cm_offline)
		{
			temp = cm_offline;
			cm_offline = cm_offline->next;
			free(temp);
		}
	}
}
void Check_Node_Time(void)
{
	cm_node * cm_offline_time=NULL;
	cm_offline_time = cm_offline;
	while(cm_offline_time != NULL)
	{
		if(cm_offline_time->time == 0)
			del(cm_offline,cm_offline_time->data);
		cm_offline_time = cm_offline_time->next;
	}
}
void list(cm_node* top) { 
    cm_node *tmpnode = top; 
    printf("\n堆疊內容：");

    if(cm_offline !=NULL)
    {   
        while(tmpnode != NULL) {
            if(tmpnode->time <= 3) {
                tmpnode->time = 0;
            }
            else
                printf("%d ", tmpnode->data); 
            tmpnode = tmpnode->next; 
        }
    }   
}

int main(void)
{
    int input, select; 


    while(1) { 
        printf("\n\n請輸入選項(-1結束)："); 
        printf("\n(1)插入值至堆疊"); 
        printf("\n(2)刪除所有結點"); 
        printf("\n(3)刪除值"); 
        printf("\n(4)顯示所有內容"); 
        printf("\n==>"); 
        scanf("%d", &select); 
        
        if(select == -1) 
            break; 

        switch(select) { 
            case 1: 
                printf("\n輸入值："); 
                scanf("%d", &input); 
                add(cm_offline, input); 
                break; 
            case 2: 
                printf("\n刪除所有結點");
				del_all(); 
                break; 
            case 3:
				printf("\n輸入刪除值："); 
				scanf("%d", &input);
                del(cm_offline,input);
				Check_Node_Time();
                break; 
            case 4: 
                list(cm_offline); 
                break; 
            default: 
                printf("\n選項錯誤！"); 
        } 
    } 

    printf("\n"); 
	return 0;
}
