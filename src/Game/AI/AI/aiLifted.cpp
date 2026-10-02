#include "Game/AI/AI/aiLifted.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
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
    ksys::act::ai::Ai::leave_();
}

void Lifted::loadParams_() {
    getStaticParam(&mIsGetItem_s, "IsGetItem");
}

}  // namespace uking::ai
