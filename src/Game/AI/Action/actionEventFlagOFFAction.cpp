#include "Game/AI/Action/actionEventFlagOFFAction.h"
#include <prim/seadSafeString.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventFlagOFFAction::EventFlagOFFAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFlagOFFAction::~EventFlagOFFAction() = default;

bool EventFlagOFFAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventFlagOFFAction::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    sead::FixedSafeString<256> message;
    const auto handle = gdm->getBoolHandle(mFlagName_d);
    if (handle == ksys::gdt::InvalidHandle) {
        message.format("無効なフラグ名です。");
        return true;
    }
    bool value = false;
    if (!gdm->getBool(handle, &value, true) || value) {
        if (!gdm->setBoolNoCheck(false, handle))
            message.format("「一度しか変更しない」になっていないか確認してください。");
    }
    return true;
}

void EventFlagOFFAction::loadParams_() {
    getDynamicParam(&mFlagName_d, "FlagName");
}

}  // namespace uking::action
