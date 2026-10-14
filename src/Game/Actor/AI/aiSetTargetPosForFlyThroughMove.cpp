#include "Game/Actor/AI/aiSetTargetPosForFlyThroughMove.h"
#include <cmath>
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::ai {

SetTargetPosForFlyThroughMove::SetTargetPosForFlyThroughMove(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SetTargetPosForFlyThroughMove::~SetTargetPosForFlyThroughMove() = default;

bool SetTargetPosForFlyThroughMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosForFlyThroughMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: the two SafeString temporaries at the end are stored with two str each instead of one stp
void SetTargetPosForFlyThroughMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            if (!child->isFinished()) {
                setFailed();
            } else {
                sub_7100568EA8(&_50);
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_50, "TargetPos", -1);
                changeChild("通過移動", &pack);
            }
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (child->isChangeable() && isCurrentChild("移動")) {
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - *mTargetPos_d;
        if (diff.length() <= *mTargetPosFixDist_s) {
            sub_7100568EA8(&_50);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_50, "TargetPos", -1);
            changeChild("通過移動", &pack);
        }
    }

    const bool is_through = isCurrentChild("通過移動");
    getCurrentChild()->setDynamicParam(is_through ? _50 : *mTargetPos_d, "TargetPos");
}

void SetTargetPosForFlyThroughMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosForFlyThroughMove::loadParams_() {
    getStaticParam(&mTargetPosFixDist_s, "TargetPosFixDist");
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: regalloc and the stack slots of target / hit (swapped). Discarded call: sub_71011EFA54's result is
// unused (the call is in the original).
void SetTargetPosForFlyThroughMove::sub_7100568EA8(sead::Vector3f* out) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const sead::Vector3f& target_pos = *mTargetPos_d;
    sead::Vector3f dir = target_pos;
    dir -= pos;
    dir.normalize();

    sead::Vector3f target = target_pos;
    target += *mThroughDist_s * dir;

    sead::Vector3f hit;
    sead::Vector3f normal;
    if (sub_710072E5F8(pos, target, 0, &hit, &normal, nullptr, 0.0f)) {
        sead::Vector3f tangent;
        ksys::util::sub_71011EFA00(&tangent, dir, normal);
        sead::Vector3f projection;
        ksys::util::sub_71011EFA54(&projection, dir, normal);
        const f32 dist =
            std::sqrt((target - pos).squaredLength() - (hit - pos).squaredLength());
        target = hit + tangent * dist;
    }
    *out = target;
}

}  // namespace uking::ai
