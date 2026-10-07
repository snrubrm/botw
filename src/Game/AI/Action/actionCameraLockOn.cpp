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

void CameraLockOn::m56(bool x) {
    _1bf = 0;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    if (stick.x == 0.0f && stick.y == 0.0f) {
        auto* attention = ksys::act::Attention::instance();
        if (attention != nullptr && attention->sub_7100D75490()) {
            _1be = 0;
        } else if (!x) {
            return;
        }
        _1bf = 1;
    } else {
        _1be = true;
        CameraAction::sub_710074BCB4();
    }
}

}  // namespace uking::action
