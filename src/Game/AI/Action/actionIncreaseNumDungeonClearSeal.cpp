#include "Game/AI/Action/actionIncreaseNumDungeonClearSeal.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

IncreaseNumDungeonClearSeal::IncreaseNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

IncreaseNumDungeonClearSeal::~IncreaseNumDungeonClearSeal() = default;

bool IncreaseNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreaseNumDungeonClearSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ui::checkWeaponFreeSlotImpl(mActorName_s, *mValue_d)) {
        ui::sub_7100A9732C();
        ui::increasePouchNumImpl(mActorName_s, *mValue_d);
    } else {
        ui::sub_7100A9E4A0(mActorName_s);
        setFailed();
    }
}

void IncreaseNumDungeonClearSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreaseNumDungeonClearSeal::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
    getDynamicParam(&mValue_d, "Value");
}

void IncreaseNumDungeonClearSeal::calc_() {
    if (isFinished() || isFailed() || ui::sub_7100A973E0())
        return;
    setFinished();
}

}  // namespace uking::action
