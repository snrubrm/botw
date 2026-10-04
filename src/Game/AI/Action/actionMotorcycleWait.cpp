#include "Game/AI/Action/actionMotorcycleWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actMotorcycle.h"

namespace uking::action {

MotorcycleWait::MotorcycleWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MotorcycleWait::~MotorcycleWait() = default;

bool MotorcycleWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MotorcycleWait::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void MotorcycleWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleWait::loadParams_() {}

// NON_MATCHING: scheduling only (the original shifts `1 << flag` after the load of _10)
void MotorcycleWait::calc_() {
    auto* motorcycle = sead::DynamicCast<uking::act::Motorcycle>(mActor);
    if (!motorcycle) {
        setFailed();
        return;
    }
    const auto* unit = mActor->getMotorcyclePriorityStuffMaybe();
    motorcycle->_e40 =
        unit && unit->isFlag10On(uking::act::Unk_7100e8b2b8::Flag(uking::act::Unk_7100e8b2b8::Flag::_6)) ?
            0.0f :
            1.0f;
    motorcycle->setAccelMaybe(0.0f);
    motorcycle->setLeftStickX(0.0f);
    motorcycle->setLeftStickY(0.0f);
    motorcycle->_f88.setBit(12);
}

}  // namespace uking::action
