#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"

// Shop tag-argument helpers (the 0x7100aa4b4c/0x7100aa4e70 tag resolvers live in this TU in the
// original: the 16-byte forwarders sit right next to them).
namespace uking::ui {

// 0x7100aa4e60
u32 sub_7100AA4E60(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4B4C(data, data->_58, out);
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

// Emits the Delegate2R vtable (0x71024987e0) + invoke (0x7100a534e8) + clone (0x7100a5351c).
}  // namespace uking::ui

template class sead::Delegate2R<uking::ui::ScreenShopInfo,
                                const sead::MessageSet<char16>::TagInfo*,
                                sead::WBufferedSafeString*, u32>;
