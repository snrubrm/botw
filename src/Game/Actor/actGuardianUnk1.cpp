#include "Game/Actor/actGuardian.h"

// 0x710235b9f0: 70 motion/geometry constants shared by the Guardian helpers (only index 5 is used
// here: the radius scale 4.0f).
KSYS_VISIBILITY_HIDDEN extern const f32 sUnk_710235b9f0[70] = {
    2.5f,          -0.1f,          0.1f,          0.9f,          -0.3f,          4.0f,
    0.1f,          0.01f,          1.3f,          1.0f,          1.0f,           30.0f,
    3.0f,          1.5f,           0.18f,         0.12f,         5.0f,           6.0f,
    1.5f,          1.5f,           2.5f,          4.0f,          8.0f,           8.0f,
    0.2f,          0.2f,           1.8f,          1.8f,          0.2f,           0.2f,
    2.0f,          2.0f,           16.0f,         0.3f,          16.0f,          1.0f,
    1.0f,          7.5f,           3.0f,          7.0f,          9.0f,           0.4f,
    4.4f,          8.5f,           1.0f,          8.5f,          7.0f,           0.1f,
    0.2f,          0.1f,           11.0f,         20.0f,         10.0f,          4.5f,
    4.0f,          200.0f,         50.0f,         3.0f,          6.0f,           2.0f,
    0.0f,          0.03f,          0.4f,          0.0f,          12.0f,          20.0f,
    0.0f,          0.18f,          0.12f,         0.0f,
};

// 0x71025af300: BSS flags of the Guardian helpers (sub_710003B554 / sub_71000380A8).
KSYS_VISIBILITY_HIDDEN u32 sUnk_71025af300 = 0;

// 0x710235ada0: 30 floats shared by the Guardian helpers (m34 reads [28] / [29]).
KSYS_VISIBILITY_HIDDEN extern const f32 sUnk_710235ada0[30] = {
    30.0f,   15.0f,   0.05f,   0.9f,    300.0f, 150.0f, 105.0f, -0.2f,
    0.9f,    60.0f,   30.0f,   20.0f,   1.5708f, 1.0472f, 90.0f, 60.0f,
    0.2f,    42.0f,   0.5f,    60.0f,   0.75f,  0.4f,   0.2f,   30.0f,
    0.4f,    0.025f,  1.0f,    0.5f,    15.0f,  5.0f,
};

namespace uking::act {

ksys::phys::RigidBody* Guardian::Unk1::sub_71000418B8() const {
    return _8->getMainBody();
}

ksys::phys::RigidBody* Guardian::Unk1::sub_71000418C4() const {
    return _8->getMainBody();
}

// Separate TU: the original keeps this out of line (Guardian::sub_710003B3FC tail-calls it).
bool Guardian::Unk1::sub_7100042338() const {
    return _8->sub_71000370B4();
}

void Guardian::Unk1::sub_7100042B40() {
    _64 = 0;
}

void Guardian::Unk1::sub_7100042B48() {}

}  // namespace uking::act
