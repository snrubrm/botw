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

// NON_MATCHING: vector loads and scalar scheduling differ.
bool CameraLockOn::m51() {
    auto* camera = getCamera();
    if (!camera)
        return false;
    _64 = camera->_860._2d0.getTranslation();
    if (sub_7100786CF4(&_1bd, 1)) {
        _70 = camera->_860._30c;
        _7c = camera->_860._300;
    } else {
        const f32 horizontal_rate = sub_7100791E44(0.6f);
        const f32 vertical_rate = sub_7100791E44(0.2f);
        _70.x += horizontal_rate * (camera->_860._30c.x - _70.x);
        _70.y += vertical_rate * (camera->_860._30c.y - _70.y);
        _70.z += horizontal_rate * (camera->_860._30c.z - _70.z);
        _7c.x += horizontal_rate * (camera->_860._300.x - _7c.x);
        _7c.y += vertical_rate * (camera->_860._300.y - _7c.y);
        _7c.z += horizontal_rate * (camera->_860._300.z - _7c.z);
    }
    return true;
}

void CameraLockOn::m57() {
    if (!_1bf)
        return;
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const act::Unk_7100922700 source(1.0f, polar._4, polar._8);
    const act::Unk_7100922700 target(1.0f, _cc, _d0);
    const sead::Vector3f source_direction = source.sub_7100923254();
    const sead::Vector3f target_direction = target.sub_7100923254();
    sub_710074BDF8(source_direction.dot(target_direction));
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
