#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Fall : public ActionEx {
    SEAD_RTTI_OVERRIDE(Fall, ActionEx)
public:
    explicit Fall(const InitArg& arg);
    ~Fall() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
    ksys::VFRValue _38;
    ksys::VFRVec3f _44;
    u8 _68[0x10];
};
KSYS_CHECK_SIZE_NX150(Fall, 0x78);

}  // namespace uking::action
