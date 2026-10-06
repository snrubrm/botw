#include "Game/AI/Action/actionHorseManeGrabbedAction.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseObject.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"

namespace uking::action {

HorseManeGrabbedAction::HorseManeGrabbedAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseManeGrabbedAction::~HorseManeGrabbedAction() = default;

bool HorseManeGrabbedAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseManeGrabbedAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _8f8 = 0;
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        if (auto* horse = reins->sub_7100E7BA64()) {
            bool synced = false;
            if (horse->getASList()->getSlot0BankCount() >= 6) {
                if (auto* rideable = horse->getHorseOptionsMaybe()) {
                    const ksys::act::Unk_7100d14598 type = rideable->sub_7100E8C03C();
                    switch (type) {
                    case 1:
                    case 2:
                    case 6:
                    case 7:
                        reins->getASList()->startAnimationMaybe(
                            -1.0f, -1.0f,
                            act::sUnk_7102603440[horse->getParam()
                                                     ->getRes()
                                                     .mGParamList->getHorse()
                                                     ->mNature.ref()],
                            0, 0, true);
                        reins->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, 4);
                        _8f8 |= 4;
                        synced = true;
                        break;
                    case 3:
                        reins->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_7102603480, 0,
                                                                0, true);
                        reins->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, 4);
                        _8f8 |= 4;
                        synced = true;
                        break;
                    case 4:
                        reins->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_71026034a0, 0,
                                                                0, true);
                        reins->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, 4);
                        _8f8 |= 4;
                        synced = true;
                        break;
                    default:
                        break;
                    }
                }
            }
            if (!synced) {
                reins->getASList()->goLimpFromHeadShotMaybe(0x2f, horse->getName(), 0);
                reins->getASList()->startAnimationMaybe(-1.0f, -1.0f, act::sUnk_71026034b0, 0, 0,
                                                        true);
            }
        }
    }
    mActor->sub_71011DA824(&_20);
}

void HorseManeGrabbedAction::leave_() {
    mActor->sub_71011DA834(&_20);
    for (s32 i = 0; i < 12; ++i)
        _20.getEntry(i).reset();
}

void HorseManeGrabbedAction::loadParams_() {}

// NON_MATCHING: the 12 matrix constants (a rotation by 1.780236 rad about Y; values verified) are stored in a different
// order / pairing (the original merges m0-m3 into two 64-bit stores); `makeRT`, brace init and element assignment all
// give other store shapes
void HorseManeGrabbedAction::calc_() {
    auto* reins = sead::DynamicCast<act::HorseReins>(mActor);
    if (!reins) {
        setFailed();
        return;
    }
    auto* horse = reins->sub_7100E7BA64();
    auto* rider = sead::DynamicCast<ksys::act::Actor>(reins->_850.getProc(nullptr, nullptr));
    if (horse)
        reins->getASList()->sub_710115F158(horse->getASList(), 0, 0, 0, 4);
    if (horse && horse->getModel()) {
        if (!(_8f8 & 1)) {
            _20.getEntry(0).set(horse, "Root", reins, "", &sead::Matrix34f::ident, true);
            _20.bindAll(horse, reins, {s32(_20.mCount < 2 ? _20.mCount : 2), _20.mEntries}, true);
            _8f8 |= 1;
        }
    } else if (_8f8 & 1) {
        _20.mEntries[0].reset();
        for (s32 i = 2; i < 12; ++i)
            _20.getEntry(i).reset();
        _8f8 &= ~1;
    }
    if (rider && rider->getModel()) {
        if (!(_8f8 & 2)) {
            sead::Matrix34f mtx;
            mtx.makeRT({0.0f, 1.780236f, 0.0f}, {0.0f, 0.0f, 0.0f});
            _20.getEntry(1).set(rider, "Weapon_R", reins, "Mane_2", &mtx, false);
            _8f8 |= 2;
        }
    } else if (_8f8 & 2) {
        _20.getEntry(1).reset();
        _8f8 &= ~2;
    }
}

}  // namespace uking::action
