#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "Game/UI/euiGrammar.h"
#include <cstring>

// Shop tag-argument helpers (the 0x7100aa4b4c/0x7100aa4e70 tag resolvers live in this TU in the
// original: the 16-byte forwarders sit right next to them).
namespace uking::ui {

namespace {

// Cook-effect table: the global info block at 0x71025f6960 (filled by the 0x7100a9fd94 static
// initializer). Only the effect-table members are modelled: the count + Buffer at +0x180/+0x188
// and the 11 inline {CookEffectId, name} entries at +0x2e0 (selectors and strings read from the
// init's stores; the MovingSpeed entry's string is "AllSpeed").
struct ShopCookEffectEntry {
    CookEffectId effect;
    sead::SafeString name;
};
static_assert(sizeof(ShopCookEffectEntry) == 0x18);

struct ShopCookInfo {
    u8 _0[0x180];
    sead::Buffer<ShopCookEffectEntry> effects;
    u8 _190[0x2e0 - 0x190];
    ShopCookEffectEntry entries[11];
};

}  // namespace

static ShopCookInfo sUnk_71025F6960{
    {},
    {11, sUnk_71025F6960.entries},
    {},
    {{CookEffectId::GutsRecover, "GutsRecover"},
      {CookEffectId::ExGutsMaxUp, "ExGutsMaxUp"},
      {CookEffectId::LifeMaxUp, "LifeMaxUp"},
      {CookEffectId::ResistHot, "ResistHot"},
      {CookEffectId::ResistCold, "ResistCold"},
      {CookEffectId::ResistElectric, "ResistElectric"},
      {CookEffectId::AttackUp, "AttackUp"},
      {CookEffectId::DefenseUp, "DefenseUp"},
      {CookEffectId::Quietness, "Quietness"},
      {CookEffectId::MovingSpeed, "AllSpeed"},
      {CookEffectId::Fireproof, "Fireproof"}},
};

// 0x7100aa4e60
u32 sub_7100AA4E60(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4B4C(data, data->_58, out);
}

// 0x7100aa4b4c (CSV unnamed): resolve a cook-effect shop tag into `out` (the message looked up
// under StaticMsg/CookEffect for the "<effect>_Name<suffix>" label, copied with the length
// returned). Returns 0 when the actor has the CookEffectName tag or the effect is not in the table.
u32 sub_7100AA4B4C(ShopInfoTagData* data, u32 selector, sead::WBufferedSafeString* out) {
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (info != nullptr) {
        if (info->hasTag(data->str.cstr(), ksys::act::tags::CookEffectName))
            return 0;
    }

    eui::Grammar::WordAttr attr;
    eui::MessageString msg;
    bool use_plural;
    if (sub_7100AA2BDC(data, &msg) != 0)
        use_plural = false;
    else
        use_plural = eui::Grammar::sub_7100BE39DC(&attr, msg);

    const s32 count = sUnk_71025F6960.effects.size();
    if (count < 1)
        return 0;
    const s64 n = count;
    for (s32 i = 0; i < n; ++i) {
        if (sUnk_71025F6960.effects[i].effect != CookEffectId(selector))
            continue;
        if (i < 0)
            return 0;
        sead::FixedSafeString<256> label;
        sead::SafeString suffix = "";
        if (use_plural) {
            // Note: written 1/2/3-first: clang lays the tests out back to front, so this
            // reproduces the original's 3/2/1 test order.
            if (attr._3 == 1) {
                suffix = "_Plural";
            } else if (attr._0 == 1) {
                suffix = "_Masculine";
            } else if (attr._0 == 2) {
                suffix = "_Feminine";
            } else if (attr._0 == 3) {
                suffix = "_Neuter";
            }
        }
        label.format("%s_Name%s", sUnk_71025F6960.effects[i].name.cstr(), suffix.cstr());
        eui::MessageString msg2;
        // Discarded call that really is in the target asm (the lookup result is used, not the
        // return value).
        ui::getMessage("StaticMsg/CookEffect", label, &msg2);
        const char16* str = msg2.getString();
        s32 len = (s32)msg2.getLength();
        char16* dst = const_cast<char16*>(out->getStringTop());
        if (dst == str)
            return msg2.getLength();
        if (len < 0) {
            len = 0;
            for (;;) {
                if (len > 0x80000 || str[len] == sead::WSafeString::cNullChar)
                    break;
                ++len;
            }
            if (len > 0x80000)
                len = 0;
        }
        if (len >= out->getBufferSize())
            len = out->getBufferSize() - 1;
        std::memcpy(dst, str, len * sizeof(char16));
        dst[len] = sead::WSafeString::cNullChar;
        return msg2.getLength();
    }
    return 0;
}

// 0x7100aa4e70 (CSV unnamed): resolve a cook-effect shop tag with a level into `out` (the
// message looked up under StaticMsg/CookEffect for the "<effect>_<Desc>" label, copied with the
// length returned). The Desc part gains a Medicine/level suffix. Returns 0 when the effect is not
// in the table.
// NON_MATCHING: the table search, entry bind, InfoData/tag check, label/message/tail all match,
// but the level-suffix block is restructured: the original keeps branchy `level >= 1`, clamping
// `level > 3` to 3, and `level >= 2` tests around a single append, while ours proves the first
// test redundant and fuses the clamp+test into predicated append-argument computing (cinc/csel
// with an unconditional append). Six natural forms tried (nested ifs, &&-outer, u32/s32 tests,
// separate level copy); the compiler always re-derives the fused shape.
u32 sub_7100AA4E70(ShopInfoTagData* data, u32 sel_lo, u32 sel_hi, sead::WBufferedSafeString* out) {
    const s32 count = sUnk_71025F6960.effects.size();
    if (count < 1)
        return 0;
    const s64 n = count;
    for (s32 i = 0; i < n; ++i) {
        if (sUnk_71025F6960.effects[i].effect != CookEffectId(sel_lo))
            continue;
        // Dead index guard that really is in the target asm (as in sub_7100AA4B4C).
        if (i < 0)
            return 0;
        sead::FixedSafeString<256> label;
        const sead::SafeString& entry_name = sUnk_71025F6960.effects[i].name;
        {
            sead::FormatFixedSafeString<16> name("Desc");
            ksys::act::InfoData* info = ksys::act::InfoData::instance();
            if (info != nullptr) {
                if (info->hasTag(data->str.cstr(), ksys::act::tags::CookEMedicine))
                    name.format("MedicineDesc");
            }
            s32 level = sel_hi;
            if (sel_lo > 15 || ((1u << sel_lo) & 0xc004) == 0) {
                if (level >= 1) {
                    if (level > 3)
                        level = 3;
                    if (level >= 2)
                        name.appendWithFormat("_%02d", level);
                }
            }
            label.format("%s_%s", entry_name.cstr(), name.cstr());
        }
        eui::MessageString msg;
        // Discarded call that really is in the target asm (as in sub_7100AA4B4C).
        ui::getMessage("StaticMsg/CookEffect", label, &msg);
        const char16* str = msg.getString();
        s32 len = (s32)msg.getLength();
        char16* dst = const_cast<char16*>(out->getStringTop());
        if (dst == str)
            return msg.getLength();
        if (len < 0) {
            len = 0;
            for (;;) {
                if (len > 0x80000 || str[len] == sead::WSafeString::cNullChar)
                    break;
                ++len;
            }
            if (len > 0x80000)
                len = 0;
        }
        if (len >= out->getBufferSize())
            len = out->getBufferSize() - 1;
        std::memcpy(dst, str, len * sizeof(char16));
        dst[len] = sead::WSafeString::cNullChar;
        return msg.getLength();
    }
    return 0;
}

// 0x7100aa5140
u32 sub_7100AA5140(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4E70(data, data->_58, data->_5c, out);
}

// 0x7100aa2bdc (CSV unnamed): resolve the tag data's string into a message (suffix-stripped actor
// name under ActorType/<profile>, or the empty message).
u32 sub_7100AA2BDC(ShopInfoTagData* data, eui::MessageString* out) {
    if (data->str.getStringTop()[0] == sead::SafeString::cNullChar) {
        const s32 len = sead::WSafeString::cEmptyString.calcLength();
        eui::MessageString empty(len, sead::WSafeString::cEmptyString.cstr());
        out->assign(empty);
        return 1;
    }
    sead::FixedSafeString<64> name;
    sub_7100AA29C4(data, name);
    sead::FixedSafeString<256> set;
    const char* profile;
    ksys::act::InfoData::instance()->getActorProfile(&profile, name.cstr());
    set.format("ActorType/%s", profile);
    sead::FixedSafeString<256> label;
    label.format("%s_Name", name.cstr());
    return ui::getMessage(set, label, out);
}

// 0x7100aa29c4 (CSV unnamed): strip the "_Far" suffix from the name, reporting whether it changed.
// NON_MATCHING: the entry, both inlined calcLength loops' heads and the return match, but the
// "_Far" literal folds in our TU (immediate char compares, constant length) while the original
// scans it generically, which also perturbs the second calcLength's unrolling and the memcmp tail.
// (A same-TU literal + simple loop always folds in clang 4; the original's must be opaque.)
bool sub_7100AA29C4(ShopInfoTagData* data, sead::SafeString& name) {
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (info == nullptr) {
        name = data->str;
        return false;
    }
    if (ksys::act::getSystemIsGetItemSelf(info, data->str.cstr())) {
        name = data->str;
        return false;
    }
    if (ksys::act::getSameGroupActorName(&name, data->str))
        return true;
    const s32 len = name.calcLength();
    s32 len2 = name.calcLength();
    const char* suffix = "_Far";
    s32 suffix_len = 0;
    while (suffix[suffix_len] != '\0' && suffix_len < 0x80000)
        ++suffix_len;
    if (suffix_len >= 0x80000)
        suffix_len = 0;
    const s32 new_len = len2 - suffix_len;
    if (new_len >= 0) {
        char* tail = const_cast<char*>(name.getStringTop()) + new_len;
        if (suffix_len >= 1 && tail != suffix) {
            const s32 cmp_len = suffix_len < 0x80000 ? suffix_len : 0x80000;
            bool matched = true;
            s32 i = 0;
            for (; i < cmp_len; ++i) {
                if (tail[i] != suffix[i]) {
                    matched = false;
                    break;
                }
                if (tail[i] == '\0')
                    break;
            }
            if (matched) {
                *tail = '\0';
                len2 = new_len;
            }
        } else {
            *tail = '\0';
            len2 = new_len;
        }
    }
    return len != len2;
}

// 0x7100aa2e08 (CSV unnamed): resolve the tag data's string into a message (the empty message
// when the string is empty, else the "<profile>" / "<name>_Desc" lookup through sub_7100AA2FA0).
u32 sub_7100AA2E08(ShopInfoTagData* data, eui::MessageString* out) {
    if (data->str.getStringTop()[0] == sead::SafeString::cNullChar) {
        const s32 len = sead::WSafeString::cEmptyString.calcLength();
        eui::MessageString empty(len, sead::WSafeString::cEmptyString.cstr());
        out->assign(empty);
        return 1;
    }
    sead::FixedSafeString<0x100> set;
    sead::FixedSafeString<0x100> label;
    sub_7100AA2FA0(data, &set, &label);
    return ui::getMessage(set, label, out);
}

// 0x7100aa2fa0 (CSV unnamed): fill `arg1` with "ActorType/<profile>" and `arg2` with
// "<name>_Desc" for the tag data's (suffix-stripped) actor name. Does nothing when the tag
// data's string is empty.
void sub_7100AA2FA0(ShopInfoTagData* data, sead::BufferedSafeStringBase<char>* arg1,
                    sead::BufferedSafeStringBase<char>* arg2) {
    if (data->str.getStringTop()[0] == sead::SafeString::cNullChar)
        return;
    sead::FixedSafeString<64> name;
    sub_7100AA29C4(data, name);
    if (arg1 != nullptr) {
        const char* profile;
        ksys::act::InfoData::instance()->getActorProfile(&profile, name.cstr());
        arg1->format("ActorType/%s", profile);
    }
    if (arg2 != nullptr) {
        arg2->format("%s_Desc", name.cstr());
    }
}

// 0x7100aa3b50 (CSV unnamed): build the "UI/StockItem/<icon>" texture path for `name` into `out`
// (icon-actor lookup, Weapon_Sword_502/503 quirk, ".%02d" count suffix, ".bitemico" extension).
void sub_7100AA3B50(const sead::SafeString& name, sead::BufferedSafeStringBase<char>* out,
                    s32 count) {
    sead::FixedSafeString<0x80> path;
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (info != nullptr) {
        const char* icon = ksys::act::getItemUseIconActorName(info, name.cstr());
        if (*icon != sead::SafeString::cNullChar)
            path.format("UI/StockItem/%s", icon);
    }
    if (path.isEmpty())
        path.format("UI/StockItem/%s", name.cstr());
    if (name == "Weapon_Sword_502") {
        const char* sword =
            shouldUseWeaponSword503() ? "Weapon_Sword_503" : "Weapon_Sword_502";
        path.format("UI/StockItem/%s", sword);
    }
    if (count >= 1)
        path.appendWithFormat(".%02d", count);
    path.append(".bitemico");
    out->copy(path);
}

// Emits the Delegate2R vtable (0x71024987e0) + invoke (0x7100a534e8) + clone (0x7100a5351c).
}  // namespace uking::ui

template class sead::Delegate2R<uking::ui::ScreenShopInfo,
                                const sead::MessageSet<char16>::TagInfo*,
                                sead::WBufferedSafeString*, u32>;
