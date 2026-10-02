#include "Game/AI/Action/actionPlayerCutTurn.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerCutTurn::PlayerCutTurn(const InitArg& arg) : PlayerAction(arg) {}

PlayerCutTurn::~PlayerCutTurn() = default;

void PlayerCutTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutTurn::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    if (_68.sub_7101241AD8(0))
        _68.fadeXLink();
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerCutTurn::loadParams_() {
    getStaticParam(&mAttackRatioNSword_s, "AttackRatioNSword");
    getStaticParam(&mAttackRatioLSword_s, "AttackRatioLSword");
    getStaticParam(&mAttackRatioSpear_s, "AttackRatioSpear");
    getStaticParam(&mEnergyAttack_s, "EnergyAttack");
    getStaticParam(&mEnergyChargeStart_s, "EnergyChargeStart");
    getStaticParam(&mRangeDiam_s, "RangeDiam");
    getStaticParam(&mRangeDiamAdd_s, "RangeDiamAdd");
    getStaticParam(&mMaxChargeLvNSword_s, "MaxChargeLvNSword");
    getStaticParam(&mRangeDiamAddNSword_s, "RangeDiamAddNSword");
}

void PlayerCutTurn::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutTurn::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
