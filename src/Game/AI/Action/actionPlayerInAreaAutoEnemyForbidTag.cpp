#include "Game/AI/Action/actionPlayerInAreaAutoEnemyForbidTag.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::action {

PlayerInAreaAutoEnemyForbidTag::PlayerInAreaAutoEnemyForbidTag(const InitArg& arg)
    : ForbidTag(arg) {}

PlayerInAreaAutoEnemyForbidTag::~PlayerInAreaAutoEnemyForbidTag() = default;

bool PlayerInAreaAutoEnemyForbidTag::init_(sead::Heap* heap) {
    if (!ForbidTag::init_(heap))
        return false;
    _58 = false;
    return true;
}

void PlayerInAreaAutoEnemyForbidTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ForbidTag::enter_(params);
}

void PlayerInAreaAutoEnemyForbidTag::leave_() {
    ForbidTag::leave_();
    m33();
}

void PlayerInAreaAutoEnemyForbidTag::loadParams_() {
    ForbidTag::loadParams_();
    getMapUnitParam(&mNonAutoPlacementAnimal_m, "NonAutoPlacementAnimal");
    getMapUnitParam(&mNonAutoPlacementBird_m, "NonAutoPlacementBird");
    getMapUnitParam(&mNonAutoPlacementEnemy_m, "NonAutoPlacementEnemy");
    getMapUnitParam(&mNonAutoPlacementFish_m, "NonAutoPlacementFish");
    getMapUnitParam(&mNonAutoPlacementInsect_m, "NonAutoPlacementInsect");
    getMapUnitParam(&mNonAutoPlacementMaterial_m, "NonAutoPlacementMaterial");
    getMapUnitParam(&mNonEnemySearchPlayer_m, "NonEnemySearchPlayer");
}

void PlayerInAreaAutoEnemyForbidTag::m32() {
    if (_58)
        return;
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (*mNonAutoPlacementAnimal_m)
            mgr->sub_7100659DE0(1, true);
        if (*mNonAutoPlacementBird_m)
            mgr->sub_7100659DE0(4, true);
        if (*mNonAutoPlacementEnemy_m)
            mgr->sub_7100659DE0(0, true);
        if (*mNonAutoPlacementFish_m)
            mgr->sub_7100659DE0(3, true);
        if (*mNonAutoPlacementInsect_m)
            mgr->sub_7100659DE0(2, true);
        if (*mNonAutoPlacementMaterial_m)
            mgr->sub_7100659DE0(5, true);
        if (*mNonEnemySearchPlayer_m)
            mgr->sub_7100659DE0(6, true);
    }
    _58 = true;
}

void PlayerInAreaAutoEnemyForbidTag::m33() {
    if (!_58)
        return;
    if (auto* mgr = ksys::map::AutoPlacementMgr::instance()) {
        if (*mNonAutoPlacementAnimal_m)
            mgr->sub_7100659DE0(1, false);
        if (*mNonAutoPlacementBird_m)
            mgr->sub_7100659DE0(4, false);
        if (*mNonAutoPlacementEnemy_m)
            mgr->sub_7100659DE0(0, false);
        if (*mNonAutoPlacementFish_m)
            mgr->sub_7100659DE0(3, false);
        if (*mNonAutoPlacementInsect_m)
            mgr->sub_7100659DE0(2, false);
        if (*mNonAutoPlacementMaterial_m)
            mgr->sub_7100659DE0(5, false);
        if (*mNonEnemySearchPlayer_m)
            mgr->sub_7100659DE0(6, false);
    }
    _58 = false;
}

void PlayerInAreaAutoEnemyForbidTag::calc_() {
    ForbidTag::calc_();
}

}  // namespace uking::action
