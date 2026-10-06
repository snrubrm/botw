#include "Game/AI/Action/actionSiteBossSwordChemicalPlus.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

SiteBossSwordChemicalPlus::SiteBossSwordChemicalPlus(const InitArg& arg)
    : ActionWithPosAngReduce(arg) {}

SiteBossSwordChemicalPlus::~SiteBossSwordChemicalPlus() = default;

bool SiteBossSwordChemicalPlus::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SiteBossSwordChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    _30 = false;
    _31 = 1;
    _32 = false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->_1558.isOnBit(0))
            _32 = true;
    }
    if (_32)
        playAS("Chemical_Plus", false, 0, 0, -1.0f);
    else
        playAS("Chemical_Change_Sword", false, 0, 0, -1.0f);
}

void SiteBossSwordChemicalPlus::leave_() {
    ActionWithPosAngReduce::leave_();
}

void SiteBossSwordChemicalPlus::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void SiteBossSwordChemicalPlus::sub_7100268FCC() {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (_32)
            boss->x_1(true, false, true);
        if (_31) {
            boss->x_5(true);
            boss->x_6(!boss->_14c8._30.isOn(4));
        }
        boss->sub_71002D223C();
    }
}

void SiteBossSwordChemicalPlus::calc_() {
    ActionWithPosAngReduce::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD780(mActor, 0x51, &query, 0, 0)) {
        _30 = true;
        sub_7100268FCC();
    }
    if (_30) {
        auto* actor = mActor;
        if (actor->get1a0() ||
            (actor->getMapObject() &&
             actor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
            if (auto* boss = sead::DynamicCast<act::SiteBoss>(actor))
                boss->sub_71002D23F0();
        }
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
