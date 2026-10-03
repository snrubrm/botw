#include "Game/AI/AI/aiSimpleLiftable.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

SimpleLiftable::SimpleLiftable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// Inline only (no out-of-line copy in the executable); placeholder name. The same block (with its
// own load of mActor) appears in calc_ and twice in m35.
inline void SimpleLiftable::x() {
    auto* actor = mActor;
    if (auto* physics = actor->getPhysics())
        physics->sub_7100FBADDC();
    ksys::act::disableAllAttClients(actor);
    _38.x();
    changeChild("所持");
}

void SimpleLiftable::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    m35();
}

// NON_MATCHING: the original loads mActor before the m36() call (matches with a single-use
// `auto* actor = mActor;` local declared first, as in handleMessage_)
void SimpleLiftable::calc_() {
    if (m36() && (mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) ||
                  _38._30)) {
        x();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        // Both checks are in the binary but have no effect (empty bodies).
        if (isCurrentChild("所持")) {
        } else if (isCurrentChild("投擲生成")) {
        }
        sub_710056E2B4();
    }
}

bool SimpleLiftable::m36() {
    return isCurrentChild("通常");
}

void SimpleLiftable::m34() {
    _78.x();
}

void SimpleLiftable::m35() {
    auto* actor = mActor;
    bool can_hold;
    if (sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent())) {
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000)) {
            x();
            return;
        }
        can_hold = true;
    } else {
        can_hold = false;
    }

    const int i = actor->getRootAi()->getI();
    if (i == 2) {
        changeChild("投擲生成");
        return;
    }

    if (can_hold && i != 5 && sub_71005DC444(actor)) {
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_40000000);
        x();
        return;
    }

    if (!actor->getMapObject()) {
        if (auto* body = actor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
    }
    changeChild("通常");
}

void SimpleLiftable::sub_710056E2B4() {
    changeChild("通常");
}

bool SimpleLiftable::handleMessage_(const ksys::Message* message) {
    auto* actor = mActor;
    if (m36()) {
        if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _38._30)
            return false;
        if (_38.m2(*message)) {
            m37();
            _38.sub_710070B5A0(actor);
            return true;
        }
    }

    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) || _38._30 ||
        _78._30) {
        return false;
    }
    if (actor->getConnectedCalcParent())
        return false;
    return _78.m2(*message);
}

}  // namespace uking::ai
