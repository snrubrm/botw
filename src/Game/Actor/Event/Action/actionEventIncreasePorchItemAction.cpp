#include "Game/Actor/Event/Action/actionEventIncreasePorchItemAction.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

EventIncreasePorchItemAction::EventIncreasePorchItemAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventIncreasePorchItemAction::~EventIncreasePorchItemAction() = default;

bool EventIncreasePorchItemAction::oneShot_() {
    if (ksys::act::InfoData::instance()->hasTag(mPorchItemName_d.cstr(), 0x30a3552e)) {
        sead::FixedSafeString<128> path("");
        sead::FixedSafeString<128> flow("");
        sead::FixedSafeString<128> entry("");
        getActiveEventFlowPath_0(mActor, &flow, &entry);
        getActiveEventFlowPath(mActor, &path);
        return false;
    }

    if (*mValue_d == 1 && (mPorchItemName_d == "Obj_HeartKakera_A_01" ||
                           mPorchItemName_d == "Obj_HeartUtuwa_A_01")) {
        callGetDemoHandler(nullptr, mPorchItemName_d);
        return true;
    }

    if (!ksys::ui::callCheckWeaponFreeSlotHandlerMaybe(mPorchItemName_d, *mValue_d))
        return false;
    ksys::ui::callIncreasePouchNum(mPorchItemName_d, *mValue_d);
    return true;
}

void EventIncreasePorchItemAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

}  // namespace uking::action
