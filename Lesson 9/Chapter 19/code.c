//
// Created by ojeda on 4/7/2026.
//

//Question 1 changes

typedef struct ObjString {
 Obj obj;
 int length;
 char chars[];
}; ObjString;

ObjString* string = (ObjString*)reallocate(NULL, 0, sizeof(ObjString) + length + 1);



//Question 2 Addition
typedef struct ObjString {
 Obj obj;
 int length;
 bool ownsChars;
 char chars[];
}; ObjString;