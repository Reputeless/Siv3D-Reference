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
# include "Wave.hpp"

namespace s3d
{
	/// <summary>
	/// FFT サンプル数
	/// </summary>
	enum class FFTSampleLength
	{
		/// <summary>
		/// 256 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 172Hz
		/// </remarks>
		SL256,

		/// <summary>
		/// 512 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 86.1Hz
		/// </remarks>
		SL512,

		/// <summary>
		/// 1024 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 43.1Hz
		/// </remarks>
		SL1K,

		/// <summary>
		/// 2048 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 21.5Hz
		/// </remarks>
		SL2K,

		/// <summary>
		/// 4096 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 10.8Hz
		/// </remarks>
		SL4K,

		/// <summary>
		/// 8192 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 5.38Hz
		/// </remarks>
		SL8K,

		/// <summary>
		/// 16384 サンプル
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 2.69Hz
		/// </remarks>
		SL16K,

		/// <summary>
		/// デフォルト (8192 サンプル)
		/// </summary>
		/// <remarks>
		/// 44.1kHz のサウンドに対して周波数分解能 5.38Hz
		/// </remarks>
		Default = SL8K
	};

	/// <summary>
	/// FFT の結果
	/// </summary>
	class FFTResult
	{
	private:

		double m_resolution = Wave::DefaultSamplingRate / 8192.0;

		int32 m_bufferLength = 0;

		int32 m_samplingRate = Wave::DefaultSamplingRate;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		FFTResult() = default;

		/// <summary>
		/// 内部で使用するコンストラクタ
		/// </summary>
		FFTResult(int32 _bufferLength, int32 _samplingRate, FFTSampleLength _sampleLength, const float* _buffer);

		/// <summary>
		/// FFT の結果の先頭ポインタ
		/// </summary>
		const float* buffer = nullptr;

		/// <summary>
		/// 周波数分解能
		/// </summary>
		double resolution() const { return m_resolution; }

		/// <summary>
		/// FFT の結果 (buffer) の要素数
		/// </summary>
		int32 length() const { return m_bufferLength; }

		/// <summary>
		/// FFT 対象のサンプリングレート
		/// </summary>
		int32 samplingRate() const { return m_samplingRate; }
	};

	namespace FFT
	{
		/// <summary>
		/// FFT を実行します。
		/// </summary>
		/// <param name="sound">
		/// 入力のサウンド
		/// </param>
		/// <param name="sampleLength">
		/// FFT サンプル数
		/// </param>
		/// <returns>
		/// FFT の結果
		/// </returns>
		FFTResult Analyze(const Sound& sound, FFTSampleLength sampleLength = FFTSampleLength::Default);

		/// <summary>
		/// FFT を実行します。
		/// </summary>
		/// <param name="wave">
		/// 入力の波形
		/// </param>
		/// <param name="pos">
		/// 波形中の位置（サンプル）
		/// </param>
		/// <param name="sampleLength">
		/// FFT サンプル数
		/// </param>
		/// <returns>
		/// FFT の結果
		/// </returns>
		FFTResult Analyze(const Wave& wave, uint32 pos, FFTSampleLength sampleLength = FFTSampleLength::Default);

		FFTResult Analyze(const Recorder& recorder, FFTSampleLength sampleLength = FFTSampleLength::Default);

		/// <summary>
		/// FFT を実行します。
		/// </summary>
		/// <param name="data">
		/// 入力のデータ
		/// </param>
		/// <param name="length">
		/// データの長さ（サンプル）
		/// </param>
		/// <param name="samplingRate">
		/// データのサンプリングレート
		/// </param>
		/// <param name="sampleLength">
		/// FFT サンプル数
		/// </param>
		/// <returns>
		/// FFT の結果
		/// </returns>
		FFTResult Analyze(const float* data, uint32 length, uint32 samplingRate, FFTSampleLength sampleLength = FFTSampleLength::Default);
	}
}
