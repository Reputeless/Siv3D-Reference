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

/// <summary>
/// Siv3D のバージョン | Version of Siv3D
/// </summary>
# define Siv3DVersion L"March 2016"

/// <summary>
/// Siv3D のバージョン ID | Version ID of Siv3D
/// </summary>
# define Siv3DVersionID 20160310

/// <summary>
/// ターゲットプラットフォーム | Platform target
/// </summary>
# ifdef _WIN64
#	define Siv3DPlatform L"x64"
# else
#	define Siv3DPlatform L"x86"
# endif
