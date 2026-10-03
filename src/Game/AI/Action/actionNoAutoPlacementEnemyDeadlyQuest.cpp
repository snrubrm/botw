#include "Game/AI/Action/actionNoAutoPlacementEnemyDeadlyQuest.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::action {

NoAutoPlacementEnemyDeadlyQuest::NoAutoPlacementEnemyDeadlyQuest(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NoAutoPlacementEnemyDeadlyQuest::~NoAutoPlacementEnemyDeadlyQuest() = default;

bool NoAutoPlacementEnemyDeadlyQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NoAutoPlacementEnemyDeadlyQuest::oneShot_() {
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance())
        mgr->sub_7100659DE0(0, true);
    return ksys::act::ai::Action::oneShot_();
}

void NoAutoPlacementEnemyDeadlyQuest::loadParams_() {}

}  // namespace uking::action
