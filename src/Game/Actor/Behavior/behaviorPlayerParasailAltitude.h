#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::phys {
class RayCastForRequest;
}

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

    /* 0x28 */ ksys::phys::RayCastForRequest* _28 = nullptr;
    /* 0x30 */ f32 _30 = 0;  // altitude
    /* 0x34 */ sead::Vector3f _34;  // cast start
    /* 0x40 */ s32 _40 = 1;  // frames since the last completed cast
    /* 0x44 */ bool _44 = true;
};
KSYS_CHECK_SIZE_NX150(PlayerParasailAltitude, 0x48);

}  // namespace uking::behavior
