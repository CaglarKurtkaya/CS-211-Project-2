#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int DebugMode; 


typedef struct StackStruct{
	char *ptr;          // pointer to the dynamic array that actually holds the stack 
	int sizeOfArr;      // integer variable specifying the current size of the dynamic array 
	int topOfArr;       // integer variable specifying the top of the stack 
	
}Stack;

//=================================================================================================
/*initializing the stack */
void init(Stack *s){
	s->sizeOfArr = 2;   // set size
	s->topOfArr = 0;    // specify the top of the stack;
	char *arr = (char*)malloc(sizeof(char)*s->sizeOfArr);  //allocate memory for the array
	s->ptr = arr;
	
}

//==================================================================================================
/*clearing the stack so that it is empty and ready to be used again*/
void clear(Stack *s){
	s->sizeOfArr = 2;   // set size
	s->topOfArr = 0;    // specify the top of the stack;
	free(s->ptr);	    // deallocate memory
}

//==================================================================================================
/*checking if the stack is empty*/
int is_empty(Stack *s){
	if(s->topOfArr == 0){   // checks if stack is empty
		return TRUE;
	}
	else{
		return FALSE;
	}
}
//==================================================================================================
/*pushing/adding an element onto the stack */
void push(Stack *s, int val){
	int i;
	if(DebugMode == TRUE){
		printf("\nDEBUG FOR PUSH()");
	}
	// check if the stack array is full
	if(s->topOfArr == s->sizeOfArr){
		// increase the size of the stack 	    	 	    
	 	s->sizeOfArr += 2;	 	  
		// if full allocate increased memory 
		char *temp = (char*)malloc(sizeof(char) * s->sizeOfArr); 
			// get current values into temp   
			for(i = 0; i < s->sizeOfArr; i++){                  
				temp[i] = s->ptr[i];
			}
			
			// deallocate the old one
			free(s->ptr);
			// get the new increased size stack
	 	    s->ptr = temp;	
			  	 	  
	 	    if(DebugMode == TRUE){
				printf("\nNew Size = %d", s->sizeOfArr);
			}
	 	    
	 	    if(DebugMode == TRUE){
				printf("\nNumber of values copied = %d", s->topOfArr);
			}
		}
		
		else{
			if(DebugMode == TRUE)
				printf("\nSize = %d", s->sizeOfArr);
		}
											
	//add val onto stack 
	s->ptr[s->topOfArr] = val;
	if(DebugMode == TRUE){
		printf("\nPushed to the Stack = %c", s->ptr[s->topOfArr]);
	}
	// incerement the variable specifying the top of the stack	     
	s->topOfArr = s->topOfArr + 1;
	
}

//==================================================================================================
/*popping/removing an element off of the stack */
void pop(Stack *s){
	
	 // decrease the top of the stack     
	 s->topOfArr -= 1;    
	 
	if(DebugMode == TRUE){
		printf("\nDEBUG FOR POP() = ");
		printf("\nPoped from stack = %c",s->ptr[s->topOfArr]);
		printf("\nTop value = %d", s->topOfArr);
						
	}
	
	// delete the top value;
	s->ptr[s->topOfArr] = 0;
		
}
//==================================================================================================
/*accessing/returning the top element on the stack */
char top(Stack *s){
	// returns what stored in the top of the stack
	return (s->ptr[s->topOfArr - 1]);
}
//==================================================================================================

 

int main (int argc, char** argv)
{
 char input[301];
 int i;
 
 
 Stack s;    // declare stack s 
 init(&s);  // initializing the stack 
 
 
 /* FOR DEBUGGING */ 
 for ( i = 0 ; i < argc ; i++ ){
 	if (strcmp (argv[i], "-d") == 0 ){
 		printf("\nDEBUG MODE IS ON\n");
 		DebugMode = TRUE; 		
	 } 	
 }
 
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   	
	/* remove the newline character from the input */
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

 /* set up an infinite loop */
 while (1)
 {
 	char macthing;     // to store symbols to macth with the closed ones
 	char missing;      // to store when there is symbol is missing to balance 
 	char expecting;    // to store when expecting a different closing symbol 
 	int check = 1;     // condition check
 	
 	int j;
 	i = 0;
		   
   fgets(input, 300, stdin);
   /* check if user enter q or Q to quit program */
   	if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     	break;
        // loop to read the user input 
   		for(i = 0; i < strlen(input) -1; i++){
			//push to stack if opening symbol is encountered
			if(input[i] == '(' || input[i] == '{' || input[i] == '[' || input[i] == '<'){
				push(&s , input[i]);
			}
   
   
   			// check if the input is closing symbol
  			 if(input[i] == ')' || input[i] == '}' || input[i] == ']' || input[i] == '>'){
   				//set closing symbols to macthing opening symbols
				if(input[i] == ')')
   					macthing = '(';
		
				if(input[i] == '}')
					macthing = '{';
		
				if(input[i] == ']')
					macthing = '[';
		
				if(input[i]== '>')
					macthing = '<';
				   			
     			// pop the top stack symbol if it is macthing 
   				if(top(&s) == macthing){
   					pop(&s);
   					continue;
  		 		}
                 
                // if it is not macthing closing symbol is expexted 
   				if(top(&s) != macthing){
					if(is_empty(&s) == 0){
						if(top(&s) == '('){			
							expecting = ')';
						}						
						else if(top(&s) == '{'){			
							expecting = '}';
						}				
						else if(top(&s) == '['){
							expecting = ']';
						}
						else{
							expecting = '>';
						}
			
						// loop to print empty chars to get to the right place to print error
						for(j = 0; j < i; j++){			
							printf(" ");
						}
						printf("^ expecting %c\n\n", expecting);
						check = 0;  // error  found exit the program without entring the next condition after while loop
						break;
			
					}
					else if(is_empty(&s) == 1){
						for(j = 0; j < i; j++){
							printf(" ");
						}
						printf("^ missing %c\n\n", macthing);
						check = 0; // error  found exit the program without entring the next condition after while loop
						break;
					}
				}
			}
		} // end of for loop

		// final check
		if(check == 1){
			// if stack is empty it is balanced
			if(is_empty(&s) == 1){
				printf("\nExpression is balanced\n");
				break;
			}	
			// stack is not empty, missing closing symbol
			if(is_empty(&s) == 0){
					if(top(&s) == '(')
					missing = ')';
					else if(top(&s) == '{')
					missing = '}';
					else if(top(&s) == '[')
					missing = ']';
					else
						missing = '>';
					for(j = 0; j < i; j++){					
						printf(" ");
					}
					printf("^ missing %c\n\n", missing);
					break;
			}	
		}		
	} // end of while
	
 //clear the stack so that it is empty and ready to be used again
 clear(&s);
 printf ("\nGoodbye\n");
 return 0;
}
