#include "Game/AI/AI/aiGuardianMiniBlownOff.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniBlownOff::GuardianMiniBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniBlownOff::~GuardianMiniBlownOff() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
}

bool GuardianMiniBlownOff::init_(sead::Heap* heap) {
    _48 = new (heap) Unk_71023f83e8(mActor, 0x8000021);
    return _48 != nullptr;
}

void GuardianMiniBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100419D88(1.0f);
    changeChild("ふっとび", params);
}

void GuardianMiniBlownOff::calc_() {}

void GuardianMiniBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniBlownOff::loadParams_() {
    getStaticParam(&mRotNeckAngle_s, "RotNeckAngle");
    getStaticParam(&mRotNeckSpeed_s, "RotNeckSpeed");
}

bool GuardianMiniBlownOff::handleMessage_(const ksys::Message& message) {
    if (_50.m2(message) && _50._34._10) {
        setFinished();
        return true;
    }
    return false;
}

}  // namespace uking::ai
