#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveObjectOneWay : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveObjectOneWay, ksys::act::ai::Ai)
public:
    explicit RailMoveObjectOneWay(const InitArg& arg);
    ~RailMoveObjectOneWay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mASKeyName_On_s{};
    // static_param at offset 0x48
    sead::SafeString mASKeyName_Off_s{};
    void* _58 = nullptr;
    f32 _60 = 0;
    f32 _64 = 0;
    f32 _68 = 0;
    bool _6c = false;
    bool _6d = false;
    bool _6e = false;
};
KSYS_CHECK_SIZE_NX150(RailMoveObjectOneWay, 0x70);

}  // namespace uking::ai
