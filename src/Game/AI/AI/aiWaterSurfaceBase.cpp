#include "Game/AI/AI/aiWaterSurfaceBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WaterSurfaceBase::WaterSurfaceBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaterSurfaceBase::~WaterSurfaceBase() {
    if (_40) {
        _40->destroy();
        _40 = nullptr;
    }
}

bool WaterSurfaceBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaterSurfaceBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaterSurfaceBase::calc_() {
    auto* actor = mActor;
    if (!_48.isActive())
        sub_71005ED41C();
    if (_40) {
        const sead::Vector3f pos = actor->getMtx().getTranslation();
        _40->setPosition(pos);
    }
}

void WaterSurfaceBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaterSurfaceBase::loadParams_() {
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
}

}  // namespace uking::ai
