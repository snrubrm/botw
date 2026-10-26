#include "Game/Actor/aiPriestBossPhaseMembers.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerInfo.h"

// Own TU (0x7100716a18 .. 0x7100717ee8): the destructors branch to Unk_7102450fe0's out-of-line destructor
// instead of inlining it, and the inline Unk_7102450fe0::m6 is emitted here (0x71007171b0).

Unk_7102450e00::Unk_7102450e00() = default;
Unk_7102450e00::~Unk_7102450e00() = default;
Unk_7102450ed8::Unk_7102450ed8() = default;
Unk_7102450ed8::~Unk_7102450ed8() = default;

void Unk_7102450e00::m7(sead::Vector3f* out, s32 idx) {
    const auto& slot = _1e0[*_b0(idx - 2)];
    if (slot.use_angle) {
        m12(out, slot.angle);
        return;
    }
    out->set(slot.pos);
    out->y = _160.y;
}

// TODO
void Unk_7102450e00::m8() {}

void Unk_7102450e00::m10() {
    Unk_7102450fe0::m10();
    _1dc = sead::GlobalRandom::instance()->getF32Range(0.0f, sead::Mathf::pi2());
}

void Unk_7102450e00::m12(sead::Vector3f* out, f32 angle) {
    out->set(_1d8 * sead::Mathf::cos(angle), 0.0f, _1d8 * sead::Mathf::sin(angle));
    *out += getPlayerPosition();
    out->y = _160.y;
}

Unk_7102450e90::Unk_7102450e90() = default;

f32 Unk_7102450e90::m3(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a,
                       ksys::phys::NavMeshCharacterType type, f32 cost) {
    return ksys::phys::NavMeshCharacter::sub_7100F74FD8(
        ksys::phys::NavMeshCharacter::sub_7100F74F94(nav), material);
}

bool Unk_7102450e90::m5(ksys::phys::NavMeshCharacter* nav, s32 material, s32 a, s32 other_material,
                        s32 other_a, ksys::phys::NavMeshCharacterType type) {
    if (material == 5 || other_material == 5) {
        if (_8->isFlagOn(Unk_7102450fa8::Flag::_8))
            return true;
        if (_8 && _8->isFlagOn(Unk_7102450fa8::Flag::_0))
            return true;
    }
    return m4(nav, other_material, other_a, type);
}

bool Unk_7102450e90::m6() {
    return true;
}

// NON_MATCHING: the original loads _1d8 before the member index but multiplies index * _1d8 (operand order only).
void Unk_7102450ed8::m7(sead::Vector3f* out, s32 idx) {
    const f32 t = _1d8 * *_b0(idx - 2) + _1dc;
    out->setScaleAdd(t, _1ec, _1e0);
}

void Unk_7102450ed8::m8() {
    Unk_7102450fe0::m8();
    sub_7100717440();
}

void Unk_7102450ed8::m10() {
    Unk_7102450fe0::m10();
    _98 = 0.1f;
    _1f8 = 0;
    sub_7100717440();
}

