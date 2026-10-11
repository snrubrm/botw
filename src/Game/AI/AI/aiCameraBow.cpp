#include "Game/AI/AI/aiCameraBow.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"

namespace uking::ai {

CameraBow::CameraBow(const InitArg& arg) : CameraAI(arg) {}

bool CameraBow::m34(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

// NON_MATCHING: the common name copy and string argument storage differ.
void CameraBow::m36() {
    if (!sub_7100926A14())
        return;

    auto* attention = ksys::act::Attention::instance();
    if (!attention || !getCamera())
        return;

    sead::FixedSafeString<64> name;
    ksys::act::BaseProcLink target;
    name.copy(attention->sub_7100D74148(&target) ? "弓注目魔獣ガノンカメラ" : "弓ズームカメラ");
    if (!isCurrentChild(name.cstr()))
        changeChild(name.cstr());
}

}  // namespace uking::ai
