#include "Game/AI/AI/aiDistanceKeepMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DistanceKeepMove::DistanceKeepMove(const InitArg& arg) : WaitNearTarget(arg) {}

DistanceKeepMove::~DistanceKeepMove() = default;

bool DistanceKeepMove::init_(sead::Heap* heap) {
    return WaitNearTarget::init_(heap);
}

void DistanceKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitNearTarget::enter_(params);
}

void DistanceKeepMove::leave_() {
    WaitNearTarget::leave_();
}

// NON_MATCHING: the direction and parameter pack use separate stack storage.
void DistanceKeepMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("後退")) {
            sub_71005E917C();
            return;
        }
    } else if (child->isChangeable() && isCurrentChild("待機")) {
        const f32 distance = sub_71005E9138();
        const f32 base_distance = *mBaseDist_s;
        const f32 back_offset = *mStartBackDistOffset_s;
        if (base_distance + back_offset + sub_71007320F0(mActor, *mWeaponIdx_s) >= distance) {
            auto* actor = mActor;
            sead::Vector3f direction = actor->getMtx().getTranslation();
            direction -= sub_71005D9330(actor);
            direction.normalize();
            if (!sub_710072FEC4(actor, direction, 3.0f, nullptr, false, nullptr)) {
                ksys::act::ai::InlineParamPack params;
                params.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("後退", &params);
                return;
            }
        }
    }
    WaitNearTarget::calc_();
}

void DistanceKeepMove::loadParams_() {
    WaitNearTarget::loadParams_();
    getStaticParam(&mStartBackDistOffset_s, "StartBackDistOffset");
}

}  // namespace uking::ai
