#include "Game/AI/Action/actionSetGetFlagBase.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

SetGetFlagBase::SetGetFlagBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetGetFlagBase::~SetGetFlagBase() = default;

bool SetGetFlagBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetGetFlagBase::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    sead::FixedSafeString<256> message;
    m33();
    const auto handle = gdm->getBoolHandle(m32());
    if (handle != ksys::gdt::InvalidHandle) {
        bool value = false;
        if (!(gdm->getBool(handle, &value, true) && value)) {
            if (!gdm->setBoolNoCheck(true, handle))
                message.format("「一度しか変更しない」になっていないか確認してください。");
        }
    } else {
        message.format("無効なフラグ名です。");
    }
    return true;
}

void SetGetFlagBase::loadParams_() {}

}  // namespace uking::action
