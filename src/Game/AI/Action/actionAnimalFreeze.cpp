#include "Game/AI/Action/actionAnimalFreeze.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

AnimalFreeze::AnimalFreeze(const InitArg& arg) : HorseFreeze(arg) {}

AnimalFreeze::~AnimalFreeze() = default;

bool AnimalFreeze::init_(sead::Heap* heap) {
    return HorseFreeze::init_(heap);
}

void AnimalFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFreeze::enter_(params);
}

void AnimalFreeze::leave_() {
    HorseFreeze::leave_();
    sub_71005DB434(mActor);
}

void AnimalFreeze::loadParams_() {
    HorseFreeze::loadParams_();
}

void AnimalFreeze::calc_() {
    HorseFreeze::calc_();
    if (_68 >= *mPauseDelayFrames_s)
        sub_71005DB41C(mActor);
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(3))
        setFinished();
}

}  // namespace uking::action
