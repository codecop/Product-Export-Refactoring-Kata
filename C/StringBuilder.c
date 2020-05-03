#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER 16

struct StringBuilder {
    char* buffer;
    size_t bufferLength;
    size_t position;
};

struct StringBuilder* make_sb(void)
{
    struct StringBuilder* this = (struct StringBuilder*)malloc(sizeof(struct StringBuilder));
    this->bufferLength = INITIAL_BUFFER;
    this->buffer = malloc(this->bufferLength);
    this->buffer[0] = '\0';
    this->position = 0;
    return this;
}

static void sb_ensure_size(struct StringBuilder* this, size_t size)
{
    if (this->bufferLength > size) {
        return;
    }

    char* oldBuffer = this->buffer;
    while (this->bufferLength <= size) {
        this->bufferLength *= 2;
    }
    this->buffer = malloc(this->bufferLength);
    memcpy(this->buffer, oldBuffer, this->position + 1);
    free(oldBuffer);
}

void sb_append(struct StringBuilder* this, const char* s)
{
    size_t length = strlen(s);
    sb_ensure_size(this, this->position + length);
    memcpy(this->buffer + this->position, s, length + 1);
    this->position += length;
}

void sb_append_long(struct StringBuilder* this, long l)
{
    size_t length = 10;
    sb_ensure_size(this, this->position + length);
    int written = sprintf(this->buffer + this->position, "%lu", l);
    this->position += written;
}

void sb_append_double(struct StringBuilder* this, double d)
{
    size_t length = 24;
    sb_ensure_size(this, this->position + length);
    int written = sprintf(this->buffer + this->position, "%f", d);
    this->position += written;
}

const char* sb_string(struct StringBuilder* this)
{
    const char* s = this->buffer;
    free(this);
    return s;
}
