#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AssassinBossIronBallAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AssassinBossIronBallAttack, ksys::act::ai::Action)
public:
    explicit AssassinBossIronBallAttack(const InitArg& arg);
    ~AssassinBossIronBallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(sead::Vector3f* out);
    virtual void m33(sead::Vector3f* out);

    // static_param at offset 0x20
    const int* mIronBallNum_s{};
    // static_param at offset 0x28
    const int* mAttackType_s{};
    // static_param at offset 0x30
    sead::SafeString mIronBallPartsName_s{};
    sead::Buffer<Unk_7102368740> _40;
    sead::Buffer<bool> _50;
    int _60 = 0;
};

}  // namespace uking::action
