#include "Game/AI/AI/aiHorseRiddenByNPC.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/Timer.h"

// Declaration only; the original source namespace and raw selector type are inferred.
bool sub_7100E804E4(sead::Vector3f* out, ksys::act::Actor* actor,
                    ksys::act::Unk_7100d78e50* entry, s32 kind);

namespace uking::ai {

HorseRiddenByNPC::HorseRiddenByNPC(const InitArg& arg) : HorseRiddenByNPCBase(arg) {}

HorseRiddenByNPC::~HorseRiddenByNPC() = default;

bool HorseRiddenByNPC::init_(sead::Heap* heap) {
    return HorseRiddenByNPCBase::init_(heap);
}

void HorseRiddenByNPC::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRiddenByNPCBase::enter_(params);
}

// NON_MATCHING: low-byte flag test uses a dynamic SEAD_ENUM bit index in the original.
void HorseRiddenByNPC::calc_() {
    HorseRiddenByNPCBase::calc_();
    if (auto* damage = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr())) {
        if (damage->_216.isOn(2)) {
            if (auto* rideable = mActor->m132()) {
                if (*(rideable->_18._b == 0 ? &rideable->_18._9 : &rideable->_18._b)) {
                    mActor->getASList()->startAnimationMaybe(-1.0f, -1.0f,
                                                           uking::act::sUnk_7102603200, 1, 0, true);
                } else {
                    rideable->_18.sub_7100E76E74(uking::act::sUnk_7102603200, false);
                }
            }
        }
    }
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        if (mActor->getASList()->x_4(1, 0))
            rideable->_18.sub_7100E78E00();
        if (auto* horse = sead::DynamicCast<uking::act::HorseBase>(mActor)) {
            bool on;
            if (rideable->_a0._88 & 4) {
                _68 = 120.0f;
                on = true;
            } else {
                ksys::Timer::update(&_68, -1.0f);
                on = _68 > 0.0f;
            }
            horse->sub_7100E6BEC0(on);
        }
    }
}

bool HorseRiddenByNPC::m35(ksys::act::Unk_7100d78e50* entry, s32 idx) {
    sead::Vector3f position;
    return !sub_7100E804E4(&position, mActor, entry, idx);
}

void HorseRiddenByNPC::leave_() {
    HorseRiddenByNPCBase::leave_();
}

void HorseRiddenByNPC::loadParams_() {
    HorseRiddenByNPCBase::loadParams_();
    getStaticParam(&mNavMeshCharacterScaleAtPrecise_s, "NavMeshCharacterScaleAtPrecise");
}

}  // namespace uking::ai
