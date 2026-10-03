#include "Game/gameHeroSoul.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"

namespace {
using uking::ui::PauseMenuDataMgr;
}

// 0x7100a9d3f8
bool hasRitoSoul() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->isHeroSoulEnabled(uking::ui::sub_7100AA7D38(0));
}

// 0x7100a9d440
bool hasDarukProtection() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->isHeroSoulEnabled(uking::ui::sub_7100AA7D38(1));
}

// 0x7100a9d488
bool hasMiphaSoul() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->isHeroSoulEnabled(uking::ui::sub_7100AA7D38(2));
}

// 0x7100a9d4d0
bool hasMiphaGraceCharges() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->isHeroSoulEnabled(uking::ui::sub_7100AA7D38(3));
}

// 0x7100a9d518
bool hasRevaliGalePlus() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->hasRitoSoulPlus();
}

// 0x7100a9d530
bool hasDarukProtectionPlus() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->hasGoronSoulPlus();
}

// 0x7100a9d548
bool hasUrbosaFuryPlus() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->hasGerudoSoulPlus();
}

// 0x7100a9d560
bool hasMiphaGracePlus() {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    return mgr->hasZoraSoulPlus();
}
