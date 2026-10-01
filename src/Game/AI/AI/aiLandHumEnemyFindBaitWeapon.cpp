#include "Game/AI/AI/aiLandHumEnemyFindBaitWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LandHumEnemyFindBaitWeapon::LandHumEnemyFindBaitWeapon(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LandHumEnemyFindBaitWeapon::~LandHumEnemyFindBaitWeapon() = default;

void LandHumEnemyFindBaitWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetWeapon_d, "TargetWeapon", -1);
    changeChild("拾う", &pack);
}

bool LandHumEnemyFindBaitWeapon::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void LandHumEnemyFindBaitWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandHumEnemyFindBaitWeapon::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
}

}  // namespace uking::ai
