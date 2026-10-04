#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateAndReplaceAssassin : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateAndReplaceAssassin, ksys::act::ai::Action)
public:
    explicit CreateAndReplaceAssassin(const InitArg& arg);
    ~CreateAndReplaceAssassin() override;
    void onPreDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasPreDeleteCb() override;

protected:
    void calc_() override;
    // 0x71000e2dc0: declared only; creates the replacement actor.
    bool sub_71000E2DC0();

    // dynamic_param at offset 0x20
    sead::Vector3f* mOffset_d{};
    ksys::act::Actor* _28{};
    bool _30 = false;
};

}  // namespace uking::action
