#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTraceGaugeControl.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>
#include <nn/ui2d/Material.h>
#include <prim/seadStorageFor.h>

namespace uking::ui {

// inline-only in the original; name is a guess. Repeated in all four preview color updates.
// Keep the saturation and brightness clamps before the byte conversion.
static sead::Color4u8 convertHorsePreviewColor(const sead::Color4f& color, f32 alpha) {
    const f32 gray = color.r * 0.298912f + color.g * 0.586611f + color.b * 0.114478f;
    const f32 red = sead::Mathf::clamp(gray + (color.r - gray), 0.0f, 1.0f);
    const f32 green = sead::Mathf::clamp(gray + (color.g - gray), 0.0f, 1.0f);
    const f32 blue = sead::Mathf::clamp(gray + (color.b - gray), 0.0f, 1.0f);
    sead::Color4u8 converted(0, 0, 0, 255);
    converted.setf(sead::Mathf::clamp(red * 5.0f, 0.0f, 1.0f),
                   sead::Mathf::clamp(green * 5.0f, 0.0f, 1.0f),
                   sead::Mathf::clamp(blue * 5.0f, 0.0f, 1.0f), alpha);
    return converted;
}

// 0x7100a50c28
// NON_MATCHING: color temporary and byte-conversion scheduling differ.
void ScreenShopHorse::sub_7100A50C28(const sead::Color4f& color) {
    _3738.setGammaCollection(convertHorsePreviewColor(color, 0.0f), 1.0f);
    if (_3720) {
        nn::util::Unorm8x4 rgba{{_3738.r, _3738.g, _3738.b, _3738.a}};
        _3720->SetColor(0, rgba);
    }
}

// 0x7100a50dc4
// NON_MATCHING: color temporary and byte-conversion scheduling differ.
void ScreenShopHorse::sub_7100A50DC4(const sead::Color4f& color) {
    _373c.setGammaCollection(convertHorsePreviewColor(color, color.a), 1.0f);
    if (_3720) {
        nn::util::Unorm8x4 rgba{{_373c.r, _373c.g, _373c.b, _373c.a}};
        _3720->SetColor(1, rgba);
    }
}

// 0x7100a50f5c
// NON_MATCHING: color temporary and byte-conversion scheduling differ.
void ScreenShopHorse::sub_7100A50F5C(const sead::Color4f& color) {
    _3740.setGammaCollection(convertHorsePreviewColor(color, color.a), 1.0f);
    if (_3728) {
        nn::util::Unorm8x4 rgba{{_3740.r, _3740.g, _3740.b, _3740.a}};
        _3728->SetColor(1, rgba);
    }
}

// 0x7100a510f4
// NON_MATCHING: color temporary and byte-conversion scheduling differ.
void ScreenShopHorse::sub_7100A510F4(sead::Color4f color) {
    _3744.setGammaCollection(convertHorsePreviewColor(color, color.a), 1.0f);
    if (_3730) {
        nn::util::Unorm8x4 rgba{{_3744.r, _3744.g, _3744.b, _3744.a}};
        _3730->SetColor(1, rgba);
    }
}


// Native A4E7B4 initializes the speed-name table. A4EE70 constructs the separate
// SafeString at 25f3468 only while initializing its guarded pointer at 25f3248.
static sead::SafeString sUnk_71025f3478[] = {"Slowest", "Slow", "Normal", "Fast", "Fastest"};
static sead::StorageFor<sead::SafeString> sUnk_71025f3468;

// 0x7100a4ee70: refreshes the horse's health, speed, stamina, familiarity and nature displays.
// NON_MATCHING: merged global addressing and saved-register allocation differ.
void ScreenShopHorse::sub_7100A4EE70(const sead::SafeString& actor_name, f32 familiarity) {
    auto* info = ksys::act::InfoData::instance();
    if (actor_name.isEmpty())
        return;
    const s32 life = ksys::act::getGeneralLife(info, actor_name.cstr());
    s32 health;
    if (life <= 100)
        health = 1;
    else if (life <= 150)
        health = 2;
    else if (life <= 200)
        health = 3;
    else if (life <= 250)
        health = 4;
    else
        health = 5;
    {
        sead::FormatFixedSafeString<5> label("%d", health);
        setWidgetString(_36d8->mLayout, "T_ParamNum_00", label);
        _36d8->setTracingSpeed(health * 20.0f);
        _36d8->set50(health * 20.0f);
    }
    const sead::FixedSafeString<16> variation(
            ksys::act::getHorseASVariation(ksys::act::InfoData::instance(), actor_name.cstr()));
    s32 speed = 0;
    for (s32 i = 0; i < 5; ++i) {
        if (sUnk_71025f3478[i] == variation) {
            speed = i + 1;
            break;
        }
    }
    {
        sead::FormatFixedSafeString<5> label("%d", speed);
        setWidgetString(_36e0->mLayout, "T_ParamNum_00", label);
        _36e0->setTracingSpeed(speed * 20.0f);
        _36e0->set50(speed * 20.0f);
    }
    static const sead::SafeString* specialHorse = sUnk_71025f3468.construct("GameRomHorse00L");
    s32 stamina = 0;
    if (actor_name != *specialHorse)
        stamina = std::clamp(ksys::act::getHorseGearTopChargeNum(
                ksys::act::InfoData::instance(), actor_name.cstr()), 0, 5);
    {
        sead::FormatFixedSafeString<5> label("%d", stamina);
        setWidgetString(_36e8->mLayout, "T_ParamNum_00", label);
        _36e8->setTracingSpeed(stamina * 20.0f);
        _36e8->set50(stamina * 20.0f);
    }
    const s32 percent = sead::Mathf::floor(familiarity * 100.0f);
    {
        sead::FormatFixedSafeString<5> label("%d", percent);
        setWidgetString(_36f0->mLayout, "T_ParamNum_00", label);
        _36f0->setTracingSpeed(percent);
        _36f0->set50(percent);
    }
    _36d0->Stop(ksys::act::getHorseNature(ksys::act::InfoData::instance(), actor_name.cstr()));
}
}  // namespace uking::ui
