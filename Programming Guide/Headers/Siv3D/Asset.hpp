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
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// <summary>
	/// アセット名
	/// </summary>
	using AssetName = String;

	/// <summary>
	/// アセットタグ名
	/// </summary>
	using AssetTag = String;

	/// <summary>
	/// アセット作成フラグ
	/// </summary>
	struct AssetFlag
	{
		enum Flag
		{
			/// <summary>
			/// ファイルの変更を追跡し、アセットの内容も更新する
			/// </summary>
			TrackFile = 0x1,

			/// <summary>
			/// 登録時にプリロード
			/// </summary>
			LoadImmediately = 0x2,

			/// <summary>
			/// デフォルト
			/// </summary>
			Default = 0,
		};
	};

	/// <summary>
	/// アセットインタフェースクラス
	/// </summary>
	class IAsset
	{
	public:

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~IAsset() = default;

		/// <summary>
		/// アセットのプリロード時に呼ばれる関数
		/// </summary>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool preload() = 0;

		/// <summary>
		/// アセットの更新時に呼ばれる関数
		/// </summary>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool update() = 0;

		/// <summary>
		/// アセットのリリース時に呼ばれる関数
		/// </summary>
		/// <returns>
		/// リリースに成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool release() = 0;

		/// <summary>
		/// アセットのタグを取得します。
		/// </summary>
		/// <returns>
		/// アセットのタグ一覧
		/// </returns>
		virtual const Array<AssetTag>& getTags() const = 0;
	};
}
