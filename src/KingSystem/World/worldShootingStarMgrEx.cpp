#include "KingSystem/World/worldShootingStarMgrEx.h"
#include "Game/gameGraphics.h"
#include <cmath>
#include <cstring>
#include <cstdio>
#include <resource/seadResource.h>
#include <codec/seadHashCRC32.h>
#include "KingSystem/Utils/Byaml/Byaml.h"
#include <math/seadQuat.h>
#include <gfx/seadCamera.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/World/worldManager.h"

// E8DCA8 returns the matching map record's resource handle at +0x58.
ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name);

namespace ksys::world {

ShootingStarAnchor::ShootingStarAnchor()
    : mIdentifier{sead::HashCRC32::calcStringHash("default"), "default"} {
    std::memset(mIdBuffer, 0, sizeof(mIdBuffer));
}

bool ShootingStarMgrEx::sub_71010CFE18() {
    auto* handle = getMapStaticMubin(mMapName);
    if (!handle || !handle->requestedLoad() || !handle->isSuccess())
        return false;
    auto* resource = sead::DynamicCast<sead::DirectResource>(handle->getResource());
    if (!resource)
        return false;
    al::ByamlIter root(resource->getRawData());
    if (!root.isValid())
        return false;
    al::ByamlIter anchors;
    root.tryGetIterByKey(&anchors, "FldObj_DLC_ShootingStarCollaborationAnchor");
    if (!anchors.isValid())
        return false;
    const u32 count = anchors.getSize();
    if (count > 32)
        return false;
    for (u32 i = 0; i < count; ++i) {
        al::ByamlIter entry;
        anchors.tryGetIterByIndex(&entry, i);
        if (!entry.isValid())
            continue;
        auto* anchor = mAnchors.emplaceBack();
        if (!anchor->sub_71010D02C0(entry))
            mAnchors.erase(mAnchors.size() - 1);
    }
    return true;
}

bool ShootingStarAnchor::sub_71010D02C0(const al::ByamlIter& iter) {
    if (!iter.tryGetIntByKey(&mStartHour, "CollaboShootingStarStartHour") ||
        !iter.tryGetIntByKey(&mEndHour, "CollaboShootingStarEndHour") ||
        !iter.tryGetIntByKey(&mDirection, "CollaboShootingStarDirection") ||
        !al::tryGetByamlV3f(&_48, iter, "Translate") ||
        !iter.tryGetStringByKey(&_68, "collaboSSFalloutFlagName") ||
        !iter.tryGetStringByKey(&_70, "collaboSSOpenFlagName") ||
        !iter.tryGetStringByKey(&_78, "collaboSSQuestFlag"))
        return false;
    if (u32(mStartHour) >= 24 || u32(mEndHour) >= 24 || u32(mDirection) >= 8)
        return false;
    if (!_68[0] || !_70[0] || !_78[0])
        return false;
    std::sprintf(mIdBuffer, "%lx", reinterpret_cast<uintptr_t>(this));
    const sead::SafeString name(mIdBuffer);
    mIdentifier.name = name;
    mIdentifier.hash = sead::HashCRC32::calcStringHash(name.cstr());
    return true;
}

// NON_MATCHING: the TU local-static base differs and index arithmetic is promoted to 64 bits.
bool sub_71010D103C() {
    static const sead::Vector2i coords[3]{{0, 0}, {1, 0}, {2, 0}};
    const auto* grid = Graphics::instance()->_378;
    f32 sum = 0.0f;
    for (const auto& coord : coords)
        sum += grid->_18->_12a8[coord.x + grid->_268 * coord.y]._18;
    return sum / 3.0f < -20000.0f;
}


// NON_MATCHING: quaternion/vector temporaries and component-copy scheduling differ.
void ShootingStarAnchor::sub_71010D0814(act::InstParamPack* pack, sead::Vector3f* out_position) {
    if (!pack)
        return;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;
    sead::Vector3f position = sead::Vector3f::zero;
    bool started = false;
    if (gdt::Manager::instance())
        gdt::getBoolByNameNoBool2(gdt::Manager::instance(), &started, _68);
    if (started) {
        position = _48;
    } else {
        sead::Vector3f direction(_48.x - camera->getPos().x, 0.0f,
                                _48.z - camera->getPos().z);
        direction.normalize();
        sead::Quatf rotation;
        rotation.makeVectorRotation(sead::Vector3f(1.0f, 0.0f, 0.0f), direction);
        sead::Vector3f offset(0.0f, 0.0f, 1.0f);
        offset.rotate(rotation);
        const f32 distance = sead::GlobalRandom::instance()->getF32Range(-500.0f, 500.0f);
        position = camera->getPos() + sead::Vector3f(0.0f, 500.0f, 0.0f) + offset * distance;
    }
    act::ActorCreator::addAITreeParam(*pack, mIdentifier.name, "CollaboShootingStarId");
    pack->getBuffer().addPosition(position);
    if (out_position)
        *out_position = position;
}



// NON_MATCHING: the final distance tests: the original branches on the 2000 bound and sets the result
// from the 25 bound directly; ours merges the result with an `and`. Same checks and constants.
bool ShootingStarAnchor::sub_71010D0D78() const {
    if (!sub_71010D0734())
        return false;
    if (sub_71010D07A4())
        return false;
    if (!sub_71010D0F64(2))
        return false;
    if (_89)
        return false;
    f32 dist = 0.0f;
    if (auto* camera = CameraMgr::instance()->getLookAtCamera()) {
        const f32 dx = _48.x - camera->getPos().x;
        const f32 dz = _48.z - camera->getPos().z;
        dist = std::sqrt(dx * dx + dz * dz);
        if (dist > 2000.0f)
            return false;
    }
    if (dist < 25.0f)
        return false;
    return true;
}

// NON_MATCHING: the inlined hour-range branches and common false-return block differ.
bool ShootingStarAnchor::sub_71010D0B64() const {
    if (_89)
        return false;
    if (auto* manager = gdt::Manager::instance()) {
        bool started = false;
        gdt::getBoolByNameNoBool2(manager, &started, _68);
        if (started)
            return false;
        if (auto* manager = gdt::Manager::instance()) {
            bool finished = false;
            gdt::getBoolByNameNoBool2(manager, &finished, _70);
            if (finished)
                return false;
        }
    }
    if (!sub_71010D0F64(0))
        return false;
    const auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;
    const f32 dx = _48.x - camera->getPos().x;
    const f32 dz = _48.z - camera->getPos().z;
    const f32 distance = dx * dx + dz * dz;
    if (!(distance > 40000.0f))
        return false;
    if (!(distance < 250000.0f))
        return false;
    if (!sub_71010D103C())
        return false;
    bool available;
    bool in_view;
    sub_71010D1130(&available, &in_view);
    if (!available || !in_view)
        return false;
    return !(_2c < 10.0f);
}

bool ShootingStarAnchor::sub_71010D0F64(s32 hour_offset) const {
    const s32 hour = Manager::instance()->getTimeMgr()->getHour();
    const s32 start = mStartHour % 24;
    const s32 end = (mEndHour + hour_offset) % 24;
    if (start == end)
        return hour == start;
    if (start < end)
        return start <= hour && hour < end;
    return (start <= hour && hour < 24) || (hour >= 0 && hour < end);
}

void ShootingStarAnchor::sub_71010D1348(bool value) const {
    if (auto* manager = gdt::Manager::instance())
        manager->setBool(value, _68);
}



ShootingStarAnchor::~ShootingStarAnchor() = default;

// NON_MATCHING: the SafeString temporaries and parameter pack use stack offset 0 rather than 8.
void ShootingStarAnchor::sub_71010D00B0() {
    if (gdt::Manager::instance()) {
        bool enabled = false;
        gdt::getBoolByNameNoBool2(gdt::Manager::instance(), &enabled, _78);
        _88 = enabled;
        if (gdt::Manager::instance()) {
            bool started = false;
            gdt::getBoolByNameNoBool2(gdt::Manager::instance(), &started, _68);
            if (started) {
                bool finished = false;
                if (gdt::Manager::instance())
                    gdt::getBoolByNameNoBool2(gdt::Manager::instance(), &finished, _70);
                if (!finished && _88) {
                    auto* camera = CameraMgr::instance()->getLookAtCamera();
                    if (!camera ||
                        std::sqrt((_48.x - camera->getPos().x) * (_48.x - camera->getPos().x) +
                                  (_48.z - camera->getPos().z) * (_48.z - camera->getPos().z)) <
                            2000.0f) {
                        act::InstParamPack pack;
                        sub_71010D0814(&pack, nullptr);
                        if (!_89) {
                            auto* creator = act::ActorCreator::instance();
                            creator->requestCreateActor("FldObj_DLC_ShootingStarCollaboration",
                                                        act::BaseProcHeapMgr::instance()->getHeap(),
                                                        nullptr, &pack, nullptr, 1);
                            _89 = true;
                        }
                    }
                }
            }
        }
    } else {
        _88 = false;
    }
    _60 = sead::GlobalRandom::instance()->getF32() + 0.5f;
}


bool ShootingStarAnchor::sub_71010D0734() const {
    if (gdt::Manager::instance()) {
        bool result = false;
        gdt::getBoolByNameNoBool2(gdt::Manager::instance(), &result, _68);
        return result;
    }
    return false;
}

bool ShootingStarAnchor::sub_71010D07A4() const {
    if (gdt::Manager::instance()) {
        bool result = false;
        gdt::getBoolByNameNoBool2(gdt::Manager::instance(), &result, _70);
        return result;
    }
    return false;
}

void ShootingStarAnchor::sub_71010D1394() {
    _2c = 0;
    _89 = false;
}

// 0x710250cb50 (TU-local, .data)
static const sead::SafeString sUnk_710250CB50 = "MainField";

ShootingStarMgrEx::ShootingStarMgrEx() : mMapName(sUnk_710250CB50) {}

ShootingStarMgrEx::~ShootingStarMgrEx() {
    mAnchors.freeBuffer();
}

void ShootingStarMgrEx::init_(sead::Heap* heap) {
    ShootingStarMgr::init_(heap);
    mAnchors.allocBuffer(32, heap);
}

void ShootingStarMgrEx::calc_() {
    ShootingStarMgr::calc_();
    for (size_t i = 0; i < size_t(mAnchors.size()); ++i)
        mAnchors.at(i)->calcShootingStarDLC();
}

void ShootingStarMgrEx::spawnStar() {
    ShootingStarMgr::spawnStar();
    mAnchors.clear();
    sub_71010CFE18();
    for (size_t i = 0; i < size_t(mAnchors.size()); ++i)
        mAnchors.at(i)->sub_71010D00B0();
}

f32 ShootingStarMgrEx::sub_71010D05F0() {
    return 20.0f;
}

ShootingStarAnchor* ShootingStarMgrEx::sub_71010D0464(const ShootingStarAnchor::Identifier& id) {
    auto* manager = Manager::instance();
    if (!manager)
        return nullptr;
    auto* stars = sead::DynamicCast<ShootingStarMgrEx>(manager->getShootingStarMgr());
    if (!stars)
        return nullptr;
    for (u32 i = 0; i < stars->mAnchors.size(); ++i) {
        auto* anchor = stars->mAnchors.unsafeAt(i);
        if (anchor->mIdentifier.hash == id.hash && anchor->mIdentifier.name == id.name)
            return anchor;
    }
    return nullptr;
}

const sead::SafeString& ShootingStarMgrEx::sub_71010D05F8() {
    auto* mgr = Manager::instance();
    if (!mgr)
        return sUnk_710250CB50;
    auto* star_mgr = sead::DynamicCast<ShootingStarMgrEx>(mgr->getShootingStarMgr());
    if (!star_mgr)
        return sUnk_710250CB50;
    return star_mgr->mMapName;
}

void ShootingStarMgrEx::sub_71010D06C4(const sead::SafeString& name) {
    for (u32 i = 0; i < mAnchors.size(); ++i) {
        // The original calls cstr() and discards the result, then reads the string top directly.
        name.cstr();
        auto* anchor = mAnchors.unsafeAt(i);
        if (std::strcmp(name.getStringTop(), anchor->_68) == 0)
            anchor->_84 = 0;
    }
}

}  // namespace ksys::world
