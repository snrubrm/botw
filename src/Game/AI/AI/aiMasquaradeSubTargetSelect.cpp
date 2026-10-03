#include "Game/AI/AI/aiMasquaradeSubTargetSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

MasquaradeSubTargetSelect::MasquaradeSubTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MasquaradeSubTargetSelect::~MasquaradeSubTargetSelect() = default;

bool MasquaradeSubTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MasquaradeSubTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    bool is_mask;
    if (auto* targets = sub_71005D9D68(mActor))
        is_mask = targets->sub_71002DC9E8(*mTargetActor_d, 8, false);
    else
        is_mask = false;

    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    sead::Vector3f pos;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(pos);
    pack.addVec3(pos, "TargetPos", -1);
    if (is_mask)
        changeChild("マスクだった", &pack);
    else
        changeChild("マスクではなかった", &pack);
}

void MasquaradeSubTargetSelect::calc_() {}

bool MasquaradeSubTargetSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool MasquaradeSubTargetSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void MasquaradeSubTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MasquaradeSubTargetSelect::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
