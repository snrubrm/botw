#include "Game/AI/Action/actionForkBoneControlFrontGround.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ForkBoneControlFrontGround::ForkBoneControlFrontGround(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBoneControlFrontGround::~ForkBoneControlFrontGround() = default;

bool ForkBoneControlFrontGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBoneControlFrontGround::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkBoneControlFrontGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkBoneControlFrontGround::loadParams_() {
    getStaticParam(&mTargetOffset_s, "TargetOffset");
}

void ForkBoneControlFrontGround::calc_() {
    if (sub_71005DD798(mActor, 44, nullptr, 0, 0)) {
        sead::Vector3f v;
        sub_7100148EB0(1.0f, &v);
        sub_71005DB068(mActor, v);
    }
}

// NON_MATCHING: same arithmetic (translation + x*col0 + y*col1 + z*col2 per component), but the loads and
// adds of the matrix transform are scheduled differently.
void ForkBoneControlFrontGround::sub_7100148EB0(f32 extent, sead::Vector3f* out) {
    const auto& mtx = mActor->getMtx();
    const sead::Vector3f& offset = *mTargetOffset_s;
    const sead::Vector3f pos(
        mtx.m[0][3] + offset.x * mtx.m[0][0] + offset.y * mtx.m[0][1] + offset.z * mtx.m[0][2],
        mtx.m[1][3] + offset.x * mtx.m[1][0] + offset.y * mtx.m[1][1] + offset.z * mtx.m[1][2],
        mtx.m[2][3] + offset.x * mtx.m[2][0] + offset.y * mtx.m[2][1] + offset.z * mtx.m[2][2]);
    const sead::Vector3f from(pos.x, extent * 0.5f + pos.y, pos.z);
    const sead::Vector3f to(pos.x, pos.y - extent * 0.5f, pos.z);
    sead::Vector3f hit;
    if (sub_710072E928(from, to, &hit, nullptr, nullptr, 0.0f))
        out->set(hit);
    else
        out->set(to);
}

}  // namespace uking::action
