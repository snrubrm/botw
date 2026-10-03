#include "Game/AI/Action/actionLandTeleportConsiderCameraDir.h"
#include "KingSystem/System/CameraMgr.h"

namespace uking::action {

LandTeleportConsiderCameraDir::LandTeleportConsiderCameraDir(const InitArg& arg)
    : LandTeleport(arg) {}

LandTeleportConsiderCameraDir::~LandTeleportConsiderCameraDir() = default;

bool LandTeleportConsiderCameraDir::init_(sead::Heap* heap) {
    return LandTeleport::init_(heap);
}

void LandTeleportConsiderCameraDir::enter_(ksys::act::ai::InlineParamPack* params) {
    LandTeleport::enter_(params);
}

void LandTeleportConsiderCameraDir::leave_() {
    LandTeleport::leave_();
}

void LandTeleportConsiderCameraDir::loadParams_() {
    LandTeleport::loadParams_();
    getStaticParam(&mCameraDirCoeff_s, "CameraDirCoeff");
}

void LandTeleportConsiderCameraDir::calc_() {
    LandTeleport::calc_();
}

void LandTeleportConsiderCameraDir::m36() {
    LandTeleport::m36();
    const sead::Vector3f base = LandTeleport::m33();
    sead::Vector3f dir;
    ksys::sub_7100D8C7FC(&dir);
    dir.y = 0;
    dir.normalize();
    _c8 = base + dir * *mCameraDirCoeff_s;
}

}  // namespace uking::action
