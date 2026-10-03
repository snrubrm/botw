#include "KingSystem/ActorSystem/LOD/actLODMgr.h"
#include <prim/seadMemUtil.h>
#include <heap/seadHeap.h>
#include <gfx/seadCamera.h>
#include "KingSystem/System/CameraMgr.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(LODMgr)

LODMgr::~LODMgr() {
    if (_21b8)
        delete _21b8;
    _1838.freeBuffer();
}

void LODMgr::init(sead::Heap* heap) {
    const sead::Heap* const heap_arg = heap;
    _21b8 = new (heap, 8) Unk_71011086dc();
    _21b8->sub_7101108774(heap_arg);
    _1838.allocBuffer(512, heap, 8);
}

void LODMgr::initBeforeStageGenB() {
    _1028 = 0;
    _1830 = 0;
    _21a0 = 0;
    _2610 = 0;
    _2a20 = 0;
    _1c80 = 0;
    _1878 = 0;
    _2110.fill(0);
}

// NON_MATCHING: the loads of the two camera vectors are grouped / scheduled differently
void LODMgr::sub_7101251B08(sead::Vector3f* pos) {
    if (!pos)
        return;
    auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return;
    sead::Vector3f dir;
    dir.setSub(camera->getAt(), camera->getPos());
    dir.normalize();
    *pos = camera->getPos();
    *pos += dir * 5.0f;
}

}  // namespace ksys::act
