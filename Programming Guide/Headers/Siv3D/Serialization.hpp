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
# include "../ThirdParty/cereal/cereal.hpp"
# include "../ThirdParty/cereal/archives/binary.hpp"
# include "../ThirdParty/cereal/types/array.hpp"
# include "../ThirdParty/cereal/types/base_class.hpp"
# ifdef _BITSET_
# include "../ThirdParty/cereal/types/bitset.hpp"
# endif
# include "../ThirdParty/cereal/types/chrono.hpp"
# include "../ThirdParty/cereal/types/common.hpp"
# ifdef _COMPLEX_
# include "../ThirdParty/cereal/types/complex.hpp"
# endif
# ifdef _DEQUE_
# include "../ThirdParty/cereal/types/deque.hpp"
# endif
# ifdef _FORWARD_LIST_
# include "../ThirdParty/cereal/types/forward_list.hpp"
# endif
# ifdef _LIST_
# include "../ThirdParty/cereal/types/list.hpp"
# endif
# ifdef _MAP_
# include "../ThirdParty/cereal/types/map.hpp"
# endif
# include "../ThirdParty/cereal/types/memory.hpp"
# include "../ThirdParty/cereal/types/polymorphic.hpp"
# ifdef _QUEUE_
# include "../ThirdParty/cereal/types/queue.hpp"
# endif
# ifdef _SET_
# include "../ThirdParty/cereal/types/set.hpp"
# endif
# ifdef _STACK_
# include "../ThirdParty/cereal/types/stack.hpp"
# endif
# include "../ThirdParty/cereal/types/string.hpp"
# ifdef _TUPLE_
# include "../ThirdParty/cereal/types/tuple.hpp"
# endif
# include "../ThirdParty/cereal/types/unordered_map.hpp"
# include "../ThirdParty/cereal/types/unordered_set.hpp"
# include "../ThirdParty/cereal/types/utility.hpp"
# ifdef _VALARRAY_
# include "../ThirdParty/cereal/types/valarray.hpp"
# endif
# include "../ThirdParty/cereal/types/vector.hpp"

namespace s3d
{
	template <class Writer>
	class Serializer : public cereal::OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>
	{
	private:

		std::shared_ptr<IWriter> m_writer;

	public:

		template <class ...Args>
		Serializer(Args&&... args)
			: OutputArchive<Serializer<Writer>, cereal::AllowEmptyClassElision>(this)
			, m_writer(std::make_shared<Writer>(std::forward<Args>(args)...))
		{

		}

		void saveBinary(const void* data, size_t size)
		{
			auto const writtenSize = static_cast<std::size_t>(m_writer->write(data, size));

			if (writtenSize != size)
				throw cereal::Exception("Failed to write " + std::to_string(size) + " bytes to output stream! Wrote " + std::to_string(writtenSize));
		}

		Writer& getWriter()
		{
			return *std::dynamic_pointer_cast<Writer>(m_writer);
		}
	};

	template <class Reader>
	class Deserializer : public cereal::InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>
	{
	private:

		std::shared_ptr<IReader> m_reader;

	public:

		template <class ...Args>
		Deserializer(Args&&... args)
			: InputArchive<Deserializer<Reader>, cereal::AllowEmptyClassElision>(this)
			, m_reader(std::make_shared<Reader>(std::forward<Args>(args)...))
		{

		}

		void loadBinary(void* const data, size_t size)
		{
			auto const readSize = static_cast<size_t>(m_reader->read(data, size));

			if (readSize != size)
				throw cereal::Exception("Failed to read " + std::to_string(size) + " bytes from input stream! Read " + std::to_string(readSize));
		}

		Reader& getReader()
		{
			return *std::dynamic_pointer_cast<Reader>(m_reader);
		}
	};


	//! Saving for POD types to binary
	template<class T, class Writer>
	inline typename std::enable_if<std::is_arithmetic<T>::value, void>::type
	CEREAL_SAVE_FUNCTION_NAME(Serializer<Writer>& ar, T const & t)
	{
		ar.saveBinary(std::addressof(t), sizeof(t));
	}

	template <class T, class Reader>
	inline typename std::enable_if<std::is_arithmetic<T>::value, void>::type
	CEREAL_LOAD_FUNCTION_NAME(Deserializer<Reader>& ar, T & t)
	{
		ar.loadBinary(std::addressof(t), sizeof(t));
	}

	//! Serializing NVP types to binary
	template <class Archive, class T>
	inline void CEREAL_SERIALIZE_FUNCTION_NAME(Archive& ar, cereal::NameValuePair<T> & t)
	{
		ar(t.value);
	}

	//! Serializing SizeTags to binary
	template <class Archive, class T>
	inline void CEREAL_SERIALIZE_FUNCTION_NAME(Archive& ar, cereal::SizeTag<T> & t)
	{
		ar(t.size);
	}

	//! Saving binary data
	template <class T, class Writer>
	inline void CEREAL_SAVE_FUNCTION_NAME(Serializer<Writer>& ar, cereal::BinaryData<T> const & bd)
	{
		ar.saveBinary(bd.data, static_cast<std::size_t>(bd.size));
	}

	//! Loading binary data
	template <class T, class Reader>
	inline void CEREAL_LOAD_FUNCTION_NAME(Deserializer<Reader> & ar, cereal::BinaryData<T> & bd)
	{
		ar.loadBinary(bd.data, static_cast<std::size_t>(bd.size));
	}

	//////////////////////////////////////////////////////
	//
	//	Optional
	//
	template <class Archive, class Type>
	inline void save(Archive& archive, const Optional<Type>& opt)
	{
		const bool hasValue = opt.has_value();
		archive(hasValue);
		if (hasValue)
		{
			archive(opt.value());
		}
	}

	template <class Archive, class Type>
	inline void load(Archive& archive, Optional<Type>& opt)
	{
		bool hasValue;
		archive(hasValue);
		if (hasValue)
		{
			if (!opt)
			{
				opt.reset(Type());
			}

			archive(opt.value());
		}
		else
		{
			opt.reset();
		}
	}

	//////////////////////////////////////////////////////
	//
	//	BoolArray
	//
	template <class Archive>
	inline void save(Archive & archive, const BoolArray& boolArray)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(boolArray.size())));
		archive(cereal::binary_data(boolArray.data(), boolArray.size() * sizeof(bool)));
	}

	template <class Archive>
	inline void load(Archive& archive, BoolArray& boolArray)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		boolArray.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(&boolArray[0], static_cast<size_t>(size) * sizeof(bool)));
	}

	//////////////////////////////////////////////////////
	//
	//	Grid
	//
	template <class Archive, class Type>
	inline void save(Archive& archive, const Grid<Type>& grid)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(grid.width)));
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(grid.height)));
		archive(grid.getArray());
	}

	template <class Archive, class Type>
	inline void load(Archive& archive, Grid<Type>& grid)
	{
		cereal::size_type width, height;
		archive(cereal::make_size_tag(width));
		archive(cereal::make_size_tag(height));
		Array<Type> data(static_cast<size_t>(width * height));
		archive(data);
		grid = Grid<Type>(static_cast<size_t>(width), static_cast<size_t>(height), std::move(data));
	}

	//////////////////////////////////////////////////////
	//
	//	String
	//
	template <class Archive>
	inline void save(Archive & archive, const String& str)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(str.length)));
		archive(cereal::binary_data(str.data(), str.length * sizeof(wchar)));
	}

	template <class Archive>
	inline void load(Archive& archive, String& str)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(size));
		str.resize(static_cast<size_t>(size));
		archive(cereal::binary_data(&str[0], static_cast<size_t>(size) * sizeof(wchar)));
	}

	//////////////////////////////////////////////////////
	//
	//	Date
	//
	template <class Archive>
	void serialize(Archive& archive, Date& date)
	{
		archive(date.year, date.month, date.day);
	}

	//////////////////////////////////////////////////////
	//
	//	DateTime
	//
	template <class Archive>
	void serialize(Archive& archive, DateTime& dateTime)
	{
		archive(dateTime.year, dateTime.month, dateTime.day,
			dateTime.hour, dateTime.minute, dateTime.second, dateTime.milliseconds);
	}

	//////////////////////////////////////////////////////
	//
	//	StopWatch
	//
	template <class Archive>
	void save(Archive& archive, const Stopwatch& stopwatch)
	{
		const Milliseconds ms = stopwatch.elapsed();
		const bool isActive = stopwatch.isActive();
		const bool isPaused = stopwatch.isPaused();
		archive(ms, isActive, isPaused);
	}

	template <class Archive>
	void load(Archive& archive, Stopwatch& stopwatch)
	{
		Milliseconds ms;
		bool isActive, isPaused;
		archive(ms, isActive, isPaused);

		if (isActive)
		{
			if (isPaused)
			{
				stopwatch.pause();
				stopwatch.set(ms);
			}
			else
			{
				stopwatch.start();
				stopwatch.set(ms);
			}
		}
		else
		{
			stopwatch.reset();
		}
	}

	//////////////////////////////////////////////////////
	//
	//	StopWatch64
	//
	template <class Archive>
	void save(Archive& archive, const Stopwatch64& stopwatch)
	{
		const Milliseconds ms = stopwatch.elapsed();
		const bool isActive = stopwatch.isActive();
		const bool isPaused = stopwatch.isPaused();
		archive(ms, isActive, isPaused);
	}

	template <class Archive>
	void load(Archive& archive, Stopwatch64& stopwatch)
	{
		Milliseconds ms;
		bool isActive, isPaused;
		archive(ms, isActive, isPaused);

		if (isActive)
		{
			if (isPaused)
			{
				stopwatch.pause();
				stopwatch.set(ms);
			}
			else
			{
				stopwatch.start();
				stopwatch.set(ms);
			}
		}
		else
		{
			stopwatch.reset();
		}
	}
	
	//////////////////////////////////////////////////////
	//
	//	StopwatchMicrosec
	//
	template <class Archive>
	void save(Archive& archive, const StopwatchMicrosec& stopwatch)
	{
		const Microseconds us = stopwatch.elapsed();
		const bool isActive = stopwatch.isActive();
		const bool isPaused = stopwatch.isPaused();
		archive(us, isActive, isPaused);
	}

	template <class Archive>
	void load(Archive& archive, StopwatchMicrosec& stopwatch)
	{
		Microseconds us;
		bool isActive, isPaused;
		archive(us, isActive, isPaused);

		if (isActive)
		{
			if (isPaused)
			{
				stopwatch.pause();
				stopwatch.set(us);
			}
			else
			{
				stopwatch.start();
				stopwatch.set(us);
			}
		}
		else
		{
			stopwatch.reset();
		}
	}

	//////////////////////////////////////////////////////
	//
	//	EventTimer
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	VariableSpeedStopwatch
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	MillisecClock
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	MicrosecClock
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	RDTSCClock
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	ByteArray
	//
	template <class Archive>
	inline void save(Archive& archive, const ByteArray& byteArray)
	{
		archive(byteArray.asArray());
	}

	template <class Archive>
	inline void load(Archive& archive, ByteArray& byteArray)
	{
		Array<uint8> data;
		archive(data);
		byteArray = ByteArray(std::move(data));
	}

	//////////////////////////////////////////////////////
	//
	//	MemoryWriter
	//
	template <class Archive>
	inline void save(Archive& archive, const MemoryWriter& memoryWriter)
	{
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(memoryWriter.size())));
		archive(cereal::binary_data(memoryWriter.data(), memoryWriter.size()));
	}

	template <class Archive>
	inline void load(Archive& archive, MemoryWriter& memoryWriter)
	{
		cereal::size_type size;
		archive(cereal::make_size_tag(static_cast<cereal::size_type>(size)));
		Array<uint8> data(static_cast<size_t>(size));
		archive(cereal::binary_data(&data[0], static_cast<size_t>(size)));
		memoryWriter.release();
		memoryWriter.write(data);
	}

	//////////////////////////////////////////////////////
	//
	//	MD5Value
	//
	template <class Archive>
	void serialize(Archive& archive, MD5Value& md5Value)
	{
		archive(md5Value.value);
	}

	//////////////////////////////////////////////////////
	//
	//	AES128Key
	//
	template <class Archive>
	void serialize(Archive& archive, AES128Key& aes128Key)
	{
		archive(aes128Key.v8);
	}

	//////////////////////////////////////////////////////
	//
	//	AESIV
	//
	template <class Archive>
	void serialize(Archive& archive, AESIV& aesIV)
	{
		archive(aesIV.v8);
	}

	//////////////////////////////////////////////////////
	//
	//	JSONValue
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Color
	//
	template <class Archive>
	inline void save(Archive& archive, const Color& color)
	{
		const uint8 r = color.r, g = color.g, b = color.b, a = color.a;
		archive(r, g, b, a);
	}

	template <class Archive>
	inline void load(Archive& archive, Color& color)
	{
		uint8 r, g, b, a;
		archive(r, g, b, a);
		color.set(r, g, b, a);
	}

	//////////////////////////////////////////////////////
	//
	//	ColorF
	//
	template <class Archive>
	void serialize(Archive& archive, ColorF& colorF)
	{
		archive(colorF.r, colorF.g, colorF.b, colorF.a);
	}

	//////////////////////////////////////////////////////
	//
	//	HSV
	//
	template <class Archive>
	void serialize(Archive& archive, HSV& hsv)
	{
		archive(hsv.h, hsv.s, hsv.v);
	}

	//////////////////////////////////////////////////////
	//
	//	Point
	//
	template <class Archive>
	void serialize(Archive& archive, Point& point)
	{
		archive(point.x, point.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Float2
	//
	template <class Archive>
	void serialize(Archive& archive, Float2& float2)
	{
		archive(float2.x, float2.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Vec2
	//
	template <class Archive>
	void serialize(Archive& archive, Vec2& vec2)
	{
		archive(vec2.x, vec2.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Float3
	//
	template <class Archive>
	void serialize(Archive& archive, Float3& float3)
	{
		archive(float3.x, float3.y, float3.z);
	}

	//////////////////////////////////////////////////////
	//
	//	Vec3
	//
	template <class Archive>
	void serialize(Archive& archive, Vec3& vec3)
	{
		archive(vec3.x, vec3.y, vec3.z);
	}

	//////////////////////////////////////////////////////
	//
	//	Float4
	//
	template <class Archive>
	void serialize(Archive& archive, Float4& float4)
	{
		archive(float4.x, float4.y, float4.z, float4.w);
	}

	//////////////////////////////////////////////////////
	//
	//	Vec4
	//
	template <class Archive>
	void serialize(Archive& archive, Vec4& vec4)
	{
		archive(vec4.x, vec4.y, vec4.z, vec4.w);
	}

	//////////////////////////////////////////////////////
	//
	//	Circular
	//
	template <class Archive, int32 Oclock>
	void serialize(Archive& archive, CircularBase<Oclock>& circular)
	{
		archive(circular.r, circular.theta);
	}

	//////////////////////////////////////////////////////
	//
	//	Cylindrical
	//
	template <class Archive>
	void serialize(Archive& archive, Cylindrical& cylindrical)
	{
		archive(cylindrical.r, cylindrical.phi, cylindrical.y);
	}

	//////////////////////////////////////////////////////
	//
	//	Spherical
	//
	template <class Archive>
	void serialize(Archive& archive, Spherical& spherical)
	{
		archive(spherical.r, spherical.theta, spherical.phi);
	}

	//////////////////////////////////////////////////////
	//
	//	Mat3x2
	//
	template <class Archive>
	void serialize(Archive& archive, Mat3x2& mat3x2)
	{
		archive(mat3x2._11, mat3x2._12, mat3x2._21, mat3x2._22, mat3x2._31, mat3x2._32);
	}

	//////////////////////////////////////////////////////
	//
	//	LineInt
	//
	template <class Archive>
	void serialize(Archive& archive, LineInt& lineInt)
	{
		archive(lineInt.begin, lineInt.end);
	}

	//////////////////////////////////////////////////////
	//
	//	Line
	//
	template <class Archive>
	void serialize(Archive& archive, Line& line)
	{
		archive(line.begin, line.end);
	}

	//////////////////////////////////////////////////////
	//
	//	Rect
	//
	template <class Archive>
	void serialize(Archive& archive, Rect& rect)
	{
		archive(rect.x, rect.y, rect.w, rect.h);
	}

	//////////////////////////////////////////////////////
	//
	//	RectF
	//
	template <class Archive>
	void serialize(Archive& archive, RectF& rectF)
	{
		archive(rectF.x, rectF.y, rectF.w, rectF.h);
	}

	//////////////////////////////////////////////////////
	//
	//	Circle
	//
	template <class Archive>
	void serialize(Archive& archive, Circle& circle)
	{
		archive(circle.x, circle.y, circle.r);
	}

	//////////////////////////////////////////////////////
	//
	//	Ellipse
	//
	template <class Archive>
	void serialize(Archive& archive, Ellipse& ellipse)
	{
		archive(ellipse.x, ellipse.y, ellipse.a, ellipse.b);
	}

	//////////////////////////////////////////////////////
	//
	//	Triangle
	//
	template <class Archive>
	void serialize(Archive& archive, Triangle& triangle)
	{
		archive(triangle.p);
	}

	//////////////////////////////////////////////////////
	//
	//	Quad
	//
	template <class Archive>
	void serialize(Archive& archive, Quad& quad)
	{
		archive(quad.p);
	}

	//////////////////////////////////////////////////////
	//
	//	RoundRect
	//
	template <class Archive>
	void serialize(Archive& archive, RoundRect& roundRect)
	{
		archive(roundRect.x, roundRect.y, roundRect.w, roundRect.h, roundRect.r);
	}

	//////////////////////////////////////////////////////
	//
	//	LineString
	//
	template <class Archive>
	void serialize(Archive& archive, LineString& lineString)
	{
		archive(lineString.data());
	}

	//////////////////////////////////////////////////////
	//
	//	Polygon
	//
	template <class Archive>
	inline void save(Archive& archive, const Polygon& polygon)
	{
		archive(polygon.outer(), polygon.inners(), polygon.indices(), polygon.boundingRect);
	}

	template <class Archive>
	inline void load(Archive& archive, Polygon& polygon)
	{
		Array<Vec2> outer;
		Array<Array<Vec2>> holes;
		Array<uint16> indices;
		RectF bound;
		archive(outer, holes, indices, bound);
		polygon = Polygon(outer, holes, indices, bound);
	}

	//////////////////////////////////////////////////////
	//
	//	MultiPolygon
	//
	template <class Archive>
	inline void save(Archive& archive, const MultiPolygon& multiPolygon)
	{
		archive(multiPolygon.polygons());
	}

	template <class Archive>
	inline void load(Archive& archive, MultiPolygon& multiPolygon)
	{
		Array<Polygon> polygons;
		archive(polygons);
		multiPolygon = MultiPolygon(std::move(polygons));
	}

	//////////////////////////////////////////////////////
	//
	//	Shape
	//
	template <class Archive>
	inline void save(Archive & archive, const Shape& shape)
	{
		const auto type = shape.type();
		archive(static_cast<int32>(type));

		switch (type)
		{
		case Shape::Type::Point:
			archive(shape.storage.point);
			break;
		case Shape::Type::Vec2:
			archive(shape.storage.vec2);
			break;
		case Shape::Type::LineInt:
			archive(shape.storage.lineInt);
			break;
		case Shape::Type::Line:
			archive(shape.storage.line);
			break;
		case Shape::Type::Rect:
			archive(shape.storage.rect);
			break;
		case Shape::Type::RectF:
			archive(shape.storage.rectF);
			break;
		case Shape::Type::Circle:
			archive(shape.storage.circle);
			break;
		case Shape::Type::Ellipse:
			archive(shape.storage.ellipse);
			break;
		case Shape::Type::Triangle:
			archive(shape.storage.triangle);
			break;
		case Shape::Type::Quad:
			archive(*shape.storage.quad);
			break;
		case Shape::Type::RoundRect:
			archive(shape.storage.roundRect);
			break;
		case Shape::Type::LineString:
			archive(*shape.storage.lineString);
			break;
		case Shape::Type::Polygon:
			archive(*shape.storage.polygon);
			break;
		case Shape::Type::MultiPolygon:
			archive(*shape.storage.multiPolygon);
			break;
		}
	}

	template <class Archive>
	inline void load(Archive& archive, Shape& shape)
	{
		int32 t = 0;
		archive(t);
		const auto type = static_cast<Shape::Type>(t);
		shape = Shape(type);

		switch (type)
		{
		case Shape::Type::Point:
			archive(shape.storage.point);
			break;
		case Shape::Type::Vec2:
			archive(shape.storage.vec2);
			break;
		case Shape::Type::LineInt:
			archive(shape.storage.lineInt);
			break;
		case Shape::Type::Line:
			archive(shape.storage.line);
			break;
		case Shape::Type::Rect:
			archive(shape.storage.rect);
			break;
		case Shape::Type::RectF:
			archive(shape.storage.rectF);
			break;
		case Shape::Type::Circle:
			archive(shape.storage.circle);
			break;
		case Shape::Type::Ellipse:
			archive(shape.storage.ellipse);
			break;
		case Shape::Type::Triangle:
			archive(shape.storage.triangle);
			break;
		case Shape::Type::Quad:
			archive(*shape.storage.quad);
			break;
		case Shape::Type::RoundRect:
			archive(shape.storage.roundRect);
			break;
		case Shape::Type::LineString:
			archive(*shape.storage.lineString);
			break;
		case Shape::Type::Polygon:
			archive(*shape.storage.polygon);
			break;
		case Shape::Type::MultiPolygon:
			archive(*shape.storage.multiPolygon);
			break;
		}
	}

	//////////////////////////////////////////////////////
	//
	//	FloatRect
	//
	template <class Archive>
	void serialize(Archive& archive, FloatRect& floatRect)
	{
		archive(floatRect.left, floatRect.top, floatRect.right, floatRect.bottom);
	}

	//////////////////////////////////////////////////////
	//
	//	FloatQuad
	//
	template <class Archive>
	void serialize(Archive& archive, FloatQuad& floatQuad)
	{
		archive(floatQuad.tl, floatQuad.tr, floatQuad.br, floatQuad.bl);
	}

	//////////////////////////////////////////////////////
	//
	//	Xorshift64Star
	//
	template <class Archive>
	inline void save(Archive& archive, const Xorshift64Star& xorshift64Star)
	{
		archive(xorshift64Star.currentSeed());
	}

	template <class Archive>
	inline void load(Archive& archive, Xorshift64Star& xorshift64Star)
	{
		uint64 seed;
		archive(seed);
		xorshift64Star.seed(seed);
	}

	//////////////////////////////////////////////////////
	//
	//	Xorshift128Plus
	//
	template <class Archive>
	inline void save(Archive& archive, const Xorshift128Plus& xorshift128Plus)
	{
		archive(xorshift128Plus.currentSeed());
	}

	template <class Archive>
	inline void load(Archive& archive, Xorshift128Plus& xorshift128Plus)
	{
		std::array<uint64, 2> seeds;
		archive(seeds);
		xorshift128Plus.seed(seeds);
	}

	//////////////////////////////////////////////////////
	//
	//	Xorshift1024Star
	//
	template <class Archive>
	inline void save(Archive& archive, const Xorshift1024Star& xorshift1024Star)
	{
		archive(xorshift1024Star.currentSeed());
	}

	template <class Archive>
	inline void load(Archive& archive, Xorshift1024Star& xorshift1024Star)
	{
		std::array<uint64, 16> seeds;
		archive(seeds);
		xorshift1024Star.seed(seeds);
	}

	//////////////////////////////////////////////////////
	//
	//	RNG
	//
	template <class Archive>
	inline void save(Archive& archive, const RNG& rng)
	{
		archive(rng.serialize());
	}

	template <class Archive>
	inline void load(Archive& archive, RNG& rng)
	{
		std::string representation;
		archive(representation);
		rng.deserialize(representation);
	}

	//////////////////////////////////////////////////////
	//
	//	UniformDistribution
	//
	template <class Archive, class Type>
	inline void save(Archive& archive, const UniformDistribution<Type>& uniformDistribution)
	{
		archive(uniformDistribution.min(), uniformDistribution.max());
	}

	template <class Archive, class Type>
	inline void load(Archive& archive, UniformDistribution<Type>& uniformDistribution)
	{
		Type min, max;
		archive(min, max);
		uniformDistribution.set(min, max);
	}

	//////////////////////////////////////////////////////
	//
	//	NormalDistribution
	//
	template <class Archive>
	inline void save(Archive& archive, const NormalDistribution& normalDistribution)
	{
		archive(normalDistribution.mean(), normalDistribution.sigma());
	}

	template <class Archive>
	inline void load(Archive& archive, NormalDistribution& normalDistribution)
	{
		double mean, sigma;
		archive(mean, sigma);
		normalDistribution.set(mean, sigma);
	}

	//////////////////////////////////////////////////////
	//
	//	PerlinNoise
	//
	template <class Archive>
	inline void save(Archive& archive, const PerlinNoise& perlinNoise)
	{
		archive(perlinNoise.serialize());
	}

	template <class Archive>
	inline void load(Archive& archive, PerlinNoise& perlinNoise)
	{
		std::array<int32, 512> representation;
		archive(representation);
		perlinNoise.deserialize(representation);
	}

	//////////////////////////////////////////////////////
	//
	//	QuadraticBezier
	//
	template <class Archive>
	void serialize(Archive& archive, QuadraticBezier& quadraticBezier)
	{
		archive(quadraticBezier.p0, quadraticBezier.p1, quadraticBezier.p2);
	}

	//////////////////////////////////////////////////////
	//
	//	QuadraticBezierPath
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	CubicBezier
	//
	template <class Archive>
	void serialize(Archive& archive, CubicBezier& cubicBezier)
	{
		archive(cubicBezier.p0, cubicBezier.p1, cubicBezier.p2, cubicBezier.p3);
	}

	//////////////////////////////////////////////////////
	//
	//	CubicBezierPath
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	HalfFloat
	//
	template <class Archive>
	void serialize(Archive& archive, HalfFloat& halfFloat)
	{
		archive(halfFloat.m_value);
	}

	//////////////////////////////////////////////////////
	//
	//	ParsedExpression
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Image
	//
	template <class Archive>
	inline void save(Archive & ar, const Image& image)
	{
		const auto encoded = image.encodePNG();
		ar(cereal::make_size_tag(static_cast<cereal::size_type>(encoded.size())));
		ar(cereal::binary_data(encoded.data(), encoded.size()));
	}

	template <class Archive>
	inline void load(Archive& ar, Image& image)
	{
		cereal::size_type binarySize;
		ar(cereal::make_size_tag(binarySize));
		Array<uint8> binary(static_cast<size_t>(binarySize));
		ar(cereal::binary_data(binary.data(), binary.size()));
		image = Image(ByteArray(std::move(binary)));
	}

	//////////////////////////////////////////////////////
	//
	//	R32F
	//
	template <class Archive>
	void serialize(Archive& archive, R32F& r32f)
	{
		archive(r32f.r);
	}

	//////////////////////////////////////////////////////
	//
	//	RGBA16F
	//
	template <class Archive>
	void serialize(Archive& archive, RGBA16F& rgba16F)
	{
		archive(rgba16F.r, rgba16F.g, rgba16F.b, rgba16F.a);
	}

	//////////////////////////////////////////////////////
	//
	//	RGBA32F
	//
	template <class Archive>
	void serialize(Archive& archive, RGBA32F& rgba32F)
	{
		archive(rgba32F.r, rgba32F.g, rgba32F.b, rgba32F.a);
	}

	//////////////////////////////////////////////////////
	//
	//	R16F
	//
	template <class Archive>
	void serialize(Archive& archive, R16F& r16f)
	{
		archive(r16f.r);
	}

	//////////////////////////////////////////////////////
	//
	//	RG16F
	//
	template <class Archive>
	void serialize(Archive& archive, RG16F& rg16f)
	{
		archive(rg16f.r, rg16f.g);
	}

	//////////////////////////////////////////////////////
	//
	//	RG32F
	//
	template <class Archive>
	void serialize(Archive& archive, RG32F& rg32f)
	{
		archive(rg32f.r, rg32f.g);
	}

	//////////////////////////////////////////////////////
	//
	//	ImageR32F
	//

	//
	// Grid<R32F>
	//

	//////////////////////////////////////////////////////
	//
	//	ImageRGBA16F
	//

	//
	// Grid<RGBA16F>
	//

	//////////////////////////////////////////////////////
	//
	//	ImageRGBA32F
	//

	//
	// Grid<RGBA32F>
	//

	//////////////////////////////////////////////////////
	//
	//	ImageR16F
	//

	//
	// Grid<R16F>
	//

	//////////////////////////////////////////////////////
	//
	//	ImageRG16F
	//

	//
	// Grid<RG16F>
	//

	//////////////////////////////////////////////////////
	//
	//	ImageRG32F
	//

	//
	// Grid<RG32F>
	//

	//////////////////////////////////////////////////////
	//
	//	QRData
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	HandwritingCharacter
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	WaveSample
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	AudioProperty
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Wave
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	FFTResult
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	SerialDeveiceInfo
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	IPv4
	//
	template <class Archive>
	void serialize(Archive& archive, IPv4& ipv4)
	{
		archive(ipv4.asUint8);
	}

	//////////////////////////////////////////////////////
	//
	//	MidiNote
	//
	template <class Archive>
	void serialize(Archive& archive, MidiNote& midiNote)
	{
		archive(midiNote.noteNumber, midiNote.startMillisec, midiNote.lengthMillisec);
	}

	//////////////////////////////////////////////////////
	//
	//	WindowState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	ExtensionFilterPair
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	GraphicsProfile
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Key
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	PlusCombinedKeys
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	KeyCombination
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Touch
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	GamepadInfo
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	DeadZone
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	KinectV1Joint
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	KinectV1Body
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	KinectV2Joint
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	KinectV2Body
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	KinectV2AudioBeam
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	EyeXState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 SamplerState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 RasterizerState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 DepthState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 StencilState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 DepthStencilState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 SamplerState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 RenderState
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 SpriteVertex
	//

	//////////////////////////////////////////////////////
	//
	//	 Sprite
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 FontProperty
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	 TextStyle
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Quaternion
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Mat4x4
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Ray
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Line3D
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Triangle3D
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	MeshVertex
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	MeshData
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Plane
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Sphere
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Box
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Disc
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Cylinder
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Cone
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Material
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Camera
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Fog
	//

	//
	// unimplemented
	//

	//////////////////////////////////////////////////////
	//
	//	Light
	//

	//
	// unimplemented
	//
}

CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::BinaryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::BinaryReader>)
CEREAL_REGISTER_ARCHIVE(s3d::Serializer<s3d::MemoryWriter>)
CEREAL_REGISTER_ARCHIVE(s3d::Deserializer<s3d::ByteArray>)

# define S3D_SERIALIZE_SAVE  template <class Archive> void save(Archive& archive)
# define S3D_SERIALIZE_LOAD  template <class Archive> void load(Archive& archive)
# define S3D_SERIALIZE_SAVE_AND_LOAD  template <class Archive> void serialize(Archive& archive)
