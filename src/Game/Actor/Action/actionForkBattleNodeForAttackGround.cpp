#include "Game/Actor/Action/actionForkBattleNodeForAttackGround.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkBattleNodeForAttackGround::ForkBattleNodeForAttackGround(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBattleNodeForAttackGround::~ForkBattleNodeForAttackGround() = default;

bool ForkBattleNodeForAttackGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBattleNodeForAttackGround::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkBattleNodeForAttackGround::leave_() {
    if (auto* spine = mActor->sub_71011D8A10())
        spine->_d4 &= ~0x40;
}

void ForkBattleNodeForAttackGround::loadParams_() {
    getStaticParam(&mIsOffsetFromBaseBone_s, "IsOffsetFromBaseBone");
    getStaticParam(&mAttackPosOffset_s, "AttackPosOffset");
}

// NON_MATCHING: choosing the matrix folds the native bone/actor transform branches together.
void ForkBattleNodeForAttackGround::calc_() {
    auto* spine = mActor->sub_71011D8A10();
    if (!spine)
        return;
    if (sub_71005DD734(mActor, 0x2c, nullptr, 0, 0))
        spine->_d4 &= ~0x40u;
    if (sub_71005DD5B0(mActor, 0x2c, nullptr, 0, 0))
        spine->_d4 = (spine->_d4 & ~0xc00u) | 0x40u;
    if (!sub_71005DD798(mActor, 0x2c, nullptr, 0, 0))
        return;
    sead::Matrix34f bone;
    spine->sub_7100D89260(&bone);
    const sead::Vector3f origin = bone.getTranslation();
    sead::Vector3f offset;
    spine->sub_7100D892C4(&offset);
    const sead::Vector3f position =
        (*mIsOffsetFromBaseBone_s ? bone : mActor->getMtx()) * *mAttackPosOffset_s;
    const sead::Vector3f from(position.x, position.y + 5.0f, position.z);
    const sead::Vector3f to(position.x, position.y - 5.0f, position.z);
    sead::Vector3f ground;
    if (!sub_710072E928(from, to, &ground, nullptr, nullptr, 0.0f))
        ground = to;
    const sead::Vector3f delta = ground - origin;
    const f32 height = delta.y + offset.y;
    const auto& target = sub_71005D9330(mActor);
    const sead::Vector3f horizontal(target.x - origin.x, 0.0f, target.z - origin.z);
    const f32 distance = horizontal.length();
    sead::Vector3f attack = target;
    attack.y = origin.y + height * distance /
                              sead::Mathf::sqrt(delta.x * delta.x + delta.z * delta.z);
    sub_71005DB068(mActor, attack);
}

}  // namespace uking::action
