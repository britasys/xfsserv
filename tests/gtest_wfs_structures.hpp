#pragma once

#ifndef __H_GTEST_WFS_STRUCTURES__
#define __H_GTEST_WFS_STRUCTURES__

#include <gtest/gtest.h>

#include <xfs_w.hpp>

#include <string>
#include <stdexcept>

TEST(_wfs_lpsz_extra_w, constructors)
{
    char l_WFSLPSZExtra[] = { 'f', 'i', 'r', 's', 't', NULL, 's', 'e', 'c', 'o', 'n', 'd', NULL, NULL };
    __N_XFS_W__::WFSLPSZEXTRA_W l_WFSLPSZExtra_w{};
    l_WFSLPSZExtra_w.assign(l_WFSLPSZExtra);
    EXPECT_EQ(l_WFSLPSZExtra_w.size(), 2);
    EXPECT_EQ(l_WFSLPSZExtra_w[0], std::string{ "first" });
    EXPECT_EQ(l_WFSLPSZExtra_w[1], std::string{ "second" });
    try {
        l_WFSLPSZExtra_w[2];
    } catch (const std::exception & e) {
        EXPECT_EQ(std::string{ "index not exist" }, e.what());
    }
}

#endif // !__H_GTEST_WFS_STRUCTURES__