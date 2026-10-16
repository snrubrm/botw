#include "Game/Actor/AI/aiStalEnemyChasePart.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AutoPlacement/AutoPlacementMgr.h"

namespace uking::ai {

StalEnemyChasePart::StalEnemyChasePart(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyChasePart::~StalEnemyChasePart() = default;

bool StalEnemyChasePart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyChasePart::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = uking::AutoPlacementMgr::instance();
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

// 0x710059d270
void StalEnemyChasePart::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("持たれパーツ追跡")) {
            if (*mIsCarriedByPlayer_d) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("プレイヤ持たれパーツ待機", &pack);
            } else {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("持たれパーツ待機", &pack);
            }
        } else if (isCurrentChild("通常パーツ追跡")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("通常パーツ待機", &pack);
        } else {
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("通常パーツ追跡") || isCurrentChild("持たれパーツ追跡")) {
            auto* mgr = uking::AutoPlacementMgr::instance();
            if (mgr && mgr->isNonAutoPlacement(*mTargetPos_d, true)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("パーツがエリア外", &pack);
                return;
            }
        }
        if (isCurrentChild("通常パーツ追跡") && *mIsCarried_d) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("持たれパーツ追跡", &pack);
        } else if (isCurrentChild("持たれパーツ追跡") && !*mIsCarried_d) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("通常パーツ追跡", &pack);
        }
    }

    if (!child->isFinished() && !child->isFailed())
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
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
