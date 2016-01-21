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
# include "Array.hpp"
# include "String.hpp"
# include "Image.hpp"
# include "Wave.hpp"

namespace s3d
{
	namespace Threading
	{
		Array<Image> LoadImages(const Array<FilePath>& paths);

		bool SaveImages(const Array<Image>& images, const Array<FilePath>& paths);

		Array<Wave> LoadWaves(const Array<FilePath>& paths);

		bool SaveWaves(const Array<Wave>& waves, const Array<FilePath>& paths);
	}
}
