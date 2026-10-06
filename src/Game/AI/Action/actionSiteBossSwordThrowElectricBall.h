#pragma once

#include <math/seadMatrix.h>
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
    const sead::SafeString& m34() override;
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
    sead::Matrix33f _e8;
    u8 _10c[0x4];
    sead::FixedSafeString<32> _110[3];
};
KSYS_CHECK_SIZE_NX150(SiteBossSwordThrowElectricBall, 0x1b8);

}  // namespace uking::action
