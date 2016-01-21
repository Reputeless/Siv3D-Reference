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
# pragma warning(disable:4512)
# include <Leap.h>
# pragma warning(default:4512)
# pragma comment (lib, "Leap")

namespace s3d
{
	/// <summary>
	/// Leap Motion
	/// </summary>
	namespace LeapMotion
	{
		/// <summary>
		/// 指の種類
		/// </summary>
		struct FingerType
		{
			enum Type
			{
				/// <summary>
				/// 親指
				/// </summary>
				Thumb,

				/// <summary>
				/// 人差し指
				/// </summary>
				Index,

				/// <summary>
				/// 中指
				/// </summary>
				Middle,

				/// <summary>
				/// 薬指
				/// </summary>
				Ring,

				/// <summary>
				/// 小指
				/// </summary>
				Pinky,
			};
		};

		/// <summary>
		/// 指の情報
		/// </summary>
		struct Finger
		{
			/// <summary>
			/// 指の長さ
			/// </summary>
			double length;

			/// <summary>
			/// 指の太さ
			/// </summary>
			double width;

			/// <summary>
			/// 指の位置 [mm]
			/// </summary>
			Vec3 pos;

			/// <summary>
			/// 安定するよう補正した指の位置 [mm]
			/// </summary>
			Vec3 stabilizedPos;

			/// <summary>
			/// 指の速度 [mm/s]
			/// </summary>
			Vec3 velocity;

			/// <summary>
			/// 指の方向の単位ベクトル
			/// </summary>
			Vec3 direction;

			/// <summary>
			/// 指の各関節
			/// </summary>
			Vec3 joints[5];

			/// <summary>
			/// 指の種類
			/// </summary>
			FingerType::Type type;

			/// <summary>
			/// 指の ID
			/// </summary>
			int id;
		};

		/// <summary>
		/// 手の情報
		/// </summary>
		struct Hand
		{
			/// <summary>
			/// 手のひらの中央の位置 [mm]
			/// </summary>
			Vec3 pos;

			/// <summary>
			/// 安定するよう補正した手のひらの中央の位置 [mm]
			/// </summary>
			Vec3 stabilizedPos;

			/// <summary>
			/// 手のひらの速度 [mm/s]
			/// </summary>
			Vec3 velocity;

			/// <summary>
			/// 手のひらの方向の単位ベクトル
			/// </summary>
			Vec3 normal;

			/// <summary>
			/// 
			/// </summary>
			double palmWidth;

			/// <summary>
			/// 手のひらから指先への方向の単位ベクトル
			/// </summary>
			Vec3 direction;

			/// <summary>
			/// 
			/// </summary>
			double armWidth;

			/// <summary>
			/// 
			/// </summary>
			Vec3 armDirection;

			/// <summary>
			/// ひじの位置 [mm]
			/// </summary>
			Vec3 elbowPos;

			/// <summary>
			/// 手首の位置 [mm]
			/// </summary>
			Vec3 wristPos;

			/// <summary>
			/// 手の湾曲にフィットする仮想的な球の中心位置 [mm]
			/// </summary>
			Vec3 sphereCenter;

			/// <summary>
			/// 手の湾曲にフィットする仮想的な球の半径 [mm]
			/// </summary>
			double sphereRadius;

			/// <summary>
			/// 親指と人差し指によるつまみの強さ [0.0, 1.0]
			/// </summary>
			double pinchStrength;

			/// <summary>
			/// 握りの強さ [0.0, 1.0]
			/// </summary>
			double grabStrength;

			/// <summary>
			/// Leap Motion に認識されている時間 [秒]
			/// </summary>
			double timeVisibleSec;

			/// <summary>
			/// 
			/// </summary>
			double confidence;

			/// <summary>
			/// 指の情報
			/// </summary>
			Array<Finger> fingers;

			/// <summary>
			/// 手の ID
			/// </summary>
			int id;

			/// <summary>
			/// 左手の場合 true, 右手の場合 false
			/// </summary>
			bool isLeft;
		};

		/// <summary>
		/// ツール
		/// </summary>
		struct Tool
		{
			/// <summary>
			/// ツールが指す方向の単位ベクトル
			/// </summary>
			Vec3 direction;

			/// <summary>
			/// 先端の位置 [mm]
			/// </summary>
			Vec3 pos;

			/// <summary>
			/// 安定するよう補正した先端の位置 [mm]
			/// </summary>
			Vec3 stabilizedPos;

			/// <summary>
			/// 先端の速度 [mm/s]
			/// </summary>
			Vec3 velocity;

			/// <summary>
			/// Leap Motion に認識されている時間 [秒]
			/// </summary>
			double timeVisibleSec;

			/// <summary>
			/// 推測される長さ [mm]
			/// </summary>
			double length;

			/// <summary>
			/// 推測される幅 [mm]
			/// </summary>
			double width;

			/// <summary>
			/// ツールの ID
			/// </summary>
			int id;
		};

		/// <summary>
		/// ジェスチャーの種類
		/// </summary>
		enum class GestureType
		{
			/// <summary>
			/// 未定義
			/// </summary>
			Undefined,

			/// <summary>
			/// 円を描く動作
			/// </summary>
			Circle,

			/// <summary>
			/// 線を描く動作
			/// </summary>
			Swipe,

			/// <summary>
			/// ピアノの鍵盤をたたくような動作
			/// </summary>
			KeyTap,

			/// <summary>
			/// 正面にタッチするような動作
			/// </summary>
			ScreenTap
		};

		/// <summary>
		/// ジェスチャーの状態
		/// </summary>
		enum class GestureState
		{
			/// <summary>
			/// 不正値
			/// </summary>
			Invalid,

			/// <summary>
			/// ジェスチャーが始まった
			/// </summary>
			Start,

			/// <summary>
			/// ジェスチャーが継続中である
			/// </summary>
			Update,

			/// <summary>
			/// ジェスチャーが終了した
			/// </summary>
			Stop,
		};

		/// <summary>
		/// Circle ジェスチャーの回転方向
		/// </summary>
		enum class CircleClockwiseness
		{
			/// <summary>
			/// 時計回り
			/// </summary>
			Clockwise,

			/// <summary>
			/// 反時計回り
			/// </summary>
			Counterclockwise,
		};

		/// <summary>
		/// ジェスチャー
		/// </summary>
		struct Gesture
		{
			/// <summary>
			/// ジェスチャーの種類
			/// </summary>
			GestureType type = GestureType::Undefined;

			/// <summary>
			/// ジェスチャーの名前
			/// </summary>
			Property_Get(String, gestureName) const
			{
				const static String gestureNames[]{ L"Undefined", L"Circle", L"Swipe", L"KeyTap", L"ScreenTap" };

				return gestureNames[static_cast<unsigned>(type)];
			}

			/// <summary>
			/// ジェスチャーの位置、Circle の場合は円の中心位置 [mm]
			/// </summary>
			Vec3 pos;

			/// <summary>
			/// ジェスチャーの方向の単位ベクトル
			/// </summary>
			Vec3 direction;

			/// <summary>
			/// ジェスチャーの速さ [mm/s] （Swipe のみ）
			/// </summary>
			double speed = 0.0;

			/// <summary>
			/// ジェスチャーの開始位置 [mm]（Swipe のみ）
			/// </summary>
			Vec3 startPos = Vec3::Zero;

			/// <summary>
			/// ジェスチャーの周回数（Circle のみ）
			/// </summary>
			double progress = 0.0;

			/// <summary>
			/// ジェスチャーの半径（Circle のみ）
			/// </summary>
			double radius = 0.0;

			/// <summary>
			/// ジェスチャーの回転方向（Circle のみ）
			/// </summary>
			CircleClockwiseness clockwiseness = CircleClockwiseness::Clockwise;

			/// <summary>
			/// ジェスチャーの状態
			/// </summary>
			GestureState state = GestureState::Invalid;

			/// <summary>
			/// ジェスチャーの ID
			/// </summary>
			int id;

			/// <summary>
			/// ジェスチャーに関連付けられた Hand の ID
			/// </summary>
			int handID;

			/// <summary>
			/// 
			/// </summary>
			int pointableID;
		};
	}

	inline Vec3 ToVec3(const Leap::Vector& v)
	{
		return{ v.x, v.y, -v.z };
	}

	class LeapMotionDevice : public IAddon
	{
	private:

		Leap::Controller m_controller;

		Array<LeapMotion::Hand> m_hands;

		Array<LeapMotion::Tool> m_tools;

		Array<LeapMotion::Gesture> m_gestures;

		bool m_connected = false;

		LeapMotion::GestureState LeapMotionDevice::convertState(Leap::Gesture::State state)
		{
			switch (state)
			{
			case Leap::Gesture::STATE_START:
				return LeapMotion::GestureState::Start;
			case Leap::Gesture::STATE_UPDATE:
				return LeapMotion::GestureState::Update;
			case Leap::Gesture::STATE_STOP:
				return LeapMotion::GestureState::Stop;
			default:
				return LeapMotion::GestureState::Invalid;
			}
		}

	public:

		static const String& name()
		{
			static const String name = L"LeapMotionSiv3D";
			return name;
		}

		String getName() const override
		{
			return name();
		}

		bool init() override
		{
			return true;
		}

		bool update() override
		{
			m_hands.clear();

			m_tools.clear();

			m_gestures.clear();

			m_connected = m_controller.isConnected();

			const Leap::Frame frame = m_controller.frame();

			for (const auto& hand : frame.hands())
			{
				const Leap::Arm arm = hand.arm();
				LeapMotion::Hand h;
				h.pos = ToVec3(hand.palmPosition());
				h.stabilizedPos = ToVec3(hand.stabilizedPalmPosition());
				h.velocity = ToVec3(hand.palmVelocity());
				h.normal = ToVec3(hand.palmNormal());
				h.palmWidth = hand.palmWidth();
				h.direction = ToVec3(hand.direction());
				h.armWidth = arm.width();
				h.armDirection = ToVec3(arm.direction());
				h.elbowPos = ToVec3(arm.elbowPosition());
				h.wristPos = ToVec3(arm.wristPosition());
				h.sphereCenter = ToVec3(hand.sphereCenter());
				h.sphereRadius = hand.sphereRadius();
				h.pinchStrength = hand.pinchStrength();
				h.grabStrength = hand.grabStrength();
				h.timeVisibleSec = hand.timeVisible();
				h.confidence = hand.confidence();
				h.isLeft = hand.isLeft();
				h.id = hand.id();

				h.fingers.reserve(hand.fingers().count());

				for (const auto& finger : hand.fingers())
				{
					LeapMotion::Finger f;
					f.length = finger.length();
					f.width = finger.width();
					f.pos = ToVec3(finger.tipPosition());
					f.stabilizedPos = ToVec3(finger.stabilizedTipPosition());
					f.velocity = ToVec3(finger.tipVelocity());
					f.direction = ToVec3(finger.direction());
					f.type = static_cast<LeapMotion::FingerType::Type>(finger.type());
					f.id = finger.id();

					f.joints[0] = ToVec3(finger.bone(Leap::Bone::TYPE_METACARPAL).prevJoint());
					f.joints[1] = ToVec3(finger.bone(Leap::Bone::TYPE_PROXIMAL).prevJoint());
					f.joints[2] = ToVec3(finger.bone(Leap::Bone::TYPE_INTERMEDIATE).prevJoint());
					f.joints[3] = ToVec3(finger.bone(Leap::Bone::TYPE_DISTAL).prevJoint());
					f.joints[4] = ToVec3(finger.bone(Leap::Bone::TYPE_DISTAL).nextJoint());

					h.fingers.push_back(f);
				}

				m_hands.push_back(h);
			}

			for (const auto& tool : frame.tools())
			{
				LeapMotion::Tool t;
				t.direction = ToVec3(tool.direction());
				t.pos = ToVec3(tool.tipPosition());
				t.stabilizedPos = ToVec3(tool.stabilizedTipPosition());
				t.velocity = ToVec3(tool.tipVelocity());
				t.timeVisibleSec = tool.timeVisible();
				t.length = tool.length();
				t.width = tool.width();
				t.id = tool.id();

				m_tools.push_back(t);
			}

			for (const auto& gesture : frame.gestures())
			{
				LeapMotion::Gesture g;
				g.id = gesture.id();
				g.handID = gesture.hands().isEmpty() ? -1 : gesture.hands().frontmost().id();
				g.pointableID = gesture.pointables().isEmpty() ? -1 : gesture.pointables().frontmost().id();
				g.state = convertState(gesture.state());

				switch (gesture.type())
				{
				case Leap::Gesture::TYPE_CIRCLE:
					{
						const Leap::CircleGesture& circleGesture = gesture;
						g.type = LeapMotion::GestureType::Circle;
						g.pos = ToVec3(circleGesture.center());
						g.direction = ToVec3(circleGesture.normal());
						g.progress = circleGesture.progress();
						g.radius = circleGesture.radius();
						g.clockwiseness =
							circleGesture.pointable().direction().angleTo(circleGesture.normal()) <= Leap::PI / 4
							? LeapMotion::CircleClockwiseness::Clockwise : LeapMotion::CircleClockwiseness::Counterclockwise;
						break;
					}
				case Leap::Gesture::TYPE_SWIPE:
					{
						const Leap::SwipeGesture& swipeGesture = gesture;
						g.type = LeapMotion::GestureType::Swipe;
						g.pos = ToVec3(swipeGesture.position());
						g.direction = ToVec3(swipeGesture.direction());
						g.speed = swipeGesture.speed();
						g.startPos = ToVec3(swipeGesture.startPosition());
						break;
					}
				case Leap::Gesture::TYPE_KEY_TAP:
					{
						const Leap::KeyTapGesture& keytapGesture = gesture;
						g.type = LeapMotion::GestureType::KeyTap;
						g.pos = ToVec3(keytapGesture.position());
						g.direction = ToVec3(keytapGesture.position());
						break;
					}
				case Leap::Gesture::TYPE_SCREEN_TAP:
					{
						const Leap::ScreenTapGesture& screentapGesture = gesture;
						g.type = LeapMotion::GestureType::ScreenTap;
						g.pos = ToVec3(screentapGesture.position());
						g.direction = ToVec3(screentapGesture.direction());
						break;
					}
				default:
					{
						g.type = LeapMotion::GestureType::Undefined;
						break;
					}
				}

				m_gestures.push_back(g);
			}

			return true;
		}

		bool isConnected() const
		{
			return m_connected;
		}

		void enableGesture(LeapMotion::GestureType type, bool enable)
		{
			switch (type)
			{
			case LeapMotion::GestureType::Circle:
				m_controller.enableGesture(Leap::Gesture::TYPE_CIRCLE, enable); break;
			case LeapMotion::GestureType::Swipe:
				m_controller.enableGesture(Leap::Gesture::TYPE_SWIPE, enable); break;
			case LeapMotion::GestureType::KeyTap:
				m_controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP, enable); break;
			case LeapMotion::GestureType::ScreenTap:
				m_controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP, enable); break;
			default:
				break;
			}
		}

		const Array<LeapMotion::Hand>& hands() const
		{
			return m_hands;
		}

		const Array<LeapMotion::Tool>& tools() const
		{
			return m_tools;
		}

		const Array<LeapMotion::Gesture>& gestures() const
		{
			return m_gestures;
		}
	};

	namespace LeapMotion
	{
		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		inline bool RegisterAddon()
		{
			return Addon::Register<LeapMotionDevice>();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		inline bool IsConnected()
		{
			if (auto p = Addon::GetAddon<LeapMotionDevice>())
			{
				return p->isConnected();
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		inline Array<Hand> Hands()
		{
			if (auto p = Addon::GetAddon<LeapMotionDevice>())
			{
				return p->hands();
			}
			else
			{
				return{};
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		inline Array<Tool> Tools()
		{
			if (auto p = Addon::GetAddon<LeapMotionDevice>())
			{
				return p->tools();
			}
			else
			{
				return{};
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>
		/// 
		/// </returns>
		inline Array<Gesture> Gestures()
		{
			if (auto p = Addon::GetAddon<LeapMotionDevice>())
			{
				return p->gestures();
			}
			else
			{
				return{};
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="type">
		/// 
		/// </param>
		/// <param name="enable">
		/// 
		/// </param>
		/// <returns>
		/// 
		/// </returns>
		inline void EnableGesture(GestureType type, bool enable = true)
		{
			if (auto p = Addon::GetAddon<LeapMotionDevice>())
			{
				return p->enableGesture(type, enable);
			}
		}
	}
}
