#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "Game/AI/Action/actionUnk_71023c8700.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Throw : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Throw, ActionWithPosAngReduce)
public:
    explicit Throw(const InitArg& arg);
    ~Throw() override = default;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    Unk_71023c8700 _30{this};
};

}  // namespace uking::action
