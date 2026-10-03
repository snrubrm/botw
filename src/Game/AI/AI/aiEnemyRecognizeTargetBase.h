#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class EnemyRecognizeTargetBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRecognizeTargetBase, ksys::act::ai::Ai)
public:
    explicit EnemyRecognizeTargetBase(const InitArg& arg);
    ~EnemyRecognizeTargetBase() override;
    virtual bool m34();
    virtual bool m35();
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    // 0x71003b08c0 (placeholder name)
    void sub_71003B08C0();

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const int* mCryInterval_s{};
    // static_param at offset 0x50
    const int* mRandomCryInterval_s{};
    // static_param at offset 0x58
    const int* mRandomCryIntervalMax_s{};
    // static_param at offset 0x60
    const float* mSpreadDist_s{};
    // static_param at offset 0x68
    const float* mNoCryDist_s{};
    void* _70{};
    void* _78{};
    ksys::act::BaseProcLink _80;
    Unk_7102372510 _90{mActor, 0x8000008};
    Unk_7102450a98 _c0;
    s32 _120 = 0;
    bool _124 = false;
    bool _125 = false;
};
KSYS_CHECK_SIZE_NX150(EnemyRecognizeTargetBase, 0x128);

}  // namespace uking::ai
