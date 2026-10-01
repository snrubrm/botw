#include "Game/AI/Action/actionForkASTrgDeleteChild.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkASTrgDeleteChild::ForkASTrgDeleteChild(const InitArg& arg) : ForkASTrgDelete(arg) {}

ForkASTrgDeleteChild::~ForkASTrgDeleteChild() = default;

void ForkASTrgDeleteChild::m32() {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (child) {
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        mActor->resetConnectedCalcChild(false);
    }
}

}  // namespace uking::action
