#include "Game/AI/AI/aiKeeseSwarmRoam.h"
#include <algorithm>
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

KeeseSwarmRoam::KeeseSwarmRoam(const InitArg& arg) : CircleMove(arg) {}

KeeseSwarmRoam::~KeeseSwarmRoam() = default;

bool KeeseSwarmRoam::init_(sead::Heap* heap) {
    if (!CircleMove::init_(heap))
        return false;
    _68.fill(0);
    return true;
}

void KeeseSwarmRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMove::enter_(params);
}

void KeeseSwarmRoam::calc_() {
    if (isCurrentChild("移動") && getCurrentChild()->isFailed()) {
        sub_7100454C9C(_58);
        _5c = -_5c;
        sub_710034E90C(true);
    } else {
        CircleMove::calc_();
    }
}

void KeeseSwarmRoam::leave_() {
    CircleMove::leave_();
}

void KeeseSwarmRoam::loadParams_() {
    CircleMove::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

void KeeseSwarmRoam::m34(sead::Vector3f* out) {
    if (out)
        out->set(*mCentralPos_d);
}

void KeeseSwarmRoam::m38(sead::Vector3f* out, f32 angle, f32 radius) {
    CircleMove::m38(out, angle, radius);
    if (out)
        out->y = sub_7100455054(angle) + out->y;
}

// Inline only in the original (placeholder name): the index of one of the ten samples of `_68` (the modulo of a
// possibly negative index).
static s32 wrapIndex(s32 index) {
    s32 result = index % 10;
    if (result < 0)
        result = std::max(result + 10, 0);
    return result;
}

// NON_MATCHING: same sample position block as sub_7100455054 (floor/ceil and the two `% 10` reductions are
// interleaved in the original), and the two sample additions are scheduled differently.
// Adds the swarm at `angle` to the ten samples of _68 (split between the two nearest samples), then smooths the
// neighbouring samples on both sides while the step between them is larger than 2.
void KeeseSwarmRoam::sub_7100454C9C(f32 angle) {
    angle -= sead::Mathf::floor(angle * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    const f32 position =
        angle >= sead::Mathf::pi2() ? 0.0f : angle * 10.0f * (1.0f / sead::Mathf::pi2());
    const s32 lower = sead::Mathf::floor(position);
    const s32 upper = sead::Mathf::ceil(position);
    const s32 a = wrapIndex(lower);
    const s32 b = wrapIndex(upper);
    const f32 weight = sead::Mathf::clamp(1.0f - (position - lower), 0.0f, 1.0f);
    _68[a] += weight;
    _68[b] += 1.0f - weight;

    // Moves sample `i` towards its neighbour `j` if the step between them is larger than 2.
    const auto smooth = [this](s32 i, s32 j) {
        const f32 diff = _68[j] - _68[i];
        if (diff > 2.0f) {
            _68[i] += diff * 0.4f;
            return true;
        }
        return false;
    };

    bool done = false;
    s32 i = a;
    do {
        if (!smooth(i, (i + 1) % 10)) {
            done = true;
            break;
        }
    } while (--i >= 0);
    if (!done) {
        for (s32 i = 9; i >= b; --i) {
            if (!smooth(i, (i + 1) % 10))
                break;
        }
    }

    for (s32 i = b; i < 10; ++i) {
        if (!smooth(i, i + (i < 1 ? 9 : -1)))
            return;
    }
    for (s32 i = 0; i <= a; ++i) {
        if (!smooth(i, i + (i < 1 ? 9 : -1)))
            return;
    }
}

// NON_MATCHING: same operations (angle wrap, ten sample periodic lerp); the original computes floor and ceil of the sample
// position and the two `% 10` reductions as interleaved blocks (cset / smull order), ours keeps them separate
f32 KeeseSwarmRoam::sub_7100455054(f32 angle) {
    angle -= sead::Mathf::floor(angle * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    const f32 position =
        angle >= sead::Mathf::pi2() ? 0.0f : angle * 10.0f * (1.0f / sead::Mathf::pi2());
    const s32 lower = sead::Mathf::floor(position);
    const s32 upper = sead::Mathf::ceil(position);
    const s32 a = wrapIndex(lower);
    const s32 b = wrapIndex(upper);
    const f32 weight = sead::Mathf::clamp(1.0f - (position - lower), 0.0f, 1.0f);
    f32 result = _68[a];
    if (a != b)
        result = weight * result + (1.0f - weight) * _68[b];
    return result;
}

}  // namespace uking::ai
