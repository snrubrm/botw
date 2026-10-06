#include "Game/AI/Action/actionDropCreateForReplace.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actDropMgr.h"

namespace uking::action {

DropCreateForReplace::DropCreateForReplace(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DropCreateForReplace::~DropCreateForReplace() = default;

bool DropCreateForReplace::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DropCreateForReplace::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DropCreateForReplace::leave_() {
    ksys::act::ai::Action::leave_();
}

void DropCreateForReplace::loadParams_() {}

void DropCreateForReplace::calc_() {
    auto* drop = static_cast<ksys::act::DropData*>(mActor->getDropData());
    if (drop && isFinishedAS(0, 0) && !mActor->isDeleteRequested() && drop->_8 != 2 &&
        drop->_8 != 1) {
        if (auto* mgr = ksys::act::DropMgr::instance()) {
            if (mgr->sub_7100D2C024(mActor))
                mActor->m135()->_4 = 0;
        }
        drop->_8 = 1;
    }
}

}  // namespace uking::action
