#include "Game/AI/Action/actionSwitchElectricOn.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

SwitchElectricOn::SwitchElectricOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool SwitchElectricOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchElectricOn::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->emitBasicSigOn();
    playAS("On", true, 0, 0, -1.0f);
    if (*mUseSklAnm_s)
        playAS("Charge", true, 1, 0, -1.0f);
}

void SwitchElectricOn::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchElectricOn::loadParams_() {
    getStaticParam(&mElecReq_s, "ElecReq");
    getStaticParam(&mVolReq_s, "VolReq");
    getStaticParam(&mTargetVol_s, "TargetVol");
    getStaticParam(&mMinEnergyRate_s, "MinEnergyRate");
    getStaticParam(&mUseSklAnm_s, "UseSklAnm");
}

void SwitchElectricOn::calc_() {
    auto* actor = mActor;
    f32 value = 0;
    if (auto* chemical = actor->getChemicalStuff()) {
        const f32 energy = chemical->sub_7100D945BC(*mElecReq_s, *mVolReq_s,
                                                    ksys::VFR::instance()->getDeltaFrame());
        if (energy <= *mMinEnergyRate_s)
            mFlags.set(Flag::Changeable);
        value = chemical->_1b4 / (*mTargetVol_s / chemical->_58);
    }
    if (*mUseSklAnm_s) {
        const f32 rate = actor->getASList()->x_5(1, 0, &ksys::as::ASList::Unk2::sub_710116323C);
        value = sead::Mathf::clamp(value * rate, 0.0f, rate);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_7101163298, value);
    }
}

}  // namespace uking::action
