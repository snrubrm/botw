#include <Havok/Common/Base/Reflection/hkClass.h>

#include <Havok/Common/Base/Container/String/hkString.h>
#include <Havok/Common/Base/Reflection/hkClassMember.h>
#include <Havok/Common/Base/Reflection/hkCustomAttributes.h>

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

const hkClass* hkClass::getParent() const {
    return m_parent;
}

hkClass* hkClass::getParent() {
    return const_cast<hkClass*>(m_parent);
}

hkBool hkClass::isSuperClass(const hkClass& k) const {
    const hkClass* derived = &k;
    do {
        if (hkString::strCmp(derived->m_name, m_name) == 0)
            return true;
        derived = derived->m_parent;
    } while (derived);
    return false;
}

const hkClass::Flags& hkClass::getFlags() const {
    return m_flags;
}

const hkVariant* hkClass::getAttribute(const char* id) const {
    const hkCustomAttributes* attributes = m_attributes;
    if (attributes) {
        for (int i = 0; i < attributes->m_attributes.m_size; ++i) {
            if (hkString::strCmp(attributes->m_attributes.m_data[i].m_name, id) == 0)
                return &attributes->m_attributes.m_data[i].m_value;
        }
    }
    return nullptr;
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

const hkClassMember& hkClass::getMember(int i) const {
    int index = i - getNumMembers();
    for (const hkClass* klass = this; klass; klass = klass->m_parent) {
        index += klass->m_numDeclaredMembers;
        if (index >= 0)
            return klass->m_declaredMembers[index];
    }
    return *m_declaredMembers;
}

// NON_MATCHING: the inlined lookup duplicates the successful-return block.
hkClassMember& hkClass::getMember(int i) {
    return const_cast<hkClassMember&>(static_cast<const hkClass*>(this)->getMember(i));
}

// NON_MATCHING: the name scan uses different saved registers.
int hkClass::getDeclaredMemberIndexByName(const char* name) const {
    for (int i = 0; i < m_numDeclaredMembers; ++i) {
        if (hkString::strCmp(m_declaredMembers[i].getName(), name) == 0)
            return i;
    }
    return -1;
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

hkBool hkClass::hasVtable() const {
    const hkClass* base = this;
    while (base->m_parent)
        base = base->m_parent;
    return base->m_numImplementedInterfaces != 0;
}

const hkClassMember* hkClass::getMemberByName(const char* name) const {
    for (int i = 0; i < getNumMembers(); ++i) {
        const hkClassMember& member = getMember(i);
        if (hkString::strCmp(member.getName(), name) == 0)
            return &member;
    }
    return nullptr;
}

// NON_MATCHING: the inherited member scan has different loop layout and saved registers.
int hkClass::getMemberIndexByName(const char* name) const {
    int i = 0;
    while (i < getNumMembers()) {
        const hkClassMember& member = getMember(i);
        if (hkString::strCmp(member.getName(), name) == 0)
            return i;
        ++i;
    }
    return -1;
}
