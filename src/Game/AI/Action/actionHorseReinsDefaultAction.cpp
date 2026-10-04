#include "Game/AI/Action/actionHorseReinsDefaultAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actHorseObject.h"

namespace uking::action {

HorseReinsDefaultAction::HorseReinsDefaultAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void HorseReinsDefaultAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        if (auto* horse = reins->sub_7100E7BA64()) {
            if (reins->getModel())
                _20.mReinsRoot.search(reins->getModel(), "Reins_Root");
            if (horse->getModel())
                _20.mBit.search(horse->getModel(), "Bit");
        }
    }
    mActor->sub_71011DA824(&_20);
    _20.mFlags = 0x10;
}

void HorseReinsDefaultAction::leave_() {
    mActor->sub_71011DA834(&_20);
    for (s32 i = 0; i < 20; ++i)
        _20.getEntry(i).reset();
}

void HorseReinsDefaultAction::loadParams_() {}

void HorseReinsDefaultAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
