#pragma once

#include "Game/AI/Action/actionLandTeleport.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LandTeleportConsiderCameraDir : public LandTeleport {
    SEAD_RTTI_OVERRIDE(LandTeleportConsiderCameraDir, LandTeleport)
public:
    explicit LandTeleportConsiderCameraDir(const InitArg& arg);
    ~LandTeleportConsiderCameraDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f& m33() override { return _c8; }
    void m36() override;

    // static_param at offset 0xc0
    const float* mCameraDirCoeff_s{};
    sead::Vector3f _c8 = sead::Vector3f::zero;
};

KSYS_CHECK_SIZE_NX150(LandTeleportConsiderCameraDir, 0xd8);

}  // namespace uking::action
