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
# include "Optional.hpp"
# include "String.hpp"
# include "Duration.hpp"
# include "WaveSample.hpp"
# include "Math.hpp"
# include "Midi.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	/// <summary>
	/// オーディオファイルのフォーマット
	/// </summary>
	enum class AudioFormat
	{
		/// <summary>
		/// 
		/// </summary>
		Unknown,

		/// <summary>
		/// WAVE
		/// </summary>
		WAV,

		/// <summary>
		/// OggVorbis
		/// </summary>
		OggVorbis,

		/// <summary>
		/// MP3
		/// </summary>
		MP3,

		/// <summary>
		/// AAC(M4A)
		/// </summary>
		AAC,

		/// <summary>
		/// WMA
		/// </summary>
		WMA,

		/// <summary>
		/// Opus
		/// </summary>
		Opus,

		//Aiff,

		//Flac,

		/// <summary>
		/// 
		/// </summary>
		Unspecified = Unknown,
	};

	/// <summary>
	/// オーディオの情報
	/// </summary>
	struct AudioProperty
	{
		/// <summary>
		/// 
		/// </summary>
		AudioFormat format;

		/// <summary>
		/// 再生時間（ミリ秒）
		/// </summary>
		uint32 durationMillisec;

		/// <summary>
		/// ビットレート
		/// </summary>
		uint32 encodingBitrate;

		/// <summary>
		/// タイトル
		/// </summary>
		String title;

		/// <summary>
		/// アーティスト
		/// </summary>
		String artist;

		/// <summary>
		/// アルバムタイトル
		/// </summary>
		String albumTitle;

		/// <summary>
		/// アルバムアーティスト
		/// </summary>
		String albumArtist;

		/// <summary>
		/// 
		/// </summary>
		Optional<uint32> year;

		/// <summary>
		/// 
		/// </summary>
		Optional<uint32> trackNumber;
	};

	/// <summary>
	/// WAVE の保存形式
	/// </summary>
	enum class WAVEFormat
	{
		/// <summary>
		/// 8bit ステレオ
		/// </summary>
		Stereo8U,

		/// <summary>
		/// 16bit ステレオ
		/// </summary>
		Stereo16S,

		/// <summary>
		/// 32bit float ステレオ
		/// </summary>
		Stereo32F,

		/// <summary>
		/// 
		/// </summary>
		Default = Stereo16S,
	};

	/// <summary>
	/// MP3 オーディオの圧縮品質
	/// </summary>
	enum class MP3Quality
	{
		/// <summary>
		/// 32kbps
		/// </summary>
		BR32kbps,

		/// <summary>
		/// 40kbps
		/// </summary>
		BR40kbps,

		/// <summary>
		/// 48kbps
		/// </summary>
		BR48kbps,

		/// <summary>
		/// 56kbps
		/// </summary>
		BR56kbps,

		/// <summary>
		/// 64kbps
		/// </summary>
		BR64kbps,

		/// <summary>
		/// 80kbps
		/// </summary>
		BR80kbps,

		/// <summary>
		/// 96kbps
		/// </summary>
		BR96kbps,

		/// <summary>
		/// 112kbps
		/// </summary>
		BR112kbps,

		/// <summary>
		/// 128kbps
		/// </summary>
		BR128kbps,

		/// <summary>
		/// 160kbps
		/// </summary>
		BR160kbps,

		/// <summary>
		/// 192kbps
		/// </summary>
		BR192kbps,

		/// <summary>
		/// 224kbps
		/// </summary>
		BR224kbps,

		/// <summary>
		/// 256kbps
		/// </summary>
		BR256kbps,

		/// <summary>
		/// 320kbps
		/// </summary>
		BR320kbps,

		/// <summary>
		/// 
		/// </summary>
		Default = BR192kbps,
	};

	/// <summary>
	/// AAC オーディオの圧縮品質
	/// </summary>
	enum class AACQuality
	{
		/// <summary>
		/// 96kbps
		/// </summary>
		BR96kbps,

		/// <summary>
		/// 128kbps
		/// </summary>
		BR128kbps,

		/// <summary>
		/// 160kbps
		/// </summary>
		BR160kbps,

		/// <summary>
		/// 192kbps
		/// </summary>
		BR192kbps,

		/// <summary>
		/// 
		/// </summary>
		Default = BR160kbps,
	};

	struct OggVorbisLoopExtension
	{
		size_t loopBegin;

		size_t loopLength;
	};

	/// <summary>
	/// 
	/// </summary>
	namespace Waving
	{
		WaveSample DoubleToSample(double mono);

		WaveSample DoubleToSample(double left, double right);

		void SwapChannel(const Wave& src, Wave& dst);

		void Reverse(const Wave& wave);

		inline double CalculateFrequency(PitchName pitch, const double standardPitch = 440.0)
		{
			return standardPitch * Math::Exp2((static_cast<int>(pitch) - static_cast<int>(PitchName::A4)) / 12.0);
		}

		template <PitchName pitch>
		inline double SinWave(double t)
		{
			return Math::Sin(t*CalculateFrequency(pitch)*Math::TwoPi);
		}

		inline double SinWave440Hz(double t)
		{
			return Math::Sin(t*440.0*Math::TwoPi);
		}
	}

	/// <summary>
	/// 波形
	/// </summary>
	class Wave
	{
	private:

		Array<WaveSample> m_data;

		uint32 m_samplingRate = DefaultSamplingRate;

	public:

		using iterator			= Array<WaveSample>::iterator;
		using const_iterator	= Array<WaveSample>::const_iterator;
		using reverse_iterator	= Array<WaveSample>::reverse_iterator;	
		using const_reverse_iterator = Array<WaveSample>::const_reverse_iterator;

		/// <summary>
		/// 
		/// </summary>
		static constexpr uint32 MinSamplingRate = 4000;
		
		/// <summary>
		/// 
		/// </summary>
		static constexpr uint32 DefaultSamplingRate = 44100;
		
		/// <summary>
		/// 
		/// </summary>
		static constexpr uint32 MaxSamplingRate = 192000;

		/// <summary>
		/// 
		/// </summary>
		Wave();

		/// <summary>
		/// 
		/// </summary>
		~Wave();

		explicit Wave(size_t sample);

		explicit Wave(const SecondsF& length);

		Wave(size_t sample, uint32 samplingRate);

		Wave(size_t sample, std::function<double(double)> generator, uint32 samplingRate = Wave::DefaultSamplingRate);

		Wave(const SecondsF& length, uint32 samplingRate);

		Wave(const SecondsF& length, std::function<double(double)> generator, uint32 samplingRate = Wave::DefaultSamplingRate);

		explicit Wave(const FilePath& path);

		explicit Wave(IReader&& reader, AudioFormat format = AudioFormat::Unspecified);

		Wave(const Wave& wave);

		Wave(Wave && wave);

		template <class InputIt>
		Wave(InputIt first, InputIt last, uint32 samplingRate = Wave::DefaultSamplingRate)
			: m_data(first, last)
			, m_samplingRate(samplingRate) {}

		Wave& operator = (const Wave& wave);

		Wave& operator = (Wave && wave);

		void assign(size_t count, const WaveSample& value)
		{
			m_data.assign(count, value);
		}
		
		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{
			m_data.assign(first, last);
		}

		template <class InputIt>
		void assign(InputIt first, InputIt last, uint32 samplingRate)
		{
			m_data.assign(first, last);
			m_samplingRate = samplingRate;
		}

		void clear();

		void shrink_to_fit()
		{
			m_data.shrink_to_fit();
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		void fillZero();

		uint32 setSamplingRate(uint32 samplingRate);

		explicit operator bool() const
		{
			return !isEmpty;
		}

		void reserve(size_t sample);

		void resize(size_t sample);

		void resize(size_t sample, const WaveSample& value);

		WaveSample& at(size_t pos);

		const WaveSample& at(size_t pos) const;

		WaveSample& operator [](size_t pos)
		{
			return m_data[pos];
		}

		const WaveSample& operator [](size_t pos) const
		{
			return m_data[pos];
		}

		void* data()
		{
			return &m_data[0];
		}

		const void* data() const
		{
			return &m_data[0];
		}

		iterator begin() { return m_data.begin(); }

		const_iterator begin() const { return m_data.begin(); }

		const_iterator cbegin() const { return m_data.cbegin(); }

		iterator end() { return m_data.end(); }

		const_iterator end() const { return m_data.end(); }

		const_iterator cend() const { return m_data.cend(); }

		reverse_iterator rbegin() { return m_data.rbegin(); }

		const_reverse_iterator rbegin() const { return m_data.rbegin(); }

		const_reverse_iterator crbegin() const { return m_data.crbegin(); }

		reverse_iterator rend() { return m_data.rend(); }

		const_reverse_iterator rend() const { return m_data.rend(); }

		const_reverse_iterator crend() const { return m_data.crend(); }

		iterator insert(const_iterator pos, const WaveSample& value)
		{
			return m_data.insert(pos, value);
		}

		iterator insert(const_iterator pos, size_t count, const WaveSample& value)
		{
			return m_data.insert(pos, count, value);
		}

		template <class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last)
		{
			return m_data.insert(pos, first, last);
		}

		iterator erase(const_iterator pos)
		{
			return m_data.erase(pos);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			return m_data.erase(first, last);
		}

		void push_back(const WaveSample& value)
		{
			m_data.push_back(value);
		}

		void pop_back()
		{
			m_data.pop_back();
		}

		void swap(Wave& wav)
		{
			m_data.swap(wav.m_data);
			
			std::swap(m_samplingRate, wav.m_samplingRate);
		}

		Wave clone() const
		{
			return *this;
		}

		/// <summary>
		/// 
		/// </summary>
		Property_Get(double, lengthSec) const { return static_cast<double>(lengthSample) / m_samplingRate; }

		/// <summary>
		/// 
		/// </summary>
		Property_Get(size_t, lengthSample) const { return m_data.size(); }

		/// <summary>
		/// 
		/// </summary>
		Property_Get(uint32, samplingRate) const { return m_samplingRate; }
		
		/// <summary>
		/// 
		/// </summary>
		size_t memorySize() const { return lengthSample * sizeof(WaveSample); }

		/// <summary>
		/// 
		/// </summary>
		Property_Get(bool, isEmpty) const { return m_data.empty(); }

		bool save(const FilePath& path, AudioFormat format = AudioFormat::Unspecified) const;

		bool saveWAVE(const FilePath& path, WAVEFormat format = WAVEFormat::Default) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="quality">
		/// 圧縮品質 [0,100]
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		bool saveOggVorbis(const FilePath& path, int32 quality = 60) const;

		bool saveMP3(const FilePath& path, MP3Quality quality = MP3Quality::Default) const;

		bool saveAAC(const FilePath& path, AACQuality quality = AACQuality::Default) const;

		bool saveOpus(const FilePath& path, int32 bitrate = 96) const;

		ByteArray encode(AudioFormat format) const;

		ByteArray encodeOggVorbis(int32 quality = 60) const;

		ByteArray encodeMP3(MP3Quality quality = MP3Quality::Default) const;

		ByteArray encodeAAC(AACQuality quality = AACQuality::Default) const;

		ByteArray encodeOpus(int32 bitrate = 96) const;

		Wave& swapChannel();

		Wave& reverse();

		Wave& convertTo32FMono();
	};

	/// <summary>
	/// 
	/// </summary>
	namespace Audio
	{
		AudioFormat GetFormat(const FilePath& path);

		AudioFormat GetFormat(const IReader& reader);

		AudioFormat GetFormatFromFileName(const FilePath& path);

		Optional<AudioProperty> GetProperty(const FilePath& path);

		Optional<OggVorbisLoopExtension> GetOggVorbisLoop(const FilePath& path);

		bool MP3EncoderAvailable();

		bool AACEncoderAvailable();

		bool WMAEncoderAvailable();
	}

	namespace Waving
	{
		[[deprecated("** Waving::Synthesize() is a deprecated function. Use Wave::Wave() instead. **")]]
		Wave Synthesize(double length, std::function<double(double)> function = SinWave440Hz, uint32 rate = Wave::DefaultSamplingRate);
	}
}

namespace std
{
	inline void swap(s3d::Wave& x, s3d::Wave& y)
	{
		x.swap(y);
	}
}
