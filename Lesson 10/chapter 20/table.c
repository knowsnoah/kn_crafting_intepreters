//Challenge Question #1

//changes for answer

#include <string.h>

static Entry* findEntry(Entry* entries, int capacity, Value key) {
    //changed key-hash to hashValue(key) so it works for any value type
    uint32_t index = hashValue(key) % capacity;
}

//changes to the else statement
else if (valuesEqual(entry->key, key)) {
    //changed from entry->key == key to valuesEqual()
    // so we can compare values instead of pointers
    return entry;
}

static void adjustCapacity(Table* table, int capacity) {
    Entry* entries = ALLOCATE(Entry, capacity);
    for (int i =0; i < capacity; i++) {
        entries[i].key = NIL_VAL;
        entries[i].value = NIL_VAL;
    }
}

bool tableDelete(Table* table, Value key){};

//use NIL_VAL key with an actual value to make a
entry->key = NIL_VAL;


//new function as well
static uint32_t hashValue(Value value) {
    switch (value.type) {
        case VAL_BOOL:
            return AS_BOOL(value) ? 1 : 0;
        case VAL_NIL:
            return 2;
        case VAL_NUMBER: {
            double num = AS_NUMBER(value);
            uint64_t bits;
            memcpy(&bits, &num, sizeof(bits));
            return (uint32_t)(bits ^ (bits >> 32));
        }
        case VAL_OBJ:
            if (IS_STRING(value)) return AS_STRING(value)->hash;
            return 0;
    }
    return 0;
}


