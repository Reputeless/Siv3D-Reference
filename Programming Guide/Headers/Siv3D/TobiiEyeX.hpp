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
# include "PointVector.hpp"

namespace s3d
{
	struct EyeXState
	{
		Vec3 leftEyePos;
		
		Vec3 leftEyeNormalized;
		
		Vec3 rightEyePos;
		
		Vec3 rightEyeNormalized;
		
		Point screenGazePos;
		
		Point screenFixationPos;
		
		Vec2 clientGazePos;
		
		Vec2 clientFixationPos;

		Vec2 displaySize;

		Point screenBounds;

		bool userPresence;
	};

	namespace TobiiEyeX
	{
		bool IsAvailable();

		bool Start();

		void Stop();

		bool HasNewState();

		bool GetState(EyeXState& state);
	}
}
