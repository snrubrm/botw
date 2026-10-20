#include "Game/Actor/Camera/AI/aiCameraEditRoot.h"
#include <prim/seadSafeString.h>
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actEditCamera.h"

namespace uking::ai {

CameraEditRoot::CameraEditRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool CameraEditRoot::init_(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

void CameraEditRoot::calc_() {
    void* camera = nullptr;
    if (mActor) {
        if (auto* edit_camera = sead::DynamicCast<act::EditCamera>(mActor))
            edit_camera->sub_71007917E0(&camera);
    }

    sead::FixedSafeString<128> name{act::sUnk_71024741A8};
    if (camera) {
        static_cast<act::Camera*>(camera)->sub_7100795518();
        name.format("%s", static_cast<act::Camera*>(camera)->sub_710079558C());
    }

    if (!isCurrentChild(name.cstr()))
        changeChild(name.cstr());
}

}  // namespace uking::ai
