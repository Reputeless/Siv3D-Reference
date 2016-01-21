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
# include "Fwd.hpp"

namespace s3d
{
	struct BeatCount
	{
		int32 bar;

		int32 beat;

		double f;
	};

	class SoundBeat
	{
	private:

		int32 m_offsetSample = 0;

		int32 m_bpm = 120;

	public:

		SoundBeat() = default;

		explicit SoundBeat(int32 offsetSample, int32 bpm = 120);

		BeatCount operator()(const Sound& sound, int32 a = 4, int32 b = 4) const;
	};
}
