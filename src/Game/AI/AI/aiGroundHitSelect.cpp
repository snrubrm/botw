#include "Game/AI/AI/aiGroundHitSelect.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

GroundHitSelect::GroundHitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GroundHitSelect::~GroundHitSelect() = default;

bool GroundHitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GroundHitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsEnterCheck_s) {
        auto* actor = mActor;
        _48 = actor && (isBgGroundHit(actor, false) || isLandedMaybe(actor, false));
    } else {
        _48 = false;
    }

    if (_48)
        changeChild("接地", params);
    else
        changeChild("通常", params);
}

void GroundHitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GroundHitSelect::loadParams_() {
    getStaticParam(&mIsActionEndEnd_s, "IsActionEndEnd");
    getStaticParam(&mIsEnterCheck_s, "IsEnterCheck");
}

void GroundHitSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (*mIsActionEndEnd_s) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
            return;
        }
        if (isCurrentChild("接地")) {
            changeChild("通常");
            return;
        }
    }

    if (isCurrentChild("通常") && !_48) {
        auto* actor = mActor;
        if (actor && (isBgGroundHit(actor, false) || isLandedMaybe(actor, false)))
            changeChild("接地");
    }

    auto* actor = mActor;
    _48 = actor && (isBgGroundHit(actor, false) || isLandedMaybe(actor, false));
}

}  // namespace uking::ai
