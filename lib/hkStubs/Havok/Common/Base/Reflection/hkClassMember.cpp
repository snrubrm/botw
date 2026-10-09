#include <Havok/Common/Base/Reflection/hkClassMember.h>

#include <Havok/Common/Base/Reflection/hkClass.h>
#include <Havok/Common/Base/Container/String/hkString.h>
#include <Havok/Common/Base/Reflection/hkCustomAttributes.h>

namespace {

// Native 253AEB8 has 36 contiguous 24-byte records, including TYPE_MAX.
// Full consumers 1587B14 / 1587BF8 / 1587CE4 read their size/alignment fields.
const hkClassMember::TypeProperties sUnk_710253AEB8[] = {
    {hkClassMember::TYPE_VOID, "void", -1, -1},
    {hkClassMember::TYPE_BOOL, "hkBool", 1, 1},
    {hkClassMember::TYPE_CHAR, "hkChar", 1, 1},
    {hkClassMember::TYPE_INT8, "hkInt8", 1, 1},
    {hkClassMember::TYPE_UINT8, "hkUint8", 1, 1},
    {hkClassMember::TYPE_INT16, "hkInt16", 2, 2},
    {hkClassMember::TYPE_UINT16, "hkUint16", 2, 2},
    {hkClassMember::TYPE_INT32, "hkInt32", 4, 4},
    {hkClassMember::TYPE_UINT32, "hkUint32", 4, 4},
    {hkClassMember::TYPE_INT64, "hkInt64", 8, 8},
    {hkClassMember::TYPE_UINT64, "hkUint64", 8, 8},
    {hkClassMember::TYPE_REAL, "hkReal", 4, 4},
    {hkClassMember::TYPE_VECTOR4, "hkVector4", 16, 16},
    {hkClassMember::TYPE_QUATERNION, "hkQuaternion", 16, 16},
    {hkClassMember::TYPE_MATRIX3, "hkMatrix3", 48, 16},
    {hkClassMember::TYPE_ROTATION, "hkRotation", 48, 16},
    {hkClassMember::TYPE_QSTRANSFORM, "hkQsTransform", 48, 16},
    {hkClassMember::TYPE_MATRIX4, "hkMatrix4", 64, 16},
    {hkClassMember::TYPE_TRANSFORM, "hkTransform", 64, 16},
    {hkClassMember::TYPE_ZERO, "hkZero", -1, -1},
    {hkClassMember::TYPE_POINTER, "hkPointer", 8, 8},
    {hkClassMember::TYPE_FUNCTIONPOINTER, "hkFunctionPointer", 8, 8},
    {hkClassMember::TYPE_ARRAY, "hkArray", 16, 8},
    {hkClassMember::TYPE_INPLACEARRAY, "hkInplaceArray", -1, -1},
    {hkClassMember::TYPE_ENUM, "hkEnum", -1, -1},
    {hkClassMember::TYPE_STRUCT, "hkStruct", -1, -1},
    {hkClassMember::TYPE_SIMPLEARRAY, "hkSimpleArray", 16, 8},
    {hkClassMember::TYPE_HOMOGENEOUSARRAY, "hkHomogeneousArray", 24, 8},
    {hkClassMember::TYPE_VARIANT, "hkVariant", 16, 8},
    {hkClassMember::TYPE_CSTRING, "char*", 8, 8},
    {hkClassMember::TYPE_ULONG, "hkUlong", 8, 8},
    {hkClassMember::TYPE_FLAGS, "hkFlags", -1, -1},
    {hkClassMember::TYPE_HALF, "hkHalf", 2, 2},
    {hkClassMember::TYPE_STRINGPTR, "hkStringPtr", 8, 8},
    {hkClassMember::TYPE_RELARRAY, "hkRelArray", 4, 2},
    {hkClassMember::TYPE_MAX, "hkTypeMax", -1, -1},
};

}  // namespace

const hkClassMember::TypeProperties& hkClassMember::getClassMemberTypeProperties(Type type) {
    return sUnk_710253AEB8[type];
}

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

const hkVariant* hkClassMember::getAttribute(const char* id) const {
    const hkCustomAttributes* attributes = m_attributes;
    if (attributes) {
        for (int i = 0; i < attributes->m_attributes.m_size; ++i) {
            if (hkString::strCmp(attributes->m_attributes.m_data[i].m_name, id) == 0)
                return &attributes->m_attributes.m_data[i].m_value;
        }
    }
    return nullptr;
}

// NON_MATCHING: the enum/flags guards combine and the type branches use different register allocation.
int hkClassMember::getArrayMemberSize() const {
    switch (m_subtype) {
    case TYPE_ENUM:
    case TYPE_FLAGS:
        return -1;
    case TYPE_STRUCT:
        return m_class->getObjectSize();
    default:
        return getClassMemberTypeProperties(m_subtype).m_size;
    }
}

// NON_MATCHING: scalar and enum array-size branches merge and use different result registers.
int hkClassMember::getSizeInBytes() const {
    switch (m_type) {
    case TYPE_BOOL:
    case TYPE_CHAR:
    case TYPE_INT8:
    case TYPE_UINT8:
    case TYPE_INT16:
    case TYPE_UINT16:
    case TYPE_INT32:
    case TYPE_UINT32:
    case TYPE_INT64:
    case TYPE_UINT64:
    case TYPE_REAL:
    case TYPE_VECTOR4:
    case TYPE_QUATERNION:
    case TYPE_MATRIX3:
    case TYPE_ROTATION:
    case TYPE_QSTRANSFORM:
    case TYPE_MATRIX4:
    case TYPE_TRANSFORM:
    case TYPE_POINTER:
    case TYPE_FUNCTIONPOINTER:
    case TYPE_ARRAY:
    case TYPE_SIMPLEARRAY:
    case TYPE_HOMOGENEOUSARRAY:
    case TYPE_VARIANT:
    case TYPE_CSTRING:
    case TYPE_ULONG:
    case TYPE_HALF:
    case TYPE_STRINGPTR:
    case TYPE_RELARRAY:
        return getClassMemberTypeProperties(m_type).m_size * (m_cArraySize ? m_cArraySize : 1);
    case TYPE_ENUM:
    case TYPE_FLAGS:
        return getClassMemberTypeProperties(m_subtype).m_size * (m_cArraySize ? m_cArraySize : 1);
    case TYPE_STRUCT: {
        const int numElements = m_cArraySize ? m_cArraySize : 1;
        return m_class->getObjectSize() * numElements;
    }
    default:
        return -1;
    }
}

int hkClassMember::getAlignment() const {
    Type type = m_type;
    if (type == TYPE_ENUM || type == TYPE_FLAGS)
        type = m_subtype;
    int alignment = 1;
    if (type == TYPE_STRUCT) {
        for (int i = 0; i < m_class->getNumMembers(); ++i) {
            if (m_class->getMember(i).getAlignment() > alignment)
                alignment = m_class->getMember(i).getAlignment();
        }
    } else {
        alignment = getClassMemberTypeProperties(type).m_align;
    }
    if (m_flags.anyIsSet(ALIGN_8 | ALIGN_16 | ALIGN_32)) {
        int forcedAlignment = m_flags.anyIsSet(ALIGN_32) ? 32 :
                              m_flags.anyIsSet(ALIGN_16) ? 16 : 8;
        if (forcedAlignment > alignment)
            alignment = forcedAlignment;
    }
    return alignment;
}
