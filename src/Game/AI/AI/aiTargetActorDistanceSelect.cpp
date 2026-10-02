#include "Game/AI/AI/aiTargetActorDistanceSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

TargetActorDistanceSelect::TargetActorDistanceSelect(const InitArg& arg)
    : TargetDistanceSelect(arg) {}

TargetActorDistanceSelect::~TargetActorDistanceSelect() = default;

bool TargetActorDistanceSelect::init_(sead::Heap* heap) {
    return TargetDistanceSelect::init_(heap);
}

void TargetActorDistanceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetDistanceSelect::enter_(params);
}

void TargetActorDistanceSelect::leave_() {
    TargetDistanceSelect::leave_();
}

void TargetActorDistanceSelect::loadParams_() {
    TargetDistanceSelect::loadParams_();
}

// NON_MATCHING: identical instructions, but ours keeps &accessor in a callee-saved register (x20) for the destructor
// call while the original recomputes `sp + 8` at the join
float TargetActorDistanceSelect::m34() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&sub_71005D94AC(mActor), &accessor)) {
        const sead::Vector3f target_pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - target_pos;
        return diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
    }
    return TargetDistanceSelect::m34();
}

void TargetActorDistanceSelect::calc_() {
    if (!sub_71005D94AC(mActor).hasProc())
        setFailed();
    TargetDistanceSelect::calc_();
}

}  // namespace uking::ai
