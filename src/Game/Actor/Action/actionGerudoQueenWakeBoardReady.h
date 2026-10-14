#pragma once

#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GerudoQueenWakeBoardReady : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GerudoQueenWakeBoardReady, ksys::act::ai::Action)
public:
    explicit GerudoQueenWakeBoardReady(const InitArg& arg);
    ~GerudoQueenWakeBoardReady() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    xlink2::HandleELink _20;
};

}  // namespace uking::action
