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
# include "String.hpp"
# include "Image.hpp"

namespace s3d
{
	/// <summary>
	/// ログファイルの詳細度
	/// </summary>
	enum class OutputLevel
	{
		/// <summary>
		/// 低
		/// </summary>
		Less,

		/// <summary>
		/// 通常
		/// </summary>
		Normal,

		/// <summary>
		/// 高
		/// </summary>
		More,
	};

	namespace Logger
	{
		[[deprecated("** Logger::Write(image, str) is a deprecated function. Use LOG(image, str) instead. **")]]
		void Write(const Image& image, const String& str = L"");

		/// <summary>
		/// ログファイルの詳細度を設定します。
		/// </summary>
		/// <param name="level">
		/// 詳細度
		/// </param>
		/// <remarks>
		/// 詳細度を高く設定すると、より多くのメッセージが出力されます。
		/// デフォルトの設定は、Debug ビルド時は More, Release ビルド時は Normal です。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetOutputLevel(OutputLevel level);

		/// <summary>
		/// ログファイルに出力する画像の縦横の最大サイズを設定します。
		/// </summary>
		/// <param name="maxSize">
		/// 画像の１辺の最大ピクセル数。デフォルトでは 256
		/// </param>
		/// <remarks>
		/// このサイズを上回る画像は縮小されて出力されます。
		/// maxSize は [1-Image::MaxSize] の範囲にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetMaxImageSize(int32 maxSize);

		/// <summary>
		/// ログファイルに出力する画像の圧縮品質を[0-100] の範囲で指定します。
		/// </summary>
		/// <param name="quality">
		/// 画像の圧縮品質。[0-99] の場合 JPEG, 100 の場合 PNG 圧縮されます。デフォルトでは 75
		/// </param>
		/// <remarks>
		/// quality は [0-100] の範囲にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetImageQuality(int32 quality);

		/// <summary>
		/// Visual Studio の出力ウィンドウに Image をアスキーアートで出力するかどうかを設定します。
		/// </summary>
		/// <param name="enabled">
		/// 出力する場合 true, 出力しない場合は false
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void EnableAsciiArt(bool enabled);
	}
}

# include "Format.hpp"
# include "Logger.inl"

# if defined(_DEBUG) || defined(S3D_LOG_DEBUG)

	/// <summary>
	/// データを文字列に変換し、通常のログとして出力します。
	/// </summary>
	#  define LOG(...)			s3d::OutputLog(s3d::LogDescription::App,__VA_ARGS__)

	/// <summary>
	/// データを文字列に変換し、デバッグログとして出力します。
	/// </summary>
	#  define LOG_DEBUG(...)	s3d::OutputLog(s3d::LogDescription::Debug,__VA_ARGS__)

	/// <summary>
	/// データを文字列に変換し、エラーログとして出力します。
	/// </summary>
	#  define LOG_ERROR(...)	s3d::OutputLog(s3d::LogDescription::Error,__VA_ARGS__)

	/// <summary>
	/// データを文字列に変換し、実行中 1 度だけ通常のログとして出力します。
	/// </summary>
	#  define LOG_ONCE(...)		s3d::OutputLogOnce(s3d::LogDescription::App,__COUNTER__,__VA_ARGS__)

# else

	/// <summary>
	/// データを文字列に変換し、通常のログとして出力します。
	/// </summary>
	#  define LOG(...)			s3d::OutputLog(s3d::LogDescription::App,__VA_ARGS__)

	/// <summary>
	/// リリースビルドでは何も出力しません。
	/// </summary>
	#  define LOG_DEBUG(...)	__noop

	/// <summary>
	/// データを文字列に変換し、エラーログとして出力します。
	/// </summary>
	#  define LOG_ERROR(...)	s3d::OutputLog(s3d::LogDescription::Error,__VA_ARGS__)

	/// <summary>
	/// データを文字列に変換し、通常のログとして出力します。
	/// </summary>
	#  define LOG_ONCE(...)		s3d::OutputLogOnce(s3d::LogDescription::App,__COUNTER__,__VA_ARGS__)

# endif
