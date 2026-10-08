#include "Game/AI/aiUnk_710073EBD4.h"
#include <gsys/gsysModel.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"

ksys::act::BaseProcLink& sub_710073E9A8(ksys::act::Actor* actor, const sead::SafeString& name) {
    if (sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return static_cast<uking::act::Enemy*>(actor)->_1128.getActorPartsActor(name);
    return ksys::act::getDummyBaseProcLink();
}

void sub_71006DED9C(const ksys::act::ActorConstDataAccess& accessor, ksys::act::BaseProc* proc);

void sub_710073EA44(ksys::act::Actor* actor, const sead::SafeString& name, const sead::Matrix34f& mtx,
                    const sead::Vector3f* vel, const sead::Vector3f* ang_vel, bool a6) {
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return;
    auto* enemy = static_cast<uking::act::Enemy*>(actor);
    auto& link = enemy->getActorPartsActor(name);
    if (!link.hasProc())
        return;
    ksys::act::ActorConstDataAccess accessor;
    acquireActor(&link, &accessor);
    accessor.setProperties(mtx, vel, ang_vel, nullptr, true, 2, -1);
    {
        ksys::act::ActorConstDataAccess accessor2;
        acquireActor(&link, &accessor2);
        sub_71006DED9C(accessor2, enemy);
        if (a6)
            enemy->sub_7100D3D2B4(name);
    }
}

Unk_710073ebd4::Unk_710073ebd4(ksys::act::Actor* actor)
    : mActor(sead::DynamicCast<uking::act::Enemy>(actor)) {}

Unk_710073ebd4::~Unk_710073ebd4() {}

bool Unk_710073ebd4::sub_710073ECC0() {
    auto* model = mActor->getModel();
    if (!mBaseNode_s.isEmpty() && model)
        mBone = model->searchBone(mBaseNode_s);
    else
        mBone.reset();
    return true;
}

void Unk_710073ebd4::sub_710073ED20(const ksys::act::ai::ActionBase* action) {
    action->getStaticParam(&mSeqBank_s, "SeqBank");
    action->getStaticParam(&mTargetBone_s, "TargetBone");
    action->getStaticParam(&mPartsKey_s, "PartsKey");
    action->getStaticParam(&mShootSpeed_s, "ShootSpeed");
    action->getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    action->getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    action->getStaticParam(&mBaseNode_s, "BaseNode");
    action->getStaticParam(&mShootOffset_s, "ShootOffset");
    action->getStaticParam(&mShootRotate_s, "ShootRotate");
    action->getStaticParam(&mShootRotSpeed_s, "ShootRotSpeed");
    action->getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    action->getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    action->getDynamicParam(&mDynTargetPos_d, "TargetPos");
}

void Unk_710073ebd4::sub_710073EEE4(const ksys::act::ai::ActionBase* action) {
    action->getDynamicParam(&mDynTargetVel_d, "TargetVel");
}

bool Unk_710073ebd4::sub_710073EF50(const ksys::act::ai::ActionBase*) {
    mWork = mPartsKey_s;
    auto* actor = mActor;
    if (sead::IsDerivedFrom<uking::act::Enemy>(actor)) {
        auto* enemy = static_cast<uking::act::Enemy*>(actor);
        auto& link = enemy->getActorPartsActor(mWork);
        if (link.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&link, &accessor);
            return accessor.isStateSleep();
        }
    }
    return false;
}

bool Unk_710073ebd4::sub_710073FA54() {
    if (auto* as_list = mActor->getASList())
        return as_list->x(0x47, nullptr, *mTargetBone_s, *mSeqBank_s,
                          &ksys::as::ASList::Unk2::sub_71011637EC, true);
    return false;
}
