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
# include "Optional.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// ユニーク ID
	/// </summary>
	/// <remarks>
	/// ユーザやコンピュータのユニーク ID を取得する機能を提供します。
	/// </remarks>
	namespace UID
	{
		/// <summary>
		/// コンピュータのボリュームシリアル番号を取得します。
		/// </summary>
		/// <returns>
		/// コンピュータのボリュームシリアル番号の Optional, 失敗した場合は none
		/// </returns>
		Optional<uint32> GetVolumeSerial();

		/// <summary>
		/// コンピュータの MAC アドレスを取得します。
		/// </summary>
		/// <returns>
		/// コンピュータの MAC アドレスの Optional, 失敗した場合は none
		/// </returns>
		Optional<String> GetMacAddress();

		/// <summary>
		/// Windows のコンピュータ SID を取得します。
		/// </summary>
		/// <returns>
		/// Windows のコンピュータ SID の Optional, 失敗した場合は none
		/// </returns>
		Optional<String> GetComputerSID();

		/// <summary>
		/// Windows のユーザ SID を取得します。
		/// </summary>
		/// <returns>
		/// Windows のユーザ SID の Optional, 失敗した場合は none
		/// </returns>
		Optional<String> GetUserSID();

		/// <summary>
		/// Windows のマシン GUID を取得します。
		/// </summary>
		/// <returns>
		/// Windows のマシン GUID の Optional, 失敗した場合は none
		/// </returns>
		Optional<String> GetMachineGUID();
	}
}
