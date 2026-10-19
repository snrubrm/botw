#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelSceneComponent.h"

namespace agl {
class DrawContext;
}

namespace gsys {

// The environment (env sets, sky/light parameters) of a ModelScene; it is the sub-object at
// ModelScene + 0x130. It holds an array of data sets (count at 0xb98, pointer at 0xba0, 0x5f0 bytes
// each), and every data set an array of env sets (count at 0x438, pointer at 0x440, 0x1e8 bytes each).
// The object is 0x1158 bytes (the distance from ModelScene + 0x130 to the next ModelScene member, and the extent
// that ModelSceneEnv::ModelSceneEnv, 0x7100c21f8c, initializes).
// TODO: incomplete. Only functions that game code calls are declared; the members are not modeled yet.
class ModelSceneEnv : public ModelSceneComponent {
public:
    struct DataSet;
    struct Parts;

    // The env-set parts interface (its defaults are empty; the working sets are the two derived
    // classes below). Native rows are all 4-8 bytes.
    class PartsSet {
    public:
        virtual ~PartsSet();
        virtual void preprocess() const;
        virtual void postprocess() const;
        virtual void prepareBinary() const;
        virtual void releaseBinary() const;
        virtual void interpolate(const Parts*, const Parts*, f32) const;
        virtual void setup(const Parts*, const sead::SafeString&) const;
        virtual bool save(sead::BufferedSafeStringBase<char>*, const Parts*,
                          const sead::SafeString&) const;
    };

    class PartsSetUserStr : public PartsSet {
    public:
        ~PartsSetUserStr() override;
    };

    class PartsSetUserBin : public PartsSet {
    public:
        ~PartsSetUserBin() override;
    };

    // OpenWorldStage::unload 0x71007c5d20 passes the data-set array at +0xba0 to
    // clearImpl 0x7100c25294. The constructor 0x7100c21f8c clears count +0xb98 and this pointer.
    // 0x7100c29f7c: the base component draws no debug output.
    virtual void drawDebug(agl::DrawContext*, const ModelSceneContext&) const;

    DataSet* getDataSets() const { return mDataSets; }
    void clearImpl(DataSet* data_set, bool free_resource);

    // Constructor 0x7100c21f8c sets this true; destructor 0x7100c22124 clears it
    // before finalization. load_ 0x7100c29658 and stage unload 0x71007c5d20 pass it to clearImpl.
    bool get_b40() const { return m_b40; }

    // 0x7100c2859c (declared only): the index of the enabled env set called `name` in the data set
    // `data_set`, or -1 if there is none. (Descriptive name unknown.)
    int sub_7100C2859C(const sead::SafeString& name, u32 data_set);

    // 0x7100c286ec (declared only): applies the env set `env_set` of the data set `data_set`; with
    // `reset` the current env objects are cleared first.
    void sub_7100C286EC(u32 env_set, bool reset, u32 data_set);

private:
    /* 0x250 */ u8 _250[0xb40 - 0x250];
    /* 0xb40 */ bool m_b40;
    /* 0xb41 */ u8 _b41[0xb98 - 0xb41];
    /* 0xb98 */ s32 mDataSetCount;
    /* 0xb9c */ u8 _b9c[4];
    /* 0xba0 */ DataSet* mDataSets;
    /* 0xba8 */ u8 _ba8[0x1158 - 0xba8];
};
static_assert(sizeof(ModelSceneEnv) == 0x1158);

}  // namespace gsys
