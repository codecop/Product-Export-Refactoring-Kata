#include <assert.h>
#include <stdbool.h>
#include "StringBuilder.h"

struct StringBuilder* make_xml()
{
    struct StringBuilder* xml = make_sb();
    sb_append(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    return xml;
}

static bool xml_tag_is_open;

void xml_x(struct StringBuilder* xml)
{
    assert(xml_tag_is_open);

    sb_append(xml, ">");
    xml_tag_is_open = false;
}

void xml_open(struct StringBuilder* xml, const char* name)
{
    if (xml_tag_is_open) {
        xml_x(xml);
    }

    assert(!xml_tag_is_open);
    sb_append(xml, "<");
    sb_append(xml, name);
    xml_tag_is_open = true;
}

void xml_attribute(struct StringBuilder* xml, const char* name, const char* value)
{
    assert(xml_tag_is_open);

    sb_append(xml, " ");
    sb_append(xml, name);
    sb_append(xml, "='");
    sb_append(xml, value);
    sb_append(xml, "'");
}

void xml_text(struct StringBuilder* xml, const char* text)
{
    if (xml_tag_is_open) {
        xml_x(xml);
    }
    assert(!xml_tag_is_open);
    sb_append(xml, text);
}

void xml_close(struct StringBuilder* xml, const char* name)
{
    if (xml_tag_is_open) {
        xml_x(xml);
    }
    assert(!xml_tag_is_open);
    sb_append(xml, "</");
    sb_append(xml, name);
    sb_append(xml, ">");
}

const char* xml_string(struct StringBuilder* xml)
{
    return sb_string(xml);
}

