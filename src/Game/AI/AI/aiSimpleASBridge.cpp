#include "Game/AI/AI/aiSimpleASBridge.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SimpleASBridge::SimpleASBridge(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleASBridge::~SimpleASBridge() = default;

bool SimpleASBridge::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleASBridge::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* as_list = mActor->getASList())
        as_list->startAnimationMaybe(-1.0f, -1.0f, mASName_s.cstr(), 0, 0, true);
    changeChild("通常");
}

void SimpleASBridge::calc_() {
    auto* child = getCurrentChild();
    if (!isFinished() && !isFailed()) {
        if (child->isFinished())
            setFinished();
        else if (child->isFailed())
            setFailed();

        auto* as_list = mActor->getASList();
        if (as_list && as_list->x_4(0, 0))
            setFinished();
    }

    if (!isChangeable() && child->isChangeable())
        mFlags.set(Flag::Changeable);
}

void SimpleASBridge::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleASBridge::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::ai
