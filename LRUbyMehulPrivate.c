#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
//3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4

struct node {
int priority;   //Priority of a frame ie COUNT
int data;		//Page Number that has to be stored in each frame
struct node *next;
};
struct node *start = NULL;

int inputArray[SIZE];	// String of Page Numbers
int counter = 1;		// Counter that will be assigned on every Page input into frame.
int HIT = -1;			// To check if Hit occure
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
	/*
		n = number of frames
		size = number of pages
	*/
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
	
	for(i=0;i<size;i++) //STEP 1 : Travers Through EVERY PAGE. For every page, check if its HIT or FAULT
	{
        frame = start;
		while(frame != NULL)	//STEP 2 : For every page, Travers through every FRAME
		{
			if(frame->data == inputArray[i]) // STEP 3 : Check if any such PAGE already exixts
			{
				frame->data = inputArray[i];	// STEP 3.1 : if yes just input that page number 
				HIT = 1;						// STEP 3.2 : set HIT = 1 to avoid FAULT code below
				frame->priority = counter;		// STEP 3.3 : set COUNT and increment even if it HIT such that we know its RECENTLY USED
				counter++;							
				numberOfHITs++;
			}

			frame = frame->next;
		}

		if(HIT != 1)					//STEP 4 : if HIT != 1, then its FAULT for sure.
		{
			numberOfFAULTs++;
			
			//STEP 5 : PAGE REAPLACEMENT STARTS HERE 
			
			//STEP 5.1 : Find lowest Priority(COUNT), That will show the page which is not being used for a while (LEAST RECENTLY USED)
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

			//STEP 5.2 : Travers through the FRAMES to see to which it corrosponds
			frame = start;
			while(frame != NULL)
			{
				if(frame->priority == smallestPriority)
				{
					//STEP 5.3 : On detecting, Breake from the loop
					break;
				}
				frame = frame->next;
			}

			//STEP 5.4 : On breaking, the pointer is currently pointing to the desired FRAME
			// Now add data and SET COUNT
			frame->data = inputArray[i];
			frame->priority = counter;
			counter++;
		}
		HIT = 0;
    }
	printf("\nIN LRU ALGORITHM : HITs = %d --- FAULTs = %d ",numberOfHITs,numberOfFAULTs);
}
