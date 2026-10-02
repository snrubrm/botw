#include "Game/AI/AI/aiRemainsWindBatteryRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RemainsWindBatteryRoot::RemainsWindBatteryRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWindBatteryRoot::~RemainsWindBatteryRoot() = default;

bool RemainsWindBatteryRoot::init_(sead::Heap* heap) {
    auto* actor = mActor;
    if (actor->getModel()) {
        _48.search(actor->getModel(), "Head");
        _80.search(actor->getModel(), "Neck");
    }
    return true;
}

void RemainsWindBatteryRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWindBatteryRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWindBatteryRoot::loadParams_() {}

}  // namespace uking::ai
