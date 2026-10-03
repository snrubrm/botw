#include "Game/AI/aiUnk_71007091AC.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActor.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>

// NON_MATCHING: the original checks the bone key with `cmn w0, #0x10, lsl #12; b.hs` (word < 0xffff0000)
// instead of the isValid() form (`orr w8, #0xfffeffff; cmp; b.hi`), and allocates out_a/out_b to
// x20/x21 in the other order (everything else is identical).
bool sub_71007091AC(ksys::act::Actor* actor, s32* out_a, s32* out_b, s32* out_c) {
    if (actor) {
        if (auto* model = actor->getModel()) {
            sead::Vector3f dir;
            model->getMatrix().getBase(dir, 2);
            const auto key = model->searchBone("Neck");
            if (key.isValid()) {
                sead::Matrix34f mtx;
                actor->getModel()
                    ->getUnits()
                    .unsafeAt(key.model_unit_index)
                    ->mModelUnit->getBoneWorldMatrix(&mtx, key.bone_index);
                sead::Vector3f neck_dir;
                mtx.getBase(neck_dir, 2);
                dir.normalize();
                neck_dir.normalize();
                f32 dot = dir.dot(neck_dir);
                dot = sead::Mathf::clamp(dot, -1.0f, 1.0f);
                const f32 angle = sead::Mathf::acos(dot);
                s32 a, b, c;
                if (angle <= sead::Mathf::deg2rad(50) && angle >= -sead::Mathf::deg2rad(50)) {
                    a = 0;
                    b = 1;
                    c = 2;
                } else {
                    const bool left = dir.x * neck_dir.z - dir.z * neck_dir.x < 0.0f;
                    a = left ? 2 : 1;
                    b = left ? 0 : 2;
                    c = left ? 1 : 0;
                }
                *out_a = a;
                *out_b = b;
                *out_c = c;
                return true;
            }
        }
    }
    *out_c = -1;
    *out_b = -1;
    *out_a = -1;
    return false;
}

s32 sub_710070914C(ksys::act::Actor* actor, s32 value) {
    s32 a = 0;
    s32 b = 0;
    s32 c = 0;
    sub_71007091AC(actor, &a, &b, &c);
    if (a == value)
        return 1;
    return b == value ? 2 : -1;
}
