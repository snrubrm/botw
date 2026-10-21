#include <random/seadGlobalRandom.h>
#include "KingSystem/Sound/sndEquipmentNoiseCache.h"
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
// NON_MATCHING: accessor null checks and locator-loop termination are folded differently.
void Unk_710251b170::sub_71012C3074() {
    if (mInitialized)
        return;
    xlink2::UserInstanceSLink* user;
    {
        act::ActorLinkConstDataAccess player;
        act::ActorSystem::instance()->getPlayer(&player);
        auto* xlink = player.sub_7100D0F214();
        user = xlink ? xlink->_50 : nullptr;
    }
    if (!user || !user->isInstanceParamValid())
        return;
    for (s32 i = 0; i < 4; ++i) {
        sead::FixedSafeString<48> name("EquipNoise_");
        name.append(Strength::text(i));
        auto* locator = mStrengthLocators.emplaceBack();
        if (!user->searchAsset(locator, name.cstr())) {
            mStrengthLocators.clear();
            mSpeedLocators.clear();
            return;
        }
    }
    for (s32 i = 0; i < 4; ++i) {
        sead::FixedSafeString<48> name("EquipNoise_");
        name.append(Speed::text(i));
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

Unk_710251b018 sUnk_710251b018 = {0.1f, 0.8f, 0.2f};

Unk_710251b028::Unk_710251b028() {
    if (!sEquipmentNoiseCache.isInitialized())
        sEquipmentNoiseCache.sub_71012C3074();
}

// `{ ; }` keeps the vtable store that a defaulted destructor drops (as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
Unk_710251b028::~Unk_710251b028() { ; }

bool Unk_710251b028::m3() {
    return sub_71012C3BC8(mName);
}

void Unk_710251b028::m4(const Unk_710251b170::Speed* speed) {
    sead::FixedSafeString<48> name;
    sub_71012C3FC8(&name, speed);
    const xlink2::Locator* locator = sEquipmentNoiseCache.getSpeedLocator(*speed);
    f32 delay = 0.0f;
    if (sead::GlobalRandom::instance()->getF32() < sUnk_710251b018.delayChance) {
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
