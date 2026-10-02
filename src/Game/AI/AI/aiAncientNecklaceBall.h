#pragma once

#include "Game/AI/AI/aiAncientNecklaceBallBase.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AncientNecklaceBall : public AncientNecklaceBallBase {
    SEAD_RTTI_OVERRIDE(AncientNecklaceBall, AncientNecklaceBallBase)
public:
    explicit AncientNecklaceBall(const InitArg& arg);
    ~AncientNecklaceBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;
    void calc_() override;

    void m35() override;
    bool m36() override;
    void m37() override;

protected:
    // static_param at offset 0x100
    const float* mLandNoiseLevel_s{};
    // map_unit_param at offset 0x108
    const int* mGrabNodeIndex_m{};
    // map_unit_param at offset 0x110
    sead::SafeString mGiantNecklaceActiveSaveFlag_m{};
    ksys::Timer _120{};
    f32 _12c{};
    ksys::act::BaseProcLink _130;
    Unk_71023d4bb0 _140{mActor};
    Unk_71023d4c08 _170;
};
KSYS_CHECK_SIZE_NX150(AncientNecklaceBall, 0x1c0);

}  // namespace uking::ai
