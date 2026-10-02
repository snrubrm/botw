#include "Game/AI/Action/actionUnk_71023c8700.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

void Unk_71023c8700::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* child = sead::DynamicCast<ksys::act::Actor>(mOwner->getActor()->getConnectedCalcChild());
    if (child)
        sub_71005DC3F4(child);
}

void Unk_71023c8700::calc_() {
    if (!mOwner->getActor()->getASList()->x(0x47, nullptr, 0, 0,
                                            &ksys::as::ASList::Unk2::sub_71011637EC, true))
        return;

    auto* child = sead::DynamicCast<ksys::act::Actor>(mOwner->getActor()->getConnectedCalcChild());
    if (!child)
        return;

    sead::Vector3f target;
    target = *mTargetPos_d;
    auto* link = sub_71005D9050(mOwner->getActor());
    if (link && link->hasProc())
        target.y = sub_71005D93CC(mOwner->getActor()).y;

    target.x += f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1) *
                (mBlurMax_s->x * sead::GlobalRandom::instance()->getF32());
    target.y += f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1) *
                (mBlurMax_s->y * sead::GlobalRandom::instance()->getF32());
    target.z += f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1) *
                (mBlurMax_s->z * sead::GlobalRandom::instance()->getF32());
    sub_71005DC2B0(child, target, *mShootAng_s, *mShootSpd_s);
}

void Unk_71023c8700::loadParams_() {
    getStaticParam(&mShootSpd_s, "ShootSpd");
    getStaticParam(&mShootAng_s, "ShootAng");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mBlurMax_s, "BlurMax");
}
