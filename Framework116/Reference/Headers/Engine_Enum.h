#pragma once
#ifndef __ENGINE_ENUM_H__

BEGIN(Engine)

enum class EResourceType
{
	Static,
	NonStatic,
	End
};

enum class ECollideType {
	Sphere,
	Box,
	End
};

enum class EProjectionType {
	Perspective,
	Orthogonal,
	End
};

END

#define __ENGINE_ENUM_H__
#endif