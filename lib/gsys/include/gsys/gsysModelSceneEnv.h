#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "gsys/gsysModelSceneComponent.h"
#include <common/aglTextureData.h>
#include <common/aglTextureSampler.h>

namespace agl {
class DrawContext;
namespace utl {
class IParameterIO;
}
}  // namespace agl

namespace gsys {

// The environment (env sets, sky/light parameters) of a ModelScene; it is the sub-object at
// ModelScene + 0x130. It holds an array of data sets (count at 0xb98, pointer at 0xba0, 0x5f0 bytes
// each), and every data set an array of env sets (count at 0x438, pointer at 0x440, 0x1e8 bytes each).
// The object is 0x1158 bytes (the distance from ModelScene + 0x130 to the next ModelScene member, and the extent
// that ModelSceneEnv::ModelSceneEnv, 0x7100c21f8c, initializes).
// TODO: incomplete. Only functions that game code calls are declared; the members are not modeled yet.
class ModelSceneEnv : public ModelSceneComponent {
public:
    struct Parts;
    // The argument of the environment apply callback delegate; only the name is recovered.
    struct ApplyCallbackArg;

    ModelSceneEnv();
    ~ModelSceneEnv() override;
    // 0x7100c221d8 (declared only): released by the destructor before the texture members.
    void finalize();

    // Env-set record: 0x1e8 bytes; enabled byte at +0, SafeString name at +8.
    struct EnvSet {
        u8 mEnabled;
        u8 _1[7];
        sead::SafeString mName;
        u8 _18[0x1e8 - 0x18];
    };
    static_assert(sizeof(EnvSet) == 0x1e8);

    // Data-set record: 0x5f0 bytes; env-set count at +0x438 and array at +0x440.
    struct DataSet {
        u8 _0[0x438];
        s32 mEnvSetCount;
        u8 _43c[4];
        EnvSet* mEnvSets;
        u8 _448[0x5c0 - 0x448];
        // setFilenameImpl 0x7100c2934c splits a path at its last '/' and stores the directory
        // here and the file name at +0x5d0; it clears the third string at +0x5e0.
        sead::SafeString mSourceDirectory;
        sead::SafeString mSourceFileName;
        sead::SafeString mSourceFileExtension;
    };
    static_assert(sizeof(DataSet) == 0x5f0);

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

    // Partial model: the getter's data layout is not modelled, only the two bit tests and
    // getAccessoryKey 0x7100c2a8b4. Both bit tests are false above index 4 and read a
    // constant mask (0xc / 0x7) below it, so they need no members.
    class AreaEnvGetter {
    public:
        s32 getAccessoryKey(u32 a, u32 b, u32 c) const;
        // 0x7100c29fdc: bit `index` of 0xc (the composite entry types 2 and 3).
        bool isComposite(u32 index) const;
        // 0x7100c2a000: bit `index` of 0x7 (the view-dependent entry types 0, 1 and 2).
        bool isViewDependence(u32 index) const;
    };

    // OpenWorldStage::unload 0x71007c5d20 passes the data-set array at +0xba0 to
    // clearImpl 0x7100c25294. The constructor 0x7100c21f8c clears count +0xb98 and this pointer.
    // 0x7100c29f7c: the base component draws no debug output.
    virtual void drawDebug(agl::DrawContext*, const ModelSceneContext&) const;

    DataSet* getDataSets() { return mDataSets.getBufferPtr(); }
    const DataSet* getDataSets() const { return mDataSets.getBufferPtr(); }
    void clearImpl(DataSet* data_set, bool free_resource);

    // The 24-byte record returned by getApplyUserBinarySlot 0x7100c29298: the user-binary pointer,
    // its size and the source-file name string. The native function is an out-of-line 180-byte
    // helper, so only the shape is recovered here.
    struct ApplyUserBinarySlotMaybe {
        const void* mBinary;
        u32 mSize;
        u32 _c;
        const char* mSourceFileName;
    };
    static_assert(sizeof(ApplyUserBinarySlotMaybe) == 0x18);

    // 0x7100c29298 (declared only): returns the user binary of the data set `data_set` for the
    // apply slot `slot`; both fields are cleared when the slot is absent.
    ApplyUserBinarySlotMaybe getApplyUserBinarySlot(u32 slot, u32 data_set) const;
    // 0x7100c2546c: joins the data set's source directory (set at +0x5c0 by setFilenameImpl) with
    // `file_name` and stores the result as the parameter I/O object's save path.
    void setSourceFileName(agl::utl::IParameterIO* io, const sead::SafeString& file_name,
                           u32 data_set) const;
    // 0x7100c25494: the out-of-line path join behind setSourceFileName. It returns false when
    // either the directory or the file name is empty and otherwise writes the 256-byte path
    // buffer of `io` (IParameterIO +0xb0) as directory + '/' + file name.
    static bool setSourceFileName_(agl::utl::IParameterIO* io, const sead::SafeString& directory,
                                   const sead::SafeString& file_name);

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
    /* 0x250 */ u8 _250[0x268 - 0x250];
    // Destructor 0x7100c22124 destroys two samplers and five texture records in this order.
    /* 0x268 */ agl::TextureSampler mSampler0;
    /* 0x3d8 */ agl::TextureData mData0;
    /* 0x500 */ u8 _500[0x510 - 0x500];
    /* 0x510 */ agl::TextureSampler mSampler1;
    /* 0x680 */ agl::TextureData mData1;
    /* 0x7a8 */ u8 _7a8[0x7b0 - 0x7a8];
    /* 0x7b0 */ agl::TextureData mData2;
    /* 0x8d8 */ agl::TextureData mData3;
    /* 0xa00 */ u8 _a00[0xa10 - 0xa00];
    /* 0xa10 */ agl::TextureData mData4;
    /* 0xb38 */ u8 _b38[0xb40 - 0xb38];
    /* 0xb40 */ bool m_b40;
    /* 0xb41 */ u8 _b41[0xb98 - 0xb41];
    // Constructor 0x7100c21f8c clears the count and the array pointer; OpenWorldStage::unload
    // 0x71007c5d20 passes the array to clearImpl.
    /* 0xb98 */ sead::Buffer<DataSet> mDataSets;
    /* 0xba8 */ u8 _ba8[0xd88 - 0xba8];
    /* 0xd88 */ agl::utl::DebugTexturePage mDebugTexturePage;
    /* 0xfc8 */ u8 _fc8[0x1158 - 0xfc8];
};
static_assert(sizeof(ModelSceneEnv) == 0x1158);

}  // namespace gsys
