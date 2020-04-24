struct ModelObject {
    char* id;
    char* (*toString)(void* this);
    void (*saveToDatabase)(void* this);
};
