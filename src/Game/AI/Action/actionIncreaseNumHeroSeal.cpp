#include "Game/AI/Action/actionIncreaseNumHeroSeal.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {
namespace {

// File-static hero-seal pouch table (0x71025af810; initialized at startup by 0x710005e600, which
// stays undecompiled). Only the tail is typed: the pouch-name multiname table that enter_ indexes
// by RelicPattern. The entries are the four Obj_DLC_HeroSeal_* pouch SafeStrings.
struct HeroSealPouchTable {
    u8 _0[0x148];
    s32 _148;
    const sead::SafeString* _150;
};
extern HeroSealPouchTable sHeroSealPouchTable;

}  // namespace

IncreaseNumHeroSeal::IncreaseNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IncreaseNumHeroSeal::~IncreaseNumHeroSeal() = default;

bool IncreaseNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreaseNumHeroSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    // NON_MATCHING: the pouch-name table is addressed through the GOT in our build (the
    // file-static owner is only declared, its 0x5e600 initializer is not decompiled), while the
    // original reaches it with direct adrp+add; the two extra load-order differences follow from it.
    const sead::SafeString* name = u32(sHeroSealPouchTable._148) > u32(*mRelicPattern_d)
                                       ? &sHeroSealPouchTable._150[*mRelicPattern_d]
                                       : sHeroSealPouchTable._150;
    const bool ok = ui::checkWeaponFreeSlotImpl(*name, *mValue_d);
    const s32 pattern = *mRelicPattern_d;
    if (ok) {
        ui::sub_7100A97860(pattern);
        const sead::SafeString* name2 = u32(sHeroSealPouchTable._148) > u32(*mRelicPattern_d)
                                            ? &sHeroSealPouchTable._150[*mRelicPattern_d]
                                            : sHeroSealPouchTable._150;
        ui::increasePouchNumImpl(*name2, *mValue_d);
        return;
    }
    const sead::SafeString* name3 = u32(sHeroSealPouchTable._148) > u32(*mRelicPattern_d)
                                        ? &sHeroSealPouchTable._150[*mRelicPattern_d]
                                        : sHeroSealPouchTable._150;
    ui::sub_7100A9E4A0(*name3);
    setFailed();
}

void IncreaseNumHeroSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreaseNumHeroSeal::loadParams_() {
    getDynamicParam(&mRelicPattern_d, "RelicPattern");
    getDynamicParam(&mValue_d, "Value");
}

void IncreaseNumHeroSeal::calc_() {
    if (isFinished() || isFailed() || ui::sub_7100A979BC())
        return;
    setFinished();
}

}  // namespace uking::action
