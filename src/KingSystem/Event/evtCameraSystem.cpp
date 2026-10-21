#include "KingSystem/Event/evtEventResource.h"
#include <gsys/gsysCameraAnimation.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Actor/actCamera.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Resource/resUnk_71024F9898.h"

namespace ksys::evt {

// 0x7100da38d4
bool isCameraActor(const sead::SafeString& name) {
    return name == "eraCamera" || name == "GameRomCamera";
}

// 0x7100da39d4
bool isCameraAnimAction(const sead::SafeString& name) {
    return name == "Demo_CameraAnim" || name == "Demo_CameraAnimFlow" ||
           name == "Demo_AnimFlowForMapTower" || name == "Demo_CameraAnimFlowAbs";
}

// 0x7100da3d14
bool CameraSystem::sub_7100DA3D14(void*) {
    bool all_success = true;
    for (s32 i = 0; i < _30; ++i) {
        auto& handle = _10[i];
        handle.parseResource(nullptr);
        all_success &= handle.isSuccess();
    }
    _8 = all_success ? 3 : 4;
    return true;
}

// NON_MATCHING: the identity matrix into the scene animation is a copy-constructed 48-byte block copy in
// the original; ours copies ident element-wise (two instructions longer).
// 0x7100da44ec
bool CameraSystem::sub_7100DA44EC(const sead::SafeString& name, const sead::Matrix34f& mtx) {
    if (_8 != 3)
        return false;
    if (_30 < 1)
        return false;

    for (s32 i = 0; i < _30; ++i) {
        if (!(name == _20[i]))
            continue;

        auto* camera = Manager::instance()->getCamera();
        auto* resource = sead::DynamicCast<res::Unk_71024F9898>(_10[i].getResource());
        if (resource->_40) {
            resource->_40->mMatrix = sead::Matrix34f::ident;
            mAnimSource.mAnim = resource->_40;
            mAnimSource.mSceneAnim = nullptr;
        } else if (resource->_48) {
            auto* anim = _2c0;
            anim->mData = resource->_48;
            anim->_100 = 1;
            // C++14 evaluation order: the original evaluates the destination first
            _2c0->mMatrix.operator=(sead::Matrix34f::ident);
            mAnimSource.mSceneAnim = _2c0;
            mAnimSource.mAnim = nullptr;
        }

        _280 = mtx;
        camera->m157(&mAnimSource, _280);
        return true;
    }

    return false;
}

// NON_MATCHING: the original stores `lane_id = 2` / `flags = 4` as one `stp w8, w9` (ours: two `str`, scheduled around
// the SafeString name stores)
bool CameraSystem::finishLoad() {
    if (_8 == 1) {
        bool all_ready = true;
        for (s32 i = 0; i < _30; ++i)
            all_ready &= _10[i].isReadyOrNeedsParse();
        if (all_ready) {
            _8 = 2;
            LowPrioThreadMgr::Request request;
            request.lane_id = 2;
            request.flags.setDirect(4);
            request.delegate = &_2c8;
            submitLowPriorityRequest(request);
        }
    }
    return u32(_8 - 1) > 1;
}

}  // namespace ksys::evt
