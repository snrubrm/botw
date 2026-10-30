#include "Game/Actor/AI/aiAirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
namespace uking {

// NON_MATCHING: matrix arithmetic and position load/store scheduling differ.
void AirOctaDataMgr::sub_71002FAF84(ksys::act::Actor* actor) {
    if (mFlags & 1)
        return;

    if (auto* object = ksys::act::findLinkReferenceObj(actor, "", "Manager", nullptr)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        object->getActorWithAccessor(accessor);
        accessor.linkAcquire(&mBaseProcLink);
    }

    if (auto* object = ksys::act::findLinkReferenceObj(actor, "", "Board", nullptr)) {
        ksys::act::ActorLinkConstDataAccess accessor;
        object->getActorWithAccessor(accessor);
        if (accessor.linkAcquire(&mBaseProcLink2)) {
            const sead::Vector3f position = actor->getMtx().getTranslation();
            sead::Matrix34f inverse;
            sead::Matrix34CalcCommon<f32>::inverse(inverse, accessor.getActorMtx());
            const sead::Vector3f local = inverse * position;
            vec_E0.set(local.x, 0.0f, local.z);
            unk_110 = local.y;
        }
    }

    vec_F8 = actor->getMtx().getTranslation();
    vec_EC = vec_F8;
    vec_EC.y -= unk_110;
    mFlags |= 1;
    changeOctasYheightMaybe();
}

// 0x71002fb1a8 (placeholder name): copies the message's snapshot into unk_28 and marks it valid.
void AirOctaDataMgr::sub_71002FB1A8(const SubData* src) {
    sub_71002FB1D8(&unk_28, src);
    mFlags |= 4;
}

// 0x71002fb32c (placeholder name): the snapshot once the message has been copied in.
AirOctaDataMgr::SubData* AirOctaDataMgr::sub_71002FB32C() {
    return (mFlags & 4) ? &unk_28 : nullptr;
}

void AirOctaDataMgr::sub_71002FB340(f32 x, f32 z) {
    vec_F8.x = x;
    vec_F8.z = z;
}

void AirOctaDataMgr::changeOctasYheightMaybe() {
    float result = vec_EC.y + unk_110 + unk_114 + unk_118 + unk_11c;
    vec_F8.y = result;
}
}  // namespace uking