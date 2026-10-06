#include "Game/AI/Action/actionHorseVanish.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseUnit.h"

namespace uking::action {

HorseVanish::HorseVanish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseVanish::~HorseVanish() = default;

bool HorseVanish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: branch layout of the m135() / deleteEx / deleteAndEmit block (the original reloads mActor before the branch)
void HorseVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710072BB28(mActor);
    if (mActor->getMapObject()) {
        mActor->becomePreActor(ksys::act::Actor::DeleteType::_1,
                               ksys::act::BaseProc::DeleteReason::_0);
    } else {
        auto* info = mActor->m135();
        if (!info || info->_0)
            mActor->deleteEx(ksys::act::Actor::DeleteType::_1,
                             ksys::act::BaseProc::DeleteReason::_0);
        else
            mActor->deleteAndEmit(0);
    }
    if (mActor->getParam()->getRes().mGParamList->getHorseUnit()->mRiddenAnimalType.ref() == 9)
        ksys::gdt::Manager::instance()->setBool(false, "AnimalMaster_Appearance");
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->Unk_7100e8b2b8::_8 = 0x200;
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D8EEE0();
}

void HorseVanish::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseVanish::loadParams_() {}

void HorseVanish::calc_() {
    if (auto* horse = sead::DynamicCast<uking::act::HorseBase>(mActor))
        horse->_b74.set(0x20);
}

}  // namespace uking::action
