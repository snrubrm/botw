#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SwimEnemyRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwimEnemyRoam, ksys::act::ai::Ai)
public:
    explicit SwimEnemyRoam(const InitArg& arg);
    ~SwimEnemyRoam() override;

    bool isChangeable() const override { return getCurrentChild()->isChangeable(); }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71005B51E8();
    void sub_71005B52EC();

protected:
    // static_param at offset 0x38
    const float* mRoamRadius_s{};
    // static_param at offset 0x40
    const float* mRoamRatio_s{};
    // static_param at offset 0x48
    const float* mRoamXRadius_s{};
    // static_param at offset 0x50
    const float* mRoamZRadius_s{};
    u32 _58 = 0;
    u32 _5c = 0;
    void* _60 = nullptr;
    void* _68 = nullptr;
    u32 _70 = 0;
    u8 _74[0xa4 - 0x74];  // not initialised by the ctor
    ksys::Timer _a4{0, 0};
};
KSYS_CHECK_SIZE_NX150(SwimEnemyRoam, 0xb0);

}  // namespace uking::ai
