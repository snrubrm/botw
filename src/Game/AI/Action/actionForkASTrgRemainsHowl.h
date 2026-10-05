#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgRemainsHowl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgRemainsHowl, ksys::act::ai::Action)
public:
    explicit ForkASTrgRemainsHowl(const InitArg& arg);
    ~ForkASTrgRemainsHowl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x7100142ec4 (declared only): out of line in the original.
    void sub_7100142EC4(bool on);
    void sub_7100143068();
    void sub_7100143180();
    void calc_() override;

    // static_param at offset 0x20
    const int* mSeqBank_s{};
    // static_param at offset 0x28
    const int* mTargetBone_s{};
    // dynamic_param at offset 0x30
    bool* mIsTargetLost_d{};
    u64 _38 = 0;
    s32 _40 = 0;
    u8 _44[0x4];
    u64 _48 = 0;
    s32 _50 = 0;
    u8 _54[0x4];

};
KSYS_CHECK_SIZE_NX150(ForkASTrgRemainsHowl, 0x58);

}  // namespace uking::action
