#include "Game/AI/Action/actionEventFlagONAction.h"
#include <prim/seadSafeString.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventFlagONAction::EventFlagONAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFlagONAction::~EventFlagONAction() = default;

bool EventFlagONAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventFlagONAction::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    sead::FixedSafeString<256> message;
    const auto handle = gdm->getBoolHandle(mFlagName_d);
    if (handle != ksys::gdt::InvalidHandle) {
        bool value = false;
        if (gdm->getBool(handle, &value, true) && value)
            return true;
        if (gdm->setBoolNoCheck(true, handle))
            return true;
        message.format("「一度しか変更しない」になっていないか確認してください。");
    } else {
        message.format("無効なフラグ名です。");
    }
    return false;
}

void EventFlagONAction::loadParams_() {
    getDynamicParam(&mFlagName_d, "FlagName");
}

}  // namespace uking::action
