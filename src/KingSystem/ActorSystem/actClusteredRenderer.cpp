#include "KingSystem/ActorSystem/actClusteredRenderer.h"
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Map/mapPlacementMgr.h"

namespace ksys::act {

// NON_MATCHING: the compiler folds the positive countdown test into the decrement.
void ClusteredRenderer::requestDraw() {
    if ((_c9c & 0x22) == 0x22) {
        if (_c44 > 0)
            --_c44;
        else
            _108->requestDraw();
    }
    _c3c = _c38;
}

}  // namespace ksys::act

namespace ksys::map {

void sub_7101249DF4(sead::Vector2<s32>* out, const sead::Vector3f* pos) {
    const sead::Vector2f xz(pos->x, pos->z);
    out->x = sead::Mathf::floor((xz.x - sead::Vector2f::zero.x) / 25.0f);
    out->y = sead::Mathf::floor((xz.y - sead::Vector2f::zero.y) / 25.0f);
}

}  // namespace ksys::map
