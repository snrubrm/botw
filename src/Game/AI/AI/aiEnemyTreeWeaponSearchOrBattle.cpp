#include "Game/AI/AI/aiEnemyTreeWeaponSearchOrBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyTreeWeaponSearchOrBattle::EnemyTreeWeaponSearchOrBattle(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

EnemyTreeWeaponSearchOrBattle::~EnemyTreeWeaponSearchOrBattle() = default;

bool EnemyTreeWeaponSearchOrBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyTreeWeaponSearchOrBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyTreeWeaponSearchOrBattle::leave_() {
    if (_50.hasProc())
        _80.sub_710070DCC0(&_50, true);
    sub_71005DB3EC(mActor);
}

void EnemyTreeWeaponSearchOrBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mNoSearchDist_s, "NoSearchDist");
}

}  // namespace uking::ai
