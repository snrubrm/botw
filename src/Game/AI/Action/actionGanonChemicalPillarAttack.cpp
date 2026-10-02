#include "Game/AI/Action/actionGanonChemicalPillarAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

GanonChemicalPillarAttack::GanonChemicalPillarAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GanonChemicalPillarAttack::~GanonChemicalPillarAttack() = default;

bool GanonChemicalPillarAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonChemicalPillarAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonChemicalPillarAttack::leave_() {
    sub_71005D74E8(mActor);
}

void GanonChemicalPillarAttack::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinPower_s, "AtMinPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mPillarNum_s, "PillarNum");
    getStaticParam(&mPillarInterval_s, "PillarInterval");
    getStaticParam(&mPillarOffset_s, "PillarOffset");
    getStaticParam(&mAppearPosDist_s, "AppearPosDist");
    getStaticParam(&mAppearPosHeight_s, "AppearPosHeight");
    getStaticParam(&mIgnitionInterval_s, "IgnitionInterval");
    getStaticParam(&mPileScale_s, "PileScale");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getStaticParam(&mCreatePileASName_s, "CreatePileASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonChemicalPillarAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
