#include "Game/AI/AI/aiAnimalRoamCheckWater.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

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

bool AnimalRoamCheckWater::m39() {
    auto* nav = mActor->m45();
    if (!nav || !AnimalRoam::m39() || (nav->_220 & 0x41000) != 0)
        return false;
    return _108;
}

}  // namespace uking::ai
