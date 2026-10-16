#include "Game/gameRuneMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(RuneMgr)

static void setLockedFlag(RuneMgr::LockedFlag& flag) {
    const auto lock = sead::makeScopedLock(flag.mCS);
    flag.mFlag = true;
}

void RuneMgr::setFieldD8() {
    setLockedFlag(_98);
}

f32 RuneMgr::sub_710067549C() const {
    return _29c;
}

f32 RuneMgr::sub_71006754A4() const {
    return _280;
}

void RuneMgr::sub_71006754AC() {
    _2a8.sub_710067E2B4();
}

void RuneMgr::sub_71006754B4() {
    _2a8.sub_710067E2F8();
}

ksys::act::Actor* RuneMgr::spawnBomb(u8 idx, const sead::Matrix34f& mtx, s32 type, bool a4) {
    return _2a8.doSpawnRemoteBomb(idx, mtx, type, a4);
}

bool RuneMgr::sub_71006754CC(u8 idx) {
    return _2a8.sub_710067E55C(idx);
}

void RuneMgr::sub_71006754D8(u8 idx) {
    _2a8.sub_710067E838(idx);
}

void RuneMgr::sub_71006757B8() {
    _3c8[0].setDuration(1e-4f);
    _3c8[1].setDuration(1e-4f);
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

bool RuneMgr::checkIsSelectedRuneAndCanUse(s32 rune, uking::act::PlayerBase* player) {
    if (_248 != rune)
        return false;
    return checkCanUseRune(rune, player);
}

// NON_MATCHING: identical code, but the original lays out the PlayerInfo lookup (`if (!player)`) inline
// before the dispatch while ours moves it behind it (block placement; five source forms tried).
bool RuneMgr::checkCanUseRune(s32 rune, uking::act::PlayerBase* player) {
    if (!player) {
        auto* info = uking::act::PlayerInfo::instance();
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

bool RuneMgr::__auto15(int idx) {
    s64 i = u32(idx) < 2 ? idx : 0;
    return !_3c8[i].isDone();
}

f32 RuneMgr::sub_710067582C(int idx) const {
    s64 i = u32(idx) < 2 ? idx : 0;
    return _3c8[i].getProgress();
}

s32 RuneMgr::sub_7100676104() {
    const s32 type = ksys::gdt::getFlag_PlayerEquipItemType(false);
    return _240 = _24c = _248 = u32(type) > 7 ? -1 : type;
}

}  // namespace uking
