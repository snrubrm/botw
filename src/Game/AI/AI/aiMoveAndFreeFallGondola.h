#pragma once

#include "Game/AI/AI/aiRailMove.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoveAndFreeFallGondola : public RailMove {
    SEAD_RTTI_OVERRIDE(MoveAndFreeFallGondola, RailMove)
public:
    explicit MoveAndFreeFallGondola(const InitArg& arg);
    ~MoveAndFreeFallGondola() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    void m34() override;
    f32 m35() override;
    ksys::map::Rail* m36() override;
    bool m40() override;
    bool handleMessage_(const ksys::Message* message) override;

    // 0x71004af894 (424 bytes; placeholder name): for the messages 0x3000003 / 0x3000004: if
    // the message's sender is the linked actor `_b0` (and not this actor), forwards the message.
    void sub_71004AF894(const ksys::Message* message);

protected:
    // map_unit_param at offset 0xa0
    const float* mRailMoveSpeed_m{};
    // map_unit_param at offset 0xa8
    const float* mGondolaRailOffsetTime_m{};
    ksys::act::BaseProcLink _b0;
    Unk_71023e7bc0 _c0{mActor, 0x8000041};
    ksys::map::Rail* _f0 = nullptr;
    u32 _f8 = 0;
};
KSYS_CHECK_SIZE_NX150(MoveAndFreeFallGondola, 0x100);

}  // namespace uking::ai
