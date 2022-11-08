#pragma once

#ifndef __H_GTEST_WFSCAM_STRUCTURES__
#define __H_GTEST_WFSCAM_STRUCTURES__

#include <gtest/gtest.h>

#include <xfsdev/xfscam_w/xfscam_w.hpp>

using namespace __N_XFSCAM_W__;

TEST(_wfs_cam_status_w, constructors)
{
    WFSCAMSTATUS l_status{};
    l_status.fwDevice           = WFS_CAM_DEVONLINE;
    l_status.fwMedia[1]         = 0x45;
    l_status.fwCameras[1]       = 0x45;
    l_status.usPictures[1]      = 0x45;
    l_status.lpszExtra          = nullptr;
    l_status.wAntiFraudModule   = 0x55;

    WFSCAMSTATUS_W l_status_w{};
    l_status_w.assign(l_status);

    EXPECT_EQ(l_status_w.fwDevice, l_status.fwDevice);
}

TEST(_wfs_cam_caps_w, constructors)
{
    WFSCAMCAPS l_caps{};
    l_caps.wClass               = 0x03;
    l_caps.fwType               = 0x10;
    l_caps.fwCameras[5]         = 0x35; 
    l_caps.usMaxPictures        = 10;
    l_caps.fwCamData            = 3;
    l_caps.usMaxDataLength      = 10;
    l_caps.fwCharSupport        = 5;
    WFSCAMCAPS_W l_caps_w{};
    l_caps_w.assign(l_caps);

    EXPECT_EQ(l_caps_w.wClass, l_caps.wClass);
}

#endif // !__H_GTEST_WFSCAM_STRUCTURES__