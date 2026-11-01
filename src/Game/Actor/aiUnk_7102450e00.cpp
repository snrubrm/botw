#include "Game/Actor/aiPriestBossPhaseMembers.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadQuat.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/System/VFR.h"

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

// NON_MATCHING: circle search control flow, register allocation and stack layout differ.
void Unk_7102450e00::m8() {
    Unk_7102450fe0::m8();
    if (!isFlagOn(Flag::_0) || !uking::act::PlayerInfo::instance()->getPlayer())
        return;
    if (sub_7100716D98(_1dc, sead::Mathf::pi2() / 9.0f, true) < 2)
        return;

    f32 next_angle = sead::Mathf::pi2();
    f32 prev_angle = 0.0f;
    s32 first = 0;
    do {
        first = (first + 10) % 9;
    } while (first != 0 && _1e0[first].use_angle);
    if (first != 0) {
        s32 next = first;
        do {
            next = (next + 10) % 9;
        } while (next != first && !_1e0[next].use_angle);
        if (next == first)
            next = -1;
        if (next >= 0)
            next_angle = _1e0[next].angle;
        s32 prev = next;
        do {
            prev = (prev + 8) % 9;
        } while (prev != next && !_1e0[prev].use_angle);
        if (prev != next && prev >= 0)
            prev_angle = _1e0[prev].angle;
        while (next_angle > sead::Mathf::pi2())
            next_angle -= sead::Mathf::pi2();
        while (prev_angle > sead::Mathf::pi2())
            prev_angle -= sead::Mathf::pi2();
    }
    if (next_angle < prev_angle)
        next_angle += sead::Mathf::pi2();
    if (uking::act::PlayerInfo::instance()->getPlayer()) {
        const f32 step = (sead::Mathf::pi2() - (next_angle - prev_angle)) * 0.125f;
        getPlayerPosition();
        sead::Vector3f pos;
        for (s32 i = 0; i < 9; ++i) {
            const s16 index = *_b0(i);
            auto& slot = _1e0[index];
            slot.angle = next_angle + step * index;
            m12(&pos, slot.angle);
            slot.use_angle = true;
        }
    }
    _1dc = next_angle;
}

void Unk_7102450e00::m10() {
    Unk_7102450fe0::m10();
    _1dc = sead::GlobalRandom::instance()->getF32Range(0.0f, sead::Mathf::pi2());
}

void Unk_7102450e00::m12(sead::Vector3f* out, f32 angle) {
    out->set(_1d8 * sead::Mathf::cos(angle), 0.0f, _1d8 * sead::Mathf::sin(angle));
    *out += getPlayerPosition();
    out->y = _160.y;
}

// NON_MATCHING: the compiler uses a different floating-point register for one load.
s32 Unk_7102450e00::sub_7100716D98(f32 angle, f32 step, bool check_navmesh) {
    auto* player = uking::act::PlayerInfo::instance()->getPlayer();
    if (!player)
        return 0;

    const auto& player_pos = getPlayerPosition();
    const f32 dx = player_pos.x - _160.x;
    const f32 dz = player_pos.z - _160.z;
    const f32 player_distance = std::sqrt(dx * dx + dz * dz);
    s32 failed = 0;
    sead::Vector3f pos;
    for (s32 i = 0; i < 9; ++i) {
        const s16 index = *_b0(i);
        auto& slot = _1e0[index];
        slot.angle = angle + step * index;
        m12(&pos, slot.angle);
        if (check_navmesh) {
            const f32 x = pos.x - _160.x;
            const f32 z = pos.z - _160.z;
            if (std::sqrt(x * x + z * z) > player_distance)
                slot.use_angle = sub_710071BAB0(&slot.pos, player->m45(), pos);
            else
                slot.use_angle = true;
            if (!slot.use_angle)
                ++failed;
        } else {
            slot.use_angle = true;
        }
    }
    return failed;
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

// NON_MATCHING: the original loads _1d8 into s0 and the member index into s1 (ours swaps the pair); the
// rest of the function is instruction-identical.
void Unk_7102450ed8::m7(sead::Vector3f* out, s32 idx) {
    const f32 t = *_b0(idx - 2) * _1d8 + _1dc;
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


// The line formation's per-frame placement search: probes the navmesh towards the player, then fans the
// twelve path queries out from the player's position and takes the first hit as the new direction.
// NON_MATCHING: ours interleaves the twelve query records' constant stores in a different order than the
// original and keeps two loop values in different registers (the original's count copy lands in both
// branches, ours only on one); the instruction set is otherwise the same.
void Unk_7102450ed8::sub_7100717440() {
    if (!isFlagOn(Flag::_0))
        return;

    if (sub_710071BA04(Step::_2)) {
        _1f8 += ksys::VFR::instance()->getDeltaTime();
        if (_1f8 > 1.6f)
            resetFlag(Flag::_0);
    }

    ksys::sub_7100D8C7FC(&_1ec);
    if (_1ec.x == 0.0f && _1ec.z == 0.0f)
        ksys::sub_7100D8C78C(&_1ec);
    _1ec.y = 0.0f;
    _1ec.normalize();

    _1e0 = getPlayerPosition();
    _1e0.y = _160.y;

    auto* player = uking::act::PlayerInfo::instance()->getPlayer();
    if (!player)
        return;

    sead::Vector3f pos;
    pos.setScaleAdd(_1d8 * 8.0f + _1dc, _1ec, _1e0);

    sead::Vector3f hit;
    if (sub_710071BAB0(&hit, player->m45(), pos))
        return;
    if (sead::Mathf::isNan(hit.x) || sead::Mathf::isNan(hit.y) || sead::Mathf::isNan(hit.z))
        return;

    const sead::Vector2f origin(_1e0.x, _1e0.z);
    const f32 origin_to_pos = (origin - sead::Vector2f(pos.x, pos.z)).length();
    const f32 origin_to_hit = (origin - sead::Vector2f(hit.x, hit.z)).length();
    const f32 t = std::pow(1.0f - origin_to_hit / origin_to_pos, 3.0f);

    const s32 count = (s32(t * 8.0f + 4.0f) + 1) & ~1;
    sead::SafeArray<ksys::phys::HavokAI::Unk3, 12> queries;
    sead::SafeArray<ksys::phys::HavokAI::Unk1, 12> results;
    if (count > 0) {
        const f32 base = t * (sead::Mathf::pi() / 6.0f);
        const f32 step = t * (sead::Mathf::pi2() - 2.0f * base) / f32(count);
        const f32 spread = std::max(step, 0.0872665f);
        const sead::Vector3f dir = _1ec;
        for (s32 i = 0; i < count; ++i) {
            const f32 sign = (i & 1) ? -0.5f : 0.5f;
            const f32 angle = sign * (base + spread * (i / 2 + 1));
            const f32 c = sead::Mathf::cos(angle);
            const f32 s = sead::Mathf::sin(angle);
            const sead::Quatf rot(c, s * sead::Vector3f::ey.x, s * sead::Vector3f::ey.y,
                                  s * sead::Vector3f::ey.z);
            _1ec.setRotated(rot, dir);
            pos.setScaleAdd(_1d8 * 8.0f + _1dc, _1ec, _1e0);
            queries[i]._10 = pos;
            queries[i].radius = 10.0f;
            queries[i].tolerance = _98;
        }

        auto* nav = player->m45();
        auto* havok = nav->_18 ? nav->_18 : ksys::phys::HavokAI::instance();
        havok->sub_7100F842A8(nav, &queries[0], nullptr, &queries[0], std::min(count, 12), &results[0],
                              nullptr);
    }

    for (s32 i = 0; i < count; ++i) {
        const auto& result = results[i];
        if (!result._30)
            continue;
        _1ec = result._c - _1e0;
        _1ec.y = 0.0f;
        _1ec.normalize();
        return;
    }
}
