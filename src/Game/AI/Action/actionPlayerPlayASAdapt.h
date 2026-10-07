#pragma once

#include "Game/AI/Action/actionPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerPlayASAdapt : public PlayASForDemo {
    SEAD_RTTI_OVERRIDE(PlayerPlayASAdapt, PlayASForDemo)
public:
    explicit PlayerPlayASAdapt(const InitArg& arg);
    ~PlayerPlayASAdapt() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    const sead::SafeString& m34() override;
    const sead::SafeString& m35() override;

    // dynamic_param at offset 0xb0
    bool* mIsOneTimeEndKeep_d{};
    // dynamic_param at offset 0xb8
    bool* mNoErrorCheck_d{};

    sead::FixedSafeString<64> _c0{""};
    sead::SafeString _118{"HorseWait"};
};

}  // namespace uking::action
