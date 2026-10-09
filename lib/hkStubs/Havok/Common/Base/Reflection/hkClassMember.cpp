#include <Havok/Common/Base/Reflection/hkClassMember.h>

int hkClassMember::getCstyleArraySize() const {
    return m_cArraySize;
}

const hkClass* hkClassMember::getClass() const {
    return m_class;
}

const hkClass& hkClassMember::getStructClass() const {
    return *m_class;
}

const hkClassEnum& hkClassMember::getEnumClass() const {
    return *m_enum;
}
