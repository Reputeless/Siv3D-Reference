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
/// プロパティ用マクロ
/// </summary>
# define Property_Get(type,name)	__declspec(property(get=_get_##name))type name;\
									type _get_##name()
