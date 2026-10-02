#include "Game/AI/Behavior/behaviorSetReceivedImpulseRate.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetReceivedImpulseRate::SetReceivedImpulseRate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetReceivedImpulseRate::~SetReceivedImpulseRate() = default;

bool SetReceivedImpulseRate::m6(sead::Heap* heap) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    actor->_a70 = &_30;
    return true;
}

void SetReceivedImpulseRate::sub_710063E528(ksys::act::Unk_71006dc134* arg) {
    if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
        return;
    if (auto* info = arg->_18) {
        if (info->sub_71007A1F68(1) || info->sub_71007A1F68(2) || info->sub_71007A1F68(4))
            arg->_0 *= *mImpulseRate_s;
    }
}

void SetReceivedImpulseRate::m7() {}

void SetReceivedImpulseRate::m8() {}

void SetReceivedImpulseRate::m9() {}

void SetReceivedImpulseRate::loadParams() {
    getStaticParam(&mImpulseRate_s, "ImpulseRate");
}

}  // namespace uking::behavior
