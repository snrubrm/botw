#include "Game/Actor/AI/aiSiteBossSpearThrow.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <limits>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SiteBossSpearThrow::SiteBossSpearThrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearThrow::~SiteBossSpearThrow() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC("Spear");
}

bool SiteBossSpearThrow::init_(sead::Heap* heap) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("Spear").hasProc())
            return true;

        enemy->sub_7100D3CED8("Spear", heap);

        s32 num_dead_blights = getNumberOfDeadBlights();
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            const s32 kind = boss->_1534 & ~3;
            if (kind == 4)
                num_dead_blights = 3;
            else if (kind == 8)
                num_dead_blights = 4;
        }

        const s32 add_power = *mAddAttackPower_s * num_dead_blights;
        const s32 attack_power = *mAttackPower_s + add_power;
        const s32 min_damage = *mAtMnDamage_s + add_power;
        ksys::act::InstParamPack pack;
        pack->add(attack_power, "AttackPower");
        pack->add(1.0f, "ScaleTime");
        ksys::act::ActorCreator::addScale(pack, 1.0f);
        pack->add(min_damage, "AtMinDamage");
        auto* spear = ksys::act::ActorCreator::instance()->createActor(
            mThrowActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &pack, true, false);
        if (spear) {
            spear->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
            enemy->sub_7100D3D108("Spear", spear);
            spear->clearFadeInCreate();
        }
    }
    return true;
}

// NON_MATCHING: SiteBoss flag bytes are addressed through separate base registers.
void SiteBossSpearThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("Spear").hasProc()) {
            sub_7100591C78(false);
        } else {
            if (!_68.isAllocatedOrFailed()) {
                sub_71005922F4();
            } else if (_68.hasProcCreationFailed()) {
                _68.deleteProcIfFailed();
                sub_71005922F4();
            }
            changeChild("生成待ち");
            _78.reset(30.0f);
        }
    }
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->_2378) {
            boss->_237b = boss->_237a;
            boss->_2378 = 1;
        }
        boss->_237a |= 1;
    }
}

void SiteBossSpearThrow::sub_7100591C78(bool created) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    if (created)
        params.addPointer(&_68, "IgniteBaseProcHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    else
        params.addPointer(nullptr, "IgniteBaseProcHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    changeChild("投げる", &params);
}

void SiteBossSpearThrow::sub_71005922F4() {
    s32 num_dead_blights = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            num_dead_blights = 3;
        else if (kind == 8)
            num_dead_blights = 4;
    }
    const s32 add_power = *mAddAttackPower_s * num_dead_blights;
    const s32 attack_power = *mAttackPower_s + add_power;
    const s32 min_damage = *mAtMnDamage_s + add_power;
    ksys::act::InstParamPack pack;
    pack->add(attack_power, "AttackPower");
    pack->add(1.0f, "ScaleTime");
    ksys::act::ActorCreator::addScale(pack, 1.0f);
    pack->add(min_damage, "AtMinDamage");
    ksys::act::ActorCreator::instance()->requestCreateActor(
        mThrowActorName_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        &_68, &pack, nullptr, 1);
}

void SiteBossSpearThrow::calc_() {
    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }
    const sead::Vector3f target = *mTargetPos_d;
    child->setDynamicParam(target, "TargetPos");
    if (isCurrentChild("生成待ち")) {
        _78.update();
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy->getActorPartsActor("Spear").hasProc()) {
            sub_7100591C78(false);
            return;
        }
        if (!_68.isAllocatedOrFailed()) {
            sub_71005922F4();
        } else if (_68.hasProcCreationFailed()) {
            _68.deleteProcIfFailed();
            sub_71005922F4();
        }
        if (_68.isAllocatedOrFailed() && _68.isProcReady()) {
            if (auto* spear = sead::DynamicCast<ksys::act::Actor>(_68.getProc())) {
                spear->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
                spear->clearFadeInCreate();
                enemy->sub_7100D3D108("Spear", spear);
                sub_7100591C78(true);
                return;
            }
        }
        if (_78.value <= std::numeric_limits<f32>::epsilon()) {
            setFailed();
            return;
        }
    }
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed())
            setFailed();
        else
            setFinished();
    }
}

// NON_MATCHING: the original addresses SiteBoss _2378-_237b through one base register (as if they
// were members of a struct at SiteBoss+0x2378; same as SiteBossSpearAttackBase::leave_)
void SiteBossSpearThrow::leave_() {
    if (_68.isAllocatedOrFailed())
        _68.deleteProc();

    if (isActorGoingBackToRootAi()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor("Spear"), &accessor);
            if (accessor.hasProc() && accessor.isStateCalc())
                accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }

    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_2378) {
            boss->_237a = boss->_237b;
            boss->_2378 = 0;
        }
    }
}

void SiteBossSpearThrow::loadParams_() {
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAtMnDamage_s, "AtMnDamage");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool SiteBossSpearThrow::isFailed() const {
    if (getCurrentChild())
        return getCurrentChild()->isFailed();
    return false;
}

bool SiteBossSpearThrow::isFinished() const {
    if (getCurrentChild())
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
