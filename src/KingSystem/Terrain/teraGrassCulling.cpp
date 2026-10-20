#include "KingSystem/Terrain/teraGrassCulling.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include <cstring>
#include <limits>

namespace ksys::tera {

// NON_MATCHING: area pointer reloads and coordinate stores differ in scheduling.
void GrassAreaInfo::initialize(f32 cell_size, const ApertureMapsCollector& collector) {
    count = collector._2942;
    for (s32 i = 0; i < 16; ++i) {
        const auto& position = collector._0[0]._0[i];
        const f32 half_size = position._18 * 0.5f;
        min[i].set(position.pos.x - half_size, position.pos.y - half_size);
        max[i].set(position.pos.x + half_size, half_size + position.pos.y);
        const f32 width = max[i].x - min[i].x;
        const f32 height = max[i].y - min[i].y;
        scales[i].set(1.0f / width, 1.0f / height, cell_size / width);
    }
}

// NON_MATCHING: scalar arithmetic and normalized vector stores differ in scheduling.
void GrassViewInfo::initialize(f32 scale, f32 near_coefficient, f32 far_coefficient, f32 cell_size,
                               const sead::Vector3f& position,
                               const agl::cull::ViewFrustumCulling& frustum) {
    mCameraPosition = position;
    mPosition.set(position.x, position.z);
    const auto& view = frustum.getViewMatrix();
    const auto direction = view.getRow(2);
    mForward.set(-direction.x, -direction.z);
    mForward.normalize();
    mSide.set(-mForward.y, mForward.x);
    const f32 vertical_extent = frustum.get_f4();
    const f32 aspect = frustum.getAspect();
    mViewScale = vertical_extent > scale ? vertical_extent : scale;
    const f32 horizontal_extent = vertical_extent * aspect;
    mRadius = std::sqrt(vertical_extent * vertical_extent + horizontal_extent * horizontal_extent);
    const f32 horizontal_margin = aspect * 0.087488666f;
    mMargin = std::sqrt(horizontal_margin * horizontal_margin + 0.007654267f);
    mRange = std::numeric_limits<f32>::max();
    if (!(near_coefficient <= 0.0f)) {
        if (near_coefficient == std::numeric_limits<f32>::max())
            mRange = 0.0f;
        else
            mRange = 1.0f / (mViewScale * near_coefficient);
    }
    f32 far = std::numeric_limits<f32>::max();
    if (!(far_coefficient <= 0.0f)) {
        if (far_coefficient == std::numeric_limits<f32>::max())
            far = 0.0f;
        else
            far = 1.0f / (mViewScale * far_coefficient);
    }
    mRange -= far;
    mRangeSquared = mRange * mRange;
    mNear = std::numeric_limits<f32>::max();
    if (!(near_coefficient <= 0.0f)) {
        if (near_coefficient == std::numeric_limits<f32>::max())
            mNear = 0.0f;
        else
            mNear = 1.0f / (scale * near_coefficient);
    }
    mNearSquared = mNear * mNear;
    const f32 extent = cell_size * 0.5f * 1.4142135f + mRadius;
    mRangeRadius = mRange * mRadius;
    mNearMargin = mNear * mMargin;
    const auto up = view.getRow(1);
    sead::Vector3f normal{-up.x * extent - direction.x,
                          -up.y * extent - direction.y,
                          -up.z * extent - direction.z};
    normal.normalize();
    mFacingUp = direction.x * sead::Vector3f::ey.x + direction.y * sead::Vector3f::ey.y +
                    direction.z * sead::Vector3f::ey.z <
                -normal.y * sead::Vector3f::ey.y - normal.x * sead::Vector3f::ey.x -
                normal.z * sead::Vector3f::ey.z;
}

// NON_MATCHING: plane copies and rotation stores differ in scheduling.
void GrassFrustum::initialize(const GrassViewInfo& info,
                              const agl::cull::ViewFrustumCulling& frustum) {
    mCameraPosition = info.mCameraPosition;
    mPosition = info.mPosition;
    mForward = info.mForward;
    mRange = info.mRange;
    mRangeSquared = info.mRangeSquared;
    mNearSquared = info.mNearSquared;
    mViewScale = info.mViewScale;
    std::memcpy(&mView, &frustum.getViewMatrix(), sizeof(mView));
    mViewNormals[0] = frustum.getViewPlaneNormal(0);
    mViewNormals[1] = frustum.getViewPlaneNormal(1);
    mViewNormals[2] = frustum.getViewPlaneNormal(3);
    mViewNormals[3] = frustum.getViewPlaneNormal(2);
    for (s32 i = 0; i < 4; ++i)
        mWorldNormals[i].setRotated(frustum.getInverseViewMatrix(), mViewNormals[i]);
    for (s32 i = 0; i < 4; ++i)
        mDistances[i] = -mCameraPosition.dot(mWorldNormals[i]);
}

// NON_MATCHING: the scalar side-plane tests differ in branching and scheduling.
s32 GrassFrustum::testSphere(f32 x, f32 y, f32 z, f32 radius, f32 limit,
                            sead::Vector3f* point) const {
    point->x = mView(0, 3) + (x * mView(0, 0) + y * mView(0, 1) + z * mView(0, 2));
    point->y = mView(1, 3) + (x * mView(1, 0) + y * mView(1, 1) + z * mView(1, 2));
    point->z = mView(2, 3) + (x * mView(2, 0) + y * mView(2, 1) + z * mView(2, 2));
    const f32 inner = -radius;
    bool inside = true;
    s32 plane = 0;
    for (; plane < 4; ++plane) {
        const f32 distance = point->dot(mViewNormals[plane]);
        if (!(distance < inner)) {
            if (!(distance < limit))
                return -1;
            inside = false;
            ++plane;
            break;
        }
    }
    for (; plane < 4; ++plane)
        if (!(point->dot(mViewNormals[plane]) < limit))
            return -1;
    return inside ? 1 : 0;
}

// NON_MATCHING: quadrant bounds tests differ in scheduling.
u8 GrassFrustum::testQuadrants(const sead::BoundBox3f& bounds, sead::Vector3f* point) const {
    const auto& min = bounds.getMin();
    const auto& max = bounds.getMax();
    const f32 x_middle = (min.x + max.x) * 0.5f;
    const f32 z_middle = (min.z + max.z) * 0.5f;
    u32 mask = 15;
    for (s32 i = 0; i < 4; ++i) {
        const auto& normal = mWorldNormals[i];
        point->y = normal.y > 0.0f ? min.y : max.y;
        if (mask & 1) {
            point->x = normal.x > 0.0f ? min.x : x_middle;
            point->z = normal.z > 0.0f ? min.z : z_middle;
            if (mDistances[i] + point->dot(normal) > 0.0f)
                mask &= ~1;
        }
        if (mask & 2) {
            point->x = normal.x > 0.0f ? x_middle : max.x;
            point->z = normal.z > 0.0f ? min.z : z_middle;
            if (mDistances[i] + point->dot(normal) > 0.0f)
                mask &= ~2;
        }
        if (mask & 4) {
            point->x = normal.x > 0.0f ? min.x : x_middle;
            point->z = normal.z > 0.0f ? z_middle : max.z;
            if (mDistances[i] + point->dot(normal) > 0.0f)
                mask &= ~4;
        }
        if (mask & 8) {
            point->x = normal.x > 0.0f ? x_middle : max.x;
            point->z = normal.z > 0.0f ? z_middle : max.z;
            if (mDistances[i] + point->dot(normal) > 0.0f)
                mask &= ~8;
        }
    }
    return mask;
}

}  // namespace ksys::tera
