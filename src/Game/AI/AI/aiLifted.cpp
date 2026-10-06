#include "Game/AI/AI/aiLifted.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

Lifted::Lifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}


void Lifted::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    _48.x();
    auto* actor = mActor;
    if (auto* body = actor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    _44 = false;
    ksys::act::disableAllAttClients(actor);
    if (!isRootAiParamINot5() &&
        (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) ||
         sub_71005DC444(actor))) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
        changeChild("所持");
        return;
    }
    changeChild("待機");
}

void Lifted::leave_() {
    auto* actor = mActor;
    actor->resetConnectedCalcParent(false);
    sub_71005DC5DC(actor);
    if (*mIsGetItem_s) {
        ksys::act::enableAttClient(actor, "Catch");
        ksys::act::enableAttClient(actor, "Pick");
        ksys::act::enableAttClient(actor, "NoticeDo");
        ksys::act::enableAttClient(actor, "AutoAim");
        ksys::act::enableAttClient(actor, "NameBalloon");
    } else {
        ksys::act::enableAllAttClients(actor);
    }
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    if (auto* physics = actor->getPhysics())
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_800);
}

void Lifted::loadParams_() {
    getStaticParam(&mIsGetItem_s, "IsGetItem");
}

// NON_MATCHING: same code; the original shares one `return true` block between both branches, ours tail-duplicates it.
bool Lifted::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000002) {
        auto* actor = mActor;
        actor->resetConnectedCalcParent(false);
        if (isCurrentChild("所持")) {
            if (auto* physics = actor->getPhysics())
                physics->getFlags().set(ksys::phys::InstanceSet::Flag::_800);
            changeChild("待機");
            setFinished();
        }
        return true;
    }

    if (isCurrentChild("投擲")) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
        if (!parent && !_48._30)
            return _48.m2(*message);
    }
    return false;
}

}  // namespace uking::ai
