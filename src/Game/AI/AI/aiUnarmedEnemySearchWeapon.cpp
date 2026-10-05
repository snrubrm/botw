#include "Game/AI/AI/aiUnarmedEnemySearchWeapon.h"

namespace uking::ai {

UnarmedEnemySearchWeapon::UnarmedEnemySearchWeapon(const InitArg& arg) : UnarmedEnemySearch(arg) {}

UnarmedEnemySearchWeapon::~UnarmedEnemySearchWeapon() = default;

void UnarmedEnemySearchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    _78.clear();
    UnarmedEnemySearch::enter_(params);
}

bool UnarmedEnemySearchWeapon::m34() {
    if (!UnarmedEnemySearch::m34())
        return false;
    _78.clear();
    return true;
}

void UnarmedEnemySearchWeapon::m44() {
    setFailed();
}

void UnarmedEnemySearchWeapon::m45() {
    setFinished();
}

void UnarmedEnemySearchWeapon::m35(const sead::Vector3f& target) {
    sub_71003B8780();
    UnarmedEnemySearch::m35(target);
}

void UnarmedEnemySearchWeapon::leave_() {
    UnarmedEnemySearch::leave_();
}

void UnarmedEnemySearchWeapon::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mSearchDist_s, "SearchDist");
    getStaticParam(&mSearchAng_s, "SearchAng");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getStaticParam(&mLineReachableWeaponDist_s, "LineReachableWeaponDist");
}

}  // namespace uking::ai
