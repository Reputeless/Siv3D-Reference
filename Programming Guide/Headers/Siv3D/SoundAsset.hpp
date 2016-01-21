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
# include "Asset.hpp"
# include "Sound.hpp"
# include "FileArchive.hpp"
# include "FileMonitor.hpp"

namespace s3d
{
	/// <summary>
	/// Sound アセットデータ
	/// </summary>
	struct SoundAssetData : IAsset
	{
	public:

		static const String& name()
		{
			static const String name = L"Sound";

			return name;
		}

		bool preload() override;

		bool update() override;

		bool release() override;

		const Array<AssetTag>& getTags() const override;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		SoundAssetData() = default;

		/// <summary>
		/// Sound アセットデータを作成します。
		/// </summary>
		/// <param name="_path">
		/// オーディオファイルのパス
		/// </param>
		/// <param name="_loop">
		/// サウンドのループ設定
		/// </param>
		/// <param name="_maxSpeed">
		/// 最大の再生スピード
		/// </param>
		/// <param name="_tags">
		/// アセットのタグ
		/// </param>
		/// <param name="_flag">
		/// アセット作成フラグ
		/// </param>
		/// <param name="_onPreload">
		/// アセットのプリロード時に実行するカスタムコールバック
		/// </param>
		/// <param name="_onUpdate">
		/// アセットの更新時に実行するカスタムコールバック
		/// </param>
		/// <param name="_onRelease">
		/// アセットのリリース時に実行するカスタムコールバック
		/// </param>
		SoundAssetData(const FilePath& _path, const SoundLoop& _loop = SoundLoop::None, SoundDesc desc = SoundDesc::Default, double _maxSpeed = 2.0, const Array<AssetTag>& _tags = {}, int32 _flag = AssetFlag::Default, std::function<bool(SoundAssetData&)> _onPreload = nullptr, std::function<bool(SoundAssetData&)> _onUpdate = nullptr, std::function<bool(SoundAssetData&)> _onRelease = nullptr);

		static SoundAssetData FromFileArchive(const FilePath& archiveFile, const FilePath& fileName, const SoundLoop& _loop = SoundLoop::None, SoundDesc desc = SoundDesc::Default, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default)
		{
			SoundAssetData asset;
			asset.tags = tags;
			asset.flag = flag;
			asset.onPreload = [=](SoundAssetData& d)
			{
				d.sound = Sound(FileArchive(archiveFile).load(fileName), _loop, desc);
				return !d.sound.isEmpty();
			};

			return asset;
		}

		double maxSpeed = 2.0;

		FilePath path;

		SoundLoop loop = SoundLoop::None;

		SoundDesc desc = SoundDesc::Default;

		FileMonitor monitor;

		Sound sound;

		Array<AssetTag> tags;

		int32 flag;

		std::function<bool(SoundAssetData&)> onPreload;

		std::function<bool(SoundAssetData&)> onUpdate;

		std::function<bool(SoundAssetData&)> onRelease;
	};

	/// <summary>
	/// Sound アセット
	/// </summary>
	class SoundAsset : public Sound
	{
	public:

		/// <summary>
		/// Sound アセットにアクセスします。
		/// </summary>
		/// <param name="name">
		/// Sound アセット名
		/// </param>
		SoundAsset(const AssetName& name);

		/// <summary>
		/// Sound アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Sound アセット名
		/// </param>
		/// <param name="_path">
		/// オーディオファイルのパス
		/// </param>
		/// <param name="tags">
		/// アセットのタグ
		/// </param>
		/// <param name="flag">
		/// アセット作成フラグ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const FilePath& path, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default);

		/// <summary>
		/// Sound アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Sound アセット名
		/// </param>
		/// <param name="path">
		/// オーディオファイルのパス
		/// </param>
		/// <param name="loop">
		/// サウンドのループ設定
		/// </param>
		/// <param name="tags">
		/// アセットのタグ
		/// </param>
		/// <param name="flag">
		/// アセット作成フラグ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const FilePath& path, const SoundLoop& loop, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default);

		/// <summary>
		/// Sound アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Sound アセット名
		/// </param>
		/// <param name="path">
		/// オーディオファイルのパス
		/// </param>
		/// <param name="_oop">
		/// サウンドのループ設定
		/// </param>
		/// <param name="desc">
		/// サウンドのループ設定
		/// </param>
		/// <param name="tags">
		/// アセットのタグ
		/// </param>
		/// <param name="flag">
		/// アセット作成フラグ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const FilePath& path, const SoundLoop& loop, SoundDesc desc, const Array<AssetTag>& tags = {}, int32 flag = AssetFlag::Default);

		/// <summary>
		/// Sound アセットを登録します。
		/// </summary>
		/// <param name="name">
		/// Sound アセット名
		/// </param>
		/// <param name="data">
		/// Sound アセットデータ
		/// </param>
		/// <returns>
		/// アセットの登録に成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Register(const AssetName& name, const SoundAssetData& data);

		/// <summary>
		/// 指定した名前の Sound アセットがすでに登録されているかを調べます。
		/// </summary>
		/// <param name="name">
		/// 検索する名前
		/// </param>
		/// <returns>
		/// 指定した名前の Sound アセットがすでに登録されている場合 true, それ以外の場合は false
		/// </returns>
		static bool IsRegistered(const AssetName& name);

		/// <summary>
		/// Sound アセットをプリロードします。
		/// </summary>
		/// <param name="name">
		/// プリロードする Sound アセットの名前
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool Preload(const AssetName& name);

		/// <summary>
		/// Sound アセットをプリロードします。
		/// </summary>
		/// <param name="tag">
		/// プリロードする Sound アセットのタグ
		/// </param>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadByTag(const AssetTag& tag);

		/// <summary>
		/// 登録しているすべての Sound アセットをプリロードします。
		/// </summary>
		/// <returns>
		/// プリロードに成功した場合 true, それ以外の場合は false
		/// </returns>
		static bool PreloadAll();

		/// <summary>
		/// Sound アセットをリリースします。
		/// </summary>
		/// <param name="name">
		/// リリースする Sound アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Release(const AssetName& name);

		/// <summary>
		/// Sound アセットをリリースします。
		/// </summary>
		/// <param name="tag">
		/// リリースする Sound アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseByTag(const AssetTag& tag);

		/// <summary>
		/// すべての Sound アセットをリリースします。
		/// </summary>
		/// <remarks>
		/// アセットはリリースされても登録は解除されません。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		static void ReleaseAll();

		/// <summary>
		/// Sound アセットを登録解除します。
		/// </summary>
		/// <param name="name">
		/// 登録解除する Sound アセットの名前
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void Unregister(const AssetName& name);

		/// <summary>
		/// Sound アセットを登録解除します。
		/// </summary>
		/// <param name="tag">
		/// 登録解除する Sound アセットのタグ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterByTag(const AssetTag& tag);

		/// <summary>
		/// すべての Sound アセットを登録解除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		static void UnregisterAll();
	};
}
