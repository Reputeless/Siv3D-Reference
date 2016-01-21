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
# include "PointVector.hpp"
# include "Math.hpp"
# include "Window.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	/// <summary>
	/// カメラ
	/// </summary>
	struct Camera
	{
		/// <summary>
		/// カメラの位置
		/// </summary>
		Vec3 pos = { 0.0, 4.0, -16.0 };

		/// <summary>
		/// カメラの注視点
		/// </summary>
		Vec3 lookat = { 0.0, 1.0, 0.0 };

		/// <summary>
		/// カメラの上方向のベクトル
		/// </summary>
		Vec3 up = { 0.0, 1.0, 0.0 };

		/// <summary>
		/// 視野角（°）
		/// </summary>
		double fovDegree = 45.0;

		/// <summary>
		/// ニアクリップ
		/// </summary>
		double nearClip = 0.1;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr Camera() = default;

		/// <summary>
		/// カメラの設定を作成します。
		/// </summary>
		/// <param name="_pos">
		/// カメラの位置
		/// </param>
		/// <param name="_lookat">
		/// カメラの注視点
		/// </param>
		/// <param name="_up">
		/// カメラの上方向のベクトル
		/// </param>
		/// <param name="_fovDegree">
		/// 視野角（°）
		/// </param>
		/// <param name="_nearclip">
		/// ニアクリップ
		/// </param>
		constexpr Camera(const Vec3& _pos, const Vec3& _lookat, const Vec3& _up, double _fovDegree, double _nearClip)
			: pos(_pos)
			, lookat(_lookat)
			, up(_up)
			, fovDegree(_fovDegree)
			, nearClip(_nearClip) {}

		/// <summary>
		/// 視野角をラジアンで取得します。
		/// </summary>
		/// <returns>
		/// 視野角（ラジアン）
		/// </returns>
		constexpr double fovRadian() const
		{
			return Math::Radians(fovDegree);
		}

		Mat4x4 calcViewMatrix() const;

		Mat4x4 calcInvViewMatrix() const;

		Mat4x4 calcViewFrontMatrix() const;

		Mat4x4 calcProjectionMatrix(double aspect = Window::AspectRatio()) const;

		Mat4x4 calcViewProjectionMatrix(double aspect = Window::AspectRatio()) const;

		Mat4x4 calcInvViewProjectionMatrix(double aspect = Window::AspectRatio()) const;
	};
}
