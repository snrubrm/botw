#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class EscapeBackTurn : public ActionEx {
    SEAD_RTTI_OVERRIDE(EscapeBackTurn, ActionEx)
public:
    explicit EscapeBackTurn(const InitArg& arg);
    ~EscapeBackTurn() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    // 0x7100113950 (declared only): out of line in the original.
    void sub_7100113950();
    void calc_() override;

    ksys::VFRValue _1c;
    u8 _28[0x24];
    ksys::Timer _4c{0.0f, 0.0f};
    f32 _58 = 0.0f;
    f32 _5c = 0.0f;
    f32 _60 = 0.0f;
    u32 _64;
    u64 _68 = 0;
    u64 _70 = 0;
    u64 _78 = 0;
    s32 _80 = -1;
    u32 _84;
};
KSYS_CHECK_SIZE_NX150(EscapeBackTurn, 0x88);

}  // namespace uking::action
