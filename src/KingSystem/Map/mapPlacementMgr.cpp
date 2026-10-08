#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacement18.h"
#include <thread/seadThreadUtil.h>
#include <time/seadTickTime.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/gameScene.h"
#include "Game/gameStage.h"
#include "Game/gameVillagerMgr.h"
#include "KingSystem/Graphics/gfxForestRenderer.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapStagePreActorCache.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementAreaMgr.h"
#include "KingSystem/Map/mapPlacementTree.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace ksys::map {

// NON_MATCHING: the coordinate stores and region-test branches differ.
s32 sub_7100EDB6E0(bool* out_below, f32* out_height, tera::System* system,
                   const sead::Vector3f* pos) {
    const sead::Vector2f xz(pos->x, pos->z);
    if (!(pos->y <= uking::sTeraWaterDisableHeight) || !uking::sTeraWaterDisableBounds.isInside(xz)) {
        const s32 result = tera::sub_710110B4A4(out_height, &xz, system);
        if (result != -1 && result != 0)
            *out_below = pos->y < *out_height;
        return result;
    }
    *out_below = false;
    return 2;
}

SEAD_SINGLETON_DISPOSER_IMPL(PlacementMgr)

PlacementMgr::PlacementMgr() : mThreadParams(this, &PlacementMgr::threadFn) {}

PlacementMgr::~PlacementMgr() {
    mThreadHeap->destroy();
    mDynamicHeap->destroy();
    mVillagerHeap->destroy();
    mTraverseResultHeap->destroy();
}

void PlacementMgr::releaseTree() {
    if (mPlacementTree != nullptr)
        delete mPlacementTree;
    mPlacementTree = nullptr;
}

// NON_MATCHING
void PlacementMgr::x_3() {
    auto ac = act::ActorCreator::instance();
    const auto loc = sead::makeScopedLock(ac->getCS());
    if (mNumStaticObjs < mPlacementActors->getNumStaticObjs()) {
        auto list = ac->getActorList();
        for (act::Actor& node : list) {
            if (node.getMapObject() == mPlacementActors->getStaticObj_2(mNumStaticObjs)) {
                node.deleteLater(act::BaseProc::DeleteReason::_0);
            }
        }
    }
}

void PlacementMgr::reset7F0() {
    _7f0 = 0;
}

// NON_MATCHING
void PlacementMgr::initClusteredRenderer() {
    if (mThread != nullptr && mClusteredRenderer == nullptr)
        return;
    if (mThreadHeap == nullptr)
        return;

    mFlags.reset(MgrFlag::_40000);
    mThread = new (mThreadHeap)
        sead::DelegateThread("PlacementMgr", &mThreadParams, mThreadHeap,
                             sead::ThreadUtil::ConvertPrioritySeadToPlatform(0x14),
                             sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0x100000, 0x20);
    mRequestedMsg = 0;
    sead::CoreIdMask mask{sead::CoreId::cSub4};
    mThread->setAffinity(mask);
    mThread->start();
    mFlags.reset(MgrFlag::_2);

    if (mClusteredRenderer != nullptr) {
        mClusteredRenderer->startThread();
    }
}

void PlacementMgr::auto0() {
    if (mThread == nullptr)
        return;
    mFlags.set(MgrFlag::_2);
    _278 = 0;
}

void PlacementMgr::printDebugInfo() {
    if (!sFlags.isOn(MgrStaticFlags::debug))
        return;

    // Actor info:%d (loaded:%d) Instance:%d
    sead::FormatFixedSafeString<128> s1("アクタ情報:%d（ロード済み:%d) インスタンス:%d",
                                        mPlacementActors->mActorDataMapSize, mLoadedActorCount,
                                        mPlacementActors->getNumStaticObjs());
    // Traverse result pre-actor:%d actor:%d
    sead::FormatFixedSafeString<128> s2("トラバース結果  pre-actor:%d actor:%d",
                                        mTraverseResults[mTraverseResultIdx].pre_actors.size(),
                                        mTraverseResults[mTraverseResultIdx].actors.size());
    // Memory preActor:%dk info:%dk result:%dk mass:%dk clustered:%d
    sead::FormatFixedSafeString<128> s3(
        "メモリ preActor:%dk info:%dk result:%dk mass:%dk clustered:%dk", 40468, 2437, 87,
        mMassMemoryUsage / 1024, mClusteredMemoryUsage / 1024);
    // Dynamic heap remaining:%dk
    sead::FormatFixedSafeString<128> s4("動的ヒープ残り:%dk",
                                        u32(mDynamicHeap->getFreeSize() / 1024));
}

void PlacementMgr::incrementCounter() {
    _278++;
}

void PlacementMgr::x() {
    if (mFlags.isOn(MgrFlag::_2))
        return;

    mPlacementActors->x_9();
    mIntTime++;

    f32 last_time = mTime;
    auto* vfr = VFR::instance();
    mTime += vfr->getDeltaFrame();
    mTimeUpdated = s32(last_time) != s32(mTime);
}

void PlacementMgr::auto5() {
    mFlags.set(MgrFlag::_1);
}

void PlacementMgr::auto16() {
    mFlags.set(MgrFlag::_100000);
    mFlags.set(MgrFlag::_200000);
    mFlags.set(MgrFlag::_400000);
}

bool PlacementMgr::someFlagCheck() const {
    if (mFlags.isOn(MgrFlag::_80000))
        return true;
    return mFlags.isOn(MgrFlag::_100000);
}

bool PlacementMgr::auto17(Object* obj) {
    return obj->getFlags0().isOn(Object::Flag0::_1000);
}

// NON_MATCHING: the original merges the two early returns into `(msg != 0) | (pa != nullptr)`
bool PlacementMgr::auto1() {
    if (mFlags.isOn(MgrFlag::_20))
        return true;
    return mRequestedMsg != 0 || (mPlacementActors && mPlacementActors->sub_7100D524B4());
}

bool PlacementMgr::isStaticCompoundReady(const sead::Vector3f& pos, bool x) {
    _234 = pos;
    return mPlacementMapMgr->isHkscResStatus3(pos, x);
}

void PlacementMgr::disableObjStaticCompound(Object* obj) {
    if (!obj->getFlags0().isOn(Object::Flag0::StaticCompoundInstanceEnabled))
        return;
    if (auto* map = mPlacementMapMgr->getMap(obj->getIdx()))
        map->setStaticCompoundInstanceEnabled(obj, false);
}

void PlacementMgr::enableObjStaticCompound(Object* obj) {
    if (obj->getFlags0().isOn(Object::Flag0::StaticCompoundInstanceEnabled))
        return;
    if (obj->getStaticCompoundActorId() < 0)
        return;
    if (!mPlacementActors->mActorData[obj->getActorDataIdx()].mFlags.isOnBit(ActorData::Flag::MapConstActive))
        return;
    if (auto* map = mPlacementMapMgr->getMap(obj->getIdx()))
        map->setStaticCompoundInstanceEnabled(obj, true);
}

void PlacementMgr::sub_71011E9C28(Object* obj, bool enabled) {
    if (!obj->getFlags0().isOn(Object::Flag0::_80000)) {
        if (obj->getFlags0().isOn(Object::Flag0::_8) == enabled)
            return;
        if (enabled)
            obj->setFlags0(Object::Flag0::_8);
        else
            obj->resetFlags0(Object::Flag0::_8);
        mMassRenderer->x_2(this, obj);
    } else {
        if (obj->getFlags0().isOn(Object::Flag0::_40000) == enabled)
            return;
        if (enabled)
            obj->setFlags0(Object::Flag0::_40000);
        else
            obj->resetFlags0(Object::Flag0::_40000);
        if (auto* fr = StagePreActorCache::instance()->getForestRenderer()) {
            const s32 idx = fr->x_7(obj->getTranslate());
            if (idx != -1)
                fr->x_8(idx, enabled, false);
        }
    }
}

void PlacementMgr::sub_71011EB46C(Object* obj) {
    mPlacementActors->sub_7100D52CA4(obj);
}

bool PlacementMgr::invoked2(void* arg) {
    invoked2_();
    return true;
}

void PlacementMgr::initBeforeStageGenB() {
    mPlacementMapMgr->updateHkscLoadStatusesMaybe();
    mMassRenderer->sub_71011E1FFC(&mTraverseResults[1 - mTraverseResultIdx], &mCameraPos, 1000.0f);
    mMassRenderer->sub_71011E264C(this);
}

void PlacementMgr::sub_71011E63FC(const sead::Vector3f* pos, CellPos* out) {
    const f32 x = pos->x + 5000.0f;
    const f32 z = pos->z + 4000.0f;
    out->col = s32(x / 1000.0f);
    out->row = s32(z / 1000.0f);
    out->x = x - f32(out->col * 1000);
    out->z = z - f32(out->row * 1000);
}

void PlacementMgr::sub_71011E6EE0() {
    if (!mThreadStarted)
        return;
    if (mFlags.isOn(MgrFlag::_2) || mFlags.isOn(MgrFlag::_10000) || !mFlags.isOn(MgrFlag::_2000000))
        return;

    if (!mFlags.isOn(MgrFlag::_100)) {
        const s32 phase = mIntTime % 2;
        if (phase == 0)
            mPlacementActors->sub_7100D52C0C();
        else if (phase == 1)
            mPlacementMapMgr->updateHkscLoadStatusesMaybe();
        mPlacementActors->mStruct1->weirdSetup(&mPlayerPos);
    }
    if (mFlags.isOn(MgrFlag::_40))
        return;
    if (!(_690 & 0x40) && mClusteredRenderer)
        mClusteredRenderer->sub_7101244038(&mCameraPos);
    if (auto* fr = StagePreActorCache::instance()->getForestRenderer())
        fr->sub_710F03C18(&mCameraPos);
}

bool PlacementMgr::sub_71011E6C60() {
    if (_228 == 0)
        return false;
    if (_228 > 30) {
        if (mFlags.isOn(MgrFlag::_20))
            return true;
        for (s32 i = 0; i < 64; ++i)
            mPlacementMapMgr->mMaps[mPlacementMapMgr->_1c + i].unloadStaticMubin();
        mPlacementActors->setNumInUseForStaticGroup(mNumStaticObjs);
        mPlacementTree->resetPlacementObjPtrs();
        const s32 num = mPlacementActors->getStaticNumInUse();
        for (s32 i = 0; i < num; ++i) {
            if (auto* obj = mPlacementActors->getStaticObj_1(i))
                mPlacementTree->calledForPlaceActor1(obj);
        }
        _228 = 0;
        return true;
    }
    mFlags.set(MgrFlag::_1);
    ++_228;
    x_3();
    return false;
}

// NON_MATCHING: only the materialisation of the constant arguments (the original derives -5000 / 5000 from the
// -4000 / 4000 registers with an add and does not merge the last two 32-bit stores into one 64-bit store).
void PlacementMgr::initPlacementTree(bool skip_rebuild) {
    auto* heap = OverlayArenaSystem::instance()->getPlacementTreeHeap();
    mPlacementTree = new (heap) PlacementTree;
    mPlacementTree->sub_71011ED47C({heap, -5000.0f, -4000.0f, 5000.0f, 4000.0f, 30.0f, 370000});
    if (!skip_rebuild)
        mPlacementActors->rebuildTree(mPlacementTree);
}

void PlacementMgr::placeActors() {
    sead::TickTime start;
    for (s32 i = 0; i < mPlacementMapMgr->getNumMaps(); ++i) {
        auto* map = mPlacementMapMgr->getMap(i);
        if (!map->mStaticMapLoaded || map->mParsedNumStaticObjs < 0)
            continue;
        mPlacementTree->mLock.writeLock();
        for (s32 j = map->mParsedNumStaticObjs; j <= map->mNumStaticObjs; ++j) {
            auto* obj = mPlacementActors->getStaticObj_0(j);
            mPlacementTree->calledForPlaceActor1(obj);
            mPlacementActors->placeObject(obj);
        }
        mPlacementTree->mLock.writeUnlock();
    }
    mPlacementMapMgr->postPlaceActorsRouteStuff(mTeraSystem);
    mPlacementActors->mStruct1->pushFarModels();
    mPlacementActors->mStruct1->postPlaceActorsUpdateFlagsAndLazyTraverse();
    static_cast<void>(start.diffToNow());
}

void PlacementMgr::stopThread() {
    if (mThread) {
        mThread->quitAndDestroySingleThread(false);
        phys::System::instance()->sub_71012157B4(mThread, false);
        delete mThread;
        mThread = nullptr;
    }
    if (mClusteredRenderer)
        mClusteredRenderer->sub_7101243B70();
}

void PlacementMgr::stopThreads() {
    if (mThread) {
        mFlags.set(MgrFlag::_2);
        _278 = 0;
    }
    stopThread();
}

void PlacementMgr::sub_71011E9DB0() {
    if (mFlags.isOn(MgrFlag::_2))
        return;
    mPlacementActors->x_7();
    if (mClusteredRenderer && !mFlags.isOn(MgrFlag::_40) && !(_690 & 0x40))
        mClusteredRenderer->sub_7101244598();
}

// NON_MATCHING: only the schedule of the bit mask (the original computes `1 << (idx & 31)` after the load).
bool PlacementMgr::sub_71011EB32C(u32 idx) const {
    if (mMassRenderer)
        return mMassRenderer->isBitSet(idx);
    return false;
}

bool PlacementMgr::sub_71011EB37C() const {
    if (mClusteredRenderer)
        return (mClusteredRenderer->_c9c & 0xc) != 8;
    return true;
}

void PlacementMgr::sub_71011EB3F8(const sead::Vector3f* pos, f32 radius, bool x,
                                  sead::IDelegate1R<Unk_71012497f8Entry*, bool>* callback) {
    if (mClusteredRenderer)
        mClusteredRenderer->sub_710124929C(pos, radius, x, callback);
}

void PlacementMgr::sub_71011EB428(const sead::Vector3f* pos, f32 radius, bool x,
                                  sead::IDelegate1R<Unk_71012497f8Entry*, bool>* callback) {
    if (mClusteredRenderer)
        mClusteredRenderer->sub_71012497F8(pos, radius, x, callback);
}

void PlacementMgr::sub_71011EB43C(sead::Vector2<s32>* out, const sead::Vector3f* pos) {
    sub_7101249DF4(out, pos);
}

bool PlacementMgr::sub_71011EB450(const void* p) {
    if (mMassRenderer)
        return mMassRenderer->sub_71011E41F4(p);
    return false;
}


void PlacementMgr::sub_71011E6E8C() {
    if (mThreadStarted && !mFlags.isOn(MgrFlag::_2) && mFlags.isOn(MgrFlag::_2000000) && !mFlags.isOn(MgrFlag::_100) &&
        getSceneStatus() == 0) {
        mVillagerMgr->sub_7100D5EB2C();
    }
}

bool PlacementMgr::sub_71011EBFBC(Object* obj) {
    for (s32 i = 0; i < mNumEventObjs; ++i) {
        if (mEventObjs[i] == obj)
            return false;
    }
    obj->setFlags0(Object::Flag0::_20000);
    mEventObjs[mNumEventObjs++] = obj;
    return true;
}

void PlacementMgr::sub_71011EC01C(Object* obj) {
    for (s32 i = 0; i < mNumEventObjs; ++i) {
        if (mEventObjs[i] == obj) {
            obj->resetFlags0(Object::Flag0::_20000);
            for (s32 j = i; j < mNumEventObjs - 1; ++j)
                mEventObjs[j] = mEventObjs[j + 1];
            --mNumEventObjs;
            return;
        }
    }
}

void PlacementMgr::sub_71011EB2AC() {
    if (mMassRenderer)
        mMassRenderer->sub_71011E4090(this, true);
    if (auto* fr = StagePreActorCache::instance()->getForestRenderer())
        fr->sub_710F06904(this, true);
}

u32 PlacementMgr::sub_71011EB460() const {
    return mMassRenderer->_78;
}

void PlacementMgr::stubbed() {}

void PlacementMgr::insertTraverseResultPreActor(act::Actor* actor) {
    mTraverseResults[0].pre_actors.pushBack(actor);
    mTraverseResults[1].pre_actors.pushBack(actor);
}

void PlacementMgr::setFlag8Enabled(bool enabled) {
    sFlags.change(MgrStaticFlags::_8, enabled);
}

const char* PlacementMgr::getEntryUnitConfigName(const Object* obj) const {
    return obj->getUnitConfigNameFromByaml();
}

f32 PlacementMgr::getDeleteDistance(const Object* obj) const {
    return obj->getDispDistance(true, false) + 10.0f;
}

f32 PlacementMgr::getLoadDistancePlus10(const Object* obj) const {
    return obj->getLoadDistance(true) + 10.0f;
}

f32 PlacementMgr::getDispDistanceComplex(const Object* obj) const {
    if (!obj)
        return 30.0f;
    return obj->getDispDistanceComplex();
}

bool PlacementMgr::objStuff(const Object* obj) const {
    return obj->getId() != _1e4;
}

void PlacementMgr::sub_71011EB40C(const sead::Vector3f* pos, f32 radius,
                                  sead::IDelegate1R<Unk_71012497f8Entry*, bool>* callback) {
    if (mClusteredRenderer)
        mClusteredRenderer->sub_71012497F8(pos, radius, true, callback);
}

void PlacementMgr::clusteredRendererRequestDraw() {
    if (!mClusteredRenderer)
        return;

    if (!(mClusteredRenderer->_c9c & 0x20)) {
        mClusteredRenderer->requestDraw();
        return;
    }

    mClusteredRenderer->_c9c &= ~0x20;
    mClusteredRenderer->requestDraw();
    mClusteredRenderer->_c9c |= 0x20;
}

void PlacementMgr::updateTimeDivisionFlags(bool on) {
    if (on) {
        if (!mFlags.isOn(MgrFlag::_4000))
            mFlags.set(MgrFlag::_1);
    }
    mFlags.change(MgrFlag::_4000, on);
}

RailConnectablePoint* PlacementMgr::sub_71011EA44C(const sead::Vector3f* pos, s32 x, s32 z) {
    return mPlacement18->sub_7100D488A0(pos, x, z);
}

RailConnectablePoint* PlacementMgr::sub_71011EA45C(const sead::Vector3f* pos,
                                                const sead::SafeString& route_id) {
    return mPlacement18->sub_7100D49000(pos, route_id, 18, 14);
}

Rail* PlacementMgr::sub_71011EA454(const sead::SafeString& name, const sead::Vector3f* pos) {
    return mPlacement18->sub_7100D48DE0(name, pos);
}

}  // namespace ksys::map
