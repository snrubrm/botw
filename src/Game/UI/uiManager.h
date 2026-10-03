#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace uking::ui {

// The UI manager singleton (CSV: uiManager::createInstance 0x7100a6e038, ctor 0x7100a6e0c4,
// instance pointer 0x71025f5ee0, size 0x653b0, disposer at +0x18). Only the fields that are read
// inline by AI code are declared (offsets from the original); the namespace and class name are guesses.
class Manager {
    u8 _0[0x18];
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();

public:
    // inline-only in the original; name is a guess. The same test is inlined at the start of
    // 14 functions (the GanonBeast actor "rain" update 0x7100710938, GameSceneSubsys14::postCalc,
    // IceBlockMgr::__auto0, ...): state 1 - 4, flag bits 3 / 4 of the byte at 0x64c30 or the field at
    // 0x64c2c being 1.
    bool isPausedMaybe() const {
        return u32(_64c24 - 1) < 4 || (_64c30 & 0x18) != 0 || _64c2c == 1;
    }

private:
    u8 _pad[0x64c24 - 0x18 - sizeof(mSingletonDisposerBuf_)];
    /* 0x64c24 */ s32 _64c24;
    /* 0x64c28 */ u8 _64c28[4];
    /* 0x64c2c */ s32 _64c2c;
    /* 0x64c30 */ u8 _64c30;
    /* 0x64c31 */ u8 _pad2[0x653b0 - 0x64c31];
};
KSYS_CHECK_SIZE_NX150(Manager, 0x653b0);

}  // namespace uking::ui
