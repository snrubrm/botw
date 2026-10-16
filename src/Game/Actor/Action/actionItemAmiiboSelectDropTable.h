#pragma once

#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ItemAmiiboSelectDropTable : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ItemAmiiboSelectDropTable, ksys::act::ai::Action)
public:
    // Placeholders (SEAD_ENUM_EX; no enum text in the binary, value names unknown). AmiiboId: value array built by
    // 0x71001c08ac (13 values, character id << 8 | variant, 0xffffff = none); CharacterId: value array built by
    // 0x71001c1eec (11 values, 0xffff = none). sub_71001C0E60 converts the first to the second.
    SEAD_ENUM_EX(AmiiboId, _0 = 0xffffff, _1 = 0x10000, _2 = 0x10001, _3 = 0x10100, _4 = 0x10101, _5 = 0x10201,
                 _6 = 0x10300, _7 = 0x10500, _8 = 0x10800, _9 = 0x10700, _10 = 0x10600, _11 = 0x14000,
                 _12 = 0x14100)
    SEAD_ENUM_EX(CharacterId, _0 = 0xffff, _1 = 0x100, _2 = 0x101, _3 = 0x102, _4 = 0x103, _5 = 0x105,
                 _6 = 0x108, _7 = 0x107, _8 = 0x106, _9 = 0x140, _10 = 0x141)

    // 0x71001c17a4: the character of an amiibo id (the id's bits 8..23), or the first value if it is unknown.
    static CharacterId sub_71001C17A4(const AmiiboId& id);

    explicit ItemAmiiboSelectDropTable(const InitArg& arg);
    ~ItemAmiiboSelectDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Complete 1C0E60 returns a SafeString through x8 and reads the two signed index inputs.
    // Caller 1C0D40 supplies copies of _1e0 and _1e4; the helper does not modify them.
    sead::SafeString sub_71001C0E60(const s32* character_id, const s32* numbering_id);

    // static_param at offset 0x20
    sead::SafeString mTableCommon_s{};
    // static_param at offset 0x30
    sead::SafeString mTableGanondorf_s{};
    // static_param at offset 0x40
    sead::SafeString mTableToonLink_s{};
    // static_param at offset 0x50
    sead::SafeString mTableSheik_s{};
    // static_param at offset 0x60
    sead::SafeString mTableLink_s{};
    // static_param at offset 0x70
    sead::SafeString mTableZelda_s{};
    // static_param at offset 0x80
    sead::SafeString mTableWolfLink_s{};
    // static_param at offset 0x90
    sead::SafeString mTableGuardian_s{};
    // static_param at offset 0xa0
    sead::SafeString mTableBokoblin_s{};
    // static_param at offset 0xb0
    sead::SafeString mTableCross_Ganondorf_s{};
    // static_param at offset 0xc0
    sead::SafeString mTableCross_ToonLink_s{};
    // static_param at offset 0xd0
    sead::SafeString mTableCross_Sheik_s{};
    // static_param at offset 0xe0
    sead::SafeString mTableCross_Link_s{};
    // static_param at offset 0xf0
    sead::SafeString mTableCross_Zelda_s{};
    // static_param at offset 0x100
    sead::SafeString mTableKing_WolfLink_s{};
    // static_param at offset 0x110
    sead::SafeString mTableKing_Link_Bow_s{};
    // static_param at offset 0x120
    sead::SafeString mTableKing_Link_Horse_s{};
    // static_param at offset 0x130
    sead::SafeString mTableKing_Zelda_Doctor_s{};
    // static_param at offset 0x140
    sead::SafeString mTableKing_Guardian_s{};
    // static_param at offset 0x150
    sead::SafeString mTableKing_Bokoblin_s{};
    // static_param at offset 0x160
    sead::SafeString mTableKing30th_Link_Ocarina_s{};
    // static_param at offset 0x170
    sead::SafeString mTableKing30th_Link_Majora_s{};
    // static_param at offset 0x180
    sead::SafeString mTableKing30th_Link_Takt_s{};
    // static_param at offset 0x190
    sead::SafeString mTableKing30th_Zelda_Takt_s{};
    // static_param at offset 0x1a0
    sead::SafeString mTableKing30th_Link_Twilight_s{};
    // static_param at offset 0x1b0
    sead::SafeString mTableKing30th_Link_Skyward_s{};
    // static_param at offset 0x1c0
    sead::SafeString mTableKing30th_Link_Dot_s{};
    // map_unit_param at offset 0x1d0
    const int* mAmiiboCharacterId_m{};
    // map_unit_param at offset 0x1d8
    const int* mAmiiboNumberingId_m{};
    int _1e0 = 0;
    int _1e4 = 0;
};

}  // namespace uking::action
