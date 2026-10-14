#pragma once

#include "Game/Actor/Action/actionFireWood.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DynamicFireWood : public FireWood {
    SEAD_RTTI_OVERRIDE(DynamicFireWood, FireWood)
public:
    explicit DynamicFireWood(const InitArg& arg);
    ~DynamicFireWood() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    bool _41 = false;
    void calc_() override;
    bool m33() override;
};

}  // namespace uking::action
