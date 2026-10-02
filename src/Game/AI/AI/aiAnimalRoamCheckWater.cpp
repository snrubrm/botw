#include "Game/AI/AI/aiAnimalRoamCheckWater.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace uking::ai
