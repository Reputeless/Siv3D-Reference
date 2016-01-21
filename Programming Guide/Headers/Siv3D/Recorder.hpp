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
# include "String.hpp"
# include "Array.hpp"
# include "Duration.hpp"

namespace s3d
{
	/// <summary>
	/// 録音のサンプリングレート
	/// </summary>
	enum class RecordingFormat
	{
		/// <summary>
		/// ステレオ 11,025 Hz
		/// </summary>
		S11025 = 0x00000008,

		/// <summary>
		/// ステレオ 22,050 Hz
		/// </summary>
		S22050 = 0x00000080,

		/// <summary>
		/// ステレオ 44,100 Hz
		/// </summary>
		S44100 = 0x00000800,

		/// <summary>
		/// ステレオ 48,000 Hz
		/// </summary>
		S48000 = 0x00008000,

		/// <summary>
		/// ステレオ 96,000 Hz
		/// </summary>
		S96000 = 0x00080000,

		/// <summary>
		/// デフォルト [ステレオ 44,100 Hz]
		/// </summary>
		Default = S44100,
	};

	/// <summary>
	/// 録音デバイスの情報
	/// </summary>
	struct RecorderInfo
	{
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		RecorderInfo() = default;

		/// <summary>
		/// エンジン内部で使用するコンストラクタ
		/// </summary>
		RecorderInfo(const String& _name, int32 _format, int32 _channels, uint32 _deviceID)
			: name(_name)
			, format(_format)
			, channels(_channels)
			, deviceID(_deviceID) {}

		/// <summary>
		/// デバイス名
		/// </summary>
		/// <remarks>
		/// 文字数によっては名前が途中で切られている場合があります。
		/// </remarks>
		String name;

		/// <summary>
		/// 対応した録音フォーマット（RecorderFormat::Type の組み合わせ）
		/// </summary>
		int32 format = 0;

		/// <summary>
		/// 録音できるチャンネル数
		/// </summary>
		int32 channels = 0;

		/// <summary>
		/// 
		/// </summary>
		uint32 deviceID = 0;
	};

	/// <summary>
	/// マイク録音
	/// </summary>
	/// <remarks>
	/// 録音に関する機能を提供します。
	/// </remarks>
	class Recorder
	{
	private:

		class CRecorder;

		std::shared_ptr<CRecorder> pImpl;
	
	public:

		Recorder();

		Recorder(size_t sample, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		Recorder(const SecondsF& length, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		Recorder(int32 deviceID, size_t sample, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		Recorder(int32 deviceID, const SecondsF& length, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		~Recorder();

		bool open(size_t sample, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		bool open(const SecondsF& length, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		bool open(int32 deviceID, size_t sample, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		bool open(int32 deviceID, const SecondsF& length, RecordingFormat format = RecordingFormat::S44100, bool loop = false);

		explicit operator bool() const
		{
			return isOpened();
		}

		bool isOpened() const;

		void close();

		/// <summary>
		/// 録音を開始します。
		/// </summary>
		/// <returns>
		/// 録音の開始に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool start();

		/// <summary>
		/// 録音を終了します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void stop();

		uint32 lengthSmaple() const;

		/// <summary>
		/// 録音しているバッファの現在の位置を返します。
		/// </summary>
		/// <returns>
		/// 録音しているバッファの現在の位置
		/// </returns>
		uint32 getPosSample() const;

		/// <summary>
		/// 録音を保存しているバッファにアクセスします。
		/// </summary>
		/// <remarks>
		/// 録音中は、GetPos() が返す位置以降のサンプルにアクセスしてはいけません。
		/// </remarks>
		/// <returns>
		/// 録音を保存しているバッファ
		/// </returns>
		const Wave& getWave() const;

		/// <summary>
		/// 録音がバッファの終端に達して終了しているかを返します。
		/// </summary>
		/// <returns>
		/// 録音がバッファの終端に達して終了している場合 true, それ以外の場合は false
		/// </returns>
		bool isEnded() const;

		bool isLoop() const;

		int32 deviceID() const;

		/// <summary>
		/// 録音している音声の直近の最大振幅を返します。
		/// </summary>
		/// <param name="duration">
		/// 計測する直近の波形の範囲（秒） [0.001, 1.0]
		/// </param>
		/// <returns>
		/// 音声の直近の最大振幅 [0.0, 1.0]
		/// </returns>
		double getMaxAmplitude(_Field_range_(SecondsF(0.001), SecondsF(1.0)) const SecondsF& duration = SecondsF(0.02)) const;

		/// <summary>
		/// 録音している音声の直近の平均振幅を返します。
		/// </summary>
		/// <param name="duration">
		/// 計測する直近の波形の範囲（秒） [0.001, 1.0]
		/// </param>
		/// <returns>
		/// 音声の直近の平均振幅 [0.0, 1.0]
		/// </returns>
		double getAverageAmplitude(_Field_range_(SecondsF(0.001), SecondsF(1.0)) const SecondsF& duration = SecondsF(0.02)) const;
	};

	namespace RecorderManager
	{
		/// <summary>
		/// PC に接続されている録音デバイスの一覧を取得します。
		/// </summary>
		/// <returns>
		/// PC に接続されている録音デバイスの一覧
		/// </returns>
		Array<RecorderInfo> Enumerate();
	}
}
