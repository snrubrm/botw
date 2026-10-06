#include "Game/AI/Action/actionExpandSensor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"

namespace uking::action {

ExpandSensor::ExpandSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandSensor::~ExpandSensor() = default;

bool ExpandSensor::init_(sead::Heap* heap) {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
        const f32 radius = capsule->getRadius();
        sead::BoundBox3f aabb;
        capsule->getAabbInLocal(&aabb);
        const f32 half_height = aabb.getHalfSizeY();
        _c8.y = half_height + half_height - radius;
        capsule->getVertices(&_b0, &_bc);
        _40.sub_71010C36A4(1.0f, 1.0f, &sead::Matrix34f::ident, heap, actor);
    }
    return true;
}

void ExpandSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        if (!body->isAddedToWorld())
            body->setTransform(actor->getMtx());
        const s32 type = *mParams.mAtkType_s;
        const s32 attr = *mParams.mAtkAttrType_s;
        const u32 attack_flags = type == 0 ? 0x800 : type == 1 ? 1 : 0x1f01f;
        const u32 attack_flags2 = attr == 2 ? 0x4c : attr == 1 ? 0x4a : 0x49;
        auto* sensor = getActorAttackSensor(actor);
        const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
        sensor->activateAttackSensor(attack_flags, attack_flags2, attack->mPower.ref(),
                                     attack->mImpulseLarge.ref(), 0.0f,
                                     attack->mGuardBreakPower.ref(), 0, -1, false, 1, -1);
        if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
            sead::Matrix34f home_mtx;
            actor->getHomeMtx(&home_mtx);
            _d4 = (_bc - _b0).length();
            _40.sub_71010C38F4(&home_mtx);
            _40.sub_71010C3A1C(capsule->getRadius());
            _40.sub_71010C3B18(_d4);
        }
        sub_710012A154();
    }
    sub_71007A44E4(actor, true);
    mFlags.set(Flag::Changeable);
}

void ExpandSensor::sub_710012A154() {
    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody"))
        sub_71007A2B64(body, nullptr);
    if (!_d8) {
        _40.sub_71010C3C44(2);
        _d8 = true;
    }
    if (auto* chemical = actor->sub_71011D8A44(0)) {
        if (chemical->_c0 != 2)
            chemical->sub_7100D90858(false, 2, false, true, false);
    }
}

void ExpandSensor::sub_710012A680() {
    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody"))
        sub_71007A2D34(body);
    _40.sub_71010C3B18(0.0f);
    _40.sub_71010C3D70(0);
    _d8 = false;
    if (auto* chemical = actor->sub_71011D8A44(0))
        chemical->sub_7100D90B78();
}

void ExpandSensor::leave_() {
    sub_710012A680();
}

void ExpandSensor::loadParams_() {
    getStaticParam(&mParams.mAtkAttrType_s, "AtkAttrType");
    getStaticParam(&mParams.mAtkType_s, "AtkType");
    getStaticParam(&mParams.mOffLength_s, "OffLength");
    getStaticParam(&mParams.mOnLength_s, "OnLength");
}

// NON_MATCHING: the structure and all callees match, but the Matrix34 / Vector3 transforms here are
// scheduled differently (the original keeps the rotated points in a handful of registers and has a 0xf0 byte
// frame; this one needs 0x140).
void ExpandSensor::calc_() {
    auto* actor = mActor;
    auto* main_body = actor->getMainBody();
    sead::Matrix34f mtx;
    if (main_body && main_body->getMotionType() == ksys::phys::MotionType::Dynamic)
        main_body->getTransform(&mtx);
    else
        actor->getHomeMtx(&mtx);

    sead::Matrix34f inverse;
    inverse.setInverse(mtx);

    sead::Vector3f center = mtx * sead::Vector3f(0, -0.5f, 0);
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body);
    if (!capsule)
        return;

    const f32 radius = capsule->getRadius();
    sead::Vector3f from = _b0;
    from.rotate(mtx);
    from += center;
    sead::Vector3f to = _bc + sead::Vector3f(0, radius, 0);
    to.rotate(mtx);
    to += center;

    sead::Vector3f hit_pos;
    if (sub_710072E830(from, to, 0, &hit_pos, nullptr, nullptr, 0.0f)) {
        from.rotate(inverse);
        hit_pos.rotate(inverse);
        to.rotate(inverse);
        f32 ratio = (hit_pos.y - from.y) / (to.y - from.y);
        const sead::Vector3f vertex = _b0;
        capsule->setVertices(vertex, _bc * ratio);
        const f32 length = ratio * _d4;
        _40.sub_71010C38F4(&mtx);
        _40.sub_71010C3A1C(radius);
        _40.sub_71010C3B18(length);
        if (length > *mParams.mOffLength_s) {
            if (length >= *mParams.mOnLength_s)
                sub_710012A154();
        } else {
            sub_710012A680();
        }
    } else {
        capsule->setVertices(_b0, _bc);
        _40.sub_71010C38F4(&mtx);
        _40.sub_71010C3A1C(radius);
        _40.sub_71010C3B18(_d4);
        sub_710012A154();
    }
}

}  // namespace uking::action
