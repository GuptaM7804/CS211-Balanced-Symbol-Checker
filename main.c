// Name: Manav Gupta
// UIN: 657115759
// Date: 9/23/2021
// Project 2
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//create struct named stack
typedef struct stack
{
    int InUse; //current or top of stack
    int size; //size of array
    char* darr; //array pointer
    int space; //counts the number of spaces so printf can output at the right spot
}STACK;

//Initialize and name all functions needed for project
STACK init(STACK* stack);
int is_empty(STACK* stack);
void push(STACK* stack, char input, int debugMode);
void pop(STACK* stack, int debugMode);
char top(STACK* stack);
STACK clear(STACK* stack);
void printStack(STACK stack);
char swap(char bracket);
int checkCUR(STACK stack, char bracket, char* input);
void errorYN(STACK stack, char temp, char cur, char* input);
int readInput(char* s, int debugMode);

//struct initializing function, gives value to all elements of the struct
STACK init(STACK* stack)
{
    stack = (STACK*) malloc (sizeof(STACK*));
    stack->InUse = -1;
    stack->size = 2;
    stack->darr = (char*) malloc((2) + sizeof(char));
    stack->space = 0;
    return *stack;
}

//checks if struct is empty/if value of inUse is more than 0
int is_empty(STACK* stack)
{
    if(stack->InUse<0)
        return 1;
    else
        return 0;
}

//pushes a value into the struct, increases size if struct is full, in debugmode, outputs what is happening and when, 
void push(STACK* stack, char userInput, int debugMode)
{
    stack->space++; //increase space by 1 every time a new item is pushed
    
    if(stack->InUse == (stack->size-1)) //if array is full increase it twofold
    {
        if(debugMode)
            printf("Old size: %d\n", stack->size);
            
        STACK* temp = (STACK*) malloc (sizeof(STACK));
        temp->darr = (char*) malloc ((2) * sizeof *stack->darr);
        for(int i=-1; i<=stack->size; i++)
            temp->darr[i] = stack->darr[i];
        
        if(debugMode)
            printf("Number of items copied over: %d\n", stack->size);
            
        stack->darr = temp->darr;
        stack->size = stack->size * 2;
        
        if(debugMode)    
            printf("New size: %d\n", stack->size);
    }
    
    stack->InUse = stack->InUse + 1;
    stack->darr[stack->InUse] = userInput; //userinput is inputted to the array at the top/current
    
    if(debugMode)
    {
        printf("Item Pushed: %c\n", stack->darr[stack->InUse]);
        printStack(*stack);
    }
}

void pop(STACK* stack, int debugMode)
{
    if(stack->InUse >= 0) //if stack is not empty
    {
        stack->space++; // increase space(counting for the closing bracket)
        
        if(debugMode == 1)
            printf("Item Popped: %c\n", stack->darr[stack->InUse]);
        
        stack->InUse = stack->InUse - 1; //reduce value of inuse by 1 per item removed
        
        if(debugMode==1)
            printStack(*stack);
    }
    else
        printf("Stack is empty\n"); //if stack is empty print stack is empty
}

//returns the top item in array
char top(STACK* stack)
{
    return (stack->darr[stack->InUse]);
}

//clears or resets the stack
STACK clear(STACK* stack)
{
    free(stack->darr); //free the array
    stack->size = 0; //set all corresponding values to what they were
    stack->InUse = -1;
    stack->space = 0;
    
    return *stack; //return this stack
}

// prints the stack
void printStack(STACK stack)
{
    printf("STACK:\t");
    for(int i = stack.InUse; i > -1; i--) //print backwards (first item entered to last item entered)
        printf("%c", stack.darr[i]);
    printf("\n");
}

//swaps the bracket, so if '(' but ')' then returns ')'
char swap(char bracket)
{
    switch(bracket)
    {
        // returns opposite bracket for each
        case '(': return ')';
        case '{': return '}';
        case '[': return ']';
        case '<': return '>';
        case ')': return '(';
        case '}': return '{';
        case ']': return '[';
        case '>': return '<';
        default:
            return bracket;
    }
}

//if stack is empty and closing bracket is given, then outputs the that the opening bracket is needed
int checkCUR(STACK stack, char bracket, char* input)
{
    if(stack.InUse<0) //if stack is empty
    {
        char cur = swap(bracket);
        printf("\n%s", input);
        for(int i=0; i<stack.space; i++)
            printf(" ");
        printf("^ missing %c\n", cur);
        return 0; //return 0 if stack closing bracket is inputted for no opening bracket
    }
    return stack.darr[stack.InUse]; //returns value if still going (stack not empty) and lets pop function pop the bracket
}

// if temp is not 0 and if temp is a different bracket to the inputted bracket...
void errorYN(STACK stack, char temp, char cur, char* input)
{
    if(temp!=0) // the temp from cur doesn't return 0, then...
    {
        cur = top(&stack);
        cur = swap(cur);
        printf("\n%s", input);
        for(int i=0; i<stack.space; i++)
            printf(" ");
        printf("^ missing %c\n", cur); //outputs the bracket that should've been added before
    }
}

//all functions in this function to keep main nice and tidy :)
int readInput(char* s, int debugMode)
{
    //initializing stack
    STACK stack;
    stack.darr = NULL;
    stack = init(&stack);
    char temp; //character variable temp to check...
    char *input = s; // unassigned charater pointer to s as s changes throughout the function
    
    if(s == NULL)
        return 0; //if s is nothing, return 0
    
    if(*s == '\0')
        return 1; //if s is '\0' return 1
    
    while(*s != '\0') //while it's not '\0'
    {
        char cur; //character variable current
        
        if(*s == ' ' || (*s > 64 && *s < 91) || (*s > 96 && *s < 123))
        {
            stack.space++; //increase space for each space in input to make mistake pointer/output statement output in the right place
            s++;
            continue;
        }
        
        switch (*s)
        {
            //break for each opening bracket inputted and check...
            case '(':   push(&stack, *s, debugMode); 
                break;
            case '{':   push(&stack, *s, debugMode);
                break;
            case '[':   push(&stack, *s, debugMode);
                break;
            case '<':   push(&stack, *s, debugMode);
                break;
            default:
                break;
        }
        
        // if the closing bracket is outputted right after or not, if not, then loops again, until closing brakcet is met
        if(*s == ')')
        {
            temp = checkCUR(stack, *s, input);
            if(temp == '(')
                pop(&stack, debugMode);
            else
            {
                errorYN(stack, temp, cur, input);
                return 0; // return 0 if closing bracket is not met and output error
            }
        }
        
        else if(*s == '}')
        {
            temp = checkCUR(stack, *s, input);
            if(temp == '{')
                pop(&stack, debugMode);
            else
            {
                errorYN(stack, temp, cur, input);
                return 0;
            }
        }
        
        else if(*s == ']')
        {
            temp = checkCUR(stack, *s, input);
            if(temp == '[')
                pop(&stack, debugMode);
            else
            {
                errorYN(stack, temp, cur, input);
                return 0;
            }
        }
        
        else if(*s == '>'){
            temp  = checkCUR(stack, *s, input);
            if(temp == '<')
                pop(&stack, debugMode);
            else
            {
                errorYN(stack, temp, cur, input);
                return 0;
            }
        }
        s++; //s counter increases
    }
    
    if(is_empty(&stack)) //if stack is empty
    {
        stack = clear(&stack); //clear the stack
        return 1; //return 1;
    }
    else
    {
        char cur = top(&stack); // since stack is not empty and no more input is inputted... 
        cur = swap(cur); //swap the current/top stack bracket
        printf("\n%s", input);
        for(int i = 0; i<stack.space ; i++)
            printf(" ");
        printf("^ missing  %c\n", cur); //and output the mistake where it was made
        stack = clear(&stack); //clear stack
        return 0; //return 0;
    }
}

int main (int argc, char** argv)
{
    char line[300]; //300 elements allowed in line
    
    int debugMode = 0; // debugmode is off/=0 until turned on
    
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0) //if '-d'
        {
            debugMode = 1; // then debugmode is on/=1
        }
    }
    
    printf ("\nEnter input to check or q/Q to quit\n");
    fgets(line, 300, stdin);
    
    while (1) // infinite loop
    {
        if(*line == 'q' || *line == 'Q')
            break; //break from while loop
        
        if(readInput(line, debugMode)) // if 1 is returned, i.e. balanced equation
        {
            printf("Expression is balanced\n");
        }   
        else //if 0 is returned, i.e. error is met
        {
            printf("Expression is not balanced\n");
        }
        printf ("\nEnter input to check or q/Q to quit\n");
        fgets(line, 300, stdin); //keep taking input until while loop is exited
    }
    
    printf ("\nGoodbye");
    return 0; //end project
}