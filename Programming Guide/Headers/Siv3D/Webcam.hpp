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
# include "Array.hpp"
# include "PointVector.hpp"
# include "AR.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// Web カメラの情報
	/// </summary>
	struct WebcamInfo
	{
		/// <summary>
		/// Web カメラの名称
		/// </summary>
		String name;

		/// <summary>
		/// デバイス ID
		/// </summary>
		int32 deviceID = 0;
	};

	class Webcam
	{
	private:

		class CWebcamDetail;

		std::shared_ptr<CWebcamDetail> pImpl;

	public:

		Webcam();

		Webcam(int32 deviceID, const Size& resolution = Size(640, 480));

		~Webcam();

		bool open(int32 deviceID, const Size& resolution = Size(640, 480));

		explicit operator bool() const
		{
			return isOpened();
		}

		bool isOpened() const;

		bool start();

		void pause();

		void resume();

		void stop();

		void close();

		bool isActive() const;

		bool isPaused() const;

		bool hasNewFrame();

		bool getFrame(Image& image);

		bool getFrame(DynamicTexture& texture);

		int32 deviceID() const;

		Size resolution() const;



		bool startAR(double markerSizeMeter = 0.05, const FilePath& calibPath = L"");

		void stopAR();

		void setARMinMax(double min, double max);

		bool hasNewMarkers() const;

		bool getMarkers(Array<ARMarker>& markers, bool mirrored = false);
	};

	/// <summary>
	/// Web カメラ管理
	/// </summary>
	/// <remarks>
	/// Web カメラに関する機能を提供します。
	/// </remarks>
	namespace WebcamManager
	{
		/// <summary>
		/// 利用可能な Web カメラの一覧を取得します。
		/// </summary>
		/// <returns>
		/// 利用可能な Web カメラの一覧
		/// </returns>
		Array<WebcamInfo> Enumerate();

		/// <summary>
		/// Web カメラ使用の認証画面を表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void RequestAccess();

		/// <summary>
		/// Web カメラの使用がユーザによって許可されているかを返します。
		/// </summary>
		/// <returns>
		/// Web カメラの使用がユーザによって許可されている場合 true, それ以外の場合は false
		/// </returns>
		bool Approved();

		/// <summary>
		/// Web カメラの使用がユーザによって拒否されているかを返します。
		/// </summary>
		/// <returns>
		/// Web カメラの使用がユーザによって拒否されている場合 true, それ以外の場合は false
		/// </returns>
		bool Denied();
	}
}
