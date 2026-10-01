#pragma once

#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class DofMgr : public Job {
    SEAD_RTTI_OVERRIDE(DofMgr, Job)
public:
    DofMgr();
    ~DofMgr() override;

    JobType getType() const override { return JobType::Dof; }

    void reset();
    // 0x00000071010d19b4
    void calcEntryJob();
    void sub_71010D20FC(float a, float b, float c);

protected:
    void init_(sead::Heap* heap) override;
    void calc_() override;

private:
    friend class Manager;

    void sub_71010D16EC();

    int _20;
    float _24;
    float _28;
    float _2c;
    agl::utl::Parameter<float> mDefaultDist;
    agl::utl::Parameter<float> mDefaultF;
    agl::utl::Parameter<float> mDefaultBlur;
    agl::utl::Parameter<float> mRemainsDist;
    agl::utl::Parameter<float> mRemainsF;
    agl::utl::Parameter<float> mRemainsBlur;
    float _f0;
    agl::utl::Parameter<float> mLockOnF;
    agl::utl::Parameter<float> mLockOnBlur;
    agl::utl::ParameterObj mDofMgrParamObj;
    float _168;
    float _16c;
    bool _170;
    float _174;
    float _178;
    float _17c;
    bool _180;
    bool _181;
    float _184;
    float _188;
    float _18c;
    float _190;
    float _194;
    float _198;
    float _19c;
    float _1a0;
    float _1a4;
    float _1a8;
    float _1ac;
    float _1b0;
    float _1b4;
    float _1b8;
    float _1bc;
};
KSYS_CHECK_SIZE_NX150(DofMgr, 0x1c0);

}  // namespace ksys::world
