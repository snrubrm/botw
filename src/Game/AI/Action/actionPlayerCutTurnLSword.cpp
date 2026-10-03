#include "Game/AI/Action/actionPlayerCutTurnLSword.h"
#include <cstring>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutTurnLSword::PlayerCutTurnLSword(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mEnergyMove_s, 0, 0x70);
}

void PlayerCutTurnLSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutTurnLSword::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c4c.resetBit(5);
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    static_cast<ksys::act::Player*>(mActor)->_1de8 = ksys::Timer(5.0f, 5.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    sub_71005D79AC(player, player->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutTurnLSword::loadParams_() {
    getStaticParam(&mEnergyMove_s, "EnergyMove");
    getStaticParam(&mEnergyLastAttack_s, "EnergyLastAttack");
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
    getStaticParam(&mAccSpeed_s, "AccSpeed");
    getStaticParam(&mDecSpeed_s, "DecSpeed");
    getStaticParam(&mSpAttackRadiusMin_s, "SpAttackRadiusMin");
    getStaticParam(&mSpAttackRadiusMax_s, "SpAttackRadiusMax");
    getStaticParam(&mSpAttackRadiusAdd_s, "SpAttackRadiusAdd");
    getStaticParam(&mSpAttackCheckUnderDist_s, "SpAttackCheckUnderDist");
    getStaticParam(&mSpLargeAttackRadius_s, "SpLargeAttackRadius");
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePowerMin_s, "RumblePowerMin");
    getStaticParam(&mRumblePowerMax_s, "RumblePowerMax");
    getStaticParam(&mEnergyChargeStart_s, "EnergyChargeStart");
}

void PlayerCutTurnLSword::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutTurnLSword::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
