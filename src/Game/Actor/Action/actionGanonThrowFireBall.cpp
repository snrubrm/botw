#include "Game/Actor/Action/actionGanonThrowFireBall.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/MathUtil.h"
#include "gsys/gsysModel.h"
#include "gsys/gsysModelUnit.h"

namespace uking::action {

GanonThrowFireBall::GanonThrowFireBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonThrowFireBall::~GanonThrowFireBall() = default;

bool GanonThrowFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonThrowFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    sub_710017BBA0(0);
}

void GanonThrowFireBall::leave_() {
    ksys::act::ai::Action::leave_();
}

const sead::SafeString& GanonThrowFireBall::m32(int idx) {
    return mThrowPartsName_d;
}

void GanonThrowFireBall::m33(sead::Vector3f* out, int idx) {
    out->x = 0.0f;
    out->y = *mBallAppearOffset_s;
    out->z = 0.0f;
}

void GanonThrowFireBall::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mBallAppearOffset_s, "BallAppearOffset");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mThrowPartsName_d, "ThrowPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void GanonThrowFireBall::calc_() {
    if (sub_71005DD780(mActor, 0x47, nullptr, 0, 0))
        sub_710017BE48(0);
    if (isFinishedAS(0, 0))
        setFinished();
}

bool GanonThrowFireBall::isFinished() const {
    return isFinishedAS(0, 0);
}

// NON_MATCHING: the original loads the m33 offset right after the call (ours after the parts actor checks).
void GanonThrowFireBall::sub_710017BBA0(int idx) {
    sead::Matrix34f rot_mtx;
    ksys::util::sub_71011F0260(&rot_mtx, sead::Vector3f::ez, sead::Vector3f::ey, sead::Vector3f::zero,
                               false);

    auto* model = mActor->getModel();
    const auto key = model->searchBone("Weapon_L");
    sead::Matrix34f bone_mtx;
    mActor->getModel()->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
        &bone_mtx, key.bone_index);
    const sead::Vector3f bone_pos = bone_mtx.getTranslation();
    sead::Vector3f offset;
    m33(&offset, idx);
    const f32 scale_value = *mFireBallScale_s;
    const sead::Vector3f scale{scale_value, scale_value, scale_value};

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !enemy->getActorPartsActor(m32(idx)).hasProc())
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    const sead::Vector3f pos = bone_pos + offset;
    ksys::act::acquireActor(&enemy->getActorPartsActor(m32(idx)), &accessor);
    accessor.setThisActorAsChild(mActor, false);
    sead::Matrix34f mtx = enemy->getMtx();
    mtx.setTranslation(pos);
    accessor.setProperties(mtx, nullptr, nullptr, &scale, false, 3, -1);
}

void GanonThrowFireBall::sub_710017BE48(int idx) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;
    auto& link = enemy->getActorPartsActor(m32(idx));
    if (!link.hasProc())
        return;
    _68 = *mTargetPos_d;
    _80 = *mTargetActor_d;
    _90 = *mInitVelocity_s;
    _98.clear();
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800003a), &_68,
                        true);
}

}  // namespace uking::action
