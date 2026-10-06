#include "Game/AI/Action/actionForkAlwayForceGetUpVelocityDir.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAlwayForceGetUpVelocityDir::ForkAlwayForceGetUpVelocityDir(const InitArg& arg)
    : ForkAlwaysForceGetUp(arg) {}

ForkAlwayForceGetUpVelocityDir::~ForkAlwayForceGetUpVelocityDir() = default;

bool ForkAlwayForceGetUpVelocityDir::init_(sead::Heap* heap) {
    return ForkAlwaysForceGetUp::init_(heap);
}

void ForkAlwayForceGetUpVelocityDir::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysForceGetUp::enter_(params);
}

void ForkAlwayForceGetUpVelocityDir::leave_() {
    ForkAlwaysForceGetUp::leave_();
}

void ForkAlwayForceGetUpVelocityDir::loadParams_() {
    ForkAlwaysForceGetUp::loadParams_();
}

void ForkAlwayForceGetUpVelocityDir::calc_() {
    ForkAlwaysForceGetUp::calc_();
}

void ForkAlwayForceGetUpVelocityDir::m32(sead::Vector3f* dir) {
    sead::Vector3f velocity_dir = mActor->getVelocity();
    velocity_dir.y = 0;
    velocity_dir.normalize();
    if ((velocity_dir.z == 0 && velocity_dir.y == 0 && velocity_dir.x == 0) ||
        velocity_dir.dot(sead::Vector3f::ey) > 0.9998477f) {
        ForkAlwaysForceGetUp::m32(dir);
    } else {
        *dir = velocity_dir;
    }
}

}  // namespace uking::action
