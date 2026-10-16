#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking {
class NpcShopData;
}

namespace uking::ui {

class PouchItem;

// 0x7100a9127c (CSV shopBuyOrSellRupeeOrMamoStuff; declared only; placeholder name)
void sub_7100A9127C(s32 state, const sead::SafeString& item_name, s32 count);

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
    u8 _34[0x38 - 0x34];
    /* 0x38 */ sead::FixedSafeString<64> _38;  // item name
    u8 _90[0x98 - 0x90];
    /* 0x98 */ s32 _98;  // unit price
    u8 _9c[0xa0 - 0x9c];
    /* 0xa0 */ s32 _a0;
    u8 _a4[0xa8 - 0xa4];
    /* 0xa8 */ PouchItem* _a8;
    u8 _b0[0xb4 - 0xb0];
    bool _b4;
    u8 _b5[0xc5 - 0xb5];
    /* 0xc5 */ bool _c5;
    u8 _c6[0xcd - 0xc6];
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
    // 0x710098425c (156 bytes, declared only; placeholder name)
    void sub_710098425C(s32 value, bool flag);
    bool sub_7100982A44(s32 state, NpcShopData* shop_data);
    bool sub_7100982A60(s32 state, s32 value);
    // 0x71009843ac (1.5 KB, declared only): `out` receives a bool
    void sub_71009843AC(bool* out);
    void sub_7100984988();
    void sub_7100984BE8();
    void sub_7100984CA0(const sead::SafeString& name);
    void sub_7100984EE0();
    void sub_7100984EF8();
    void sub_71009852C0(bool value);
    void sub_71009853F4();

    // 0x71009854fc (placeholder name): acquires `proc` through _140 without acquiring it immediately
    bool sub_71009854FC(ksys::act::BaseProc* proc);
    // 0x7100985508 (declaration only; NPCClerkRoot::leave_): `_140.reset()`.
    void sub_7100985508();
};

}  // namespace uking::ui
