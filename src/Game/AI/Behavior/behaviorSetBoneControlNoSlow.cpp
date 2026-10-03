#include "Game/AI/Behavior/behaviorSetBoneControlNoSlow.h"
#include "Game/AI/aiNoSlowTime.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

SetBoneControlNoSlow::SetBoneControlNoSlow(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetBoneControlNoSlow::~SetBoneControlNoSlow() = default;

bool SetBoneControlNoSlow::m6(sead::Heap* heap) {
    return true;
}

void SetBoneControlNoSlow::m7() {}

// NON_MATCHING: the original keeps the default ratio 1.0f in d8 across the isSlowTimeMaybe() call (fmov s8, #1.0
// before the call); ours materialises it after
void SetBoneControlNoSlow::m8() {
    auto* bone_control = mActor->getBoneControl();
    const f32 ratio = getNoSlowTimeRatio();
    if (bone_control)
        bone_control->sub_7100D82FE8(ratio);
}

void SetBoneControlNoSlow::m9() {
    if (auto* bone_control = mActor->getBoneControl())
        bone_control->sub_7100D82FE8(1.0f);
}

void SetBoneControlNoSlow::loadParams() {}

}  // namespace uking::behavior
