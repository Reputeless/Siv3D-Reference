//-----------------------------------------------
//
//	Originally based on
//	Formatting library for C++
//
//	Copyright (c) 2012 - 2014, Victor Zverovich
//	All rights reserved.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//
//	1. Redistributions of source code must retain the above copyright notice, this
//	list of conditions and the following disclaimer.
//	2. Redistributions in binary form must reproduce the above copyright notice,
//	this list of conditions and the following disclaimer in the documentation
//	and/or other materials provided with the distribution.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-----------------------------------------------
//
//	Copyright (C) 2015 Ryo Suzuki
//
//	- Modified for Siv3D
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"

namespace s3d
{
	namespace detail
	{
		struct IntDigits
		{
			static const char DIGITS[];
		};

		class FormatInt
		{
		private:

			enum { BUFFER_SIZE = std::numeric_limits<uint64>::digits10 + 3 };

			mutable wchar buffer_[BUFFER_SIZE];

			wchar* str_;

			wchar* format_decimal(uint64 value)
			{
				wchar *buffer_end = buffer_ + BUFFER_SIZE - 1;

				while (value >= 100)
				{
					uint32 index = (value % 100) * 2;
					value /= 100;
					*--buffer_end = IntDigits::DIGITS[index + 1];
					*--buffer_end = IntDigits::DIGITS[index];
				}

				if (value < 10)
				{
					*--buffer_end = static_cast<char>('0' + value);
					return buffer_end;
				}

				uint32 index = static_cast<uint32>(value * 2);
				*--buffer_end = IntDigits::DIGITS[index + 1];
				*--buffer_end = IntDigits::DIGITS[index];
				return buffer_end;
			}

			void formatSigned(int64 value)
			{
				uint64 abs_value = static_cast<uint64>(value);
				bool negative = value < 0;
				if (negative)
					abs_value = 0 - abs_value;
				str_ = format_decimal(abs_value);
				if (negative)
					*--str_ = '-';
			}

		public:

			explicit FormatInt(int32 value) { formatSigned(value); }

			explicit FormatInt(int64 value) { formatSigned(value); }

			explicit FormatInt(uint32 value) : str_(format_decimal(value)) {}

			explicit FormatInt(uint64 value) : str_(format_decimal(value)) {}

			std::size_t size() const { return buffer_ - str_ + BUFFER_SIZE - 1; }

			const wchar *data() const { return str_; }

			const wchar *c_str() const
			{
				buffer_[BUFFER_SIZE - 1] = '\0';
				return str_;
			}

			String str() const { return String(str_, size()); }
		};
	}
}
