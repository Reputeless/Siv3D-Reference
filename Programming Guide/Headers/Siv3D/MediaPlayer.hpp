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
	namespace experimental
	{
		namespace MediaPlayer
		{
			bool Open(const FilePath& path);

			bool Play();

			bool Play(const Rect& region);

			void Pause();

			void Stop();

			bool IsPlaying();

			void SetVolume(double volume);

			double GetVolume();

			bool HasVideo();

			bool HasAudio();

			double GetLengthSec();

			double GetPosSec();

			const Size& GetVideoSize();

			bool GetFrame(Image& image);
		}
	}
}
