#include <math/seadMathCalcCommon.h>
#include "Game/gameUnk_71024739d0.h"

namespace uking {

bool sub_710090D904(const sead::Vector3f& pos, const sead::Vector3f& dir, f32 distance, f32 height) {
    sead::Vector3f target = pos;
    target += dir * distance;

    Unk_71024739d0 ray(ksys::phys::GroundHit::HitAll);
    ray.sub_710090D73C();

    sead::Vector3f point = pos;
    point.y += 0.3f;
    ray.setStart(point);
    point = {target.x, target.y + 0.3f, target.z};
    ray.setEnd(point);
    ray.worldRayCast();

    sead::Vector3f normal;
    if (ray.hasHit()) {
        ray.getHitNormal(&normal);
        return sead::Mathf::abs(normal.y) < 0.64278764f;
    }

    ray.mQuery.resetCastResult();
    ray.setStart(point);
    point.y -= height + 1.0f;
    ray.setEnd(point);
    ray.worldRayCast();
    if (!ray.hasHit())
        return true;

    sead::Vector3f hit_pos;
    ray.getHitPosition(&hit_pos);
    if (pos.y - hit_pos.y > height) {
        point.x = hit_pos.x;
        point.z = hit_pos.z;
        point.y = hit_pos.y + 0.1f;
        ray.setStart(point);
        point.x = pos.x;
        point.z = pos.z;
        ray.setEnd(point);
        ray.worldRayCast();
        if (!ray.hasHit())
            return true;

        sead::Vector3f normal2;
        ray.getHitNormal(&normal2);
        return sead::Mathf::abs(normal2.y) < 0.64278764f;
    }
    return false;
}

bool sub_710090DB04(const sead::Vector3f& start, const sead::Vector3f& end,
                    sead::Vector3f* hit_position, sead::Vector3f* hit_normal,
                    ksys::phys::MaterialMask* material_mask) {
    Unk_71024739d0 ray(ksys::phys::GroundHit::HitAll);
    ray.sub_710090D73C();
    ray.setStart(start);
    ray.setEnd(end);
    ray.worldRayCast();
    if (!ray.hasHit())
        return false;

    if (hit_position)
        ray.getHitPosition(hit_position);
    if (hit_normal)
        ray.getHitNormal(hit_normal);
    if (material_mask)
        *material_mask = ray.mQuery.getMaterialMask();
    return true;
}

}  // namespace uking
