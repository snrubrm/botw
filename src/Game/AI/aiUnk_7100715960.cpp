#include "Game/AI/aiUnk_7100715960.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

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
