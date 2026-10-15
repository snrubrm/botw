#include "Game/Actor/Action/actionLastBossChemicalPillarAttack.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

bool sub_71006DEBEC(const ksys::act::ActorLinkConstDataAccess& accessor, int mask);

namespace uking::action {

LastBossChemicalPillarAttack::LastBossChemicalPillarAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

LastBossChemicalPillarAttack::~LastBossChemicalPillarAttack() = default;

bool LastBossChemicalPillarAttack::sub_71001CF880() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (u32 i = 0; i < 16; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.isStateCalc() && !accessor.sub_7100D13BB8())
                    return false;
            }
        }
    }
    return true;
}

void LastBossChemicalPillarAttack::sub_71001CFA48(s32 index, ksys::act::ActorLinkConstDataAccess* accessor) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        const sead::FormatFixedSafeString<64> name("IronPile%d", index);
        if (enemy->getActorPartsActor(name).hasProc())
            ksys::act::acquireActor(&enemy->getActorPartsActor(name), accessor);
    }
}

bool LastBossChemicalPillarAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossChemicalPillarAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    const f32 interval = *mParams.mCreateInterval_s;
    _50 = ksys::Timer(interval, interval);
    playAS("Chemical_Attack", true, 0, 0, -1.0f);
    _48 = -1;
    _4c = false;
    _4e = false;
    _5c.rate = -1.0f;
    _5c.value = 300.0f;
    _5c.previous_value = 300.0f;
}

void LastBossChemicalPillarAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossChemicalPillarAttack::loadParams_() {
    getStaticParam(&mParams.mPillarNum_s, "PillarNum");
    getStaticParam(&mParams.mAttackEndWait_s, "AttackEndWait");
    getStaticParam(&mParams.mCreateInterval_s, "CreateInterval");
    getStaticParam(&mParams.mPillarYOffset_s, "PillarYOffset");
}

// NON_MATCHING: normalized up-vector stores and fallback loads are reordered.
void LastBossChemicalPillarAttack::calc_() {
    if (isFinishedAS(0, 0)) {
        if (_4e) {
            setFinished();
        } else if (_4c) {
            _4c = false;
            playAS("Chemical_Attack", false, 0, 0, -1.0f);
        }
        return;
    }
    if (auto* manager = sub_710072BA90(mActor)) {
        if (manager->getField54() == 12) {
            _4c = true;
            xlinkSearchAndEmit(mActor, "ShieldDamage", 2, nullptr);
            playAS("GuardShock", false, 0, 0, -1.0f);
        }
    }
    _50.update();
    if (_50.value <= sead::Mathf::epsilon()) {
        _5c.update();
        if (u32(_40) < 16 && !(_5c.value <= sead::Mathf::epsilon())) {
            const s32 index = m33();
            if (u32(index) < 16) {
                ksys::act::ActorLinkConstDataAccess accessor;
                sub_71001CFA48(index, &accessor);
                mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                   ksys::MessageType(0x800005b), nullptr, true);
            }
            ++_40;
            const f32 interval = *mParams.mCreateInterval_s;
            _50 = ksys::Timer(interval, interval);
            _5c = ksys::Timer(120.0f, 120.0f);
        } else if (sub_71001CF880() || _5c.value <= sead::Mathf::epsilon()) {
            if (!_4e && !_4c) {
                _4e = true;
                playAS("Chemical_Attack_End", true, 0, 0, -1.0f);
            }
            return;
        }
    }
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        if (sub_71006DEBEC(player, 24)) {
            if (!_4c) {
                _4e = true;
                playAS("Chemical_Attack_End", true, 0, 0, -1.0f);
            }
            _40 = 16;
            return;
        }
    }
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->sub_7100F5F6FC(sead::Vector3f::zero);
    const auto gravity = controller->get70();
    const f32 length = gravity.length();
    sead::Vector3f up = -gravity;
    if (length > 0.0f)
        up *= 1.0f / length;
    if (length < sead::Mathf::epsilon())
        up = sead::Vector3f::ey;
    sub_710073FA94(&_68, mActor);
    sead::Vector3f to_player = getPlayerPosition();
    to_player -= mActor->getMtx().getTranslation();
    to_player.normalize();
    ksys::util::sub_71011EFA00(&to_player, to_player, up);
    sub_710074006C(&_68, to_player, up, true, 0.16f, sead::Mathf::pi2(), 0.0f);
    sub_7100740E04(_68, controller);
}

void LastBossChemicalPillarAttack::m32() {}

s32 LastBossChemicalPillarAttack::m33() {
    const s32 start = _40;
    if (_48 != -1)
        return start - (start <= _48);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        for (u32 i = start; i < 16; ++i) {
            const sead::FormatFixedSafeString<64> name("IronPile%d", i);
            if (enemy->getActorPartsActor(name).hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&enemy->getActorPartsActor(name), &accessor);
                if (accessor.sub_7100D13BB8()) {
                    const auto position = accessor.getActorMtx().getTranslation();
                    if ((position - mActor->getMtx().getTranslation()).squaredLength() <= 16.0f) {
                        _48 = i;
                        return i;
                    }
                }
            }
        }
    }
    return start;
}

bool LastBossChemicalPillarAttack::isChangeable() const {
    auto* damage_mgr = sub_710072BA90(mActor);
    if (damage_mgr && (damage_mgr->getField54() == 9 || damage_mgr->getField54() == 10 ||
                       damage_mgr->getField54() == 22)) {
        return true;
    }
    return false;
}

}  // namespace uking::action
