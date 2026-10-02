#include "Game/AI/Action/actionPlayASForAnimalUnit.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayASForAnimalUnit::PlayASForAnimalUnit(const InitArg& arg) : ForkAnimalASPlay(arg) {}

PlayASForAnimalUnit::~PlayASForAnimalUnit() = default;

bool PlayASForAnimalUnit::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void PlayASForAnimalUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimalASPlay::enter_(params);
}

void PlayASForAnimalUnit::leave_() {
    ForkAnimalASPlay::leave_();
}

void PlayASForAnimalUnit::loadParams_() {
    ForkAnimalASPlay::loadParams_();
}

void PlayASForAnimalUnit::calc_() {
    ForkAnimalASPlay::calc_();
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (as_list && controller && rideable)
        uking::act::sub_7100E7F698(rideable, as_list, controller);
    else
        setFailed();
}

}  // namespace uking::action
