#include "Game/AI/aiUnk_71007024d4.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/Utils/MathUtil.h"

bool Unk_71007024d4::m0(sead::Vector3f* out) {
    f32 radius, angle;
    sead::Vector3f base;
    m6(&base);

    sead::Vector3f pos;
    if (m4(&pos)) {
        pos.y = 0;
        pos.normalize();
        pos = base + pos * _30;
    } else {
        pos = base;
    }
    pos.y += _34;

    m5(&radius, &angle, &pos);
    sead::Vector3f result = pos;
    result.x += std::cos(angle) * radius;
    result.z += std::sin(angle) * radius;
    if (sead::Mathf::sqrt(ksys::util::sqXZDistance(result, base)) < _3c) {
        sead::Vector3f result2 = pos;
        m5(&radius, &angle, &pos);
        result2.x += std::cos(angle) * radius;
        result2.z += std::sin(angle) * radius;
        if (!(sead::Mathf::sqrt(ksys::util::sqXZDistance(result2, base)) <
              sead::Mathf::sqrt(ksys::util::sqXZDistance(result, base))))
            result.set(result2);
    }
    *out = result;
    return true;
}

bool Unk_71007024d4::m4(sead::Vector3f* out) {
    return ksys::sub_7100D8C7FC(out);
}

// NON_MATCHING: the original loads `_38` before the GlobalRandom instance pointer (argument evaluated first)
void Unk_71007024d4::m5(f32* radius, f32* angle, const sead::Vector3f* base) {
    *radius = sead::GlobalRandom::instance()->getF32Range(0.0f, _38);
    *angle = sead::Mathf::deg2rad(sead::GlobalRandom::instance()->getS32Range(0, 360));
}

void Unk_71007024d4::m6(sead::Vector3f* out) {
    *out = getPlayerPosition();
}
