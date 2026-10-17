#include "KingSystem/Map/mapObjectGenGroup.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDebug.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementAreaMgr.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapLinkTag.h"
#include "KingSystem/System/SystemTimers.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <thread/seadThread.h>

namespace ksys::map {

bool GenGroup::sub_7100D507F8() {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    const s32 num_prepare_delete = mNumPrepareDelete;
    if (num_prepare_delete != mObjects.size())
        return false;
    if (mInitState != 2 && (mInitState != 3 || _4 != num_prepare_delete))
        return false;
    if (!_0.compareExchange(0, 1))
        return false;
    bool deleted = false;
    for (auto& obj : mObjects) {
        if (auto* actor = obj.getActor())
            actor->x_34(&deleted);
        else if (auto* tag = sead::DynamicCast<LinkTag>(obj.getProc()))
            tag->_1de = 1;
    }
    _0 = 2;
    if (!deleted)
        deleteEachActorIfDeleteType2();
    return true;
}

void GenGroup::deleteEachActorIfDeleteType2() {
    if (!tera::checkTeraSystemStatus()) {
        auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
        thread->getPriority();
    }
    if (!_0.compareExchange(2, 3))
        return;
    for (auto& obj : mObjects) {
        auto* proc = obj.getProc();
        if (!proc)
            continue;
        if (auto* actor = sead::DynamicCast<act::Actor>(proc)) {
            actor->deleteIfDeleteType2();
        } else if (proc->deleteLater(act::BaseProc::DeleteReason::_0)) {
            obj.setFlags0(Object::Flag0::ActorCreated);
            if (auto* mgr = PlacementMgr::instance())
                mgr->sub_71011EB46C(&obj);
        }
    }
}

// NON_MATCHING: the original addresses the PtrArray through `this` (no copy of `&mObjects` kept in a second
// callee-saved register) and null-tests `this` before the final size check
void GenGroup::sub_7100D50778(Object* obj) {
    const s32 idx = mObjects.indexOf(obj);
    if (idx < 0)
        return;
    mObjects.erase(idx);
    if (mObjects.size() == 0) {
        mObjects.freeBuffer();
        delete this;
    }
}

// NON_MATCHING: the original keeps the three byte stores at the end separate (ours merges two into a strh) and
// addresses the counters through a second base register.
void GenGroup::sub_7100D50AA8() {
    if (_4 != 0)
        return;

    if (mObjects.size() == mObjects.capacity()) {
        if (mNumPrepareDelete != mObjects.size()) {
            // The original builds a status text for a debug print here (dropped in release builds).
            sead::FixedSafeString<1024> text;
            text.format("グループ内数(%d), LinkTag数(%d)\n", mObjects.size(), _18);
            text.appendWithFormat(" 存在アクタ数(%d), ステート(%d), 削除準備数(%d), 生成itr(%d)\n", s32(_4),
                                  u32(_0), s32(mNumPrepareDelete), s32(_c));
            text.appendWithFormat("実行待ちLinkTag(%d), 実行待ち他(%d)\n", s32(_10), s32(_14));
            text.appendWithFormat("初期完了ステート(%d), LinkTag実行(%d)\n", mInitState, mNumExecLinkTag);
            text.appendWithFormat("グローバルカウンタ( %x : %x, %x, %x )\n",
                                  SystemTimers::instance()->mFrameCounter, _20, _24, _28);
            mNumPrepareDelete = mObjects.capacity();
        }
        if (_10 != 0) {
            sead::FixedSafeString<1024> text;
            text.format("グループ内数(%d), LinkTag数(%d)\n", mObjects.size(), _18);
            text.appendWithFormat(" 存在アクタ数(%d), ステート(%d), 削除準備数(%d), 生成itr(%d)\n", s32(_4),
                                  u32(_0), s32(mNumPrepareDelete), s32(_c));
            text.appendWithFormat("実行待ちLinkTag(%d), 実行待ち他(%d)\n", s32(_10), s32(_14));
            text.appendWithFormat("初期完了ステート(%d), LinkTag実行(%d)\n", mInitState, mNumExecLinkTag);
            text.appendWithFormat("グローバルカウンタ( %x : %x, %x, %x )\n",
                                  SystemTimers::instance()->mFrameCounter, _20, _24, _28);
            _10 = 0;
        }
        if (_14 != 0) {
            sead::FixedSafeString<1024> text;
            text.format("グループ内数(%d), LinkTag数(%d)\n", mObjects.size(), _18);
            text.appendWithFormat(" 存在アクタ数(%d), ステート(%d), 削除準備数(%d), 生成itr(%d)\n", s32(_4),
                                  u32(_0), s32(mNumPrepareDelete), s32(_c));
            text.appendWithFormat("実行待ちLinkTag(%d), 実行待ち他(%d)\n", s32(_10), s32(_14));
            text.appendWithFormat("初期完了ステート(%d), LinkTag実行(%d)\n", mInitState, mNumExecLinkTag);
            text.appendWithFormat("グローバルカウンタ( %x : %x, %x, %x )\n",
                                  SystemTimers::instance()->mFrameCounter, _20, _24, _28);
            _14 = 0;
        }
    } else {
        mNumPrepareDelete = mObjects.capacity();
        _10 = 0;
        _14 = 0;
    }

    mInitState = 0;
    _1f = 0;
    mNumExecLinkTag = 0;
    _0 = 0;
    _c = 0;
    _1d = 0;
}

bool GenGroup::sub_7100D50E00() {
    if (_0)
        return true;
    if (!_1c)
        return false;
    auto* debug = act::ActorDebug::instance();
    if (!debug)
        return false;
    return debug->hasFlag(act::ActorDebug::Flag::_10000000);
}

bool GenGroup::sub_7100D50E44(bool a1) {
    if (a1) {
        _10.increment();
        return true;
    }
    if (mInitState == 3)
        return false;
    _14.increment();
    return true;
}

void GenGroup::sub_7100D50E90(bool a1) {
    if (a1) {
        _10.decrement();
        mInitState = 0;
        return;
    }
    _14.decrement();
    if (mHasCreateOrDeleteLinks)
        mInitState = 3;
    else if (mInitState == 2)
        mInitState = _18 != 0;
}

bool GenGroup::sub_7100D50EF4(bool a1) {
    auto* timers = SystemTimers::instance();
    if (!timers)
        return false;
    if (mInitState == 3) {
        if (a1 || !_1f || _14 != 0)
            return false;
        _1f = 0;
        mInitState = _18 != 0;
        return false;
    }

    const u32 frame = timers->mFrameCounter;
    if (a1 ? frame == _24 : frame == _20)
        return false;
    if (mInitState == 2)
        return true;
    if (mInitState == 1) {
        if (a1)
            return true;
        if (!mNumExecLinkTag || _10 + _14 != mObjects.size())
            return false;
    } else if (a1) {
        if (_10 != _18)
            return false;
        _24 = frame;
        mInitState = 1;
        return false;
    } else {
        if (_18 || _14 != mObjects.size())
            return false;
    }
    _20 = frame;
    mInitState = 2;
    return false;
}

bool GenGroup::checkContainsObjWithName(const sead::SafeString& name, const u32* mode) {
    for (auto& object : mObjects) {
        const sead::SafeString object_name(object.getUnitConfigName());
        switch (*mode) {
        case 0:
            if (object_name == name)
                return true;
            break;
        case 1:
            if (object_name.include(name))
                return true;
            break;
        case 2:
            if (object_name.startsWith(name))
                return true;
            break;
        case 3:
            if (object_name.endsWith(name))
                return true;
            break;
        }
    }
    return false;
}

bool GenGroup::sub_7100D51064() {
    auto* mgr = PlacementMgr::instance();
    for (auto& obj : mObjects) {
        if (obj.getProc() || !mgr->objStuff(&obj))
            return false;
    }
    return true;
}

bool GenGroup::sub_7100D51134() {
    for (auto& obj : mObjects) {
        auto* actor = obj.tryGetActor(false);
        if (!actor)
            continue;
        if (actor->get1a0())
            return true;
        if (auto* map_obj = actor->getMapObject()) {
            if (map_obj->getFlags0().isOn(Object::Flag0::_20000))
                return true;
        }
    }
    return false;
}

bool GenGroup::x(const u16* id) {
    for (auto& obj : mObjects) {
        if (obj.getId() == *id)
            return false;
    }
    return true;
}

// NON_MATCHING: the original loads the 16-bit flags of the object (ldrh) instead of the low byte (ldrb)
void GenGroup::sub_7100D5119C(Object* obj) {
    if (mInitState == 2)
        return;
    if (_4 == mObjects.size())
        return;

    auto* actors = PlacementMgr::instance()->mPlacementActors;
    if (!_c.compareExchange(0, 1))
        return;

    bool spawned = false;
    for (auto& object : mObjects) {
        if (!spawned && object.getFlags().isOn(Object::Flag::IsLinkTag))
            break;
        spawned |= actors->spawnGenGroupActor(&object, obj);
    }
    _c = 0;
}

void GenGroup::sub_7100D51250(bool a1, u32 a2) {
    for (auto& obj : mObjects) {
        if (a1)
            obj.setFlags0(Object::Flag0(1u << a2));
        else
            obj.resetFlags0(Object::Flag0(1u << a2));
    }
}

void GenGroup::sub_7100D51D78(Object* except) {
    auto* mgr = PlacementMgr::instance();
    if (!mgr)
        return;
    auto* actors = mgr->mPlacementActors;
    if (!actors)
        return;

    for (auto& obj : mObjects) {
        if (&obj == except)
            continue;
        if (!actors->mActorData[obj.getActorDataIdx()].mFlags.isOnBit(ActorData::Flag::OnLowTree))
            continue;

        if (obj.getId() == mgr->_1e4) {
            if (auto* link_data = obj.getLinkData())
                link_data->field_57 = true;
        } else {
            mgr->sub_71011E9C28(&obj, false);
            mgr->disableObjStaticCompound(&obj);
            obj.mFlags0.set(Object::Flag0(0x100400));
        }
    }
}

// NON_MATCHING: same loop; the original computes the end pointer and the odd-count test before it branches on `on`.
void GenGroup::sub_7100D513F4(const u32* bit, bool on) {
    for (auto& obj : mObjects) {
        if (on)
            obj.mHardModeFlags.set(Object::HardModeFlag(1 << *bit));
        else
            obj.mHardModeFlags.reset(Object::HardModeFlag(1 << *bit));
    }
}

// NON_MATCHING: same code, different register allocation (x10 / x11 swapped)
bool GenGroup::sub_7100D51330(const u32* a1) {
    for (auto& obj : mObjects) {
        if (obj.getActorData().mFlags.isOnBit(ActorData::Flag(*a1)))
            return true;
    }
    return false;
}

bool GenGroup::sub_7100D51E6C() {
    s32 count = 0;
    for (auto it = mObjects.begin(), end = mObjects.end(); it != end; ++it) {
        auto* actor = (*it).tryGetActor(false);
        if (actor ? actor->isDeletedOrDeleting() : !(*it).getFlags().isOn(Object::Flag::IsLinkTag))
            ++count;
    }
    return count == mObjects.size() - _18;
}

// NON_MATCHING: Candidate filtering and distance calculations use different register allocation.
Object* GenGroup::sub_7100D514E8(const sead::Vector3f* pos) {
    _30 = 1000.0f;
    bool checked_area = false;
    bool contains_event_tag = false;
    bool has_saved_link_tag = false;
    for (auto& obj : mObjects) {
        if (sead::SafeString(obj.getUnitConfigName()) == "Area") {
            if (!checked_area) {
                const u32 mode = 0;
                contains_event_tag = checkContainsObjWithName("EventTag", &mode);
                for (auto& other : mObjects) {
                    if (other.getFlags().isOn(Object::Flag::IsLinkTag) &&
                        other.getRevivalGameDataFlagHash() != gdt::InvalidHandle) {
                        has_saved_link_tag = true;
                        break;
                    }
                }
                checked_area = true;
            }
            if (!contains_event_tag && !has_saved_link_tag)
                continue;
        }
        if (obj.getHardModeFlags().isOn(Object::HardModeFlag::ActorCreated) ||
            obj.getActorData().mFlags.isOnBit(ActorData::Flag::Dragon) ||
            obj.getActorFlags8().isOff(ActorFlag8::EnemyOrNpcOrActiveOrAreaOrAirWall) ||
            obj.shouldSkipSpawn())
            continue;
        if (sead::SafeString(obj.getUnitConfigName()).endsWith("_Trunk") ||
            sead::SafeString(obj.getUnitConfigName()).endsWith("_Stump") ||
            sead::SafeString(obj.getUnitConfigName()).startsWith("Weapon_") ||
            sead::SafeString(obj.getUnitConfigName()).startsWith("Animal_"))
            continue;
        if (obj.getActorData().mFlags.isOnBit(ActorData::Flag::IgnoreBoundingAtAreaCulling) &&
            obj.getActorData().mFlags.isOffBit(ActorData::Flag::NpcOrNonGanonAndNonGuardianEnemy))
            continue;
        const auto translate = obj.getTranslate();
        const f32 radius = obj.getActorData()._10c * obj.getScale().x;
        if (PlacementMgr::instance()->mPlacementActors->mStruct1->boundsChecking(
                translate, radius, &obj, false))
            continue;
        const f32 display_distance = obj.getDispDistance(false, false);
        if (display_distance > 1000.0f || display_distance == 0.0f)
            continue;
        const f32 dx = pos->x - obj.getTranslate().x;
        const f32 dz = pos->z - obj.getTranslate().z;
        const f32 distance = sead::Mathf::sqrt(dx * dx + dz * dz) - obj.getTraverseDistInt();
        if (distance <= 0.0f) {
            _30 = 0.0f;
            return &obj;
        }
        if (distance < _30)
            _30 = distance;
    }
    return nullptr;
}

void GenGroup::sub_7100D510D0() {
    if (_1d)
        return;
    if (auto* timers = SystemTimers::instance()) {
        _1d = 1;
        _28 = timers->mFrameCounter;
    }
}

u8 GenGroup::sub_7100D510FC() {
    if (_1d) {
        auto* timers = SystemTimers::instance();
        if (timers && timers->mFrameCounter != _28)
            return true;
    }
    return false;
}

}  // namespace ksys::map
