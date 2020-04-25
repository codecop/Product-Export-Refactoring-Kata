#ifndef MODEL_OBJECT
#define MODEL_OBJECT

struct ModelObject {
    const char* (*getId)(void* this);
    const char* (*toString)(void* this);
    void (*saveToDatabase)(void* this);
};

#endif
