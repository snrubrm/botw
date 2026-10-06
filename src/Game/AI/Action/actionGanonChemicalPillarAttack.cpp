#include "Game/AI/Action/actionGanonChemicalPillarAttack.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

GanonChemicalPillarAttack::GanonChemicalPillarAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GanonChemicalPillarAttack::~GanonChemicalPillarAttack() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (mPillarNum_s) {
            for (s32 i = 0; i <= *mPillarNum_s; ++i) {
                const sead::FormatFixedSafeString<64> name("IronPile%d", i);
                if (enemy->getActorPartsActor(name).hasProc()) {
                    ksys::act::ActorConstDataAccess accessor;
                    ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
                enemy->sub_7100D3CFEC(name);
            }
        }
    }
}

void GanonChemicalPillarAttack::sub_7100178DC4(s32 index, ksys::act::ActorConstDataAccess* accessor) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const sead::FormatFixedSafeString<64> name("IronPile%d", index);
        if (enemy->getActorPartsActor(name).hasProc())
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), accessor);
    }
}

bool GanonChemicalPillarAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original keeps `_b8` / `_b9` as two byte stores (no strh merge) and schedules the stores of the
// final block differently (_c8 load before the third word of *mTargetPos_d, `_cc` store last).
void GanonChemicalPillarAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _e4 = ksys::Timer(0.0f, 0.0f);
    _b9 = true;
    _b8 = true;
    auto* actor = mActor;
    _ba = false;
    _bc = 0;
    _c8 = -1;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        for (s32 i = 0; i <= *mPillarNum_s; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.sub_7100D13BB8()) {
                    _c8 = i;
                } else {
                    enemy->sendMessage(*accessor.getMessageTransceiverId(),
                                       ksys::MessageType(0x8000004), nullptr, true);
                }
            }
        }
        if (!mCreatePileASName_s.isEmpty())
            playAS(mCreatePileASName_s.cstr(), false, 0, 0, -1.0f);
        else if (!mWaitASName_s.isEmpty())
            playAS(mWaitASName_s.cstr(), false, 0, 0, -1.0f);
        _d8 = *mTargetPos_d;
        _c0 = 0;
        _d0 = 0;
        _d4 = 120.0f;
        _c4 = _c8 == -1 ? *mPillarNum_s : *mPillarNum_s + 1;
        _cc = -1;
        mFlags.set(Flag::Changeable);
    }
}

void GanonChemicalPillarAttack::leave_() {
    sub_71005D74E8(mActor);
}

void GanonChemicalPillarAttack::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMinPower_s, "AtMinPower");
    getStaticParam(&mAttackPowerForPlayer_s, "AttackPowerForPlayer");
    getStaticParam(&mPillarNum_s, "PillarNum");
    getStaticParam(&mPillarInterval_s, "PillarInterval");
    getStaticParam(&mPillarOffset_s, "PillarOffset");
    getStaticParam(&mAppearPosDist_s, "AppearPosDist");
    getStaticParam(&mAppearPosHeight_s, "AppearPosHeight");
    getStaticParam(&mIgnitionInterval_s, "IgnitionInterval");
    getStaticParam(&mPileScale_s, "PileScale");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mWaitASName_s, "WaitASName");
    getStaticParam(&mCreatePileASName_s, "CreatePileASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonChemicalPillarAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
