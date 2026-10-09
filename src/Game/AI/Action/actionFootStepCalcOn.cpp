#include "Game/AI/Action/actionFootStepCalcOn.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

FootStepCalcOn::FootStepCalcOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FootStepCalcOn::~FootStepCalcOn() = default;

bool FootStepCalcOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FootStepCalcOn::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100DA1A0C(true);
}

void FootStepCalcOn::leave_() {
    sub_7100DA1A0C(false);
}

void FootStepCalcOn::loadParams_() {
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void FootStepCalcOn::sub_7100DA1A0C(bool on) {
    auto* manager = ksys::evt::Manager::instance();
    if (auto* link = manager->getBaseProcLinkFromActiveEvent(sead::SafeString(mActor_d.cstr()),
                                                           sead::SafeString(mInstanceName_d.cstr()))) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (accessor.sub_7100D0F214()) {
            if (auto* xlink = accessor.sub_7100D0F214())
                xlink->_a0->sub_710123827C(on);
        }
    } else if (mActor_d == "GameROMPlayer") {
        if (auto* xlink = ksys::evt::Manager::instance()->_1d108->getPlayer()->getXLink())
            xlink->_a0->sub_710123827C(on);
    }
}

void FootStepCalcOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
