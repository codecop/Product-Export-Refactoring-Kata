#include <time.h>
#include "StringBuilder.h"

struct StringBuilder* make_xml();
void xml_open(struct StringBuilder* xml, const char* name);
void xml_attribute_s(struct StringBuilder* xml, const char* name, const char* value);
void xml_attribute_l(struct StringBuilder* xml, const char* name, const long value);
void xml_attribute_date(struct StringBuilder* xml, const char* name, const time_t value);
void xml_attribute_d(struct StringBuilder* xml, const char* name, const double value);
void xml_text_s(struct StringBuilder* xml, const char* text);
void xml_text_d(struct StringBuilder* xml, const double value);
void xml_close(struct StringBuilder* xml, const char* name);
const char* xml_string(struct StringBuilder* xml);
