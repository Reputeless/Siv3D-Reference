﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Types.hpp"

namespace s3d
{
	//////////////////////////////////////////////////////
	//
	//	Uncopyable.hpp
	//
	class Uncopyable;

	//////////////////////////////////////////////////////
	//
	//	Optional.hpp
	//
	template <class Type> class Optional;

	//////////////////////////////////////////////////////
	//
	//	Grid.hpp
	//
	template <class Type> class Grid;

	//////////////////////////////////////////////////////
	//
	//	String.hpp
	//
	class String;
	using FilePath = String;
	using URL = String;

	//////////////////////////////////////////////////////
	//
	//	StringView.hpp
	//
	class StringView;

	//////////////////////////////////////////////////////
	//
	//	Date.hpp
	//
	struct Date;

	//////////////////////////////////////////////////////
	//
	//	DateTime.hpp
	//
	struct DateTime;

	//////////////////////////////////////////////////////
	//
	//	Stopwatch.hpp
	//
	class Stopwatch;
	class Stopwatch64;
	class StopwatchMicrosec;

	//////////////////////////////////////////////////////
	//
	//	EventTimer.hpp
	//
	class EventTimer;

	//////////////////////////////////////////////////////
	//
	//	VariableSpeedStopwatch.hpp
	//
	class VariableSpeedStopwatch;

	//////////////////////////////////////////////////////
	//
	//	ProfilerUtility.hpp
	//
	class MillisecClock;
	class MicrosecClock;
	class RDTSCClock;

	//////////////////////////////////////////////////////
	//
	//	FileSystem.hpp
	//
	enum class OpenMode;
	enum class TextEncoding;
	enum class CopyOption;

	//////////////////////////////////////////////////////
	//
	//	Handle.hpp
	//
	using HandleIDType = uint32;

	//////////////////////////////////////////////////////
	//
	//	FileMonitor.hpp
	//
	enum class FileAction;
	class FileMonitor;

	//////////////////////////////////////////////////////
	//
	//	IReader.hpp
	//
	class IReader;

	//////////////////////////////////////////////////////
	//
	//	ByteArray.hpp
	//
	class ByteArray;

	//////////////////////////////////////////////////////
	//
	//	BinaryReader.hpp
	//
	class BinaryReader;

	//////////////////////////////////////////////////////
	//
	//	IWriter.hpp
	//
	class IWriter;

	//////////////////////////////////////////////////////
	//
	//	MemoryWriter.hpp
	//
	class MemoryWriter;

	//////////////////////////////////////////////////////
	//
	//	BinaryWriter.hpp
	//
	class BinaryWriter;

	//////////////////////////////////////////////////////
	//
	//	TextReader.hpp
	//
	class TextReader;

	//////////////////////////////////////////////////////
	//
	//	TextWriter.hpp
	//
	class TextWriter;

	//////////////////////////////////////////////////////
	//
	//	MD5.hpp
	//
	struct MD5Value;

	//////////////////////////////////////////////////////
	//
	//	Logger.hpp
	//
	enum class OutputLevel;
	enum class LogDescription;

	//////////////////////////////////////////////////////
	//
	//	Crypto.hpp
	//
	union AES128Key;
	union AESIV;

	//////////////////////////////////////////////////////
	//
	//	ArchivedFileReader.hpp
	//
	class ArchivedFileReader;

	//////////////////////////////////////////////////////
	//
	//	FileArchive.hpp
	//
	class FileArchive;

	//////////////////////////////////////////////////////
	//
	//	CSVReader.hpp
	//
	class CSVReader;

	//////////////////////////////////////////////////////
	//
	//	CSVWriter.hpp
	//
	class CSVWriter;

	//////////////////////////////////////////////////////
	//
	//	INIReader.hpp
	//
	class INIReader;

	//////////////////////////////////////////////////////
	//
	//	INIWriter.hpp
	//
	class INIWriter;

	//////////////////////////////////////////////////////
	//
	//	XMLReader.hpp
	//
	class XMLElement;
	class XMLReader;

	//////////////////////////////////////////////////////
	//
	//	JSONValue.hpp
	//
	class JSONValue;

	//////////////////////////////////////////////////////
	//
	//	JSONReader.hpp
	//
	class JSONReader;

	//////////////////////////////////////////////////////
	//
	//	ZIPReader.hpp
	//
	class ZIPReader;

	//////////////////////////////////////////////////////
	//
	//	ZIPWriter.hpp
	//
	class ZIPWriter;

	//////////////////////////////////////////////////////
	//
	//	Color.hpp
	//
	struct Color;
	struct ColorF;

	//////////////////////////////////////////////////////
	//
	//	HSV.hpp
	//
	struct HSV;

	//////////////////////////////////////////////////////
	//
	//	PointVector.hpp
	//
	struct Point;
	using Size = Point;
	template <class Type> struct Vector2D;
	template <class Type> struct Vector3D;
	template <class Type> struct Vector4D;
	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using Float3	= Vector3D<float>;
	using Vec3		= Vector3D<double>;
	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;

	//////////////////////////////////////////////////////
	//
	//	Circular.hpp
	//
	template<int32 Oclock> struct  CircularBase;
	using Circular = CircularBase<0>;
	using Circular0 = CircularBase<0>;
	using Circular3 = CircularBase<3>;
	using Circular6 = CircularBase<6>;
	using Circular9 = CircularBase<9>;

	//////////////////////////////////////////////////////
	//
	//	Cylindrical.hpp
	//
	struct Cylindrical;

	//////////////////////////////////////////////////////
	//
	//	Spherical.hpp
	//
	struct Spherical;

	//////////////////////////////////////////////////////
	//
	//	Mat3x2.hpp
	//
	struct Mat3x2;

	//////////////////////////////////////////////////////
	//
	//	Line.hpp
	//
	struct  LineInt;
	struct  Line;

	//////////////////////////////////////////////////////
	//
	//	Rectangle.hpp
	//
	template <class SizeType, class ElementType> struct Rectangle;
	using Rect = Rectangle<Point, int>;
	using RectF = Rectangle<Vec2, double>;

	//////////////////////////////////////////////////////
	//
	//	Circle.hpp
	//
	struct Circle;

	//////////////////////////////////////////////////////
	//
	//	Ellipse.hpp
	//
	struct Ellipse;

	//////////////////////////////////////////////////////
	//
	//	Triangle.hpp
	//
	struct Triangle;

	//////////////////////////////////////////////////////
	//
	//	Quad.hpp
	//
	struct Quad;

	//////////////////////////////////////////////////////
	//
	//	RoundRect.hpp
	//
	struct RoundRect;

	//////////////////////////////////////////////////////
	//
	//	LineString.hpp
	//
	class LineString;

	//////////////////////////////////////////////////////
	//
	//	Polygon.hpp
	//
	class PolygonHoles;
	class Polygon;
	class PolygonTriangles;

	//////////////////////////////////////////////////////
	//
	//	MultiPolygon.hpp
	//
	class MultiPolygon;

	//////////////////////////////////////////////////////
	//
	//	Shape.hpp
	//
	class Shape;

	//////////////////////////////////////////////////////
	//
	//	FloatShape.hpp
	//
	struct FloatRect;
	struct FloatQuad;

	//////////////////////////////////////////////////////
	//
	//	RNG.hpp
	//
	class Xorshift64Star;
	class Xorshift128Plus;
	class Xorshift1024Star;
	class RNG;

	//////////////////////////////////////////////////////
	//
	//	Distribution.hpp
	//
	template <class Type> class UniformDistribution;
	class NormalDistribution;

	//////////////////////////////////////////////////////
	//
	//	EasingController.hpp
	//
	template <class Type> class EasingController;

	//////////////////////////////////////////////////////
	//
	//	PerlinNoise.hpp
	//
	class PerlinNoise;

	//////////////////////////////////////////////////////
	//
	//	QuadraticBezier.hpp
	//
	struct QuadraticBezier;
	struct QuadraticBezierPath;

	//////////////////////////////////////////////////////
	//
	//	CubicBezier.hpp
	//
	struct CubicBezier;
	struct CubicBezierPath;

	//////////////////////////////////////////////////////
	//
	//	SIMD.hpp
	//
	enum class SSE;

	//////////////////////////////////////////////////////
	//
	//	HalfFloat.hpp
	//
	struct HalfFloat;

	//////////////////////////////////////////////////////
	//
	//	ExpressionParser.hpp
	//
	class ParsedExpression;

	//////////////////////////////////////////////////////
	//
	//	Image.hpp
	//
	enum class ImageFormat;
	enum class DDSFormat;
	enum class WebPMethod;
	enum class Interpolation;
	enum class ImageAddressMode;
	enum class AdaptiveMethod;
	enum class Interpolation;
	enum class FloodFillConnectivity;
	enum class CascadeType;
	class Image;
	class ImageRegion;

	//////////////////////////////////////////////////////
	//
	//	TextureFormat.hpp
	//
	enum class TextureFormat;

	//////////////////////////////////////////////////////
	//
	//	CustomColor.hpp
	//
	struct R32F;
	struct RGBA16F;
	struct RGBA32F;
	struct R16F;
	struct RG16F;
	struct RG32F;

	//////////////////////////////////////////////////////
	//
	//	CustomImage.hpp
	//
	template <class Type> class CustomImage;
	using ImageR32F = CustomImage<R32F>;
	using ImageRGBA16F = CustomImage<RGBA16F>;
	using ImageRGBA32F = CustomImage<RGBA32F>;
	using ImageR16F = CustomImage<R16F>;
	using ImageRG16F = CustomImage<RG16F>;
	using ImageRG32F = CustomImage<RG32F>;

	//////////////////////////////////////////////////////
	//
	//	QR.hpp
	//
	enum class QREncodingMode;
	enum class QRECLevel;
	struct QRData;

	//////////////////////////////////////////////////////
	//
	//	HandwritingRecognizer.hpp
	//
	struct HandwritingCharacter;
	class HandwritingRecognizer;

	//////////////////////////////////////////////////////
	//
	//	HandwritingTrainer.hpp
	//
	class HandwritingTrainer;

	//////////////////////////////////////////////////////
	//
	//	WaveSample.hpp
	//
	struct WaveSample;

	//////////////////////////////////////////////////////
	//
	//	Wave.hpp
	//
	enum class AudioFormat;
	struct AudioProperty;
	enum class WAVEFormat;
	enum class MP3Quality;
	enum class AACQuality;
	struct OggVorbisLoopExtension;
	class Wave;

	//////////////////////////////////////////////////////
	//
	//	WaveStretcher.hpp
	//
	class WaveStretcher;

	//////////////////////////////////////////////////////
	//
	//	FFT.hpp
	//
	enum class FFTSampleLength;
	class FFTResult;

	//////////////////////////////////////////////////////
	//
	//	AnimatedGIFWriter.hpp
	//
	class AnimatedGIFWriter;

	//////////////////////////////////////////////////////
	//
	//	VideoReader.hpp
	//
	class VideoReader;

	//////////////////////////////////////////////////////
	//
	//	VideoWriter.hpp
	//
	enum class VideoCompression;
	enum class VideoFormat;
	class VideoWriter;

	//////////////////////////////////////////////////////
	//
	//	Serial.hpp
	//
	class Serial;
	struct SerialDeveiceInfo;

	//////////////////////////////////////////////////////
	//
	//	PipeServer.hpp
	//
	class PipeServer;

	//////////////////////////////////////////////////////
	//
	//	HTTPClient.hpp
	//
	enum class DownloadStatus;
	struct DownloadProgress;
	class HTTPClient;

	//////////////////////////////////////////////////////
	//
	//	Twitter.hpp
	//
	class TwitterClient;

	//////////////////////////////////////////////////////
	//
	//	Network.hpp
	//
	enum class NetworkErrorCode;
	union IPv4;

	//////////////////////////////////////////////////////
	//
	//	TCPServer.hpp
	//
	class TCPServer;

	//////////////////////////////////////////////////////
	//
	//	TCPClient.hpp
	//
	class TCPClient;

	//////////////////////////////////////////////////////
	//
	//	Script.hpp
	//
	class Script;
	template <class Type> struct ScriptFunction;

	//////////////////////////////////////////////////////
	//
	//	Midi.hpp
	//
	struct MidiNote;
	enum class PitchName : uint8;
	enum class GMInstrument : uint8;

	//////////////////////////////////////////////////////
	//
	//	System.hpp
	//
	struct WindowEvent;
	enum class LaunchVerb;
	class ProcessInfo;

	//////////////////////////////////////////////////////
	//
	//	 Window.hpp
	//
	enum class WindowStyle;
	struct WindowState;

	//////////////////////////////////////////////////////
	//
	//	 MessageBox.hpp
	//
	enum class MessageBoxStyle;
	enum class MessageBoxCommand;

	//////////////////////////////////////////////////////
	//
	//	 Clipboard.hpp
	//
	enum class ClipboardItemType;

	//////////////////////////////////////////////////////
	//
	//	 Clipboard.hpp
	//
	enum class ExtensionFilter;
	struct ExtensionFilterPair;

	//////////////////////////////////////////////////////
	//
	//	 Profiler.hpp
	//
	struct GraphicsProfile;

	//////////////////////////////////////////////////////
	//
	//	 Recorder.hpp
	//
	enum class RecordingFormat;
	class Recorder;

	//////////////////////////////////////////////////////
	//
	//	 Key.hpp
	//
	class Key;
	class PlusCombinedKeys;
	class KeyCombination;

	//////////////////////////////////////////////////////
	//
	//	 Touch.hpp
	//
	struct Touch;

	//////////////////////////////////////////////////////
	//
	//	 Gamepad.hpp
	//
	struct GamepadInfo;
	enum class DeadZoneType;
	struct DeadZone;
	class Gamepad;

	//////////////////////////////////////////////////////
	//
	//	 XInput.hpp
	//
	class XInput;

	//////////////////////////////////////////////////////
	//
	//	 KinectV1.hpp
	//
	enum class TrackingState;
	struct KinectV1Joint;
	struct KinectV1Body;

	//////////////////////////////////////////////////////
	//
	//	 KinectV2.hpp
	//
	enum class HandState;
	struct KinectV2Joint;
	struct KinectV2Body;
	struct KinectV2AudioBeam;

	//////////////////////////////////////////////////////
	//
	//	 TobiiEyeX.hpp
	//
	struct EyeXState;

	//////////////////////////////////////////////////////
	//
	//	 Sound.hpp
	//
	struct SoundLoop;
	struct SoundEmitter;
	struct SoundListener;
	enum class SoundDesc;
	class Sound;

	//////////////////////////////////////////////////////
	//
	//	 SoundBeat.hpp
	//
	struct BeatCount;
	class SoundBeat;

	//////////////////////////////////////////////////////
	//
	//	 SamplerState.hpp
	//
	enum class Blend : uint8;
	enum class BlendOp : uint8;
	struct BlendState;

	//////////////////////////////////////////////////////
	//
	//	 RasterizerState.hpp
	//
	enum class FillMode : uint8;
	enum class CullMode : uint8;
	struct RasterizerState;

	//////////////////////////////////////////////////////
	//
	//	 DepthStencilState.hpp
	//
	enum class DepthFunc : uint16;
	struct DepthState;
	enum class StencilOp : uint8;
	enum class StencilFunc : uint8;
	struct StencilState;
	struct DepthStencilState;

	//////////////////////////////////////////////////////
	//
	//	 SamplerState.hpp
	//
	enum class TextureFilter : uint8;
	enum class TextureAddressMode : uint8;
	struct SamplerState;

	//////////////////////////////////////////////////////
	//
	//	 RenderState.hpp
	//
	struct RenderState;

	//////////////////////////////////////////////////////
	//
	//	 Shader.hpp
	//
	enum class ShaderType;
	enum class ShaderStage;

	//////////////////////////////////////////////////////
	//
	//	 VertexShader.hpp
	//
	class VertexShader;

	//////////////////////////////////////////////////////
	//
	//	 PixelShader.hpp
	//
	class PixelShader;

	//////////////////////////////////////////////////////
	//
	//	 ConstantBuffer.hpp
	//
	class ConstantBufferBase;
	template <class Type> class ConstantBuffer;

	//////////////////////////////////////////////////////
	//
	//	 InputLayout.hpp
	//
	enum class InputClassification;
	struct InputElementDesc;
	class InputLayout;

	//////////////////////////////////////////////////////
	//
	//	 Texture.hpp
	//
	enum class TextureDesc;
	struct MultiSampling;
	class Texture;

	//////////////////////////////////////////////////////
	//
	//	 TextureRegion.hpp
	//
	struct TextureRegion;

	//////////////////////////////////////////////////////
	//
	//	 TexturedQuad.hpp
	//
	struct TexturedQuad;

	//////////////////////////////////////////////////////
	//
	//	 DynamicTexture.hpp
	//
	class DynamicTexture;

	//////////////////////////////////////////////////////
	//
	//	 RenderTexture.hpp
	//
	class RenderTexture;

	//////////////////////////////////////////////////////
	//
	//	 Sprite.hpp
	//
	struct SpriteVertex;
	class Sprite;

	//////////////////////////////////////////////////////
	//
	//	 KineticTypography.hpp
	//
	struct KineticTypography;

	//////////////////////////////////////////////////////
	//
	//	 Font.hpp
	//
	enum class FontStyle;
	struct FontProperty;
	struct TextOutlineStyle;
	class Font;
	class DrawableString;
	struct TextStyle;

	//////////////////////////////////////////////////////
	//
	//	 WidgetStyle.hpp
	//
	struct Padding;
	struct Margin;
	enum class Align;
	enum class Repeat;
	struct Background;
	struct WidgetStyle;
	struct WidgetState;

	//////////////////////////////////////////////////////
	//
	//	 Widget.hpp
	//
	class IWidget;

	//////////////////////////////////////////////////////
	//
	//	 GUIText.hpp
	//
	class GUIText;
	class GUITextWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUINewLine.hpp
	//
	class GUINewLine;
	class GUINewLineWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUITexture.hpp
	//
	class GUITexture;
	class GUITextureWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUIHorizontalLine.hpp
	//
	class GUIHorizontalLine;
	class GUIHorizontalLineWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUIButton.hpp
	//
	class GUIButton;
	class GUIButtonWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUIToggleSwitch.hpp
	//
	class GUIToggleSwitch;
	class GUIToggleSwitchWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUISlider.hpp
	//
	class GUISlider;
	class GUISliderWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUICheckBox.hpp
	//
	class GUICheckBox;
	class GUICheckBoxWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUIRadioButton.hpp
	//
	class GUIRadioButton;
	class GUIRadioButtonWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUITextField.hpp
	//
	class GUITextField;
	class GUITextFieldWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUITextArea.hpp
	//
	class GUITextArea;
	class GUITextAreaWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUIColorPalette.hpp
	//
	class GUIColorPalette;
	class GUIColorPaletteWrapper;

	//////////////////////////////////////////////////////
	//
	//	 GUI.hpp
	//
	struct GUIStyle;
	class GUI;

	//////////////////////////////////////////////////////
	//
	//	 Cursor.hpp
	//
	enum class CursorType;
	struct CursorStyle;

	//////////////////////////////////////////////////////
	//
	//	 VideoPlayer.hpp
	//
	class VideoPlayer;

	//////////////////////////////////////////////////////
	//
	//	 Webcam.hpp
	//
	struct WebcamInfo;
	class Webcam;

	//////////////////////////////////////////////////////
	//
	//	 AR.hpp
	//
	struct ARMarker;

	//////////////////////////////////////////////////////
	//
	//	Quaternion.hpp
	//
	struct Quaternion;

	//////////////////////////////////////////////////////
	//
	//	Mat4x4.hpp
	//
	struct Mat4x4;

	//////////////////////////////////////////////////////
	//
	//	Ray.hpp
	//
	struct Ray;

	//////////////////////////////////////////////////////
	//
	//	Line3D.hpp
	//
	struct Line3D;

	//////////////////////////////////////////////////////
	//
	//	Triangle3D.hpp
	//
	struct Triangle3D;

	//////////////////////////////////////////////////////
	//
	//	MeshData.hpp
	//
	struct MeshVertex;
	enum class PlaneFace;
	struct MeshData;

	//////////////////////////////////////////////////////
	//
	//	Mesh.hpp
	//
	class Mesh;

	//////////////////////////////////////////////////////
	//
	//	DynamicMesh.hpp
	//
	class DynamicMesh;

	//////////////////////////////////////////////////////
	//
	//	TransformedMesh.hpp
	//
	struct TransformedMesh;

	//////////////////////////////////////////////////////
	//
	//	Particle.hpp
	//
	struct Particle;

	//////////////////////////////////////////////////////
	//
	//	Plane.hpp
	//
	struct Plane;

	//////////////////////////////////////////////////////
	//
	//	Sphere.hpp
	//
	struct Sphere;

	//////////////////////////////////////////////////////
	//
	//	Box.hpp
	//
	struct Box;

	//////////////////////////////////////////////////////
	//
	//	Disc.hpp
	//
	struct Disc;

	//////////////////////////////////////////////////////
	//
	//	Cylinder.hpp
	//
	struct Cylinder;

	//////////////////////////////////////////////////////
	//
	//	Cone.hpp
	//
	struct Cone;

	//////////////////////////////////////////////////////
	//
	//	Model.hpp
	//
	struct Material;
	struct ModelNode;
	class Model;

	//////////////////////////////////////////////////////
	//
	//	Camera.hpp
	//
	struct Camera;

	//////////////////////////////////////////////////////
	//
	//	Fog.hpp
	//
	struct Fog;

	//////////////////////////////////////////////////////
	//
	//	Light.hpp
	//
	struct Light;

	//////////////////////////////////////////////////////
	//
	//	Graphics3D.hpp
	//
	enum class Renderer;
	enum class AntiAliasing;

	//////////////////////////////////////////////////////
	//
	//	Asset.hpp
	//
	using AssetName = String;
	using AssetTag = String;
	class IAsset;

	//////////////////////////////////////////////////////
	//
	//	SoundAsset.hpp
	//
	struct SoundAssetData;
	class SoundAsset;

	//////////////////////////////////////////////////////
	//
	//	TextureAsset.hpp
	//
	struct TextureAssetData;
	class TextureAsset;

	//////////////////////////////////////////////////////
	//
	//	FontAsset.hpp
	//
	struct FontAssetData;
	class FontAsset;

	//////////////////////////////////////////////////////
	//
	//	GUIAsset.hpp
	//
	struct GUIAssetData;
	class GUIAsset;

	//////////////////////////////////////////////////////
	//
	//	Effect.hpp
	//
	struct IEffect;
	class Effect;

	//////////////////////////////////////////////////////
	//
	//	Addon.hpp
	//
	class IAddon;

	//////////////////////////////////////////////////////
	//
	//	ApplicationUtility.hpp
	//
	class PutText;
}
