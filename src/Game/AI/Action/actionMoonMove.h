#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoonMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoonMove, ksys::act::ai::Action)
public:
    explicit MoonMove(const InitArg& arg);
    ~MoonMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _1c = false;
    void* _20{};
    int _28 = 0;
    int _2c = 0;
    void* _30{};
    int _38 = 0;
    int _3c = 0;
};

}  // namespace uking::action
