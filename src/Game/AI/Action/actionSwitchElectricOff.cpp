#include "Game/AI/Action/actionSwitchElectricOff.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

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
    auto* actor = mActor;
    f32 value = 0.0f;
    if (auto* chemical = actor->getChemicalStuff())
        value = chemical->_1b4 / (*mTargetVol_s / chemical->_58);
    if (*mUseSklAnm_s) {
        const f32 max = actor->getASList()->x_5(1, 0, &ksys::as::ASList::Unk2::sub_710116323C);
        value = sead::Mathf::clamp(value * max, 0.0f, max);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, value);
    }
}

}  // namespace uking::action
