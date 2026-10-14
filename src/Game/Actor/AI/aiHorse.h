#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Horse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Horse, ksys::act::ai::Ai)
public:
    explicit Horse(const InitArg& arg);
    ~Horse() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100435420();
    // 0x7100435180 (placeholder name)
    void sub_7100435180(u64 value);
    // 0x7100435260 (placeholder name): sets _48 bits 0x20 / 0x80 (clears 0x10), resets the chemicals and calls
    // m13(0..11) on the horse's _1028, then HorseBase::sub_7100E67230.
    void sub_7100435260();

protected:
    // static_param at offset 0x38
    const float* mDistanceFall_s{};
    // static_param at offset 0x40
    const float* mDistanceFallDie_s{};
    sead::BitFlag8 _48;
    u32 _4c{};
    u64 _50{};
    u32 _58{};
};

}  // namespace uking::ai
