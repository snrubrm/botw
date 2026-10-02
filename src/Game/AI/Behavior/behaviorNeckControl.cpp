#include "Game/AI/Behavior/behaviorNeckControl.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::behavior {

NeckControl::NeckControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

NeckControl::~NeckControl() = default;

bool NeckControl::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: regalloc (s8/s9 swapped for the x/z differences)
void NeckControl::m7() {
    if (m14()) {
        sub_71005DB3EC(mActor);
        return;
    }
    if (!*mIsUpdatePos_s)
        return;
    sead::Vector3f target;
    m15(&target);
    if (*mOffsetToTargetDirXZ_s != 0.0f) {
        sead::Vector3f pos;
        sub_71005DB4B8(&pos, mActor);
        sead::Vector3f dir{target.x - pos.x, 0.0f, target.z - pos.z};
        dir.normalize();
        target += dir * *mOffsetToTargetDirXZ_s;
    }
    sub_71005DB068(mActor, target);
}

void NeckControl::m8() {
    sead::Vector3f target;
    m15(&target);
    sub_71005DB068(mActor, target);
}

void NeckControl::m9() {
    sub_71005DB3EC(mActor);
}

// NON_MATCHING: the original computes &mOffsetToTargetDirXZ_s before the first call
void NeckControl::loadParams() {
    getStaticParam(&mIsUpdatePos_s, "IsUpdatePos");
    getStaticParam(&mOffsetToTargetDirXZ_s, "OffsetToTargetDirXZ");
}

}  // namespace uking::behavior
