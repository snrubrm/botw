#include "Game/AI/Action/actionForkEmitExpandChemicalField.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkEmitExpandChemicalField::ForkEmitExpandChemicalField(const InitArg& arg)
    : ForkEmitExpandField(arg) {}

ForkEmitExpandChemicalField::~ForkEmitExpandChemicalField() = default;

bool ForkEmitExpandChemicalField::init_(sead::Heap* heap) {
    return ForkEmitExpandField::init_(heap);
}

void ForkEmitExpandChemicalField::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitExpandField::enter_(params);
    sub_710014E780(&mActor->getMtx());
}

void ForkEmitExpandChemicalField::leave_() {
    ForkEmitExpandField::leave_();
}

void ForkEmitExpandChemicalField::loadParams_() {
    ForkEmitExpandField::loadParams_();
}

void ForkEmitExpandChemicalField::calc_() {
    ForkEmitExpandField::calc_();
}

}  // namespace uking::action
