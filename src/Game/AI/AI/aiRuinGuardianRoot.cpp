#include "Game/AI/AI/aiRuinGuardianRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"

namespace uking::ai {

RuinGuardianRoot::RuinGuardianRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RuinGuardianRoot::~RuinGuardianRoot() = default;

bool RuinGuardianRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RuinGuardianRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = 0;
}

void RuinGuardianRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: collision body loading is scheduled after accessor initialization.
void RuinGuardianRoot::calc_() {
    auto* actor = mActor;
    if (_48 < *mSweepFrame_s) {
        if (auto* body = actor->getMainBody()) {
            if (auto* info = body->getCollisionInfo()) {
                auto* bodies = info->getCollidingBodies().front();
                info->lock();
                for (; bodies; bodies = info->getCollidingBodies().next(bodies)) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::getCollidedActorMaybe(&accessor, bodies->bodies[1]);
                    if (accessor.hasTag(ksys::act::tags::IsIceMakerBlock))
                        actor->sendMessage(*accessor.getMessageTransceiverId(),
                                           ksys::MessageType(0x8000004), nullptr, true);
                }
                info->unlock();
            }
        }
        ++_48;
    }

    if (actor->getMtx().m[1][1] < *mDropThreshold_s) {
        if (!actor->isWaitRevivalForDrop()) {
            actor->setRevivalFlagForDrop(true);
            actor->createDrops(0, 0);
        }
        if (!actor->checkLinkBasicSig())
            actor->emitBasicSigOn();
    }
}

void RuinGuardianRoot::loadParams_() {
    getStaticParam(&mSweepFrame_s, "SweepFrame");
    getStaticParam(&mDropThreshold_s, "DropThreshold");
}

}  // namespace uking::ai
