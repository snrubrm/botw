#include "Game/AI/Action/actionDemoMotorcyclePutMaterials.h"
#include "Game/Actor/actMotorcycle.h"

namespace uking::action {

DemoMotorcyclePutMaterials::DemoMotorcyclePutMaterials(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoMotorcyclePutMaterials::~DemoMotorcyclePutMaterials() = default;

bool DemoMotorcyclePutMaterials::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoMotorcyclePutMaterials::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoMotorcyclePutMaterials::leave_() {
    if (auto* motorcycle = sead::DynamicCast<act::Motorcycle>(mActor)) {
        if (motorcycle->_bc8.getMotorcycleEnergy() > 0.0f)
            motorcycle->_bc8._19e = false;
    }
}

void DemoMotorcyclePutMaterials::loadParams_() {
    getStaticParam(&mCloseSaddleFramesSincePut_s, "CloseSaddleFramesSincePut");
    getStaticParam(&mFinishCookFramesSincePut_s, "FinishCookFramesSincePut");
    getStaticParam(&mCloseSaddleFramesSincePutFairy_s, "CloseSaddleFramesSincePutFairy");
    getStaticParam(&mFinishCookFramesSincePutFairy_s, "FinishCookFramesSincePutFairy");
}

void DemoMotorcyclePutMaterials::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
