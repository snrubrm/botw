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

// The item record the shop manager works on (0x78 bytes at UiShopMgr + 0x38). Its name comes first;
// the state helpers (0x7100a90e40 / 0x7100a91e84 / 0x7100a91f64 / 0x7100a92180) read the fields after
// it through the same pointer, which is why the item is passed as one record.
struct ShopItem {
    /* 0x00 */ sead::FixedSafeString<64> name;
    /* 0x58 */ s32 _58;  // count (1 after sub_7100982A7C)
    /* 0x5c */ s32 _5c;
    /* 0x60 */ s32 _60;  // unit price
    /* 0x64 */ s32 _64;
    /* 0x68 */ s32 _68;
    /* 0x6c */ u8 _6c;  // a flag the state helpers test for the 11 - 13 states
    /* 0x6d */ u8 _6d[3];
    /* 0x70 */ PouchItem* _70;
};
KSYS_CHECK_SIZE_NX150(ShopItem, 0x78);

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
    /* 0x38 */ ShopItem _38;  // the selected item
    /* 0xb0 */ s32 _b0;  // the last value passed to sub_710098425C
    bool _b4;
    u8 _b5[0xc0 - 0xb5];
    /* 0xc0 */ s32 _c0;
    u8 _c4;
    /* 0xc5 */ bool _c5;
    u8 _c6;
    /* 0xc7 */ bool _c7;
    /* 0xc8 */ s32 _c8;
    u8 _cc;
    bool _cd;
    u8 _ce[0xd0 - 0xce];
    NpcShopData* _d0;
    s32 _d8;
    s32 _dc;
    /* 0xe0 */ s32 _e0;  // passed to sub_7100A92180 for the state-10 item
    u8 _e4[4];
    // createInstance constructs capacity 64; shop item selection compares against this name.
    /* 0xe8 */ sead::FixedSafeString<64> _e8;
    /* 0x140 */ ksys::act::BaseProcLink _140;

    // Placeholder names (the CSV leaves these unnamed); the facade functions forward to them.
    bool sub_71009816B0(s32 state, s32 a2);
    // Open / close the button list selected by the shop-state table.
    void sub_7100981888(bool value, s32 index);
    void sub_7100981FAC();
    bool sub_71009821F0(s32 state);  // returns true (its last block)
    // 0x710098411c (320 bytes, declared only)
    void sub_710098411C(s32 value);
    // 0x71009842f8 (declared only; 180 bytes; called from the shop list's Unk_7102497698::m9)
    void sub_71009842F8();
    // 0x710098425c (156 bytes, declared only; placeholder name)
    // 0x710098425c: the shop list entries pass (Unk_7102474e38::sub_7100939C68(), sub_7100939C78())
    void sub_710098425C(s32 a1, s32 a2);
    // 0x7100983e48 / 0x7100982c90 / 0x7100980f48 (CSV unnamed; not decompiled): called by sub_710098425C
    bool sub_7100983E48(s32 category, s32 index, ShopItem* item);
    void sub_7100982C90();
    bool sub_71009831B0(s32 index, ShopItem* item);
    // Native 980F48 consumes the item metadata through +0x70, not just its string.
    void sub_7100980F48(ShopItem* item);
    bool sub_7100982A44(s32 state, NpcShopData* shop_data);
    bool sub_7100982A60(s32 state, s32 value);
    // 0x7100982b9c (244 bytes): the state value the shop menu shows for `item` (state dispatch over
    // _30, forwarded to the four shop tag state helpers).
    u32 sub_7100982B9C(const ShopItem& item);
    // 0x7100982124 (placeholder name): for the states 7 / 8, shows the selected item's name on the shop
    // info screen.
    void sub_7100982124();
    // 0x7100982a7c (placeholder name): fills the selected item (name, count 1, `price`) and its state,
    // then sets _c0 to 5 when the shop info screen is open and to 4 otherwise.
    bool sub_7100982A7C(s32 a1, const sead::SafeString& name, s32 price, s32 a2);
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
