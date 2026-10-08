#include "Game/AI/Action/actionGanonBeastBeamMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actBeamBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

GanonBeastBeamMove::GanonBeastBeamMove(const InitArg& arg) : SimpleLineBeam(arg) {}

GanonBeastBeamMove::~GanonBeastBeamMove() = default;

bool GanonBeastBeamMove::init_(sead::Heap* heap) {
    if (!SimpleLineBeam::init_(heap))
        return false;

    auto* transceiver = &mActor->getMessageTransceiver();
    for (auto& sender : _50)
        sender._8 = transceiver;
    return true;
}

void GanonBeastBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLineBeam::enter_(params);

    _288 = *mRestNumMax_s;
    const f32 min_limit = *mRestDistMinLimit_s;
    const sead::Vector3f& player_pos = getPlayerPosition();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 dx = player_pos.x - pos.x;
    const f32 dz = player_pos.z - pos.z;
    _27c = sead::Mathf::clamp(sead::Mathf::sqrt(dx * dx + dz * dz) * 0.5f, min_limit, *mRestDistLimit_s);
    if (sead::DynamicCast<act::LineBeam>(mActor))
        mActor->getMtx().getTranslation(_270);
    _280 = *mRestDistMinLimit_s;
    _284 = *mRestDistTime_s;
    _28c = false;
}

void GanonBeastBeamMove::leave_() {
    SimpleLineBeam::leave_();
}

void GanonBeastBeamMove::loadParams_() {
    SimpleLineBeam::loadParams_();
    getStaticParam(&mRestDistTime_s, "RestDistTime");
    getStaticParam(&mRestDistTimeAdd_s, "RestDistTimeAdd");
    getStaticParam(&mRestNumMax_s, "RestNumMax");
    getStaticParam(&mRestDistLimit_s, "RestDistLimit");
    getStaticParam(&mRestDistMinLimit_s, "RestDistMinLimit");
    getStaticParam(&mRestDistInterval_s, "RestDistInterval");
    getStaticParam(&mRestActor_s, "RestActor");
}

// NON_MATCHING: register allocation, spill slots and scheduling order only; all calls,
// values, branch structure and the sender-atomics match.
void GanonBeastBeamMove::calc_() {
    SimpleLineBeam::calc_();
    auto* actor = mActor;
    if (sead::DynamicCast<act::LineBeam>(actor) == nullptr)
        return;
    auto* beam = static_cast<act::LineBeam*>(actor);
    if (beam->_d30) {
        auto* terrain = ksys::tera::Terrain::sInstance;
        if (terrain && terrain->isGrassEnabled()) {
            terrain->sub_710114DE4C()->sub_7101150FD4(&beam->_d1c, 10.0f, 8.0f);
            terrain->sub_710114DE4C()->sub_7101150A7C(&beam->_d1c, 13.0f, 10.0f);
            const f32 dx = beam->_d1c.x - _270.x;
            const f32 dz = beam->_d1c.z - _270.z;
            const f32 len = sqrtf(dx * dx + 0.0f + dz * dz);
            const f32 inv = 1.0f / len;
            s32 n = static_cast<s32>(len / 5.0f);
            sead::Vector3f step{
                len <= 0.0f ? dx : dx * inv,
                len <= 0.0f ? 0.0f : 0.0f * inv,
                len <= 0.0f ? dz : dz * inv,
            };
            sead::Vector3f pos = _270;
            if (n >= 1) {
                do {
                    pos.x += step.x * 5.0f;
                    pos.y += step.y + 5.0f;
                    pos.z += step.z * 5.0f;
                    sead::Vector3f neg_ey = -sead::Vector3f::ey;
                    if (!::somePositionCalc(&pos, pos, neg_ey, 10.0f))
                        pos.x += -5.0f;
                    auto* terrain2 = ksys::tera::Terrain::sInstance;
                    terrain2->sub_710114DE4C()->sub_7101150FD4(&pos, 10.0f, 8.0f);
                    --n;
                } while (n != 0);
            }
        }
        _28c = true;
        _270 = beam->_d1c;
    } else if (!_28c) {
        return;
    }
    if (_288 < 1)
        return;
    sead::Vector3f dir = beam->_d1c;
    dir.y = 0.0f;
    const f32 dx = dir.x - beam->_c68.x;
    const f32 dz = dir.z - beam->_c68.z;
    dir.x = dx;
    dir.z = dz;
    const f32 len = sqrtf(dx * dx + 0.0f + dz * dz);
    const f32 inv = 1.0f / len;
    if (len > 0.0f)
        dir *= inv;
    if (len < *mRestDistLimit_s)
        return;
    // NOTE: the point uses inv (not len) times the normalized dir; kept as-is to match.
    sead::Vector3f point{beam->_c68.x + inv * dir.x, beam->_c68.y + inv * dir.y,
                         beam->_c68.z + inv * dir.z};
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    ksys::util::sub_71011F00EC(&mtx, dir, sead::Vector3f::ey, sead::Vector3f::zero, false);
    f32 height = 0.0f;
    sead::Vector3f ground;
    ground.x = actor->getMtx().m[0][3];
    ground.y = actor->getMtx().m[1][3];
    ground.z = actor->getMtx().m[2][3];
    if (::sub_710072C21C(&height, &ground)) {
        point.y = height;
    } else {
        point.y += 10.0f;
        const sead::Vector3f neg = -sead::Vector3f::ey;
        if (!::somePositionCalc(&point, point, neg, 80.0f))
            point.y += -10.0f;
    }
    mtx.m[0][3] = point.x;
    mtx.m[1][3] = point.y;
    mtx.m[2][3] = point.z;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_50[0]._18.mLock);
        _50[0]._18._0 = mtx;
        _50[0]._18._30 = _284;
    }
    _50[0].sub_710070DCC0(&beam->_b90._40, false);
    --_288;
}

}  // namespace uking::action
