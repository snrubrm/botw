#pragma once

#include "Game/AI/Action/actionBackWalkEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackWalkWithAS : public BackWalkEx {
    SEAD_RTTI_OVERRIDE(BackWalkWithAS, BackWalkEx)
public:
    explicit BackWalkWithAS(const InitArg& arg);
    ~BackWalkWithAS() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
    // 0x71000b6d2c: finishes once the AS is finished (when an AS name is set).
    void sub_71000B6D2C();

    // static_param at offset 0xc0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
