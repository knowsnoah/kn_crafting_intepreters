//Chapter 26 Challenge Question 3 

//changes made to object.h
struct Obj {
    ObjType type;
    //Add refCount to Obj struct
    int refCount;
    struct Obj* next;
};

//Changes made to object.c
static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)rellocate(NULL, 0, size);
    object->type = type;
    object->refCount = 0; //initialize refCount to 0
}


//in memory.c
static void sweep() {
    Obj* previous = NULL;
    Obj* object = vm.objects;
    while (object != NULL) {
        //changing sweep to free refCount of 0
        if (object != NULL) {
            previous = object;
            object = object->next;
        }
    }
}

void collectGarbage() {
#ifdef DEBUG_LOG_GC
    printf("-- gc begin\n");
    size_t before = vm.bytesAllocated;
#endif 
}
    sweep();
    
    vm.nextGC = vm.bytesAllocated * GC_HEAP_GROW_FACTOR;


//in memory.h
//newobject ref counting functions
void incRef(Obj* value);
void decRef(Obj* value);

//in memory.c
void incRef(Obj* value) {
    value->refCount++;
}
static void decrementValue(Value value) {
    if (IS_OBJ(value)) decRef(AS_OBJ(value));
}
static void decrementArray(ValueArray* value_array) {
    for (int i=0; i < value_array->count; i++) {
        decrementValue(value_array->values[i]);
    }
}

void decRef(Obj* value) {
    if (value->refCount > 1 ) {
        value_.refCount--;
    } else {
        //Decrement refVal of objets referenced by the current object
        switch (value->type) {
            case OBJ_FUNCTION: {
                ObjFunction* function = (ObjFunction*)value;
                if (function->name != NULL) decRef((Obj*)function->name);
                decrementArray(&function->chunk.constants);
                break;
            }

            case OBJ_UPVALUE: {
                ObjUpvalue* upvalue = (ObjUpvalue*)value;
                decrementRef(upvalue->closed);
                break;
            }
            case OBJ_CLOSURE: {
                OBjClosure* closure = (ObjClosure*)value;
                decRef((Obj*)closure->function);
                for (int i=0; i < closure->upvalueCount; i++) {
                    decRef((Obj*)closure->upvalues[i]);
                }
                break;
            }
            case OBJ_NATIVE:
            case OBJ_STRING:
                break;
        }
    }
}



//in compiler.c
static void initCompiler(Compiler* compiler, FunctionType type) {
    compiler->enclosing = NULL;
    //this function is referenced by the compiler
    incRef((Obj*)compiler->function);
}

static ObjFunction* endCompiler() {
    current = current->enclosing;
    //function no longer reference by the compiler
    decRef((Obj*)function);
    return function;
}

//lastly in vm.c
void push(Value value){
    if (IS_OBJ(value)) incRef(AS_OBJ(value));
    *vm.stackTop = value;
    vm.stackTop++;
}

//pops trigger a reference count decrease 
Value pop() {
    if (IS_OBJ(*vm.stackTop)) decRef(AS_OBJ(*vm.stackTop));
    vm.stackTop--;
    return *vm.stackTop;
}

static ObjValue* captureUpvalue(Value* local){
    //Upvalue is referenced immediately, so refCount is updated
    ObjUpvalue* createdUpvalue = newUpvalue(local);
    incRef((Obj*)createdUpvalue);
    //increment the reference count of the local if is it an object
    if (IS_OBJ(*local)) incRef(AS_OBJ(*local));
    createdUpvalue->next = upvalue;
}