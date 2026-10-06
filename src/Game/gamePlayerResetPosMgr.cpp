#include "Game/gamePlayerResetPosMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/GameData/gdtManager.h"

SEAD_SINGLETON_DISPOSER_IMPL(PlayerResetPosMgr)

bool PlayerResetPosMgr::isNotResetting() const {
    return mStatus == 0;
}

void PlayerResetPosMgr::callCameraM151IfStatus4() {
    if (mStatus == 4) {
        if (auto* camera = uking::act::Root6::instance()->getCameraActor())
            camera->m151(&mCameraPos, &mCameraAt, false);
    }
}

void PlayerResetPosMgr::addResetPos(const sead::Vector3f& position, f32 yaw) {
    sead::ScopedLock<sead::SpinLock> lock(&mLock);
    if (mNumResetPos < 64) {
        mResetPositions[mNumResetPos].position = position;
        mResetPositions[mNumResetPos].yaw = yaw;
        ++mNumResetPos;
    }
}

void PlayerResetPosMgr::setResetPos(const sead::Vector3f& position, f32 yaw,
                                    ksys::act::Actor* actor) {
    sead::ScopedLock<sead::SpinLock> lock(&mLock);
    mActor = actor;
    mHasResetPos = true;
    mResetPos.position = position;
    mResetPos.yaw = yaw;
}

void PlayerResetPosMgr::sub_71007A6620(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::SpinLock> lock(&mLock);
    if (mActor == actor)
        mHasResetPos = false;
}

void PlayerResetPosMgr::resetSmallKeyFlags() {
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;

    s32 size = 0;
    manager->getParam().get1().getS32ArraySize(&size, "SmallKey");
    for (s32 i = 0; i < size; ++i)
        manager->resetS32("SmallKey", i);
    manager->resetS32("RemainsWater_SmallKeyNum");
    manager->resetS32("RemainsFire_SmallKeyNum");
    manager->resetS32("RemainsWind_SmallKeyNum");
    manager->resetS32("RemainsElectric_SmallKeyNum");
}

void PlayerResetPosMgr::clearResetPos() {
    {
        sead::ScopedLock<sead::SpinLock> lock(&mLock);
        if (!mActor)
            mHasResetPos = false;
    }
    mNumResetPos = 0;
}

void PlayerResetPosMgr::addResetPos(const sead::Vector3f& position, f32 yaw) {
    sead::ScopedLock<sead::SpinLock> lock(&mLock);
    if (_20 < 64) {
        mResetPositions[_20].position = position;
        mResetPositions[_20].yaw = yaw;
        ++_20;
    }
}

void PlayerResetPosMgr::setResetPos(const sead::Vector3f& position, f32 yaw, ksys::act::Actor* actor) {
    sead::ScopedLock<sead::SpinLock> lock(&mLock);
    _428 = actor;
    _430 = true;
    _434 = position;
    _440 = yaw;
}

void PlayerResetPosMgr::sub_71007A6620(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::SpinLock> lock(&mLock);
    if (_428 == actor)
        _430 = false;
}
