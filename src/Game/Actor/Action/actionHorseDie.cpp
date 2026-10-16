#include "Game/Actor/Action/actionHorseDie.h"
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/actHorse.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

HorseDie::HorseDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseDie::~HorseDie() = default;

bool HorseDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original computes &mASName_s before &rideable->_18 (two add instructions swapped)
void HorseDie::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710072BB28(mActor);
    if (auto* options = mActor->getHorseOptionsMaybe()) {
        options->Unk_7100e8b2b8::_8 = 0x200;
        options->_18.sub_7100E76E74(mASName_s, false);
    }
    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->sub_7100D8EEE0();
        if (!sead::DynamicCast<act::HorseBase>(mActor))
            sub_71006F5940(chemical);
    }
    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor)) {
        horse->_a98._58 |= 1 << int(act::ExtendedEntity::Flag(act::ExtendedEntity::Flag::_3));
        horse->_a98._2c = 1.0f;
        horse->_a98._58 |= 1 << int(act::ExtendedEntity::Flag(act::ExtendedEntity::Flag::_4));
    }
    _40 = 0;
    _44 = -1;
    _48 = 0;
    _4c = true;
}

// NON_MATCHING: only the two SEAD_ENUM stack temporaries are in swapped slots (+8 / +0xc)
void HorseDie::leave_() {
    if (auto* horse = sead::DynamicCast<act::Horse>(mActor)) {
        horse->_f50.sub_71006EDCB8();
        horse->_a98._58 &= ~(1 << int(act::ExtendedEntity::Flag(act::ExtendedEntity::Flag::_3)));
        horse->_a98._2c = 0.1f;
        horse->_a98._58 |= 1 << int(act::ExtendedEntity::Flag(act::ExtendedEntity::Flag::_4));
    }
    sub_71007A3540(mActor);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EC30();
    ksys::act::enableAllAttClients(mActor);
    if (auto* options = mActor->getHorseOptionsMaybe())
        options->Unk_7100e8b2b8::_8 &= ~0x200u;
}

void HorseDie::loadParams_() {
    getStaticParam(&mDyingFrames_s, "DyingFrames");
    getStaticParam(&mCheckIfStable_s, "CheckIfStable");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: the original also keeps a discarded atomic load of the map object flags (an unused demo
// check: _1a0 || map object Flag0::_20000) at the start.
void HorseDie::calc_() {
    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
        horse->_b74.set(0x20);
    xlinkEventOn(mActor, 0x1f, 1, false);

    auto* ragdoll = mActor->getPhysics()->getRagdollInstance();
    auto* controller = mActor->getCharacterController();
    if (ragdoll) {
        ksys::as::ASList::Unk4 query;
        const bool started = mActor->getASList()->x(
            0x23, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
        const s32 index = _44;
        if (started) {
            auto* physics = mActor->getPhysics();
            if (index < 0) {
                _44 = physics->sub_7100FBDA2C("full_keyframed2dynamic");
                if (_44 >= 0) {
                    if (controller) {
                        controller->sub_7100F5EC44();
                        controller->mFlags.reset(8);
                    }
                    mActor->sub_71011D7E24();
                    ragdoll->x_22(-1, 0.0f);
                    mActor->getPhysics()->sub_7100FBC838(_44);
                    mActor->getPhysics()->sub_7100FBDB90(_44, 1.0f);
                    _48 = query._10;
                }
            } else if (mActor->getASList()->x_4(0, 0)) {
                physics->sub_7100FBDB90(index, -1.0f);
            } else {
                physics->sub_7100FBDB90(index, query._10 / _48 + -1.0f);
            }
        } else if (index >= 0) {
            mActor->getPhysics()->sub_7100FBDB90(index, -1.0f);
        } else if (controller && controller->sub_7100F5E954()) {
            act::sub_7100E7F698(mActor->m132(), mActor->getASList(), controller);
        }
    } else if (controller && controller->sub_7100F5E954()) {
        controller->sub_7100F5EC44();
        controller->mFlags.reset(8);
    }

    if (*mCheckIfStable_s || (!_4c && mActor->getASList()->x_4(0, 0)))
        ksys::Timer::update(&_40, 1.0f);

    if (_40 > f32(*mDyingFrames_s)) {
        auto* info = mActor->m135();
        if (info) {
            if (info->_0)
                mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
            else
                mActor->deleteAndEmit(0);
        } else {
            mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
        }
    }
    _4c = false;
}

bool HorseDie::handleMessage_(const ksys::Message* message) {
    if (message->getType() != ksys::MessageType(0x380001c))
        return false;
    auto* info = mActor->m135();
    if (info) {
        if (info->_0)
            mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
        else
            mActor->deleteAndEmit(0);
    } else {
        mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
    }
    return true;
}

}  // namespace uking::action
