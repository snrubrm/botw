#include "Game/AI/Action/actionPlayerDemoAccelerateHorse.h"
#include "Game/AI/aiUnk_7100E81220.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

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
    ksys::act::ActorConstDataAccess accessor;
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

void PlayerDemoAccelerateHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
