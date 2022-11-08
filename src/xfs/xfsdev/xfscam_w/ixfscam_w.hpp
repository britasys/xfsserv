#pragma once

#ifndef __H_IXFSCAM_W__
#define __H_IXFSCAM_W__

#include "../ixfsdev.hpp"
#include "./xfscam_w.hpp"

namespace __N_XFSCAM_W__
{
	class IXFSCAM_W : public __N_IXFSDEV__::IXFSDEV
	{
	public:
		IXFSCAM_W() = default;
		IXFSCAM_W(const IXFSCAM_W&) = delete;
		IXFSCAM_W(IXFSCAM_W&&) = delete;
		IXFSCAM_W& operator = (const IXFSCAM_W) = delete;
		IXFSCAM_W& operator = (IXFSCAM_W&&) = delete;
		virtual ~IXFSCAM_W() = default;

		/* CAM Info Functions */
		virtual long getStatus_sync(WFSCAMSTATUS_W&, const unsigned long) noexcept = 0;
		virtual long getCapabilities_sync(WFSCAMCAPS_W&, const unsigned long) noexcept = 0;

		virtual long getStatus_async(unsigned long&, const unsigned long) noexcept = 0;
		virtual long getCapabilities_async(unsigned long&, const unsigned long) noexcept = 0;

		/* CAM Execute Functions */
		virtual long takePicture_sync(const WFSCAMTAKEPICT_W&, const unsigned long) noexcept = 0;
		virtual long reset_sync(const unsigned long) noexcept = 0;

		virtual long takePicture_async(const WFSCAMTAKEPICT_W&, unsigned long&, const unsigned long) noexcept = 0;
		virtual long reset(unsigned long&, const unsigned long) noexcept = 0;
	};
} // !__N_XFSCAM_W__

#endif // !__H_IXFSCAM_W__