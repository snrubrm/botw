#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class OctarockEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OctarockEscape, ksys::act::ai::Ai)
public:
    explicit OctarockEscape(const InitArg& arg);
    ~OctarockEscape() override;

    bool isChangeable() const override { return false; }
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual sead::Vector3f* m34();
    virtual void m35();

protected:
    void sub_71004EC6F0();
    bool sub_71004EC7A0();
    void sub_71004EC9BC();
    void sub_71004ECB04();
    bool sub_71004ECBB4();

    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    ksys::act::BaseProcLink _40;
    ksys::Timer _50;
};
KSYS_CHECK_SIZE_NX150(OctarockEscape, 0x60);

}  // namespace uking::ai
