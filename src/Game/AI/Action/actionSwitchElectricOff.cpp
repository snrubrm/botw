#include "Game/AI/Action/actionSwitchElectricOff.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SwitchElectricOff::SwitchElectricOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool SwitchElectricOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchElectricOff::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->emitBasicSigOff();
    mFlags.set(Flag::Changeable);
    playAS("Off", true, 0, 0, -1.0f);
    if (*mUseSklAnm_s)
        playAS("Charge", true, 1, 0, -1.0f);
}

void SwitchElectricOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchElectricOff::loadParams_() {
    getStaticParam(&mVolReq_s, "VolReq");
    getStaticParam(&mTargetVol_s, "TargetVol");
    getStaticParam(&mUseSklAnm_s, "UseSklAnm");
}

void SwitchElectricOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
