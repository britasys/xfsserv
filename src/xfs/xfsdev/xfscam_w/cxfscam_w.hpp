#pragma once

#ifndef __H_CXFSCAM_W__
#define __H_CXFSCAM_W__

#include "./ixfscam_w.hpp"

namespace __N_XFSCAM_W__
{
	class CXFSCAM_W : public IXFSCAM_W
	{
	public:
		CXFSCAM_W() = default;
		CXFSCAM_W(const CXFSCAM_W&) = delete;
		CXFSCAM_W(CXFSCAM_W&&) = delete;
		CXFSCAM_W& operator = (const CXFSCAM_W) = delete;
		CXFSCAM_W& operator = (CXFSCAM_W&&) = delete;
		virtual ~CXFSCAM_W() = default;

		/* CAM Info Functions */
		long getStatus_sync(WFSCAMSTATUS_W&, const unsigned long) noexcept final;
		long getCapabilities_sync(WFSCAMCAPS_W&, const unsigned long) noexcept final;

		long getStatus_async(unsigned long&, const unsigned long) noexcept final;
		long getCapabilities_async(unsigned long&, const unsigned long) noexcept final;

		/* CAM Execute Functions */
		long takePicture_sync(const WFSCAMTAKEPICT_W&, const unsigned long) noexcept final;
		long reset_sync(const unsigned long) noexcept final;

		long takePicture_async(const WFSCAMTAKEPICT_W&, unsigned long&, const unsigned long) noexcept final;
		long reset(unsigned long&, const unsigned long) noexcept final;
	};
} // !__N_XFSCAM_W__

#endif // !__H_CXFSCAM_W__