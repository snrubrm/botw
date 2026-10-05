#include "Game/AI/Action/actionHorseWaitEx.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

// Source namespace and nominal receiver spelling are inferred; declaration only.
void sub_71001ABF60(uking::act::Rideable* rideable, const char* name, ...);

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
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        rideable->_18.sub_7100E78E00();
        sub_71001ABF60(rideable, act::sUnk_7102603230.cstr(), nullptr);
    }
}

void HorseWaitEx::loadParams_() {
    HorseWaitAction::loadParams_();
    getStaticParam(&mKeepFrame_s, "KeepFrame");
}

void HorseWaitEx::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action
