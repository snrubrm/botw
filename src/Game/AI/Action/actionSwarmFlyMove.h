#pragma once

#include "Game/AI/Action/actionFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmFlyMove : public FlyMoveBase {
    SEAD_RTTI_OVERRIDE(SwarmFlyMove, FlyMoveBase)
public:
    explicit SwarmFlyMove(const InitArg& arg);
    ~SwarmFlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100285ad8 (declared only): out of line in the original.
    bool sub_7100285AD8();
    void calc_() override;
    void m32(sead::Vector3f* target) override {
        if (target)
            target->set(_f0);
    }

    // static_param at offset 0xc0
    const int* mIgnoreSensorTime_s{};
    // static_param at offset 0xc8
    const float* mSubAccRateMin_s{};
    // static_param at offset 0xd0
    const float* mSubAccRateMax_s{};
    // static_param at offset 0xd8
    const float* mMaterialAnimFrame_s{};
    // static_param at offset 0xe0
    sead::SafeString mMaterialAnimName_s{};
    sead::Vector3f _f0;
    sead::Vector3f _fc;
    sead::Vector3f _108{0, 0, 0};
    f32 _114 = 0.0f;
    bool _118 = true;
    sead::Vector3f _11c{0, 0, 0};
    sead::Vector3f _128{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(SwarmFlyMove, 0x138);

}  // namespace uking::action
