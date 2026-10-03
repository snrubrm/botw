#include "Game/AI/Action/actionGanonThrowTornado.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
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

// NON_MATCHING: scheduling of the direction math: the original stores dir.y = 0 right after loading the target z and
// only stores dir.x / dir.z after the sqrt; ours stores dir.x first.
void GanonThrowTornado::calc_() {
    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        sub_710073FA94(&_6c, mActor);
        auto* actor = mActor;
        const f32 pos_x = actor->getMtx()(0, 3);
        const f32 pos_z = actor->getMtx()(2, 3);
        sead::Vector3f dir;
        dir.x = mTargetPos_d->x - pos_x;
        dir.y = 0.0f;
        dir.z = mTargetPos_d->z - pos_z;
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

}  // namespace uking::action
