#include "Game/AI/Action/actionAnimalStop.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimalStop::AnimalStop(const InitArg& arg) : HorseWaitAction(arg) {}

AnimalStop::~AnimalStop() = default;

bool AnimalStop::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void AnimalStop::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
    auto* asl = mActor->getASList();
    auto* rideable = mActor->m132();
    if (!asl || !rideable) {
        setFailed();
        return;
    }
    if (!(rideable->_18._52 & 2))
        rideable->_18._52 |= 2;
}

void AnimalStop::leave_() {
    HorseWaitAction::leave_();
}

void AnimalStop::loadParams_() {
    HorseWaitAction::loadParams_();
    getStaticParam(&mIsFixAxisY_s, "IsFixAxisY");
}

void AnimalStop::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action
