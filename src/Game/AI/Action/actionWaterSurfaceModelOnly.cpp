#include "Game/AI/Action/actionWaterSurfaceModelOnly.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

WaterSurfaceModelOnly::WaterSurfaceModelOnly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterSurfaceModelOnly::~WaterSurfaceModelOnly() = default;

bool WaterSurfaceModelOnly::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterSurfaceModelOnly::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* as_list = mActor->getASList()) {
        as_list->startAnimationMaybe(-1.0f, -1.0f, "Flow", 0, 0, true);
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, *mFlowSpeedFactor_m);
    }
}

void WaterSurfaceModelOnly::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterSurfaceModelOnly::loadParams_() {
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
}

void WaterSurfaceModelOnly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
