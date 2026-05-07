//chapter 27 challenge question 3

//in vm.c
static Value deleteFieldNative(int argCount, Value* args){
    if (argCount !=2 ) return NIL_VALUE;
    if (!ITS_INSTANCE(args[0])) return NIL_VALUE;
    if (!IS_STRING(args[1])) return NIL_VALUE;

    ObjInstance* instance = AS_INSTANCE(args[0]);
    tableDelete(&instance->fields, AS_STRING(args[1]));
    return NIL_VALUE;
}

//register the function inside initVM() in vm.c
void initVM() {
    //..
    defineNative("deleteField", deleteFieldNative);
}