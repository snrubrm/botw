#include "Game/AI/aiUnkDamageCallbacks.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

void Unk_71024518c8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a4 == 3) {
        *a5 = -1;
        *a1 = 0;
    }
}

void Unk_7102451938::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if ((*a5 == 7 || *a5 == 8) && *a1 == 0)
        *a1 = _24;
}

void Unk_7102451970::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
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

void Unk_71024519e0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 != -1)
        *a5 = 1;
}

void Unk_7102451a18::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
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

void Unk_7102451a88::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 == 32) {
        *a5 = -1;
        *a4 = -1;
    }
}

void Unk_7102451ac0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 == 20) {
        *a5 = -1;
        *a1 = 0;
        *a4 = -1;
    }
}

void Unk_7102451bd8::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 != -1 && *a5 <= 21)
        *a5 = 2;
}

void Unk_7102451c10::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a4 == 15) {
        *a4 = -1;
        *a5 = -1;
        *a1 = 0;
    }
}

void Unk_7102451c98::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 >= 3)
        *a5 = 2;
}

void Unk_7102451cd0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    auto* manager = sead::DynamicCast<uking::dmg::DamageManagerBase>(mDamageManager);
    if (manager && manager->checkDamageFlags(0))
        return;
    if (*a5 >= 3)
        *a5 = 2;
}

void Unk_7102451d08::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a1 != 0 || *a4 != _30 || !_28)
        return;
    const auto* info = sub_71007A255C(_28, 0);
    if (!info || (_34 & ~info->_54) != 0)
        return;
    const s32* life = _28->getLife();
    *a1 = life ? *life : 1;
}

void Unk_7102451d78::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 != -1 && *a5 < _24)
        *a5 = 2;
}

void Unk_7102451858::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a4 != 1)
        return;
    if (*a5 != 5 && *a5 != 2)
        return;
    if (!mDamageManager)
        return;
    auto* as_list = mDamageManager->mActor->getASList();
    if (!as_list)
        return;
    if (as_list->x(5, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        *a5 = 15;
}

void Unk_7102451890::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 < 3)
        return;
    if (*a5 >= 29 && _25)
        return;
    if (!mDamageManager)
        return;
    if (_24 && (mDamageManager->checkDamageFlags(1) || *a5 == 22)) {
        *a5 = 21;
        return;
    }
    if (*a4 != 4)
        *a5 = 2;
}

void Unk_7102451b30::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    auto* manager = mDamageManager;
    if (!manager)
        return;
    if (_24.isOnBit(0) && (manager->checkDamageFlags(0) || manager->checkDamageFlags(7) ||
                           manager->checkDamageFlags(11))) {
        return;
    }
    switch (*a5) {
    case 15:
        if (_24.isOnBit(1))
            return;
        break;
    case 17:
        if (_24.isOnBit(2))
            return;
        break;
    case 20:
        if (!_24.isOnBit(5))
            *a5 = 2;
        return;
    case 21:
        if (_24.isOnBit(3))
            return;
        break;
    case 22:
        if (_24.isOnBit(4))
            return;
        break;
    default:
        return;
    }
    if (manager->mActor->getASList()->x(5, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                                        true)) {
        return;
    }
    if (isSlowTimeMaybe())
        return;
    *a5 = 2;
}

void Unk_7102451d40::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(mDamageManager);
    if (!manager || manager->getDamageType() != 9)
        return;
    if (*a5 == 5) {
        if (_24 != -1)
            *a5 = _24;
    } else {
        if (_28 != -1)
            *a5 = _28;
    }
}

// 0x7100749720
void Unk_7102451ba0::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                          uking::dmg::DamageCallbackInfo* a6) {
    if (*a5 != 0xf && *a5 != 5)
        return;
    auto* manager = mDamageManager;
    if (!manager)
        return;
    auto* actor = manager->mActor;
    if (actor->getASList()->x(5, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return;
    if (isSlowTimeMaybe())
        return;
    if (_24) {
        *a5 = 2;
        return;
    }
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
        return;
    auto* damage_manager = sead::DynamicCast<uking::dmg::DamageManager>(manager);
    if (damage_manager && damage_manager->sub_71006D8534() > 0)
        return;
    *a5 = 2;
}
