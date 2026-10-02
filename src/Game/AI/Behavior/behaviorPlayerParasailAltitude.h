#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayerParasailAltitude : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerParasailAltitude, ksys::act::ai::Behavior)
public:
    explicit PlayerParasailAltitude(const InitArg& arg);
    ~PlayerParasailAltitude() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ u32 _30 = 0;
    /* 0x34 */ u8 _34[0xc];
    /* 0x40 */ u32 _40 = 0x1;
    /* 0x44 */ bool _44 = true;
};
KSYS_CHECK_SIZE_NX150(PlayerParasailAltitude, 0x48);

}  // namespace uking::behavior
