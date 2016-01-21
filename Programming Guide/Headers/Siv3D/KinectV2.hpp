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
# include "KinectV1.hpp"

namespace s3d
{
	/// <summary>
	/// Kinect v2 の取得データフラグ
	/// </summary>
	struct KinectV2DataType
	{
		enum Type
		{
			/// <summary>
			/// カラー (1920×1080)
			/// </summary>
			Color		= 0x01,

			/// <summary>
			/// デプス (512×424)
			/// </summary>
			Depth		= 0x02,

			/// <summary>
			/// ボディインデックス
			/// </summary>
			BodyIndex	= 0x04,

			/// <summary>
			/// ボディ
			/// </summary>
			Body		= 0x08,

			/// <summary>
			/// 赤外線 (512×424)
			/// </summary>
			Infrared	= 0x10,

			/// <summary>
			/// オーディオビーム
			/// </summary>
			AudioBeam	= 0x20,

			/// <summary>
			/// デフォルト [カラー (1920×1080) | デプス (512×424) | ボディインデックス | ボディ]
			/// </summary>
			Default		= Color | Depth | BodyIndex | Body,
		};
	};

	/// <summary>
	/// 手の状態
	/// </summary>
	enum class HandState
	{
		/// <summary>
		/// 不明
		/// </summary>
		Unknown,

		/// <summary>
		/// 追跡されていない
		/// </summary>
		NotTracked,

		/// <summary>
		/// 開いている
		/// </summary>
		Open,

		/// <summary>
		/// 閉じている
		/// </summary>
		Closed,

		/// <summary>
		/// チョキ
		/// </summary>
		Lasso,
	};

	/// <summary>
	/// 関節のインデックス
	/// </summary>
	struct V2JointType
	{
		enum Type
		{
			/// <summary>
			/// 背骨の下部
			/// </summary>
			SpineBase,

			/// <summary>
			/// 背骨の中央
			/// </summary>
			SpineMid,

			/// <summary>
			/// 首
			/// </summary>
			Neck,

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
			FootRight,

			/// <summary>
			/// 肩の高さの背骨
			/// </summary>
			SpineShoulder,

			/// <summary>
			/// 左手の先端
			/// </summary>
			HandTipLeft,

			/// <summary>
			/// 左手の親指
			/// </summary>
			ThumbLeft,

			/// <summary>
			/// 右手の先端
			/// </summary>
			HandTipRight,

			/// <summary>
			/// 右手の親指
			/// </summary>
			ThumbRight,
		};
	};

	/// <summary>
	/// 関節の情報
	/// </summary>
	struct KinectV2Joint
	{
		/// <summary>
		/// カメラ空間での座標
		/// </summary>
		Vec3 cameraSpacePos = Vec3::Zero;

		/// <summary>
		/// カラー画像(1920x1080)上の座標
		/// </summary>
		Vec2 colorSpacePos = Vec2::Zero;

		/// <summary>
		/// デプス画像(512×424)上の座標
		/// </summary>
		Vec2 depthSpacePos = Vec2::Zero;

		/// <summary>
		/// トラッキングの状態
		/// </summary>
		TrackingState trackingState = TrackingState::NotTracked;
	};

	/// <summary>
	/// Kinect v2 ボディ
	/// </summary>
	struct KinectV2Body
	{
		enum
		{
			/// <summary>
			/// 関節の個数
			/// </summary>
			Num_Joints = 25
		};

		/// <summary>
		/// 関節
		/// </summary>
		KinectV2Joint joints[Num_Joints];

		/// <summary>
		/// 体の傾き
		/// </summary>
		Vec2 lean = Vec2::Zero;

		/// <summary>
		/// 左手の状態
		/// </summary>
		HandState leftHand = HandState::Unknown;

		/// <summary>
		/// 右手の状態
		/// </summary>
		HandState rightHand = HandState::Unknown;

		/// <summary>
		/// 左手の追跡が高信頼であるか
		/// </summary>
		bool leftHandHighConfidence = false;

		/// <summary>
		/// 右手の追跡が高信頼であるか
		/// </summary>
		bool rightHandHighConfidence = false;
	};

	/// <summary>
	/// オーディオビーム
	/// </summary>
	struct KinectV2AudioBeam
	{
		/// <summary>
		/// オーディオの方向（ラジアン）
		/// </summary>
		double angle = 0.0;

		/// <summary>
		/// オーディオの方向の信頼性 [0.0, 1.0]
		/// </summary>
		double confidence = 0.0;
	};

	/// <summary>
	/// Kinect v2
	/// </summary>
	/// <remarks>
	/// Kinect v2 の機能を提供します。
	/// </remarks>
	namespace KinectV2
	{
		/// <summary>
		/// 深度を色に変換するデフォルトの関数です。
		/// </summary>
		/// <param name="depth">
		/// デプス [mm]
		/// </param>
		/// <returns>
		/// 変換後の色
		/// </returns>
		inline Color DefaultDepthColoring(uint16 depth)
		{
			return depth != 0 ? HueToColor(depth / 4.0) : Palette::Black;
		}

		/// <summary>
		/// ボディインデックスを色に変換するデフォルトの関数です。
		/// </summary>
		/// <param name="index">
		/// ボディインデックス。何もない場合は 255
		/// </param>
		/// <returns>
		/// 変換後の色
		/// </returns>
		inline Color DefaultBodyIndexColoring(uint8 index)
		{
			return index != 255 ? HueToColor(index * 60) : Palette::Black;
		}

		/// <summary>
		/// 赤外線を色に変換するデフォルトの関数です。
		/// </summary>
		/// <param name="infrared">
		/// 赤外線
		/// </param>
		/// <returns>
		/// 変換後の色
		/// </returns>
		inline Color DefaultInfraredColoring(uint16 infrared)
		{
			return Color(infrared / 256);
		}

		/// <summary>
		/// Kinect v2 が使用可能かを取得します。
		/// </summary>
		/// <returns>
		/// Kinect v2 が使用可能な場合 true, それ以外の場合は false
		/// </returns>
		bool IsAvailable();

		/// <summary>
		/// Kinect v2 を起動します。
		/// </summary>
		/// <param name="dataType">
		/// Kinect v2 の設定、KinectV2DataType::Type の組み合わせ
		/// </param>
		/// <returns>
		/// 起動に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool Start(int32 dataType = KinectV2DataType::Default);


		////////////////////////////////////////////////////////////////
		//
		//		カラー
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// カラーフレームの撮影を開始 / 再開します。
		/// </summary>
		/// <returns>
		/// カラーフレームの撮影開始 / 再開に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool StartColorFrame();

		/// <summary>
		/// カラーフレームの撮影を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void StopColorFrame();

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
		/// デプスフレームの撮影を開始 / 再開します。
		/// </summary>
		/// <returns>
		/// デプスフレームの撮影開始 / 再開に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool StartDepthFrame();

		/// <summary>
		/// デプスフレームの撮影を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void StopDepthFrame();

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
		/// ボディインデックスの取得を開始 / 再開します。
		/// </summary>
		/// <returns>
		/// ボディインデックスの取得開始 / 再開に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool StartBodyIndexFrame();

		/// <summary>
		/// ボディインデックスの取得を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void StopBodyIndexFrame();

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
		/// ボディの取得を開始 / 再開します。
		/// </summary>
		/// <returns>
		/// ボディの取得開始 / 再開に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool StarBodyFrame();

		/// <summary>
		/// ボディの取得を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void StopBodyFrame();

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
		bool GetBodyFrame(std::array<Optional<KinectV2Body>, 6>& bodies);


		////////////////////////////////////////////////////////////////
		//
		//		赤外線
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// 赤外線の撮影を開始 / 再開します。
		/// </summary>
		/// <returns>
		/// 赤外線の撮影開始 / 再開に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool StartInfraredFrame();

		/// <summary>
		/// 赤外線の撮影を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void StopInfraredFrame();

		/// <summary>
		/// 新しい赤外線フレームがあるかを取得します。
		/// </summary>
		/// <returns>
		/// 新しい赤外線フレームがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewInfraredFrame();

		/// <summary>
		/// 赤外線データにアクセスします。
		/// </summary>
		/// <returns>
		/// 赤外線データへの参照
		/// </returns>
		const Grid<uint16>& GetRawInfraredData();

		/// <summary>
		/// 赤外線フレームを取得します。
		/// </summary>
		/// <param name="image">
		/// 赤外線フレームのコピー先
		/// </param>
		/// <param name="coloring">
		/// 色の変換ルール
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetInfraredFrame(Image& image, std::function<Color(uint16)> coloring = DefaultInfraredColoring);

		/// <summary>
		/// 赤外線フレームを取得します。
		/// </summary>
		/// <param name="texture">
		/// 赤外線フレームのコピー先
		/// </param>
		/// <param name="coloring">
		/// 色の変換ルール
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetInfraredFrame(DynamicTexture& texture, std::function<Color(uint16)> coloring = DefaultInfraredColoring);


		////////////////////////////////////////////////////////////////
		//
		//		オーディオビーム
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// オーディオビームの取得を開始 / 再開します。
		/// </summary>
		/// <returns>
		/// オーディオビームの取得開始 / 再開に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool StarAudioBeamFrame();

		/// <summary>
		/// オーディオビームの取得を停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void StopAudioBeamFrame();

		/// <summary>
		/// 新しいオーディオビームフレームがあるかを取得します。
		/// </summary>
		/// <returns>
		/// 新しいオーディオビームフレームがある場合 true, それ以外の場合は false
		/// </returns>
		bool HasNewAudioBeamFrame();

		/// <summary>
		/// オーディオビームフレームを取得します。
		/// </summary>
		/// <param name="audioBeam">
		/// オーディオビームフレームのコピー先
		/// </param>
		/// <returns>
		/// 取得に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool GetAudioBeamFrame(KinectV2AudioBeam& audioBeam);
	}
}
