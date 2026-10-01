#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/AI/aiHorseFollow.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class WolfLinkFollowPlayerRoot : public HorseFollow {
    SEAD_RTTI_OVERRIDE(WolfLinkFollowPlayerRoot, HorseFollow)
public:
    explicit WolfLinkFollowPlayerRoot(const InitArg& arg);
    ~WolfLinkFollowPlayerRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mLateralDistance_s{};
    // static_param at offset 0xe8
    const float* mAnteriorDistanceStop_s{};
    // static_param at offset 0xf0
    const float* mAnteriorDistanceRun_s{};
    // static_param at offset 0xf8
    const float* mAnteriorDistanceSprint_s{};
    void* _100{};
    void* _108{};
    void* _110{};
    u32 _118 = 0;
    f32 _11c = 1.0f;
    ksys::Timer _120{0.0f, 0.0f};
    sead::Vector3f _12c{0, 0, 0};
    sead::Vector3f _138{0, 0, 0};
    sead::Matrix34f _144;
    u32 _174 = 0;
    f32 _178 = 0;
    bool _17c = false;
};
KSYS_CHECK_SIZE_NX150(WolfLinkFollowPlayerRoot, 0x180);

}  // namespace uking::ai
