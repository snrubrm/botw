#pragma once

#include "Game/AI/Action/actionNPCAnchorWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCArtistAnchorWait : public NPCAnchorWait {
    SEAD_RTTI_OVERRIDE(NPCArtistAnchorWait, NPCAnchorWait)
public:
    explicit NPCArtistAnchorWait(const InitArg& arg);
    ~NPCArtistAnchorWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    const char* m32() override;
};

}  // namespace uking::action
