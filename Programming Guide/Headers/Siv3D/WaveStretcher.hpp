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

namespace s3d
{
	class WaveStretcher
	{
	private:

		class CWaveStretcher;

		std::shared_ptr<CWaveStretcher> pImpl;

	public:

		WaveStretcher();

		WaveStretcher(uint32 inputSamplingRate);

		void set(double targetTempo, double targetPitchSemitones, uint32 targetSamplingRate);

		bool send(const WaveSample* src, size_t srcLength, bool reachEnd);

		size_t available();

		size_t receive(WaveSample* dst, size_t dstLength);

		size_t receive(float* dst, size_t dstSamples);

		bool isEnd();

		void reset(uint32 inputSamplingRate);

		uint32 getInputSamplingRate() const;

		CWaveStretcher* _detail() const;
	};

	namespace Waving
	{
		bool TempoAndPitchAvailable();

		/// <summary>
		/// テンポを変更した Wave を返します。
		/// </summary>
		/// <param name="wave">
		/// 元の Wave
		/// </param>
		/// <param name="tempo">
		/// 1.0 を基準としたテンポ。小さいと遅く、大きいと速くなる　[0.1, 10.0]
		/// </param>
		/// <returns>
		/// テンポを変更した Wave
		/// </returns>
		void ChangeTempo(const Wave& src, Wave& dst, double tempo);

		/// <summary>
		/// ピッチを変更した Wave を返します。
		/// </summary>
		/// <param name="wave">
		/// 元の Wave
		/// </param>
		/// <param name="pitchSemitones">
		/// ピッチの変更 (半音上げる場合は 1.0, 1 オクターブ上げる場合は 12.0, 半音下げる場合は -1.0)
		/// </param>
		/// <returns>
		/// ピッチを変更した Wave
		/// </returns>
		void ChangePitchSemitones(const Wave& src, Wave& dst, double pitchSemitones);

		void ChangeTempoAndPitchSemitones(const Wave& src, Wave& dst, double tempo, double pitchSemitones);

		/// <summary>
		/// サンプリングレートを変更した Wave を返します。
		/// </summary>
		/// <param name="wave">
		/// 元の Wave
		/// </param>
		/// <param name="samplingRate">
		/// サンプリングレート
		/// </param>
		/// <returns>
		/// サンプリングレートを変更した Wave
		/// </returns>
		void ChangeSamplingRate(const Wave& src, Wave& dst, uint32 samplingRate);
	}
}
