#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAbyss : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraAbyss, CameraAction)
public:
    explicit CameraAbyss(const InitArg& arg);

protected:
    void m33() override;
    void m34() override;
    void m36() override;

    sead::Vector3f _4c = sead::Vector3f::zero;
    f32 _58 = 0;
    // static_param at offset 0x60
    const f32* mRadiusMin_s{};
    // static_param at offset 0x68
    const f32* mFovy_s{};
    f32 _70 = 0;
    f32 _74 = 0;
};

}  // namespace uking::action
