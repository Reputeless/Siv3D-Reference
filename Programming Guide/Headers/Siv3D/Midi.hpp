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
# include "Utility.hpp"

namespace s3d
{
	struct MidiNote
	{
		uint32 noteNumber;

		int32 startMillisec;

		int32 lengthMillisec;
	};

	/// <summary>
	/// MIDI
	/// </summary>
	/// <remarks>
	/// MIDI サウンドを再生する機能を提供します。
	/// </remarks>
	namespace Midi
	{
		/// <summary>
		/// 新しい MIDI ファイルを読み込みます。
		/// </summary>
		/// <param name="path">
		/// MIDI ファイル名
		/// </param>
		/// <remarks>
		/// 以前に読み込まれていた MIDI は停止・破棄され、音量・再生速度はリセットされます。
		/// </remarks>
		/// <returns>
		/// MIDI ファイルの読み込みに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Open(const FilePath& path);

		/// <summary>
		/// Midi::Open() で読み込んだ MIDI を再生します。
		/// </summary>
		/// <remarks>
		/// MIDI は同時に 1 つのファイルしか再生できません。
		/// ほかのアプリケーションが MIDI デバイスを使用していた場合、再生に失敗する場合があります。
		/// </remarks>
		/// <returns>
		/// MIDI の再生開始に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Play();

		/// <summary>
		/// Midi::Open() で読み込んだ MIDI をループ再生します。
		/// </summary>
		/// <remarks>
		/// MIDI は同時に 1 つのファイルしか再生できません。
		/// ほかのアプリケーションが MIDI デバイスを使用していた場合、再生に失敗する場合があります。
		/// </remarks>
		/// <returns>
		/// MIDI の再生開始に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool PlayLoop();

		/// <summary>
		/// 再生中の MIDI を一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Pause();

		/// <summary>
		/// 再生中の MIDI を停止し、再生位置を曲の先頭に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Stop();

		/// <summary>
		/// MIDI が再生中かどうかを示します。
		/// </summary>
		/// <returns>
		/// MIDI が再生中の場合 true, それ以外の場合は false
		/// </returns>
		bool IsPlaying();

		/// <summary>
		/// MIDI の再生音量を指定します。
		/// </summary>
		/// <param name="volume">
		/// 音量 (0.0 が最小、1.0 が最大)
		/// </param>
		/// <remarks>
		/// volume は [0.1, 1.0] の範囲にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetVolume(double volume);

		/// <summary>
		/// 現在設定されている MIDI の再生音量を返します。
		/// </summary>
		/// <returns>
		/// 現在設定されている MIDI の再生音量 [0.0-1.0]
		/// </returns>
		double GetVolume();

		/// <summary>
		/// MIDI の再生速度を変更します。
		/// </summary>
		/// <param name="speed">
		/// 再生倍率 (0.1 が最小、10.0 が最大)
		/// </param>
		/// <remarks>
		/// speed は [0.1, 10.0] の範囲にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetTempo(double speed);

		/// <summary>
		/// 現在設定されている MIDI の再生速度を返します。
		/// </summary>
		/// <returns>
		/// 現在設定されている MIDI の再生速度
		/// </returns>
		double GetTempo();

		void SetPitch(double pitch);

		double GetPitch();

		/// <summary>
		/// 現在読み込まれている MIDI を通常速度で再生した場合の曲の長さを秒で返します。
		/// </summary>
		/// <returns>
		/// MIDI の長さ (秒)
		/// </returns>
		double GetLengthSec();

		/// <summary>
		/// 現在読み込まれている MIDI の再生位置を秒で返します。
		/// </summary>
		/// <returns>
		/// MIDI の再生位置 (秒)
		/// </returns>
		double GetPosSec();

		/// <summary>
		/// MIDI の再生位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// MIDI の再生位置 (秒)
		/// </param>
		/// <remarks>
		/// MIDI が再生中の場合は、そこから再生を再開します。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetPosSec(double pos);

		void Close();

		const std::array<Array<MidiNote>, 16>& GetScore();

		bool SendMessage(const Array<uint8>& message);
	}

	/// <summary>
	/// 音階
	/// </summary>
	enum class PitchName : uint8
	{
		C_1 = 0,
		CS_1,
		DF_1 = CS_1,
		D_1,
		DS_1,
		EF_1 = DS_1,
		E_1,
		FF_1 = E_1,
		F_1,
		ES_1 = F_1,
		FS_1,
		GF_1 = FS_1,
		G_1,
		GS_1,
		AF_1 = GS_1,
		A_1,
		AS_1,
		BF_1 = AS_1,
		B_1,
	
		CF0 = B_1,
		C0,
		BS_1 = C0,
		CS0,
		DF0 = CS0,
		D0,
		DS0,
		EF0 = DS0,
		E0,
		FF0 = E0,
		F0,
		ES0 = F0,
		FS0,
		GF0 = FS0,
		G0,
		GS0,
		AF0 = GS0,
		A0,
		AS0,
		BF0 = AS0,
		B0,
		
		CF1 = B0,
		C1,
		BS0 = C1,
		CS1,
		DF1 = CS1,
		D1,
		DS1,
		EF1 = DS1,
		E1,
		FF1 = E1,
		F1,
		ES1 = F1,
		FS1,
		GF1 = FS1,
		G1,
		GS1,
		AF1 = GS1,
		A1,
		AS1,
		BF1 = AS1,
		B1,

		CF2 = B1,
		C2,
		BS1 = C2,
		CS2,
		DF2 = CS2,
		D2,
		DS2,
		EF2 = DS2,
		E2,
		FF2 = E2,
		F2,
		ES2 = F2,
		FS2,
		GF2 = FS2,
		G2,
		GS2,
		AF2 = GS2,
		A2,
		AS2,
		BF2 = AS2,
		B2,

		CF3 = B2,
		C3,
		BS2 = C3,
		CS3,
		DF3 = CS3,
		D3,
		DS3,
		EF3 = DS3,
		E3,
		FF3 = E3,
		F3,
		ES3 = F3,
		FS3,
		GF3 = FS3,
		G3,
		GS3,
		AF3 = GS3,
		A3,
		AS3,
		BF3 = AS3,
		B3,

		CF4 = B3,
		C4,
		BS3 = C4,
		CS4,
		DF4 = CS4,
		D4,
		DS4,
		EF4 = DS4,
		E4,
		FF4 = E4,
		F4,
		ES4 = F4,
		FS4,
		GF4 = FS4,
		G4,
		GS4,
		AF4 = GS4,
		A4,
		AS4,
		BF4 = AS4,
		B4,

		CF5 = B4,
		C5,
		BS4 = C5,
		CS5,
		DF5 = CS5,
		D5,
		DS5,
		EF5 = DS5,
		E5,
		FF5 = E5,
		F5,
		ES5 = F5,
		FS5,
		GF5 = FS5,
		G5,
		GS5,
		AF5 = GS5,
		A5,
		AS5,
		BF5 = AS5,
		B5,

		CF6 = B5,
		C6,
		BS5 = C6,
		CS6,
		DF6 = CS6,
		D6,
		DS6,
		EF6 = DS6,
		E6,
		FF6 = E6,
		F6,
		ES6 = F6,
		FS6,
		GF6 = FS6,
		G6,
		GS6,
		AF6 = GS6,
		A6,
		AS6,
		BF6 = AS6,
		B6,

		CF7 = B6,
		C7,
		BS6 = C7,
		CS7,
		DF7 = CS7,
		D7,
		DS7,
		EF7 = DS7,
		E7,
		FF7 = E7,
		F7,
		ES7 = F7,
		FS7,
		GF7 = FS7,
		G7,
		GS7,
		AF7 = GS7,
		A7,
		AS7,
		BF7 = AS7,
		B7,

		CF8 = B7,
		C8,
		BS7 = C8,
		CS8,
		DF8 = CS8,
		D8,
		DS8,
		EF8 = DS8,
		E8,
		FF8 = E8,
		F8,
		ES8 = F8,
		FS8,
		GF8 = FS8,
		G8,
		GS8,
		AF8 = GS8,
		A8,
		AS8,
		BF8 = AS8,
		B8,

		CF9 = B8,
		C9,
		BS8 = C9,
		CS9,
		DF9 = CS9,
		D9,
		DS9,
		EF9 = DS9,
		E9,
		FF9 = E9,
		F9,
		ES9 = F9,
		FS9,
		GF9 = FS9,
		G9,
	};
	
	/// <summary>
	/// GM 音色
	/// </summary>
	enum class GMInstrument : uint8
	{
		// Piano
		Piano1,
		Piano2,
		Piano3,
		Piano4,
		ElectricPiano1,
		ElectricPiano2,
		Harpsichord,
		Clavinet,

		// Chromatic Percussion
		Celesta,
		Glockenspiel,
		MusicBox,
		Vibraphone,
		Marimba,
		Xylophone,
		TubularBells,
		Dulcimer,

		// Organ
		DrawbarOrgan,
		PercussiveOrgan,
		RockOrgan,
		ChurchOrgan,
		ReedOrgan,
		Accordion,
		Harmonica,
		TangoAccordion,

		//Guitar
		NylonGuitar,
		SteelGuitar,
		JazzGuitar,
		CleanGuitar,
		MutedGuitar,
		OverdrivenGuitar,
		DistortionGuitar,
		GuitarHarmonics,

		// Bass
		AcousticBass,
		FingeredBass,
		PickedBass,
		FretlessBass,
		SlapBass1,
		SlapBass2,
		SynthBass1,
		SynthBass2,

		// Strings
		Violin,
		Viola,
		Cello,
		Contrabass,
		TremoloStrings,
		PizzicatoStrings,
		OrchestralHarp,
		Timpani,

		// Ensemble
		StringEnsemble1,
		StringEnsemble2,
		SynthStrings1,
		SynthStrings2,
		ChoirAahs,
		VoiceOohs,
		SynthChoir,
		OrchestraHit,

		// Brass
		Trumpet,
		Trombone,
		Tuba,
		MutedTrumpet,
		FrenchHorn,
		BrassSection,
		SynthBrass1,
		SynthBrass2,

		// Reed
		SopranoSax,
		AltoSax,
		TenorSax,
		BaritoneSax,
		Oboe,
		EnglishHorn,
		Bassoon,
		Clarinet,

		// Pipe
		Piccolo,
		Flute,
		Recorder,
		PanFlute,
		Blownbottle,
		Shakuhachi,
		Whistle,
		Ocarina,

		// Synth Lead
		SquareWave,
		SawWave,
		SynCalliope,
		ChifferLead,
		Charang,
		SoloVox,
		FifthSawWave,
		BassAndLead,

		// Synth Pad
		Fantasia,
		WarmPad,
		Polysynth,
		SpaceVoice,
		BowedGlass,
		MetalPad,
		HaloPad,
		SweepPad,

		// Synth Effects
		IceRain,
		Soundtrack,
		Crystal,
		Atmosphere,
		Brightness,
		Goblin,
		EchoDrops,
		StarTheme,

		// Ethnic
		Sitar,
		Banjo,
		Shamisen,
		Koto,
		Kalimba,
		Bagpipe,
		Fiddle,
		Shanai,

		// Percussive
		TinkleBell,
		Agogo,
		SteelDrums,
		Woodblock,
		TaikoDrum,
		MelodicTom,
		SynthDrum,
		ReverseCymbal,

		// Sound effects
		GuitarFretNoise,
		BreathNoise,
		Seashore,
		BirdTweet,
		TelephoneRing,
		Helicopter,
		Applause,
		Gunshot,
	};

	/// <summary>
	/// MIDI メッセージ・ユーティリティ
	/// </summary>
	namespace MidiMessage
	{
		/// <summary>
		/// 音色を変更する MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="instrument">
		/// 音色
		/// </param>
		/// <returns>
		/// 音色を変更する MIDI メッセージ
		/// </returns>
		inline Array<uint8> SetInstrument(uint32 ch, uint32 instrument)
		{
			return{ uint8(0xC0 | (ch & 0xF)), uint8(instrument & 0x7F) };
		}

		/// <summary>
		/// 音色を変更する MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="instrument">
		/// 音色
		/// </param>
		/// <returns>
		/// 音色を変更する MIDI メッセージ
		/// </returns>
		inline Array<uint8> SetInstrument(uint32 ch, GMInstrument instrument)
		{
			return{ uint8(0xC0 | (ch & 0xF)), uint8(static_cast<uint8>(instrument) & 0x7F) };
		}

		/// <summary>
		/// ノート・オンの MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="note">
		/// ノート番号
		/// </param>
		/// <param name="velocity">
		/// ベロシティ
		/// </param>
		/// <returns>
		/// ノート・オンの MIDI メッセージ
		/// </returns>
		inline Array<uint8> NoteOn(uint32 ch, uint32 note, uint8 velocity = 64)
		{
			return{ uint8(0x90 | (ch & 0xF)), uint8(note & 0x7F), velocity };
		}

		/// <summary>
		/// ノート・オンの MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="note">
		/// ノート番号
		/// </param>
		/// <param name="velocity">
		/// ベロシティ
		/// </param>
		/// <returns>
		/// ノート・オンの MIDI メッセージ
		/// </returns>
		inline Array<uint8> NoteOn(uint32 ch, PitchName note, uint8 velocity = 64)
		{
			return{ uint8(0x90 | (ch & 0xF)), uint8(static_cast<uint8>(note) & 0x7F), velocity };
		}

		/// <summary>
		/// ノート・オフの MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="note">
		/// ノート番号
		/// </param>
		/// <param name="velocity">
		/// ベロシティ
		/// </param>
		/// <returns>
		/// ノート・オフの MIDI メッセージ
		/// </returns>
		inline Array<uint8> NoteOff(uint32 ch, uint32 note, uint8 velocity = 64)
		{
			return{ uint8(0x80 | (ch & 0xF)), uint8(note & 0x7F), velocity };
		}

		/// <summary>
		/// ノート・オフの MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="note">
		/// ノート番号
		/// </param>
		/// <param name="velocity">
		/// ベロシティ
		/// </param>
		/// <returns>
		/// ノート・オフの MIDI メッセージ
		/// </returns>
		inline Array<uint8> NoteOff(uint32 ch, PitchName note, uint8 velocity = 64)
		{
			return{ uint8(0x80 | (ch & 0xF)), uint8(static_cast<uint8>(note) & 0x7F), velocity };
		}

		/// <summary>
		/// 音量を変更する MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="volume">
		/// 音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// 音量を変更する MIDI メッセージ
		/// </returns>
		inline Array<uint8> SetVolume(uint32 ch, double volume)
		{
			return{ uint8(0xB0 | (ch & 0xF)), uint8(0x07), static_cast<uint8>(Clamp(255 * volume, 0.0, 255.0)) };
		}

		/// <summary>
		/// パンポットを変更する MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <param name="panpot">
		/// パンポット [-1.0, 1.0]
		/// </param>
		/// <returns>
		/// パンポットを変更する MIDI メッセージ
		/// </returns>
		inline Array<uint8> SetPanpot(uint32 ch, double panpot)
		{
			return{ uint8(0xB0 | (ch & 0xF)), uint8(0x0A), static_cast<uint8>(Clamp(64 + 63.5 * panpot, 0.0, 127.0)) };
		}

		/// <summary>
		/// 全てのノートをオフにする MIDI メッセージを作成します。
		/// </summary>
		/// <param name="ch">
		/// チャンネル [0, 15]
		/// </param>
		/// <returns>
		/// 全てのノートをオフにする MIDI メッセージ
		/// </returns>
		inline Array<uint8> AllSoundOff(uint32 ch)
		{
			return{ uint8(0xB0 | (ch & 0xF)), uint8(0x78), uint8(0x00) };
		}
	}
}
