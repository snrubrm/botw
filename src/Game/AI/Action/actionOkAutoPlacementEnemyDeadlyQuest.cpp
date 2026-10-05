#include "Game/AI/Action/actionOkAutoPlacementEnemyDeadlyQuest.h"
#include "Game/AI/aiUnk_7100736460.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::action {

OkAutoPlacementEnemyDeadlyQuest::OkAutoPlacementEnemyDeadlyQuest(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OkAutoPlacementEnemyDeadlyQuest::~OkAutoPlacementEnemyDeadlyQuest() = default;

bool OkAutoPlacementEnemyDeadlyQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OkAutoPlacementEnemyDeadlyQuest::loadParams_() {}

bool OkAutoPlacementEnemyDeadlyQuest::oneShot_() {
    if (auto* manager = ksys::map::AutoPlacementMgr::instance()) {
        if (dlc::isPlayingOneHitObliteratorQuest() || manager->_171e68[0] > 0)
            manager->sub_7100659DE0(0, false);
    }
    return true;
}

}  // namespace uking::action
