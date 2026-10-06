#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "Game/Actor/actArmorBase.h"
#include "Game/Actor/actArmorStrings.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtManagerInline.h"

namespace ksys::act {

bool PlayerArmors::hasAncientPowUpEffect() {
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            if (accessor.getArmorEffectAncientPowUp())
                return true;
        }
    }
    return false;
}

void PlayerArmors::sub_7100E31B9C(Unk117* arg) {
    for (int i = 0; i < 6; ++i) {
        if (auto* actor = sead::DynamicCast<Actor>(_10(i).getProc(nullptr, nullptr)))
            actor->x_17(arg);
    }
}

void PlayerArmors::sleep(BaseProc::SleepWakeReason reason) {
    for (int i = 0; i < 6; ++i) {
        if (_10(i).hasProc()) {
            ActorConstDataAccess accessor;
            acquireActor(&_10(i), &accessor);
            accessor.sleep(reason);
        }
    }
}

void PlayerArmors::sub_7100E3170C(BaseProc::SleepWakeReason reason) {
    bool flag = false;
    s32 count = 3;
    if (auto* mgr = gdt::Manager::instance()) {
        gdt::getBoolByName(mgr, &flag, "IsGet_PortableUnit");
        count = !flag ? 3 : 6;
    }
    for (int i = 0; i < count; ++i) {
        ActorConstDataAccess accessor;
        if (acquireActor(&_10[i], &accessor))
            accessor.wakeUp(reason);
    }
}

s32 PlayerArmors::sub_7100E2F490() {
    s32 result = 0;
    if (_10(1).hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10(1), &accessor);
        result = accessor.getArmorUpperUseMantleType();
    }
    return result;
}

bool PlayerArmors::sub_7100E2F428() {
    bool result = false;
    if (_10(1).hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10(1), &accessor);
        result = accessor.getArmorUpperDisableSelfMantle();
    }
    return result;
}

bool PlayerArmors::sub_7100E2F358() {
    bool result = false;
    if (_10(0).hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10(0), &accessor);
        result = accessor.sub_7100E2BF44();
    }
    return result;
}

sead::BitFlag16* PlayerArmors::sub_7100E2F61C() {
    return &_134;
}

s32 PlayerArmors::getArmorEffectLevelResistBurn() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[2]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelResistCold() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[3]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelResistFreeze() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[17]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelResistLightning() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[5]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelSwimSpeed() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[6]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelClimbSpeed() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[7]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelAttackUp() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[8]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelQuietness() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[9]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelSandMove() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[10]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelSnowMove() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[11]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelResistAncient() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[12]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorEffectLevelClimbSpeedHorizontalOnly() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[20]);
        }
    }
    return level;
}

s32 PlayerArmors::getArmorDefenceAddLevelSum() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorDefenceAddLevel();
        }
    }
    return level;
}

bool PlayerArmors::hasEnableClimbWaterfall() {
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            if (accessor.getArmorEffectEnableClimbWaterfall())
                return true;
        }
    }
    return false;
}

bool PlayerArmors::hasEnableSpinAttack() {
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            if (accessor.getArmorEffectEnableSpinAttack())
                return true;
        }
    }
    return false;
}

bool PlayerArmors::hasSeriesCompBonus() {
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            if (!accessor.getSeriesArmorEnableCompBonus())
                return false;
        }
    }
    return true;
}

s32 PlayerArmors::getArmorEffectLevelResistHot() {
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[1]);
        }
    }
    if (_134.isOnBit(2) && level == 0)
        return 1;
    return level;
}

s32 PlayerArmors::getArmorEffectLevelResistElectric() {
    if (getArmorEffectLevelResistLightning() > 0)
        return 3;
    s32 level = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            level += accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[4]);
        }
    }
    return level;
}

bool PlayerArmors::hasWakeWindArmorEffect() {
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            if (accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[18]) > 0)
                return true;
        }
    }
    return false;
}

bool PlayerArmors::hasBeamPowerUpEffect() {
    if (_136 & 8)
        return true;
    for (s32 i = 0; i < 3; ++i) {
        if (_10(i).hasProc()) {
            acc::Armor accessor;
            acquireActor(&_10(i), &accessor);
            if (accessor.getArmorEffectEffectLevel_checkEffect(sUnk_7102602358[19]) > 0)
                return true;
        }
    }
    return false;
}

}  // namespace ksys::act
