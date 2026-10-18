#include "Game/Actor/Action/actionPullOut.h"
#include "Game/Actor/actGiantEnemy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actUnk_71024eed28.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

// NON_MATCHING: the original zeroes the params before the vtable store
PullOut::PullOut(const InitArg& arg) : ActionWithAS(arg) {}

PullOut::~PullOut() = default;

bool PullOut::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void PullOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    playAS("PullOut", false, 0, 0, -1.0f);
}

void PullOut::leave_() {
    sub_7100223B90();
    ActionWithAS::leave_();
}

void PullOut::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mParams.mAnimGrabPos_s, "AnimGrabPos");
    getDynamicParam(&mParams.mTargetActor_d, "TargetActor");
}

bool PullOut::handleMessage_(const ksys::Message* message) {
    if (_70.m2(*message)) {
        auto* proc = _70._38.mLink.getProc(nullptr, nullptr);
        auto* actor = sead::DynamicCast<ksys::act::Actor>(proc);
        if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(actor)) {
            sub_71005D8A30(mActor, weapon, 0);
            if (auto* as_list = mActor->getASList())
                as_list->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
            sub_7100223B90();
        }
    }
    return false;
}

void PullOut::calc_() {
    ActionWithAS::calc_();
    if (!sub_71005D83E8(mActor, 0))
        sub_7100223964();
    if (sub_71005DD780(mActor, 0x45, nullptr, 0, 0)) {
        _40._18.sub_710070E3D8(mActor);
        _40.sub_710070DCC0(mParams.mTargetActor_d, true);
    }
}

// NON_MATCHING: the original schedules the _98 / _9c stores and the _c8 vector store after the
// whole matrix product; the arithmetic and result are identical.
void PullOut::sub_7100223964() {
    auto* enemy = sead::DynamicCast<uking::act::GiantEnemy>(mActor);
    if (!enemy)
        return;
    auto* child = enemy->_1558 ? enemy->_1558->m7() : nullptr;
    auto* grab = sead::DynamicCast<ksys::act::Unk_7102359478>(child);
    if (!grab)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(mParams.mTargetActor_d, &accessor);
    const sead::Vector3f target_pos = accessor.getActorMtx().getTranslation();
    sead::Matrix34f inverse;
    inverse.setInverse(mActor->getMtx());

    grab->_98 |= 1;
    grab->_9c = 1;
    grab->_c8 = sead::Vector3f(
        inverse.m[0][3] + (target_pos.x * inverse.m[0][0] + target_pos.y * inverse.m[0][1] +
                           target_pos.z * inverse.m[0][2]),
        inverse.m[1][3] + (target_pos.x * inverse.m[1][0] + target_pos.y * inverse.m[1][1] +
                           target_pos.z * inverse.m[1][2]),
        inverse.m[2][3] + (target_pos.x * inverse.m[2][0] + target_pos.y * inverse.m[2][1] +
                           target_pos.z * inverse.m[2][2]));
    grab->_d4 = *mParams.mAnimGrabPos_s;
}

void PullOut::sub_7100223B90() {
    auto* enemy = sead::DynamicCast<uking::act::GiantEnemy>(mActor);
    if (!enemy)
        return;
    auto* child = enemy->_1558 ? enemy->_1558->m7() : nullptr;
    auto* grab = sead::DynamicCast<ksys::act::Unk_7102359478>(child);
    if (!grab)
        return;
    grab->_98 = 0;
}

}  // namespace uking::action
