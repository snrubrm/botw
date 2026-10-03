#include "Game/AI/AI/aiIceMakerBlock.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/gameSceneSubsys14.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
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
    ksys::act::ai::Ai::enter_(params);
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
