#include "Game/AI/AI/aiTargetDirLRInHideSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetDirLRInHideSelect::TargetDirLRInHideSelect(const InitArg& arg) : TargetDirLRSelect(arg) {}

TargetDirLRInHideSelect::~TargetDirLRInHideSelect() = default;

u8 TargetDirLRInHideSelect::m34() {
    if (!sub_71005D8F28(mActor))
        return 0xff;

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    const sead::Vector3f end = front * 5.0f + pos;
    sead::Vector3f normal;
    if (!sub_710072E928(pos, end, nullptr, &normal, nullptr, 1.5f))
        return 0xff;

    sead::Vector3f dir = sub_71005D9330(mActor);
    dir -= mActor->getMtx().getTranslation();
    dir.y = 0.0f;
    dir.normalize();
    return dir.cross(normal).y > 0;
}

}  // namespace uking::ai
