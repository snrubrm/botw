#include "KingSystem/Sound/sndEquipmentNoiseCache.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include <xlink2/xlink2UserInstanceSLink.h>
namespace ksys::snd {

// The startup record stores a 64-bit constant before its start tick and duration.
struct EquipmentNoiseInitInfo {
    u64 mConstants = 0x8004ef;
    util::InitTimeInfo mTiming;
};
KSYS_CHECK_SIZE_NX150(EquipmentNoiseInitInfo, 0x18);
static EquipmentNoiseInitInfo sEquipmentNoiseInitInfo;
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
}  // namespace ksys::snd
