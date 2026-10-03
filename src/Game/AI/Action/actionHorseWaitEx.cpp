#include "Game/AI/Action/actionHorseWaitEx.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseWaitEx::HorseWaitEx(const InitArg& arg) : HorseWaitAction(arg) {}

HorseWaitEx::~HorseWaitEx() = default;

bool HorseWaitEx::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void HorseWaitEx::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
    _68 = 0;
    mActor->getMtx().getTranslation(_70);
}

void HorseWaitEx::leave_() {
    HorseWaitAction::leave_();
}

void HorseWaitEx::loadParams_() {
    HorseWaitAction::loadParams_();
    getStaticParam(&mKeepFrame_s, "KeepFrame");
}

void HorseWaitEx::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action
