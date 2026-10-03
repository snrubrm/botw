#include "Game/AI/Action/actionLandOnCeil.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::action {

LandOnCeil::LandOnCeil(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LandOnCeil::~LandOnCeil() = default;

bool LandOnCeil::init_(sead::Heap* heap) {
    _80 = ksys::phys::System::instance()->getField48();
    return true;
}

void LandOnCeil::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LandOnCeil::leave_() {
    ksys::act::ai::Action::leave_();
}

void LandOnCeil::loadParams_() {
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

void LandOnCeil::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
