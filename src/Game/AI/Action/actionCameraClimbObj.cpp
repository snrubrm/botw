#include "Game/AI/Action/actionCameraClimbObj.h"
#include <cfloat>
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraClimbObj::CameraClimbObj(const InitArg& arg) : CameraAction(arg) {}

CameraClimbObj::~CameraClimbObj() = default;

bool CameraClimbObj::m32(sead::Heap* heap) {
    return true;
}

void CameraClimbObj::m35() {
    if (auto* camera = getCamera())
        camera->_860._7fc.sub_710079B62C(0x200000);
}

// NON_MATCHING: scheduling only (the original stores _64 after computing the new y and uses another register for the
// offset sum).
void CameraClimbObj::m33() {
    _110 = sub_7100924CAC(*mLat_s);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_114, &_118);
    _11c = sub_7100924D40(*mRadius_s);
    _120 = sub_7100924D50(*mFovy_s);
    _124 = 0;
    _125 = 3;

    if (auto* camera = getCamera())
        _74 = camera->_860._48c;

    f32 offset;
    if (auto* camera = getCameraActor()) {
        const f32 dy = camera->_860._2b8.y - camera->_860._48c.y;
        offset = dy * (dy <= 0.0f ? 1.0f : 0.75f);
    } else {
        offset = 0.0f;
    }

    _68 = _74;
    _80 = offset;
    _68.y = offset + (_68.y + *mOffsetY_s);
    _64 = FLT_MAX;
}

void CameraClimbObj::sub_7100755C80() {
    if (auto* camera = getCamera()) {
        const sead::Vector3f d = camera->_860._2b8 - camera->_860._48c;
        if (d.x != 0.0f || d.z != 0.0f) {
            _c8 = act::Unk_7100922700(d)._8;
        } else if (!(_124 & 1)) {
            _c8 = act::Unk_7100922700(camera->_860._0._0 - camera->_860._0._c)._8;
        }
        _124 |= 1;
    }
}

// NON_MATCHING: the final fadd has its operands swapped (s0 + s1 instead of s1 + s0).
void CameraClimbObj::sub_7100755D60() {
    if (auto* camera = getCamera())
        _74 = camera->_860._48c;

    f32 offset;
    if (auto* camera = getCameraActor()) {
        const f32 dy = camera->_860._2b8.y - camera->_860._48c.y;
        offset = dy * (dy <= 0.0f ? 1.0f : 0.75f);
    } else {
        offset = 0.0f;
    }

    const f32 rate = sub_710092523C(sub_71009251C4(getCamera()), 0.6f);
    _68 = _74;
    _80 += rate * (offset - _80);
    _68.y = _80 + (*mOffsetY_s + _74.y);
}

void CameraClimbObj::m36() {
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
}

}  // namespace uking::action
