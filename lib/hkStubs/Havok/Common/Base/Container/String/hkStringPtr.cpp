#include <Havok/Common/Base/Container/String/hkStringPtr.h>

hkStringPtr::hkStringPtr() : m_stringAndFlag(nullptr) {}

hkStringPtr::hkStringPtr(const char* string) : m_stringAndFlag(nullptr) {
    set(string);
}

hkStringPtr::hkStringPtr(const char* string, int len) : m_stringAndFlag(nullptr) {
    set(string, len);
}

hkStringPtr::hkStringPtr(const hkStringPtr& strRef) : m_stringAndFlag(nullptr) {
    set(strRef.cString());
}

hkStringPtr& hkStringPtr::operator=(const char* string) {
    set(string);
    return *this;
}

hkStringPtr& hkStringPtr::operator=(const hkStringPtr& strRef) {
    set(strRef.cString());
    return *this;
}

int hkStringPtr::getLength() const {
    const char* string = cString();
    if (string)
        return hkString::strLen(string);
    return 0;
}
