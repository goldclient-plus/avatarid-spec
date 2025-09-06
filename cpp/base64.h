/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#pragma once

namespace base64 {
	uint32_t GetEncodeMaxOutput(uint32_t cubData);
	bool Encode(const uint8_t *pubData, uint32_t cubData, char *pchEncodedData, uint32_t *pcchEncodedData, bool bURLSafe = false);

	uint32_t GetDecodeMaxOutput(uint32_t cubData);
	bool Decode(const char *pchEncodedData, uint32_t cchEncodedData, uint8_t *pubDecodedData, uint32_t *pcubDecodedData, bool bURLSafe = false);

#if defined(UTLBUFFER_H)
	// Encode/decode helpers using CUtlBuffer
	bool DecodeToBuf(const char *pszEncoded, uint32_t cbEncoded, CUtlBuffer &buf);
	bool EncodeToBuf(uint8_t *pubData, uint32_t cubData, CUtlBuffer &buf);
#endif
}
