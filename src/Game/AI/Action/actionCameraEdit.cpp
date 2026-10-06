#include "Game/AI/Action/actionCameraEdit.h"
#include <cstring>
#include "Game/Actor/actEditCamera.h"

namespace uking::action {

CameraEdit::CameraEdit(const InitArg& arg) : ActionEx(arg) {}

CameraEdit::~CameraEdit() = default;

// NON_MATCHING: register allocation only (the original keeps `this` in x20 and the actor in x19)
void CameraEdit::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor) {
        if (auto* camera = sead::DynamicCast<act::EditCamera>(mActor))
            std::memcpy(camera->sub_71007917BC(), &mNormal_s, sizeof(act::EditCamera::CameraNames));
    }
}

void CameraEdit::loadParams_() {
    getStaticParam(&mNormal_s, "Normal");
    getStaticParam(&mLockOn_s, "LockOn");
    getStaticParam(&mWall_s, "Wall");
    getStaticParam(&mNormalSubject_s, "NormalSubject");
    getStaticParam(&mBow_s, "Bow");
    getStaticParam(&mBowSquat_s, "BowSquat");
    getStaticParam(&mBowLockOn_s, "BowLockOn");
    // FIXME: CALL _ZNK4ksys3act2ai10ActionBase7getNameEv @ 0x7100d165fc
}

}  // namespace uking::action
