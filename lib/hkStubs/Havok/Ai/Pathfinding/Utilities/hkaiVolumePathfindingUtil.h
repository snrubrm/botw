#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Common/Base/Container/Array/hkArray.h>
#include <Havok/Common/Base/Math/Vector/hkVector4f.h>
#include <Havok/Common/Base/Object/hkReferencedObject.h>

namespace hkaiVolumePathfindingUtil {

// Reflection class "hkaiVolumePathfindingUtilFindPathInput". Its destructor
// 0x7100f83bc8 has the same two arrays as hkaiPathfindingUtil::FindPathInput
// (0x10-byte elements at +0x20, 4-byte elements at +0x38); the remaining fields
// and the real element types are not recovered.
class FindPathInput : public hkReferencedObject {
    HK_DECLARE_CLASS_ALLOCATOR(FindPathInput)
public:
    FindPathInput();
    ~FindPathInput() override;

    /* 0x10 */ hkUint8 _10[0x10];
    /* 0x20 */ hkArray<hkVector4f> m_20;
    /* 0x30 */ hkUint8 _30[8];
    /* 0x38 */ hkArray<hkUint32> m_38;
    /* 0x48 */ hkUint8 _48[0xb0 - 0x48];
};
static_assert(sizeof(FindPathInput) == 0xb0);

}  // namespace hkaiVolumePathfindingUtil
