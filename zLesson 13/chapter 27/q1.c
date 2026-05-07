//Chapter 27 Challenge Question 1

//in vm.c
static Vlaue hasFieldNative(int argCount, Value* args) {
    if (argCount != 2) return FALSE_VAL;
    if (!ITS_INSTANCE(args[0])) return FALSE_VAL;
    if (!IS_STRING(args[0])) return FALSE_VAL;

    ObjInstance* instance = AS_INSTANCE(args[0]);
    Value dummy;
    return BOOL_VAL(tableGet(&instance->fields, AS_STRING(args[1]), &dummy));
}
//Add the native function: checks whether there are exactly 2 arguments, the 
//first argument is an instance, the second argument is a string, and the 
//named field exists in the instance’s fields table

void initVM() {
    //..
    defineNAtive("hasField", hasFieldNative);
}
//register the function insidde initVM() in vm.c
//inside initVM(), add this line with the other defineNative calls