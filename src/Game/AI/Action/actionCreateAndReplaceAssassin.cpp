#include "Game/AI/Action/actionCreateAndReplaceAssassin.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

// Declaration-only helper; its original source namespace is unknown.
bool yigaWeaponStuff(sead::SafeString* actor_name, sead::SafeString* weapon_name, bool option,
                     const char* original_actor_name);

namespace uking::action {

CreateAndReplaceAssassin::CreateAndReplaceAssassin(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateAndReplaceAssassin::~CreateAndReplaceAssassin() = default;

bool CreateAndReplaceAssassin::init_(sead::Heap* heap) {
    sub_71000E2DC0();
    return true;
}

// NON_MATCHING: the early failure and final actor-pointer test use different branches.
bool CreateAndReplaceAssassin::sub_71000E2DC0() {
    sead::SafeString actor_name;
    sead::SafeString weapon_name;
    if (!yigaWeaponStuff(&actor_name, &weapon_name, true, mActor->getName().cstr()))
        return false;

    ksys::act::InstParamPack params;
    params->add(weapon_name, "EquipItem1");
    params->add(true, "IsNearCreate");
    params->addPosition(mActor->getMtx().getTranslation());
    params->add(6, "@I");
    if (ksys::gdt::getFlag_Electric_Relic_GetBack(false))
        params->add(sead::SafeString("HighRank"), "DropTable");

    _28 = ksys::act::ActorCreator::instance()->createActor(
        actor_name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &params, true,
        false);
    return _28 != nullptr;
}

void CreateAndReplaceAssassin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateAndReplaceAssassin::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateAndReplaceAssassin::loadParams_() {
    getDynamicParam(&mOffset_d, "Offset");
}

void CreateAndReplaceAssassin::calc_() {
    if (isFinished() || isFailed())
        return;
    if (!_28) {
        setFailed();
        return;
    }

    sead::Vector3f pos = *mOffset_d;
    pos.rotate(mActor->getMtx());
    pos += mActor->getMtx().getTranslation();
    sead::Matrix34f mtx = mActor->getMtx();
    mtx.setTranslation(pos);
    _28->setProperties(0, mtx, nullptr, nullptr, nullptr, false, 0, -1);
    _30 = true;
    mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
    setFinished();
}

bool CreateAndReplaceAssassin::hasPreDeleteCb() {
    return true;
}

void CreateAndReplaceAssassin::onPreDelete() {
    if (_30)
        return;
    if (_28)
        _28->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

}  // namespace uking::action
