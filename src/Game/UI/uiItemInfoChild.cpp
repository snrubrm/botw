#include <prim/seadSafeString.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiTraceGaugeControl.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actInfoData.h"

// Unk_710247ca18 methods. The native group 0x71009c1edc - 0x71009c2a3c (ctor, methods and its own
// RTTI statics) is separate from the Unk_710247ade8 code, which it calls out of line.

namespace uking::ui {

// 0x71009c20f0
void Unk_710247ca18::sub_71009C20F0(eui::TraceGaugeControl* gauge) {
    _170 = gauge;
    if (gauge)
        gauge->_6c = false;
}

// 0x71009c21f0
void Unk_710247ca18::sub_71009C21F0(const sead::SafeString& name) {
    eui::MessageString message;
    sub_7100AA2BDC(name, &message);
    setWidgetString(mLayout, "T_ItemName_00", message);
    setWidgetString(mLayout, "T_CookName_00", sead::SafeString::cEmptyString);
}

// 0x71009c2274
void Unk_710247ca18::sub_71009C2274(const sead::SafeString& name) {
    eui::MessageString message;
    sub_7100AA2BDC(name, &message);
    setWidgetString(mLayout, "T_CookName_00", message);
    setWidgetString(mLayout, "T_ItemName_00", sead::SafeString::cEmptyString);
}

// 0x71009c22f8
void Unk_710247ca18::sub_71009C22F8(const sead::SafeString& name) {
    if (_130 && _130->mFrame != 0.0f)
        _130->StopAtMin();
    _178.sub_71009B26A0();
    if (_138)
        _138->Stop(1.0f);

    auto* mgr = PauseMenuDataMgr::instance();
    const auto type = PauseMenuDataMgr::getType(name);
    const PouchItem* equipped = mgr->getEquippedItem(type);
    const s32 value = sub_7100AA7A50(name, type == PouchItemType::Shield);
    u32 category;
    s32 bow_value;
    if (type == PouchItemType::Bow) {
        bow_value = getBowActorInfoAddValue(name);
        category = 1;
    } else {
        category = type == PouchItemType::Shield ? 2 : 0;
        bow_value = 0;
    }
    s32 old_value = 0;
    s32 old_bow_value = 0;
    if (equipped) {
        WeaponStats stats;
        getWeaponStats(*equipped, &stats);
        old_value = stats.power;
        old_bow_value = stats.bow_add_value;
    }
    _140.sub_71009B2380(category, old_value, value, old_bow_value, bow_value);
}

// 0x71009c2420
// NON_MATCHING: clang hoists the _130 frame load above the flag test.
void Unk_710247ca18::sub_71009C2420(const sead::SafeString& name, const sead::SafeString& equipped,
                                    bool flag) {
    if (_130) {
        if (flag) {
            if (_130->mFrame != static_cast<f32>(_130->GetFrameSize()))
                _130->StopAtMax();
        } else if (_130->mFrame != 0.0f) {
            _130->StopAtMin();
        }
    }
    if (_138)
        _138->Stop(2.0f);

    const auto type = PauseMenuDataMgr::getType(name);
    const u32 category = type == PouchItemType::ArmorUpper ? 4 :
                         type == PouchItemType::ArmorLower ? 5 :
                                                             3;
    ArmorInfo info;
    getArmorInfoMaybe(name, &info);
    if (flag) {
        _178.sub_71009B26B8(info, true);
        _140.sub_71009B20E4(category, info.defence, 0);
    } else {
        ArmorInfo equipped_info;
        if (!equipped.isEmpty())
            getArmorInfoMaybe(equipped, &equipped_info);
        _178.sub_71009B26B8(info, false);
        _140.sub_71009B2380(category, equipped_info.defence, info.defence, 0, 0);
    }
}

// 0x71009c25a0
// NON_MATCHING: clang hoists the _130 frame load above the equipped test.
void Unk_710247ca18::sub_71009C25A0(const sead::SafeString& a, const sead::SafeString& b,
                                    bool equipped, bool flag) {
    if (_130) {
        if (equipped) {
            if (_130->mFrame != static_cast<f32>(_130->GetFrameSize()))
                _130->StopAtMax();
        } else if (_130->mFrame != 0.0f) {
            _130->StopAtMin();
        }
    }
    if (_138)
        _138->Stop(2.0f);

    const auto type = PauseMenuDataMgr::getType(a);
    const u32 category = type == PouchItemType::ArmorUpper ? 4 :
                         type == PouchItemType::ArmorLower ? 5 :
                                                             3;
    ArmorInfo info;
    getArmorInfoMaybe(a, &info);
    _178.sub_71009B26B8(info, true);
    if (flag) {
        ArmorInfo other_info;
        if (!b.isEmpty())
            getArmorInfoMaybe(b, &other_info);
        _140.sub_71009B2380(category, other_info.defence, info.defence, 0, 0);
    } else {
        _140.sub_71009B20E4(category, info.defence, 0);
    }
}

// 0x71009c2718
// NON_MATCHING: the success flag store is duplicated into the gauge branch (block layout).
bool Unk_710247ca18::sub_71009C2718(const sead::SafeString& name) {
    if (_130 && _130->mFrame != 0.0f)
        _130->StopAtMin();

    bool shown;
    auto* info = ksys::act::InfoData::instance();
    s32 recover;
    if (info && info->hasTag(name.cstr(), 0x14185415) &&
        (recover = getItemHitPointRecover(name)) != 0) {
        if (_138)
            _138->Stop(3.0f);
        shown = true;
        if (_170) {
            f32 ratio = 0.0f;
            sub_7100AA8FCC(&ratio, f32(recover), 120.0f);
            _170->setTracingSpeed(ratio);
            _170->set50(ratio);
        }
    } else {
        if (_138)
            _138->Stop(0.0f);
        shown = false;
    }
    _1b0.sub_71009B2010();
    return shown;
}

// 0x71009c2828
void Unk_710247ca18::sub_71009C2828(const CookingInfo& cook) {
    if (_130 && _130->mFrame != 0.0f)
        _130->StopAtMin();
    if (_138)
        _138->Stop(3.0f);
    if (_170) {
        const s32 value = cook.healthRecover;
        f32 ratio = 0.0f;
        sub_7100AA8FCC(&ratio, f32(value), 120.0f);
        _170->setTracingSpeed(ratio);
        _170->set50(ratio);
    }
    _1b0.sub_71009B1D74(cook);
}

// 0x71009c28d0
void Unk_710247ca18::sub_71009C28D0() {
    if (_130 && _130->mFrame != 0.0f)
        _130->StopAtMin();
    if (_138)
        _138->Stop(0.0f);
}

}  // namespace uking::ui
