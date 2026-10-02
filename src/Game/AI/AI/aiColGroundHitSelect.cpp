#include "Game/AI/AI/aiColGroundHitSelect.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

ColGroundHitSelect::ColGroundHitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ColGroundHitSelect::~ColGroundHitSelect() = default;

bool ColGroundHitSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool ColGroundHitSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool ColGroundHitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ColGroundHitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isBgGroundHit(mActor, false))
        changeChild("地上", params);
    else
        changeChild("空中", params);
}

void ColGroundHitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ColGroundHitSelect::loadParams_() {
    getStaticParam(&mIsCheckEachFrame_s, "IsCheckEachFrame");
}

void ColGroundHitSelect::calc_() {
    if (!*mIsCheckEachFrame_s || !getCurrentChild()->isChangeable())
        return;

    if (isBgGroundHit(mActor, false)) {
        if (isCurrentChild("空中"))
            changeChild("地上");
    } else {
        if (isCurrentChild("地上"))
            changeChild("空中");
    }
}

}  // namespace uking::ai
