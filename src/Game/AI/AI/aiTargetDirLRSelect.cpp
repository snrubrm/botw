#include "Game/AI/AI/aiTargetDirLRSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetDirLRSelect::TargetDirLRSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetDirLRSelect::~TargetDirLRSelect() = default;

void TargetDirLRSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (m34()) {
    case 0:
        changeChild("左側", params);
        break;
    case 1:
        changeChild("右側", params);
        break;
    default:
        changeChild("左側", params);
        setFailed();
        break;
    }
}

// NON_MATCHING: the original loads target x / z and the actor x / z first (four loads), then subtracts; ours interleaves
u8 TargetDirLRSelect::m34() {
    if (!sub_71005D8F28(mActor))
        return 0xff;
    const sead::Vector3f& target = sub_71005D9330(mActor);
    const sead::Vector2f diff(target.x - mActor->getMtx().m[0][3],
                              target.z - mActor->getMtx().m[2][3]);
    sead::Vector3f dir(diff.x, 0.0f, diff.y);
    dir.normalize();
    return dir.z * mActor->getMtx().m[0][2] - dir.x * mActor->getMtx().m[2][2] > 0.0f;
}

void TargetDirLRSelect::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (getCurrentChild()->isFinished())
        setFinished();
    else
        setFailed();
}

}  // namespace uking::ai
