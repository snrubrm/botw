#include "Game/Actor/Horse/AI/aiHorseRiddenAI.h"
#include "Game/Actor/actRideable.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Sound/sndBgmMgr.h"

namespace uking::ai {

HorseRiddenAI::HorseRiddenAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool HorseRiddenAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: enum temporaries and flag/child branch scheduling differ.
void HorseRiddenAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _38.makeAllZero();
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable) {
        setFailed();
        return;
    }
    if (rideable->m44())
        rideable->act::RideableBase::_8.setBitOn(9);
    else
        rideable->act::RideableBase::_8.setBitOff(9);
    if (auto* physics = mActor->getPhysics()) {
        const act::Unk_7100e8b2b8::Unk8 type(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff);
        if (type == act::Unk_7100e8b2b8::Unk8::_1)
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::SensorAttackPlayer);
        else if (type == act::Unk_7100e8b2b8::Unk8::_2)
            physics->sub_7100FBAC4C(ksys::phys::ContactLayer::SensorAttackEnemy);
    }
    rideable->sub_7100E8BE10();
    switch (int(act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff))) {
    case 0:
        setFailed();
        break;
    case 1:
        if (rideable->isFlag10On(act::Unk_7100e8b2b8::Flag(act::Unk_7100e8b2b8::Flag::_0))) {
            if (rideable->act::Unk_7100e8b2b8::_8.load() & 0x400) {
                static_cast<act::Unk_7100e8b2b8*>(rideable)->m43();
                rideable->act::Unk_7100e8b2b8::_c = 0;
            }
            changeChild("落馬させる", nullptr);
        } else if (rideable->act::Unk_7100e8b2b8::_8.load() & 0x400) {
            if (!(rideable->act::RideableBase::_8.load() & 0x800) && HorseMgr::instance())
                HorseMgr::instance()->setRiddenHorseMaybe(mActor);
            changeChild("暴れる", nullptr);
        } else {
            if (HorseMgr::instance())
                HorseMgr::instance()->setRiddenHorseMaybe(mActor);
            _38.setBit(Flag(Flag::_1));
            changeChild("従う", nullptr);
        }
        break;
    case 2: {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "CanEscape", -1);
        changeChild("敵が騎乗", &pack);
        _38.setBit(Flag(Flag::_1));
        break;
    }
    case 3:
        changeChild("NPCが騎乗", nullptr);
        _38.setBit(Flag(Flag::_1));
        break;
    }
    if (act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff) ==
        act::Unk_7100e8b2b8::Unk8::_1) {
        if (auto* bgm = ksys::snd::sub_7100FFDD38())
            bgm->_19c = 1;
    }
}

// NON_MATCHING: enum temporaries, SafeString slots and child-selection branches differ.
void HorseRiddenAI::calc_() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable || act::Unk_7100e8b2b8::Unk8(rideable->act::Unk_7100e8b2b8::_8.load() & 0xff) ==
                         act::Unk_7100e8b2b8::Unk8::_0) {
        setFailed();
        return;
    }
    if ((rideable->act::Unk_7100e8b2b8::_8.load() & 0xff) == 1) {
        if (auto* bgm = ksys::snd::sub_7100FFDD38()) {
            const act::Rideable::Gear gear(rideable->_18._b ? rideable->_18._b : rideable->_18._9);
            bgm->_1a0 = int(gear);
        }
    }
    if (isCurrentChild("落馬させる")) {
        const bool flag3 = rideable->isFlag10On(act::Unk_7100e8b2b8::Flag(act::Unk_7100e8b2b8::Flag::_3));
        const bool other_flags = (rideable->act::Unk_7100e8b2b8::_10.load() & 0x28) != 0;
        auto* object = mActor->getMapObject();
        if (mActor->get1a0() ||
            (object && object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) || flag3 || other_flags) {
            act::sub_7100E80D4C(mActor, !_38.isOnBit(Flag(Flag::_0)), flag3, other_flags);
            _38.setBit(Flag(Flag::_0));
            return;
        }
        if (_38.isOnBit(Flag(Flag::_0))) {
            changeChild("落馬させる", nullptr);
            _38.resetBit(Flag(Flag::_0));
        }
    }
    auto* child = getCurrentChild();
    if (child->isFailed()) {
        const sead::SafeString name(child->getName());
        if (name == "暴れる") {
            rideable->m24();
            rideable->act::Unk_7100e8b2b8::_8.setBitOff(10);
            if (rideable->act::RideableBase::_8.load() & 0x800)
                rideable->sub_7100E7EF1C();
            if (int(rideable->sub_7100E8C03C()) == 9)
                rideable->m29(1.0f);
            if (HorseMgr::instance())
                HorseMgr::instance()->setRiddenHorseMaybe(mActor);
            _38.setBit(Flag(Flag::_1));
            changeChild("従う", nullptr);
        } else if (name == "落馬させる") {
            rideable->m22(act::Unk_7100e8b2b8::Unk8(act::Unk_7100e8b2b8::Unk8::_0));
            setFinished();
        } else {
            changeChild(child->getName(), nullptr);
        }
    } else if (child->isFinished()) {
        const sead::SafeString name(child->getName());
        if (name == "暴れる") {
            if (!_38.isOnBit(Flag(Flag::_1))) {
                static_cast<act::Unk_7100e8b2b8*>(rideable)->m43();
                rideable->act::Unk_7100e8b2b8::_c = 0;
            }
            changeChild("落馬させる", nullptr);
        } else if (name == "従う") {
            changeChild(rideable->act::Unk_7100e8b2b8::_8.load() & 0x400 ? "暴れる" : "落馬させる", nullptr);
        } else {
            rideable->m22(act::Unk_7100e8b2b8::Unk8(act::Unk_7100e8b2b8::Unk8::_0));
            setFinished();
        }
    } else if (child->isChangeable() && rideable->isFlag10On(act::Unk_7100e8b2b8::Flag(act::Unk_7100e8b2b8::Flag::_0))) {
        if (isCurrentChild("暴れる") && !_38.isOnBit(Flag(Flag::_1))) {
            static_cast<act::Unk_7100e8b2b8*>(rideable)->m43();
            rideable->act::Unk_7100e8b2b8::_c = 0;
        }
        changeChild("落馬させる", nullptr);
    }
}

// NON_MATCHING: flag branch and BGM clear scheduling differ.
void HorseRiddenAI::leave_() {
    if (auto* physics = mActor->getPhysics()) {
        physics->sub_7100FBACE0(ksys::phys::ContactLayer::SensorAttackPlayer);
        physics->sub_7100FBACE0(ksys::phys::ContactLayer::SensorAttackEnemy);
    }
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;
    if (_38.isOnBit(Flag(Flag::_1))) {
        if (rideable->act::Unk_7100e8b2b8::_c.load() == 1) {
            if (auto* bgm = ksys::snd::sub_7100FFDD38()) {
                bgm->_19c = 0;
                bgm->_1a0 = 0;
            }
        }
    } else {
        static_cast<act::Unk_7100e8b2b8*>(rideable)->m43();
        rideable->act::Unk_7100e8b2b8::_c = 0;
    }
    rideable->m22(act::Unk_7100e8b2b8::Unk8(act::Unk_7100e8b2b8::Unk8::_0));
    rideable->sub_7100E8BD80();
    rideable->_134 = 0;
}

void HorseRiddenAI::loadParams_() {}

}  // namespace uking::ai
