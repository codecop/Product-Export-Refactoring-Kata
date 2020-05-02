#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_BUFFER 1000
static char readBuffer[READ_BUFFER];

static const char* approvals_file_name_for(const char* fullFileName,
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

static const const char* approvals_load(const char* filename)
{
    memset(readBuffer, 0, READ_BUFFER);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return "";
    }
    fread(readBuffer, sizeof(char), READ_BUFFER, file);
    int errorClose = fclose(file);
    if (errorClose) {
        fprintf(stderr, "Could not close %s, error %d\n", filename, errorClose);
    }
    return readBuffer;
}

static void approvals_save(const char* filename, const char* data)
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

static void approvals_delete(const char* filename)
{
    int errorRemove = remove(filename);
    if (errorRemove) {
        fprintf(stderr, "Could not delete %s, error %d\n", filename, errorRemove);
    }
}

const char* approvals_verify(const char* received,
                             const char* fullFileName,
                             const char* testName,
                             const char* extensionNoDot)
{
    const char* receivedName =
        approvals_file_name_for(fullFileName, testName, false, extensionNoDot);
    approvals_save(receivedName, received);

    const char* approvedName =
        approvals_file_name_for(fullFileName, testName, true, extensionNoDot);
    const char* approved = approvals_load(approvedName);

    if (strcmp(approved, received) == 0) {
        /* OK */
        approvals_delete(receivedName);
    }

    free((void*)receivedName);
    free((void*)approvedName);

    return approved;
}
