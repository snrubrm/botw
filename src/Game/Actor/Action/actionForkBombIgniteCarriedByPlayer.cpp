#include "Game/Actor/Action/actionForkBombIgniteCarriedByPlayer.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

ForkBombIgniteCarriedByPlayer::ForkBombIgniteCarriedByPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBombIgniteCarriedByPlayer::~ForkBombIgniteCarriedByPlayer() = default;

bool ForkBombIgniteCarriedByPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBombIgniteCarriedByPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkBombIgniteCarriedByPlayer::leave_() {
    if (_1c) {
        _1c = false;
        auto* actor = mActor;

        if (auto* unit = actor->m100())
            unit->_1c8._10 &= ~2;
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);

        if (auto* chemicals = mActor->getChemicalContainer()) {
            if (auto* bomb = chemicals->sub_7100E381DC("bomb")) {
                if (!sub_71006F5934(bomb))
                    sub_71006F5A80(bomb);
            }
        }

        auto* proc = mActor;
        if (auto* body = proc->getMainBody()) {
            if (auto* info = body->getContactPointInfo())
                info->set30(0);
        }

        if (auto* unit = mActor->m100())
            unit->_1c8._8 &= ~2;

        auto* awareness = proc->get548();
        sub_71007A3800(proc);
        sub_71006F5A80(proc->getChemicalStuff());
        if (awareness)
            awareness->_18._50 = 0;
    } else if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_20) &&
               !isActorDeletedOrDeleting()) {
        if (auto* chemicals = mActor->getChemicalContainer()) {
            if (auto* bomb = chemicals->sub_7100E381DC("bomb")) {
                if (!sub_71006F5934(bomb))
                    sub_71006F5A80(bomb);
            }
        }
    }
}

void ForkBombIgniteCarriedByPlayer::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getAITreeVariable(&mIsIgniteCarriedBomb_a, "IsIgniteCarriedBomb");
}

void ForkBombIgniteCarriedByPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
