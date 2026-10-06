#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "Game/Actor/actArmorBase.h"
#include "Game/Actor/actArmorStrings.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/Utils/Thread/MessageDispatcher.h"

namespace ksys::act {

PlayerArmors::PlayerArmors(bool flag) : _130(flag) {}

PlayerArmors::~PlayerArmors() {
    sub_7100E2D70C();
}

void PlayerArmors::sub_7100E317F0() {
    for (s32 i = 0; i < 3; ++i) {
        if (_10[i].hasProc()) {
            ActorConstDataAccess accessor;
            acquireActor(&_10[i], &accessor);
            if (auto* dispatcher = MessageDispatcher::instance()) {
                const bool processing = dispatcher->isProcessingOnCurrentThread();
                const auto* id = accessor.getMessageTransceiverId();
                if (processing)
                    mTransceiver.sendMessageOnProcessingThread(*id, MessageType(0x4000001), nullptr,
                                                               true);
                else
                    mTransceiver.sendMessage(*id, MessageType(0x4000001), nullptr, true);
            }
        }
    }
}

void PlayerArmors::sub_7100E2D70C() {
    for (s32 i = 0; i < 6; ++i) {
        if (_70[i].isAllocatedOrFailed())
            _70[i].deleteProc();
        ActorConstDataAccess accessor;
        acquireActor(&_10[i], &accessor);
        if (!accessor.sub_7100D14250())
            accessor.deleteLater(BaseProc::DeleteReason::_0);
        _10[i].reset();
    }
}

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

PlayerArmors::EffectFlags* PlayerArmors::sub_7100E2F61C() {
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
    if (_134._2 & 8)
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

s32 PlayerArmors::getHeadMantleType() {
    s32 result = 0;
    if (_10(0).hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10(0), &accessor);
        result = accessor.getArmorHeadMantleType();
    }
    return result;
}

bool PlayerArmors::hasNoPartBeingCreated() {
    for (auto& handle : _70) {
        if (handle.isAllocatedOrFailed())
            return false;
    }
    return true;
}

void PlayerArmors::wakeUpExtraParts() {
    ActorConstDataAccess accessor;
    for (s32 i = 3; i < 6; ++i) {
        if (acquireActor(&_10(i), &accessor))
            accessor.wakeUp(BaseProc::SleepWakeReason::_0);
    }
}

void PlayerArmors::sleepLastPart() {
    ActorConstDataAccess accessor;
    if (acquireActor(&_10(5), &accessor))
        accessor.sleep(BaseProc::SleepWakeReason::_0);
}

s32 PlayerArmors::sub_7100E2ED78(s32 idx) {
    if (idx <= 2 && _10[idx].hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10[idx], &accessor);
        return accessor.sub_7100E2CE80();
    }
    return -1;
}

void PlayerArmors::sub_7100E2EDF8(s32 idx, sead::BufferedSafeString* out) {
    auto& link = _10[idx];
    if (link.hasProc()) {
        ActorConstDataAccess accessor;
        acquireActor(&link, &accessor);
        out->copy(accessor.getName());
    } else {
        out->copy(sUnk_71026022f8[idx]);
    }
}

void PlayerArmors::sub_7100E313FC(s32 idx, sead::BufferedSafeString* out) {
    auto& link = _10[idx];
    if (link.hasProc()) {
        acc::Armor accessor;
        acquireActor(&link, &accessor);
        out->copy(accessor.getArmorHeadMaskType());
    } else {
        out->copy("");
    }
}

// 0x7100e2f000: how many of the first three parts have the ArmorDye tag.
s32 PlayerArmors::sub_7100E2F000() {
    s32 count = 0;
    for (s32 i = 0; i < 3; ++i) {
        sead::FixedSafeString<64> name;
        sub_7100E2EDF8(i, &name);
        if (InfoData::instance()->hasTag(name.cstr(), tags::ArmorDye))
            ++count;
    }
    return count;
}

// 0x7100e2f18c (Player::m280): one of the first three parts is a default armor ("Armor_Default*").
bool PlayerArmors::sub_7100E2F18C() {
    for (s32 i = 0; i < 3; ++i) {
        sead::FixedSafeString<64> name;
        sub_7100E2EDF8(i, &name);
        if (name.startsWith("Armor_Default"))
            return true;
    }
    return false;
}

void PlayerArmors::sub_7100E30B00(s32 idx, sead::BufferedSafeString* out) {
    auto& link = _10[idx];
    if (link.hasProc()) {
        acc::Armor accessor;
        acquireActor(&link, &accessor);
        out->copy(accessor.getSeriesArmorSeriesType());
    } else {
        out->copy("");
    }
}

bool PlayerArmors::sub_7100E30C78(s32 idx, const sead::SafeString& series) {
    sead::FixedSafeString<64> name;
    sub_7100E30B00(idx, &name);
    return series == name;
}

bool PlayerArmors::sub_7100E30DA8() {
    if (_138 == sUnk_71026024c8[2])
        return true;
    if (!sub_7100E30C78(1, sUnk_71026024c8[2]))
        return false;
    const sead::SafeString thunder = "Thunder";
    if (sub_7100E30C78(0, sUnk_71026024c8[2]) || sub_7100E30C78(0, thunder)) {
        const sead::SafeString desert = "Desert";
        const sead::SafeString snow = "Snow";
        if (sub_7100E30C78(2, sUnk_71026024c8[2]) || sub_7100E30C78(2, desert) ||
            sub_7100E30C78(2, snow)) {
            return true;
        }
    }
    return false;
}

void PlayerArmors::setActor(Actor* actor) {
    _128 = actor;
}

}  // namespace ksys::act
