#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

#include "Game/AI/AI/aiRailMoveRemainsBGCamera.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsElectricBGCamera : public RailMoveRemainsBGCamera {
    SEAD_RTTI_OVERRIDE(RemainsElectricBGCamera, RailMoveRemainsBGCamera)
public:
    explicit RemainsElectricBGCamera(const InitArg& arg);
    ~RemainsElectricBGCamera() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    f32 m43() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x108
    sead::SafeString mParentActorName_s{};
    ksys::act::BaseProcLink _118;
    gsys::BoneAccessKeyEx _128[4];
    u32 _208 = 0;
};
KSYS_CHECK_SIZE_NX150(RemainsElectricBGCamera, 0x210);

}  // namespace uking::ai
