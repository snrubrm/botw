#include "KingSystem/Map/mapPlacementActors.h"
#include <algorithm>
#include <prim/seadMemUtil.h>
#include <time/seadTickTime.h>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Effect/eftEffect.h"
#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/Map/mapObject.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/Map/mapObjectEffect.h"
#include "KingSystem/Map/mapDebug.h"
#include "KingSystem/Map/mapObjectGenGroup.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapPlacementAreaMgr.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacementTree.h"

namespace ksys::map {

// The static SafeString the LinkTagNone comparisons use (0x71024db4b0 in the original, right before the
// PlacementActors vtable; the original symbol name is stripped).
static const sead::SafeString sLinkTagNone("LinkTagNone");


void PlacementActors::threadSpawnGenGroupActors(const sead::Vector3f& pos, void* traverse_results) {
    auto* objs = static_cast<sead::PtrArray<Object>*>(traverse_results);
    auto* mgr = PlacementMgr::instance();
    for (s32 i = 0; i < objs->size(); ++i) {
        if (mgr->isFlagOn(PlacementMgr::MgrFlag::_2) ||
            mgr->isFlagOn(PlacementMgr::MgrFlag::_10000))
            return;

        Object* obj = (*objs)[i];
        if (!obj->mFlags0.set(Object::Flag0::_10000))
            continue;

        if (shouldSpawn(obj)) {
            if (x_13(obj, pos, nullptr, nullptr) && !obj->mFlags.isOn(Object::Flag::IsLinkTag)) {
                if (obj->mLinkData && obj->mLinkData->mGenGroup)
                    obj->spawnGenGroupActorsIfNeeded(obj);
                else
                    spawnActor(obj);
            }
        } else {
            if (obj->getProc() && obj->mLinkData && !obj->mLinkData->isGroupInitComplete())
                obj->spawnGenGroupActorsIfNeeded(obj);
        }

        obj->mFlags0.reset(Object::Flag0::_10000);
    }
}

// NON_MATCHING: the inlined GenGroup constructor merges the zero stores differently (the original keeps
// 0x18 / 0x1a / 0x1b separate) and the register allocation differs; the traversal, the group fill and
// the create/delete-source checks match.
bool PlacementActors::buildGenGroup(Object* obj, sead::Heap* heap) {
    if (obj->mFlags.isOn(Object::Flag::IsLinkTag)) {
        if (sLinkTagNone == obj->getUnitConfigName())
            return true;
    }

    Object* objs_buf[0x200];
    sead::PtrArray<Object> objs;
    Object* link_tags_buf[0x20];
    sead::PtrArray<Object> link_tags;

    objs.setBuffer(0x200, objs_buf);
    const f32 max_dist = getMaxTraverseDistForGenGroupRecursively(obj, &objs);
    link_tags.setBuffer(0x20, link_tags_buf);

    addAllLinkedActorsToGenGroupRecursively(max_dist, obj, &objs, &link_tags);

    const s32 num_objs = objs.size();
    if (num_objs < 2)
        return true;

    auto* group = new (heap, 8) GenGroup();
    if (!group)
        return false;

    group->mNumPrepareDelete = num_objs;
    if (!group->mObjects.tryAllocBuffer(num_objs, heap, 8)) {
        group->mObjects.freeBuffer();
        delete group;
        return false;
    }

    s32 num_create_src = 0;
    s32 num_delete_src = 0;
    Object* create_src = nullptr;
    Object* delete_src = nullptr;

    for (Object& o : objs) {
        if (o.mFlags.isOn(Object::Flag::IsLinkTag))
            continue;

        auto* link_data = o.mLinkData;
        link_data->setGenGroup(group);
        if (group->mObjects.indexOf(&o) < 0) {
            if (group->mObjects.size() < group->mObjects.capacity())
                group->mObjects.pushBack(&o);
            if (o.mFlags.isOn(Object::Flag::IsLinkTag))
                ++group->_18;
        }

        if (group->_1c == 0 && o.isEnemyOrNpc(this))
            group->_1c = 1;

        if (num_create_src >= 0) {
            Object* src = link_data->mCreateLinksSrcObj;
            if (create_src == nullptr) {
                create_src = src;
                if (src != nullptr)
                    ++num_create_src;
            } else if (create_src == src) {
                ++num_create_src;
            } else {
                num_create_src = -1;
            }
        }
        if (num_delete_src >= 0) {
            Object* src = link_data->mDeleteLinksSrcObj;
            if (delete_src == nullptr) {
                delete_src = src;
                if (src != nullptr)
                    ++num_delete_src;
            } else if (delete_src == src) {
                ++num_delete_src;
            } else {
                num_delete_src = -1;
            }
        }
    }

    for (Object& o : objs) {
        if (!o.mFlags.isOn(Object::Flag::IsLinkTag))
            continue;

        o.mLinkData->setGenGroup(group);
        if (group->mObjects.indexOf(&o) < 0) {
            if (group->mObjects.size() < group->mObjects.capacity())
                group->mObjects.pushBack(&o);
            if (o.mFlags.isOn(Object::Flag::IsLinkTag))
                ++group->_18;
        }
    }

    if (link_tags.size() == 1) {
        Object* tag = link_tags[0];
        if (tag->mLinkData) {
            const s32 num_group_objs = num_objs - group->_18;
            if (tag->mLinkData->mLinksToSelf.links.size() >= num_group_objs) {
                if ((num_create_src != 0 && num_create_src != num_group_objs) ||
                    (num_delete_src != 0 && num_delete_src != num_group_objs)) {
                    group->mHasCreateOrDeleteLinks = 0;
                } else {
                    group->mHasCreateOrDeleteLinks = num_create_src > 0 || num_delete_src > 0;
                }
            }
        }
    }

    return true;
}

// NON_MATCHING: the two `return true` tails are tail-merged here (the original keeps them separate);
// every check and the flag set match.
bool shouldSpawn(Object* obj) {
    auto* mgr = PlacementMgr::instance();
    if (mgr->isFlagOn(PlacementMgr::MgrFlag::_2) ||
        mgr->isFlagOn(PlacementMgr::MgrFlag::_10000))
        return false;

    if (obj->isNpcOrActiveOrMapPassiveOrFlag1())
        return false;
    // ActorCreated or _80000000.
    if (obj->mFlags0.getDirect() & 0x80000200)
        return false;
    if (obj->getProc())
        return false;
    if (obj->mFlags0.isOn(Object::Flag0::_4000) ||
        obj->mFlags0.isOn(Object::Flag0::_8000))
        return false;

    auto* link = obj->mLinkData;
    if (link && link->x())
        return false;

    if (obj->mFlags0.getDirect() & 6) {
        if (!obj->hasGenGroup())
            return false;
        if (obj->getProc())
            return false;
        if (!obj->mFlags0.isOn(Object::Flag0::_80))
            return false;

        if (obj->shouldSkipSpawn_(true))
            return true;
        if (link && link->hasCreateOrDeleteLinks())
            return true;
        obj->mFlags0.set(Object::Flag0::_400);
        return true;
    }

    if (obj->shouldSkipSpawn_(false))
        return obj->hasGenGroup();
    return true;
}

bool PlacementActors::spawnGenGroupActor(Object* obj, Object* other) {
    if (other != obj && !obj->mFlags0.set(Object::Flag0::_10000))
        return false;

    // The original reads the flag word here and discards it (the load is in the target asm).
    obj->mFlags0.getDirect();

    bool result = false;
    if (shouldSpawn(obj)) {
        bool spawn = true;
        if (obj->mActorFlags8.isOn(ActorFlag8::MapPassive)) {
            const ActorData& data = mActorData[obj->mActorDataIdx];
            const char* profile;
            if (!ksys::act::InfoData::instance()->getActorProfile(&profile,
                                                                  data.mActorName.cstr()) ||
                (!data.mFlags.isOnBit(ActorData::Flag::_16) &&
                 !obj->isEnemyOrNpcOrActiveOrMapPassive())) {
                spawn = false;
            } else {
                obj->mFlags0.reset(Object::Flag0::_2000);
            }
        }
        if (spawn)
            result = spawnActor(obj);
    }

    if (other != obj)
        obj->mFlags0.reset(Object::Flag0::_10000);
    return result;
}

bool PlacementActors::doSpawn(Object* obj, bool set_flag, bool use_gen_group) {
    const ActorData& data = mActorData[obj->mActorDataIdx];
    const char* profile;
    if (!ksys::act::InfoData::instance()->getActorProfile(&profile, data.mActorName.cstr()))
        return false;
    if (!data.mFlags.isOnBit(ActorData::Flag::_16) && !obj->isEnemyOrNpcOrActiveOrMapPassive())
        return false;

    if (set_flag)
        obj->mFlags0.set(Object::Flag0::_2000);
    else
        obj->mFlags0.reset(Object::Flag0::_2000);

    if (!use_gen_group)
        return spawnActor(obj);

    if (!obj->mLinkData || !obj->mLinkData->mGenGroup)
        spawnActor(obj);
    else
        obj->spawnGenGroupActorsIfNeeded(obj);

    if ((obj->mFlags0.getDirect() & 6) == 0)
        return false;
    return (obj->mFlags0.getDirect() & 0x80) == 0;
}

s32 ActorData::sub_7100D4DF48() const {
    if (mFlags.isOnBit(Flag::_4) || mFlags.isOnBit(Flag::_7))
        return -1;
    if (mFlags.isOnBit(Flag::_1) || mFlags.isOnBit(Flag::_2)) {
        if (mFlags.isOnBit(Flag::IgnoreBoundingAtAreaCulling))
            return 0;
        if (mFlags.isOnBit(Flag::_40) &&
            PlacementMgr::instance()->mFlags.isOn(PlacementMgr::MgrFlag::_1000000))
            return 0;
        return 1;
    }
    return mFlags.isOnBit(Flag::_5) ? 2 : -1;
}


// NON_MATCHING: the original keeps the link-count decrement in a 64-bit register (sub x21 / cbnz x21)
// and schedules the pointer increment before it; ours uses the 32-bit counter and the other order.
// NON_MATCHING: the three link loops keep their counter 64-bit in the original (sub x22); ours uses
// the 32-bit counter. The traversal, the LinkTagNone bucket and the distance write match.
void PlacementActors::addAllLinkedActorsToGenGroupRecursively(f32 max_dist, Object* obj,
                                                             sead::PtrArray<Object>* group_objs,
                                                             sead::PtrArray<Object>* link_tags) {
    if (!obj)
        return;

    const bool link_tag_none =
        obj->mFlags.isOn(Object::Flag::IsLinkTag) &&
        sLinkTagNone == obj->getUnitConfigName();

    if (obj->isMapPassive(this) ||
        (obj->checkActorDataFlag(this, ActorData::Flag::MapConstPassive) &&
         !obj->mActorFlags8.isOn(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall) &&
         (obj->mLinkData == nullptr ||
          (obj->mLinkData->mLinksToSelf.links.size() == 0 &&
           obj->mLinkData->mLinksOther.links.size() == 1 &&
           obj->mLinkData->mLinksOther.links[0].type == MapLinkDefType::SyncLink)))) {
        const f32 disp = obj->getDispDistance(this, false, false);
        if (max_dist <= disp)
            return;
        if (!obj->checkActorDataFlag(this, ActorData::Flag::MapConstPassive))
            return;
        if (obj->checkActorDataFlag(this, ActorData::Flag::_47))
            return;
        obj->sub_7100D4AF3C(max_dist);
        return;
    }

    if (group_objs->indexOf(obj) >= 0)
        return;
    if (link_tags->indexOf(obj) >= 0)
        return;

    auto* link_data = obj->mLinkData;
    if (!link_data) {
        if (obj->isNpcOrActiveOrMapPassiveOrFlag1())
            return;
        sead::FixedSafeString<128> path;
        makeProjectMapMuuntPath(path, obj);
        return;
    }

    if (link_tag_none)
        link_tags->pushBack(obj);
    else
        group_objs->pushBack(obj);

    const ObjectLink* link = link_data->mLinksOther.links.getBufferPtr();
    for (s32 i = link_data->mLinksOther.links.size(); i != 0; --i, ++link) {
        if (!ObjectLink::isPlacementLODOrForSaleLink(link->type))
            addAllLinkedActorsToGenGroupRecursively(max_dist, link->other_obj, group_objs,
                                                   link_tags);
    }
    link = link_data->mLinksCs.links.getBufferPtr();
    for (s32 i = link_data->mLinksCs.links.size(); i != 0; --i, ++link) {
        addAllLinkedActorsToGenGroupRecursively(max_dist, link->other_obj, group_objs, link_tags);
    }
    link = link_data->mLinksToSelf.links.getBufferPtr();
    for (s32 i = link_data->mLinksToSelf.links.size(); i != 0; --i, ++link) {
        if (!ObjectLink::isPlacementLODOrForSaleLink(link->type))
            addAllLinkedActorsToGenGroupRecursively(max_dist, link->other_obj, group_objs,
                                                   link_tags);
    }
}

// NON_MATCHING: the actor-flag clear goes through a stack temporary here (the original stores zero
// directly) and the register allocation of the whole function differs. The map find / insert and the
// actor data creation match.
s32 PlacementActors::findOrInsertActorData(const char* name) {
    const u32 hash = sead::HashCRC32::calcStringHash(name);
    if (const auto* node = mActorDataMap.find(hash))
        return node->value();

    const s32 idx = mActorDataMapSize++;
    ActorData& data = mActorData[idx];
    data.mRes.requestedLoad();
    data.mFlags.makeAllZero();
    data._b = 0;
    initActorDataEntry(&data, name);

    return *mActorDataMap.insert(hash, s16(idx));
}

f32 PlacementActors::getMaxTraverseDistForGenGroupRecursively(Object* obj,
                                                             sead::PtrArray<Object>* visited) {
    f32 max_dist = 0.0f;
    if (!obj)
        return max_dist;

    if (visited->indexOf(obj) >= 0)
        return max_dist;

    if (obj->isMapPassive(this))
        return max_dist;

    if (obj->checkActorDataFlag(this, ActorData::Flag::MapConstPassive) &&
        !obj->mActorFlags8.isOn(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall)) {
        const auto* link_data = obj->mLinkData;
        if (!link_data ||
            (link_data->mLinksToSelf.links.size() == 0 &&
             link_data->mLinksOther.links.size() == 1 &&
             link_data->mLinksOther.links[0].type == MapLinkDefType::SyncLink))
            return max_dist;
    }

    if (obj->mFlags.isOn(Object::Flag::IsLinkTag))
        return max_dist;

    max_dist = obj->getDispDistance(this, false, false);
    auto* link_data = obj->mLinkData;
    if (!link_data)
        return max_dist;

    visited->pushBack(obj);

    const ObjectLink* link = link_data->mLinksOther.links.getBufferPtr();
    for (s32 i = link_data->mLinksOther.links.size(); i != 0; --i, ++link) {
        if (!ObjectLink::isPlacementLODOrForSaleLink(link->type))
            max_dist = sead::Mathf::max(
                max_dist, getMaxTraverseDistForGenGroupRecursively(link->other_obj, visited));
    }
    link = link_data->mLinksCs.links.getBufferPtr();
    for (s32 i = link_data->mLinksCs.links.size(); i != 0; --i, ++link) {
        max_dist = sead::Mathf::max(
            max_dist, getMaxTraverseDistForGenGroupRecursively(link->other_obj, visited));
    }
    link = link_data->mLinksToSelf.links.getBufferPtr();
    for (s32 i = link_data->mLinksToSelf.links.size(); i != 0; --i, ++link) {
        if (!ObjectLink::isPlacementLODOrForSaleLink(link->type))
            max_dist = sead::Mathf::max(
                max_dist, getMaxTraverseDistForGenGroupRecursively(link->other_obj, visited));
    }
    return max_dist;
}

PlacementActors::~PlacementActors() {
    for (int i = 0; i < mActorData.size(); ++i)
        deleteActorData(&mActorData[i]);
    delete mObjs;
    mObjs = nullptr;
    delete mStruct1;
    mStruct1 = nullptr;
}

void PlacementActors::removeInnerData1() {
    _e8 = 0;
}

void PlacementActors::clearActorDataAndObjects() {
    for (int i = 0; i < mActorData.size(); ++i)
        deleteActorData(&mActorData[i]);
    if (mObjs)
        mObjs->freeObjects();
    for (auto*& slot : _f8)
        slot = nullptr;
}

// NON_MATCHING: an extra `and w0, w0, #1` on the returned bool
bool PlacementActors::checkResLoadStartedAndFailed() {
    bool result = false;
    for (int i = 0; !result && i < mActorData.size(); ++i)
        result = mActorData[i].mRes.requestedLoad();
    return result;
}

void PlacementActors::freeObjects() {
    if (mObjs)
        mObjs->freeObjects();
}

void PlacementActors::reinitActorDataEntryForTreeBuild() {
    for (int i = 0; i < int(mActorDataMapSize); ++i)
        initActorDataEntry(&mActorData[i], mActorData[i].mActorName.cstr());
}

u32 PlacementActors::getStaticNumInUse() const {
    return mObjs->mGroups[0].num_objs;
}

void PlacementActors::rebuildTree(PlacementTree* tree) {
    sead::TickTime start;
    tree->mLock.writeLock();
    tree->resetPlacementObjPtrs();
    mObjs->x_0(tree);
    tree->mLock.writeUnlock();
    static_cast<void>(start.diffToNow());

    PlacementMgr::instance()->mFlags.reset(PlacementMgr::MgrFlag::_20000);
    PlacementMgr::instance()->mFlags.set(PlacementMgr::MgrFlag::_1);
}

int PlacementActors::getNumGroups() const {
    return mObjs->mGroups.size();
}

// NON_MATCHING: the original stores -1 to _e8 before materialising the false return value; clang
// emits the two instructions in the opposite order.
bool PlacementActors::removeInnerData2() {
    sead::TickTime start;

    if (s32(_e8) < 0) {
        if (mObjs)
            mObjs->freeObjects();
        sead::MemUtil::fillZero(_f8, sizeof(_f8));
        return true;
    }

    for (;;) {
        deleteActorData(&mActorData[_e8]);
        ++_e8;
        if (_e8 == 6000) {
            _e8 = u32(-1);
            return false;
        }
        if (start.diffToNow().toMilliSeconds() > 9)
            return false;
    }
}

void PlacementActors::releaseEffectModel(ActorData* data) {
    if (data->mEffectModelData) {
        eft::Effect::instance()->getModelMgr().requestDeleteModel(nullptr, data->mEffectModelData);
        eft::Effect::instance()->getModelMgr().release(nullptr, data->mEffectModelData);
        data->mEffectModelData = nullptr;
    }

    if (data->mEffectEntry) {
        _2a8078.lock();
        _2a8060.erase(data->mEffectEntry);
        _2a8078.unlock();
        delete data->mEffectEntry;
        data->mEffectEntry = nullptr;
    }
}

void PlacementActors::sub_7100D52C0C() {}

void PlacementActors::sub_7100D58028(ActorData* data) {
    if (!data->mActorFlags8.isOn(ActorFlag8::_8))
        return;

    data->mEffectEntry = new (mEffectHeap, 8) Unk_7100D4D998(data, mEffectHeap);
    _2a8078.lock();
    _2a8060.pushBack(data->mEffectEntry);
    _2a8078.unlock();
}

void PlacementActors::x_7() {
    _2a8078.lock();
    for (auto& obj : _2a8060)
        obj.sub_7100D4DB08();
    _2a8078.unlock();
}

void PlacementActors::x_9() {
    mMutex.lock();
    for (auto*& slot : _f8) {
        auto* obj = slot;
        if (!obj)
            continue;
        if (!obj->shouldSkipSpawn()) {
            if (obj->getFlags0().isOn(Object::Flag0::_1))
                PlacementMgr::instance()->enableObjStaticCompound(obj);
            PlacementMgr::instance()->sub_71011E9C28(obj, true);
        }
        slot = nullptr;
    }
    mMutex.unlock();
}

void PlacementActors::placeObject(Object* obj) {
    if (obj->mProc || obj->mFlags0.isOn(Object::Flag0::_4))
        obj->spawnGenGroupActorsIfNeeded(nullptr);

    if (obj->shouldSkipSpawn()) {
        PlacementMgr::instance()->disableObjStaticCompound(obj);
        PlacementMgr::instance()->sub_71011E9C28(obj, false);
    }

    if (obj->mActorFlags8.isOn(ActorFlag8::CanGetPouch) && obj->getForSaleLink())
        obj->mActorFlags8.reset(ActorFlag8::CanGetPouch);

    if (obj->mLinkData && (obj->mLinkData->findLinkWithType(MapLinkDefType::BasicSig) ||
                           obj->mLinkData->findLinkWithType(MapLinkDefType::BasicSigOnOnly))) {
        obj->setFieldATrue();
    }

    if (act::InfoData::instance()->hasTag(obj->getUnitConfigName(), 0xD53A8775) && obj->mLinkData &&
        obj->mLinkData->mLinksToSelf.findLinkWithType(MapLinkDefType::BasicSig)) {
        obj->mFlags.set(Object::Flag::IsTurnActorBowChargeAndHasBasicSigLink);
    }
}

void PlacementActors::sub_7100D52CA4(Object* obj) {
    mMutex.lock();
    for (int i = 0; i < 128; ++i) {
        if (!_f8[i]) {
            _f8[i] = obj;
            break;
        }
    }
    mMutex.unlock();
}

bool PlacementActors::sub_7100D524B4() const {
    for (int i = 0; i < mActorData.size(); ++i) {
        if (mActorData[i]._b == 1)
            return true;
    }
    return false;
}

Object* PlacementActors::getObj(int group_idx, int object_idx) {
    return &mObjs->mGroups[group_idx].objects[object_idx];
}

Object* PlacementActors::getStaticObj_2(s32 idx) const {
    return &mObjs->mGroups[0].objects[idx];
}

Object* PlacementActors::getStaticObj_0(int object_idx) {
    return &mObjs->mGroups[0].objects[object_idx];
}

Object* PlacementActors::getStaticObj(int object_idx) {
    return &mObjs->mGroups[0].objects[object_idx];
}

int PlacementActors::getNumObjs(int group_idx) const {
    return mObjs->mGroups[group_idx].num_objs;
}

PlacementMap* PlacementActors::getMapNextGroup(int group_idx) const {
    return mObjs->mGroups[group_idx].map;
}

u32 PlacementActors::getNumStaticObjs() const {
    return mObjs->mGroups[0].num_objs;
}

void PlacementActors::setNumInUseForStaticGroup(int num) {
    mObjs->mGroups[0].num_objs = num;
}

Object* PlacementActors::getStaticObj_1(int object_idx) {
    return &mObjs->mGroups[0].objects[object_idx];
}

u32 PlacementActors::allocGroupForDynamicMap(PlacementMap* pmap) {
    return mObjs->allocGroupForDynamicMap(pmap);
}

void PlacementActors::resetGroup(int group_idx) {
    mObjs->resetGroup(group_idx);
}

namespace {
// 0x7101ec0b8c / 0x7101ec0c04 (indexed by the integer part of the bounding size, clamped to the last entry)
constexpr f32 sPassiveTraverseDist[30] = {80.0f, 100.0f, 130.0f, 154.0f, 169.0f, 184.0f, 215.0f, 246.0f, 277.0f, 308.0f, 354.0f, 400.0f, 446.0f, 492.0f, 539.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f, 850.0f, 900.0f, 950.0f, 1000.0f, 1050.0f, 1100.0f, 1300.0f, 1400.0f, 1500.0f, 1600.0f};
constexpr f32 sTraverseDist[15] = {70.0f, 80.0f, 90.0f, 100.0f, 110.0f, 120.0f, 140.0f, 160.0f, 180.0f, 200.0f, 230.0f, 260.0f, 290.0f, 320.0f, 350.0f};
}  // namespace

f32 getActorTraverseDist(const sead::SafeString& name, f32 a2) {
    f32 dist = act::InfoData::instance()->getTraverseDist(name.cstr());
    if (dist > 0.0f) {
        const char* profile;
        act::InfoData::instance()->getActorProfile(&profile, name.cstr());
        const sead::SafeString profile_str(profile);
        if (profile_str.findIndex("Enemy") != -1 || profile_str.findIndex("NPC") != -1)
            dist *= 0.7f;
        return dist;
    }

    f32 size = act::InfoData::instance()->getBoundingForTraverse(name.cstr());
    if (size <= 0.0f)
        size = a2;

    const char* profile;
    act::InfoData::instance()->getActorProfile(&profile, name.cstr());
    const sead::SafeString profile_str(profile);
    if (profile_str.findIndex("Passive") != -1) {
        if (size < 0.3f)
            return 30.0f;
        if (size < 0.5f)
            return 50.0f;
        return sPassiveTraverseDist[std::min(s32(size), 29)];
    }

    if (size < 0.3f)
        return 40.0f;
    if (size < 0.5f)
        return 45.0f;
    if (size < 0.8f)
        return 50.0f;
    return sTraverseDist[std::min(s32(size), 14)] * 0.8f;
}

f32 getActorTraverseDistPlus100(const sead::SafeString& name, f32 a2) {
    return getActorTraverseDist(name, a2) + 100.0f;
}

}  // namespace ksys::map
