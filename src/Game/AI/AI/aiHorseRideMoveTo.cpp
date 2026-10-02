#include "Game/AI/AI/aiHorseRideMoveTo.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideMoveTo::HorseRideMoveTo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideMoveTo::~HorseRideMoveTo() = default;

bool HorseRideMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("指令", &pack);
    _60.x();
    _98.x();
}

void HorseRideMoveTo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideMoveTo::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool HorseRideMoveTo::handleMessage_(const ksys::Message& message) {
    return _60.m2(message) || _98.m2(message);
}

}  // namespace uking::ai
