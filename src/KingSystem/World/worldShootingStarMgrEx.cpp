#include "KingSystem/World/worldShootingStarMgrEx.h"
#include <cmath>
#include <cstring>
#include <math/seadQuat.h>
#include <gfx/seadCamera.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

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
