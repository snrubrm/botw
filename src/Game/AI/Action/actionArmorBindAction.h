#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class ModelBindInfo;
}

namespace uking::action {

class ArmorBindAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ArmorBindAction, ksys::act::ai::Action)
public:
    explicit ArmorBindAction(const InitArg& arg);
    ~ArmorBindAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    ksys::act::ModelBindInfo* _20 = nullptr;
    ksys::act::BoneHandle* _28 = nullptr;
};

}  // namespace uking::action
