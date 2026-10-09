#include "KingSystem/Physics/Constraint/physFixedCs.h"
#include <Havok/Physics/Constraint/Data/Fixed/hkpFixedConstraintData.h>
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

u32 sub_7100F6D3DC(bool breakable) {
    return sub_7100F6ACF4(breakable) + 0x1c0;
}

FixedCs::~FixedCs() = default;

void FixedCs::sub_7100F6D6D8(const sead::Matrix34f& mtx_a, const sead::Matrix34f& mtx_b) {
    hkTransform frame_a;
    hkTransform frame_b;
    toHkTransform(&frame_a, mtx_a);
    toHkTransform(&frame_b, mtx_b);
    mData->sub_71015F3F90(frame_a, frame_b);
}

}  // namespace ksys::phys

ksys::phys::FixedCs* sub_7100F6D358(sead::Heap* heap) {
    ksys::phys::FixedCs::Param param;
    return ksys::phys::FixedCs::make(param, heap);
}
