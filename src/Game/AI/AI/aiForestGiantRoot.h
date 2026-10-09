#pragma once

#include <prim/seadBitFlag.h>
#include "Game/AI/AI/aiEnemyRoot.h"
#include "Game/AI/aiUnk_7102450390.h"
#include "Game/AI/aiUnk_7102451120.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(ForestGiantRoot, EnemyRoot)
public:
    explicit ForestGiantRoot(const InitArg& arg);
    ~ForestGiantRoot() override;

    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;

protected:
    // 0x71003DA620 creates the weak point actors using the supplied heap; returns success.
    bool sub_71003DA620(sead::Heap* heap);
    // 0x71003DAF1C updates the root flags and controller callbacks; called first by calc_.
    void sub_71003DAF1C();

    // Deletes the parts actors "WeakPoint0" .. "WeakPoint3" (called by the destructor; name is a guess).
    void deleteWeakPoints();

    // static_param at offset 0x1d8
    const bool* mIsDamageToEnemy_s{};
    // static_param at offset 0x1e0 (WeakPointNode0 .. WeakPointNode3)
    sead::SafeString mWeakPointNode_s[4]{};
    // aitree_variable at offset 0x220
    bool* mIgnoreGiantArmorCondition_a{};
    // aitree_variable at offset 0x228
    void* mGiantNecklaceUnit_a{};
    Unk_7102450390 _230{mActor};
    // enter_ passes this exact adjacent callback pair to sub_71007214A0.
    Unk_71007214A0 _538;
    // calc_ tests and clears one byte-sized necklace bit per actor-parts slot.
    sead::BitFlag8 _558;
    u8 _559 = 0xff;
};
KSYS_CHECK_SIZE_NX150(ForestGiantRoot, 0x560);

}  // namespace uking::ai
