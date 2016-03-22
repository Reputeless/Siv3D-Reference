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
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// 
	/// </summary>
	class VideoPlayer
	{
	private:

		class CVideoPlayer;

		std::shared_ptr<CVideoPlayer> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		VideoPlayer();

		explicit VideoPlayer(const FilePath& path, bool loop = true, bool useSRGB = false);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~VideoPlayer();

		bool open(const FilePath& path, bool loop = true, bool useSRGB = false);

		void close();

		explicit operator bool() const
		{
			return isOpened();
		}

		bool isOpened() const;

		void update();

		void play();

		void pause();

		void stop();

		bool isPlaying() const;

		const Size& getSize() const;

		const Image& getFrameImage() const;

		const Texture& getFrameTexture() const;

		bool hasNewFrame() const;

		double getLengthSec() const;

		int32 getLengthFrame() const;

		int32 getPosFrame() const;

		double getPosSec() const;

		void setPosFrame(int32 frame);

		void setPosSec(double posSec);

		double getVolume() const;

		void setVolume(double volume);

		FilePath path() const;
	};
}
