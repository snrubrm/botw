#include "Game/AI/AI/aiStalEnemyChasePart.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::ai {

StalEnemyChasePart::StalEnemyChasePart(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyChasePart::~StalEnemyChasePart() = default;

bool StalEnemyChasePart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyChasePart::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (mgr && mgr->isNonAutoPlacement(*mTargetPos_d, true)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("パーツがエリア外", &pack);
    } else if (*mIsCarried_d) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("持たれパーツ追跡", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("通常パーツ追跡", &pack);
    }
}

void StalEnemyChasePart::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyChasePart::loadParams_() {
    getDynamicParam(&mIsCarried_d, "IsCarried");
    getDynamicParam(&mIsCarriedByPlayer_d, "IsCarriedByPlayer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool StalEnemyChasePart::isFinished() const {
    const bool chasing = isCurrentChild("持たれパーツ追跡") || isCurrentChild("通常パーツ追跡");
    if (chasing)
        return ActionBase::isFinished();
    return ActionBase::isFinished() || getCurrentChild()->isFinished();
}

bool StalEnemyChasePart::isChangeable() const {
    if (isCurrentChild("通常パーツ待機"))
        return true;
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
