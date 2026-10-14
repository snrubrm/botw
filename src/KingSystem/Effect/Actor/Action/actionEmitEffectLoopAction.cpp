#include "KingSystem/Effect/Actor/Action/actionEmitEffectLoopAction.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/Effect/eftEffect.h"

namespace ksys::eft {

EmitEffectLoopAction::EmitEffectLoopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitEffectLoopAction::~EmitEffectLoopAction() = default;

bool EmitEffectLoopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EmitEffectLoopAction::enter_(ksys::act::ai::InlineParamPack* params) {
    doStuff();
}

void EmitEffectLoopAction::leave_() {
    if (!*mNoFade_d)
        uking::xlink::fade(_d0, -1);
}

void EmitEffectLoopAction::loadParams_() {
    getDynamicParam(&mScale_d, "Scale");
    getDynamicParam(&mX_d, "X");
    getDynamicParam(&mY_d, "Y");
    getDynamicParam(&mZ_d, "Z");
    getDynamicParam(&mRX_d, "RX");
    getDynamicParam(&mRY_d, "RY");
    getDynamicParam(&mRZ_d, "RZ");
    getDynamicParam(&mR_d, "R");
    getDynamicParam(&mG_d, "G");
    getDynamicParam(&mB_d, "B");
    getDynamicParam(&mA_d, "A");
    getDynamicParam(&mOverWrite_d, "OverWrite");
    getDynamicParam(&mNoFade_d, "NoFade");
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mOption_d, "Option");
    getDynamicParam(&mCutChangeReset_d, "CutChangeReset");
}

// NON_MATCHING: saved-handle addressing and create-id load scheduling differ.
void EmitEffectLoopAction::calc_() {
    if (*mCutChangeReset_d && ksys::eft::Effect::instance()->get193e0() == 2) {
        _e0 = _d0;
        doStuff();
        if (ksys::eft::Effect::instance()->get193e0() == 2) {
            _e0.kill();
            _e0.reset();
        }
    }
}

}  // namespace ksys::eft
