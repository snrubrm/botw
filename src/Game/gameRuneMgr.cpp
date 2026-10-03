#include "Game/gameRuneMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking {

static void setLockedFlag(RuneMgr::LockedFlag& flag) {
    const auto lock = sead::makeScopedLock(flag.mCS);
    flag.mFlag = true;
}

void RuneMgr::setFieldD8() {
    setLockedFlag(_98);
}

void RuneMgr::sub_710067587C() {
    setLockedFlag(_e0);
}

void RuneMgr::sub_71006758B0() {
    setLockedFlag(_e0);
}

void RuneMgr::setHandled() {
    setLockedFlag(_128);
}

void RuneMgr::sub_710067594C() {
    setLockedFlag(_170);
}

void RuneMgr::setFlag1F8() {
    setLockedFlag(_1b8);
}

s32 RuneMgr::getCurrentItem() {
    const auto lock = sead::makeScopedLock(_200);
    return _240;
}

void RuneMgr::setCurrentItem(s32 item) {
    const auto lock = sead::makeScopedLock(_200);
    _240 = item;
}

bool RuneMgr::isSelectedRune(s32 rune) const {
    return _248 == rune;
}

bool RuneMgr::checkIsSelectedRuneAndCanUse(s32 rune, ksys::act::PlayerBase* player) {
    if (_248 != rune)
        return false;
    return checkCanUseRune(rune, player);
}

// NON_MATCHING: identical code, but the original lays out the PlayerInfo lookup (`if (!player)`) inline
// before the dispatch while ours moves it behind it (block placement; five source forms tried).
bool RuneMgr::checkCanUseRune(s32 rune, ksys::act::PlayerBase* player) {
    if (!player) {
        auto* info = ksys::act::PlayerInfo::instance();
        if (!info)
            return false;
        player = info->getPlayer();
    }
    if (!player)
        return false;
    if (rune == 0 || rune == 1)
        return player->x_13();
    if (rune == 3 || rune == 4)
        return player->checkCanUseRuneCommon();

    switch (rune) {
    case 2:
        return player->checkCanUseMagnesis();
    case 5:
        return player->checkCanUseCamera();
    case 6:
        return player->checkCanUseAmiibo();
    case 7:
        return player->checkCanUseMotorcycle();
    default:
        return false;
    }
}

bool RuneMgr::sub_710067525C() const {
    return _250;
}

}  // namespace uking
