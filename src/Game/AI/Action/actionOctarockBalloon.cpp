#include "Game/AI/Action/actionOctarockBalloon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"

namespace uking::action {

inline void OctarockBalloon::applyScale_(ksys::phys::SphereRigidBody* body, f32 scale) {
    body->setTranslate(_184 * scale);
    body->setRadius(_180 * scale);
    body->resetInertiaAndCenterOfMass();
}

OctarockBalloon::OctarockBalloon(const InitArg& arg) : OctarockBalloonBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
OctarockBalloon::~OctarockBalloon() {
    ;
}

bool OctarockBalloon::init_(sead::Heap* heap) {
    return OctarockBalloonBase::init_(heap);
}

void OctarockBalloon::sub_710020ECB0() {
    auto* actor = mActor;
    auto* sensor_body = actor->findPhysicsBodyByName(ksys::act::getStr_EntitySensor().cstr(), "SwapBody");
    auto* main_body = actor->getMainBody();
    if (!main_body || !sensor_body || main_body == sensor_body)
        return;
    sensor_body->setTransform(main_body->getTransform());
    sensor_body->setAngularVelocity(main_body->getAngularVelocity());
    sensor_body->setLinearVelocity(main_body->getLinearVelocity());
    sensor_body->addToWorld();
    if (auto* set = actor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr())) {
        if (set->getRigidBodies().size() >= 1) {
            if (auto* body = set->getRigidBodies()(0)) {
                body->setLinkedRigidBody(nullptr);
                body->setTransform(main_body->getTransform());
                body->setLinkedRigidBody(sensor_body);
            }
        }
    }
    if (auto* body = sub_7100EE5FE4(actor)) {
        body->setLinkedRigidBody(nullptr);
        body->setTransform(main_body->getTransform());
        body->setLinkedRigidBody(sensor_body);
    }
    actor->sub_71011DB364(sensor_body);
    main_body->removeFromWorld();
}

void OctarockBalloon::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710020ECB0();
    OctarockBalloonBase::enter_(params);
    _190 = 0;
    if (auto* sphere = sead::DynamicCast<ksys::phys::SphereRigidBody>(mActor->getMainBody())) {
        _180 = sphere->getRadius();
        _184.set(sphere->getTranslate());
        const f32 scale = *mTargetScale_s;
        if (auto* body = sead::DynamicCast<ksys::phys::SphereRigidBody>(sub_7100EE5FE4(mActor)))
            applyScale_(body, scale);
        if (auto* set = mActor->getRigidBodyByName(ksys::act::getStr_Tgt().cstr())) {
            if (set->getRigidBodies().size() >= 1) {
                if (auto* body = sead::DynamicCast<ksys::phys::SphereRigidBody>(set->getRigidBodies()(0)))
                    applyScale_(body, scale);
            }
        }
    } else {
        _180 = -1.0f;
        _184.set(0.0f, 0.0f, 0.0f);
    }
    if (mStartASName_s.isEmpty()) {
        _190 = 2;
    } else {
        _190 = 1;
        playAS(mStartASName_s.cstr(), false, 0, 0, -1.0f);
    }
    _168.mTimer.reset(sead::Mathf::max(*mStartSignTimer_s, 0.0f));
}

void OctarockBalloon::leave_() {
    OctarockBalloonBase::leave_();
}

void OctarockBalloon::loadParams_() {
    OctarockBalloonBase::loadParams_();
    getStaticParam(&mTargetScale_s, "TargetScale");
    getStaticParam(&mStartSignTimer_s, "StartSignTimer");
    getStaticParam(&mStartASName_s, "StartASName");
    getStaticParam(&mSignASName_s, "SignASName");
}

void OctarockBalloon::calc_() {
    OctarockBalloonBase::calc_();
    auto* actor = mActor;
    if (!(_168.mTimer.value <= sead::Mathf::epsilon()))
        _168.sub_7100D3BCE4();
    if (_190 == 1) {
        auto* body = sead::DynamicCast<ksys::phys::SphereRigidBody>(mActor->getMainBody());
        auto* as_list = actor->getASList();
        if (body && as_list) {
            const f32 target_scale = *mTargetScale_s;
            if (target_scale > 0.0f) {
                f32 scale = target_scale;
                if (!isFinishedAS(0, 0)) {
                    const f32 frame = as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_71011632F8);
                    const f32 duration = as_list->x_5(0, 0, &ksys::as::ASList::Unk2::sub_710116323C);
                    const f32 ratio = sead::Mathf::clamp(frame / duration, 0.0f, 1.0f);
                    scale = ratio * (*mTargetScale_s - 1.0f) + 1.0f;
                }
                applyScale_(body, scale);
            }
        }
        if (isFinishedAS(0, 0))
            _190 = 2;
    }
    if (_190 == 2) {
        if (*mStartSignTimer_s > 0.0f && _168.mTimer.value <= sead::Mathf::epsilon() &&
            !mSignASName_s.isEmpty()) {
            playAS(mSignASName_s.cstr(), false, 0, 0, -1.0f);
            _190 = 3;
        }
    }
}

bool OctarockBalloon::m32() {
    if (sub_71000B89DC()) {
        if (_190 != 1)
            return true;
        const f32 height = mActor->getMtx().m[1][3];
        const f32 limit = _b5 ? *mRemainsHeightLimit_s : *mHeightLimit_s;
        if (height > limit + 10.0f)
            return true;
    }
    if (!(*mStartSignTimer_s > 0.0f) || mSignASName_s.isEmpty())
        return BalloonBase::m32();
    auto* life = mActor->getLife();
    if (life && *life < 1)
        return true;
    if (_190 != 3)
        return false;
    return isFinishedAS(0, 0);
}

}  // namespace uking::action
