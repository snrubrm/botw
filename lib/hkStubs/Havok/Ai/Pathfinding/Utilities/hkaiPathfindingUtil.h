#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Math/Vector/hkVector4f.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>

namespace hkaiPathfindingUtil {

// Reflection class names in the image: "hkaiPathfindingUtilFindPathInput",
// "hkaiPathfindingUtilFindPathOutput" and "hkaiPathfindingUtilFindGraphPathInput".
// The member layouts below come from the native constructors 0x710155e7a0 /
// 0x710155e8cc and the destructors 0x7100f7c080 / 0x7100f7c118.
class FindPathInput : public hkReferencedObject {
    HK_DECLARE_CLASS_ALLOCATOR(FindPathInput)
public:
    FindPathInput();
    ~FindPathInput() override;

    /* 0x10 */ hkVector4f m_startPoint;
    /* 0x20 */ hkArray<hkVector4f> m_goalPoints;
    /* 0x30 */ hkUint32 m_startFaceKey;
    // The fields from 0x48 on (agentInfo, searchParameters, buffers) are not modelled;
    // the constructor and the destructor only touch the four members above.
    /* 0x38 */ hkArray<hkUint32> m_goalFaceKeys;
    /* 0x48 */ hkUint8 _48[0xd0 - 0x48];
};
static_assert(sizeof(FindPathInput) == 0xd0);

class FindPathOutput : public hkReferencedObject {
    HK_DECLARE_CLASS_ALLOCATOR(FindPathOutput)
public:
    // Reflected member "pathOut": the destructor frees it with a 0x30-byte element stride.
    // Its fields are not modelled yet.
    struct PathOut {
        hkUint8 _0[0x30];
    };

    FindPathOutput();
    ~FindPathOutput() override;

    /* 0x10 */ hkArray<hkUint32> m_10;
    /* 0x20 */ hkArray<PathOut> m_pathOut;
    // Reflected member "outputParameters" (hkaiAstarOutputParameters); unmodelled.
    /* 0x30 */ hkUint8 _30[0x10];
};
static_assert(sizeof(FindPathOutput) == 0x40);

}  // namespace hkaiPathfindingUtil
