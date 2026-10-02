#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveByAnimeDriven : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveByAnimeDriven, ksys::act::ai::Action)
public:
    explicit MoveByAnimeDriven(const InitArg& arg);
    ~MoveByAnimeDriven() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual const char* m32();

    // static_param at offset 0x20
    const bool* mIsChangeable_s{};
    // static_param at offset 0x28
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x30
    sead::SafeString mASKeyName_s{};
    // static_param at offset 0x40
    sead::SafeString mTargetBoneName_s{};
    bool _50 = false;
};

KSYS_CHECK_SIZE_NX150(MoveByAnimeDriven, 0x58);

}  // namespace uking::action
