#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// Damage callback embedded in KokkoRoot (_248); vtable 0x71023fff70 (placeholder name), no RTTI
// override. `call` (0x710045746c) compares the attacker's name with _28 and reads its last argument
// as an object of an unknown RTTI class (like Unk_71024519a8), so it is declared only.
class Unk_71023fff70 : public dmg::DamageCallback {
public:
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) override;

    sead::FixedSafeString<64> _28;
    bool _80 = false;
};

class KokkoRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(KokkoRoot, PreyRoot)
public:
    explicit KokkoRoot(const InitArg& arg);
    ~KokkoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m40() override;
    void m41() override;
    void m43() override;
    void m46() override;
    // 0x7100457240 (placeholder name)
    void changeToAngry();

protected:
    // static_param at offset 0x208
    const int* mStartSpecialAttackCount_s{};
    // static_param at offset 0x210
    sead::SafeString mAvoidCountActorName_s{};
    s32 _220 = 0;
    ksys::act::BaseProcLink _228;
    ksys::Timer _238;
    Unk_71023fff70 _248;
};
KSYS_CHECK_SIZE_NX150(KokkoRoot, 0x2d0);

}  // namespace uking::ai
