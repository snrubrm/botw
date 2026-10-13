#include "Game/AI/Action/actionSwitchStepSliderConstraint.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physSliderCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

static const sead::SafeString sUnk_71023c3f28 = "Button";

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

// NON_MATCHING: Timer reset stores differ, and the switch flag store precedes the parameter loads.
void SwitchStepSliderConstraint::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _a8.mTimer.reset(6.0f);
    sead::Matrix34f home;
    home = actor->getHomeMtxRaw();
    auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), sUnk_71023c3f28.cstr());
    if (body) {
        body->setTransform(home);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityGround);
        body->enableContactLayer(ksys::phys::ContactLayer::EntityGroundRough);
        body->setGravityFactor(0.0f);
        body->addToWorld();
    }
    if (_20 && !(_20->_50 & 1)) {
        auto* main_body = actor->getMainBody();
        _20->sub_7100F71058(sead::Vector3f::zero, sead::Vector3f::zero,
                            home.getBase(1), home.getBase(1), home.getBase(2), home.getBase(2));
        _20->setMinMaxLimit(*mMinLimit_s, *mMaxLimit_s);
        _20->sub_7100F71028(*mFriction_s);
        if (body && main_body)
            _20->sub_7100F6AAA4(body, main_body);
        _20->sub_7100F69FF0();
    }
    _e0 = 0;
    _a0 = *mMaxLimit_s - *mMinLimit_s;
    body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), sUnk_71023c3f28.cstr());
    if (body) {
        sead::Vector3f position;
        body->getPosition(&position);
        _d0 = (position - _94).length();
    }
    m34();
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

void SwitchStepSliderConstraint::m32(f32 value) {
    auto* actor = mActor;
    if (value <= 0.001f) {
        if (!(_a8.mTimer.value <= std::numeric_limits<f32>::epsilon()))
            _a8.sub_7100D3BCE4();
        if (!_e0 && _a8.mTimer.value <= std::numeric_limits<f32>::epsilon()) {
            actor->emitBasicSigOn();
            _e0 = 1;
            ksys::eft::searchAndEmitSLink(actor, "on", false);
            sub_710028EE24();
        }
    } else if (value >= 0.001f) {
        _a8.mTimer = ksys::Timer(6, 6);
        if (_e0) {
            actor->emitBasicSigOff();
            _e0 = 0;
            ksys::eft::searchAndEmitSLink(actor, "off", false);
            sub_710028EE98();
        }
    }
}

void SwitchStepSliderConstraint::m33(ksys::phys::RigidBody* body, const sead::Vector3f* impulse,
                                     const sead::Vector3f* pos) {
    body->applyLinearImpulse(*impulse * body->getTimeFactor());
}

void SwitchStepSliderConstraint::m34() {
    sub_710028EE98();
}

void SwitchStepSliderConstraint::sub_710028EE24() {
    if (!mOnASName_s.isEmpty())
        playAS(mOnASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
}

void SwitchStepSliderConstraint::sub_710028EE98() {
    if (!mOffASName_s.isEmpty())
        playAS(mOffASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
}

void SwitchStepSliderConstraint::m9() {
    _d8 = mActor->getFieldBodyGroup();
}

}  // namespace uking::action
