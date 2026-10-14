#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class SiteBossCreateChildDevice : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossCreateChildDevice, ksys::act::ai::Action)
public:
    explicit SiteBossCreateChildDevice(const InitArg& arg);
    ~SiteBossCreateChildDevice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71002583a4 (declared only; 1072 B): out of line in the original, called by enter_.
    void sub_71002583A4();
    void calc_() override;
    virtual int m32();

    // dynamic_param at offset 0x20
    bool* mIsCreateA_d{};
    // dynamic_param at offset 0x28
    bool* mIsCreateB_d{};
    // dynamic_param at offset 0x30
    bool* mIsCreateC_d{};
    // dynamic_param at offset 0x38
    bool* mIsCreateD_d{};
    u8 _40 = 0;
    bool _41 = false;
    bool _42 = false;
    int _44 = 0;
    ksys::Timer _48;
};

}  // namespace uking::action
