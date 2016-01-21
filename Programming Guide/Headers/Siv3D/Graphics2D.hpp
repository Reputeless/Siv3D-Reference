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
# include "Shader.hpp"

namespace s3d
{
	/// <summary>
	/// 2D グラフィックス
	/// </summary>
	/// <remarks>
	/// 2D　グラフィックスに関連する機能を提供します。
	/// </remarks>
	namespace Graphics2D
	{
		/// <summary>
		/// 2D 描画時の変換行列を設定します。
		/// </summary>
		/// <remarks>
		/// GUI と Println 等による画面表示には適用されません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void SetTransform(const Mat3x2& matrix);

		/// <summary>
		/// 現在の 2D 描画時の変換行列を取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画時の変換行列
		/// </returns>
		Mat3x2 GetTransform();


		void SetZ(uint16 z);

		uint16 GetZ();

		/// <summary>
		/// 2D 描画のブレンドステートを設定します。
		/// </summary>
		/// <param name="blendState">
		/// ブレンドステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetBlendState(const BlendState& blendState);

		/// <summary>
		/// 現在の 2D 描画のブレンドステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のブレンドステート
		/// </returns>
		BlendState GetBlendState();

		/// <summary>
		/// 2D 描画のラスタライザーステートを設定します。
		/// </summary>
		/// <param name="rasterizerState">
		/// ラスタライザーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRasterizerState(const RasterizerState& rasterizerState);

		/// <summary>
		/// 現在の 2D 描画のラスタライザーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のラスタライザーステート
		/// </returns>
		RasterizerState GetRasterizerState();

		void SetDepthState(const DepthState& depthState);

		DepthState GetDepthState();

		/// <summary>
		/// 2D 描画のステンシルステートを設定します。
		/// </summary>
		/// <param name="stencilState">
		/// ステンシルステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStencilState(const StencilState& stencilState);

		/// <summary>
		/// 現在の 2D 描画のステンシルステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のステンシルステート
		/// </returns>
		StencilState GetStencilState();

		/// <summary>
		/// 2D 描画のステンシル値を設定します。
		/// </summary>
		/// <param name="value">
		/// ステンシル値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetStencilValue(uint8 value);

		/// <summary>
		/// 現在の 2D 描画のステンシル値を取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のステンシル値
		/// </returns>
		uint8 GetStencilValue();

		/// <summary>
		/// 2D 描画のサンプラーステートを設定します。
		/// </summary>
		/// <param name="samplerState">
		/// サンプラーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetSamplerState(const SamplerState& samplerState);

		/// <summary>
		/// 2D 描画のサンプラーステートをスロットを指定して設定します。
		/// </summary>
		/// <param name="slot">
		/// スロット [0 または 1]
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
		/// 現在の 2D 描画のサンプラーステートを取得します。
		/// </summary>
		/// <param name="slot">
		/// スロット [0 または 1]
		/// </param>
		/// <returns>
		/// 現在の 2D 描画のサンプラーステート
		/// </returns>
		SamplerState GetSamplerState();

		SamplerState GetSamplerState(uint32 slot);

		SamplerState GetSamplerState(ShaderStage stage, uint32 slot);

		void SetScissorRect(const Rect& rect);

		Rect GetScissorRect();

		/// <summary>
		/// 現在の 2D 描画のレンダーステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のレンダーステート
		/// </returns>
		RenderState GetRenderState();

		/// <summary>
		/// 2D 描画のレンダーステートを設定します。
		/// </summary>
		/// <param name="state">
		/// レンダーステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetRenderState(const RenderState& state);	

		bool DrawPointSprites(uint32 num_particles);

		bool DrawPointSprites(uint32 num_particles, const Texture& texture);

		void SetTexture(ShaderStage stage, uint32 slot, const Texture& texture);

		void SetTexture(ShaderStage stage, uint32 slot, nullopt_t);

		void SetRenderTarget(const RenderTexture& texture);

		const RenderTexture& GetRenderTarget();

		bool BeginVS(const VertexShader& vs);

		void EndVS();

		bool BeginPS(const PixelShader& ps);

		void EndPS();

		void SetConstant(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);

		template <class Type>
		inline void SetConstant(ShaderStage stage, uint32 slot, const ConstantBuffer<Type>& buffer)
		{
			SetConstant(stage, slot, buffer.base(), buffer.getPtr(), sizeof(Type) / sizeof(__m128));
		}


		[[deprecated("** Graphics2D::SetUVTransform() is a deprecated function. Use custom vertex shader instead. **")]]
		void SetUVTransform(const Float4& transform);

		[[deprecated("** Graphics2D::GetUVTransform() is a deprecated function. Use custom vertex shader instead. **")]]
		Float4 GetUVTransform();


		[[deprecated("** Graphics2D::BeginShader() is a deprecated function. Use Graphics::BeginPS() instead. **")]]
		bool BeginShader(const PixelShader& ps);

		[[deprecated("** Graphics::EndShader() is a deprecated function. Use Graphics::EndPS() instead. **")]]
		void EndShader();
	}
}
