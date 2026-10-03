#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionForkASPlayBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonBeastASPlayFromActiveWp : public ForkASPlayBase {
    SEAD_RTTI_OVERRIDE(GanonBeastASPlayFromActiveWp, ForkASPlayBase)
public:
    explicit GanonBeastASPlayFromActiveWp(const InitArg& arg);
    ~GanonBeastASPlayFromActiveWp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    // aitree_variable at offset 0x60
    void* mWeakPointActiveFlag_a{};
    sead::FixedSafeString<32> _68;
};
KSYS_CHECK_SIZE_NX150(GanonBeastASPlayFromActiveWp, 0xa0);

}  // namespace uking::action
