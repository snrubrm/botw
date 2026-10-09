#include <Havok/Common/Base/Reflection/hkClassMember.h>

#include <Havok/Common/Base/Reflection/hkClass.h>

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
