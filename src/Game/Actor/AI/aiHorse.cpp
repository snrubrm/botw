#include "Game/Actor/AI/aiHorse.h"
#include "Game/Actor/actHorse.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

Horse::Horse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Horse::~Horse() = default;

void Horse::sub_7100435180(const sead::Matrix34f* value) {
    _48.reset(0x70);
    _48.set(0x50);
    _50 = value;
    _4c = 0;
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        rideable->sub_7100E8BE10();
        rideable->Unk_7100e8b2b8::_8 = 0x200;
    }
    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
        horse->sub_7100E6C0E0(true);
}

// NON_MATCHING: block layout (the original duplicates the x_2(66, 26) call into the horse / no-horse paths and threads
// the later horse check), two enum stack slots swapped, and RideableBase::sub_7100E63374 is compared as 32-bit there
// (declared u64 here)
void Horse::sub_71004334C8() {
    auto* as_list = mActor->getASList();
    as_list->x_6(14, 0, 0.0f);
    as_list->x_2(66, 12, false, false);
    as_list->x_2(66, 24, false, false);
    auto* rideable = mActor->getHorseOptionsMaybe();
    auto* horse = sead::DynamicCast<act::Horse>(mActor);
    if (rideable) {
        if (as_list->x_1(0, 0) != act::sUnk_7102603180 || as_list->x_4(0, 0)) {
            const auto gear = act::Rideable::Gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b);
            as_list->x_6(10, 0, static_cast<f32>(int(gear)));
        }
        as_list->x_6(23, 0, rideable->sub_7100E63374() == 2 ? 1.0f : 0.0f);
        as_list->x_2(66, 16, rideable->m39() != nullptr, false);
        as_list->x_2(66, 22, rideable->Unk_7100e8b2b8::sub_7100E8BFF4(), false);
        const act::Unk_7100e8b2b8::Unk8 kind = rideable->Unk_7100e8b2b8::_8.load() & 0xff;
        if (horse)
            as_list->x_2(66, 26, int(kind) != 0 && !horse->sub_7100E696D4(), false);
        else
            as_list->x_2(66, 26, int(kind) != 0, false);
    } else {
        as_list->x_6(10, 0, 0.0f);
        as_list->x_6(23, 0, 0.0f);
        as_list->x_2(66, 16, false, false);
        as_list->x_2(66, 22, false, false);
        as_list->x_2(66, 26, false, false);
    }

    if (!horse) {
        as_list->x_2(66, 3, false, false);
        as_list->x_6(17, 0, 1.0f);
        return;
    }
    as_list->x_2(66, 3, horse->sub_7100E6BE40(), false);
    const HorseMgr::RiddenAnimalType type = horse->x();
    switch (type) {
    case HorseMgr::RiddenAnimalType::_6:
        as_list->x_6(17, 0, 2.0f);
        break;
    case HorseMgr::RiddenAnimalType::_7:
        as_list->x_6(17, 0, 0.5f);
        break;
    default:
        as_list->x_6(17, 0, 1.0f);
        break;
    }
}

void Horse::sub_7100435260() {
    _48.reset(0xb0);
    _48.set(0xa0);
    _4c = 0;
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D8EEE0();
    auto* horse = sead::DynamicCast<act::Horse>(mActor);
    if (!horse)
        return;
    for (int i = 0; i < 12; ++i) {
        // called through a pointer in the original (not devirtualised)
        (&horse->_1028)->m13(i);
    }
    horse->sub_7100E67230();
}

void Horse::sub_7100435420() {
    if (_48.isOn(0x30)) {
        mActor->x_3(0.0f);
        _48.reset(0x30);
        _50 = 0;
        if (auto* rideable = mActor->getHorseOptionsMaybe()) {
            rideable->sub_7100E8BD80();
            rideable->Unk_7100e8b2b8::_8.setBitOff(9);
        }
        if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor)) {
            horse->sub_7100E6C0E0(false);
            horse->_b74.resetBit(3);
        }
    }
}

void Horse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addInt(-1, "ChildSelectAtFirst", -1);
    changeChild("非騎乗", &pack);
    _48.reset(0xfb);
    sub_71004334C8();
    if (_48.isOn(4))
        return;
    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor)) {
        if (!horse->_c00.isEmpty()) {
            if (auto* rideable = horse->getHorseOptionsMaybe())
                rideable->_18.sub_7100E76E74(act::sUnk_7102603330, false);
        }
    }
    _48.set(4);
}

void Horse::leave_() {
    sub_7100435420();
}

// NON_MATCHING: enum temporary stack slots differ.
bool Horse::handleMessage_(const ksys::Message* message) {
    auto* horse = sead::DynamicCast<act::Horse>(mActor);
    auto* rideable = mActor->getHorseOptionsMaybe();
    const u32 type = u32(message->getType());
    switch (type) {
    case 0x3000007:
        if (horse && rideable) {
            const act::Unk_7100e8b2b8::Unk8 kind = rideable->Unk_7100e8b2b8::_8.load() & 0xff;
            if (int(kind) != 0) {
                const act::Unk_7100e8b2b8::Flag10 flag = act::Unk_7100e8b2b8::Flag10::_0;
                rideable->Unk_7100e8b2b8::_10.setBitOn(int(flag));
                return true;
            }
        }
        changeChild("奈落復帰");
        return true;
    case 0x3800001:
        if (isCurrentChild("泳ぐ終了待ち")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addInt(-1, "ChildSelectAtFirst", -1);
            changeChild("非騎乗", &pack);
            return false;
        }
        if (!isCurrentChild("非騎乗")) {
            ksys::gdt::Manager::instance()->setS32(1, "Horse_UnreachableCause");
            return true;
        }
        return false;
    case 0x380001d:
    case 0x380001e: {
        const bool swimming = isCurrentChild("泳ぐ") || isCurrentChild("泳ぐ終了待ち");
        const bool not_ridden = isCurrentChild("非騎乗");
        if (_48.isOn(0x30))
            return true;
        if (swimming || not_ridden) {
            if (!rideable || int(act::Unk_7100e8b2b8::Unk8(rideable->Unk_7100e8b2b8::_8.load() & 0xff)) == 0) {
                auto* payload = static_cast<const sead::Matrix34f*>(message->getUserData());
                if (payload) {
                    if (swimming) {
                        ksys::act::ai::InlineParamPack pack;
                        pack.addInt(-1, "ChildSelectAtFirst", -1);
                        changeChild("非騎乗", &pack);
                    }
                    if (type == 0x380001e)
                        sub_7100435260();
                    else
                        sub_7100435180(payload);
                }
                return true;
            }
        }
        if (rideable && (rideable->Unk_7100e8b2b8::_8.load() & 0xff) == 1)
            return true;
        ksys::gdt::Manager::instance()->setS32(2, "Horse_UnreachableCause");
        return true;
    }
    default:
        return false;
    }
}

void Horse::loadParams_() {
    getStaticParam(&mDistanceFall_s, "DistanceFall");
    getStaticParam(&mDistanceFallDie_s, "DistanceFallDie");
}

}  // namespace uking::ai
