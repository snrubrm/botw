#include "Game/AI/AI/aiStole.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

Stole::Stole(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void Stole::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor)
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1);
    changeChild("開く");
}

void Stole::calc_() {}

bool Stole::handleMessage_(const ksys::Message& message) {
    if (message.getType().value != 0x8000024)
        return false;
    if (mActor)
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20000000);
    return true;
}

}  // namespace uking::ai
