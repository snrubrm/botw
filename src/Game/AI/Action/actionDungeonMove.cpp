#include "Game/AI/Action/actionDungeonMove.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2HandleSLink.h>
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DungeonMove::DungeonMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DungeonMove::~DungeonMove() {
    if (_90) {
        delete _90;
        _90 = nullptr;
    }
}

bool DungeonMove::init_(sead::Heap* heap) {
    _80 = mActor->getFieldBodyGroup();
    if (!mActor->getMapObjIter().tryGetParamIntByKey(&_88, "FieldBodyGroup"))
        _88 = -1;
    _78 = *mInitDgnPriority_m;
    _90 = new (heap) xlink2::HandleSLink;
    return true;
}

void DungeonMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DungeonMove::leave_() {
    if (_90->getEvent() && _90->getEvent()->getCreateId() == u32(_90->getCreateId()))
        xlink::fade(*_90, -1);
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
