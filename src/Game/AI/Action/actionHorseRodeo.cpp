#include "Game/AI/Action/actionHorseRodeo.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/PlayReportMgr.h"

namespace uking::action {

HorseRodeo::HorseRodeo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRodeo::~HorseRodeo() = default;

bool HorseRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->getHorseOptionsMaybe();
    mActor->getASList()->x_6(1, 0, 0.0f);
    const sead::SafeString& name = rideable && (rideable->RideableBase::_8.load() & 0x800) ?
                                       act::sUnk_7102603190 :
                                       act::sUnk_71026031c0;
    rideable->_18.sub_7100E76E74(name, false);
    ksys::PlayReportMgr::instance()->reportDebug("HorseRodeo", mActor->getName());
    _1c = 0;
    _20 = true;
}

void HorseRodeo::leave_() {
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->_18.sub_7100E770C4(false);
}

void HorseRodeo::loadParams_() {}

void HorseRodeo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
