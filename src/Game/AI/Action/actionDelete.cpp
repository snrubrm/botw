#include "Game/AI/Action/actionDelete.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Delete::Delete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void Delete::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    switch (*mDeleteType_s) {
    case 0:
        if (actor->m135())
            actor->m135()->_4 = 1;
        callDeleteAndCreateDropAndEmit(actor, 0);
        break;
    case 1:
        actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        break;
    case 2:
    case 3:
        actor->deleteAndEmit(*mDeleteType_s == 3);
        break;
    case 4:
        actor->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
        break;
    case 5:
        callDeleteAndCreateDropAndEmit(actor, 1);
        break;
    default:
        break;
    }
}

void Delete::leave_() {
    ksys::act::ai::Action::leave_();
}

void Delete::loadParams_() {
    getStaticParam(&mDeleteType_s, "DeleteType");
}

void Delete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
