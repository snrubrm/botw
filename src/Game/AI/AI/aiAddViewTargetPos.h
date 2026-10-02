#pragma once

#include "Game/AI/AI/aiAddViewTargetPosBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddViewTargetPos : public AddViewTargetPosBase {
    SEAD_RTTI_OVERRIDE(AddViewTargetPos, AddViewTargetPosBase)
public:
    explicit AddViewTargetPos(const InitArg& arg);
    ~AddViewTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m34(sead::Vector3f* out) override;

protected:
};

}  // namespace uking::ai
