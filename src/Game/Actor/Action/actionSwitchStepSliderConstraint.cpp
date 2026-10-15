#include "Game/Actor/Action/actionSwitchStepSliderConstraint.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/Constraint/physSliderCs.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

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
    auto* actor = mActor;
    _d8 = actor->getFieldBodyGroup();
    auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), sUnk_71023c3f28.cstr());
    auto* main_body = actor->getMainBody();
    if (body) {
        body->setRestitutionScale(0.6f);
        ksys::phys::SliderCs::Param param;
        param.body_a = body;
        if (main_body)
            param.body_b = main_body;
        _20 = ksys::phys::SliderCs::make(param, heap);
    }
    return true;
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

// NON_MATCHING: threshold and virtual-function loads are scheduled before the final dot-product add.
void SwitchStepSliderConstraint::calc_() {
    auto* actor = mActor;
    sead::Matrix34f home;
    actor->getHomeMtx(&home);
    const sead::Vector3f axis = home.getBase(1);
    const sead::Vector3f translation = actor->getMtx().getTranslation();
    _94 = translation + axis * *mMinLimit_s;
    _88 = translation + axis * *mMaxLimit_s;
    auto* main_body = actor->getMainBody();
    auto* body = actor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), sUnk_71023c3f28.cstr());
    const sead::Vector3f minimum = _94;
    sead::Vector3f position;
    if (body) {
        body->changeRotation(home, sead::Mathf::epsilon());
        sead::Vector3f impulse(0.0f, *mImpulse_s, 0.0f);
        impulse.rotate(home);
        impulse *= ksys::VFR::instance()->getDeltaFrame();
        m33(body, &impulse, &minimum);
        body->getPosition(&position);
    }
    if (main_body && main_body->getMotionType() == ksys::phys::MotionType::Keyframed)
        main_body->changePositionAndRotation(home, sead::Mathf::epsilon());
    const f32 distance = axis.dot(position - minimum);
    m32(distance - *mSwTh_s);
    sub_710028EA1C(distance);
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

void SwitchStepSliderConstraint::sub_710028EA1C(f32 distance) {
    auto* actor = mActor;
    if (!actor)
        return;
    const f32 length = (_88 - _94).length();
    f32 speed = distance - _d0;
    if (!(speed > 0.0f))
        speed = -speed;
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    if (delta > 0.0f)
        speed /= delta;
    _d0 = distance;
    if (auto* xlink = actor->getXLink())
        if (auto* user = xlink->_50)
            user->setPropertyValue(3, speed * 1000.0f);
    if (!(distance >= 0.001f) || !(length - 0.001f >= distance) || !(speed > 0.0001f)) {
        _c0.fade();
    } else if (!_c0.isActive()) {
        _c0 = ksys::eft::searchAndEmitSLink(actor, "moving", false);
    }
}

void SwitchStepSliderConstraint::sub_710028EE24() {
    if (!mOnASName_s.isEmpty())
        playAS(mOnASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
}

void SwitchStepSliderConstraint::sub_710028EE98() {
    if (!mOffASName_s.isEmpty())
        playAS(mOffASName_s.cstr(), *mIsIgnoreSame_s, *mTargetIdx_s, *mSeqBankIdx_s, -1.0f);
}

void SwitchStepSliderConstraint::applyParams() {
    _d8 = mActor->getFieldBodyGroup();
}

}  // namespace uking::action
