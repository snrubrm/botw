#pragma once

#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaWait, ksys::act::ai::Ai)
public:
    explicit AirOctaWait(const InitArg& arg);
    ~AirOctaWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x71002ffedc (placeholder name): sets `_48` from the AS event 0x39 ("待機可" / "待機不可").
    void sub_71002FFEDC();
    // 0x71002ffbbc (placeholder name; declared only): moves the actor along `move` (uses its main rigid body).
    void sub_71002FFBBC(const sead::Vector3f& move);

protected:
    // dynamic_param at offset 0x38
    bool* mIsSameChange_d{};
    // aitree_variable at offset 0x40
    Unk_71025afb58** mAirOctaDataMgr_a{};
    bool _48 = true;
};

}  // namespace uking::ai
