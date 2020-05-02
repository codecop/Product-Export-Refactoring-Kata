#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_BUFFER 1000
static char __readBuffer[READ_BUFFER];

const const char* approvals_load(const char* filename)
{
    memset(__readBuffer, 0, READ_BUFFER);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return "";
    }
    fread(__readBuffer, sizeof(char), READ_BUFFER, file);
    int errorClose = fclose(file);
    if (errorClose) {
        fprintf(stderr, "Could not close %s, error %d\n", filename, errorClose);
    }
    return __readBuffer;
}

void approvals_save(const char* filename, const char* data)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Could not create file %s\n", filename);
        return;
    }
    size_t written = fwrite(data, sizeof(char), strlen(data), file);
    if (written != strlen(data)) {
        fprintf(stderr, "Could not write %s, %d instead %d bytes\n", filename,
                strlen(data), written);
    }
    int errorFlush = fflush(file);
    if (errorFlush) {
        fprintf(stderr, "Could not flush %s, error %d\n", filename, errorFlush);
    }
    int errorClose = fclose(file);
    if (errorClose) {
        fprintf(stderr, "Could not close %s, error %d\n", filename, errorClose);
    }
}

const char* approvals_file_name_for(const char* fullFileName,
                                    const char* testName,
                                    bool isApproved,
                                    const char* extensionNoDot)
{
    const char* lastDot = strrchr(fullFileName, '.');
    size_t lengthFileName = 0;
    if (lastDot) {
        lengthFileName = lastDot - fullFileName;
    }
    else {
        lengthFileName = strlen(fullFileName);
    }

    size_t length = 0;
    length += lengthFileName;
    length += 1; /* . */
    length += strlen(testName);
    length += 1; /* . */
    length += 8; /* "approved" or "received" */
    length += 1; /* . */
    length += strlen(extensionNoDot);
    length += 1; /* NULL */
    char* s = (char*)malloc(length);

    char* offset = s;
    strcpy(offset, fullFileName);
    offset += lengthFileName;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, testName);
    offset += strlen(testName);
    strcpy(offset, ".");
    offset += 1;
    if (isApproved) {
        strcpy(offset, "approved");
    }
    else {
        strcpy(offset, "received");
    }
    offset += 8;
    strcpy(offset, ".");
    offset += 1;
    strcpy(offset, extensionNoDot);

    return s;
}

#define verify_xml(xml, file_name)                               \
    if (strcmp(get_approved(__FILE__(file_name)), (xml)) != 0) { \
        save("foo.xml", (xml));                                  \
    }                                                            \
    assert_string_equal(get_approved(__FILE__(file_name)), xml);

/*
 * remove file before run
 * add received and approved file names
 *
 */