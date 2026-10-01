#include "Game/AI/Action/actionDungeonMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DungeonMove::DungeonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonMove::~DungeonMove() = default;

bool DungeonMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DungeonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void DungeonMove::loadParams_() {
    getStaticParam(&mAccel_s, "Accel");
    getDynamicParam(&mDynMoveDis_d, "DynMoveDis");
    getMapUnitParam(&mInitDgnPriority_m, "InitDgnPriority");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mMoveSpeed_m, "MoveSpeed");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

void DungeonMove::calc_() {
    ksys::act::ai::Action::calc_();
}

void DungeonMove::m9() {
    _80 = mActor->getFieldBodyGroup();
    _74 = *mMoveSpeed_m;
    _78 = *mInitDgnPriority_m;
}

}  // namespace uking::action
