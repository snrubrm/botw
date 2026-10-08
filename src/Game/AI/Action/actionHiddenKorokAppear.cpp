#include "Game/AI/Action/actionHiddenKorokAppear.h"
#include "Game/gamePlayReport.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

HiddenKorokAppear::HiddenKorokAppear(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HiddenKorokAppear::~HiddenKorokAppear() = default;

bool HiddenKorokAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the rotation angle fed to sinf/cosf is the sub_71011EEB08 axis output's
// Y component multiplied by literal 0.0 (fmul with fmov-zero; the call's float output is
// never read), and the RotY rows are built arithmetically from it; the source form of that
// zero is unknown, so this uses sinf/cosf(angle) with plain rows instead. The composition
// (4-wide row combos into the mtx copy, setMtx(mtx, false, true)) and the tail
// (x_6, clear 0x518 bit 0x20, CC pair, getHomePos + reportKorok, return true) match.
bool HiddenKorokAppear::oneShot_() {
    const sead::Vector3f& player_pos = getPlayerPosition();
    auto* actor = mActor;
    const sead::Matrix34f& mtx = actor->getMtx();
    sead::Vector3f dir;
    dir.x = player_pos.x - mtx.m[0][3];
    dir.z = player_pos.z - mtx.m[2][3];
    dir.y = 0.0f;
    sead::Vector3f front{mtx.m[0][2], 0.0f, mtx.m[2][2]};
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, dir, sead::Vector3f::ey);
    const f32 s = sinf(angle);
    const f32 c = cosf(angle);
    const sead::Vector4f r0{c, 0.0f, s, 0.0f};
    const sead::Vector4f r1{0.0f, 1.0f, 0.0f, 0.0f};
    const sead::Vector4f r2{-s, 0.0f, c, 0.0f};
    sead::Matrix34f new_mtx = mtx;
    {
        const f32 x = new_mtx.m[0][0];
        const f32 y = new_mtx.m[0][1];
        const f32 z = new_mtx.m[0][2];
        sead::Vector4f n = r0 * x + r1 * y + r2 * z;
        new_mtx.m[0][0] = n.x;
        new_mtx.m[0][1] = n.y;
        new_mtx.m[0][2] = n.z;
    }
    {
        const f32 x = new_mtx.m[1][0];
        const f32 y = new_mtx.m[1][1];
        const f32 z = new_mtx.m[1][2];
        sead::Vector4f n = r0 * x + r1 * y + r2 * z;
        new_mtx.m[1][0] = n.x;
        new_mtx.m[1][1] = n.y;
        new_mtx.m[1][2] = n.z;
    }
    {
        const f32 x = new_mtx.m[2][0];
        const f32 y = new_mtx.m[2][1];
        const f32 z = new_mtx.m[2][2];
        sead::Vector4f n = r0 * x + r1 * y + r2 * z;
        new_mtx.m[2][0] = n.x;
        new_mtx.m[2][1] = n.y;
        new_mtx.m[2][2] = n.z;
    }
    actor->setMtx(new_mtx, false, true);
    actor->x_6();
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    sub_71007A3540(actor);
    auto* controller = actor->getCharacterController();
    if (controller) {
        controller->sub_7100F60604();
        controller->sub_7100F63388(true, -1);
    }
    sead::Vector3f home;
    actor->getHomePos(&home);
    reportKorok(home);
    return true;
}

void HiddenKorokAppear::loadParams_() {}

}  // namespace uking::action
