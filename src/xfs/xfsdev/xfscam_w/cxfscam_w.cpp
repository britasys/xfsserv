#include "./cxfscam_w.hpp"

namespace __N_XFSCAM_W__
{
	/* CAM Info Functions */
	long CXFSCAM_W::getStatus_sync(WFSCAMSTATUS_W& wfs_cam_status_w, const unsigned long timeout) noexcept
    {
        return this->info_sync(WFS_INF_CAM_STATUS, nullptr, wfs_cam_status_w, timeout);
    }

	long CXFSCAM_W::getCapabilities_sync(WFSCAMCAPS_W& wfs_cam_caps_w, const unsigned long timeout) noexcept
    {
        return this->info_sync(WFS_INF_CAM_CAPABILITIES, nullptr, wfs_cam_caps_w, timeout);
    }

	long CXFSCAM_W::getStatus_async(unsigned long& reqid, const unsigned long timeout) noexcept
    {
        return this->info_async(WFS_INF_CAM_STATUS, nullptr, reqid, timeout);
    }

	long CXFSCAM_W::getCapabilities_async(unsigned long& reqid, const unsigned long timeout) noexcept
    {
        return this->info_async(WFS_INF_CAM_CAPABILITIES, nullptr, reqid, timeout);
    }

	/* CAM Execute Functions */
	long CXFSCAM_W::takePicture_sync(const WFSCAMTAKEPICT_W&, const unsigned long) noexcept
    {
        return true;
    }

	long CXFSCAM_W::reset_sync(const unsigned long) noexcept
    {
        return true;
    }

	long CXFSCAM_W::takePicture_async(const WFSCAMTAKEPICT_W&, unsigned long&, const unsigned long) noexcept
    {
        return true;
    }

	long CXFSCAM_W::reset(unsigned long&, const unsigned long) noexcept
    {
        return true;
    }
} // !__N_XFSCAM_W__