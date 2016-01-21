//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iostream>
# include <sstream>
# include "Fwd.hpp"
# include "String.hpp"
# include "Format.hpp"

namespace s3d
{
	enum class NetworkErrorCode
	{
		OK,

		EoF,

		NoBufferSpace,

		ConnectionRefused,

		OtherError,
	};

	union IPv4
	{
		uint32 asUint = 0;

		uint8 asUint8[4];

		IPv4() = default;

		explicit IPv4(uint32 value)
			: asUint(value) {}

		IPv4(uint8 b1, uint8 b2, uint8 b3, uint8 b4)
			: asUint8{ b1,b2,b3,b4 } {}

		explicit IPv4(const String& ipv4)
		{
			std::wistringstream(ipv4.str()) >> *this;
		}

		static IPv4 localhost()
		{
			return{ 127,0,0,1 };
		}

		String str() const
		{
			return Format(asUint8[0], L'.', asUint8[1], L'.', asUint8[2], L'.', asUint8[3]);
		}
	};

	template <class CharType>
	inline std::basic_ostream<CharType>& operator << (std::basic_ostream<CharType>& os, const IPv4& ipv4)
	{
		return	os
			<< ipv4.asUint8[0] << CharType('.')
			<< ipv4.asUint8[1] << CharType('.')
			<< ipv4.asUint8[2] << CharType('.')
			<< ipv4.asUint8[3];
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >> (std::basic_istream<CharType>& is, IPv4& ipv4)
	{
		CharType unused;
		uint32 b1 = 0, b2 = 0, b3 = 0, b4 = 0;
		is	>> b1 >> unused
			>> b2 >> unused
			>> b3 >> unused
			>> b4;

		ipv4.asUint8[0] = static_cast<uint8>(b1);
		ipv4.asUint8[1] = static_cast<uint8>(b2);
		ipv4.asUint8[2] = static_cast<uint8>(b3);
		ipv4.asUint8[3] = static_cast<uint8>(b4);

		return is;
	}

	namespace Network
	{
		Optional<IPv4> GetPrivateIPv4();

		Optional<IPv4> GetGlobalIPv4();
	}
}
