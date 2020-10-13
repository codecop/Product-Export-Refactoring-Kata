#include "StringBuilder.h"

struct StringBuilder* make_xml();
void xml_open(struct StringBuilder* xml, const char* name);
void xml_attribute(struct StringBuilder* xml, const char* name, const char* value);
void xml_text(struct StringBuilder* xml, const char* text);
void xml_close(struct StringBuilder* xml, const char* name);
const char* xml_string(struct StringBuilder* xml);
