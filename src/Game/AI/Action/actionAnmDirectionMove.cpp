#include "Game/AI/Action/actionAnmDirectionMove.h"
#include <prim/seadStringUtil.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnmDirectionMove::AnmDirectionMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDirectionMove::~AnmDirectionMove() = default;

bool AnmDirectionMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original keeps the two arms as branches (fmov constants joined by a phi) where ours selects with fcsel
void AnmDirectionMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    _68 = 1.0f;
    if (*mDirection_s == 1) {
        _5c.x = 1.0f;
        _5c.y = 0.0f;
        _5c.z = 0.0f;
    } else {
        _5c.x = 0.0f;
        _5c.y = 0.0f;
        _5c.z = 1.0f;
    }
}

void AnmDirectionMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDirectionMove::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mUsereachableCheck_s, "UsereachableCheck");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: only the stack layout differs (the original keeps the parsed scale / the -ey temporary
// above the query struct; ours has the query above them).
void AnmDirectionMove::calc_() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0)) {
        f32 scale;
        if (!sead::StringUtil::tryParseF32(&scale, query.name))
            scale = 1.0f;
        if (scale >= 0.0f) {
            _68 = 1.0f;
        } else {
            _68 = -1.0f;
            scale = -scale;
        }
        scale = sub_7100095AA0(scale);
        _58 = scale / sead::Mathf::clampMin(query._10, 1.0f);
        sub_7100095BD0();
    } else if (sub_71005DD798(mActor, 0x2f, nullptr, 0, 0)) {
        sub_7100095BD0();
    } else {
        sub_7100738488(mActor, *mPosReduceRatio_s, -sead::Vector3f::ey);
    }
    sub_7100738AA8(mActor, *mRotReduceRatio_s);
    if (!mASName_s.isEmpty() && isFinishedAS(0, 0))
        setFinished();
}

f32 AnmDirectionMove::sub_7100095AA0(f32 scale) {
    if (!*mUsereachableCheck_s)
        return scale;
    const sead::Vector3f offset = _5c * _68;
    sead::Vector3f dir;
    dir.setRotated(mActor->getMtx(), offset);
    const sead::Vector3f from = mActor->getMtx().getTranslation();
    sead::Vector3f to = dir * scale + from;
    sub_710072FBD4(0.0f, -1.0f, mActor, from, to, &to, -1);
    const f32 dx = from.x - to.x;
    const f32 dz = from.z - to.z;
    return sead::Mathf::sqrt(dx * dx + dz * dz);
}

void AnmDirectionMove::sub_7100095BD0() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f dir;
    dir.setRotated(mActor->getMtx(), _5c * _68);
    sub_710072C1B4(controller, dir);
    sub_7100737708(controller, _58);
}

}  // namespace uking::action
