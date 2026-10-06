#pragma once

#include "Game/AI/aiUnk_7102431fa8.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class WizzrobeWeatherMagic : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeWeatherMagic, ksys::act::ai::Ai)
public:
    explicit WizzrobeWeatherMagic(const InitArg& arg);
    ~WizzrobeWeatherMagic() override;

    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71005FF9BC();
    void sub_71005FFF84(sead::Vector3f* out);

protected:
    // 0x71005ffe8c: changes to the "詠唱" child
    void sub_71005FFE8C();
    // aitree_variable at offset 0x38
    void* mWizzrobeMagicWeatherUnit_a{};
    // static_param at offset 0x40
    const float* mRiseLength_s{};
    // static_param at offset 0x48
    const float* mTimer_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    ksys::act::Unk_7100d3bce4 _58{mActor};
    f32 _70 = 0;
    f32 _74 = -1.0f;
    Unk_7102431fa8* _78 = nullptr;
};
KSYS_CHECK_SIZE_NX150(WizzrobeWeatherMagic, 0x80);

}  // namespace uking::ai
