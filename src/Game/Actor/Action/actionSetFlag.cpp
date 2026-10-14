#include "Game/Actor/Action/actionSetFlag.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

SetFlag::SetFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetFlag::~SetFlag() = default;

bool SetFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool SetFlag::oneShot_() {
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

void SetFlag::loadParams_() {}

}  // namespace uking::action
