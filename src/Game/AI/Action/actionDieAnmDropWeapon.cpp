#include "Game/AI/Action/actionDieAnmDropWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DieAnmDropWeapon::DieAnmDropWeapon(const InitArg& arg) : DieAnm(arg) {}

DieAnmDropWeapon::~DieAnmDropWeapon() = default;

void DieAnmDropWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    DieAnm::enter_(params);
    sead::Vector3f velocity = sead::Vector3f::ey;
    velocity *= *mWeaponDropSpeedY_s;
    sub_71005D8748(mActor, velocity, true, false, nullptr, false);
}

void DieAnmDropWeapon::loadParams_() {
    DieAnm::loadParams_();
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
}

}  // namespace uking::action
