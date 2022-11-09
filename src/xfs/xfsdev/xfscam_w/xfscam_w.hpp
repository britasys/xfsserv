#pragma once

#ifndef __H_XFSCAM_W__
#define __H_XFSCAM_W__

#include <xfscam.h>

#include <utility.hpp>
#include <xfs_w.hpp>

#include <sstream>
#include <ostream>
#include <string>

namespace __N_XFSCAM_W__
{

#pragma pack(push, 1)

	/*=================================================================*/
	/* CAM Info Command Structures */
	/*=================================================================*/

	typedef struct _wfs_cam_status_w : public _wfs_cam_status
	{
        //lpszExtra
        __N_XFS_W__::WFSLPSZEXTRA_W wfslpszextra_w{};

        // assign
        void assign(const _wfs_cam_status& obj) noexcept(false)
        {
			this->fwDevice = obj.fwDevice;
			SAFECOPYMEMORY(this->fwMedia, obj.fwMedia, WFS_CAM_CAMERAS_SIZE * sizeof(WORD));
			SAFECOPYMEMORY(this->fwCameras, obj.fwCameras, WFS_CAM_CAMERAS_SIZE * sizeof(WORD));
			SAFECOPYMEMORY(this->usPictures, obj.usPictures, WFS_CAM_CAMERAS_SIZE * sizeof(USHORT));
            if (obj.lpszExtra) this->wfslpszextra_w.assign(obj.lpszExtra);
        }

        // assign
        void assign(void* lpBuffer) noexcept(false)
        {
            if (!lpBuffer) throw std::invalid_argument("lpBuffer is NULL");
            auto l_lpBuffer = static_cast<LPWFSCAMSTATUS>(lpBuffer);
            this->assign(*l_lpBuffer);
        }

        // << operator
		friend std::ostream& operator<< (std::ostream& out, const _wfs_cam_status_w& obj)
		{
			out << " fwDevice: "    << obj.fwDevice
				<< " fwMedia: "     << __N_UTILITY__::Array2Str(obj.fwMedia, WFS_CAM_CAMERAS_SIZE)
				<< " fwCameras: "   << __N_UTILITY__::Array2Str(obj.fwCameras, WFS_CAM_CAMERAS_SIZE)
				<< " usPictures: "  << __N_UTILITY__::Array2Str(obj.usPictures, WFS_CAM_CAMERAS_SIZE)
				<< " lpszExtra: "   << obj.wfslpszextra_w.to_string();

			return out;
		}
	} WFSCAMSTATUS_W, * LPWFSCAMSTATUS_W;

	typedef struct _wfs_cam_caps_w : public _wfs_cam_caps
	{
        //lpszExtra
        __N_XFS_W__::WFSLPSZEXTRA_W wfslpszextra_w{};

        // assign
        void assign(const _wfs_cam_caps& obj) noexcept
        {
			this->wClass = obj.wClass;
			this->fwType = obj.fwType;
			SAFECOPYMEMORY(this->fwCameras, obj.fwCameras, WFS_CAM_CAMERAS_SIZE * sizeof(WORD));
			this->usMaxPictures = obj.usMaxPictures;
			this->fwCamData = obj.fwCamData;
			this->usMaxDataLength = obj.usMaxDataLength;
			this->fwCharSupport = obj.fwCharSupport;
            if (obj.lpszExtra) this->wfslpszextra_w.assign(obj.lpszExtra);
        }

        // assign
        void assign(void* lpBuffer) noexcept(false)
        {
            if (!lpBuffer) throw std::invalid_argument("lpBuffer is NULL");
            auto l_lpBuffer = static_cast<LPWFSCAMCAPS>(lpBuffer);
            this->assign(*l_lpBuffer);
        }

        // << operator
		friend std::ostream& operator<< (std::ostream& out, const _wfs_cam_caps_w& obj)
		{
			out << " wClass: "          << obj.wClass
				<< " fwType: "          << obj.fwType
				<< " fwCameras: "       << __N_UTILITY__::Array2Str(obj.fwCameras, WFS_CAM_CAMERAS_SIZE)
				<< " usMaxPictures: "   << obj.usMaxPictures
				<< " fwCamData: "       << obj.fwCamData
				<< " usMaxDataLength: " << obj.usMaxDataLength
				<< " fwCharSupport: "   << obj.fwCharSupport
				<< " lpszExtra: "       << obj.wfslpszextra_w.to_string();
			return out;
		}
	} WFSCAMCAPS_W, * LPTTWFSCAMCAPS_W;

	/*=================================================================*/
	/* CAM Execute Command Structures */
	/*=================================================================*/

	typedef struct _wfs_cam_take_picture_w : public _wfs_cam_take_picture
	{
        // assign
        void assign(const _wfs_cam_take_picture& obj) noexcept
        {
			this->wCamera = obj.wCamera;
			if (obj.lpszCamData)
				SAFEALLOCCOPYSTRING(&this->lpszCamData, std::string{ obj.lpszCamData });
			if (obj.lpszUNICODECamData)
				SAFEALLOCCOPYSTRING(&this->lpszUNICODECamData, std::wstring{ obj.lpszUNICODECamData });
        }

        // default constructor
        _wfs_cam_take_picture_w() = default;

        // normal constructor
        _wfs_cam_take_picture_w(void* lpBuffer) noexcept(false)
        {
            if (!lpBuffer) throw std::invalid_argument("lpBuffer is NULL");
            auto l_lpBuffer = static_cast<LPWFSCAMTAKEPICT>(lpBuffer);
            this->assign(*l_lpBuffer);
        }

        // destructor
		~_wfs_cam_take_picture_w() 
		{
			SAFEFREEMEMORY(&this->lpszCamData)
			SAFEFREEMEMORY(&this->lpszUNICODECamData)
		}
        
        // << operator
		friend std::ostream& operator<< (std::ostream& out, const _wfs_cam_take_picture_w& obj)
		{
			out << " wCamera: " << obj.wCamera
				<< " lpszCamData: " << std::string{ obj.lpszCamData }
				<< " lpszUNICODECamData: " << std::string{ std::wstring{ obj.lpszUNICODECamData }.begin(), std::wstring{ obj.lpszUNICODECamData }.end() };
			return out;
		}
	} WFSCAMTAKEPICT_W, * LPWFSCAMTAKEPICT_W;

#pragma pack(pop)
}

#endif // !__H_ITTCAM_H