#include <random/seadGlobalRandom.h>
#include "KingSystem/Sound/sndEquipmentNoiseCache.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include <xlink2/xlink2UserInstanceSLink.h>
namespace ksys::snd {

// NON_MATCHING: the supported timing model places 0x8004ef in the second constant word;
// this initializer stores it in the first word, as in sndSoundResourceMgr.cpp.
static util::InitTimeInfoEx sEquipmentNoiseInitInfo;
Unk_710251b170 sEquipmentNoiseCache;

Unk_710251b170::~Unk_710251b170() = default;
void Unk_710251b170::sub_71012C3074() {
    if (mInitialized)
        return;
    xlink2::UserInstanceSLink* user;
    {
        act::ActorLinkConstDataAccess player;
        act::ActorSystem::instance()->getPlayer(&player);
        auto* xlink = player.hasProc() ? player.sub_7100D0F214() : nullptr;
        user = xlink ? xlink->_50 : nullptr;
    }
    if (!user || !user->isInstanceParamValid())
        return;
    for (const auto value : Strength()) {
        sead::FixedSafeString<48> name("EquipNoise_");
        name.append(value.text());
        auto* locator = mStrengthLocators.emplaceBack();
        if (!user->searchAsset(locator, name.cstr())) {
            mStrengthLocators.clear();
            mSpeedLocators.clear();
            return;
        }
    }
    for (const auto value : Speed()) {
        sead::FixedSafeString<48> name("EquipNoise_");
        name.append(value.text());
        auto* locator = mSpeedLocators.emplaceBack();
        if (!user->searchAsset(locator, name.cstr())) {
            mStrengthLocators.clear();
            mSpeedLocators.clear();
            return;
        }
    }
    mInitialized = true;
}
namespace {
// 0x710251b070 / 0x710251b090 / 0x710251b0a8 / 0x710251b0c0 / 0x710251b0e0 / 0x710251b0f8 / 0x710251b110
const char* const sSpeedNames[4] = {"Strong", "Fast", "Fast", "Slow"};
const char* const sVariantNames[3] = {"00", "01", "02"};
const char* const sSlowVariantNames[3] = {"01", "02", "03"};
const char* const sStrengthNames[4] = {"Slow", "Slow", "Fast", "Strong"};
const char* const sWeakVariantNames[3] = {"02", "03", "04"};
const char* const sMiddleVariantNames[3] = {"01", "03", "06"};
const char* const sOtherVariantNames[3] = {"04", "05", "06"};
// 0x7101e79668: the delays of the delayed variant for each speed.
const f32 sSpeedDelays[4] = {4.5f, 5.5f, 7.0f, 9.0f};
}  // namespace

f32 sUnk_710251b018 = 0.1f;
f32 sUnk_710251b01c = 0.8f;
f32 sUnk_710251b020 = 0.2f;

Unk_710251b028::Unk_710251b028() {
    if (!sEquipmentNoiseCache.isInitialized())
        sEquipmentNoiseCache.sub_71012C3074();
}

// `{ ; }` keeps the vtable store that a defaulted destructor drops (as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
Unk_710251b028::~Unk_710251b028() { ; }

bool Unk_710251b028::m2(const sead::SafeString& name) {
    mName = name;
    _70 = mName.startsWith("Head_Special");
    return sub_71012C3BC8(name);
}

bool Unk_710251b028::sub_71012C3BC8(const sead::SafeString& name) {
    xlink2::UserInstanceSLink* user;
    {
        act::ActorLinkConstDataAccess player;
        act::ActorSystem::instance()->getPlayer(&player);
        auto* xlink = player.hasProc() ? player.sub_7100D0F214() : nullptr;
        user = xlink ? xlink->_50 : nullptr;
    }
    if (!user || !user->isInstanceParamValid())
        return false;

    sead::FixedSafeString<48> asset_name("EquipNoise_");
    asset_name.append(name);
    return user->searchAsset(&mLocator, asset_name.cstr());
}

bool Unk_710251b028::m3() {
    return sub_71012C3BC8(mName);
}

// NON_MATCHING: the two argument moves before the first getVolume call are swapped.
void Unk_710251b028::sub_71012C40C8(const xlink2::Locator* locator, f32 delay,
                                     const sead::SafeString& name) {
    if (!locator || !sEquipmentNoiseCache.isInitialized())
        return;

    auto* entry = Unk_7102502138::instance()->sub_710103B488();
    xlink2::UserInstanceSLink* user;
    {
        act::ActorLinkConstDataAccess player;
        act::ActorSystem::instance()->getPlayer(&player);
        auto* xlink = player.hasProc() ? player.sub_7100D0F214() : nullptr;
        user = xlink ? xlink->_50 : nullptr;
    }
    if (!entry || !user)
        return;

    const auto& accessor = user->getResourceAccessor();
    const auto& asset = *locator->getAssetCallTable();
    const auto& part_asset = *mLocator.getAssetCallTable();

    const f32 asset_volume = accessor.getVolume(asset, user);
    const f32 part_volume = accessor.getVolume(part_asset, user);
    const f32 asset_scale = accessor.getCustomParamValueFloat(0u, asset, user);
    const f32 part_scale = accessor.getCustomParamValueFloat(0u, part_asset, user);
    f32 volume = asset_volume * part_volume * asset_scale * part_scale;
    if (delay > 0.0f)
        volume *= sUnk_710251b01c;
    entry->volume = volume;
    entry->delay = (accessor.getDelay(asset, user) + accessor.getDelay(part_asset, user) + delay) / 30.0f;
    entry->pitch = accessor.getPitch(asset, user) * accessor.getPitch(part_asset, user);
    const f32 lpf = accessor.getLpf(asset, user) + accessor.getLpf(part_asset, user);
    entry->lpf = delay > 0.0f ? lpf + sUnk_710251b020 : lpf;
    const f32 priority = accessor.getPriority(asset, user);
    const f32 part_priority = accessor.getPriority(part_asset, user);
    entry->priority = priority > part_priority ? priority : part_priority;
    entry->name = name;
}

void Unk_710251b028::m4(const Unk_710251b170::Speed* speed) {
    sead::FixedSafeString<48> name;
    sub_71012C3FC8(&name, speed);
    const xlink2::Locator* locator = sEquipmentNoiseCache.getSpeedLocator(*speed);
    f32 delay = 0.0f;
    if (sead::GlobalRandom::instance()->getF32() < sUnk_710251b018) {
        const s32 idx = *speed;
        if (u32(idx) < 4)
            delay = sSpeedDelays[idx];
    }
    sub_71012C40C8(locator, delay, name);
}

void Unk_710251b028::sub_71012C3FC8(sead::BufferedSafeString* out,
                                     const Unk_710251b170::Speed* speed) {
    const u32 random = sead::GlobalRandom::instance()->getU32();
    s32 variant = _8 + (random & 1) * 2 - 1;
    if (variant > 2)
        variant = 0;
    if (variant < 0)
        variant = 2;
    _8 = variant;

    if (_70) {
        const char* const* names = sSlowVariantNames;
        if (*speed == Unk_710251b170::Speed::Slow)
            names = sVariantNames;
        out->format("Skn_Pl_%s_%s", mName.cstr(), names[_8]);
    } else {
        out->format("Skn_Pl_%s_%s%s", mName.cstr(), sSpeedNames[*speed], sVariantNames[_8]);
    }
}

void Unk_710251b028::m5(const Unk_710251b170::Strength* strength) {
    if (_70 && *strength == Unk_710251b170::Strength::Minimum)
        return;

    sead::FixedSafeString<48> name;
    sub_71012C44A0(&name, strength);
    sub_71012C40C8(sEquipmentNoiseCache.getStrengthLocator(*strength), 0.0f, name);
}

void Unk_710251b028::sub_71012C44A0(sead::BufferedSafeString* out,
                                     const Unk_710251b170::Strength* strength) {
    const u32 random = sead::GlobalRandom::instance()->getU32();
    s32 variant = _8 + (random & 1) * 2 - 1;
    if (variant > 2)
        variant = 0;
    if (variant < 0)
        variant = 2;
    _8 = variant;

    if (_70) {
        const char* const* names = sOtherVariantNames;
        if (*strength == Unk_710251b170::Strength::Weak)
            names = sWeakVariantNames;
        else if (*strength == Unk_710251b170::Strength::Middle)
            names = sMiddleVariantNames;
        out->format("Skn_Pl_%s_%s", mName.cstr(), names[_8]);
    } else {
        out->format("Skn_Pl_%s_%s%s", mName.cstr(), sStrengthNames[*strength],
                    sVariantNames[_8]);
    }
}

void Unk_710251b028::m6() {
    _70 = false;
}

Unk_710251b128::Unk_710251b128() {
    if (!sEquipmentNoiseCache.isInitialized())
        sEquipmentNoiseCache.sub_71012C3074();
}

bool Unk_710251b128::m3() {
    return m2("");
}

void Unk_710251b128::m6() {
    mLocators.clear();
}

void Unk_710251b128::sub_71012C5034(s32 value) {
    _10 = value > 4 ? 2 : value > 0;
}

}  // namespace ksys::snd
