#include "Game/Actor/Action/actionGanonThrowTornado.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

GanonThrowTornado::GanonThrowTornado(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonThrowTornado::~GanonThrowTornado() = default;

bool GanonThrowTornado::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonThrowTornado::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _68 = 0;
    sub_710073FA90(&_6c, mActor);
}

void GanonThrowTornado::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonThrowTornado::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mCreateHeight_s, "CreateHeight");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAppearOffset_s, "AppearOffset");
    getDynamicParam(&mThrowPartsName_d, "ThrowPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void GanonThrowTornado::calc_() {
    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        sub_710073FA94(&_6c, mActor);
        auto* actor = mActor;
        const sead::Vector3f position = actor->getMtx().getTranslation();
        const sead::Vector3f target = *mTargetPos_d;
        sead::Vector3f dir = target - position;
        dir.y = 0.0f;
        dir.normalize();
        sub_710074006C(&_6c, dir, sead::Vector3f::ey, true, 0.08f, 6.2831855f, 0.0f);
        sub_7100740F1C(_6c, mActor);
    } else if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    if (sub_71005DD780(mActor, 0x47, nullptr, 0, 0)) {
        sub_710017CFF8(_68);
        ++_68;
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: the original returns the address of the dummy link global directly (`ldr x0, [GOT]`; the getter is
// inlined there); ours calls getDummyBaseProcLink().
ksys::act::BaseProcLink& GanonThrowTornado::m32(int idx) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        return enemy->getActorPartsActor(mThrowPartsName_d);
    return ksys::act::getDummyBaseProcLink();
}

const sead::Vector3f* GanonThrowTornado::m33(int idx) {
    return mAppearOffset_s;
}

bool GanonThrowTornado::isFinished() const {
    return isFinishedAS(0, 0);
}

// NON_MATCHING: scheduling of the appear position transform and stack slots.
void GanonThrowTornado::sub_710017CFF8(int idx) {
    if (!sead::DynamicCast<act::Enemy>(mActor))
        return;
    auto& link = m32(idx);
    if (!link.hasProc())
        return;

    sead::Vector3f dir = *mTargetPos_d;
    auto* actor = mActor;
    sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f offset;
    offset.setRotated(actor->getMtx(), *m33(idx));
    pos += offset;

    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.setStartAndDisplacementScaled(pos, {0.0f, -1.0f, 0.0f}, 12.0f);
    sead::Vector3f hit_pos = pos;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        query.getHitPosition(&hit_pos);
    else
        hit_pos.y = *mCreateHeight_s;
    hit_pos.y += 4.0f;
    pos = hit_pos;

    dir -= pos;
    dir.normalize();
    sead::Matrix34f mtx;
    ksys::util::sub_71011F00EC(&mtx, dir, sead::Vector3f::ey, pos, false);
    dir *= *mInitVelocity_s;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.setProperties(mtx, &dir, nullptr, nullptr, false, 0, -1);
}

}  // namespace uking::action
