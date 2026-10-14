#include "Game/AI/Action/actionExpandSensorSlowly.h"
#include <gfx/seadColor.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCapsule.h"

// Native 5A4C8 is the variadic debug-print stub also called by SimpleLiftableDLC.
void sub_710005A4C8(const char*, const sead::Vector3f*, const sead::Color4f*, const char*, ...);

namespace uking::action {

ExpandSensorSlowly::ExpandSensorSlowly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandSensorSlowly::~ExpandSensorSlowly() = default;

bool ExpandSensorSlowly::init_(sead::Heap* heap) {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
        sead::BoundBox3f aabb;
        capsule->getAabbInLocal(&aabb);
        const f32 half_height = aabb.getHalfSizeY();
        _d0.y = half_height + half_height - capsule->getRadius();
        capsule->getVertices(&_b8, &_c4);
        _48.sub_71010C36A4(1.0f, 1.0f, &sead::Matrix34f::ident, heap, actor);
    }
    return true;
}

void ExpandSensorSlowly::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        if (!body->isAddedToWorld())
            body->setTransform(actor->getMtx());
        const s32 type = *mAtkType_s;
        const s32 attr = *mAtkAttrType_s;
        const u32 attack_flags = type == 0 ? 0x800 : type == 1 ? 1 : 0x1f01f;
        const u32 attack_flags2 = attr == 2 ? 0x4c : attr == 1 ? 0x4a : 0x49;
        auto* sensor = getActorAttackSensor(actor);
        const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
        sensor->activateAttackSensor(attack_flags, attack_flags2, attack->mPower.ref(),
                                     attack->mImpulseLarge.ref(), 0.0f,
                                     attack->mGuardBreakPower.ref(), 0, -1, false, 1, -1);
        if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
            _dc = (_c4 - _b8).length();
            sead::Matrix34f home_mtx;
            actor->getHomeMtx(&home_mtx);
            _48.sub_71010C38F4(&home_mtx);
            _48.sub_71010C3A1C(capsule->getRadius());
            _48.sub_71010C3B18(_dc);
        }
        sub_7100059988();
    }
    _e0 = 1.0f;
    _e4 = 1.0f;
    sub_71007A44E4(actor, true);
    mFlags.set(Flag::Changeable);
}

void ExpandSensorSlowly::sub_7100059988() {
    if (_e8)
        return;

    auto* actor = mActor;
    _e8 = true;
    _48.sub_71010C3C44(2);
    if (auto* chemical = actor->sub_71011D8A44(0)) {
        if (chemical->_c0 != 2)
            chemical->sub_7100D90858(false, 2, false, true, false);
    }
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody"))
        sub_71007A2B64(body, nullptr);
}

void ExpandSensorSlowly::sub_710005A348() {
    auto* actor = mActor;
    if (auto* chemical = actor->sub_71011D8A44(0))
        chemical->sub_7100D90B78();
    if (_e8) {
        _e8 = false;
        _48.sub_71010C3B18(0.0f);
        _48.sub_71010C3D70(0);
        if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody"))
            sub_71007A2D34(body);
    }
}

void ExpandSensorSlowly::leave_() {
    sub_710005A348();
}

// NON_MATCHING: the native call snapshots the first endpoint; the direct field argument uses less stack.
void ExpandSensorSlowly::sub_710005A3DC(ksys::phys::CapsuleRigidBody* capsule) {
    const f32 step = *mAtExpandStep_s;
    if (_e4 < _e0) {
        _e4 += step;
        if (_e4 > _e0)
            _e4 = _e0;
    } else {
        _e4 = _e0;
    }
    if (_e8)
        capsule->setVertices(_b8, _c4 * _e4);
    if (_e9) {
        const auto position = mActor->getMtx().getTranslation();
        sub_710005A4C8("", &position, &sead::Color4f::cGreen, "Scale: %.3f/%.3f /%.3f",
                      _e4, _e0, step);
    }
}

void ExpandSensorSlowly::loadParams_() {
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
    getStaticParam(&mAtkType_s, "AtkType");
    getStaticParam(&mOffLength_s, "OffLength");
    getStaticParam(&mOnLength_s, "OnLength");
    getStaticParam(&mAtExpandStep_s, "AtExpandStep");
}

void ExpandSensorSlowly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
