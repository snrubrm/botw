#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionSiteBossThrowParts.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordThrowElectricBall : public SiteBossThrowParts {
    SEAD_RTTI_OVERRIDE(SiteBossSwordThrowElectricBall, SiteBossThrowParts)
public:
    explicit SiteBossSwordThrowElectricBall(const InitArg& arg);
    ~SiteBossSwordThrowElectricBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m35() override;

    struct Params {
        // static_param at offset 0xc8
        const float* mMoveSpeed_s{};
        // static_param at offset 0xd0
        const sead::Vector3f* mMoveOffset_s{};
    };
    Params mParams;
    sead::Vector3f _d8;
    f32 _e4 = 0.0f;
    u8 _e8[0x28];
    sead::FixedSafeString<32> _110[3];
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordThrowElectricBall, 0x1b8);

}  // namespace uking::action
