#include "Game/AI/Action/actionSwitchStepSliderConstraint.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"

namespace uking::action {

SwitchStepSliderConstraint::SwitchStepSliderConstraint(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SwitchStepSliderConstraint::~SwitchStepSliderConstraint() {
    if (_20) {
        ksys::phys::Constraint::destroy(_20);
        _20 = nullptr;
    }
}

bool SwitchStepSliderConstraint::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchStepSliderConstraint::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchStepSliderConstraint::leave_() {
    if (_20)
        _20->sub_7100F6A074();
}

void SwitchStepSliderConstraint::loadParams_() {
    getStaticParam(&mTargetIdx_s, "TargetIdx");
    getStaticParam(&mSeqBankIdx_s, "SeqBankIdx");
    getStaticParam(&mImpulse_s, "Impulse");
    getStaticParam(&mMinLimit_s, "MinLimit");
    getStaticParam(&mMaxLimit_s, "MaxLimit");
    getStaticParam(&mSwTh_s, "SwTh");
    getStaticParam(&mFriction_s, "Friction");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mOnASName_s, "OnASName");
    getStaticParam(&mOffASName_s, "OffASName");
}

void SwitchStepSliderConstraint::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: the two discarded SLink handles get separate stack slots in the original
void SwitchStepSliderConstraint::m32(f32 value) {
    auto* actor = mActor;
    if (value <= 0.001f) {
        if (!(_a8.mTimer.value <= std::numeric_limits<f32>::epsilon()))
            _a8.sub_7100D3BCE4();
        if (!_e0 && _a8.mTimer.value <= std::numeric_limits<f32>::epsilon()) {
            actor->emitBasicSigOn();
            _e0 = 1;
            ksys::eft::searchAndEmitSLink(actor, "on", false);
            if (!mOnASName_s.isEmpty())
                playAS(mOnASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
        }
    } else if (value >= 0.001f) {
        _a8.mTimer = ksys::Timer(6, 6);
        if (_e0) {
            actor->emitBasicSigOff();
            _e0 = 0;
            ksys::eft::searchAndEmitSLink(actor, "off", false);
            if (!mOffASName_s.isEmpty())
                playAS(mOffASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
        }
    }
}

void SwitchStepSliderConstraint::m9() {
    _d8 = mActor->getFieldBodyGroup();
}

}  // namespace uking::action
