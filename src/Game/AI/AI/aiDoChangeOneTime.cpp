#include "Game/AI/AI/aiDoChangeOneTime.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

DoChangeOneTime::DoChangeOneTime(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoChangeOneTime::~DoChangeOneTime() = default;

bool DoChangeOneTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DoChangeOneTime::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    ksys::act::enableAllAttClients(actor);
    if (actor->isWaitRevivalForUsed() || actor->checkBasicSig()) {
        _38.x();
        changeChild("On待機");
    } else {
        _38.x();
        changeChild("Off待機");
    }
}

void DoChangeOneTime::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoChangeOneTime::loadParams_() {}

bool DoChangeOneTime::handleMessage_(const ksys::Message& message) {
    return _38.sub_710070A674(message);
}

void DoChangeOneTime::calc_() {
    auto* child = getCurrentChild();
    if (!child->isChangeable() && !child->isFinished() && !child->isFailed())
        return;

    if (!_38._30)
        return;

    if (isCurrentChild("Off待機")) {
        ksys::act::disableAllAttClients(mActor);
        _38.x();
        changeChild("Off起動");
    } else if (isCurrentChild("On待機")) {
        ksys::act::disableAllAttClients(mActor);
        _38.x();
        changeChild("On起動");
    }
}

}  // namespace uking::ai
