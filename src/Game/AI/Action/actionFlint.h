#pragma once

#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {
class Flint;
}

// vtable 0x71023820a8 (Flint damage callback; no RTTI of its own, its D2 slot is DamageCallback's; D0 at
// 0x710012f760, `call` at 0x710012f2b8). Placeholder name. `call` and D0 are not defined yet: `call` is
// -O0-style code that reads an object returned by DamageManagerBase::m33 (declared as s64).
class Unk_71023820a8 : public uking::dmg::DamageCallback {
public:
    explicit Unk_71023820a8(uking::action::Flint* owner) : mOwner(owner) {}
    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, uking::dmg::DamageCallbackInfo* a6) override;

    uking::action::Flint* mOwner;
};

namespace uking::action {

class Flint : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Flint, ksys::act::ai::Action)
public:
    explicit Flint(const InitArg& arg);
    ~Flint() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x20
        const float* mRadius_s{};
        // static_param at offset 0x28
        const float* mLife_s{};
        // static_param at offset 0x30
        const bool* mSetDelete_s{};
    };
    Params mParams;
    Unk_71023820a8 _38{this};
};
KSYS_CHECK_SIZE_NX150(Flint, 0x68);

}  // namespace uking::action
