#pragma once

#include <cull/aglViewFrustumCulling.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <cstddef>

namespace ksys::tera {

class ApertureMapsCollector;

// Shared embedded area metadata: second grid+b8 and first grid+371f8.
// Producer1076A24 copies all16 area bounds and three scales per area.
struct GrassAreaInfo {
    s32 count;
    sead::Vector2f min[16];
    sead::Vector2f max[16];
    sead::Vector3f scales[16];

    void initialize(f32 cell_size, const ApertureMapsCollector& collector);
};
static_assert(offsetof(GrassAreaInfo, min) == 4);
static_assert(offsetof(GrassAreaInfo, max) == 0x84);
static_assert(offsetof(GrassAreaInfo, scales) == 0x104);
static_assert(sizeof(GrassAreaInfo) == 0x1c4);

// Transient 0x4c-byte view information built by 10711EC for both grass grids.
struct GrassViewInfo {
    sead::Vector3f mCameraPosition;
    sead::Vector2f mPosition;
    sead::Vector2f mForward;
    sead::Vector2f mSide;
    f32 mRange;
    f32 mRangeSquared;
    f32 mNear;
    f32 mNearSquared;
    f32 mViewScale;
    f32 mRadius;
    f32 mMargin;
    f32 mRangeRadius;
    f32 mNearMargin;
    bool mFacingUp;

    void initialize(f32 scale, f32 near_coefficient, f32 far_coefficient, f32 cell_size,
                    const sead::Vector3f& position, const agl::cull::ViewFrustumCulling& frustum);
};
static_assert(offsetof(GrassViewInfo, mRange) == 0x24);
static_assert(offsetof(GrassViewInfo, mFacingUp) == 0x48);
static_assert(sizeof(GrassViewInfo) == 0x4c);

// Transient 0xcc-byte culling packet built by 10717BC. Both grid update callers
// keep this packet on the stack; it owns no grid or persistent renderer state.
struct GrassFrustum {
    sead::Vector3f mCameraPosition;
    sead::Vector2f mPosition;
    sead::Vector2f mForward;
    f32 mRange;
    f32 mRangeSquared;
    f32 mNearSquared;
    f32 mViewScale;
    sead::Matrix34f mView;
    sead::Vector3f mViewNormals[4];
    sead::Vector3f mWorldNormals[4];
    f32 mDistances[4];

    void initialize(const GrassViewInfo& info, const agl::cull::ViewFrustumCulling& frustum);
    s32 testSphere(f32 x, f32 y, f32 z, f32 radius, f32 limit, sead::Vector3f* point) const;
    u8 testQuadrants(const sead::BoundBox3f& bounds, sead::Vector3f* point) const;
};
static_assert(offsetof(GrassFrustum, mView) == 0x2c);
static_assert(offsetof(GrassFrustum, mViewNormals) == 0x5c);
static_assert(offsetof(GrassFrustum, mWorldNormals) == 0x8c);
static_assert(offsetof(GrassFrustum, mDistances) == 0xbc);
static_assert(sizeof(GrassFrustum) == 0xcc);

}  // namespace ksys::tera
