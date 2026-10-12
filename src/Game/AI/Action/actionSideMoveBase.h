#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SideMoveBase : public MoveBase {
    SEAD_RTTI_OVERRIDE(SideMoveBase, MoveBase)
public:
    explicit SideMoveBase(const InitArg& arg);
    ~SideMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(sead::Vector3f* dir) override;

    // static_param at offset 0xe0
    const bool* mLeftMove_s{};
};

}  // namespace uking::action
