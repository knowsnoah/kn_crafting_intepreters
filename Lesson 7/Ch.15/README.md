# Chapter 15 Questions 3 and 4

## Question 3:
### Replace the Stack definition in vm.h:
Before:

    #define STACK_MAX 256
    
    typedef struct {
    
        Chunk* chunk;
        uint*_t* ip;
        value stack[STACK_MAX];
        value* stackTop;
    
    } VM;

After:

    typedef struct {

        Chunk* chunk;
        uint8_t* ip;
        Value* stack;
        Value* stackTop;
        int stackCapacity;
} VM;

### Initialize the stack memory vm.c

Before:

    void initVM() {
        resetStack();
    }

After:

    void initVM() {
        vm.stackCapacity = 256;
        vm.stack = malloc(sizeof(value))
        resetStack();
    }

### Free the stack memory in vm.c

Before:

    void freeVM(){}

After:

    void freeVM(){
        free(vm.stack);
    }

### Modify the push function in vm.c

Before:
 
    void push(value value){
        *vm.stackTop = values;
        vm.stackTop++;
    }

After:

    void push(Value value) {

        if (vm.stackTop - vm.stack >= vm.stackCapacity) {
            vm.stackCapacity *= 2;
            vm.stack = realloc(vm.stack, sizeof(Value) * vm.stackCapacity);
            vm.stackTop = vm.stack + vm.stackCapacity / 2;
        }
    
        *vm.stackTop = value;
        vm.stackTop++;
    }

## Question 4:

Optimize OP_NEGATE

Before:

    case OP_NEGATE: push(-pop()); break;

After:
    
    case OP_NEGATE:
        vm.stackTop[-1] = -vm.stackTop[-1];
        break;

Replace the marco with this optimized version

After:
    
    #define BINARY_OP(op) \
    do { \
    vm.stackTop[-2] = vm.stackTop[-2] op vm.stackTop[-1]; \
    vm.stackTop--; \
    } while (false) 
        