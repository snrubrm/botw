#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

void Unk_71024518c8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 == 3) {
        *a5 = -1;
        *a1 = 0;
    }
}

void Unk_7102451938::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if ((*a5 == 7 || *a5 == 8) && *a1 == 0)
        *a1 = _24;
}

void Unk_7102451970::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    switch (*a5) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 15:
    case 17:
    case 21:
        *a5 = 22;
        break;
    default:
        break;
    }
}

void Unk_71024519e0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1)
        *a5 = 1;
}

void Unk_7102451a18::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    const s32 type = *a5;
    if (type == -1)
        return;

    if (mActor) {
        const s32 damage = *a1;
        const s32* life_ptr = mActor->getLife();
        const s32 life = life_ptr ? *life_ptr : 1;
        if (type < 28 && life > damage)
            *a5 = 1;
    } else if (type < 28) {
        *a5 = 1;
    }
}

void Unk_7102451a88::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == 32) {
        *a5 = -1;
        *a4 = -1;
    }
}

void Unk_7102451ac0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == 20) {
        *a5 = -1;
        *a1 = 0;
        *a4 = -1;
    }
}

void Unk_7102451bd8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 && *a5 <= 21)
        *a5 = 2;
}

void Unk_7102451c10::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 == 15) {
        *a4 = -1;
        *a5 = -1;
        *a1 = 0;
    }
}

void Unk_7102451c98::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 >= 3)
        *a5 = 2;
}

void Unk_7102451cd0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    auto* manager = sead::DynamicCast<uking::dmg::DamageManagerBase>(mDamageManager);
    if (manager && manager->checkDamageFlags(0))
        return;
    if (*a5 >= 3)
        *a5 = 2;
}

void Unk_7102451d08::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a1 != 0 || *a4 != _30 || !_28)
        return;
    const auto* info = sub_71007A255C(_28, 0);
    if (!info || (_34 & ~info->_54) != 0)
        return;
    const s32* life = _28->getLife();
    *a1 = life ? *life : 1;
}

void Unk_7102451d78::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1 && *a5 < _24)
        *a5 = 2;
}
