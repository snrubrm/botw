#include "Game/AI/AI/aiAncientNecklaceBall.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

// Re-enables the main body of the ball in the physics system (and the "Chemical" body); with
// `restore_groups` also the system group handlers.
void AncientNecklaceBall::sub_7100301D90(bool restore_groups) {
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;
    if (auto* body = mActor->getMainBody()) {
        physics->sub_7100FBAF18(body);
        if (!body->isAddedToWorld()) {
            body->addToWorld();
            physics->sub_7100FC012C(nullptr);
        }
        body->setMaxAngularVelocity(_12c);
        body->resetFlag1000000();
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
        sead::Vector3f position;
        mActor->getMtx().getTranslation(position);
        body->setPosition(position);
        sead::Vector3f velocity = body->getLinearVelocity();
        if (velocity.length() > 10.0f) {
            const f32 length = velocity.length();
            if (length > 0.0f)
                velocity *= 10.0f / length;
            body->setLinearVelocity(velocity);
        }
        mActor->nullsub_4649();
    }
    if (restore_groups) {
        physics->sub_7100FBDFA4(physics->get178(0));
        physics->sub_7100FBDFA4(physics->get178(1));
    }
    if (auto* set = physics->findBodyByName("Chemical")) {
        if (auto* body = set->getRigidBodies()[0]) {
            if (!body->isAddedToWorld())
                body->addToWorld();
        }
    }
}

AncientNecklaceBall::AncientNecklaceBall(const InitArg& arg) : AncientNecklaceBallBase(arg) {}

AncientNecklaceBall::~AncientNecklaceBall() = default;

bool AncientNecklaceBall::init_(sead::Heap* heap) {
    if (!AncientNecklaceBallBase::init_(heap))
        return false;

    if (auto* body = mActor->getMainBody())
        _12c = body->getMaxAngularVelocity();
    _140._18.y(mActor);
    return true;
}

void AncientNecklaceBall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mGiantNecklaceActiveSaveFlag_m.isEmpty())
        ksys::gdt::setBoolByKey(true, mGiantNecklaceActiveSaveFlag_m);
    _120 = ksys::Timer(1.0f, 1.0f, 0.0f);
    AncientNecklaceBallBase::enter_(params);
}

void AncientNecklaceBall::leave_() {
    if (isCurrentChild("吊るす")) {
        if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
            weapon->m175(sead::Vector3f::zero, false, false, nullptr, false);
            weapon->m199();
            sub_7100301D90(true);
        }
    }
    AncientNecklaceBallBase::leave_();
    if (!mGiantNecklaceActiveSaveFlag_m.isEmpty())
        ksys::gdt::setBoolByKey(false, mGiantNecklaceActiveSaveFlag_m);
}

void AncientNecklaceBall::calc_() {
    if (isCurrentChild("吊るす")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed() || _170._30) {
            if (_170._38.mLink.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_170._38.mLink, &accessor);
                sead::Vector3f position;
                accessor.getMtxPos(&position);
                sead::Vector3f from;
                mActor->getMtx().getTranslation(from);
                sead::Vector3f hit;
                if (sub_710072EB10(from, position, ksys::phys::RayCast::NormalCheckingMode::_1,
                                  mActor, &hit, nullptr, nullptr, 0.0f)) {
                    _120.reset(3.0f);
                    sub_7100301D90(false);
                    auto* actor = mActor;
                    if (auto* physics = actor->getPhysics()) {
                        sead::Matrix34f matrix = actor->getMtx();
                        matrix.setTranslation(position);
                        physics->setMtxAndScale(matrix, false, false, actor->getScale().x);
                    }
                } else {
                    sub_7100301D90(true);
                }
            } else {
                sub_7100301D90(true);
            }
            _170.x();
            SimpleLiftable::sub_710056E2B4();
            return;
        }
    }
    AncientNecklaceBallBase::calc_();
    _120.update();
    if (_120.value <= sead::Mathf::epsilon()) {
        _120.reset(1.0f, 0.0f);
        if (auto* physics = mActor->getPhysics()) {
            physics->sub_7100FBDFA4(physics->get178(0));
            physics->sub_7100FBDFA4(physics->get178(1));
        }
    }
}

void AncientNecklaceBall::loadParams_() {
    AncientNecklaceBallBase::loadParams_();
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mGrabNodeIndex_m, "GrabNodeIndex");
    getMapUnitParam(&mGiantNecklaceActiveSaveFlag_m, "GiantNecklaceActiveSaveFlag");
}

bool AncientNecklaceBall::handleMessage_(const ksys::Message* message) {
    if (_170.m2(*message))
        return true;
    return AncientNecklaceBallBase::handleMessage_(message);
}

// NON_MATCHING: message receiver address scheduling differs.
void AncientNecklaceBall::m37() {
    if (auto* weapon = sead::DynamicCast<act::Weapon>(mActor)) {
        weapon->m175(sead::Vector3f::zero, false, false, nullptr, false);
        weapon->m199();
    }
    if (auto* bind = mActor->getModelBindInfo())
        _140.sub_710070DE98(bind->sub_7100D3C5E0(mActor), true);
    sub_7100301D90(true);
}

bool AncientNecklaceBall::m36() {
    if (SimpleLiftable::m36())
        return true;
    return isCurrentChild("吊るす");
}

}  // namespace uking::ai

// Defined in this TU in the original (inlined into AncientNecklaceBall::handleMessage_).
bool Unk_71023d4c08::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000ab)
        return false;

    auto* payload = static_cast<Unk_71023d4bb0_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}
