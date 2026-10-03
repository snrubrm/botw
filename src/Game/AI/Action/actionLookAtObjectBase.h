#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class LookAtObjectBase : public PlayerAction {
    SEAD_RTTI_OVERRIDE(LookAtObjectBase, PlayerAction)
public:
    explicit LookAtObjectBase(const InitArg& arg);
    ~LookAtObjectBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m33();
    // 0x710029e918 / 0x710029ed3c / 0x710029ee04 (declared only; signatures from the callers).
    virtual bool m34(ksys::act::BaseProcLink* link, sead::Vector3f* pos, const sead::SafeString& name1,
                     const sead::SafeString& name2);
    virtual bool m35(ksys::act::BaseProcLink* link, sead::Vector3f* pos, const sead::SafeString& name);
    virtual void m36(const ksys::act::BaseProcLink* link, const sead::Vector3f& pos);
    virtual void m37() {}
    virtual void m38() {}
    virtual sead::Vector3f* m39() { return mTurnPosition_d; }

    f32 _20 = 0.0f;
    f32 _24 = 1.5f;
    f32 _28 = 100.0f;
    f32 _2c = 3.0f;
    s32 _30 = 0;
    s32 _34 = 0;
    sead::Vector3f _38 = sead::Vector3f::zero;
    bool _44 = false;
    bool _45 = false;
    sead::SafeString _48{};
    sead::SafeString _58{};
    sead::Vector3f _68 = sead::Vector3f::zero;

    // dynamic_param at offset 0x78
    int* mObjectId_d{};
    // dynamic_param at offset 0x80
    int* mFaceId_d{};
    // dynamic_param at offset 0x88
    float* mTurnDirection_d{};
    // dynamic_param at offset 0x90
    bool* mIsValid_d{};
    // dynamic_param at offset 0x98
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0xa8
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mPosOffset_d{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mTurnPosition_d{};
};
KSYS_CHECK_SIZE_NX150(LookAtObjectBase, 0xc8);

}  // namespace uking::action
