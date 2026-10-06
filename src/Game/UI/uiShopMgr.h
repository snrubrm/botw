#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking {
class NpcShopData;
}

namespace uking::ui {

// Placeholder declaration (name from the CSV: UiShopMgr::createInstance 0x7100980794, deleteInstance
// 0x7100980910; instance pointer at 0x71025d7ae0; namespace is a guess). The shop UI manager; only
// what the AI classes use is declared.
// TODO: incomplete.
class UiShopMgr {
    u8 _0[0x10];  // two vtable pointers (the class has two polymorphic bases) and padding
    SEAD_SINGLETON_DISPOSER(UiShopMgr)
    UiShopMgr();
    ~UiShopMgr();

public:
    // The shop state (set by UiShopMgr::sub_7100982A44 & co.; 3 = ..., 4 = ..., 5 = NPC shop data set,
    // 6, 9, 10, 11-13, 14 are tested by the UI facade functions).
    s32 _30;
    u8 _34[0xb4 - 0x34];
    bool _b4;
    u8 _b5[0xcd - 0xb5];
    bool _cd;
    u8 _ce[0xd0 - 0xce];
    NpcShopData* _d0;
    u8 _d8[4];
    s32 _dc;
    u8 _e0[0x140 - 0xe0];
    /* 0x140 */ ksys::act::BaseProcLink _140;

    // Placeholder names (the CSV leaves these unnamed); the facade functions forward to them.
    bool sub_71009816B0(s32 state, s32 a2);
    bool sub_71009821F0(s32 state);  // returns true (its last block)
    // 0x710098411c (320 bytes, declared only)
    void sub_710098411C(s32 value);
    bool sub_7100982A44(s32 state, NpcShopData* shop_data);
    bool sub_7100982A60(s32 state, s32 value);
    void sub_7100984988();
    void sub_7100984BE8();
    void sub_7100984CA0(const sead::SafeString& name);
    void sub_7100984EE0();
    void sub_7100984EF8();
    void sub_71009852C0(bool value);
    void sub_71009853F4();

    // 0x7100985508 (declaration only; NPCClerkRoot::leave_): `_140.reset()`.
    void sub_7100985508();
};

}  // namespace uking::ui
