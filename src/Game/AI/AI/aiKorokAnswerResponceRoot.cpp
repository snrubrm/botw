#include "Game/AI/AI/aiKorokAnswerResponceRoot.h"

#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

void playEffectMaybe(const char* name, Unk_71012419b4* handles);

namespace uking::ai {

KorokAnswerResponceRoot::KorokAnswerResponceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokAnswerResponceRoot::~KorokAnswerResponceRoot() = default;

bool KorokAnswerResponceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokAnswerResponceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = false;
    _79 = false;
}

void KorokAnswerResponceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: vector normalization uses different register allocation and spills.
void KorokAnswerResponceRoot::calc_() {
    if (!mActor->checkBasicSig())
        return;
    sub_7100457BB4();
    if (!_78) {
        if (!*mIsNoResponceSound_m)
            playEffectMaybe("Solve_HiddenKorok", &_a0);
        if (!_79)
            xlinkSearchAndEmit(mActor, "AnswerResponce", 2, &_80);
        _78 = true;
    }
    if (_60.hasProc()) {
        sead::Matrix34f matrix = sead::Matrix34f::ident;
        sead::Vector3f position;
        _60.getActorMtx().getTranslation(position);
        sead::Vector3f x = _60.getActorMtx().getBase(0);
        sead::Vector3f y = _60.getActorMtx().getBase(1);
        sead::Vector3f z = _60.getActorMtx().getBase(2);
        x.normalize();
        y.normalize();
        z.normalize();
        matrix.setBase(0, x);
        matrix.setBase(1, y);
        matrix.setBase(2, z);
        sub_7100457EB8(matrix, position);
    }
}

void KorokAnswerResponceRoot::sub_7100457BB4() {
    if (mEffectDispActorName_m == "none") {
        _79 = true;
        return;
    }

    ksys::map::Object* obj;
    if (mEffectDispActorName_m == "DesignerLocaterKorokRock") {
        obj = ksys::act::findLinkReferenceObj(mActor, "Obj_LiftRockWhite_Korok_A_01", "", nullptr);
        if (!obj) {
            obj = ksys::act::findLinkReferenceObj(mActor, "Obj_LiftRockGerudo_Korok_A_01", "",
                                                  nullptr);
            if (!obj) {
                obj = ksys::act::findLinkReferenceObj(mActor, "Obj_LiftRockEldin_Korok_A_01", "",
                                                      nullptr);
            }
        }
    } else {
        ksys::act::findLinkedActor(&_60, mActor, mEffectDispActorName_m);
        obj = ksys::act::findLinkReferenceObj(mActor, mEffectDispActorName_m, "", nullptr);
        if (_60.hasProc())
            return;
        if (!obj) {
            _79 = true;
            return;
        }
    }

    if (obj) {
        sead::Matrix34f mtx;
        mtx.makeR(obj->getRotate());
        mtx.setTranslation(0.0f, 0.0f, 0.0f);
        const sead::Vector3f pos = obj->getTranslate();
        sub_7100457EB8(mtx, pos);
    } else {
        _79 = true;
    }
}

// NON_MATCHING: the original builds the identity / scale / offset matrices from literal-pool vectors
// and vectorises the products; ours copies sead::Matrix34f::ident. Semantics match.
void KorokAnswerResponceRoot::sub_7100457EB8(const sead::Matrix34f& matrix,
                                             const sead::Vector3f& position) {
    sead::Matrix34f result = sead::Matrix34f::ident;
    sead::Matrix34f inv = sead::Matrix34f::ident;
    sead::Matrix34f mtx = matrix;
    const f32 size = *mEffectDispSize_m;
    const sead::Vector3f offset = *mEffectDIspOffset_m;
    inv.setInverse(mtx);

    sead::Matrix34f scale;
    scale.makeS(size, size, size);
    inv = scale * inv;
    sead::Matrix34f trans = sead::Matrix34f::ident;
    trans.setTranslation(offset);
    inv = trans * inv;
    mtx = mtx * inv;

    result.setTranslation(position);
    result = result * mtx;
    _80.sub_7101241A44(result);
}

void KorokAnswerResponceRoot::loadParams_() {
    getMapUnitParam(&mEffectDispSize_m, "EffectDispSize");
    getMapUnitParam(&mIsNoResponceSound_m, "IsNoResponceSound");
    getMapUnitParam(&mEffectDispActorName_m, "EffectDispActorName");
    getMapUnitParam(&mEffectDIspOffset_m, "EffectDIspOffset");
}

}  // namespace uking::ai
