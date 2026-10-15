#include "Game/Actor/Action/actionLyzalfosFlame.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/aiUnk_7100EDD26C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

LyzalfosFlame::LyzalfosFlame(const InitArg& arg) : ChemicalAttack(arg) {}

LyzalfosFlame::~LyzalfosFlame() = default;

bool LyzalfosFlame::init_(sead::Heap* heap) {
    if (!ChemicalAttack::init_(heap))
        return false;
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        bullet->_cf4 |= 0x200;
    return true;
}

void LyzalfosFlame::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
}

void LyzalfosFlame::leave_() {
    xlink::fade(_1c8, -1);
    ChemicalAttack::leave_();
}

void LyzalfosFlame::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mParams.mLengthFrame_s, "LengthFrame");
    getStaticParam(&mParams.mAtResetTime_s, "AtResetTime");
    getStaticParam(&mParams.mAtChaseFrame_s, "AtChaseFrame");
    getStaticParam(&mParams.mBindGrabNodeIdx_s, "BindGrabNodeIdx");
    getStaticParam(&mParams.mChaseMax_s, "ChaseMax");
    getStaticParam(&mParams.mChaseRate_s, "ChaseRate");
    getStaticParam(&mParams.mOffsetRot_s, "OffsetRot");
}

void LyzalfosFlame::sub_71001E271C(sead::Matrix34f* out) {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(
        mActor->getCreateArgBaseProcLink().getProc(nullptr, nullptr));
    if (!actor)
        return;
    const auto& bone_name = sub_7100EDD258(actor, 5);
    if (auto* model = actor->getModel()) {
        const auto key = model->searchBone(bone_name.getStringTop());
        if (key.isValid()) {
            model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                out, key.bone_index);
            return;
        }
    }
    *out = actor->getMtx();
}

void LyzalfosFlame::calc_() {
    ChemicalAttack::calc_();
}

bool LyzalfosFlame::m33() {
    return false;
}

}  // namespace uking::action
