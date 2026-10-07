#include "Game/AI/Action/actionCameraLockOn.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"

namespace uking::action {

CameraLockOn::CameraLockOn(const InitArg& arg) : CameraLockOnBase(arg) {}

float CameraLockOn::m44() {
    return sub_71009222F4();
}

float CameraLockOn::m45() {
    return sub_7100922300();
}

bool CameraLockOn::m58() {
    auto* attention = ksys::act::Attention::instance();
    return attention && attention->sub_7100D75490();
}

}  // namespace uking::action
