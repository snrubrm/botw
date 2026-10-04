#include "Game/gameFlagUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtTriggerParam.h"

// Name guesses: the CSV only names the int variant (getFlagInt); the bool / f32 variants (0x7100900bb0, 0x7100900c0c,
// 0x7100900c84, 0x7100900ce0) are unnamed.

bool sub_7100900BB0(const sead::SafeString& flag) {
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        bool value = false;
        return mgr->getParam().get().getBuffer0()->getBoolIfCopied(&value, flag, false, true);
    }
    return false;
}

bool getFlagBool(bool* value, const sead::SafeString& flag) {
    if (auto* mgr = ksys::gdt::Manager::instance())
        return mgr->getParam().get().getBuffer0()->getBoolIfCopied(value, flag, false, true);
    return false;
}

bool getFlagInt(s32* value, const sead::SafeString& flag) {
    if (auto* mgr = ksys::gdt::Manager::instance())
        return mgr->getParam().get().getBuffer0()->getS32IfCopied(value, flag, false, true);
    return false;
}

bool sub_7100900C84(const sead::SafeString& flag) {
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        f32 value = 0;
        return mgr->getParam().get().getBuffer0()->getF32IfCopied(&value, flag, false, true);
    }
    return false;
}

bool getFlagF32(f32* value, const sead::SafeString& flag) {
    if (auto* mgr = ksys::gdt::Manager::instance())
        return mgr->getParam().get().getBuffer0()->getF32IfCopied(value, flag, false, true);
    return false;
}
