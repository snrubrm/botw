#include "Game/AI/AI/aiKorokAnswerResponceRoot.h"

#include "KingSystem/ActorSystem/actActor.h"

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

void KorokAnswerResponceRoot::loadParams_() {
    getMapUnitParam(&mEffectDispSize_m, "EffectDispSize");
    getMapUnitParam(&mIsNoResponceSound_m, "IsNoResponceSound");
    getMapUnitParam(&mEffectDispActorName_m, "EffectDispActorName");
    getMapUnitParam(&mEffectDIspOffset_m, "EffectDIspOffset");
}

}  // namespace uking::ai
