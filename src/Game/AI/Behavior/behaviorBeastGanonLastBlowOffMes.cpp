#include "Game/AI/Behavior/behaviorBeastGanonLastBlowOffMes.h"
#include <cmath>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::behavior {

BeastGanonLastBlowOffMes::BeastGanonLastBlowOffMes(const InitArg& arg)
    : SimpleAtvUnitOpenDlgRnd3(arg) {}

BeastGanonLastBlowOffMes::~BeastGanonLastBlowOffMes() = default;

bool BeastGanonLastBlowOffMes::m6(sead::Heap* heap) {
    if (!SimpleAtvUnitOpenDlgRnd3::m6(heap))
        return false;
    _d8.search(mActor->getModel(), mXZBaseNode_s);
    return true;
}

void BeastGanonLastBlowOffMes::m7() {
    SimpleAtvUnitOpenDlgRnd3::m7();
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    if (accessor.isGroundForEvent() && _84)
        m16();
}

void BeastGanonLastBlowOffMes::m8() {
    SimpleAtvUnitOpenDlgRnd3::m8();
}

void BeastGanonLastBlowOffMes::m9() {
    SimpleAtvUnitOpenDlgRnd3::m9();
}

// NON_MATCHING: the original keeps the normalized forward vector in integer registers (memcpy-style Vector3f copy) and
// saves x21; also the operand order of the length-squared fadd differs
bool BeastGanonLastBlowOffMes::m15() {
    if (!isSlowTimeMaybe())
        return true;
    if (mActor->getASList()->x(2, nullptr, 2, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return true;
    if (!(mActor->getASList()->x_1(2, 0) == "WeakPointLastOn"))
        return true;

    bool result;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    const sead::Matrix34f& player_mtx = accessor.getActorMtx();
    const f32 player_x = player_mtx(0, 3);
    const f32 player_z = player_mtx(2, 3);
    f32 base_x = mActor->getMtx()(0, 3);
    f32 base_z = mActor->getMtx()(2, 3);
    const f32 actor_y = mActor->getMtx()(1, 3);
    if (*mSubsY_s >= 0.0f && player_mtx(1, 3) - actor_y < *mSubsY_s) {
        result = true;
    } else {
        if (!mXZBaseNode_s.isEmpty()) {
            sead::Matrix34f bone_mtx;
            mActor->getModel()
                ->getUnits()
                .unsafeAt(_d8.getKey().model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&bone_mtx, _d8.getKey().bone_index);
            base_x = bone_mtx(0, 3);
            base_z = bone_mtx(2, 3);
        }
        sead::Vector3f direction{player_x - base_x, 0, player_z - base_z};
        const f32 length = direction.normalize();
        if (*mDistXZ_s >= 0 && length > f32(*mDistXZ_s)) {
            result = true;
        } else {
            sead::Vector3f forward = mActor->getMtx().getBase(2);
            forward.y = 0;
            forward.normalize();
            result = !(direction.dot(forward) >= std::cos(*mFrontAngle_s));
        }
    }
    return result;
}

void BeastGanonLastBlowOffMes::loadParams() {
    SimpleAtvUnitOpenDlgRnd3::loadParams();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mSubsY_s, "SubsY");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mXZBaseNode_s, "XZBaseNode");
}

}  // namespace uking::behavior
