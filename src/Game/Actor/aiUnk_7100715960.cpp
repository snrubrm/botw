#include "Game/Actor/aiUnk_7100715960.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

Unk_7100715960::Unk_7100715960(ksys::act::Actor* actor) : mActor(actor) {}

Unk_7100715960::~Unk_7100715960() = default;

void Unk_7100715960::sub_7100715B3C() {
    mActor->sub_71011DA868(&_40);
}

void Unk_7100715960::sub_7100715A20(sead::Vector3f* target, const sead::SafeString& bone_name) {
    _40.setName(bone_name);
    _40._68.makeRT(sead::Vector3f::zero, sead::Vector3f::zero);
    mActor->boneHandleStuff(&_40, false);
}

void Unk_7100715960::sub_7100715B4C(sead::Vector3f* target) {
    sead::Vector3f dir;
    sub_7100715C6C(&dir, target);
    sead::Vector3f rot;
    sub_7100715E94(&rot, &dir);
    _40._68.makeRT(rot, sead::Vector3f::zero);
}

// NON_MATCHING: the compiler reuses the forward vector and schedules vector loads differently.
void Unk_7100715960::sub_7100715C6C(sead::Vector3f* out, sead::Vector3f* target) {
    const auto position = mActor->getMtx().getTranslation();
    auto forward = mActor->getMtx().getBase(2);
    forward.y = 0.0f;
    forward.normalize();

    auto direction = *target - position;
    direction.y = 0.0f;
    const f32 distance = direction.normalize();
    sead::Vector3f rotation;
    ksys::util::sub_71011EF10C(&rotation, forward, direction, sead::Vector3f::ey);
    const f32 clamped_distance = sead::Mathf::clamp(distance, _f0, _f4);
    const f32 angle = sead::Mathf::clamp(rotation.y, _e8, _ec);
    ksys::util::sub_71011EF010(&forward, angle);
    *out = position + forward * clamped_distance;
    out->y = target->y;
    if (_f8) {
        sead::Vector3f hit;
        if (somePositionCalc(&hit, *out, -sead::Vector3f::ey, 10.0f))
            out->y = hit.y;
    }
}

// NON_MATCHING: the original loads the matrix rows 0 / 2 as 16-byte vectors (ldur q) and spills row 0 across the
// calls; ours loads single floats (the math itself is identical)
void Unk_7100715960::sub_7100716264(f32 value) {
    const sead::Matrix34f m = _40._68;
    f32 x, y, z;
    if (1.0f - sead::Mathf::abs(m.m[2][0]) < 1.1920929e-06f) {
        x = 0.0f;
        y = m.m[2][0] / sead::Mathf::abs(m.m[2][0]) * -(sead::Mathf::pi() / 2);
        z = std::atan2(-m.m[0][1], -(m.m[0][2] * m.m[2][0]));
    } else {
        x = std::atan2(m.m[2][1], m.m[2][2]);
        y = std::asin(-m.m[2][0]);
        z = std::atan2(m.m[1][0], m.m[0][0]);
    }
    _40._68.makeRT(sead::Vector3f(x * value, y * value, z * value), sead::Vector3f::zero);
}
