#include "Game/AI/AI/aiInForceEnemyLostAreaSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::ai {

InForceEnemyLostAreaSelect::InForceEnemyLostAreaSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

InForceEnemyLostAreaSelect::~InForceEnemyLostAreaSelect() = default;

bool InForceEnemyLostAreaSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool InForceEnemyLostAreaSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool InForceEnemyLostAreaSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InForceEnemyLostAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (mgr && (mgr->isNonAutoPlacement(pos, true) ||
                mgr->isNonAutoPlacement(getPlayerPosition(), true))) {
        changeChild("エリア内", params);
    } else {
        changeChild("エリア外", params);
    }
}

void InForceEnemyLostAreaSelect::calc_() {}

void InForceEnemyLostAreaSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InForceEnemyLostAreaSelect::loadParams_() {}

}  // namespace uking::ai
