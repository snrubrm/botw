#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Controller;
class CriticalSection;
}

namespace eui {
class UIController;
}

namespace uking::ui {

// The UI manager singleton (CSV: uiManager::createInstance 0x7100a6e038, ctor 0x7100a6e0c4,
// instance pointer 0x71025f5ee0, size 0x653b0, disposer at +0x18). Only the fields that are used
// by the UI facade functions / read inline by AI code are declared (offsets from the original);
// the namespace and class name are guesses.
class Manager {
    u8 _0[0x18];
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();

public:
    // 0x7100a7b5d8 (CSV uiManager::createAndLoadScreenIfNeeded)
    void createAndLoadScreenIfNeeded(s32 id);

    // Placeholder-named members (the CSV calls them uiManager::__autoN / x_N or leaves them unnamed).
    void sub_7100A76180();  // CSV loadSaveForStageUnload's target
    void sub_7100A76420();  // empty (CSV nullsub_6139)
    void sub_7100A76424();
    void sub_7100A79968();
    void sub_7100A79ED4();
    void sub_7100A7A4C0();
    void sub_7100A7A6E4(s32 a1);
    void sub_7100A7A704(s32 a1);
    void sub_7100A7C904();
    void sub_7100A7DA38();
    void sub_7100A7C71C();
    void sub_7100A7F0D0();
    void sub_7100A7F2EC(const void* a1, void* a2);
    void sub_7100A7F468(const void* a1, void* a2);
    void sub_7100A7C8D4();
    void sub_7100A7C9AC();
    void sub_7100AA8698();  // 0x7100aa8698 (CSV unnamed; called by sub_7100A7C8D4)
    void sub_7100A7F81C();
    // 0x7100a702e8 (CSV uiManager::x_1)
    void sub_7100A702E8(eui::UIController* controller);
    // 0x7100a7f918 / 0x7100a7fdb4 (CSV uiManager::__auto4 / __auto11; placeholder names)
    bool sub_7100A7F918() const;
    bool sub_7100A7FDB4() const;
    void sub_7100A7F890();
    void sub_7100A7FBA4();
    bool sub_7100A7FDAC();
    void sub_7100A7B8CC(s32 a1);
    void sub_7100A7B92C(s32 a1);
    // 0x7100a7041c (CSV uiManager::loadStaticInfo, 5.8 KB; declaration only)
    void loadStaticInfo(sead::Heap* heap);

    // inline-only in the original; name is a guess. The same test is inlined at the start of
    // 14 functions (the GanonBeast actor "rain" update 0x7100710938, GameSceneSubsys14::postCalc,
    // IceBlockMgr::__auto0, ...): state 1 - 4, flag bits 3 / 4 of the byte at 0x64c30 or the field at
    // 0x64c2c being 1.
    bool isPausedMaybe() const {
        return u32(_64c24 - 1) < 4 || (_64c30 & 0x18) != 0 || _64c2c == 1;
    }

    /* 0x38 */ u8 _38;
    u8 _39[0x48 - 0x39];
    /* 0x48 */ s32 _48;
    /* 0x4c */ s32 _4c;
    /* 0x50 */ f32 _50;
    /* 0x54 */ f32 _54;
    /* 0x58 */ f32 _58;
    /* 0x5c */ f32 _5c;
    /* 0x60 */ f32 _60;
    /* 0x64 */ f32 _64;
    /* 0x68 */ f32 _68;
    /* 0x6c */ f32 _6c;
    /* 0x70 */ f32 _70;
    /* 0x74 */ u8 _74;
    u8 _75[0x78 - 0x75];
    /* 0x78 */ s32 _78;
    /* 0x7c */ s32 _7c;
    /* 0x80 */ sead::Vector3f _80;
    /* 0x8c */ sead::Vector3f _8c;
    /* 0x98 */ sead::Vector2f _98;
    /* 0xa0 */ f32 _a0;
    u8 _a4[0xb0 - 0xa4];
    /* 0xb0 */ sead::SafeArray<s32, 5> _b0;
    /* 0xc4 */ s32 _c4;
    /* 0xc8 */ s32 _c8;
    /* 0xcc */ s32 _cc;
    /* 0xd0 */ s32 _d0;
    /* 0xd4 */ s32 _d4;
    /* 0xd8 */ u64 _d8;
    /* 0xe0 */ u64 _e0;

    // inline-only in the original; names are guesses (the facade stores `*value` after fetching the
    // singleton, which a plain assignment through instance() does not reproduce).
    void setD8(const u64* value) { _d8 = *value; }
    void setE0(const u64* value) { _e0 = *value; }
    void set64c68(bool value) { _64c68 = value; }

    u8 _e8[0x649ec - 0xe8];
    /* 0x649ec */ sead::BitFlag8 _649ec;
    u8 _649ed[0x649f0 - 0x649ed];
    /* 0x649f0 */ sead::Controller* _649f0;  // the controller the screens' UIControllers are registered with
    u8 _649f8[0x64b0c - 0x649f8];
    /* 0x64b0c */ u32 _64b0c;
    /* 0x64b10 */ u32 _64b10;
    u8 _64b14[0x64c24 - 0x64b14];
    /* 0x64c24 */ s32 _64c24;
    /* 0x64c28 */ s32 _64c28;
    /* 0x64c2c */ s32 _64c2c;

    // The flag word at 0x64c30 (bit 3 / 4 = pause related, see isPausedMaybe; 0x20, 0x40, 0x80 set /
    // cleared by the UI facade); byte 5 is also read on its own.
    union {
        /* 0x64c30 */ u64 _64c30;
        u8 _64c30_bytes[8];
    };
    /* 0x64c38 */ s32 _64c38;
    u8 _64c3c[0x64c4d - 0x64c3c];
    /* 0x64c4d */ u8 _64c4d;
    u8 _64c4e[0x64c68 - 0x64c4e];
    /* 0x64c68 */ bool _64c68;
    u8 _64c69[0x650f0 - 0x64c69];
    /* 0x650f0 */ s32 _650f0;
    u8 _650f4[0x65160 - 0x650f4];
    /* 0x65160 */ u64 _65160;
    /* 0x65168 */ s32 _65168;
    u8 _6516c[0x651f8 - 0x6516c];
    /* 0x651f8 */ s32 _651f8;
    u8 _651fc[0x65218 - 0x651fc];
    /* 0x65218 */ bool _65218;
    u8 _65219[0x652e8 - 0x65219];
    /* 0x652e8 */ u8 _652e8;
    u8 _652e9[0x65387 - 0x652e9];
    /* 0x65387 */ u8 _65387;
    u8 _65388[0x653b0 - 0x65388];
};
KSYS_CHECK_SIZE_NX150(Manager, 0x653b0);

}  // namespace uking::ui
