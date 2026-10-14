#include "Game/Actor/Action/actionForkStalPartBlownOff.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>

namespace uking::action {

ForkStalPartBlownOff::ForkStalPartBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkStalPartBlownOff::~ForkStalPartBlownOff() = default;

bool ForkStalPartBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalPartBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const auto* life = actor->getLife();
    if ((life ? f32(*life) : 1.0f) / f32(actor->getMaxLife()) <= *mLifeRate_s)
        sub_7100166114();
    mFlags.set(Flag::Changeable);
}

void ForkStalPartBlownOff::leave_() {
    auto* actor = mActor;
    if (_50 > 0) {
        _50 = 0;
        sub_71007275C8(sub_7100724D7C(actor));
    }
    sub_7100738DC8(actor);
}

void ForkStalPartBlownOff::loadParams_() {
    getStaticParam(&mShootParts_s, "ShootParts");
    getStaticParam(&mShootSpeed_s, "ShootSpeed");
    getStaticParam(&mLifeRate_s, "LifeRate");
    getStaticParam(&mBaseNodeName_s, "BaseNodeName");
    getStaticParam(&mShootDir_s, "ShootDir");
}

// Shoots the Stal part ShootParts from the BaseNodeName bone along ShootDir (in actor space) at ShootSpeed.
void ForkStalPartBlownOff::sub_7100166114() {
    auto* actor = mActor;
    if (!sub_7100724D7C(actor))
        return;

    sead::Matrix34f mtx = actor->getMtx();
    if (auto* model = actor->getModel()) {
        const auto key = model->searchBone(mBaseNodeName_s);
        if (key.isValid()) {
            sead::Matrix34f bone_mtx;
            model->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(&bone_mtx,
                                                                                    key.bone_index);
            mtx.setTranslation(bone_mtx.getTranslation());
        }
    }
    sead::Vector3f velocity = *mShootDir_s;
    velocity.setRotated(mtx, velocity);
    velocity.normalize();
    velocity *= *mShootSpeed_s;

    auto& link = sub_7100724F08(actor, *mShootParts_s);
    ksys::act::ActorLinkConstDataAccess accessor;
    if (link.hasProc()) {
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateSleep()) {
            const auto* life = actor->getLife();
            accessor.setProperties(mtx, &velocity, nullptr, nullptr, true, 0, life ? *life : 1);
            sub_7100738CB0(actor, &link);
            sub_71007250E4(actor, *mShootParts_s);
            if (sub_71007271D4(actor))
                *actor->getLife() = 1;
        }
    }
    sub_710072735C(actor, false, true);
    _50 = 2;
}

void ForkStalPartBlownOff::calc_() {
    if (_50 > 0 && --_50 == 0)
        sub_71007275C8(sub_7100724D7C(mActor));
}

}  // namespace uking::action
