#include "Game/AI/Behavior/behaviorSwarmPatternMovingSphere.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actSwarm.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SwarmPatternMovingSphere::SwarmPatternMovingSphere(const InitArg& arg) : SwarmPatternBase(arg) {}

SwarmPatternMovingSphere::~SwarmPatternMovingSphere() = default;

bool SwarmPatternMovingSphere::m6(sead::Heap* heap) {
    return SwarmPatternBase::m6(heap);
}

// NON_MATCHING: same arithmetic (Matrix33 makeR / setMul, three random jitters, sin / cos order); the original spills the timer
// address and keeps the axis / base vectors in different registers, so the register allocation and the operand scheduling differ
void SwarmPatternMovingSphere::m7() {
    SwarmPatternBase::m7();
    _60.update();
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm)
        return;

    const s32 num = *mUseSubActorNum_s;
    const f32 num_f = num;
    const f32 cycle_speed = *mCycleSpeed_s;
    const f32 radius = *mRadius_s;
    for (s32 i = 0; i < num; ++i) {
        const f32 base_angle = i * sead::Mathf::pi2() / num_f;
        sead::Vector3f axis = sead::Vector3f::ey;
        ksys::util::sub_71011EF070(&axis, base_angle);
        const f32 angle = f32((i & 1) * 2 - 1) * (base_angle + cycle_speed * _60.value);
        const sead::Vector3f rot = axis * angle;
        sead::Matrix33f rot_mtx;
        rot_mtx.makeR(rot);
        const sead::Vector3f pos = sead::Vector3f::ez * radius;
        sead::Vector3f result;
        result.setMul(rot_mtx, pos);
        result.x += sead::GlobalRandom::instance()->getF32Range(-0.1f, 0.1f);
        result.y += sead::GlobalRandom::instance()->getF32Range(-0.1f, 0.1f);
        result.z += sead::GlobalRandom::instance()->getF32Range(-0.1f, 0.1f);
        if (auto* unit = swarm->_14c8[i])
            unit->_6c = result;
    }
}

void SwarmPatternMovingSphere::m8() {
    SwarmPatternBase::m8();
    if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
        for (s32 i = *mUseSubActorNum_s; i < swarm->_14c8.size(); ++i) {
            if (auto* unit = swarm->_14c8[i]) {
                unit->_6c = sead::Vector3f::zero;
                unit->sub_71002DAA98();
            }
        }
    }
    _60 = ksys::Timer(0.0f, 0.0f, 1.0f);
}

void SwarmPatternMovingSphere::m9() {
    if (mActor->getActorFlags2().isOff(ksys::act::Actor::ActorFlag2::Alive)) {
        if (auto* swarm = sead::DynamicCast<act::Swarm>(mActor)) {
            for (s32 i = *mUseSubActorNum_s; i < swarm->_14c8.size(); ++i) {
                if (auto* unit = swarm->_14c8[i])
                    unit->sub_71002DAA78();
            }
        }
    }
    SwarmPatternBase::m9();
}

void SwarmPatternMovingSphere::loadParams() {
    SwarmPatternBase::loadParams();
    getStaticParam(&mUseSubActorNum_s, "UseSubActorNum");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mCycleSpeed_s, "CycleSpeed");
}

void SwarmPatternMovingSphere::m14(f32 value, act::Swarm* swarm) {
    swarm->_1628 = 2;
    swarm->_162c = 2;
    swarm->_1620 = value;
}

}  // namespace uking::behavior
