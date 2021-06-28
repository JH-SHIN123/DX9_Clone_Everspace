#pragma once

#ifndef __LOAD_PROTOTYPE_H__

USING(Engine)

class CLoad_Prototype
{
public:
	CLoad_Prototype();
	~CLoad_Prototype();

public:
	static _bool Load_PassData_Object(const wstring& wstrObjectPrototypePath, PASSDATA_OBJECT& tPassDataObject);
};

#define __LOAD_PROTOTYPE_H__
#endif // !__LOAD_PROTOTYPE_H__
