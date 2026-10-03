#include "KingSystem/Map/mapPlacementMgr.h"
#include <thread/seadThreadUtil.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementTree.h"
#include "KingSystem/System/VFR.h"

namespace ksys::map {

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

}  // namespace ksys::map
