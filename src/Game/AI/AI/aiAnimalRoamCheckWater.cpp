#include "Game/AI/AI/aiAnimalRoamCheckWater.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"

// Adjacent to AnimalRoamCheckWater::m38/m39 in the original; keep this terrain query in the owner TU.
// 0x710030c688 (placeholder name): how far the terrain is above the highest ground below `pos` (searched `limit` below).
f32 sub_710030C688(void*, const sead::Vector3f* pos, f32 limit) {
    f32 terrain_height = 0.0f;
    if (!sub_710072C494(&terrain_height, pos))
        return 0.0f;

    const sead::Vector3f from = *pos + sead::Vector3f(0.0f, 3.0f, 0.0f);
    const sead::Vector3f to(from.x, from.y - limit, from.z);
    sead::Vector3f hit_pos;
    f32 ground_height;
    if (sub_710072EA18(from, to, 0, &hit_pos, nullptr, nullptr, 0.0f)) {
        ground_height = hit_pos.y;
    } else {
        f32 height = -10000.0f;
        sub_710072C21C(&height, pos);
        ground_height = sead::Mathf::max(pos->y, height);
    }
    return terrain_height - ground_height;
}

namespace uking::ai {

AnimalRoamCheckWater::AnimalRoamCheckWater(const InitArg& arg) : AnimalRoam(arg) {}

AnimalRoamCheckWater::~AnimalRoamCheckWater() = default;

bool AnimalRoamCheckWater::init_(sead::Heap* heap) {
    return AnimalRoam::init_(heap);
}

void AnimalRoamCheckWater::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalRoam::enter_(params);
    _108 = false;
}

void AnimalRoamCheckWater::leave_() {
    AnimalRoam::leave_();
}

void AnimalRoamCheckWater::loadParams_() {
    AnimalRoam::loadParams_();
    getStaticParam(&mWaterLevelLimitLower_s, "WaterLevelLimitLower");
    getStaticParam(&mWaterLevelLimitUpper_s, "WaterLevelLimitUpper");
}

void AnimalRoamCheckWater::calc_() {
    auto* nav = mActor->m45();
    if (_108 && !nav->_194.isNan()) {
        const sead::Vector3f& pos = nav->_194;
        const f32 dx = pos.x - _10c.x;
        const f32 dy = pos.y - _10c.y;
        const f32 dz = pos.z - _10c.z;
        if (dx <= 0.01f && dx >= -0.01f) {
            if (dy <= 0.01f && dy >= -0.01f) {
                if (dz <= 0.01f && dz >= -0.01f) {
                    AnimalRoam::calc_();
                    return;
                }
            }
        }
        _108 = false;
        mActor->m45()->inlineReset();
        mActor->m45()->inlineClearTargets();
    }
    AnimalRoam::calc_();
}

bool AnimalRoamCheckWater::m34(const sead::Vector3f* pos) {
    _108 = false;
    mActor->m45()->inlineReset();
    mActor->m45()->inlineClearTargets();
    return AnimalRoam::m34(pos);
}

bool AnimalRoamCheckWater::m40(sead::Vector3f* pos) {
    if (!pos)
        return false;
    if (auto* nav = mActor->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state == 1) {
            pos->set(_10c);
            return true;
        }
    }
    return false;
}

bool AnimalRoamCheckWater::m38() {
    auto* nav = mActor->m45();
    if (!nav)
        return false;

    if (AnimalRoam::m38()) {
        _108 = false;
        return true;
    }

    if (!m35() || _108)
        return false;

    const f32 depth = sub_710030C688(nullptr, &nav->_194, 7.0f);
    if (*mWaterLevelLimitLower_s <= depth && *mWaterLevelLimitUpper_s >= depth) {
        _108 = true;
        _10c = nav->_194;
        return false;
    }

    _108 = false;
    return true;
}

bool AnimalRoamCheckWater::m39() {
    auto* nav = mActor->m45();
    if (!nav || !AnimalRoam::m39() || (nav->_220 & 0x41000) != 0)
        return false;
    return _108;
}

}  // namespace uking::ai
