#include "Game/AI/Action/actionAirOctaFloatBase.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

AirOctaFloatBase::AirOctaFloatBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaFloatBase::~AirOctaFloatBase() = default;

bool AirOctaFloatBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaFloatBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi();
    _44 = 0.0f;
    _1c0 &= ~1;
    _70.setName("Neck");
    _118.setName("Head_2");
    mActor->boneHandleStuff(&_70, false);
    mActor->boneHandleStuff(&_118, false);
}

void AirOctaFloatBase::leave_() {
    mActor->sub_71011DA868(&_70);
    mActor->sub_71011DA868(&_118);
}

void AirOctaFloatBase::loadParams_() {
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mGoalInSuccessEnd_s, "GoalInSuccessEnd");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaFloatBase::calc_() {
    m32();
    sub_7100088400();
    sub_71000885B0();
    sub_71000886B8();
    _40 += ksys::VFR::instance()->getDeltaTime();
}

AirOctaDataMgr* AirOctaFloatBase::sub_7100088DA8() {
    return sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
}

AirOctaDataMgr* AirOctaFloatBase::sub_7100089328() {
    return sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
}

// NON_MATCHING: block layout of the `_44 >= 1.0f` branch and where &_1c0 is computed differ.
bool AirOctaFloatBase::sub_7100088400() {
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
    if (!manager)
        return false;
    const f32 delta_time = ksys::VFR::instance()->getDeltaTime();
    if ((manager->vec_F8 - mActor->getMtx().getTranslation()).length() <= *mGoalDistance_s) {
        _44 += delta_time;
        if (_44 >= 1.0f) {
            _1c0 |= 1;
            if (*mGoalInSuccessEnd_s)
                setFinished();
        }
    } else {
        _44 = 0.0f;
        _1c0 &= ~1;
    }
    return _1c0 & 1;
}

void AirOctaFloatBase::sub_71000885B0() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Vector3f velocity;
    body->getAngularVelocity(&velocity);
    velocity *= 0.65f;
    sead::Vector3f min, max;
    m33(&min, &max);
    velocity.x = sead::Mathf::clamp2(min.x, velocity.x, max.x);
    velocity.y = sead::Mathf::clamp2(min.y, velocity.y, max.y);
    velocity.z = sead::Mathf::clamp2(min.z, velocity.z, max.z);
    body->setAngularVelocity(velocity);
}

void AirOctaFloatBase::m33(sead::Vector3f* min, sead::Vector3f* max) {
    min->set(-3.0f, -3.0f, -3.0f);
    max->set(3.0f, 3.0f, 3.0f);
}

f32 AirOctaFloatBase::m34() {
    return *mAmplitude_s;
}

// NON_MATCHING: register allocation / scheduling of the PID terms (the original spills the velocity components to the
// stack and keeps the target components in registers); structure and arithmetic match.
void AirOctaFloatBase::sub_7100088E38(f32 p1, f32 p2, f32 p3, f32 p4, f32 p5, sead::Vector3f* out,
                                      const sead::Vector3f* target, const sead::Vector3f* pos,
                                      const sead::Vector3f* limit) {
    f32 y = target->y;
    const sead::Vector3f velocity = mActor->getMainBody()->getLinearVelocity();
    auto* lod = mActor->getLodState();
    if (!lod || !lod->mFlags8.isOnBit(7))
        y += std::sin(_40) * m34();

    const f32 dt = ksys::VFR::instance()->getDeltaTime();
    const f32 ey = y - pos->y;
    const f32 ex = target->x - pos->x;
    const f32 ez = target->z - pos->z;
    _48.x += dt * ex;
    _48.y += dt * ey;
    _48.z += dt * ez;
    const f32 inv_dt = 1.0f / dt;
    const f32 dx = inv_dt * (ex - _54.x);
    const f32 dy = inv_dt * (ey - _54.y);
    const f32 dz = inv_dt * (ez - _54.z);
    out->x = ex * p1 - velocity.x * p4;
    out->y = ey * p1 - velocity.y * p4;
    out->z = ez * p1 - velocity.z * p4;
    out->x = _48.x * p2 + out->x;
    out->y = _48.y * p2 + out->y;
    out->z = _48.z * p2 + out->z;
    out->x = dx * p3 + out->x;
    out->y = dy * p3 + out->y;
    out->z = dz * p3 + out->z;
    if (limit) {
        out->x = sead::Mathf::clamp(out->x, -limit->x, limit->x);
        out->y = sead::Mathf::clamp(out->y, -limit->y, limit->y);
        out->z = sead::Mathf::clamp(out->z, -limit->z, limit->z);
        if (p2 > 0.0f) {
            _48 *= p2;
            _48.x = sead::Mathf::clamp(_48.x, -limit->x, limit->x);
            _48.y = sead::Mathf::clamp(_48.y, -limit->y, limit->y);
            _48.z = sead::Mathf::clamp(_48.z, -limit->z, limit->z);
            const f32 inv = 1.0f / p2;
            _48.x = inv * _48.x;
            _48.y = inv * _48.y;
            _48.z = inv * _48.z;
        }
    }
    if (p5 > 0.0f) {
        const f32 length = out->length();
        if (length > p5) {
            const f32 scale = (1.0f / length) * p5;
            out->x = scale * out->x;
            out->y = scale * out->y;
            out->z = scale * out->z;
        }
    }
    _54.x = ex;
    _54.y = ey;
    _54.z = ez;
}

// NON_MATCHING: register naming of one integer translation load only.
void AirOctaFloatBase::m32() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    auto* manager = sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
    if (!manager)
        return;
    const f32 delta_frame = ksys::VFR::instance()->getDeltaFrame();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f impulse;
    sub_7100088E38(1.5f, 0.25f, 0.025f, 0.96f, 20.0f, &impulse, &manager->vec_F8, &pos, nullptr);
    const f32 mass = body->getMass();
    impulse *= mass;
    impulse *= delta_frame;
    body->applyLinearImpulse(impulse);
}

}  // namespace uking::action
