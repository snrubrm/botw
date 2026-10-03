#include "Game/AI/Action/actionDamagedTurn.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DamagedTurn::DamagedTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DamagedTurn::~DamagedTurn() = default;

bool DamagedTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DamagedTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr());
    if (!manager) {
        setFailed();
        return;
    }
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    manager->m29(&_48);
    _48 = -_48;
    sub_710073FA90(&_54, mActor);
}

void DamagedTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void DamagedTurn::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void DamagedTurn::calc_() {
    const sead::Vector3f up = getUpDir(mActor);
    sub_710073FA94(&_54, mActor);
    sub_710074006C(&_54, _48, up, true, *mRotRatio_s, *mRotSpeed_s, *mRotSpeed_s * 0.1f);
    sub_7100740F1C(_54, mActor);
    sub_7100738488(mActor, *mPosReduceRatio_s, -up);
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
