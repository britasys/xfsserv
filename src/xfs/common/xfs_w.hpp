#pragma once

#ifndef __H_XFS_W__
#define __H_XFS_W__

/****** xfs **********************************************/
#include <xfs/common/xfs_headers/xfsapi.h>
#include <xfs/common/xfsdef.hpp>

#pragma comment(lib, "msxfs")
// #pragma comment(lib, "xfs_conf")
// #pragma comment(lib, "xfs_supp")

/****** std **********************************************/
#include <vector>
#include <string>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace __N_XFS_W__
{

#pragma pack(push, 1)

    typedef struct _wfs_lpsz_extra_w
    {
    private:
        std::vector<std::string> extra{};

    public:
        // assign
        void assign(LPSTR lpszExtra) noexcept(false)
        {
            if (!lpszExtra) throw std::invalid_argument("lpszExtra is NULL");
		    
		    size_t l_index_1 = 0;
            while (lpszExtra[l_index_1])
            {
		        size_t l_index_2 = l_index_1;
                while (lpszExtra[l_index_2])
                    l_index_2++;
                
                std::string l_temp{ lpszExtra + l_index_1, l_index_2 - l_index_1 };
                this->extra.push_back(l_temp);

                l_index_1 += l_temp.size() + 1;           // first NULL
                if (NULL == lpszExtra[l_index_1] + 1)     // second NULL
                    break;
            }
        }

        // default contructor
        _wfs_lpsz_extra_w() = default;

        // copy constructor
        _wfs_lpsz_extra_w(const _wfs_lpsz_extra_w&) = default;

        // move constructor
        _wfs_lpsz_extra_w(_wfs_lpsz_extra_w&&) = default;

        // copy assignment
        _wfs_lpsz_extra_w& operator = (const _wfs_lpsz_extra_w&) = default;

        // move assignment
        _wfs_lpsz_extra_w& operator = (_wfs_lpsz_extra_w&&) = default;

        // noraml constructor
        _wfs_lpsz_extra_w(LPSTR lpstr) noexcept(false)
        {
            if (!lpstr) throw std::invalid_argument("lpstr is NULL");
            this->assign(lpstr);
        }

        // destructor
        virtual ~_wfs_lpsz_extra_w() = default;

        // to_original
        LPSTR to_original() noexcept
        {
            return nullptr;
        }

        // to_string
        std::string to_string() const noexcept
        {
		    std::stringstream l_stream;
		    for (const auto & elem : extra)
		    	l_stream << elem << ' ';
		    return l_stream.str();
        }

        // size
        size_t size() const noexcept
        {
		    return this->extra.size();
        }

        // [] operator
        std::string operator [] (const int& index)
        {
            if (this->extra.size() <= index) throw std::invalid_argument("index not exist");
            return this->extra[index];
        }

        // << operator
        friend std::ostream& operator << (std::ostream& out, const _wfs_lpsz_extra_w& obj) noexcept
        {
            for(const auto& elem : obj.extra)
                out << elem << " ";
            return out;
        }
    } WFSLPSZEXTRA_W, * LPWFSLPSZEXTRA_W;

#pragma pack(pop)

} // !__N_XFS_W__

#endif // !__H_XFS_W__