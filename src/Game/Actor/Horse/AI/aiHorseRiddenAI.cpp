#include "Game/Actor/Horse/AI/aiHorseRiddenAI.h"
#include "Game/Actor/actRideable.h"
#include "Game/gameHorseMgr.h"
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

void HorseRiddenAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRiddenAI::loadParams_() {}

}  // namespace uking::ai
