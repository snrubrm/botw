#include "Game/AI/Action/actionOnEnterSwapDropTableActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

OnEnterSwapDropTableActor::OnEnterSwapDropTableActor(const InitArg& arg)
    : OnEnterSwapDropTable(arg) {}

OnEnterSwapDropTableActor::~OnEnterSwapDropTableActor() = default;

bool OnEnterSwapDropTableActor::init_(sead::Heap* heap) {
    return OnEnterSwapDropTable::init_(heap);
}

void OnEnterSwapDropTableActor::enter_(ksys::act::ai::InlineParamPack* params) {
    OnEnterSwapDropTable::enter_(params);
}

void OnEnterSwapDropTableActor::leave_() {
    OnEnterSwapDropTable::leave_();
}

void OnEnterSwapDropTableActor::loadParams_() {
    OnEnterSwapDropTable::loadParams_();
    getStaticParam(&mDieType_s, "DieType");
}

void OnEnterSwapDropTableActor::calc_() {
    OnEnterSwapDropTable::calc_();
    if (*mDieType_s >= 0) {
        if (auto* info = mActor->m135())
            info->_4 = sub_71005E2B28(*mDieType_s);
    }
    callDeleteAndCreateDropAndEmit(mActor, 0);
}

}  // namespace uking::action
