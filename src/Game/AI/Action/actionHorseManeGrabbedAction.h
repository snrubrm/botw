#pragma once

#include "Game/Actor/actHorseBindSets.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseManeGrabbedAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseManeGrabbedAction, ksys::act::ai::Action)
public:
    explicit HorseManeGrabbedAction(const InitArg& arg);
    ~HorseManeGrabbedAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    /* 0x20 */ act::Unk_71024e8e18 _20;
    /* 0x8f8 */ u8 _8f8 = 0;  // bit 0: bound, bit 1: second bind, bit 2: animation synced
};

}  // namespace uking::action
