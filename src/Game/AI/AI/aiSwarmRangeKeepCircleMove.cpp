#include "Game/AI/AI/aiSwarmRangeKeepCircleMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SwarmRangeKeepCircleMove::SwarmRangeKeepCircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmRangeKeepCircleMove::~SwarmRangeKeepCircleMove() = default;

bool SwarmRangeKeepCircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmRangeKeepCircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwarmRangeKeepCircleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmRangeKeepCircleMove::loadParams_() {
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mUpdateCircleMoveDistance_s, "UpdateCircleMoveDistance");
}

bool SwarmRangeKeepCircleMove::isFinished() const {
    return ksys::act::ai::Ai::isFinished();
}

// NON_MATCHING: scheduling (the target squares the distance before loading the two params)
bool SwarmRangeKeepCircleMove::isFailed() const {
    if (ActionBase::isFailed())
        return true;
    if (!isChangeable())
        return false;

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const auto& target_pos = sub_71005D9330(mActor);
    const f32 dx = pos.x - target_pos.x;
    const f32 dz = pos.z - target_pos.z;
    const f32 dist = *mBaseDist_s + *mOutDist_s;
    return dx * dx + dz * dz > dist * dist;
}

}  // namespace uking::ai
