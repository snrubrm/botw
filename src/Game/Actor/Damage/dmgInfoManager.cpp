#include "Game/Actor/Damage/dmgInfoManager.h"
#include <atomic>
#include <cmath>
#include "Game/Actor/aiUnk_710001A69C.h"
#include "Game/Scene/gameStageInfo.h"
#include <limits>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include "Game/Scene/gameScene.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::act {

SEAD_SINGLETON_DISPOSER_IMPL(DamageInfoMgr)

// Shared stage flag (placeholder name; defined in this TU so other damage TUs reach it through the GOT).
bool sUnk_71025C59D8 = false;

void DamageInfoMgr::UnkCe0::init(sead::Heap* heap) {
    mLinks.freeBuffer();
    mLinks.tryAllocBuffer(s32(mCount), heap);
}

// Clears the tags of the entries whose tag is set (resetting their link), counts the living entries
// without a tag and stores whether a tag was cleared with no living entry left.
// NON_MATCHING: the two commutative operations (the tag OR and the final AND) keep their operands in
// the opposite order; our source order does not change the encoding.
void DamageInfoMgr::UnkCe0::sub_7100672E48() {
    s32 count = 0;
    u32 cleared = 0;
    if (mCount != 0) {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            Entry& entry = mLinks[i];
            if (entry.mTag != -1) {
                cleared |= entry.mTag == 0;
                entry.mLink.reset();
                entry.mTag = -1;
            } else {
                count += accessor.sub_7100D10E6C(25);
            }
        }
    }
    _14 = cleared & (count < 1);
}

// NON_MATCHING: the ring iterator's index increment and the loop countdown are emitted in the opposite
// order (both near misses of the same loop); the loop form does not change it.
bool DamageInfoMgr::UnkD00::sub_7100673630(const sead::Vector3f& pos, f32 radius) {
    mLock.readLock();
    bool too_close = true;
    for (const RingEntry& entry : mRing) {
        const f32 dx = entry.mPos.x - pos.x;
        const f32 dy = entry.mPos.y - pos.y;
        const f32 dz = entry.mPos.z - pos.z;
        if (dx * dx + dy * dy + dz * dz <=
            (entry.mRadius + radius) * (entry.mRadius + radius)) {
            too_close = false;
            break;
        }
    }
    mLock.readUnlock();
    return too_close;
}

// NON_MATCHING: as above, one loop-latch instruction pair is ordered the other way.
bool DamageInfoMgr::UnkD00::sub_71006736E8(const sead::Vector3f& pos, f32 radius) {
    mLock.writeLock();
    bool pushed = false;
    if (mRing.size() < mRing.capacity()) {
        bool too_close = false;
        for (const RingEntry& entry : mRing) {
            const f32 dx = entry.mPos.x - pos.x;
            const f32 dy = entry.mPos.y - pos.y;
            const f32 dz = entry.mPos.z - pos.z;
            if (dx * dx + dy * dy + dz * dz <=
                (entry.mRadius + radius) * (entry.mRadius + radius)) {
                too_close = true;
                break;
            }
        }
        if (!too_close) {
            RingEntry entry;
            entry.mPos = pos;
            entry.mRadius = radius;
            entry.mCountdown = 10.0f;
            mRing.pushBack(entry);
            pushed = true;
        }
    }
    mLock.writeUnlock();
    return pushed;
}

bool DamageInfoMgr::UnkCe0::sub_7100672F54(ksys::act::BaseProc* proc) {
    while (mLock.load() == 1) {
    }
    while (!mLock.compareExchange(0, 1)) {
    }

    s32 free_index = -1;
    bool found = false;
    for (s32 i = 0; i < mCount; ++i) {
        if (free_index < 0 && !mLinks[i].mLink.hasProc())
            free_index = i;
        if (mLinks[i].mLink.hasProcById(proc)) {
            found = true;
            break;
        }
    }

    bool acquired;
    if (found) {
        acquired = false;
    } else {
        mLinks[free_index].mLink.acquire(proc, false);
        acquired = true;
    }

    std::atomic_thread_fence(std::memory_order_seq_cst);
    while (!mLock.compareExchange(1, 0)) {
    }
    return acquired;
}

// NON_MATCHING: the tag store is scheduled one slot before the found constant; the statement order
// of the two does not change it.
bool DamageInfoMgr::UnkCe0::sub_7100673064(ksys::act::BaseProc* proc, u32 tag) {
    while (mLock.load() == 1) {
    }
    while (!mLock.compareExchange(0, 1)) {
    }

    bool found = false;
    for (s32 i = 0; i < mCount; ++i) {
        if (mLinks[i].mLink.hasProcById(proc)) {
            mLinks[i].mTag = tag;
            found = true;
            break;
        }
    }

    std::atomic_thread_fence(std::memory_order_seq_cst);
    while (!mLock.compareExchange(1, 0)) {
    }
    return found;
}

s32 DamageInfoMgr::UnkCe0::sub_710067313C(f32 radius) {
    const sead::Vector3f& player_pos = getPlayerPosition();
    const f32 player_x = player_pos.x;
    const f32 player_z = player_pos.z;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (mCount == 0)
        return 0;

    s32 count = 0;
    if (radius < 0.0f) {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            if (!accessor.hasProc())
                continue;
            if (accessor.sub_7100D10E6C(0x18) || accessor.sub_7100D10E6C(25))
                ++count;
        }
    } else {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            if (!accessor.hasProc())
                continue;
            if (!accessor.sub_7100D10E6C(0x18) && !accessor.sub_7100D10E6C(25))
                continue;
            const sead::Matrix34f& mtx = accessor.getActorMtx();
            const f32 dx = mtx(0, 3) - player_x;
            const f32 dz = mtx(2, 3) - player_z;
            if (std::sqrt(dx * dx + dz * dz) < radius)
                ++count;
        }
    }
    return count;
}

void DamageInfoMgr::UnkCe0::sub_710067343C(f32 value) {
    sub_71006732CC(value, 25);
}

// NON_MATCHING: the loop's accumulated flag add keeps its operands in the opposite order (the original
// adds the count first); the source order of the sum does not change the encoding.
s32 DamageInfoMgr::UnkCe0::sub_71006732CC(f32 radius, u32 type) {
    const sead::Vector3f& player_pos = getPlayerPosition();
    const f32 player_x = player_pos.x;
    const f32 player_z = player_pos.z;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (mCount == 0)
        return 0;

    s32 count = 0;
    if (radius < 0.0f) {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            if (!accessor.hasProc())
                continue;
            count += accessor.sub_7100D10E6C(type);
        }
    } else {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            if (!accessor.hasProc())
                continue;
            if (!accessor.sub_7100D10E6C(type))
                continue;
            const sead::Matrix34f& mtx = accessor.getActorMtx();
            const f32 dx = mtx(0, 3) - player_x;
            const f32 dz = mtx(2, 3) - player_z;
            if (std::sqrt(dx * dx + dz * dz) < radius)
                ++count;
        }
    }
    return count;
}

// Whether fewer than GlobalParameter's ForceNoticeEnemyCount listed actors are near `position`. The list is
// only read here; the lock is used by the insert/remove functions.
bool DamageInfoMgr::UnkCe0::sub_7100673444(const sead::Vector3f& position) const {
    s32 limit = 3;
    f32 radius = 50.0f;
    if (auto* global = ksys::act::GlobalParameter::instance()) {
        if (const auto* param = global->getGlobalParam()) {
            limit = param->mForceNoticeEnemyCount.ref();
            if (limit < 0)
                return false;
            radius = param->mForceNoticeEnemyDist.ref();
        }
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    if (mCount == 0)
        return false;

    s32 count = 0;
    if (radius < 0.0f) {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            if (!accessor.hasProc())
                continue;
            if (!accessor.sub_7100D10E6C(25))
                continue;
            if (!sub_710001A69C(&accessor, 0x4000))
                continue;
            if (++count >= limit)
                return true;
        }
    } else {
        for (s32 i = 0; i < mCount; ++i) {
            ksys::act::acquireActor(&mLinks[i].mLink, &accessor);
            if (!accessor.hasProc())
                continue;
            if (!accessor.sub_7100D10E6C(25))
                continue;
            if (!sub_710001A69C(&accessor, 0x4000))
                continue;
            const sead::Matrix34f& mtx = accessor.getActorMtx();
            // NON_MATCHING: the original loads the matrix components before the position ones (the fsub
            // operands are mirrored); the squared distance is the same.
            const f32 dx = position.x - mtx(0, 3);
            const f32 dz = position.z - mtx(2, 3);
            if (std::sqrt(dx * dx + dz * dz) < radius && ++count >= limit)
                return true;
        }
    }
    return false;
}

void DamageInfoMgr::init(sead::Heap* heap) {
    _28.sub_710065CAE8();
    _450.sub_710065D0A4();
    mUnkCe0.init(heap);
    mReactionTable.load(heap);
    _868.sub_71006682B8(heap);
    if (_790._20.sub_71007107CC(heap, 5))
        _790._20.mOwner = &_790;
    _11e2 = 0;
    mMasterSwordDisableTrueForm = false;
}

void DamageInfoMgr::postCalc() {
    _28.sub_710065CB6C();
    _868.sub_7100668468();
    _450.sub_710065D138();
    mUnkCe0.sub_7100672E48();
    _4f8.sub_7100671794();
    _630.sub_7100672110();
    _790.sub_7100672578();

    const s32 count = mUnkD00.mRing.size();
    for (s32 i = 0; i != count; ++i)
        mUnkD00.mRing(i).mCountdown -= 1.0f;

    while (mUnkD00.mRing.size() != 0 && mUnkD00.mRing(0).mCountdown <= 0.0f)
        mUnkD00.mRing.popFront();

    mClothStiffnessMgr.sub_7100665B64();
    _11f0.sub_710067446C();
    _11eb[3] = _11eb[0] + _11eb[1] + _11eb[2];
    if (_11e1 && _cd8 <= 0)
        _11e2 = true;
    _11e1 = false;
    if (auto* weather = wm::getWeatherMgr()) {
        _11e0 = weather->isRaining() ? _11e0 | 1 : _11e0 & ~1;
        if (weather->isSnowing())
            _11e0 |= 2;
        else
            _11e0 &= ~2;
    }
    mMasterSwordDetectedEvil = false;
    mMasterSwordDetectedEvil =
        mGuardianRegistry.getNearestDistance(false) < mMasterSwordSearchEvilDist;
}

void DamageInfoMgr::sub_7100673D8C(sead::Heap* heap) {
    mReactionTable.sub_71006681D4();
}

void DamageInfoMgr::onLoadStage() {
    _28.sub_710065CAEC();

    for (s32 i = 0; i < mUnkCe0.mCount; ++i) {
        auto& entry = mUnkCe0.mLinks[i];
        entry.mLink.reset();
        entry.mTag = -1;
    }

    _4f8._c0 = 0.0f;
    for (auto& entry : _4f8.mEntries) {
        entry.mLink.reset();
        entry.mDistance = std::numeric_limits<f32>::max();
    }
    _4f8._c4 = -1;
    _4f8._c8 = 0;

    _630.mRing.clear();
    _790.mLink.reset();
    _790.mStatus = 0;
    _790._4 = -1;
    _790._20.sub_7100710DE4();
    _790.mParams.mActorName.copy("");
    _790.mParams.mIgniteRotSpd = 0.0f;
    _790.mParams.mOffsetY = 6.0f;
    _790.mParams.mCenterOffsetXZ = 5.0f;
    _790.mParams.mRandRadius = 12.0f;
    _790.mParams.mIntervalMax = 20.0f;
    _790.mParams.mIntervalMin = 15.0f;
    _790._20.sub_7100710890(15, 20);

    mUnkD00.mRing.clear();
    mClothStiffnessMgr.sub_7100665B20();

    _11f0.mLock.writeLock();
    _11f0.mSelectedIndex = -1;
    for (auto& link : _11f0.mLinks)
        link.reset();
    _11f0.mLock.writeUnlock();

    _868.sub_71006682C0();
    _450.sub_710065D0A8();

    _cd8 = 0;
    _11e1 = false;
    if (auto* data = ksys::act::InfoData::instance())
        mMasterSwordSearchEvilDist =
            ksys::act::getMasterSwordSearchEvilDist(data, "Weapon_Sword_070");
    mMasterSwordDetectedEvil = false;
    _11eb.fill(0);
}

void DamageInfoMgr::sub_7100674058() {
    _11eb.fill(0);
    _868.sub_71006685C0();
    _28.sub_710065CB68();
    _450.sub_710065D134();
    mMasterSwordDisableTrueForm = false;
}

void DamageInfoMgr::stubbed() {
    mReactionTable.stubbed();
}

bool DamageInfoMgr::isReady() {
    return mReactionTable.isReady();
}

bool DamageInfoMgr::enableBoomerangRemoteBombs() {
    return false;
}

bool DamageInfoMgr::sub_7100674764() {
    return false;
}

bool DamageInfoMgr::sub_710067476C() {
    return false;
}

s8 DamageInfoMgr::sub_7100674774() {
    return 7;
}

f32 DamageInfoMgr::sub_7100674788() {
    return 1.0f;
}

f32 DamageInfoMgr::sub_7100674790() {
    return 0.3f;
}

bool DamageInfoMgr::sub_710067479C() {
    return false;
}

bool DamageInfoMgr::sub_7100674704() const {
    if (!(_11e0 & 1)) {
        if (auto* weather = wm::getWeatherMgr())
            return weather->isRaining();
    }
    return false;
}

bool DamageInfoMgr::sub_7100674730() const {
    if (!(_11e0 & 2)) {
        if (auto* weather = wm::getWeatherMgr())
            return weather->isSnowing();
    }
    return false;
}

int DamageInfoMgr::getShieldRideBaseFrame() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 0;

    return global->getGlobalParam()->mShieldRideBaseFrame.ref();
}

int DamageInfoMgr::getShieldRideHitBaseDamage() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 0;

    return global->getGlobalParam()->mShieldRideHitBaseDamage.ref();
}

int DamageInfoMgr::sub_7100674804() {
    return 10;
}

f32 DamageInfoMgr::getCriticalAttackRatio() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 1.0;

    return global->getGlobalParam()->mCriticalAttackRatio.ref();
}

bool DamageInfoMgr::isTrueFormMasterSword() const {
    if (mMasterSwordDisableTrueForm)
        return false;

    if (ksys::gdt::getFlag_Open_MasterSword_FullPower())
        return true;

    if (ksys::gdt::getFlag_IsInHyruleCastleArea())
        return true;

    if (ksys::gdt::getFlag_LastBossGanonBeastGenerateFlag())
        return true;

    const sead::SafeString& map = uking::StageInfo::getCurrentMapName();

    if (!ksys::gdt::getFlag_Die_PGanonElectric() && map == "RemainsElectric")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonFire() && map == "RemainsFire")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonWater() && map == "RemainsWater")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonWind() && map == "RemainsWind")
        return true;

    return mMasterSwordDetectedEvil;
}


bool DamageInfoMgr::Unk11f0::sub_7100674A94(ksys::act::Actor* actor) {
    bool registered = false;
    mLock.writeLock();
    for (auto& link : mLinks) {
        if (!link.hasProc()) {
            link.acquire(actor, false);
            registered = true;
            break;
        }
    }
    mLock.writeUnlock();
    return registered;
}

void DamageInfoMgr::Unk11f0::sub_7100674B30(ksys::act::Actor* actor) {
    mLock.writeLock();
    for (auto& link : mLinks) {
        if (link.hasProcById(actor)) {
            link.reset();
            break;
        }
    }
    mLock.writeUnlock();
}

bool DamageInfoMgr::Unk11f0::sub_7100674BC0(ksys::act::Actor* actor) {
    mLock.readLock();
    bool selected = false;
    if (u32(mSelectedIndex) < mLinks.size())
        selected = mLinks[mSelectedIndex].hasProcById(actor);
    mLock.readUnlock();
    return selected;
}

void DamageInfoMgr::Unk11f0::sub_710067446C() {
    const sead::Vector3f player_pos = getPlayerPosition();
    mLock.writeLock();
    mSelectedIndex = -1;
    f32 nearest = std::numeric_limits<f32>::infinity();
    for (s32 i = 0; i < mLinks.size(); ++i) {
        if (!mLinks[i].hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&mLinks[i], &accessor);
        const f32 distance = (accessor.getActorMtx().getTranslation() - player_pos).length();
        if (distance < nearest) {
            nearest = distance;
            mSelectedIndex = i;
        }
    }
    mLock.writeUnlock();
}

}  // namespace uking::act
