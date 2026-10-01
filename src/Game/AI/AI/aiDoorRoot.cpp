#include "Game/AI/AI/aiDoorRoot.h"

namespace uking::ai {

DoorRoot::DoorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoorRoot::~DoorRoot() = default;

bool DoorRoot::init_(sead::Heap* heap) {
    *mIsOpenDoor_a = false;
    *mIsOpenToInside_a = false;
    return true;
}

void DoorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DoorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoorRoot::loadParams_() {
    getStaticParam(&mCloseWaitFrame_s, "CloseWaitFrame");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mOpen_L_AS_s, "Open_L_AS");
    getStaticParam(&mOpen_R_AS_s, "Open_R_AS");
    getStaticParam(&mClose_L_AS_s, "Close_L_AS");
    getStaticParam(&mClose_R_AS_s, "Close_R_AS");
    getMapUnitParam(&mNpcCanOpenFlag_m, "NpcCanOpenFlag");
    getAITreeVariable(&mIsOpenDoor_a, "IsOpenDoor");
    getAITreeVariable(&mIsOpenToInside_a, "IsOpenToInside");
}

bool DoorRoot::handleMessage_(const ksys::Message& message) {
    if (_a8._30)
        return false;
    if (isCurrentChild("Wait") && !*mIsOpenDoor_a)
        return _a8.m2(message);
    return false;
}

}  // namespace uking::ai
