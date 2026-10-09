#include <Havok/Common/Base/Reflection/hkClass.h>

#include <Havok/Common/Base/Container/String/hkString.h>
#include <Havok/Common/Base/Reflection/hkClassMember.h>

hkClass::hkClass(const char* className, const hkClass* parentClass, int objectSizeInBytes,
                 const hkClass** implementedInterfaces, int numImplementedInterfaces,
                 const hkClassEnum* declaredEnums, int numDeclaredEnums,
                 const hkClassMember* declaredMembers, int numDeclaredMembers,
                 const void* defaults, const hkCustomAttributes* attributes,
                 hkUint32 flags, hkUint32 version)
    : m_name(className), m_parent(parentClass), m_objectSize(objectSizeInBytes),
      m_numImplementedInterfaces(numImplementedInterfaces), m_declaredEnums(declaredEnums),
      m_numDeclaredEnums(numDeclaredEnums), m_declaredMembers(declaredMembers),
      m_numDeclaredMembers(numDeclaredMembers), m_defaults(defaults), m_attributes(attributes),
      m_flags(flags), m_describedVersion(version) {}

const char* hkClass::getName() const {
    return m_name;
}

bool hkClass::equals(const hkClass* other) const {
    if (!other)
        return false;
    if (this == other)
        return true;
    return hkString::strCmp(m_name, other->m_name) == 0;
}

// NON_MATCHING: the parent-chain loop has a separate initial load and null branch.
int hkClass::getNumInterfaces() const {
    int count = m_numImplementedInterfaces;
    for (const hkClass* parent = m_parent; parent; parent = parent->m_parent)
        count += parent->m_numImplementedInterfaces;
    return count;
}

int hkClass::getNumDeclaredInterfaces() const {
    return m_numImplementedInterfaces;
}

// NON_MATCHING: the parent-chain loop has a separate initial load and null branch.
int hkClass::getNumMembers() const {
    int count = m_numDeclaredMembers;
    for (const hkClass* parent = m_parent; parent; parent = parent->m_parent)
        count += parent->m_numDeclaredMembers;
    return count;
}

int hkClass::getNumDeclaredMembers() const {
    return m_numDeclaredMembers;
}

const hkClassMember& hkClass::getDeclaredMember(int i) const {
    return m_declaredMembers[i];
}

int hkClass::getObjectSize() const {
    return m_objectSize;
}

void hkClass::setObjectSize(int size) {
    m_objectSize = size;
}

int hkClass::getDescribedVersion() const {
    return m_describedVersion;
}
