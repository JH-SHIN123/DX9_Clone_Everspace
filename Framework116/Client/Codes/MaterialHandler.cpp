#include "stdafx.h"
#include "..\Headers\MaterialHandler.h"


CMaterialHandler::CMaterialHandler()
{
}


CMaterialHandler::~CMaterialHandler()
{
}

void CMaterialHandler::Set_RGBA(const _float & r, const _float & g, const _float & b, const _float & a, D3DMATERIAL9 * pMaterial)
{
	(*pMaterial).Diffuse.r	= r;
	(*pMaterial).Ambient.r	= r;
	(*pMaterial).Specular.r = r;
	(*pMaterial).Emissive.r = r;

	(*pMaterial).Diffuse.r	= g;
	(*pMaterial).Ambient.r	= g;
	(*pMaterial).Specular.r = g;
	(*pMaterial).Emissive.r = g;

	(*pMaterial).Diffuse.r	= b;
	(*pMaterial).Ambient.r	= b;
	(*pMaterial).Specular.r = b;
	(*pMaterial).Emissive.r = b;

	(*pMaterial).Diffuse.r	= a;
	(*pMaterial).Ambient.r	= a;
	(*pMaterial).Specular.r = a;
	(*pMaterial).Emissive.r = a;
}

void CMaterialHandler::Set_Power(const _float & Power, D3DMATERIAL9 * pMaterial)
{
	(*pMaterial).Power = Power;
}
