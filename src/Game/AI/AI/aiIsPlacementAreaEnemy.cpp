#include "Game/AI/AI/aiIsPlacementAreaEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::ai {

IsPlacementAreaEnemy::IsPlacementAreaEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IsPlacementAreaEnemy::~IsPlacementAreaEnemy() = default;

bool IsPlacementAreaEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IsPlacementAreaEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        const int type = *mCheckType_s;
        if (type == 0) {
            if (mgr->auto0(pos, 0)) {
                changeChild("禁止");
                return;
            }
            if (mgr->isNonAutoPlacement(pos, true))
                changeChild("禁止");
            else
                changeChild("許可");
            return;
        }
        if (type == 2) {
            if (mgr->isNonAutoPlacement(pos, true))
                changeChild("禁止");
            else
                changeChild("許可");
            return;
        }
        if (type == 1) {
            if (mgr->auto0(pos, 0))
                changeChild("禁止");
            else
                changeChild("許可");
            return;
        }
    }
    changeChild("許可");
}

void IsPlacementAreaEnemy::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    bool permitted = true;
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        const int type = *mCheckType_s;
        if (type == 0) {
            if (mgr->auto0(pos, 0))
                permitted = false;
            else
                permitted = !mgr->isNonAutoPlacement(pos, true);
        } else if (type == 2) {
            permitted = !mgr->isNonAutoPlacement(pos, true);
        } else if (type == 1) {
            permitted = !mgr->auto0(pos, 0);
        }
    }

    auto* child = getCurrentChild();
    if (isCurrentChild("許可")) {
        if (!permitted && child->isChangeable())
            changeChild("禁止");
    } else if (isCurrentChild("禁止") && permitted && child->isChangeable()) {
        changeChild("許可");
    }
}

bool IsPlacementAreaEnemy::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool IsPlacementAreaEnemy::isFinished() const {
    return getCurrentChild()->isFinished();
}

void IsPlacementAreaEnemy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IsPlacementAreaEnemy::loadParams_() {
    getStaticParam(&mCheckType_s, "CheckType");
}

}  // namespace uking::ai
