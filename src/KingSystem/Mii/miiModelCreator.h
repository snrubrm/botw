#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"
#include <gsys/gsysModel.h>

namespace al {
class ByamlIter;
}

namespace ksys::mii {

class UMii;

extern sead::SafeArray<sead::SafeString, 4> s_rot_labels;

// Name from the CSV (Netfp::ctor 0x7100f58078, Netfp::initParamsAndLoadArchive 0x7100f5833c, Netfp::dtor
// 0x7100f59744); the namespace is a guess. ModelCreator owns one (0x8048 bytes) for Mii/umii.bnetfp.
// Declaration only.
class Netfp {
public:
    Netfp();
    virtual ~Netfp();
    void initParamsAndLoadArchive(u8* data, sead::Heap* heap);

private:
    u8 _8[0x8048 - 0x8];
};
KSYS_CHECK_SIZE_NX150(Netfp, 0x8048);

// FIXME: incomplete
class ModelCreator final : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ModelCreator)
public:
    ModelCreator() = default;
    ~ModelCreator();

    struct Arg {
        int type;
    };

    // 0x7100f4c778: loads Mii/UMiiConstructionInfo.byml and Mii/umii.bnetfp.
    void init(sead::Heap* heap);
    void loadUMiiConstructionInfo(sead::Heap* heap);
    void loadUmiiBnetfp(sead::Heap* heap);

    const sead::SafeString& getActorName(const Arg& arg) const;
    // 0x7100f4cb50: dispatches on the Mii's race (Body::race) to one of the seven createUmiiModelRaceN helpers.
    gsys::Model* createUmiiModel(const UMii& umii, const sead::SafeString& name, void* part_names,
                                 gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    // 0x7100f4cc88 .. 0x7100f4d74c (declared only): the per-race Mii model builders.
    gsys::Model* createUmiiModelRace0(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    gsys::Model* createUmiiModelRace1(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    gsys::Model* createUmiiModelRace2(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    gsys::Model* createUmiiModelRace3(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    gsys::Model* createUmiiModelRace4(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    gsys::Model* createUmiiModelRace5(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    gsys::Model* createUmiiModelRace6(const UMii& umii, const sead::SafeString& name, void* part_names,
                                      gsys::Model::CreateArg arg, void* out, sead::Heap* heap);
    // 0x7100f4c9fc (placeholder name; CSV ModelCreator::__auto2): looks up the "%03d" entry `index` in the Mouth
    // (type 1) or Hair (type 3) table of the construction info.
    bool sub_7100F4C9FC(const char** out, const s32& index, const Arg& arg) const;

private:
    res::Unk_71025148b8 _28;
    res::Handle mBnetfpHandle;
    res::Handle mConstructionInfoHandle;
    Netfp* mNetfp = nullptr;
    al::ByamlIter* mConstructionInfo = nullptr;
};
KSYS_CHECK_SIZE_NX150(ModelCreator, 0xf8);

}  // namespace ksys::mii
