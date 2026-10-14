#include "Game/Actor/AI/aiStalHeadLifted.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

StalHeadLifted::StalHeadLifted(const InitArg& arg) : Lifted(arg) {}

StalHeadLifted::~StalHeadLifted() = default;

bool StalHeadLifted::init_(sead::Heap* heap) {
    return Lifted::init_(heap);
}

void StalHeadLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    Lifted::enter_(params);
}

// NON_MATCHING: vector normalization keeps an intermediate stack copy and schedules products differently.
void StalHeadLifted::calc_() {
    Lifted::calc_();
    if (isCurrentChild("所持") && sub_71005DD780(mActor, 71, nullptr, 0, 0)) {
        sead::Vector3f direction = *mEscapeDir_s;
        direction.normalize();
        direction *= *mEscapeSpeed_s;
        direction *= ksys::act::sub_7100EDD218(mActor);
        sub_71005A66E8(direction, false);
    } else {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && isCurrentChild("逃走"))
            setFinished();
    }
}

void StalHeadLifted::sub_71005A66E8(const sead::Vector3f& direction, bool a1) {
    auto* actor = mActor;
    ksys::act::ai::InlineParamPack params;
    if (direction.x == 0.0f && direction.y == 0.0f && direction.z == 0.0f) {
        params.addFloat(0.0f, "Power", -1);
        params.addVec3(direction, "TargetDir", -1);
        params.addBool(a1, "IsShootByPlayer", -1);
    } else {
        sead::Vector3f dir = direction;
        const f32 power = dir.normalize();
        params.addFloat(power, "Power", -1);
        params.addVec3(dir, "TargetDir", -1);
        params.addBool(a1, "IsShootByPlayer", -1);
    }
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_40000000);
    changeChild("逃走", &params);
}

void StalHeadLifted::leave_() {
    Lifted::leave_();
}

void StalHeadLifted::loadParams_() {
    Lifted::loadParams_();
    getStaticParam(&mEscapeSpeed_s, "EscapeSpeed");
    getStaticParam(&mEscapeDir_s, "EscapeDir");
}

}  // namespace uking::ai
