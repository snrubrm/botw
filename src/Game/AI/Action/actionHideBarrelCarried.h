#pragma once

#include "Game/AI/Action/actionCarried.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HideBarrelCarried : public Carried {
    SEAD_RTTI_OVERRIDE(HideBarrelCarried, Carried)
public:
    explicit HideBarrelCarried(const InitArg& arg);
    ~HideBarrelCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x168
    const float* mCutLength_s{};
    sead::Vector3f _170{0, 0, 0};
    sead::Vector3f _17c{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(HideBarrelCarried, 0x188);

}  // namespace uking::action
