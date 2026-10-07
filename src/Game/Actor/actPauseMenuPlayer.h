#pragma once

#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::act {

// CSV PauseMenuPlayer: factory 0x71006e9aec, vtable 0x710244ee40,
// RTTI static 0x71025bb0b8 (direct PlayerOrEnemy subclass).
class PauseMenuPlayer : public ksys::act::PlayerOrEnemy {
    SEAD_RTTI_OVERRIDE(PauseMenuPlayer, ksys::act::PlayerOrEnemy)
public:
    explicit PauseMenuPlayer(const CreateArg& arg);
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~PauseMenuPlayer() override;

protected:
    void finalizeInit_(InitContext* context) override;
    void preDelete3_(const PreDeleteArg& arg) override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;

public:
    void calcMaybe() override;
    ksys::act::PlayerArmors* getArmors() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message& message) override;
    void m114() override;
    bool m165(sead::BufferedSafeString* out) override;
    void coldHotStatusEffectStuff();
    void sub_71006EA6B8(s32 bit);
    void sub_71006E9E24();

    s32 _c38 = 0;
    s32 _c3c = 0;
    s32 _c40 = 0;
    s32 _c44 = 0;
    s32 _c48 = 0;
    sead::BitFlag8 _c4c;
};
KSYS_CHECK_SIZE_NX150(PauseMenuPlayer, 0xc50);

}  // namespace uking::act
