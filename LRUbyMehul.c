#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
//3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4

struct node {
int priority;
int data;
struct node *next;
};
struct node *start = NULL;

int inputArray[SIZE];
int counter = 1;
int HIT = -1;
int FAULT = -1;
int numberOfHITs = 0,numberOfFAULTs = 0;

void createNode()
{
    struct node *p = (struct node *)malloc(sizeof(struct node));

	p->priority = 0;
	p->data = 0;
    p->next=NULL;

    if(start == NULL){
        start = p;
    }

    else{
		struct node *temp = start;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
    }
}


void main()
{
	int n,size,i;
	struct node *frame = start;

    printf("\nENTER THE NUMBER OF FRAMES : ");
    scanf("%d",&n);

    for(i=1;i<=n;i++){
        createNode();
    }

    printf("\nENTER THE NUMBER OF PAGES : ");
    scanf("%d",&size);

	printf("\nENTER THE %d : ",size);
	for(i=0;i<size;i++){
        scanf("%d",&inputArray[i]);
    }

	int smallestPriority;
	for(i=0;i<size;i++)
	{
        frame = start;
		while(frame != NULL)
		{
			if(frame->data == inputArray[i])
			{
				frame->data = inputArray[i];
				HIT = 1;
				frame->priority = counter;
				counter++;
				numberOfHITs++;
			}

			frame = frame->next;
		}

		if(HIT != 1)
		{
			numberOfFAULTs++;
			frame = start;
			smallestPriority = frame->priority;
			while(frame != NULL)
			{
				if(frame->priority < smallestPriority)
				{
					smallestPriority = frame->priority;
				}
				frame = frame->next;
			}

			frame = start;
			while(frame != NULL)
			{
				if(frame->priority == smallestPriority)
				{
					break;
				}
				frame = frame->next;
			}

			frame->data = inputArray[i];
			frame->priority = counter;
			counter++;
		}
		HIT = 0;
    }
	printf("\nIN LRU ALGORITHM : HITs = %d --- FAULTs = %d ",numberOfHITs,numberOfFAULTs);
}
