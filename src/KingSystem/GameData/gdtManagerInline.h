#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtTriggerParam.h"

namespace ksys::gdt {

// inline-only in the original; name is a guess. The same sequence (the buffer of the TriggerParamRef at Manager +0xbb0
// / +0xbd0 and its permission flag are loaded after the SafeString temporary, then TriggerParam::getBool2 is called) is
// in ArmorBase::sub_7100E29B8C, PlayerArmors::sub_7100E3170C, Player::m63 (with getParamBypassPerm) and
// RemainElectricCannon*::enter_.
inline bool getBoolByName(Manager* mgr, bool* value, const sead::SafeString& name) {
    auto& ref = mgr->getParam();
    return ref.get().getBuffer0()->getBool2(value, name, ref.shouldCheckPermissions(), true);
}

inline bool getBoolByNameBypassPerm(Manager* mgr, bool* value, const sead::SafeString& name) {
    auto& ref = mgr->getParamBypassPerm();
    return ref.get().getBuffer0()->getBool2(value, name, ref.shouldCheckPermissions(), true);
}

// inline-only in the original; names are guesses. NPCSaleAppReception::calc_ repeats the same sequence for the by-name
// getters below (the buffer is loaded after the SafeString temporary created by the caller).
inline bool getS32IfCopiedByName(Manager* mgr, s32* value, const sead::SafeString& name) {
    auto& ref = mgr->getParam();
    return ref.get().getBuffer0()->getS32IfCopied(value, name, false, true);
}

inline bool getBoolByNameNoBool2(Manager* mgr, bool* value, const sead::SafeString& name) {
    auto& ref = mgr->getParam();
    return ref.get().getBuffer0()->getBool(value, name, ref.shouldCheckPermissions(), true);
}

inline bool getS32ByName(Manager* mgr, s32* value, const sead::SafeString& name) {
    auto& ref = mgr->getParam();
    return ref.get().getBuffer0()->getS32(value, name, ref.shouldCheckPermissions(), true);
}

inline bool getStr64ByName(Manager* mgr, const char** value, const sead::SafeString& name) {
    auto& ref = mgr->getParam();
    return ref.get().getBuffer0()->getStr64(value, name, ref.shouldCheckPermissions(), true);
}

}  // namespace ksys::gdt
