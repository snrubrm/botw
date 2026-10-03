#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseManeCollarSyncAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseManeCollarSyncAction, ksys::act::ai::Action)
public:
    explicit HorseManeCollarSyncAction(const InitArg& arg);
    ~HorseManeCollarSyncAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    s32 _1c = -1;

};
KSYS_CHECK_SIZE_NX150(HorseManeCollarSyncAction, 0x20);

}  // namespace uking::action
