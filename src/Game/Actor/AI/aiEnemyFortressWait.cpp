#include "Game/Actor/AI/aiEnemyFortressWait.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

EnemyFortressWait::EnemyFortressWait(const InitArg& arg) : EnemyWaitViewItem(arg), _70(arg, this) {}

EnemyFortressWait::~EnemyFortressWait() = default;

// NON_MATCHING: the original copies the translation to the stack word by word before the "@P" key setup.
bool EnemyFortressWait::init_(sead::Heap* heap) {
    if (!EnemyWaitViewItem::init_(heap) || !_70.sub_7100390930(heap))
        return false;

    if (!mFortressEatItem_m.isEmpty()) {
        ksys::act::InstParamPack pack;
        pack->addPosition(mActor->getMtx().getTranslation());
        sead::Vector3f rotation;
        mActor->getMtx().getRotation(rotation);
        pack->addRotation(rotation);
        pack->addNoDisplay();
        ksys::act::ActorCreator::instance()->requestCreateActor(
            mFortressEatItem_m.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_440, &pack, nullptr, 1);
    } else if (!mEatItem_s.isEmpty()) {
        const s32 fortress_eat_per = *mFortressEatPer_m;
        const s32 eat_per = *mEatPer_s;
        const s32 per = fortress_eat_per >= 0 ? fortress_eat_per : eat_per;
        if (per > s32(sead::GlobalRandom::instance()->getU32(100))) {
            ksys::act::InstParamPack pack;
            pack->addPosition(mActor->getMtx().getTranslation());
            sead::Vector3f rotation;
            mActor->getMtx().getRotation(rotation);
            pack->addRotation(rotation);
            pack->addNoDisplay();
            ksys::act::ActorCreator::instance()->requestCreateActor(
                mEatItem_s.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_440, &pack, nullptr, 1);
        }
    }
    _450 = false;
    _451 = false;
    return true;
}

inline void EnemyFortressWait::changeToEat() {
    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_440, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    changeChild("食事", &pack);
}

void EnemyFortressWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _70.sub_7100390A90();
    _70.getTargetLink() = *mTargetActor_d;
    if (_440.hasProcCreationFailed())
        _440.deleteProcIfFailed();

    if (!mFortressEatItem_m.isEmpty() && (_440.isAllocatedOrFailed() || _440.isProcReady())) {
        _70._3c8 |= 0x28;
        changeToEat();
        return;
    }

    if (!(_440.isAllocatedOrFailed() || _440.isProcReady()) || !sub_71003C3C68()) {
        _70._3c8 &= ~0x20;
        EnemyWaitViewItem::enter_(params);
        return;
    }
    _70._3c8 |= 0x28;
    changeToEat();
}

// NON_MATCHING: the compare chains on the sender results (the original tests 1 then 2 and 3 then 2 in source order; clang
// turns them into descending switches) and `&_70` is computed before the first branch in the original.
void EnemyFortressWait::calc_() {
    if (_440.hasProcCreationFailed())
        _440.deleteProcIfFailed();

    if (isCurrentChild("食事")) {
        _70._3c8 |= 0x20;
        auto* proc = mActor->getConnectedCalcChild();
        if (sead::DynamicCast<ksys::act::Actor>(proc)) {
            if (auto* mgr = sub_71005D9D68(mActor))
                mgr->sub_71002DC3A8(proc, 0x100);
        }
    } else {
        _70._3c8 &= ~0x20;
    }
    _70.sub_7100390ABC();
    _70.getTargetLink() = *mTargetActor_d;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        if (child->isChangeable()) {
            switch (_70.sub_7100391230()) {
            case 3:
                if (!isCurrentChild("食事") && sub_71003C3C68() &&
                    (_440.isAllocatedOrFailed() || _440.isProcReady())) {
                    _70._3c8 |= 8;
                    changeToEat();
                    return;
                }
                break;
            case 2:
                if (!isCurrentChild("食事")) {
                    if (!sub_71003C3C68() || !(_440.isAllocatedOrFailed() || _440.isProcReady())) {
                        sub_71003C3A2C(false);
                        return;
                    }
                    _70._3c8 |= 8;
                    changeToEat();
                }
                break;
            default:
                if (_440.isProcReady())
                    _440.deleteProc();
                else if (_440.hasProcCreationFailed())
                    _440.deleteProcIfFailed();
                break;
            }
        }
        if (!isCurrentChild("食事") && !(_70._3c8 & 1))
            EnemyWaitViewItem::calc_();
    } else {
        _70._3c8 = _451 ? (_70._3c8 | 8) : (_70._3c8 & ~8);
        const s32 result = _70.sub_7100390D0C();
        if (result == 1) {
            if (_440.isProcReady())
                _440.deleteProc();
            else if (_440.hasProcCreationFailed())
                _440.deleteProcIfFailed();
            return;
        }
        if (result == 2 || isCurrentChild("食事")) {
            sub_71003C3A2C(false);
        } else if (!isCurrentChild("食事") && !(_70._3c8 & 1)) {
            EnemyWaitViewItem::calc_();
        }
    }
}

void EnemyFortressWait::leave_() {
    if (_440.isProcReady())
        _440.deleteProc();
    else if (_440.hasProcCreationFailed())
        _440.deleteProcIfFailed();
    _70.sub_7100392044();
    EnemyWaitViewItem::leave_();
}

void EnemyFortressWait::loadParams_() {
    EnemyWaitViewItem::loadParams_();
    _70.sub_7100392230();
    getStaticParam(&mEatPer_s, "EatPer");
    getStaticParam(&mEatItem_s, "EatItem");
    getMapUnitParam(&mFortressEatPer_m, "FortressEatPer");
    getMapUnitParam(&mFortressEatItem_m, "FortressEatItem");
}

bool EnemyFortressWait::handleMessage_(const ksys::Message* message) {
    return _70.sub_710039235C(*message);
}

bool EnemyFortressWait::isChangeable() const {
    return getCurrentChild()->isChangeable() || (_70._3c8 & 1);
}

void EnemyFortressWait::m34() {
    _450 = true;
    _451 = false;
    _70._3c8 &= ~8;
}

void EnemyFortressWait::m35() {
    _451 = _450;
    _70._3c8 = _450 ? (_70._3c8 | 8) : (_70._3c8 & ~8);
}

void EnemyFortressWait::m36() {
    _451 = _450;
    _70._3c8 = _450 ? (_70._3c8 | 8) : (_70._3c8 & ~8);
}

}  // namespace uking::ai
