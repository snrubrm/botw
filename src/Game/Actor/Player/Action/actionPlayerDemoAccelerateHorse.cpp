#include "Game/Actor/Player/Action/actionPlayerDemoAccelerateHorse.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_7100E81220.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

PlayerDemoAccelerateHorse::PlayerDemoAccelerateHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerDemoAccelerateHorse::~PlayerDemoAccelerateHorse() = default;

bool PlayerDemoAccelerateHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerDemoAccelerateHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, mASName_s, 0, 0, true);
    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f, mASName_s, 1, 0, true);
    ksys::act::ActorLinkConstDataAccess accessor;
    if (sub_7100E81220(mActor, &accessor)) {
        if (!accessor.sub_7100D10F0C())
            accessor.sub_7100D150E8(mActor);
    }
}

void PlayerDemoAccelerateHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerDemoAccelerateHorse::loadParams_() {
    getStaticParam(&mInputAccelerateFrame_s, "InputAccelerateFrame");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: the stack slots of the two enum temporaries are swapped
void PlayerDemoAccelerateHorse::calc_() {
    if (mActor->getASList()->x_4(0, 0))
        setFinished();

    if (!mActor->getASList()->sub_710115F0BC(0, 0, *mInputAccelerateFrame_s))
        return;

    auto* ride_actor = act::getRideActor(mActor);
    if (!ride_actor)
        return;
    auto* rideable = ride_actor->getHorseOptionsMaybe();
    if (!rideable)
        return;

    rideable->_278 = act::Rideable::Unk278(act::Rideable::Unk278::_3);
    rideable->_10 |= 1u << act::Rideable::Flag10(act::Rideable::Flag10::_2);
}

}  // namespace uking::action
