#include "Game/AI/Action/actionForkStalEnemyHeadShot.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

ForkStalEnemyHeadShot::ForkStalEnemyHeadShot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStalEnemyHeadShot::~ForkStalEnemyHeadShot() = default;

bool ForkStalEnemyHeadShot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalEnemyHeadShot::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    auto* damage = sub_710072BA90(mActor);
    if (!damage || damage->getField50() != 3 || !damage->checkDamageFlags(0))
        return;
    sub_7100164F64();
    auto* actor = mActor;
    if (!sub_71007271D4(actor))
        sub_7100728C40(actor, sead::Vector3f::zero);
}

void ForkStalEnemyHeadShot::leave_() {
    auto* actor = mActor;
    if (_60 > 0) {
        _60 = 0;
        sub_71007275C8(sub_7100724D7C(actor));
    }
    sub_7100738DC8(actor);
}

void ForkStalEnemyHeadShot::loadParams_() {
    getStaticParam(&mVisibleCount_s, "VisibleCount");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mUseAddVec_s, "UseAddVec");
    getStaticParam(&mHeadBoneKey_s, "HeadBoneKey");
    getStaticParam(&mAddVec_s, "AddVec");
    getStaticParam(&mRotVec_s, "RotVec");
}

void ForkStalEnemyHeadShot::calc_() {
    if (_60 > 0 && --_60 == 0)
        sub_71007275C8(sub_7100724D7C(mActor));
}

// NON_MATCHING: register allocation, spill slots and scheduling order only; all calls,
// values and control flow match.
void ForkStalEnemyHeadShot::sub_7100164F64() {
    const sead::Vector3f addvec = *mAddVec_s;
    auto* actor = mActor;
    const sead::Matrix34f& mtx0 = actor->getMtx();
    sead::Vector3f dir;
    dir.x = addvec.x * mtx0.m[0][0] + addvec.y * mtx0.m[0][1] + addvec.z * mtx0.m[0][2];
    dir.y = addvec.x * mtx0.m[1][0] + addvec.y * mtx0.m[1][1] + addvec.z * mtx0.m[1][2];
    dir.z = addvec.x * mtx0.m[2][0] + addvec.y * mtx0.m[2][1] + addvec.z * mtx0.m[2][2];
    dir.normalize();
    if (auto* dmg = sub_710072BA90(actor)) {
        if (dmg->getField50() == 3 && dmg->checkDamageFlags(0)) {
            auto* link = dmg->m37();
            if (link->hasProc()) {
                ksys::act::ActorConstDataAccess access;
                ksys::act::acquireActor(link, &access);
                sead::Vector3f vel = access.getVelocity();
                vel.normalize();
                if (*mUseAddVec_s)
                    vel += dir;
                dir = vel;
                dir.normalize();
            }
        }
    }
    dir *= *mSpeed_s;

    sead::Vector3f rotvec = *mRotVec_s;
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return;
    sead::Matrix34f mtx = actor->getMtx();
    if (auto* model = actor->getModel()) {
        const gsys::BoneAccessKey key = model->searchBone(mHeadBoneKey_s);
        if (key.isValid()) {
            sead::Matrix34f bone_mtx;
            model->getUnits()
                .unsafeAt(key.model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&bone_mtx, key.bone_index);
            mtx.m[0][3] = bone_mtx.m[0][3];
            mtx.m[1][3] = bone_mtx.m[1][3];
            mtx.m[2][3] = bone_mtx.m[2][3];
        }
    }
    rotvec.normalize();
    const sead::Vector3f kv = *mRotSpd_s * rotvec;
    sead::Vector3f ang;
    ang.setRotated(mtx, kv);
    auto& link = sub_7100725588(actor);
    ksys::act::ActorConstDataAccess access;
    if (link.hasProc()) {
        ksys::act::acquireActor(&link, &access);
        if (access.isStateSleep()) {
            access.setProperties(mtx, &dir, &ang, nullptr, true, 0, 0);
            sub_7100738CB0(actor, &link);
            sub_710072587C(actor);
        }
    }
    _60 = *mVisibleCount_s;
    sub_710072735C(actor, false, true);
    if (_60 <= 0)
        sub_71007275C8(sub_7100724D7C(actor));
}

}  // namespace uking::action
