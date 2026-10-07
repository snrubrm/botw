#include "KingSystem/World/worldShootingStarMgrEx.h"
#include <cmath>
#include <gfx/seadCamera.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/System/CameraMgr.h"

namespace ksys::world {

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

}  // namespace ksys::world
