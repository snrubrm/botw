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
