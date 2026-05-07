//chapter 27 challege question 2

//in vm.c
static Value getFieldNative(int argCount, Value* args) {
    if (argCount != 2) return FALSE_VAL;
    if (!ITS_INSTANCE(args[0])) return FALSE_VAL;
    if (!IS_STRING(args[0])) return FALSE_VAL;

    ObjInstance* instance = AS_INSTANCE(args[0]);
    Value value;

    if (!tableGet(&instance->fields, AS_STRING(args[1]), &value)) {
        return NIL_VAL;
    }
    return value;
}

static Value setFieldNative(int argCount, Value* args){
    if (argCount != 3) return FALSE_VAL;
    if (!ITS_INSTANCE(args[0])) return FALSE_VAL;
    if (!IS_STRING(args[0])) return FALSE_VAL;

    ObjInstance* instance = AS_INSTANCE(args[0]);
    tableSet(&instance->fields, AS_STRING(args[1]), args[2]);
    return args[2];
}

//register the functions inside initVM() in vm.c
void initVM() {
    //..
    defineNative("getField", getFieldNative);
    defineNative("setField", setFieldNative);
}