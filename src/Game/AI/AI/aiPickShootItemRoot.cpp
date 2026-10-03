#include "Game/AI/AI/aiPickShootItemRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100EE53C4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PickShootItemRoot::PickShootItemRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PickShootItemRoot::~PickShootItemRoot() = default;

void PickShootItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    ksys::act::sub_7100EE5408(mActor);
    changeChild("待機");
}

void PickShootItemRoot::calc_() {
    if (isCurrentChild("待機")) {
        if (!mActor->getConnectedCalcParent()) {
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        } else if (sub_71005DC444(mActor)) {
            ksys::act::sub_7100EE53C4(mActor);
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            changeChild("所持");
        }
    } else if (isCurrentChild("所持")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            ksys::act::sub_7100EE53C4(mActor);
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
            _40 = ksys::Timer(f32(*mRemainTime_s), f32(*mRemainTime_s));
            changeChild("落下");
        }
    } else {
        _40.update();
        if (_40.value <= sead::Mathf::epsilon())
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

void PickShootItemRoot::loadParams_() {
    getStaticParam(&mRemainTime_s, "RemainTime");
}

}  // namespace uking::ai
