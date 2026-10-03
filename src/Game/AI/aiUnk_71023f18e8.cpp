#include "Game/AI/aiUnk_71023f18e8.h"
#include <cmath>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/MathUtil.h"

bool Unk_71023f18e8::m1(sead::Vector3f* out) {
    *out = getPlayerPosition();
    return true;
}

bool Unk_71023f18e8::m2(sead::BufferedSafeString* out) {
    if (!_6c)
        return false;
    if (_6d) {
        out->copy(mGrudeRainObject_s);
    } else if (_60.sub_7100A92248()) {
        out->copy(mGrudeRainObject2_s);
    } else {
        out->copy(mGrudeRainObject_s);
    }
    return !out->isEmpty();
}

// NON_MATCHING: instruction scheduling only (the original computes `-excess` before the dot product
// is finished and loads `*radius` before the compare)
void Unk_71023f18e8::m5(f32* radius, f32* angle, const sead::Vector3f* base) {
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    f32 limit = _3c;
    if (!_6d) {
        if (accessor.isRidingHorse()) {
            if (accessor.x_12())
                limit *= 4;
        } else {
            limit *= 3;
        }
    }

    Unk_71007024d4::m5(radius, angle, base);

    sead::Vector3f pos = *base;
    ksys::util::sub_71011EEF5C(&pos, *angle, *radius);
    sead::Vector3f player;
    m6(&player);
    const f32 dx = player.x - pos.x;
    const f32 dz = player.z - pos.z;
    const f32 excess = limit - std::sqrt(dx * dx + dz * dz);
    if (excess > 0) {
        sead::Vector3f dir;
        m4(&dir);
        sead::Vector3f circle = sead::Vector3f::zero;
        ksys::util::sub_71011EEE98(&circle, *angle, 1.0f);
        dir.y = 0;
        dir.normalize();
        *radius += dir.dot(circle) >= 0 ? excess : -excess;
    }
}

void Unk_71023f18e8::m6(sead::Vector3f* out) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    accessor.getActorMtx().getTranslation(*out);
    *out += accessor.getVelocity() * 24;
}
