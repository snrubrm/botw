#pragma once

#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Freeze : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Freeze, ActionWithPosAngReduce)
public:
    explicit Freeze(const InitArg& arg);
    ~Freeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    bool _30 = false;
    ksys::act::CCAccessor _34;
    // static_param at offset 0x40
    sead::SafeString mTransBoneKey_s{};
    // static_param at offset 0x50
    const bool* mIsChangeInAir_s{};
    // aitree_variable at offset 0x58
    bool* mIsKeepFreeze_a{};
    // aitree_variable at offset 0x60
    void* mCRBOffsetUnit_a{};
    // unknown reference-counted object (created in init_ by 0x7100137a28)
    void* _68{};
    bool _70 = false;
};

}  // namespace uking::action
