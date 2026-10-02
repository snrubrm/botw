#include "Game/AI/AI/aiPriestBossIronBall.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

static const sead::SafeString sUnk_7102413eb8 = "Body";

namespace {
// Rigid body names in the "Body" set; TU-local (the original accesses the enum's text storage
// directly, not through the GOT). Placeholder name = its text_ function (0x710051f5fc).
SEAD_ENUM(Unk_710051f5fc, HandR, ArmR, UpperArmR, HandL, ArmL, UpperArmL)
}  // namespace

static s32 sUnk_7102413ff8 = 90;

PriestBossIronBall::PriestBossIronBall(const InitArg& arg) : ksys::act::ai::Ai(arg), _a0() {}

PriestBossIronBall::~PriestBossIronBall() = default;

bool PriestBossIronBall::init_(sead::Heap* heap) {
    for (auto& sender : _a0)
        sender._8 = &mActor->getMessageTransceiver();
    for (auto& sender : _420)
        sender._8 = &mActor->getMessageTransceiver();
    return true;
}

void PriestBossIronBall::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("準備完了待ち", params);
    _650 = 0;
    _654 = 0;
    _98 = false;
    _99 = false;
    _9a = false;
    _9b = false;
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (unit) {
        unit->_34c = 0;
        unit->_3c8 = 0;
        unit->_3cc = true;
    }
}

void PriestBossIronBall::calc_() {
    if (isFinished() || isFailed())
        return;
    if (!getCurrentChild())
        return;

    if (mActor->getASList()->x(0x34, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC,
                               true)) {
        sub_710051F1FC();
    } else {
        sub_710051F3FC();
    }
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");

    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    if (!_9b && unit->sub_710071A22C()) {
        _9b = true;
        ksys::act::ActorConstDataAccess accessor;
        for (s32 i = 0; i < 8; ++i) {
            if (!unit->sub_71007194D4(i + 11, &accessor))
                continue;
            auto& sender = _420[i];
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&sender._18.mLock);
                sender._18._0 = 4;
                sender._18._4 = sead::Vector3f::zero;
            }
            sender.sub_710070DD78(accessor, true);
        }
    }

    if (isCurrentChild("準備完了待ち")) {
        if (!_9a && mActor->getASList()->x(0x47, nullptr, 0, 0,
                                           &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            _9a = true;
            sub_710051E830();
        }
        if (!_99) {
            _99 = true;
            sub_710051EE40();
        }
        bool attack = false;
        if (--sUnk_7102413ff8 == 0) {
            sUnk_7102413ff8 = 90;
            attack = true;
        }
        if (attack) {
            if (!_9a)
                sub_710051E830();
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("攻撃", &params);
        }
    } else if (isCurrentChild("攻撃")) {
        if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            ++_654;
            m34();
        } else if (*mIsAfterAttack_s) {
            if (sub_710051E678())
                setFinished();
        } else {
            auto* child = getCurrentChild();
            if (child->isFinished() || child->isFailed())
                setFinished();
        }
        if (*mIsAfterAttack_s && _654 == 7 &&
            mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("攻撃後", &params);
        }
    } else if (isCurrentChild("攻撃後")) {
        if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true)) {
            m34();
        } else if (sub_710051E678() &&
                   mActor->getASList()->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101162FE8)) {
            setFinished();
        }
        if (unit->sub_710071A2D0())
            changeChild("攻撃終了");
    } else if (isCurrentChild("攻撃終了")) {
        if (getCurrentChild()) {
            auto* child = getCurrentChild();
            if (child->isFinished() || child->isFailed())
                setFinished();
        }
    }

    sub_710051EBDC();
    if (!_98)
        _98 = true;
}

void PriestBossIronBall::leave_() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 11; i < 19; ++i) {
        if (unit->sub_71007194D4(i, &accessor))
            _620.sub_710070DD78(accessor, true);
    }
    sub_710051F3FC();
    sub_710051F79C();
    unit->_3cc = false;
}

// NON_MATCHING: the original keeps the null path of the Enemy cast (x1 = 0); see
// PriestBossGiantStageRotRoot::sub_710051D234
void PriestBossIronBall::m34() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (_650 > 7)
        return;
    if (unit->sub_71007194D4(_650 + 11, &accessor)) {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        const sead::Vector3f enemy_pos = enemy->getMtx().getTranslation();
        {
            auto& payload = _a0[_650]._18;
            sead::ScopedLock<sead::JobQueueLock> lock(&payload.mLock);
            payload._0.acquire(enemy, false);
            payload._10 = enemy->_c48._8;
            payload._44 = 0;
            payload._20 = enemy_pos;
            payload._2c = sead::Vector3f::zero;
            payload._48 = 2;
            payload._38 = enemy_pos;
            payload._4c = 0;
        }
        _a0[_650].sub_710070DD78(accessor, true);
    }
    ++_650;
}

// NON_MATCHING: the original loads _650 before the two sign selects (scheduling only)
void PriestBossIronBall::m35(sead::Vector3f* out, s32 idx) {
    sead::Matrix34f left;
    left.makeIdentity();
    sead::Matrix34f right;
    right.makeIdentity();
    mActor->sub_71011D57F8(&left, mIronSummonLeftBoneName_s);
    mActor->sub_71011D57F8(&right, mIronSummonRightBoneName_s);

    const bool is_right = (idx & 1) == 0;
    const f32 angle = *mIronBallAngle_s;
    const f32 offset_y = *mIronBallOffsetY_s;
    const sead::Vector3f side = mActor->getMtx().getBase(0);
    const f32 angle_offset = *mIronBallAngleOffset_s;
    (is_right ? right : left).getTranslation(*out);
    const f32 signed_angle = is_right ? angle : -angle;
    const f32 signed_offset = is_right ? angle_offset : -angle_offset;
    const s32 n = sead::Mathf::floor((idx - _650) * 0.5f);
    const f32 rad = ((signed_offset + 90.0f) + signed_angle * n) * (sead::Mathf::pi() / 180.0f);
    const f32 dist = std::cos(rad) * *mIronBallRadius_s;
    const f32 height = std::sin(rad) * *mIronBallRadius_s - *mIronBallRadius_s;
    out->x += side.x * dist;
    out->y += offset_y + height;
    out->z += side.z * dist;
}

bool PriestBossIronBall::sub_710051E678() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 11; i < 19; ++i) {
        if (unit->sub_71007194D4(i, &accessor) && accessor.isStateCalc())
            return false;
    }
    return true;
}

void PriestBossIronBall::sub_710051E830() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 0; i < 8; ++i) {
        if (!unit->sub_71007194D4(i + 11, &accessor))
            continue;
        sead::Vector3f pos;
        m35(&pos, i);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx;
            mtx.makeIdentity();
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
        }
    }
}

// NON_MATCHING: the original keeps the null path of the Enemy cast (x1 = 0) and compares the start
// index with 7 (b.gt); see PriestBossGiantStageRotRoot::sub_710051D234
void PriestBossIronBall::sub_710051EBDC() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = _650; i < 8; ++i) {
        if (!unit->sub_71007194D4(i + 11, &accessor))
            continue;
        sead::Vector3f pos;
        m35(&pos, i);
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        const sead::Vector3f enemy_pos = enemy->getMtx().getTranslation();
        auto& sender = _a0[i];
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&sender._18.mLock);
            sender._18._0.acquire(enemy, false);
            sender._18._10 = enemy->_c48._8;
            sender._18._44 = 0;
            sender._18._20 = enemy_pos;
            sender._18._2c = sead::Vector3f::zero;
            sender._18._48 = 0;
            sender._18._38 = pos;
            sender._18._4c = 0;
        }
        sender.sub_710070DD78(accessor, true);
    }
}

// NON_MATCHING: block layout / register allocation around the two accessor scopes
void PriestBossIronBall::sub_710051EE40() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    if (*mIronBallWaitThunderTime_s >= 0) {
        ksys::act::ActorConstDataAccess accessor;
        if (unit->sub_71007194CC(&accessor)) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_658._18.mLock);
                _658._18._0 = 2;
                _658._18._4 = sead::Vector3f::zero;
            }
            _658._18._14 = *mIronBallWaitThunderTime_s;
            _658.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
        const f32 time = *mChangeEndAnime_s;
        unit->_35c = ksys::Timer(time, time);
    } else {
        ksys::act::ActorConstDataAccess accessor;
        if (unit->sub_71007194CC(&accessor)) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_658._18.mLock);
                _658._18._0 = 2;
                _658._18._4 = sead::Vector3f::zero;
            }
            _658._18._14 = *mIronBallWaitThunderTime_s;
            _658.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
        }
    }
}

void PriestBossIronBall::sub_710051F1FC() {
    for (s32 i = 0; i < Unk_710051f5fc::size(); ++i) {
        auto* body =
            mActor->findPhysicsBodyByName(sUnk_7102413eb8.cstr(), Unk_710051f5fc::text(i));
        if (body && body->isAddedToWorld())
            body->removeFromWorld();
    }
}

void PriestBossIronBall::sub_710051F3FC() {
    for (s32 i = 0; i < Unk_710051f5fc::size(); ++i) {
        auto* body =
            mActor->findPhysicsBodyByName(sUnk_7102413eb8.cstr(), Unk_710051f5fc::text(i));
        if (body && !body->isAddedToWorld())
            body->addToWorld();
    }
}

// NON_MATCHING: stack slot of the u32 temporary (sp+0 in the original) and the accessor address
// kept in a register for the destructor
void PriestBossIronBall::sub_710051F79C() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    ksys::act::ActorConstDataAccess accessor;
    unit->sub_71007194D4(1, &accessor);
    if (accessor.hasProc()) {
        _698.sub_710070E2BC(0, -1);
        _698.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}

void PriestBossIronBall::loadParams_() {
    getStaticParam(&mIronBallWaitThunderTime_s, "IronBallWaitThunderTime");
    getStaticParam(&mChangeEndAnime_s, "ChangeEndAnime");
    getStaticParam(&mIronBallOffsetY_s, "IronBallOffsetY");
    getStaticParam(&mIronBallRadius_s, "IronBallRadius");
    getStaticParam(&mIronBallAngle_s, "IronBallAngle");
    getStaticParam(&mIronSummonLeftBoneName_s, "IronSummonLeftBoneName");
    getStaticParam(&mIronSummonRightBoneName_s, "IronSummonRightBoneName");
    getStaticParam(&mIronBallAngleOffset_s, "IronBallAngleOffset");
    getStaticParam(&mIsAfterAttack_s, "IsAfterAttack");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
