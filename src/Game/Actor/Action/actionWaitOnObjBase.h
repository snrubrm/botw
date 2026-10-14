#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include <math/seadVector.h>
#include <math/seadMatrix.h>

namespace uking::action {

class WaitOnObjBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaitOnObjBase, ksys::act::ai::Action)
public:
    explicit WaitOnObjBase(const InitArg& arg);
    ~WaitOnObjBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mRotReduceRatio_s{};
    /* 0x30 */ ksys::VFRValue _30;
    /* 0x3c */ sead::Matrix33f _3c;
    /* 0x60 */ ksys::VFRValue _60;
    /* 0x6c */ sead::Vector3f _6c;
    /* 0x78 */ sead::Vector3f _78;
    /* 0x84 */ f32 _84 = 0;
    f32 _88 = 0;
    f32 _8c = 0;
    f32 _90 = 0;
    f32 _94 = 0;
    f32 _98 = 0;
    f32 _9c = 0;
    /* 0xa0 */ sead::Vector3f _a0;
    /* 0xac */ ksys::act::CCAccessor _ac;
};
KSYS_CHECK_SIZE_NX150(WaitOnObjBase, 0xb8);

}  // namespace uking::action
