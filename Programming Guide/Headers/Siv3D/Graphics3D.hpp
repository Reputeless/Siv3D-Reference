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
# include "BlendState.hpp"
# include "RasterizerState.hpp"
# include "DepthStencilState.hpp"
# include "SamplerState.hpp"
# include "RenderState.hpp"
# include "Camera.hpp"
# include "Fog.hpp"
# include "Light.hpp"

namespace s3d
{
	/// <summary>
	/// レンダラー
	/// </summary>
	enum class Renderer
	{
		/// <summary>
		/// デフォルトの Deferred レンダラー
		/// </summary>
		Deferred,

		/// <summary>
		/// Forward レンダラー
		/// </summary>
		Forward,
	};

	/// <summary>
	/// アンチエイリアシングのレベル
	/// </summary>
	enum class AntiAliasing
	{
		/// <summary>
		/// なし
		/// </summary>
		None,

		/// <summary>
		/// 低
		/// </summary>
		Low,

		/// <summary>
		/// 中
		/// </summary>
		Medium,

		/// <summary>
		/// 高
		/// </summary>
		High,

		/// <summary>
		/// デフォルト [低]
		/// </summary>
		Default = Low
	};

	/// <summary>
	/// 3D グラフィックス
	/// </summary>
	/// <remarks>
	/// 3D　グラフィックスに関連する機能を提供します。
	/// </remarks>
	namespace Graphics3D
	{
		////////////////////////////////////////////////////////////////
		//
		//		カメラ
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// カメラを設定します。
		/// </summary>
		/// <param name="state">
		/// カメラの設定
		/// </param>
		/// <remarks>
		/// 毎フレーム、最後に適用されたカメラ設定がシーンの描画に使用されます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetCamera(const Camera& state);

		/// <summary>
		/// 現在のカメラの設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在のカメラの設定
		/// </returns>
		const Camera& GetCamera();

		/// <summary>
		/// デバッグ用のカメラを適用します。
		/// </summary>
		/// <param name="speed">
		/// カメラの移動速度
		/// </param>
		/// <remarks>
		/// A, W, S, D, E, X, 矢印キーを使ってカメラを操作できます。
		/// Shift, Ctrl キーを同時に押すと移動速度が上がります。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void FreeCamera(double speed = 0.1);

		/// <summary>
		/// 現在のカメラの設定を使って、ワールド座標をスクリーン座標に変換します。
		/// </summary>
		/// <param name="worldPos">
		/// ワールド座標
		/// </param>
		/// <returns>
		/// スクリーン座標。z は深度
		/// </returns>
		Vec3 ToScreenPos(const Vec3& worldPos);

		/// <summary>
		/// 現在のカメラの設定を使って、スクリーン座標をワールド座標に変換します。
		/// </summary>
		/// <param name="screenPos">
		/// スクリーン座標
		/// </param>
		/// <param name="depth">
		/// 深度
		/// </param>
		/// <returns>
		/// ワールド座標
		/// </returns>
		Vec3 ToWorldPos(const Vec2& screenPos, double depth);

		/// <summary>
		/// 現在のカメラの設定を使って、スクリーン座標をレイに変換します。
		/// </summary>
		/// <param name="screenPos">
		/// スクリーン座標
		/// </param>
		/// <returns>
		/// レイ
		/// </returns>
		Ray ToRay(const Vec2& screenPos);

		void SetViewportForward(const Rect& viewport);

		Rect GetViewportForward();

		////////////////////////////////////////////////////////////////
		//
		//		レンダーステート
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// Forward レンダラ―のブレンドステートを設定します。
		/// </summary>
		/// <param name="blendState">
		/// ブレンドステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetBlendStateForward(const BlendState& blendState);

		/// <summary>
		/// 現在の Forward レンダラ―のブレンドステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のブレンドステート
		/// </returns>
		BlendState GetBlendStateForward();

		/// <summary>
		/// Deferred レンダラ―のラスタライザーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// ラスタライザーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRasterizerState(const RasterizerState& rasterizerState);

		/// <summary>
		/// Forward レンダラ―のラスタライザーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// ラスタライザーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRasterizerStateForward(const RasterizerState& rasterizerState);

		/// <summary>
		/// 現在の Deferred レンダラ―のラスタライザーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―のラスタライザーステート
		/// </returns>
		RasterizerState GetRasterizerState();

		/// <summary>
		/// 現在の Forward レンダラ―のラスタライザーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のラスタライザーステート
		/// </returns>
		RasterizerState GetRasterizerStateForward();

		/// <summary>
		/// Deferred レンダラ―のステンシルステートを設定します。
		/// </summary>
		/// <param name="stencilState">
		/// ステンシルステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStencilState(const StencilState& stencilState);

		/// <summary>
		/// Forward レンダラ―のステンシルステートを設定します。
		/// </summary>
		/// <param name="stencilState">
		/// ステンシルステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStencilStateForward(const StencilState& stencilState);

		/// <summary>
		/// 現在の Deferred レンダラ―のステンシルステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―のステンシルステート
		/// </returns>
		StencilState GetStencilState();

		/// <summary>
		/// 現在の Forward レンダラ―のステンシルステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のステンシルステート
		/// </returns>
		StencilState GetStencilStateForward();

		/// <summary>
		/// Deferred レンダラ―のデプスステートを設定します。
		/// </summary>
		/// <param name="depthState">
		/// デプスステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetDepthState(const DepthState& depthState);

		/// <summary>
		/// Forward レンダラ―のデプスステートを設定します。
		/// </summary>
		/// <param name="depthState">
		/// デプスステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetDepthStateForward(const DepthState& depthState);

		/// <summary>
		/// 現在の Deferred レンダラ―のデプスステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―のデプスステート
		/// </returns>
		DepthState GetDepthState();

		/// <summary>
		/// 現在の Forward レンダラ―のデプスステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のデプスステート
		/// </returns>
		DepthState GetDepthStateForward();

		/// <summary>
		/// Deferred レンダラ―のステンシル値を設定します。
		/// </summary>
		/// <param name="value">
		/// ステンシル値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStencilValue(uint8 value);

		/// <summary>
		/// Forward レンダラ―のステンシル値を設定します。
		/// </summary>
		/// <param name="value">
		/// ステンシル値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStencilValueForward(uint8 value);

		/// <summary>
		/// 現在の Deferred レンダラ―のステンシル値を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―のステンシル値
		/// </returns>
		uint8 GetStencilValue();

		/// <summary>
		/// 現在の Forward レンダラ―のステンシル値を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のステンシル値
		/// </returns>
		uint8 GetStencilValueForward();

		/// <summary>
		/// Deferred レンダラ―のサンプラーステートを設定します。
		/// </summary>
		/// <param name="samplerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSamplerState(const SamplerState& samplerState);

		/// <summary>
		/// Deferred レンダラ―のサンプラーステートを設定します。
		/// </summary>
		/// <param name="slot">
		/// スロット番号 [0 - 3]
		/// </param>
		/// <param name="samplerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSamplerState(uint32 slot, const SamplerState& samplerState);

		void SetSamplerState(ShaderStage stage, uint32 slot, const SamplerState& samplerState);



		/// <summary>
		/// Forward レンダラ―のサンプラーステートを設定します。
		/// </summary>
		/// <param name="samplerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSamplerStateForward(const SamplerState& samplerState);

		/// <summary>
		/// Forward レンダラ―のサンプラーステートを設定します。
		/// </summary>
		/// <param name="slot">
		/// スロット番号 [0 - 3]
		/// </param>
		/// <param name="samplerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSamplerStateForward(uint32 slot, const SamplerState& samplerState);

		void SetSamplerStateForward(ShaderStage stage, uint32 slot, const SamplerState& samplerState);

		/// <summary>
		/// 現在の Deferred レンダラ―のサンプラーステートを取得します。
		/// </summary>
		/// <param name="slot">
		/// スロット番号 [0 - 3]
		/// </param>
		/// <returns>
		/// 現在の Deferred レンダラ―のサンプラーステート
		/// </returns>
		SamplerState GetSamplerState();

		SamplerState GetSamplerState(uint32 slot);

		SamplerState GetSamplerState(ShaderStage stage, uint32 slot);

		/// <summary>
		/// 現在の Forward レンダラ―のサンプラーステートを取得します。
		/// </summary>
		/// <param name="slot">
		/// スロット番号 [0 - 3]
		/// </param>
		/// <returns>
		/// 現在の Forward レンダラ―のサンプラーステート
		/// </returns>
		SamplerState GetSamplerStateForward();

		SamplerState GetSamplerStateForward(uint32 slot);

		SamplerState GetSamplerStateForward(ShaderStage stage, uint32 slot);



		void SetScissorRect(const Rect& rect);

		Rect GetScissorRect();


		void SetScissorRectForward(const Rect& rect);

		Rect GetScissorRectForward();

		/// <summary>
		/// 現在の Deferred レンダラ―のレンダーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―のレンダーステート
		/// </returns>
		RenderState GetRenderState();

		/// <summary>
		/// 現在の Forward レンダラ―のレンダーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のレンダーステート
		/// </returns>
		RenderState GetRenderStateForward();

		/// <summary>
		/// Deferred レンダラ―のレンダーステートを設定します。
		/// </summary>
		/// <param name="state">
		/// レンダーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRenderState(const RenderState& state);

		/// <summary>
		/// Forward レンダラ―のレンダーステートを設定します。
		/// </summary>
		/// <param name="state">
		/// レンダーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRenderStateForward(const RenderState& state);


		void SetTexture(ShaderStage stage, uint32 slot, const Texture& texture);

		void SetTexture(ShaderStage stage, uint32 slot, nullopt_t);

		void SetTextureForward(ShaderStage stage, uint32 slot, const Texture& texture);

		void SetTextureForward(ShaderStage stage, uint32 slot, nullopt_t);

		bool BeginVS(const VertexShader& vs);

		void EndVS();

		bool BeginVSForward(const VertexShader& vs);

		void EndVSForward();

		bool BeginPS(const PixelShader& ps);

		void EndPS();

		bool BeginPSForward(const PixelShader& ps);

		void EndPSForward();

		void SetConstant(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);

		template <class Type>
		inline void SetConstant(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			SetConstant(stage, slot, buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(__m128));
		}

		void SetConstantForward(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);

		template <class Type>
		inline void SetConstantForward(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			SetConstantForward(stage, slot, buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(__m128));
		}

		////////////////////////////////////////////////////////////////
		//
		//		ライトとフォグ
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// Deferred レンダラ―にフォグを設定します。
		/// </summary>
		/// <param name="fog">
		/// フォグ
		/// </param>
		/// <remarks>
		/// 毎フレーム、最後に適用された設定がシーンの描画に使用されます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetFog(const Fog& fog);

		/// <summary>
		/// 現在の Deferred レンダラ―のフォグ設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―のフォグ設定
		/// </returns>
		const Fog& GetFog();

		/// <summary>
		/// Forward レンダラ―にフォグを設定します。
		/// </summary>
		/// <param name="fog">
		/// フォグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetFogForward(const Fog& fog);

		/// <summary>
		/// 現在の Forward レンダラ―のフォグ設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のフォグ設定
		/// </returns>
		const Fog& GetFogForward();

		/// <summary>
		/// Deferred レンダラ―に環境光を設定します。
		/// </summary>
		/// <param name="color">
		/// 環境光の強さ
		/// </param>
		/// <remarks>
		/// 毎フレーム、最後に適用された設定がシーンの描画に使用されます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetAmbientLight(const ColorF& color);

		/// <summary>
		/// 現在の Deferred レンダラ―の環境光設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Deferred レンダラ―の環境光の強さ
		/// </returns>
		ColorF GetAmbientLight();

		/// <summary>
		/// Forward レンダラ―に環境光を設定します。
		/// </summary>
		/// <param name="color">
		/// 環境光の強さ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetAmbientLightForward(const ColorF& color);

		/// <summary>
		/// 現在の Forward レンダラ―の環境光設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―の環境光の強さ
		/// </returns>
		ColorF GetAmbientLightForward();

		/// <summary>
		/// Deferred レンダラ―最大の光源数
		/// </summary>
		constexpr uint32 MaxLight = 128;

		/// <summary>
		/// Deferred レンダラ―最大の光源インデックス
		/// </summary>
		constexpr uint32 MaxLightIndex = MaxLight - 1;

		/// <summary>
		/// Forward レンダラ―最大の光源数
		/// </summary>
		constexpr uint32 MaxLightForward = 4;

		/// <summary>
		/// Forward レンダラ―最大の光源インデックス
		/// </summary>
		constexpr uint32 MaxLightIndexForward = MaxLightForward - 1;
		/// <summary>
		/// Deferred レンダラ―にライトを設定します。
		/// </summary>
		/// <param name="index">
		/// ライトインデックス [0-127]
		/// </param>
		/// <param name="light">
		/// ライトの設定
		/// </param>
		/// <remarks>
		/// 毎フレーム、ライトインデックスごとに最後に適用された設定がシーンの描画に使用されます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetLight(uint32 index, const Light& light);

		/// <summary>
		/// 現在の Deferred レンダラ―のライトの設定を取得します。
		/// </summary>
		/// <param name="index">
		/// ライトインデックス [0-127]
		/// </param>
		/// <returns>
		/// 現在の Deferred レンダラ―のライトの設定
		/// </returns>
		const Light& GetLight(uint32 index);

		/// <summary>
		/// Forward レンダラ―にライトを設定します。
		/// </summary>
		/// <param name="light">
		/// ライトの設定
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetLightForward(uint32 index, const Light& light);

		/// <summary>
		/// 現在の Forward レンダラ―のライトの設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在の Forward レンダラ―のライトの設定
		/// </returns>
		const Light& GetLightForward(uint32 index);


		////////////////////////////////////////////////////////////////
		//
		//		画質
		//
		////////////////////////////////////////////////////////////////

		/// <summary>
		/// アンチエイリアシングの品質を設定します。
		/// </summary>
		/// <param name="antiAliasing">
		/// アンチエイリアシングの設定
		/// </param>
		/// <remarks>
		/// 毎フレーム、最後に適用された設定がシーンの描画に使用されます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetAntiAliasing(AntiAliasing antiAliasing);

		/// <summary>
		/// 現在のアンチエイリアシングの設定を取得します。
		/// </summary>
		/// <returns>
		/// 現在のアンチエイリアシングの設定
		/// </returns>
		AntiAliasing GetAntiAliasing();

		/// <summary>
		/// ライトバッファの品質を変更します。
		/// </summary>
		/// <param name="quality">
		/// ライトバッファの品質。 [1-100] の範囲で指定します
		/// </param>
		/// <remarks>
		/// デフォルトでは 100 で、品質を小さくすると複雑なシーンでの画質が低下しますが、
		/// ライティングにかかるコストは数値に比例して減少します。
		/// quality は 1 から 100 の範囲にクランプされます
		/// </remarks>
		/// <remarks>
		/// 毎フレーム、最後に適用された設定がシーンの描画に使用されます。
		/// </remarks>
		/// <returns>
		/// 正常に変更できた場合 true, メモリ不足などのエラーが発生した場合は false
		/// </returns>
		bool SetLightBufferQuality(uint32 quality = 100);

		/// <summary>
		/// 現在のライトバッファの品質を取得します。
		/// </summary>
		/// <returns>
		/// ライトバッファの品質 [1-100]
		/// </returns>
		uint32 GetLightBufferQuality();

		/// <summary>
		/// カメラ、ライト、フォグ、画質の設定を初期設定に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		inline void ResetScene()
		{
			SetAmbientLight(ColorF(0.1));

			SetAmbientLightForward(ColorF(0.1));

			SetLight(0, Light::Default());

			for (uint32 i = 1; i <= MaxLightIndex; ++i)
			{
				SetLight(i, Light::None());
			}

			SetLightForward(0, Light::Default());

			for (uint32 i = 1; i <= MaxLightIndexForward; ++i)
			{
				SetLightForward(i, Light::None());
			}

			SetFog(Fog::None());

			SetFogForward(Fog::None());

			SetCamera(Camera());

			SetAntiAliasing(AntiAliasing::Default);

			SetLightBufferQuality(100);
		}
	}
}
