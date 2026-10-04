#include "Game/AI/AI/aiDragonFireRoot.h"
#include "Game/gameDragonChallengeMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

// Kept out of aiDragonFireRoot.cpp: the original calls it out-of-line with `this` although it does not use it, which
// only happens when the definition is not visible to the caller (otherwise the unused argument is dropped).
void DragonFireRoot::sub_7100367E70() {
    if (auto* mgr = DragonChallengeMgr::instance()) {
        if (mgr->incrementRef() == 0) {
            ksys::gdt::setFlag_BalladOfHeroRito_Dragon_Passing(false, false);
            if (auto* mgr2 = DragonChallengeMgr::instance())
                mgr2->setAllFlags(false);
        }
        auto* mgr3 = DragonChallengeMgr::instance();
        const bool effect = ksys::gdt::getFlag_BalladOfHeroRito_DragonEffect(false);
        const bool success = ksys::gdt::getFlag_BalladOfHeroRito_DragonSuccess(false);
        mgr3->setFlag(0, effect && !success);
        DragonChallengeMgr::instance()->resetTimerRate();
    }
}

}  // namespace uking::ai
