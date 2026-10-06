#include "Game/AI/Action/actionTreasureBoxBurnedOut.h"
#include "Game/AI/AI/aiTreasureBox.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Map/mapObject.h"

// 0x71002eba28 (declared only): the weapon type id of an actor profile (-1 if it is not a weapon).
s32 getWeaponTypeId(const sead::SafeString& profile);

// 0x710073ceb4 (declared only): requests the creation of the actor `name` dropped by a treasure chest (adds
// the save data index of `object`, the weapon modifier, "IsPlayerPut", "@RL" and "CheckInBgInit" params and calls
// WeaponBase::requestCreateWeaponActor).
void requestCreateActorForTreasureChestDrop(f32 scale, const char* name, const sead::Matrix34f* mtx,
                                            sead::Heap* heap, ksys::act::BaseProcHandle* handle,
                                            int a6, bool is_player_put,
                                            uking::act::WeaponModifierInfo* modifier,
                                            ksys::map::Object* object, int a10, u32 resource_lane);

namespace uking::action {

TreasureBoxBurnedOut::TreasureBoxBurnedOut(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TreasureBoxBurnedOut::~TreasureBoxBurnedOut() = default;

bool TreasureBoxBurnedOut::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TreasureBoxBurnedOut::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TreasureBoxBurnedOut::leave_() {
    _20.deleteProc();
}

void TreasureBoxBurnedOut::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
    getAITreeVariable(&mSharpWeaponAddParam_a, "SharpWeaponAddParam");
}

// NON_MATCHING: the original lays out the weapon branch first and folds the DynamicCast result and the
// `&variable->_8` null test into one csel; stack slots differ accordingly.
void TreasureBoxBurnedOut::spawnDropActor() {
    auto* actor = mActor;
    const char* profile;
    if (ksys::act::InfoData::instance()->getActorProfile(&profile, mDropActorName_a->cstr()) &&
        getWeaponTypeId(profile) != -1) {
        auto* variable = sead::DynamicCast<Unk_710242cd08>(
            *static_cast<Unk_71025afb58**>(mSharpWeaponAddParam_a));
        auto* modifier = variable ? &variable->_8 : nullptr;
        auto* object = actor->getMapObject();
        requestCreateActorForTreasureChestDrop(
            1.0f, mDropActorName_a->cstr(), &_58,
            ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_20, -1, false, modifier,
            object, 1, 1);
    } else {
        ksys::act::InstParamPack pack;
        pack->add(_58, "@M");
        if (auto* object = actor->getMapObject()) {
            ksys::act::ActorCreator::addAITreeParam(
                pack, u32(object->getRevivalGameDataFlagHash()),
                ksys::act::getStr_AtvKeyActorSaveDataIndex());
        }
        ksys::act::ActorCreator::instance()->requestCreateActor(
            mDropActorName_a->cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &_20, &pack, nullptr, 1);
    }
}

// NON_MATCHING: the address of _30 is computed before the releaseAndWakeProc call in the original.
void TreasureBoxBurnedOut::calc_() {
    if (_20.isAllocatedOrFailed()) {
        if (_20.isProcReady()) {
            auto* proc = _20.releaseAndWakeProc();
            _30.acquire(sead::DynamicCast<ksys::act::Actor>(proc), false);
        } else if (_20.hasProcCreationFailed()) {
            _20.deleteProcIfFailed();
            spawnDropActor();
        }
    } else {
        auto* actor = mActor;
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
        actor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

}  // namespace uking::action
