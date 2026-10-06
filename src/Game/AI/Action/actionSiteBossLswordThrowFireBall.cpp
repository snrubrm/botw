#include "Game/AI/Action/actionSiteBossLswordThrowFireBall.h"
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

// NON_MATCHING: the original runs the 21-entry array loop with a byte-offset counter from `this`
// (x21 += 0x68) instead of an element pointer
SiteBossLswordThrowFireBall::SiteBossLswordThrowFireBall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordThrowFireBall::~SiteBossLswordThrowFireBall() = default;

bool SiteBossLswordThrowFireBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordThrowFireBall::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mThrowASName_s.cstr(), true, 0, 0, -1.0f);
    if (!mBindNodeName_s.isEmpty()) {
        for (u32 i = 0; i < 20; ++i) {
            if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
                if (boss->_1560._1e0[i].hasProc())
                    sub_710025F148(&boss->_1560._1e0[i], i);
            }
        }
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (enemy->getActorPartsActor(mPartsName_d).hasProc()) {
                auto& link = enemy->getActorPartsActor(mPartsName_d);
                if (link.hasProc())
                    sub_710025F148(&link, 0);
            }
        }
    }
    _80 = false;
    mFlags.reset(Flag::Changeable);
}

void SiteBossLswordThrowFireBall::leave_() {
    if (_80)
        return;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        for (s32 i = 0; i < 20; ++i)
            boss->_1560.sub_710066CC64(i);
    }
}

void SiteBossLswordThrowFireBall::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mFireBallAng_s, "FireBallAng");
    getStaticParam(&mIsThrowAll_s, "IsThrowAll");
    getStaticParam(&mThrowASName_s, "ThrowASName");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getDynamicParam(&mIsThrowChildDevice_d, "IsThrowChildDevice");
    getDynamicParam(&mPartsName_d, "PartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SiteBossLswordThrowFireBall::calc_() {
    if (mActor->getASList()->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        _80 = true;
        sub_710025F368();
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

// NON_MATCHING: same message-type stack slot as sub_710025F958 (the type is built before the accessor)
void SiteBossLswordThrowFireBall::sub_710025F148(ksys::act::BaseProcLink* link, s32 idx) {
    if (!link)
        return;
    auto& entry = _88[idx];
    entry._0 = sead::Vector3f::zero;
    entry._c = sead::Vector3f::zero;
    entry._18.reset();
    entry._28 = 0;
    entry._30.copy(mBindNodeName_s);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000058), &entry,
                        true);
}

// NON_MATCHING: the loop body, the offset table and the call match; the original copies *mTargetPos_d with integer
// loads (ldp w9, w10 / ldr w8, shared by the initial store to `pos` and `fmov s9..s11`) at the very top, ours loads
// the target as floats after the table stores
void SiteBossLswordThrowFireBall::sub_710025F368() {
    if (*mIsThrowChildDevice_d) {
        const sead::Vector3f offsets[20] = {
            {0, 0, 0},   {0, 2, 0},   {0, -2, 0},   {2, 0, 0},   {-2, 0, 0},
            {0, 0, 2},   {0, 0, -2},  {2, 2, 2},    {-2, -2, -2}, {-2, 2, 2},
            {2, -2, -2}, {-2, 2, -2}, {2, -2, 2},   {0, 5, 0},   {0, -5, 0},
            {5, 0, 0},   {-5, 0, 0},  {0, 0, 5},    {0, 0, -5},  {1.5f, 1.5f, 0},
        };
        const sead::Vector3f target = *mTargetPos_d;
        sead::Vector3f pos = target;
        for (s32 i = 0; i < 20; ++i) {
            pos.x = target.x + offsets[i].x;
            pos.y = target.y + offsets[i].y;
            pos.z = target.z + offsets[i].z;
            auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
            sub_710025F958(boss ? &boss->_1560._1e0[i] : nullptr, pos, i, 8.0f);
        }
        return;
    }

    ksys::act::BaseProcLink* link = nullptr;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor(mPartsName_d).hasProc())
            link = &enemy->getActorPartsActor(mPartsName_d);
    }
    sub_710025F958(link, *mTargetPos_d, 20, 1.0f);
}

// NON_MATCHING: the original builds the message type (stack slot above the accessor) before the accessor; only a named
// `const auto type = ksys::MessageType(0x800003a);` declared before the accessor reproduces that
void SiteBossLswordThrowFireBall::sub_710025F958(ksys::act::BaseProcLink* link,
                                                 const sead::Vector3f& pos, s32 idx, f32 scale) {
    if (!link)
        return;
    auto& entry = _88[idx];
    entry._0 = pos;
    entry._c = sead::Vector3f::zero;
    entry._18 = *mTargetActor_d;
    entry._28 = *mInitVelocity_s * scale;
    entry._30.clear();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x800003a), &entry,
                        true);
}

}  // namespace uking::action
