#include "Game/Actor/Behavior/behaviorSyncBodyASAndAnimalUnitAS.h"
#include <prim/seadFormatPrint.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::behavior {

SyncBodyASAndAnimalUnitAS::SyncBodyASAndAnimalUnitAS(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// NON_MATCHING: member destruction calls its own D1 instead of inlining the unregister body.
SyncBodyASAndAnimalUnitAS::~SyncBodyASAndAnimalUnitAS() = default;

// NON_MATCHING: the root callback's original own D1 remains a real out-of-line call.
SyncBodyASAndAnimalUnitAS::Callback::~Callback() = default;

void SyncBodyASAndAnimalUnitAS::Callback::call(ksys::act::Actor* actor) {
    sub_71006459BC(actor);
}

// NON_MATCHING: scheduling of the two parameter loads before the bank selection (the original
// computes the S1 address only at the call).
void SyncBodyASAndAnimalUnitAS::Callback::sub_71006459BC(ksys::act::Actor* actor) {
    auto* list = actor->getASList();
    if (!list)
        return;
    auto* rideable = actor->getRideableMaybe();
    if (!rideable)
        return;

    const int target_bone = *mTargetBone_s;
    const int seq_bank = *mSeqBank_s;
    int bank;
    if ((rideable->_18._9 != rideable->_18._b || rideable->_18._8 != rideable->_18._a) &&
        rideable->_18._c > 0) {
        bank = rideable->_18._9 ? s8(3 - rideable->_18._2e) : rideable->_18.sub_7100E76CEC();
    } else {
        bank = rideable->_18._9 ? rideable->_18._2e : rideable->_18.sub_7100E76CEC();
    }

    if (!list->x_7(0, bank, &ksys::as::ASList::Unk2::sub_710002E82C))
        return;
    list->x_1(target_bone, seq_bank);
    const auto& name = list->x_1(0, bank);
    if (!list->x_7(0, bank, &ksys::as::ASList::Unk2::sub_7101163940) && mBank == bank) {
        list->sub_710115F158(list, target_bone, 0, seq_bank, bank);
        return;
    }
    sub_7100645E24(list, name, target_bone, seq_bank);
    list->sub_710115F158(list, target_bone, 0, seq_bank, bank);
    mBank = bank;
}

// NON_MATCHING: argument setup order of the two merged startAnimationMaybe calls.
void SyncBodyASAndAnimalUnitAS::Callback::sub_7100645E24(ksys::as::ASList* list,
                                                          const sead::SafeString& name,
                                                          int target_bone, int seq_bank) {
    if (!mPreFix_s.isEmpty()) {
        sead::FixedSafeString<128> key;
        (sead::StringCutOffPrintFormatter(&key) << "%s%s" << mPreFix_s.cstr(), name) << sead::flush;
        if (list->sub_710115AA68(key)) {
            list->startAnimationMaybe(-1.0f, -1.0f, key, target_bone, seq_bank, true);
            return;
        }
    }
    list->startAnimationMaybe(-1.0f, -1.0f, name, target_bone, seq_bank, true);
}

void SyncBodyASAndAnimalUnitAS::enter() {
    _28.mBank = -1;
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (enemy && enemy->_1170)
        enemy->_1170->append(&_28);
}

void SyncBodyASAndAnimalUnitAS::leave() {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (enemy && enemy->_1170)
        enemy->_1170->erase(&_28);
}

bool SyncBodyASAndAnimalUnitAS::init_(sead::Heap* heap) {
    return true;
}

void SyncBodyASAndAnimalUnitAS::calc() {}

void SyncBodyASAndAnimalUnitAS::loadParams() {
    getStaticParam(&_28.mSeqBank_s, "SeqBank");
    getStaticParam(&_28.mTargetBone_s, "TargetBone");
    getStaticParam(&_28.mPreFix_s, "PreFix");
}

}  // namespace uking::behavior
