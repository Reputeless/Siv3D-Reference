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
# include <utility>
# include "Types.hpp"

namespace s3d
{
	/// <summary>
	/// 波形のサンプルデータ
	/// </summary>
	struct WaveSample
	{
# pragma warning ( disable: 4201 )
		union
		{
			uint32 _left_right;
			float  _asFloat32;

			struct
			{
				int32 left : 16;
				int32 right : 16;
			};
		};
# pragma warning ( default: 4201 )

		WaveSample() = default;

		explicit WaveSample(int32 mono)
			: WaveSample(mono, mono) {}

		WaveSample(int32 _left, int32 _right)
			: left(_left & 0xffFF)
			, right(_right & 0xffFF) {}

		WaveSample& operator = (const WaveSample& sample) = default;

		WaveSample& operator = (int32 mono)
		{
			left = right = mono;
			return *this;
		}

		WaveSample& set(int32 mono)
		{
			left = right = mono;
			return *this;
		}

		WaveSample& set(int32 _left, int32 _right)
		{
			left = _left;	
			right = _right;			
			return *this;
		}

		void swapChannel()
		{
			const int tmp = left;
			left = right;
			right = tmp;
		}
	};
}
