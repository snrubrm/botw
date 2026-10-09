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

hkStringPtr::~hkStringPtr() {
    // Native 158DA80 treats 0/1 as empty tagged states and frees only owned
    // strings. Setter 158D970 allocates writable bytes and stores their pointer + 1.
    const uintptr_t taggedString = uintptr_t(m_stringAndFlag);
    if (taggedString > OWNED_FLAG) {
        if (taggedString & OWNED_FLAG) {
            // Keep the owned allocation address while looking up its heap (158DA80).
            char* ownedString = const_cast<char*>(m_stringAndFlag - OWNED_FLAG);
            hkMemoryRouter::easyFree(hkMemoryRouter::getInstance().heap(), ownedString);
        }
        m_stringAndFlag = nullptr;
    }
}
