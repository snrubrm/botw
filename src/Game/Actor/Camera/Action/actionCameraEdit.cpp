#include "Game/Actor/Camera/Action/actionCameraEdit.h"
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
    if (!getStaticParam(&mNormal_s, "Normal"))
        mNormal_s = "DefaultNormal";
    if (!getStaticParam(&mLockOn_s, "LockOn"))
        mLockOn_s = "DefaultLockOn";
    if (!getStaticParam(&mWall_s, "Wall"))
        mWall_s = "DefaultWall";
    if (!getStaticParam(&mNormalSubject_s, "NormalSubject"))
        mNormalSubject_s = "DefaultNormalSubject";
    if (!getStaticParam(&mBow_s, "Bow"))
        mBow_s = "デフォルト弓カメラ";
    if (!getStaticParam(&mBowSquat_s, "BowSquat"))
        mBowSquat_s = "デフォルト弓屈みカメラ";
    if (!getStaticParam(&mBowLockOn_s, "BowLockOn"))
        mBowLockOn_s = "デフォルト弓注目カメラ";

    if (sead::SafeString(getName()) == act::sUnk_71024741A8) {
        if (mActor) {
            if (auto* camera = sead::DynamicCast<act::EditCamera>(mActor))
                std::memcpy(camera->sub_71007917B4(), &mNormal_s,
                            sizeof(act::EditCamera::CameraNames));
        }
    }
}

}  // namespace uking::action
