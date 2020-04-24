#ifndef MODEL_OBJECT
#define MODEL_OBJECT

struct ModelObject {
    char* id;
    char* (*toString)(void* this);
    void (*saveToDatabase)(void* this);
};

#endif
