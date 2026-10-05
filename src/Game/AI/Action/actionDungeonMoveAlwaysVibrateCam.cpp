#include "Game/AI/Action/actionDungeonMoveAlwaysVibrateCam.h"
#include "KingSystem/ActorSystem/actActor.h"

void sub_71005DDC98(ksys::act::Actor* actor, s32 pattern, f32 power, f32 range, bool start,
                    ksys::map::Object* object);

namespace uking::action {

DungeonMoveAlwaysVibrateCam::DungeonMoveAlwaysVibrateCam(const InitArg& arg) : DungeonMove(arg) {}

DungeonMoveAlwaysVibrateCam::~DungeonMoveAlwaysVibrateCam() = default;

bool DungeonMoveAlwaysVibrateCam::init_(sead::Heap* heap) {
    return DungeonMove::init_(heap);
}

void DungeonMoveAlwaysVibrateCam::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonMove::enter_(params);
}

void DungeonMoveAlwaysVibrateCam::leave_() {
    if (!isFinished()) {
        auto* actor = mActor;
        auto* object = sub_71000F9C9C();
        if (!*mIsSilentOnSuccess_s || !actor->checkGimmickSuccessSignal())
            sub_71005DDC98(actor, *mCameraPattern_m, *mCameraPower_m, *mCameraRange_m, false,
                          object);
    }
    DungeonMove::leave_();
}

void DungeonMoveAlwaysVibrateCam::loadParams_() {
    DungeonMove::loadParams_();
    getStaticParam(&mIsSilentOnSuccess_s, "IsSilentOnSuccess");
    getMapUnitParam(&mCameraPattern_m, "CameraPattern");
    getMapUnitParam(&mCameraPower_m, "CameraPower");
    getMapUnitParam(&mCameraRange_m, "CameraRange");
}

void DungeonMoveAlwaysVibrateCam::calc_() {
    DungeonMove::calc_();
}

}  // namespace uking::action
