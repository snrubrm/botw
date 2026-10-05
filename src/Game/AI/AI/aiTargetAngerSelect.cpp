#include "Game/AI/AI/aiTargetAngerSelect.h"
#include "Game/AI/aiUnk_710001A69C.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

TargetAngerSelect::TargetAngerSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetAngerSelect::~TargetAngerSelect() = default;

bool TargetAngerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetAngerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* target = sub_71005D9050(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(target, &accessor);
        if (sub_710001A69C(&accessor, 0x40))
            changeChild("対象怒り", params);
        else
            changeChild("通常", params);
    } else {
        changeChild("通常", params);
    }
}

void TargetAngerSelect::calc_() {
    bool angry = false;
    if (auto* target = sub_71005D9050(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(target, &accessor);
        angry = sub_710001A69C(&accessor, 0x40);
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("怒り移行"))
            changeChild("対象怒り");
    } else if (child->isChangeable() && getCurrentChild()->isChangeable()) {
        if (isCurrentChild("通常")) {
            if (angry)
                changeChild("怒り移行");
        } else if (!angry) {
            changeChild("通常");
        }
    }
}

void TargetAngerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetAngerSelect::loadParams_() {}

bool TargetAngerSelect::isFailed() const {
    if (isCurrentChild("怒り移行"))
        return false;
    return getCurrentChild()->isFailed();
}

bool TargetAngerSelect::isFinished() const {
    if (isCurrentChild("怒り移行"))
        return false;
    return getCurrentChild()->isFinished();
}

}  // namespace uking::ai
