#include "Game/AI/Action/actionMotorcycleWaitUntilFellOver.h"
#include "Game/Actor/actMotorcycle.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MotorcycleWaitUntilFellOver::MotorcycleWaitUntilFellOver(const InitArg& arg)
    : MotorcycleWait(arg) {}

MotorcycleWaitUntilFellOver::~MotorcycleWaitUntilFellOver() = default;

bool MotorcycleWaitUntilFellOver::init_(sead::Heap* heap) {
    return MotorcycleWait::init_(heap);
}

void MotorcycleWaitUntilFellOver::enter_(ksys::act::ai::InlineParamPack* params) {
    MotorcycleWait::enter_(params);
}

void MotorcycleWaitUntilFellOver::leave_() {
    MotorcycleWait::leave_();
}

void MotorcycleWaitUntilFellOver::loadParams_() {
    MotorcycleWait::loadParams_();
}

void MotorcycleWaitUntilFellOver::calc_() {
    MotorcycleWait::calc_();
    if (auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor)) {
        if (motorcycle->sub_710007A6E8())
            setFinished();
    }
}

}  // namespace uking::action
