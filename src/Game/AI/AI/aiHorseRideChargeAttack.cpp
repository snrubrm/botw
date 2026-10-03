#include "Game/AI/AI/aiHorseRideChargeAttack.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideChargeAttack::HorseRideChargeAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideChargeAttack::~HorseRideChargeAttack() = default;

bool HorseRideChargeAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideChargeAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _98 = false;
    _9c = ksys::Timer(8, 8);
    sub_710043EFAC();
}

void HorseRideChargeAttack::sub_710043EFAC() {
    _60.x();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("指令", &pack);
}

void HorseRideChargeAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideChargeAttack::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackableAngle_s, "AttackableAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool HorseRideChargeAttack::handleMessage_(const ksys::Message* message) {
    return _60.m2(*message);
}

}  // namespace uking::ai
