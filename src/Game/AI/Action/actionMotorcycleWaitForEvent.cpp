#include "Game/AI/Action/actionMotorcycleWaitForEvent.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MotorcycleWaitForEvent::MotorcycleWaitForEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleWaitForEvent::~MotorcycleWaitForEvent() = default;

bool MotorcycleWaitForEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleWaitForEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
    if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor)) {
        if (!motorcycle->_f88.isOnBit(20)) {
            motorcycle->sub_7100077830();
            _1c = true;
        }
    }
}

void MotorcycleWaitForEvent::leave_() {
    if (_1c) {
        if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor))
            motorcycle->sub_7100072204();
    }
}

void MotorcycleWaitForEvent::loadParams_() {}

void MotorcycleWaitForEvent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
