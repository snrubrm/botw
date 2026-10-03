#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class StalPartNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalPartNormal, ksys::act::ai::Ai)
public:
    explicit StalPartNormal(const InitArg& arg);
    ~StalPartNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    struct Params {
        // static_param at offset 0x38
        const float* mTerritoryArea_s{};
        // static_param at offset 0x40
        const float* mCatchArea_s{};
        // static_param at offset 0x48
        const float* mWaitTimer_s{};
        // static_param at offset 0x50
        const sead::Vector3f* mTgtOffset_s{};
    };
    Params mParams;
    ksys::act::BaseProcLink _58;
    Unk_7102450558 _68;
    Unk_7102396ae0 _b8{mActor, 0x800001f};
    f32 _e8 = 0;
    f32 _ec = 0;
    u32 _f0 = 0;
    bool _f4 = true;
    bool _f5 = false;
};
KSYS_CHECK_SIZE_NX150(StalPartNormal, 0xf8);

}  // namespace uking::ai
