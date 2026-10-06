#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AscendingCurrent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AscendingCurrent, ksys::act::ai::Action)
public:
    explicit AscendingCurrent(const InitArg& arg);
    ~AscendingCurrent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool hasUpdateForPreDeleteCb() override;

protected:
    void calc_() override;

    void sub_71000A6F24();
    void sub_71000A7354();

    // static_param at offset 0x20
    const float* mWindSpeed_s{};
    // 0x28: a 0x30-byte member (out-of-line ctor at 0x710f122c) followed by 0x58..0x80 pointer/int pairs
    u8 _28[0x58];
};

}  // namespace uking::action
