#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionAnmBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmBlownOffBackward : public AnmBlownOff {
    SEAD_RTTI_OVERRIDE(AnmBlownOffBackward, AnmBlownOff)
public:
    explicit AnmBlownOffBackward(const InitArg& arg);
    ~AnmBlownOffBackward() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    sead::Matrix33f _a4;
};

KSYS_CHECK_SIZE_NX150(AnmBlownOffBackward, 0xc8);

}  // namespace uking::action
