#include "Game/AI/AI/aiCreateCarryActor.h"

namespace uking::ai {

CreateCarryActor::CreateCarryActor(const InitArg& arg) : CreateActor(arg) {}

CreateCarryActor::~CreateCarryActor() = default;

bool CreateCarryActor::init_(sead::Heap* heap) {
    return CreateActor::init_(heap);
}

void CreateCarryActor::enter_(ksys::act::ai::InlineParamPack* params) {
    CreateActor::enter_(params);
}

void CreateCarryActor::calc_() {
    CreateActor::calc_();
}

void CreateCarryActor::leave_() {
    CreateActor::leave_();
}

void CreateCarryActor::loadParams_() {
    CreateActor::loadParams_();
    getMapUnitParam(&mCarryActorName_m, "CarryActorName");
}

const sead::SafeString& CreateCarryActor::m34() {
    return mCarryActorName_m.isEmpty() ? mActorName_s : mCarryActorName_m;
}

}  // namespace uking::ai
