#include "Game/AI/Action/actionGolemRepairParts.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::action {

GolemRepairParts::GolemRepairParts(const InitArg& arg) : ActionWithAS(arg) {
    _e8._18.y(mActor);
}

GolemRepairParts::~GolemRepairParts() = default;

bool GolemRepairParts::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemRepairParts::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void GolemRepairParts::leave_() {
    sub_71005DA114(mActor, &_118);
    ActionWithAS::leave_();
}

void GolemRepairParts::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    _60.sub_71005E1BE8(this, 0);
    _a0.sub_71005E1BE8(this, 1);
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemRepairParts::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
