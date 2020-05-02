extern const char* approvals_verify(const char* received,
                                    const char* fullFileName,
                                    const char* testName,
                                    const char* extensionNoDot);

#define verify_xml(xml, testName)                                                \
    const char* __approved = approvals_verify((xml), __FILE__, testName, "xml"); \
    assert_string_equal(__approved, (xml));
