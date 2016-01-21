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
# include "Handle.hpp"
# include "PropertyMacro.hpp"
# include "Math.hpp"
# include "Duration.hpp"
# include "Optional.hpp"

namespace s3d
{
	/// <summary>
	/// サウンドのループ設定
	/// </summary>
	struct SoundLoop
	{
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		SoundLoop() = default;

		/// <summary>
		/// サウンドのループを設定します。
		/// </summary>
		/// <param name="_loop">
		/// 
		/// </param>
		explicit SoundLoop(bool _loop)
			: beginSample(0)
			, endSample(0)
			, loop(_loop) {}

		/// <summary>
		/// サウンドのループを設定します。
		/// </summary>
		/// <param name="_beginSample">
		/// ループ範囲の始点（サンプル）
		/// </param>
		/// <param name="_endSample">
		/// ループ範囲の終点（サンプル）、曲の最後までをループさせる場合は 0
		/// </param>
		SoundLoop(int64 _beginSample, int64 _endSample)
			: beginSample(_beginSample)
			, endSample(_endSample)
			, loop(true) {}

		/// <summary>
		/// サウンドのループを設定します。
		/// </summary>
		/// <param name="_loop">
		/// ループの有無
		/// </param>
		/// <param name="_beginSample">
		/// ループ範囲の始点（サンプル）
		/// </param>
		/// <param name="_endSample">
		/// ループ範囲の終点（サンプル）、曲の最後までをループさせる場合は 0
		/// </param>
		SoundLoop(bool _loop, int64 _beginSample, int64 _endSample)
			: beginSample(_loop ? _beginSample : 0)
			, endSample(_loop ? _endSample : 0)
			, loop(_loop) {}

		/// <summary>
		/// サウンドのループを設定します。
		/// </summary>
		/// <param name="_beginSec">
		/// ループ範囲の始点（秒）
		/// </param>
		/// <param name="_endSec">
		/// ループ範囲の終点（秒）、曲の最後までをループさせる場合は 0
		/// </param>
		SoundLoop(SecondsF _beginSec, SecondsF _endSec)
			: beginSec(_beginSec)
			, endSec(_endSec)
			, loop(true) {}

		/// <summary>
		/// サウンドのループを設定します。
		/// </summary>
		/// <param name="_loop">
		/// ループの有無
		/// </param>
		/// <param name="_beginSec">
		/// ループ範囲の始点（秒）
		/// </param>
		/// <param name="_endSec">
		/// ループ範囲の終点（秒）、曲の最後までをループさせる場合は 0
		/// </param>
		SoundLoop(bool _loop, SecondsF _beginSec, SecondsF _endSec)
			: beginSec(_loop ? Optional<SecondsF>() : _beginSec)
			, endSec(_loop ? Optional<SecondsF>() : _endSec)
			, loop(_loop) {}

		enum class Predefined
		{
			None,
			All
		};

		SoundLoop(Predefined predefined);

		/// <summary>
		/// ループしない
		/// </summary>
		/// <remarks>
		/// SoundLoop(false, 0, 0)
		/// </remarks>
		const static Predefined None = Predefined::None;

		/// <summary>
		/// 永久にループ
		/// </summary>
		/// <remarks>
		/// SoundLoop(true, 0, 0)
		/// </remarks>
		const static Predefined All = Predefined::All;

		int64 beginSample = 0;

		int64 endSample = 0;

		Optional<SecondsF> beginSec;

		Optional<SecondsF> endSec;

		bool loop = false;
	};

	struct SoundEmitter
	{
		Vec3 position = Vec3::Zero;

		Vec3 velocity = Vec3::Zero;

		double innerRadius = 0.0;

		double curveDistanceScaler = 1.0;

		double dopplerScaler = 1.0;
	};

	struct SoundListener
	{
		Vec3 position = Vec3::Zero;

		Vec3 velocity = Vec3::Zero;
	};

	/// <summary>
	/// テクスチャの設定
	/// </summary>
	enum class SoundDesc
	{
		Default,

		For3D,
	};

	/// <summary>
	/// サウンド
	/// </summary>
	class Sound
	{
	private:

		class Handle{};

		using SoundHandle = Siv3DHandle<Handle>;

		std::shared_ptr<SoundHandle> m_handle;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Sound();

		/// <summary>
		/// オーディオファイルからサウンドを作成します。
		/// </summary>
		/// <param name="path">
		/// オーディオファイルのパス
		/// </param>
		/// <param name="loop">
		/// サウンドのループ設定
		/// </param>
		/// <param name="maxSpeed">
		/// 最大の再生スピード
		/// </param>
		explicit Sound(const FilePath& path, const SoundLoop& loop = SoundLoop::None, SoundDesc desc = SoundDesc::Default, double maxSpeed = 2.0);

		explicit Sound(IReader&& reader, const SoundLoop& loop = SoundLoop::None, SoundDesc desc = SoundDesc::Default, double maxSpeed = 2.0);

		/// <summary>
		/// 波形データをコピーしてサウンドを作成します。
		/// </summary>
		/// <param name="wave">
		/// 波形データ
		/// </param>
		/// <param name="loop">
		/// サウンドのループ設定
		/// </param>
		/// <param name="maxSpeed">
		/// 最大の再生スピード
		/// </param>
		explicit Sound(const Wave& wave, const SoundLoop& loop = SoundLoop::None, SoundDesc desc = SoundDesc::Default, double maxSpeed = 2.0);

		/// <summary>
		/// 波形データをムーブしてサウンドを作成します。
		/// </summary>
		/// <param name="wave">
		/// 波形データ
		/// </param>
		/// <param name="loop">
		/// サウンドのループ設定
		/// </param>
		/// <param name="maxSpeed">
		/// 最大の再生スピード
		/// </param>
		explicit Sound(Wave&& wave, const SoundLoop& loop = SoundLoop::None, SoundDesc desc = SoundDesc::Default, double maxSpeed = 2.0);

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~Sound();

		/// <summary>
		/// サウンドをリリースします。
		/// </summary>
		/// <remarks>
		/// プログラムのほかの場所で同じサウンドが使われていない場合、サウンドのメモリを解放します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// サウンドが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// サウンドが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return !isEmpty(); }

		/// <summary>
		/// サウンドハンドルの ID を示します。
		/// </summary>
		HandleIDType id() const;

		/// <summary>
		/// サウンドが空かどうかを示します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// 2 つの Sound が同じかどうかを返します。
		/// </summary>
		/// <param name="sound">
		/// 比較する Sound
		/// </param>
		/// <returns>
		/// 2 つの Sound が同じ場合 true, それ以外の場合は false
		/// </returns>
		bool operator == (const Sound& sound) const;

		/// <summary>
		/// 2 つの Sound が異なるかどうかを返します。
		/// </summary>
		/// <param name="sound">
		/// 比較する Sound
		/// </param>
		/// <returns>
		/// 2 つの Sound が異なる場合 true, それ以外の場合は false
		/// </returns>
		bool operator != (const Sound& sound) const;

		/// <summary>
		/// サウンドを現在の設定で再生します。
		/// </summary>
		/// <remarks>
		/// すでに再生されている場合、関数は失敗します。
		/// 同じ Sound を同時に複数再生したい場合は playMuliti() を使います。
		/// </remarks>
		/// <returns>
		/// 再生に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool play(const SecondsF& fadeinDuration = SecondsF(0.0)) const;

		/// <summary>
		/// サウンドを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause(const SecondsF& fadeoutDuration = SecondsF(0.0)) const;

		/// <summary>
		/// サウンドを停止し、再生位置を曲の先頭に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void stop(const SecondsF& fadeoutDuration = SecondsF(0.0)) const;

		/// <summary>
		/// サウンドが再生中であるかを返します。
		/// </summary>
		bool isPlaying() const;

		/// <summary>
		/// サウンドが一時停止中であるかを返します。
		/// </summary>
		bool isPaused() const;

		/// <summary>
		/// ループを含めた再生済みのサンプル数を返します。
		/// </summary>
		int64 samplesPlayed() const;

		/// <summary>
		/// 再生バッファに送信済みのサウンドの位置（サンプル）を返します。
		/// </summary>
		int64 streamPosSample() const;

		/// <summary>
		/// 再生バッファに送信済みのサウンドの位置（秒）を返します。
		/// </summary>
		double streamPosSec() const;

		/// <summary>
		/// サウンドの長さ（サンプル）を返します。
		/// </summary>
		int64 lengthSample() const;

		/// <summary>
		/// サウンドの長さ（秒）を返します。
		/// </summary>
		double lengthSec() const;

		/// <summary>
		/// サウンドのサンプリングレートを示します。
		/// </summary>
		uint32 samplingRate() const;

		/// <summary>
		/// 波形データにアクセスします。
		/// </summary>
		/// <returns>
		/// サウンドの波形データへの参照
		/// </returns>
		const Wave& getWave() const;

		/// <summary>
		/// ループが有効かを示ます。
		/// </summary>
		bool isLoop() const;

		/// <summary>
		/// ループ範囲の始点（サンプル）を示します。
		/// </summary>
		int64 loopBeginSample() const;

		/// <summary>
		/// ループ範囲の終点（サンプル）を示します。
		/// </summary>
		int64 loopEndSample() const;

		/// <summary>
		/// ループの有無を変更します。
		/// </summary>
		/// <param name="loop">
		/// ループの有無
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setLoop(bool loop) const;

		/// <summary>
		/// ループを設定します。
		/// </summary>
		/// <param name="loop">
		/// ループの有無
		/// </param>
		/// <param name="loopBeginSample">
		/// ループ範囲の始点（サンプル）
		/// </param>
		/// <param name="loopEndSample">
		/// ループ範囲の終点（サンプル）、曲の最後までをループさせる場合は 0
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setLoopBySample(bool loop, int64 loopBeginSample, int64 loopEndSample = 0) const;

		/// <summary>
		/// ループを設定します。
		/// </summary>
		/// <param name="loop">
		/// ループの有無
		/// </param>
		/// <param name="loopBeginSec">
		/// ループ範囲の始点（秒）
		/// </param>
		/// <param name="loopEndSec">
		/// ループ範囲の終点（秒）、曲の最後までをループさせる場合は 0
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setLoopBySec(bool loop, const SecondsF& loopBegin, const SecondsF&  loopEnd = SecondsF(0.0)) const;

		void setLoopBySec(bool loop, double loopBeginSec, double loopEndSec = 0.0) const
		{
			setLoopBySec(loop, SecondsF(loopBeginSec), SecondsF(loopEndSec));
		}

		/// <summary>
		/// 再生位置を変更します。
		/// </summary>
		/// <param name="sec">
		/// 再生位置（秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setPosSec(const SecondsF& pos) const;

		/// <summary>
		/// 再生位置を変更します。
		/// </summary>
		/// <param name="sec">
		/// 再生位置（秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setPosSec(double posSec) const
		{
			setPosSec(SecondsF(posSec));
		}

		/// <summary>
		/// 再生位置を変更します。
		/// </summary>
		/// <param name="posSample">
		/// 再生位置（サンプル）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setPosSample(int64 posSample) const;

		/// <summary>
		/// 音量を変更します。
		/// </summary>
		/// <param name="volume">
		/// 音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setVolume(double volume) const;

		/// <summary>
		/// 音量を変更します。
		/// </summary>
		/// <param name="left">
		/// 左チャンネルの音量 [0.0, 1.0]
		/// </param>
		/// <param name="right">
		/// 右チャンネルの音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setVolume(double left, double right) const;

		/// <summary>
		/// 音量を減衰レベル（dB）で設定します。
		/// </summary>
		/// <param name="attenuation_dB">
		/// 減衰レベル（dB）
		/// </param>
		/// <remarks>
		/// atten. = vol.
		/// 0 dB = 1.0
		/// -6 dB = 0.5
		/// -12 dB = 0.25
		/// -18 db = 0.125
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void setAttenuation_dB(double attenuation_dB) const
		{
			setAttenuation_dB(attenuation_dB, attenuation_dB);
		}

		/// <summary>
		/// 音量を減衰レベル（dB）で設定します。
		/// </summary>
		/// <param name="attenuationLeft_dB">
		/// 左チャンネルの減衰レベル（dB）
		/// </param>
		/// <param name="attenuationRight_dB">
		/// 右チャンネルの減衰レベル（dB）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setAttenuation_dB(double attenuationLeft_dB, double attenuationRight_dB) const
		{
			const double left = Math::Pow(10.0, attenuationLeft_dB / 20.0);
			const double right = Math::Pow(10.0, attenuationRight_dB / 20.0);
			setVolume(left, right);
		}

		/// <summary>
		/// 音量
		/// </summary>
		double getVolume() const;

		/// <summary>
		/// 左チャンネルの音量
		/// </summary>
		double getVolumeLeft() const;

		/// <summary>
		/// 右チャンネルの音量
		/// </summary>
		double getVolumeRight() const;

		/// <summary>
		/// 再生スピードを変更します。
		/// </summary>
		/// <param name="speed">
		/// 再生スピード [minSpeed, maxSpeed]
		/// </param>
		/// <remarks>
		/// 再生スピードは [minSpeed, maxSpeed] の範囲にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void setSpeed(double speed) const;

		/// <summary>
		/// 再生スピードを変更して音の高さを変更します。
		/// </summary>
		/// <param name="semitone">
		/// 音の高さの変更（半音単位）
		/// </param>
		/// <remarks>
		/// 再生スピードは [minSpeed, maxSpeed] の範囲にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void setSpeedBySemitone(int32 semitone) const;

		/// <summary>
		/// 現在の再生スピード
		/// </summary>
		double getSpeed() const;

		/// <summary>
		/// 指定可能な最小の再生スピード
		/// </summary>
		double getMinSpeed() const;

		/// <summary>
		/// 指定可能な最大の再生スピード
		/// </summary>
		double getMaxSpeed() const;

		void changeTempo(double tempo) const;

		double getTempo() const;

		void changePitchSemitones(double pitchSemitones) const;

		double getPitchSemitones() const;

		/// <summary>
		/// サウンドを重ねて再生します。
		/// </summary>
		/// <param name="volume">
		/// 再生するサウンドの音量
		/// </param>
		/// <remarks>
		/// この関数でサウンドを再生すると、同じサウンドを重ねて再生できます。
		/// </remarks>
		/// <returns>
		/// 再生に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool playMulti(double volume = 1.0) const;

		/// <summary>
		/// サウンドを重ねて再生します。
		/// </summary>
		/// <param name="volumeLeft">
		/// 再生するサウンドの左チャンネルの音量
		/// </param>
		/// <param name="volumeRight">
		/// 再生するサウンドの右チャンネルの音量
		/// </param>
		/// <remarks>
		/// この関数でサウンドを再生すると、同じサウンドを重ねて再生できます。
		/// </remarks>
		/// <returns>
		/// 再生に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool playMulti(double volumeLeft, double volumeRight) const;

		/// <summary>
		/// サウンドを重ねて再生します。
		/// </summary>
		/// <param name="volumeLeft">
		/// 再生するサウンドの左チャンネルの音量
		/// </param>
		/// <param name="volumeRight">
		/// 再生するサウンドの右チャンネルの音量
		/// </param>
		/// <param name="speed">
		/// 再生するサウンドのスピード
		/// </param>
		/// <remarks>
		/// この関数でサウンドを再生すると、同じサウンドを重ねて再生できます。
		/// </remarks>
		/// <returns>
		/// 再生に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool playMulti(double volumeLeft, double volumeRight, double speed) const;

		/// <summary>
		/// 重ねて再生しているサウンドを一斉に一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pauseMulti() const;

		/// <summary>
		/// 重ねて再生しているサウンドの一時停止を解除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resumeMulti() const;

		/// <summary>
		/// 重ねて再生しているサウンドを一斉に停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void stopMulti() const;

		bool set3D(const SoundEmitter& emitter, const SoundListener& listner);

		/// <summary>
		/// 3D サウンドであるかを示ます。
		/// </summary>
		bool is3D() const;

		bool playMulti(const SoundEmitter& emitter, const SoundListener& listner) const;

		bool fill(const Wave& wave);

		bool fill(size_t dstSample, const WaveSample* src, size_t lengthSample);
	};

	/// <summary>
	/// マスターボリューム
	/// </summary>
	/// <remarks>
	/// マスターボリュームを設定する機能を提供します。
	/// </remarks>
	namespace MasterVoice
	{
		/// <summary>
		/// マスターボリュームを設定します。
		/// </summary>
		/// <param name="volume">
		/// 音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetVolume(double volume);

		/// <summary>
		/// 現在のマスターボリュームを取得します。
		/// </summary>
		/// <returns>
		/// 現在のマスターボリューム [0.0, 1.0]
		/// </returns>
		double GetVolume();
	}
}
