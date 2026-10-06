#include "Game/AI/Action/actionHorseManeCollarSyncAction.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseObject.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"

namespace uking::action {

HorseManeCollarSyncAction::HorseManeCollarSyncAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

HorseManeCollarSyncAction::~HorseManeCollarSyncAction() = default;

bool HorseManeCollarSyncAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseManeCollarSyncAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = -1;
    auto* mane = sead::DynamicCast<act::HorseObject>(mActor);
    if (!mane)
        return;
    auto* horse = sead::DynamicCast<ksys::act::Actor>(mane->_840.getProc(nullptr, nullptr));
    if (!horse)
        return;
    auto* rideable = horse->getHorseOptionsMaybe();
    const s32 bank_count = horse->getASList()->getSlot0BankCount();
    if (!rideable) {
        if (bank_count >= 3) {
            mane->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_7102603440[0], 0, 0, true);
            _1c = 2;
            mane->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, 2);
        }
    } else if (bank_count >= 5) {
        {
            const act::Unk_7100e8b2b8::Unk8 type = rideable->sub_7100E8C03C();
            switch (type) {
            case 3:
                mane->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_7102603480, 0, 0,
                                                       true);
                break;
            case 4:
                mane->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_71026034a0, 0, 0,
                                                       true);
                break;
            default:
                mane->getASList()->startAnimationMaybe(
                    -1.0f, -1.0f,
                    act::sUnk_7102603440[horse->getParam()
                                             ->getRes()
                                             .mGParamList->getHorse()
                                             ->mNature.ref()],
                    0, 0, true);
                break;
            }
        }
        _1c = 4;
        mane->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, 4);
    }
}

bool HorseManeCollarSyncAction::sub_7100E51F94() {
    if (auto* mane = sead::DynamicCast<act::HorseObject>(mActor)) {
        if (auto* horse = sead::DynamicCast<ksys::act::Actor>(mane->_840.getProc(nullptr, nullptr))) {
            if (auto* rideable = horse->m132())
                return !(rideable->_18._52 & 8);
        }
    }
    return true;
}

void HorseManeCollarSyncAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseManeCollarSyncAction::loadParams_() {}

// NON_MATCHING: register allocation only (the original keeps the AS list in x0 and moves the bool to w8).
void HorseManeCollarSyncAction::calc_() {
    if (_1c >= 0) {
        if (auto* mane = sead::DynamicCast<act::HorseObject>(mActor)) {
            if (auto* horse =
                    sead::DynamicCast<ksys::act::Actor>(mane->_840.getProc(nullptr, nullptr)))
                mane->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, _1c);
        }
    }
    if (auto* physics = mActor->getPhysics()) {
        if (sub_7100E51F94()) {
            const bool no_cloth = physics->sub_7100FBD390();
            auto* as_list = mActor->getASList();
            if (no_cloth) {
                if (as_list->x_1(0, 0) != "PlayAtNoCloth")
                    as_list->startAnimationMaybe(-1.0f, -1.0f, "PlayAtNoCloth", 0, 1, true);
                return;
            }
            as_list->sub_710115B01C(0, 1, true);
            return;
        }
    }
    mActor->getASList()->sub_710115B01C(0, 1, true);
}

}  // namespace uking::action
