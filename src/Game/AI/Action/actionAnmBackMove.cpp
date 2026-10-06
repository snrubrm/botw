#include "Game/AI/Action/actionAnmBackMove.h"
#include <prim/seadStringUtil.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnmBackMove::AnmBackMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmBackMove::~AnmBackMove() = default;

bool AnmBackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmBackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void AnmBackMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmBackMove::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: only the stack layout differs (the original keeps the parsed scale / the -ey temporary
// above the query struct; ours has the query above them).
void AnmBackMove::calc_() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0)) {
        f32 scale;
        if (!sead::StringUtil::tryParseF32(&scale, query.name))
            scale = 1.0f;
        _40 = scale / sead::Mathf::clampMin(query._10, 1.0f);
        sub_71000942B8();
    } else if (sub_71005DD798(mActor, 0x2f, nullptr, 0, 0)) {
        sub_71000942B8();
    } else {
        sub_7100738488(mActor, *mPosReduceRatio_s, -sead::Vector3f::ey);
    }
    sub_7100738AA8(mActor, *mRotReduceRatio_s);
    if (isFinishedAS(0, 0))
        setFinished();
}

void AnmBackMove::sub_71000942B8() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f dir;
    dir.setRotated(mActor->getMtx(), _44);
    sub_710072C1B4(controller, dir);
    sub_7100737708(controller, _40);
}

}  // namespace uking::action
