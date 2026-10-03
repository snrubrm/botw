#include "Game/AI/AI/aiIceMakerBlock.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"

namespace uking::ai {

IceMakerBlock::IceMakerBlock(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IceMakerBlock::~IceMakerBlock() {
    _78[0] = nullptr;
    _78[1] = nullptr;
    _88 = nullptr;
    _90 = nullptr;
    _98 = nullptr;
}

bool IceMakerBlock::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IceMakerBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    setDamageCallbackTiming(mActor, 4, &_38);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "NPCSensor"))
        body->addToWorld();
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "PlayerSensor"))
        body->addToWorld();
    _14c = 20.0f;
    _148 = 1.0f;
    _144 = 1.0f;
    _a4 = false;
    _a5 = true;
    _a6 = false;
    sub_7100446DA8();
}

void IceMakerBlock::sub_71004473A8() {
    _a4 = true;
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, 1.0f);
    auto* body = mActor->getMainBody();
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBA010(false);
    if (body) {
        body->setGravityFactor(1.0f);
        body->setFlag100000();
        body->setAngularVelocity(sead::Vector3f::zero);
        body->setLinearVelocity(sead::Vector3f::zero);
    }
    for (auto* rigid_body : _78) {
        if (rigid_body)
            rigid_body->removeFromWorld();
    }
}

bool IceMakerBlock::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000b6)
        mActor->sub_71011D0204(0x80);
    else if (message->getType() == 0x80000b7)
        mActor->sub_71011D0228(0x80);
    else if (message->getType() == 0x8000004)
        sub_71004473A8();
    else
        return false;
    return true;
}

void IceMakerBlock::sub_7100447C8C() {
    auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "PlayerSensor");
    if (body && body->getCollisionInfo()) {
        if (_a8 != (body->getCollisionInfo()->getCollidingBodies().size() != 0)) {
            const bool state = !_a8;
            _a8 = state;
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_150._18.mLock);
                _150._18._0 = state;
            }
            _150.sub_710070DBB0(*GameSceneSubsys14::instance()->_180, true);
        }
    }
}

// NON_MATCHING: the original computes `&_150` for the sender call between the payload store and the
// lock release (ours materialises it before the lock)
void IceMakerBlock::leave_() {
    sub_71005DA114(mActor, &_38);
    for (auto* body : _78) {
        if (body && body->isAddedToWorld())
            body->removeFromWorld();
    }
    if (!isActorDeletedOrDeleting() && _a8) {
        _a8 = false;
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_150._18.mLock);
            _150._18._0 = false;
        }
        _150.sub_710070DBB0(*GameSceneSubsys14::instance()->_180, true);
    }
}

void IceMakerBlock::loadParams_() {
    getStaticParam(&mParams.mSubRigidStartOffset_s, "SubRigidStartOffset");
    getStaticParam(&mParams.mSubRigidEndOffset_s, "SubRigidEndOffset");
    getStaticParam(&mParams.mSubRigidExOffset_s, "SubRigidExOffset");
}

}  // namespace uking::ai
