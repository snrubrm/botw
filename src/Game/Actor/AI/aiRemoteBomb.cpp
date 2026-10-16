#include "Game/Actor/AI/aiRemoteBomb.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71006F5B14.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

RemoteBomb::RemoteBomb(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemoteBomb::~RemoteBomb() = default;

bool RemoteBomb::init_(sead::Heap* heap) {
    _198 = nullptr;
    return true;
}

void RemoteBomb::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mXLinkKey_s.isEmpty() && mActor->getRootAi()->getI() != 7) {
        auto* actor = mActor;
        xlinkSearchAndEmit(actor, mXLinkKey_s.cstr(), 2, nullptr);
    }
    _108.x();
    _148.x();

    auto* actor = mActor;
    if (actor->getRootAi()->getI() == 7) {
        if (auto* chemicals = actor->getChemicalContainer()) {
            if (auto* bomb = chemicals->sub_7100E381DC("bomb"))
                bomb->sub_7100D909A4();
        }
        ksys::act::disableAllAttClients(mActor);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        mActor->clearFadeInCreate();
        sub_710054FEF4();
    } else {
        auto* parent = actor->getConnectedCalcParent();
        if (sead::IsDerivedFrom<ksys::act::Actor>(parent) &&
            (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || sub_71005DC444(actor))) {
            if (_198)
                _198->sub_710067EE7C(actor);
            actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
            if (isRootAiParamINot5())
                *mIsIgniteCarriedBomb_a = true;
            if (auto* body = mActor->getMainBody())
                body->changeMotionType(ksys::phys::MotionType::Dynamic);
            _58.x();
            ksys::act::disableAllAttClients(mActor);
            changeChild("所持");
        } else if (actor->getRootAi()->getI() == 2) {
            if (_198)
                _198->sub_710067EE7C(actor);
            ksys::act::disableAllAttClients(mActor);
            changeChild("投擲生成");
        } else {
            if (_198)
                _198->sub_710067EE7C(actor);
            if (auto* body = mActor->getMainBody())
                body->changeMotionType(ksys::phys::MotionType::Dynamic);
            changeChild("待機");
        }
    }

    if (auto* chemical = actor->getChemicalStuff())
        chemical->_14c = *mWindRatio_s;
}

void RemoteBomb::leave_() {
    if (_198 && mActor->isDeletedOrDeleting())
        _198->sub_710067ED08(mActor, 0, false);
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->_14c = 1.0f;
}

// Explodes when the "bomb" chemical says so (state 4) or when ignited / told to; deletes itself when cancelled;
// otherwise picks the carried / placed state from the child status.
void RemoteBomb::calc_() {
    auto* actor = mActor;
    if (auto* body = actor->getMainBody()) {
        body->clearFlag2000000(false);
        actor = mActor;
    }
    if (isCurrentChild("爆発")) {
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
        return;
    }
    if (_d0._30) {
        xlinkSearchAndEmit(actor, "Cancel", 2, nullptr);
        actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }

    if (auto* chemicals = mActor->getChemicalContainer()) {
        if (auto* bomb = chemicals->sub_7100E381DC("bomb")) {
            if (bomb->_c0 == 4) {
                sub_7100550260();
                return;
            }
            if (isCurrentChild("爆発予約"))
                return;
            if (_98._30 || sub_71005E2B48(mActor)) {
                if (!sub_71006F5934(bomb))
                    sub_71006F5A80(bomb);
                bomb->sub_7100D909A4();
                sub_710054FEF4();
                return;
            }
        }
    }

    if (isCurrentChild("爆発予約"))
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("爆発")) {
            actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            return;
        }
        changeChild("待機");
        return;
    }
    if (!child->isChangeable())
        return;

    auto* main_body = mActor->getMainBody();
    if (main_body && main_body->getMotionType() == ksys::phys::MotionType::Keyframed) {
        ksys::act::enableAllAttClients(actor);
        _1a0 = true;
    } else if (auto* unk = actor->m100(); unk && unk->sub_7100E502B8()) {
        ksys::act::disableAllAttClients(actor);
    } else {
        ksys::act::enableAllAttClients(actor);
    }
    if (!_58._30)
        return;

    if (isRootAiParamINot5())
        *mIsIgniteCarriedBomb_a = true;
    if (auto* body = mActor->getMainBody())
        body->changeMotionType(ksys::phys::MotionType::Dynamic);
    _58.x();
    ksys::act::disableAllAttClients(mActor);
    changeChild("所持");
}

// NON_MATCHING: registers and SafeString temporary scheduling
bool RemoteBomb::handleMessage_(const ksys::Message* message) {
    if (_108.m2(*message)) {
        _198 = _108._38;
        if (!_198)
            return false;
        _198->sub_710067ED08(mActor, 0, true);
        return true;
    }
    if (_98.m2(*message)) {
        if (_198) {
            _198->sub_710067ED08(mActor, 0, false);
            _198->sub_710067ED08(mActor, 3, true);
        }
        mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, true);
        return true;
    }
    if (!isCurrentChild("爆発") && _d0.m2(*message))
        return true;

    bool picked_up = false;
    if (isCurrentChild("待機")) {
        if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000))
            return false;
        if (_58._30)
            return false;
        if (_148._30)
            return false;
        if (_58.m2(*message)) {
            _58.sub_710070B5A0(mActor);
            return true;
        }
        picked_up = _148.m2(*message);
    }
    if (!picked_up) {
        if (!isCurrentChild("所持"))
            return false;
        if (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _148._30 ||
            !_148.m2(*message)) {
            return false;
        }
    }
    if (_198)
        _198->sub_710067EDDC(mActor, _148._38.mLink);
    return true;
}

void RemoteBomb::sub_710054FEF4() {
    _58.x();
    if (_198) {
        _198->sub_710067ED08(mActor, 0, false);
        _198->sub_710067ED08(mActor, 3, true);
    }
    ksys::act::disableAllAttClients(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, true);
    changeChild("爆発予約");
}

void RemoteBomb::sub_7100550260() {
    _58.x();
    if (_198) {
        _198->sub_710067ED08(mActor, 0, false);
        _198->sub_710067ED08(mActor, 3, true);
    }
    ksys::act::disableAllAttClients(mActor);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    changeChild("爆発");
}

void RemoteBomb::loadParams_() {
    getStaticParam(&mWindRatio_s, "WindRatio");
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getAITreeVariable(&mIsIgniteCarriedBomb_a, "IsIgniteCarriedBomb");
}

}  // namespace uking::ai
