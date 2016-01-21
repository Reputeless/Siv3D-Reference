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
# include <array>
# include "Fwd.hpp"
# include "Color.hpp"
# include "HSV.hpp"

namespace s3d
{
	/// <summary>
	/// トラッキングの状態
	/// </summary>
	enum class TrackingState
	{
		/// <summary>
		/// トラッキングされていない
		/// </summary>
		NotTracked,

		/// <summary>
		/// 遮蔽されている
		/// </summary>
		Inferred,

		/// <summary>
		/// トラッキングされている
		/// </summary>
		Tracked,
	};

	/// <summary>
	/// Kinect v1 の取得データフラグ
	/// </summary>
	struct KinectV1DataType
	{
		enum Type
		{
			/// <summary>
			/// カラー (80x60)
			/// </summary>
			Color_80x60		= 0x01,

			/// <summary>
			/// カラー (320x240)
			/// </summary>
			Color_320x240	= 0x02,

			/// <summary>
			/// カラー (640x480)
			/// </summary>
			Color_640x480	= 0x04,

			/// <summary>
			/// デプス (80x60)
			/// </summary>
			Depth_80x60		= 0X08,
			
			/// <summary>
			/// デプス (320x240)
			/// </summary>
			Depth_320x240	= 0x10,

			/// <summary>
			/// デプス (640x480)
			/// </summary>
			Depth_640x480	= 0x20,

			/// <summary>
			/// ボディインデックス
			/// </summary>
			BodyIndex		= 0x40,

			/// <summary>
			/// ボディ
			/// </summary>
			Body			= 0x80,

			/// <summary>
			/// 近接モード
			/// </summary>
			/// <remarks>
			/// 遠くの精度を犠牲にして、40cm からデプスを取得できます。
			/// </remarks>
			NearMode		= 0x1000,

			/// <summary>
			/// 着席モード
			/// </summary>
			SeatedMode		= 0x2000,

			/// <summary>
			/// デフォルト [デプス(640x480) | ボディインデックス | ボディ]
			/// </summary>
			Default			= Depth_640x480 | BodyIndex | Body,

			/// <summary>
			///	着席モードのデフォルト [デプス(640x480) | ボディインデックス | ボディ | 近接モード | 着席モード]
			/// </summary>
			DefaultSeated	= Depth_640x480 | BodyIndex | Body | NearMode | SeatedMode,
		};
	};

	/// <summary>
	/// 関節のインデックス
	/// </summary>
	struct V1JointType
	{
		enum Index
		{
			/// <summary>
			/// しり中央
			/// </summary>
			HipCenter,

			/// <summary>
			/// 背骨
			/// </summary>
			Spine,

			/// <summary>
			/// 肩の中心
			/// </summary>
			ShoulderCenter,

			/// <summary>
			/// 頭
			/// </summary>
			Head,

			/// <summary>
			/// 左肩
			/// </summary>
			ShoulderLeft,

			/// <summary>
			/// 左ひじ
			/// </summary>
			ElbowLeft,

			/// <summary>
			/// 左手首
			/// </summary>
			WristLeft,

			/// <summary>
			/// 左手
			/// </summary>
			HandLeft,

			/// <summary>
			/// 右肩
			/// </summary>
			ShoulderRight,

			/// <summary>
			/// 右ひじ
			/// </summary>
			ElbowRight,

			/// <summary>
			/// 右手首
			/// </summary>
			WristRight,

			/// <summary>
			/// 右手
			/// </summary>
			HandRight,

			/// <summary>
			/// 左尻
			/// </summary>
			HipLeft,

			/// <summary>
			/// 左ひざ
			/// </summary>
			KneeLeft,

			/// <summary>
			/// 左足首
			/// </summary>
			AnkleLeft,

			/// <summary>
			/// 左足
			/// </summary>
			FootLeft,

			/// <summary>
			/// 右尻
			/// </summary>
			HipRight,

			/// <summary>
			/// 右ひざ
			/// </summary>
			KneeRight,

			/// <summary>
			/// 右足首
			/// </summary>
			AnkleRight,

			/// <summary>
			/// 右足
			/// </summary>
			FootRight
		};
	};

	/// <summary>
	/// 関節の情報
	/// </summary>
	struct KinectV1Joint
	{
		/// <summary>
		/// カメラ空間での座標
		/// </summary>
		Vec3 cameraSpacePos = Vec3::Zero;

		/// <summary>
		/// デプス画像上の座標
		/// </summary>
		Vec2 depthSpacePos = Vec2::Zero;

		/// <summary>
		/// トラッキングの状態
		/// </summary>
		TrackingState trackingState = TrackingState::NotTracked;
	};

	/// <summary>
	/// Kinect v1 ボディ
	/// </summary>
	struct KinectV1Body
	{
		enum
		{
			/// <summary>
			/// 関節の個数
			/// </summary>
			Num_Joints = 20
		};

		/// <summary>
		/// 関節
		/// </summary>
		KinectV1Joint joints[Num_Joints];

		/// <summary>
		/// カメラ空間でのボディの座標
		/// </summary>
		Vec3 cameraSpaceBodyPos;

		/// <summary>
		/// デプス画像上のボディの座標
		/// </summary>
		Vec2 depthSpaceBodyPos;

		/// <summary>
		/// トラッキング ID
		/// </summary>
		int trackingID;
	};

	/// <summary>
	/// Kinect v1
	/// </summary>
	/// <remarks>
	/// Kinect v1 の機能を提供します。
	/// </remarks>
	namespace KinectV1
	{
		/// <summary>
		/// 深度を色に変換するデフォルトの関数です。
		/// </summary>
		/// <param name="d">
		/// デプス [mm]
		/// </param>
		/// <returns>
		/// 変換後の色
		/// </returns>
		inline Color DefaultDepthColoring(unsigned short d)
		{
			return d != 0 ? HueToColor(d / 6) : Palette::Black;
		}

		/// <summary>
		/// ボディインデックスを色に変換するデフォルトの関数です。
		/// </summary>
		/// <param name="index">
		/// ボディインデックス。何もない場合は 0
		/// </param>
		/// <returns>
		/// 変換後の色
		/// </returns>
		inline Color DefaultBodyIndexColoring(unsigned char index)
		{
			return index != 0 ? HueToColor(index * 60) : Palette::Black;
		}

		/// <summary>
		/// Kinect v1 が使用可能かを取得します。
		/// </summary>
		/// <returns>
		/// Kinect v1 が使用可能な場合 true, それ以外の場合は false
		/// </returns>
		bool IsAvailable();

		/// <summary>
		/// Kinect v1 を起動します。
		/// </summary>
		/// <param name="dataType">
		/// Kinect v1 の設定、KinectV1DataType::Type の組み合わせ
		/// </param>
		/// <returns>
		/// 起動に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Start(int32 dataType = KinectV1DataType::Default);

		/// <summary>
		/// Kinect v1 を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Stop();


		////////////////////////////////////////////////////////////////
		//
		//		カラー
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// 新しいカラーフレームがあるかを取得します。
		/// </summary>
		/// <returns>
		/// 新しいカラーフレームがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewColorFrame();

		/// <summary>
		/// カラーフレームを取得します。
		/// </summary>
		/// <param name="image">
		/// カラーフレームのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetColorFrame(Image& image);

		/// <summary>
		/// カラーフレームを取得します。
		/// </summary>
		/// <param name="texture">
		/// カラーフレームのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetColorFrame(DynamicTexture& texture);


		////////////////////////////////////////////////////////////////
		//
		//		デプス
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// 新しいデプスフレームがあるかを取得します。
		/// </summary>
		/// <returns>
		/// 新しいデプスフレームがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewDepthFrame();

		/// <summary>
		/// デプスデータにアクセスします。
		/// </summary>
		/// <returns>
		/// デプスデータへの参照
		/// </returns>
		const Grid<uint16>& GetRawDepthData();

		/// <summary>
		/// デプスフレームを取得します。
		/// </summary>
		/// <param name="image">
		/// デプスフレームのコピー先
		/// </param>
		/// <param name="coloring">
		/// 色の変換ルール
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetDepthFrame(Image& image, std::function<Color(uint16)> coloring = DefaultDepthColoring);

		/// <summary>
		/// デプスフレームを取得します。
		/// </summary>
		/// <param name="texture">
		/// デプスフレームのコピー先
		/// </param>
		/// <param name="coloring">
		/// 色の変換ルール
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetDepthFrame(DynamicTexture& texture, std::function<Color(uint16)> coloring = DefaultDepthColoring);


		////////////////////////////////////////////////////////////////
		//
		//		ボディインデックス
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// 新しいボディインデックスフレームがあるかを取得します。
		/// </summary>
		/// <returns>
		/// 新しいボディインデックスフレームがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewBodyIndexFrame();

		/// <summary>
		/// ボディインデックスデータにアクセスします。
		/// </summary>
		/// <returns>
		/// ボディインデックスデータへの参照
		/// </returns>
		const Grid<uint8>& GetRawBodyIndexData();

		/// <summary>
		/// ボディインデックスフレームを取得します。
		/// </summary>
		/// <param name="image">
		/// ボディインデックスフレームのコピー先
		/// </param>
		/// <param name="coloring">
		/// 色の変換ルール
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetBodyIndexFrame(Image& image, std::function<Color(uint8)> coloring = DefaultBodyIndexColoring);

		/// <summary>
		/// ボディインデックスフレームを取得します。
		/// </summary>
		/// <param name="texture">
		/// ボディインデックスフレームのコピー先
		/// </param>
		/// <param name="coloring">
		/// 色の変換ルール
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetBodyIndexFrame(DynamicTexture& texture, std::function<Color(uint8)> coloring = DefaultBodyIndexColoring);
		

		////////////////////////////////////////////////////////////////
		//
		//		ボディ
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// 新しいボディフレームがあるかを取得します。
		/// </summary>
		/// <returns>
		/// 新しいボディフレームがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewBodyFrame();

		/// <summary>
		/// ボディフレームを取得します。
		/// </summary>
		/// <param name="bodies">
		/// ボディフレームのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetBodyFrame(std::array<Optional<KinectV1Body>, 2>& bodies);


		////////////////////////////////////////////////////////////////
		//
		//		本体の設定
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// 現在の Kinect カメラの角度を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Kinect カメラの角度
		/// </returns>
		int32 GetElevation();

		/// <summary>
		/// Kinect カメラの角度を設定します。
		/// </summary>
		/// <param name="angleDegree">
		/// 角度
		/// </param>
		/// <remarks>
		/// angleDegree は [-27,27] にクランプされます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetElevation(int32 angleDegree);

		/// <summary>
		/// Kinect にかかっている加速度を取得します。
		/// </summary>
		/// <remarks>
		/// 水平に静止している場合 Vec3(0,-1,0) を返します。
		/// </remarks>
		/// <returns>
		/// Kinect にかかっている加速度。取得に失敗した場合は Vec3::Zero
		/// </returns>
		Vec3 GetAcceleration();
	}
}
