#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "StringBuilder.h"

struct StringBuilder* make_xml()
{
    struct StringBuilder* xml = make_sb();
    sb_append(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    return xml;
}

static bool xml_tag_is_open;

static void xml_finish_open(struct StringBuilder* xml)
{
    assert(xml_tag_is_open);

    sb_append(xml, ">");
    xml_tag_is_open = false;
}

void xml_open(struct StringBuilder* xml, const char* name)
{
    if (xml_tag_is_open) {
        xml_finish_open(xml);
    }
    assert(!xml_tag_is_open);

    sb_append(xml, "<");
    sb_append(xml, name);
    xml_tag_is_open = true;
}

void xml_attribute_s(struct StringBuilder* xml, const char* name, const char* value)
{
    assert(xml_tag_is_open);

    sb_append(xml, " ");
    sb_append(xml, name);
    sb_append(xml, "='");
    sb_append(xml, value);
    sb_append(xml, "'");
}

static const char* make_formatted_double(double d)
{
    char* s = (char*)malloc(sizeof(char[24 + 1]));
    sprintf(s, "%03.2f", d);
    return s;
}

void xml_attribute_d(struct StringBuilder* xml, const char* name, const double value)
{
    const char* formatted_total = make_formatted_double(value);
    xml_attribute_s(xml, name, formatted_total);
    free((void*)formatted_total);
}

void xml_text_s(struct StringBuilder* xml, const char* text)
{
    if (xml_tag_is_open) {
        xml_finish_open(xml);
    }
    assert(!xml_tag_is_open);

    sb_append(xml, text);
}

void xml_text_d(struct StringBuilder* xml, const double value)
{
    const char* formatted = make_formatted_double(value);
    xml_text_s(xml, formatted);
    free((void*)formatted);
}

void xml_close(struct StringBuilder* xml, const char* name)
{
    if (xml_tag_is_open) {
        xml_finish_open(xml);
    }
    assert(!xml_tag_is_open);

    sb_append(xml, "</");
    sb_append(xml, name);
    sb_append(xml, ">");
}

const char* xml_string(struct StringBuilder* xml)
{
    assert(!xml_tag_is_open);

    return sb_string(xml);
}

